#include "daScript/misc/platform.h"

#include "daScript/simulate/runtime_table.h"

namespace das
{
    void table_clear ( Table & arr ) {
        if ( arr.lock ) {
            __context__->throw_error("clearing locked table");
            return;
        }
        memset(arr.hashes, 0, arr.capacity * sizeof(uint32_t));
        arr.size = 0;
    }

    void table_lock ( Table & arr ) {
        arr.lock ++;
        if ( arr.lock==0 ) {
            __context__->throw_error("table lock overflow");
        }
    }

    void table_unlock ( Table & arr ) {
        if ( arr.lock==0 ) {
            __context__->throw_error("table lock underflow");
        }
        arr.lock --;
    }

    // TableIterator

    size_t TableIterator::nextValid ( Table * tab, size_t index ) const {
        for (; index < tab->capacity; index++)
            if (tab->hashes[index] > HASH_KILLED32)
                break;
        return index;
    }

    bool TableIterator::first ( IteratorContext & itc ) {
        vec4f ll = source->eval();
        auto pTable = cast<Table *>::to(ll);
        table_lock(*pTable);
        size_t index = nextValid(pTable, 0);
        char * data    = getData(pTable);
        itc.value      = cast<char *>::from(data + index * stride);
        itc.table_end  = data + pTable->capacity * stride;
        itc.table      = pTable;
        return (bool) pTable->size;
    }

    bool TableIterator::next  ( IteratorContext & itc ) {
        char * data = cast<char *>::to(itc.value);
        char * tableData = getData(itc.table);
        size_t index = nextValid(itc.table, (data - tableData) / stride + 1 );
        data = tableData + index * stride;
        itc.value = cast<char *>::from(data);
        return data != itc.table_end;
    }

    void TableIterator::close ( IteratorContext & itc ) {
        if ( itc.table ) {
            table_unlock(*itc.table);
        }
    }

    // TableKeysIterator

    char * TableKeysIterator::getData ( Table * tab ) const {
        return tab->keys;
    }

    // TableValuesIterator

    char * TableValuesIterator::getData ( Table * tab ) const {
        return tab->data;
    }

    // delete

    vec4f SimNode_DeleteTable::eval ( ) {
        auto pTable = (Table *) subexpr->evalPtr();
        pTable = pTable + total - 1;
        for ( uint32_t i=0; i!=total; ++i, pTable-- ) {
            if ( pTable->data ) {
                if ( !pTable->lock ) {
                    uint32_t oldSize = pTable->capacity*(vts_add_kts + sizeof(uint32_t));
                    __context__->heap.free(pTable->data, oldSize);
                } else {
                    __context__->throw_error("deleting locked table");
                    return v_zero();
                }
            }
            memset ( pTable, 0, sizeof(Table) );
        }
        return v_zero();
    }
}

