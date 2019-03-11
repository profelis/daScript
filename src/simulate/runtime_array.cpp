#include "daScript/misc/platform.h"

#include "daScript/simulate/runtime_array.h"

namespace das
{
    void array_clear ( Array & arr ) {
        if ( arr.lock ) {
            __context__->throw_error("clearing locked array");
            return;
        }
        arr.size = 0;
    }

    void array_lock ( Array & arr ) {
        arr.lock ++;
        if ( arr.lock==0 ) {
            __context__->throw_error("array lock overflow");
        }
    }

    void array_unlock ( Array & arr ) {
        if ( arr.lock==0 ) {
            __context__->throw_error("array lock underflow");
        }
        arr.lock --;
    }

    void array_reserve(Array & arr, uint32_t newCapacity, uint32_t stride) {
        if (arr.lock) {
            __context__->throw_error("changing capacity of a locked array");
            return;
        }
        if (arr.capacity >= newCapacity) {
            return;
        }
        auto newData = (char *)__context__->heap.reallocate(arr.data, arr.capacity*stride, newCapacity*stride);
        if (!newData) {
            __context__->throw_error("out of linear allocator memory");
            return;
        }
        if (newData != arr.data) {
            memcpy(newData, arr.data, arr.capacity);
            arr.data = newData;
        }
        arr.capacity = newCapacity;
    }

    void array_resize ( Array & arr, uint32_t newSize, uint32_t stride, bool zero ) {
        if ( arr.lock ) {
            __context__->throw_error("resizing locked array");
            return;
        }
        if ( newSize > arr.capacity ) {
            uint32_t newCapacity = 1 << (32 - __builtin_clz (max(newSize,2u) - 1));
            newCapacity = max(newCapacity, 16u);
            array_reserve(arr, newCapacity, stride);
        }
        if ( zero && newSize>arr.size )
            memset ( arr.data + arr.size*stride, 0, (newSize-arr.size)*stride );
        arr.size = newSize;
    }

    // GoodArrayIterator

    bool GoodArrayIterator::first ( IteratorContext & itc )  {
        vec4f ll = source->eval();
        auto pArray = cast<Array *>::to(ll);
        array_lock(*pArray);
        char * data    = pArray->data;
        itc.value      = cast<char *>::from(data);
        itc.array_end  = data + pArray->size * stride;
        itc.array      = pArray;
        return (bool) pArray->size;
    }

    bool GoodArrayIterator::next  ( IteratorContext & itc )  {
        char * data = cast<char *>::to(itc.value) + stride;
        itc.value = cast<char *>::from(data);
        return data != itc.array_end;
    }

    void GoodArrayIterator::close ( IteratorContext & itc )  {
        if ( itc.array ) {
            array_unlock(*itc.array);
        }
    }

    vec4f SimNode_GoodArrayIterator::eval ( ) {
        return cast<Iterator *>::from(static_cast<GoodArrayIterator *>(this));
    }

    // FixedArrayIterator

    bool FixedArrayIterator::first ( IteratorContext & itc )  {
        vec4f ll = source->eval();
        char * data = cast<char *>::to(ll);
        itc.value = cast<char *>::from(data);
        itc.fixed_array_end = data + size*stride;
        return (bool) size;
    }

    bool FixedArrayIterator::next  ( IteratorContext & itc )  {
        char * data = cast<char *>::to(itc.value) + stride;
        itc.value = cast<char *>::from(data);
        return data != itc.fixed_array_end;
    }

    void FixedArrayIterator::close ( IteratorContext &  )  {
    }

    vec4f SimNode_FixedArrayIterator::eval ( ) {
        return cast<Iterator *>::from(static_cast<FixedArrayIterator *>(this));
    }

    // delete

    vec4f SimNode_DeleteArray::eval ( ) {
        auto pArray = (Array *) subexpr->evalPtr();
        pArray = pArray + total - 1;
        for ( uint32_t i=0; i!=total; ++i, pArray-- ) {
            if ( pArray->data ) {
                if ( !pArray->lock ) {
                    uint32_t oldSize = pArray->capacity*stride;
                    __context__->heap.free(pArray->data, oldSize);
                } else {
                    __context__->throw_error("deleting locked array");
                    return v_zero();
                }
            }
            memset ( pArray, 0, sizeof(Array) );
        }
        return v_zero();
    }
}
