#include "daScript/misc/platform.h"

#include "daScript/ast/ast.h"
#include "daScript/ast/ast_match.h"

#include "daScript/simulate/runtime_array.h"
#include "daScript/simulate/runtime_table.h"
#include "daScript/simulate/runtime_range.h"
#include "daScript/simulate/hash.h"

namespace das
{
    // common for move and copy

    SimNode * makeLocalCMResMove (const LineInfo & at, uint32_t offset, const ExpressionPtr & rE ) {
        const auto & rightType = *rE->type;
        // now, call with CMRES
        if ( rE->rtti_isCall() ) {
            auto cll = static_pointer_cast<ExprCall>(rE);
            if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = __context__->code->makeNode<SimNode_GetCMResOfs>(rE->at, offset);
                return right;
            }
        }
        // now, invoke with CMRES
        if ( rE->rtti_isInvoke() ) {
            auto cll = static_pointer_cast<ExprInvoke>(rE);
            if ( cll->isCopyOrMove() ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = __context__->code->makeNode<SimNode_GetCMResOfs>(rE->at, offset);
                return right;
            }
        }
        // now, to the regular move
        auto left = __context__->code->makeNode<SimNode_GetCMResOfs>(at, offset);
        auto right = rE->simulate();
        if ( rightType.isRef() ) {
            return __context__->code->makeNode<SimNode_MoveRefValue>(at, left, right, rightType.getSizeOf());
        } else {
            DAS_ASSERTF(0, "we are calling makeLocalCMResMove where expression on a right is not a referece."
                        "we should not be here, script compiler should have caught this during compilation."
                        "compiler later will likely report internal compilation error.");
            return nullptr;
        }
    }

    SimNode * makeLocalCMResCopy(const LineInfo & at, uint32_t offset, const ExpressionPtr & rE ) {
        const auto & rightType = *rE->type;
        assert ( rightType.canCopy() &&
                "we are calling makeLocalCMResCopy on a type, which can't be copied."
                "we should not be here, script compiler should have caught this during compilation."
                "compiler later will likely report internal compilation error.");
        auto right = rE->simulate();
        if ( rightType.isWorkhorseType() ) {
            if ( rightType.ref ) {
                return __context__->code->makeValueNode<SimNode_SetCMResRefT>(rightType.baseType,
                                                                         at, right, offset);
            } else {
                return __context__->code->makeValueNode<SimNode_SetCMResValueT>(rightType.baseType,
                                                                           at, right, offset);
            }
        }
        // now, call with CMRES
        if ( rE->rtti_isCall() ) {
            auto cll = static_pointer_cast<ExprCall>(rE);
            if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                SimNode_CallBase * rightC = (SimNode_CallBase *) right;
                rightC->cmresEval = __context__->code->makeNode<SimNode_GetCMResOfs>(rE->at, offset);
                return rightC;
            }
        }
        // now, invoke with CMRES
        if ( rE->rtti_isInvoke() ) {
            auto cll = static_pointer_cast<ExprInvoke>(rE);
            if ( cll->isCopyOrMove() ) {
                SimNode_CallBase * rightC = (SimNode_CallBase *) right;
                rightC->cmresEval = __context__->code->makeNode<SimNode_GetCMResOfs>(rE->at, offset);
                return rightC;
            }
        }
        // wo standard path
        auto left = __context__->code->makeNode<SimNode_GetCMResOfs>(rE->at, offset);
        if ( rightType.isRef() ) {
            if ( rightType.isWorkhorseType() ) {
                return __context__->code->makeValueNode<SimNode_CopyRefValueT>(rightType.baseType, at, left, right);
            } else {
                return __context__->code->makeNode<SimNode_CopyRefValue>(at, left, right, rightType.getSizeOf());
            }
        } else if ( rightType.isHandle() ) {
            auto resN = rightType.annotation->simulateCopy(at, left, right);
            if ( !resN ) {
                __context__->thisProgram->error("integration error, simulateCopy returned null",
                                           at, CompilationError::missing_node );
            }
            return resN;
        } else {
            return __context__->code->makeValueNode<SimNode_CopyValue>(rightType.baseType, at, left, right);
        }
    }

    SimNode * makeLocalRefMove (const LineInfo & at, uint32_t stackTop, uint32_t offset, const ExpressionPtr & rE ) {
        const auto & rightType = *rE->type;
        // now, call with CMRES
        if ( rE->rtti_isCall() ) {
            auto cll = static_pointer_cast<ExprCall>(rE);
            if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = __context__->code->makeNode<SimNode_GetLocalRefOff>(rE->at, stackTop, offset);
                return right;
            }
        }
        // now, invoke with CMRES
        if ( rE->rtti_isInvoke() ) {
            auto cll = static_pointer_cast<ExprInvoke>(rE);
            if ( cll->isCopyOrMove() ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = __context__->code->makeNode<SimNode_GetLocalRefOff>(rE->at, stackTop, offset);
                return right;
            }
        }
        // now, to the regular move
        auto left = __context__->code->makeNode<SimNode_GetLocalRefOff>(at, stackTop, offset);
        auto right = rE->simulate();
        if ( rightType.isRef() ) {
            return __context__->code->makeNode<SimNode_MoveRefValue>(at, left, right, rightType.getSizeOf());
        } else {
            DAS_ASSERTF(0, "we are calling makeLocalRefMove where expression on a right is not a referece."
                        "we should not be here, script compiler should have caught this during compilation."
                        "compiler later will likely report internal compilation error.");
            return nullptr;
        }
    }

    SimNode * makeLocalRefCopy(const LineInfo & at, uint32_t stackTop, uint32_t offset, const ExpressionPtr & rE ) {
        const auto & rightType = *rE->type;
        assert ( rightType.canCopy() &&
                "we are calling makeLocalRefCopy on a type, which can't be copied."
                "we should not be here, script compiler should have caught this during compilation."
                "compiler later will likely report internal compilation error.");
        auto right = rE->simulate();
        if ( rightType.isWorkhorseType() ) {
            if ( rightType.isRef() ) {
                return __context__->code->makeValueNode<SimNode_SetLocalRefRefOffT>(rightType.baseType,
                                                                            at, right, stackTop, offset);
            } else {
                return __context__->code->makeValueNode<SimNode_SetLocalValueRefOffT>(rightType.baseType,
                                                                            at, right, stackTop, offset);
            }
        }
        // now, call with CMRES
        if ( rE->rtti_isCall() ) {
            auto cll = static_pointer_cast<ExprCall>(rE);
            if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                SimNode_CallBase * rightC = (SimNode_CallBase *) right;
                rightC->cmresEval = __context__->code->makeNode<SimNode_GetLocalRefOff>(rE->at, stackTop, offset);
                return rightC;
            }
        }
        // now, invoke with CMRES
        if ( rE->rtti_isInvoke() ) {
            auto cll = static_pointer_cast<ExprInvoke>(rE);
            if ( cll->isCopyOrMove() ) {
                SimNode_CallBase * rightC = (SimNode_CallBase *) right;
                rightC->cmresEval = __context__->code->makeNode<SimNode_GetLocalRefOff>(rE->at, stackTop, offset);
                return rightC;
            }
        }
        // wo standard path
        auto left = __context__->code->makeNode<SimNode_GetLocalRefOff>(rE->at, stackTop, offset);
        if ( rightType.isRef() ) {
            if ( rightType.isWorkhorseType() ) {
                return __context__->code->makeValueNode<SimNode_CopyRefValueT>(rightType.baseType, at, left, right);
            } else {
                return __context__->code->makeNode<SimNode_CopyRefValue>(at, left, right, rightType.getSizeOf());
            }
        } else if ( rightType.isHandle() ) {
            auto resN = rightType.annotation->simulateCopy(at, left, right);
            if ( !resN ) {
                __context__->thisProgram->error("integration error, simulateCopy returned null",
                                           at, CompilationError::missing_node );
            }
            return resN;
        } else {
            return __context__->code->makeValueNode<SimNode_CopyValue>(rightType.baseType, at, left, right);
        }
    }

    SimNode * makeLocalMove (const LineInfo & at, uint32_t stackTop, const ExpressionPtr & rE ) {
        const auto & rightType = *rE->type;
        // now, call with CMRES
        if ( rE->rtti_isCall() ) {
            auto cll = static_pointer_cast<ExprCall>(rE);
            if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = __context__->code->makeNode<SimNode_GetLocal>(rE->at, stackTop);
                return right;
            }
        }
        // now, invoke with CMRES
        if ( rE->rtti_isInvoke() ) {
            auto cll = static_pointer_cast<ExprInvoke>(rE);
            if ( cll->isCopyOrMove() ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = __context__->code->makeNode<SimNode_GetLocal>(rE->at, stackTop);
                return right;
            }
        }
        // now, to the regular move
        auto left = __context__->code->makeNode<SimNode_GetLocal>(at, stackTop);
        auto right = rE->simulate();
        if ( rightType.isRef() ) {
            return __context__->code->makeNode<SimNode_MoveRefValue>(at, left, right, rightType.getSizeOf());
        } else {
            DAS_ASSERTF(0, "we are calling makeLocalMove where expression on a right is not a referece."
                        "we should not be here, script compiler should have caught this during compilation."
                        "compiler later will likely report internal compilation error.");
            return nullptr;
        }
    }

    SimNode * makeLocalCopy(const LineInfo & at, uint32_t stackTop, const ExpressionPtr & rE ) {
        const auto & rightType = *rE->type;
        assert ( rightType.canCopy() &&
                "we are calling makeLocalCopy on a type, which can't be copied."
                "we should not be here, script compiler should have caught this during compilation."
                "compiler later will likely report internal compilation error.");
        // TODO:
        //  expand to (while managing combinatorics explosion, policy?)
        //      1. local ref variables (iterator results etc)
        //      2. global variables
        //      3. arguments
        //      4. blocks
        //      5. common cross-copy scenarios
        if ( rightType.isWorkhorseType() ) {
            if ( rE->rtti_isVar() ) {
                auto rvar = static_pointer_cast<ExprVar>(rE);
                if ( rvar->local && !rvar->variable->type->ref && !rvar->variable->aliasCMRES ) {
                    return __context__->code->makeValueNode<SimNode_CopyLocal2LocalT>(rightType.baseType,
                                                                                at, stackTop,
                                                                                rvar->variable->stackTop);
                }
            }
            auto right = rE->simulate();
            if ( rightType.ref ) {
                return __context__->code->makeValueNode<SimNode_SetLocalRefT>(rightType.baseType,
                                                                        at, right, stackTop);
            } else {
                return __context__->code->makeValueNode<SimNode_SetLocalValueT>(rightType.baseType,
                                                                          at, right, stackTop);
            }
        }
        // now, call with CMRES
        if ( rE->rtti_isCall() ) {
            auto cll = static_pointer_cast<ExprCall>(rE);
            if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = __context__->code->makeNode<SimNode_GetLocal>(rE->at, stackTop);
                return right;
            }
        }
        // now, invoke with CMRES
        if ( rE->rtti_isInvoke() ) {
            auto cll = static_pointer_cast<ExprInvoke>(rE);
            if ( cll->isCopyOrMove() ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = __context__->code->makeNode<SimNode_GetLocal>(rE->at, stackTop);
                return right;
            }
        }
        // now, to the regular copy
        auto left = __context__->code->makeNode<SimNode_GetLocal>(rE->at, stackTop);
        auto right = rE->simulate();
        if ( rightType.isRef() ) {
            if ( rightType.isWorkhorseType() ) {
                return __context__->code->makeValueNode<SimNode_CopyRefValueT>(rightType.baseType, at, left, right);
            } else {
                return __context__->code->makeNode<SimNode_CopyRefValue>(at, left, right, rightType.getSizeOf());
            }
        } else if ( rightType.isHandle() ) {
            auto resN = rightType.annotation->simulateCopy(at, left, right);
            if ( !resN ) {
                __context__->thisProgram->error("integration error, simulateCopy returned null",
                                           at, CompilationError::missing_node );
            }
            return resN;
        } else {
            return __context__->code->makeValueNode<SimNode_CopyValue>(rightType.baseType, at, left, right);
        }
    }

    SimNode * makeCopy(const LineInfo & at, const ExpressionPtr & lE, const ExpressionPtr & rE ) {
        const auto & rightType = *rE->type;
        assert ( rightType.canCopy() &&
                "we are calling makeCopy on a type, which can't be copied."
                "we should not be here, script compiler should have caught this during compilation."
                "compiler later will likely report internal compilation error.");
        // TODO:
        //  expand to (while managing combinatorics explosion, policy?)
        //      1. local ref variables (iterator results etc)
        //      2. global variables
        //      3. arguments
        //      4. blocks
        //      5. common cross-copy scenarios
        if ( rightType.isWorkhorseType() && lE->rtti_isVar() ) {
            auto var = static_pointer_cast<ExprVar>(lE);
            if ( var->local && !var->variable->type->ref ) {
                if ( var->variable->aliasCMRES ) {
                    auto right = rE->simulate();
                    if ( rightType.isWorkhorseType() ) {
                        if ( rightType.ref ) {
                            return __context__->code->makeValueNode<SimNode_SetCMResRefT>(rightType.baseType,
                                                                                     at, right, 0);
                        } else {
                            return __context__->code->makeValueNode<SimNode_SetCMResValueT>(rightType.baseType,
                                                                                       at, right, 0);
                        }
                    }
                } else {
                    if ( rE->rtti_isVar() ) {
                        auto rvar = static_pointer_cast<ExprVar>(rE);
                        if ( rvar->local && !rvar->variable->type->ref&& !rvar->variable->aliasCMRES ) {
                            return __context__->code->makeValueNode<SimNode_CopyLocal2LocalT>(rightType.baseType,
                                    at, var->variable->stackTop, rvar->variable->stackTop);
                        }
                    }
                    auto right = rE->simulate();
                    if ( rightType.ref ) {
                        return __context__->code->makeValueNode<SimNode_SetLocalRefT>(rightType.baseType,
                                    at, right, var->variable->stackTop);
                    } else {
                        return __context__->code->makeValueNode<SimNode_SetLocalValueT>(rightType.baseType,
                                    at, right, var->variable->stackTop);
                    }
                }
            }
        }
        // now, call with CMRES
        if ( rE->rtti_isCall() ) {
            auto cll = static_pointer_cast<ExprCall>(rE);
            if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = lE->simulate();
                return right;
            }
        }
        // now, invoke with CMRES
        if ( rE->rtti_isInvoke() ) {
            auto cll = static_pointer_cast<ExprInvoke>(rE);
            if ( cll->isCopyOrMove() ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = lE->simulate();
                return right;
            }
        }
        // now, to the regular copy
        auto left = lE->simulate();
        auto right = rE->simulate();
        if ( rightType.isRef() ) {
            if ( rightType.isWorkhorseType() ) {
                return __context__->code->makeValueNode<SimNode_CopyRefValueT>(rightType.baseType, at, left, right);
            } else {
                return __context__->code->makeNode<SimNode_CopyRefValue>(at, left, right, rightType.getSizeOf());
            }
        } else if ( rightType.isHandle() ) {
            auto resN = rightType.annotation->simulateCopy(at, left, right);
            if ( !resN ) {
                __context__->thisProgram->error("integration error, simulateCopy returned null",
                                           at, CompilationError::missing_node );
            }
            return resN;
        } else {
            return __context__->code->makeValueNode<SimNode_CopyValue>(rightType.baseType, at, left, right);
        }
    }

    SimNode * makeMove (const LineInfo & at, const ExpressionPtr & lE, const ExpressionPtr & rE ) {
        const auto & rightType = *rE->type;
        // now, call with CMRES
        if ( rE->rtti_isCall() ) {
            auto cll = static_pointer_cast<ExprCall>(rE);
            if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = lE->simulate();
                return right;
            }
        }
        // now, invoke with CMRES
        if ( rE->rtti_isInvoke() ) {
            auto cll = static_pointer_cast<ExprInvoke>(rE);
            if ( cll->isCopyOrMove() ) {
                SimNode_CallBase * right = (SimNode_CallBase *) rE->simulate();
                right->cmresEval = lE->simulate();
                return right;
            }
        }
        // now to the regular one
        if ( rightType.isRef() ) {
            auto left = lE->simulate();
            auto right = rE->simulate();
            return __context__->code->makeNode<SimNode_MoveRefValue>(at, left, right, rightType.getSizeOf());
        } else {
            DAS_ASSERTF(0, "we are calling makeMove where expression on a right is not a referece."
                   "we should not be here, script compiler should have caught this during compilation."
                   "compiler later will likely report internal compilation error.");
            return nullptr;
        }
    }

    SimNode * Function::simulate () const {
        if ( builtIn ) {
            DAS_ASSERTF(0, "can only simulate non built-in function");
            return nullptr;
        }
        if ( fastCall ) {
            assert(totalStackSize == sizeof(Prologue) && "function can't allocate stack");
            assert((result->isWorkhorseType() || result->isVoid()) && "fastcall can only return a workhorse type");
            assert(body->rtti_isBlock() && "function must contain a block");
            auto block = static_pointer_cast<ExprBlock>(body);
            assert(block->list.size()==1 && "fastcall is only one expr in a function body");
            if ( block->list.back()->rtti_isReturn() ) {
                assert(block->list.back()->rtti_isReturn() && "fastcall body expr is return");
                auto retE = static_pointer_cast<ExprReturn>(block->list.back());
                assert(retE->subexpr && "fastcall must return a value");
                return retE->subexpr->simulate();
            } else {
                return block->list.back()->simulate();
            }
        } else {
            return body->simulate();
        }
    }

    SimNode * Expression::trySimulate (uint32_t, Type ) const {
        return nullptr;
    }

    void ExprMakeLocal::setRefSp ( bool ref, bool cmres, uint32_t sp, uint32_t off ) {
        useStackRef = ref;
        useCMRES = cmres;
        doesNotNeedSp = true;
        doesNotNeedInit = true;
        stackTop = sp;
        extraOffset = off;
    }

    vector<SimNode *> ExprMakeLocal::simulateLocal ( ) const {
        return vector<SimNode *>();
    }

    void ExprMakeStructure::setRefSp ( bool ref, bool cmres, uint32_t sp, uint32_t off ) {
        ExprMakeLocal::setRefSp(ref, cmres, sp, off);
        int total = int(structs.size());
        int stride = makeType->getStride();
        // we go through all fields, and if its [[ ]] field
        // we tell it to piggy-back on our current sp, with appropriate offset
        for ( int index=0; index != total; ++index ) {
            auto & fields = structs[index];
            for ( const auto & decl : *fields ) {
                auto field = makeType->structType->findField(decl->name);
                assert(field && "should have failed in type infer otherwise");
                if ( decl->value->rtti_isMakeLocal() ) {
                    uint32_t offset =  extraOffset + index*stride + field->offset;
                    auto mkl = static_pointer_cast<ExprMakeLocal>(decl->value);
                    mkl->setRefSp(ref, cmres, sp, offset);
                } else if ( decl->value->rtti_isCall() ) {
                    auto cll = static_pointer_cast<ExprCall>(decl->value);
                    if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                        cll->doesNotNeedSp = true;
                    }
                } else if ( decl->value->rtti_isInvoke() ) {
                    auto cll = static_pointer_cast<ExprInvoke>(decl->value);
                    if ( cll->isCopyOrMove() ) {
                        cll->doesNotNeedSp = true;
                    }
                }
            }
        }
    }

    vector<SimNode *> ExprMakeStructure::simulateLocal () const {
        vector<SimNode *> simlist;
        // init with 0
        int total = int(structs.size());
        int stride = makeType->getStride();
        if ( !doesNotNeedInit ) {
            SimNode * init0;
            if ( useCMRES ) {
                init0 = __context__->code->makeNode<SimNode_InitLocalCMRes>(at,extraOffset,stride * total);
            } else if ( useStackRef ) {
                init0 = __context__->code->makeNode<SimNode_InitLocalRef>(at,stackTop,extraOffset,stride * total);
            } else {
                init0 = __context__->code->makeNode<SimNode_InitLocal>(at,stackTop + extraOffset,stride * total);
            }
            simlist.push_back(init0);
        }
        for ( int index=0; index != total; ++index ) {
            auto & fields = structs[index];
            for ( const auto & decl : *fields ) {
                auto field = makeType->structType->findField(decl->name);
                assert(field && "should have failed in type infer otherwise");
                uint32_t offset =  extraOffset + index*stride + field->offset;
                SimNode * cpy;
                if ( decl->value->rtti_isMakeLocal() ) {
                    // so what happens here, is we ask it for the generated commands and append it to this list only
                    auto mkl = static_pointer_cast<ExprMakeLocal>(decl->value);
                    auto lsim = mkl->simulateLocal();
                    simlist.insert(simlist.end(), lsim.begin(), lsim.end());
                    continue;
                } else if ( useCMRES ) {
                    if ( decl->moveSemantic ){
                        cpy = makeLocalCMResMove(at,offset,decl->value);
                    } else {
                        cpy = makeLocalCMResCopy(at,offset,decl->value);
                    }
                } else if ( useStackRef ) {
                    if ( decl->moveSemantic ){
                        cpy = makeLocalRefMove(at,stackTop,offset,decl->value);
                    } else {
                        cpy = makeLocalRefCopy(at,stackTop,offset,decl->value);
                    }
                } else {
                    if ( decl->moveSemantic ){
                        cpy = makeLocalMove(at,stackTop+offset,decl->value);
                    } else {
                        cpy = makeLocalCopy(at,stackTop+offset,decl->value);
                    }
                }
                if ( !cpy ) {
                    __context__->thisProgram->error("internal compilation error, can't generate structure initialization", at);
                }
                simlist.push_back(cpy);
            }
        }
        return simlist;
    }

    SimNode * ExprMakeStructure::simulate () const {
        SimNode_Block * block;
        if ( useCMRES ) {
            block = __context__->code->makeNode<SimNode_MakeLocalCMRes>(at);
        } else {
            block = __context__->code->makeNode<SimNode_MakeLocal>(at, stackTop);
        }
        auto simlist = simulateLocal();
        block->total = int(simlist.size());
        block->list = (SimNode **) __context__->code->allocate(sizeof(SimNode *)*block->total);
        for ( uint32_t i = 0; i != block->total; ++i )
            block->list[i] = simlist[i];
        return block;
    }

    void ExprMakeArray::setRefSp ( bool ref, bool cmres, uint32_t sp, uint32_t off ) {
        ExprMakeLocal::setRefSp(ref, cmres, sp, off);
        int total = int(values.size());
        uint32_t stride = recordType->getSizeOf();
        for ( int index=0; index != total; ++index ) {
            auto & val = values[index];
            if ( val->rtti_isMakeLocal() ) {
                uint32_t offset =  extraOffset + index*stride;
                auto mkl = static_pointer_cast<ExprMakeLocal>(val);
                mkl->setRefSp(ref, cmres, sp, offset);
            } else if ( val->rtti_isCall() ) {
                auto cll = static_pointer_cast<ExprCall>(val);
                if ( cll->func->copyOnReturn || cll->func->moveOnReturn ) {
                    cll->doesNotNeedSp = true;
                }
            } else if ( val->rtti_isInvoke() ) {
                auto cll = static_pointer_cast<ExprInvoke>(val);
                if ( cll->isCopyOrMove() ) {
                    cll->doesNotNeedSp = true;
                }
            }
        }
    }

    vector<SimNode *> ExprMakeArray::simulateLocal () const {
        vector<SimNode *> simlist;
        // init with 0
        int total = int(values.size());
        uint32_t stride = recordType->getSizeOf();
        if ( !doesNotNeedInit ) {
            SimNode * init0;
            if ( useCMRES ) {
                init0 = __context__->code->makeNode<SimNode_InitLocalCMRes>(at,extraOffset,stride * total);
            } else if ( useStackRef ) {
                init0 = __context__->code->makeNode<SimNode_InitLocalRef>(at,stackTop,extraOffset,stride * total);
            } else {
                init0 = __context__->code->makeNode<SimNode_InitLocal>(at,stackTop + extraOffset,stride * total);
            }
            simlist.push_back(init0);
        }
        for ( int index=0; index != total; ++index ) {
            auto & val = values[index];
            uint32_t offset = extraOffset + index*stride;
            SimNode * cpy;
            if ( val->rtti_isMakeLocal() ) {
                // so what happens here, is we ask it for the generated commands and append it to this list only
                auto mkl = static_pointer_cast<ExprMakeLocal>(val);
                auto lsim = mkl->simulateLocal();
                simlist.insert(simlist.end(), lsim.begin(), lsim.end());
                continue;
            } else if ( useCMRES ) {
                cpy = makeLocalCMResCopy(at,offset,val);
            } else if ( useStackRef ) {
                cpy = makeLocalRefCopy(at,stackTop,offset,val);
            } else {
                cpy = makeLocalCopy(at,stackTop+offset,val);
            }
            if ( !cpy ) {
                __context__->thisProgram->error("internal compilation error, can't generate array initialization", at);
            }
            simlist.push_back(cpy);
        }
        return simlist;
    }

    SimNode * ExprMakeArray::simulate () const {
        SimNode_Block * block;
        if ( useCMRES ) {
            block = __context__->code->makeNode<SimNode_MakeLocalCMRes>(at);
        } else {
            block = __context__->code->makeNode<SimNode_MakeLocal>(at, stackTop);
        }
        auto simlist = simulateLocal();
        block->total = int(simlist.size());
        block->list = (SimNode **) __context__->code->allocate(sizeof(SimNode *)*block->total);
        for ( uint32_t i = 0; i != block->total; ++i )
            block->list[i] = simlist[i];
        return block;
    }

    SimNode * ExprRef2Value::simulate () const {
        return GetR2V(at, type, subexpr->simulate());
    }

    SimNode * ExprAddr::simulate () const {
        assert(func->index>=0 && "how, we specified in the unused");
        Func fn; fn.index = func->index + 1;
        return __context__->code->makeNode<SimNode_ConstValue>(at,cast<Func>::from(fn));
    }

    SimNode * ExprPtr2Ref::simulate () const {
        return __context__->code->makeNode<SimNode_Ptr2Ref>(at,subexpr->simulate());
    }

    SimNode * ExprNullCoalescing::simulate () const {
        if ( type->ref ) {
            return __context__->code->makeNode<SimNode_NullCoalescingRef>(at,subexpr->simulate(),defaultValue->simulate());
        } else {
            return __context__->code->makeValueNode<SimNode_NullCoalescing>(type->baseType,at,subexpr->simulate(),defaultValue->simulate());
        }
    }

    SimNode * ExprConst::simulate () const {
        return __context__->code->makeNode<SimNode_ConstValue>(at,value);
    }

    SimNode * ExprConstString::simulate () const {
        char * str = __context__->code->allocateString(text);
        return __context__->code->makeNode<SimNode_ConstValue>(at,cast<char *>::from(str));
    }

    SimNode * ExprStaticAssert::simulate () const {
        return nullptr;
    }

    SimNode * ExprAssert::simulate () const {
        string message;
        if ( arguments.size()==2 && arguments[1]->rtti_isStringConstant() )
            message = static_pointer_cast<ExprConstString>(arguments[1])->getValue();
        return __context__->code->makeNode<SimNode_Assert>(at,arguments[0]->simulate(),__context__->code->allocateString(message));
    }

    SimNode * ExprDebug::simulate () const {
        TypeInfo * pTypeInfo = __context__->thisHelper->makeTypeInfo(nullptr, arguments[0]->type);
        string message;
        if ( arguments.size()==2 && arguments[1]->rtti_isStringConstant() )
            message = static_pointer_cast<ExprConstString>(arguments[1])->getValue();
        return __context__->code->makeNode<SimNode_Debug>(at,
                                               arguments[0]->simulate(),
                                               pTypeInfo,
                                               __context__->code->allocateString(message));
    }

    SimNode * ExprMakeLambda::simulate () const {
        DAS_ASSERTF(0, "we should not be here ever, ExprMakeLambda should completly fold during type inference.");
        __context__->thisProgram->error("internal compilation error, generating node for ExprMakeLambda", at);
        return nullptr;
    }

    SimNode * ExprMakeBlock::simulate () const {
        uint32_t argSp = static_pointer_cast<ExprBlock>(block)->stackTop;
        return __context__->code->makeNode<SimNode_MakeBlock>(at,block->simulate(),argSp,stackTop);
    }

    bool ExprInvoke::isCopyOrMove() const {
        auto blockT = arguments[0]->type;
        return blockT->firstType && blockT->firstType->isRefType();
    }

    SimNode * ExprInvoke::simulate () const {
        auto blockT = arguments[0]->type;
        SimNode_CallBase * pInvoke;
        if ( isCopyOrMove() ) {
            auto getSp = __context__->code->makeNode<SimNode_GetLocal>(at,stackTop);
            if ( blockT->baseType==Type::tBlock ) {
                pInvoke = (SimNode_CallBase *) __context__->code->makeNodeUnroll<SimNode_InvokeAndCopyOrMove>(
                                                    int(arguments.size()), at, getSp);
            } else if ( blockT->baseType==Type::tFunction ) {
                pInvoke = (SimNode_CallBase *) __context__->code->makeNodeUnroll<SimNode_InvokeAndCopyOrMoveFn>(
                                                    int(arguments.size()), at, getSp);
            } else {
                pInvoke = (SimNode_CallBase *) __context__->code->makeNodeUnroll<SimNode_InvokeAndCopyOrMoveLambda>(
                                                    int(arguments.size()), at, getSp);
            }
        } else {
            if ( blockT->baseType==Type::tBlock ) {
                pInvoke = (SimNode_CallBase *) __context__->code->makeNodeUnroll<SimNode_Invoke>(int(arguments.size()),at);
            } else if ( blockT->baseType==Type::tFunction ) {
                pInvoke = (SimNode_CallBase *) __context__->code->makeNodeUnroll<SimNode_InvokeFn>(int(arguments.size()),at);
            } else {
                pInvoke = (SimNode_CallBase *) __context__->code->makeNodeUnroll<SimNode_InvokeLambda>(int(arguments.size()),at);
            }
        }
        pInvoke->debugInfo = at;
        if ( int nArg = (int) arguments.size() ) {
            pInvoke->arguments = (SimNode **) __context__->code->allocate(nArg * sizeof(SimNode *));
            pInvoke->nArguments = nArg;
            for ( int a=0; a!=nArg; ++a ) {
                pInvoke->arguments[a] = arguments[a]->simulate();
            }
        } else {
            pInvoke->arguments = nullptr;
            pInvoke->nArguments = 0;
        }
        return pInvoke;
    }

    SimNode * ExprErase::simulate () const {
        auto cont = arguments[0]->simulate();
        auto val = arguments[1]->simulate();
        if ( arguments[0]->type->isGoodTableType() ) {
            uint32_t valueTypeSize = arguments[0]->type->secondType->getSizeOf();
            return __context__->code->makeValueNode<SimNode_TableErase>(arguments[0]->type->firstType->baseType, at, cont, val, valueTypeSize);
        } else {
            DAS_ASSERTF(0, "we should not even be here. erase can only accept tables. infer type should have failed.");
            __context__->thisProgram->error("internal compilation error, generating erase for non-table type", at);
            return nullptr;
        }
    }

    SimNode * ExprFind::simulate () const {
        auto cont = arguments[0]->simulate();
        auto val = arguments[1]->simulate();
        if ( arguments[0]->type->isGoodTableType() ) {
            uint32_t valueTypeSize = arguments[0]->type->secondType->getSizeOf();
            return __context__->code->makeValueNode<SimNode_TableFind>(arguments[0]->type->firstType->baseType, at, cont, val, valueTypeSize);
        } else {
            DAS_ASSERTF(0, "we should not even be here. find can only accept tables. infer type should have failed.");
            __context__->thisProgram->error("internal compilation error, generating find for non-table type", at);
            return nullptr;
        }
    }

    SimNode * ExprSizeOf::simulate () const {
        uint32_t size = typeexpr->getSizeOf();
        return __context__->code->makeNode<SimNode_ConstValue>(at,cast<uint32_t>::from(size));
    }

    SimNode * ExprTypeName::simulate () const {
        auto pName = __context__->code->allocateString(typeexpr->describe(false));
        return __context__->code->makeNode<SimNode_ConstValue>(at,cast<char *>::from(pName));
    }
    
    SimNode * ExprDelete::simulate () const {
        uint32_t total = uint32_t(subexpr->type->getCountOf());
        auto sube = subexpr->simulate();
        if ( subexpr->type->baseType==Type::tArray ) {
            auto stride = subexpr->type->firstType->getSizeOf();
            return __context__->code->makeNode<SimNode_DeleteArray>(at, sube, total, stride);
        } else if ( subexpr->type->baseType==Type::tTable ) {
            auto vts_add_kts = subexpr->type->firstType->getSizeOf() +
                subexpr->type->secondType->getSizeOf();
            return __context__->code->makeNode<SimNode_DeleteTable>(at, sube, total, vts_add_kts);
        } else if ( subexpr->type->baseType==Type::tPointer ) {
            if ( subexpr->type->firstType->baseType==Type::tStructure ) {
                auto structSize = subexpr->type->firstType->getSizeOf();
                return __context__->code->makeNode<SimNode_DeleteStructPtr>(at, sube, total, structSize);
            } else {
                auto ann = subexpr->type->firstType->annotation;
                assert(ann->canDeletePtr() && "has to be able to delete ptr");
                auto resN = ann->simulateDeletePtr(at, sube, total);
                if ( !resN ) {
                    __context__->thisProgram->error("integration error, simulateDelete returned null",
                                               at, CompilationError::missing_node );
                }
                return resN;
            }
        } else if ( subexpr->type->baseType==Type::tHandle ) {
            auto ann = subexpr->type->annotation;
            assert(ann->canDelete() && "has to be able to delete");
            auto resN =  ann->simulateDelete(at, sube, total);
            if ( !resN ) {
                __context__->thisProgram->error("integration error, simulateDelete returned null",
                                           at, CompilationError::missing_node );
            }
            return resN;
        } else {
            DAS_ASSERTF(0, "we should not be here. this is delete for unsupported type. infer types should have failed.");
            __context__->thisProgram->error("internal compilation error, generating node for unsupported ExprDelete", at);
            return nullptr;
        }
    }
    SimNode * ExprCast::trySimulate (uint32_t extraOffset, Type r2vType ) const {
        return subexpr->trySimulate(extraOffset, r2vType);
    }

    SimNode * ExprCast::simulate () const {
        return subexpr->simulate();
    }

    SimNode * ExprAscend::simulate () const {
        auto se = subexpr->simulate();
        auto bytes = subexpr->type->getSizeOf();
        if ( useStackRef ) {
            return __context__->code->makeNode<SimNode_AscendAndRef<false>>(at, se, bytes, stackTop);
        } else {
            return __context__->code->makeNode<SimNode_Ascend<false>>(at, se, bytes);
        }
    }

    SimNode * ExprNew::simulate () const {
        SimNode * newNode;
        if ( typeexpr->baseType == Type::tHandle ) {
            assert(typeexpr->annotation->canNew() && "how???");
            newNode = typeexpr->annotation->simulateGetNew(at);
            if ( !newNode ) {
                __context__->thisProgram->error("integration error, simulateGetNew returned null",
                                           at, CompilationError::missing_node );
            }
        } else {
            int32_t bytes = type->firstType->getSizeOf();
            if ( initializer ) {
                auto pCall = (SimNode_CallBase *) __context__->code->makeNodeUnroll<SimNode_NewWithInitializer>(int(arguments.size()),at,bytes);
                pCall->cmresEval = nullptr;
                newNode = ExprCall::simulateCall(func->shared_from_this(), this, pCall);
            } else {
                newNode = __context__->code->makeNode<SimNode_New>(at,bytes);
            }
        }
        if ( type->dim.size() ) {
            uint32_t count = type->getCountOf();
            return __context__->code->makeNode<SimNode_NewArray>(at,newNode,stackTop,count);
        } else {
            return newNode;
        }
    }

    SimNode * ExprAt::trySimulate (uint32_t extraOffset, Type r2vType ) const {
        if ( subexpr->type->isVectorType() ) {
            return nullptr;
        } else if ( subexpr->type->isGoodTableType() ) {
            return nullptr;
        } else if ( subexpr->type->isHandle() ) {
            SimNode * result;
            if ( r2vType!=Type::none ) {
                result = subexpr->type->annotation->simulateGetAtR2V(at, index->type, subexpr, index, extraOffset);
                if ( !result ) {
                    __context__->thisProgram->error("integration error, simulateGetAtR2V returned null",
                                               at, CompilationError::missing_node );
                }
            } else {
                result = subexpr->type->annotation->simulateGetAt(at, index->type, subexpr, index, extraOffset);
                if ( !result ) {
                    __context__->thisProgram->error("integration error, simulateGetAt returned null",
                                               at, CompilationError::missing_node );
                }
            }
            return result;
        } else if ( subexpr->type->isGoodArrayType() ) {
            auto prv = subexpr->simulate();
            auto pidx = index->simulate();
            uint32_t stride = subexpr->type->firstType->getSizeOf();
            if ( r2vType!=Type::none ) {
                return __context__->code->makeValueNode<SimNode_ArrayAtR2V>(r2vType, at, prv, pidx, stride, extraOffset);
            } else {
                return __context__->code->makeNode<SimNode_ArrayAt>(at, prv, pidx, stride, extraOffset);
            }
        } else {
            uint32_t range = subexpr->type->dim.back();
            uint32_t stride = subexpr->type->getStride();
            if ( index->rtti_isConstant() ) {
                // if its constant index, like a[3]..., we try to let node bellow simulate
                auto idxCE = static_pointer_cast<ExprConst>(index);
                uint32_t idxC = cast<uint32_t>::to(idxCE->value);
                if ( idxC >= range ) {
                    __context__->thisProgram->error("index out of range", at, CompilationError::index_out_of_range);
                    return nullptr;
                }
                auto tnode = subexpr->trySimulate(extraOffset + idxC*stride, r2vType);
                if ( tnode ) {
                    return tnode;
                }
            }
            // regular scenario
            auto prv = subexpr->simulate();
            auto pidx = index->simulate();
            if ( r2vType!=Type::none ) {
                return __context__->code->makeValueNode<SimNode_AtR2V>(r2vType, at, prv, pidx, stride, extraOffset, range);
            } else {
                return __context__->code->makeNode<SimNode_At>(at, prv, pidx, stride, extraOffset, range);
            }
        }
    }

    SimNode * ExprAt::simulate () const {

        if ( subexpr->type->isVectorType() ) {
            auto prv = subexpr->simulate();
            auto pidx = index->simulate();
            uint32_t range = subexpr->type->getVectorDim();
            uint32_t stride = type->getSizeOf();
            if ( subexpr->type->ref ) {
                auto res = __context__->code->makeNode<SimNode_At>(at, prv, pidx, stride, 0, range);
                if ( r2v ) {
                    return ExprRef2Value::GetR2V(at, type, res);
                } else {
                    return res;
                }
            } else {
                switch ( type->baseType ) {
                    case tInt:      return __context__->code->makeNode<SimNode_AtVector<int32_t>>(at, prv, pidx, range);
                    case tUInt:     return __context__->code->makeNode<SimNode_AtVector<uint32_t>>(at, prv, pidx, range);
                    case tFloat:    return __context__->code->makeNode<SimNode_AtVector<float>>(at, prv, pidx, range);
                    default:
                        DAS_ASSERTF(0, "we should not even be here. infer type should have failed on unsupported_vector[blah]");
                        __context__->thisProgram->error("internal compilation error, generating vector at for unsupported vector type.", at);
                        return nullptr;
                }
            }
        } else if ( subexpr->type->isGoodTableType() ) {
            auto prv = subexpr->simulate();
            auto pidx = index->simulate();
            uint32_t valueTypeSize = subexpr->type->secondType->getSizeOf();
            auto res = __context__->code->makeValueNode<SimNode_TableIndex>(subexpr->type->firstType->baseType, at, prv, pidx, valueTypeSize, 0);
            if ( r2v ) {
                return ExprRef2Value::GetR2V(at, type, res);
            } else {
                return res;
            }
        } else {
            if ( r2v ) {
                return trySimulate(0, type->baseType);
            } else {
                return trySimulate(0, Type::none);
            }
        }
    }
    
    vector<SimNode *> ExprBlock::collectExpressions ( const vector<ExpressionPtr> & lis ) const {
        vector<SimNode *> simlist;
        for ( auto & node : lis ) {
            if ( node->rtti_isLet()) {
                shared_ptr<ExprLet> pLet = static_pointer_cast<ExprLet>(node);
                if (!pLet->subexpr) {
                    auto letInit = ExprLet::simulateInit(pLet.get());
                    simlist.insert(simlist.end(), letInit.begin(), letInit.end());
                    continue;
                }
            }
            if ( auto simE = node->simulate() ) {
                simlist.push_back(simE);
            }
        }
        return simlist;
    }
    
    void ExprBlock::simulateFinal ( SimNode_Final * block ) const {
        vector<SimNode *> simFList = collectExpressions(finalList);
        block->totalFinal = int(simFList.size());
        if ( block->totalFinal ) {
            block->finalList = (SimNode **) __context__->code->allocate(sizeof(SimNode *)*block->totalFinal);
            for ( uint32_t i = 0; i != block->totalFinal; ++i )
                block->finalList[i] = simFList[i];
        }
    }

    void ExprBlock::simulateBlock ( SimNode_Block * block ) const {
        vector<SimNode *> simlist = collectExpressions(list);
        block->total = int(simlist.size());
        if ( block->total ) {
            block->list = (SimNode **) __context__->code->allocate(sizeof(SimNode *)*block->total);
            for ( uint32_t i = 0; i != block->total; ++i )
                block->list[i] = simlist[i];
        }
    }

    SimNode * ExprBlock::simulate () const {
        vector<SimNode *> simlist = collectExpressions(list);
        // TODO: what if list size is 0?
        if ( simlist.size()!=1 || isClosure || finalList.size() ) {
            auto block = isClosure ? __context__->code->makeNode<SimNode_ClosureBlock>(at, type!=nullptr && type->baseType!=Type::tVoid, annotationData)
                : __context__->code->makeNode<SimNode_Block>(at);
            block->total = int(simlist.size());
            if ( block->total ) {
                block->list = (SimNode **) __context__->code->allocate(sizeof(SimNode *)*block->total);
                for ( uint32_t i = 0; i != block->total; ++i )
                    block->list[i] = simlist[i];
            }
            if ( !inTheLoop ) {
                simulateFinal(block);
            }
            return block;
        } else {
            return simlist[0];
        }
    }

    SimNode * ExprSwizzle::trySimulate ( uint32_t extraOffset, Type r2vType ) const {
        if ( !value->type->ref ) {
            return nullptr;
        }
        uint32_t offset = fields[0] * sizeof(float);
        if ( auto chain = value->trySimulate(extraOffset + offset, r2vType) ) {
            return chain;
        }
        auto simV = value->simulate();
        if ( r2vType!=Type::none ) {
            return __context__->code->makeValueNode<SimNode_FieldDerefR2V>(r2vType,at,simV,offset + extraOffset);
        } else {
            return __context__->code->makeNode<SimNode_FieldDeref>(at,simV,offset + extraOffset);
        }
    }

    SimNode * ExprSwizzle::simulate () const {
        if ( !type->ref ) {
            bool seq = TypeDecl::isSequencialMask(fields);
            if (seq && value->type->ref) {
                return trySimulate(0, type->baseType);
            } else {
                auto fsz = fields.size();
                uint8_t fs[4];
                fs[0] = fields[0];
                fs[1] = fsz >= 2 ? fields[1] : fields[0];
                fs[2] = fsz >= 3 ? fields[2] : fields[0];
                fs[3] = fsz >= 4 ? fields[3] : fields[0];
                auto simV = value->simulate();
                return __context__->code->makeNode<SimNode_Swizzle>(at, simV, fs);
            }
        } else {

            return trySimulate(0, r2v ? type->baseType : Type::none);
        }
    }

    SimNode * ExprField::simulate () const {
        if ( !field ) {
            if ( r2v ) {
                auto resN = annotation->simulateGetFieldR2V(name, at, value);
                if ( !resN ) {
                    __context__->thisProgram->error("integration error, simulateGetFieldR2V returned null",
                                               at, CompilationError::missing_node );
                }
                return resN;
            } else {
                auto resN = annotation->simulateGetField(name, at, value);
                if ( !resN ) {
                    __context__->thisProgram->error("integration error, simulateGetField returned null",
                                               at, CompilationError::missing_node );
                }
                return resN;
            }
        } else {
            return trySimulate(0, r2v ? type->baseType : Type::none);
        }
    }

    SimNode * ExprField::trySimulate (uint32_t extraOffset, Type r2vType ) const {
        if ( !field ) {
            return nullptr;
        }
        if (value->type->isPointer()) {
            auto simV = value->simulate();
            if ( r2vType!=Type::none ) {
                return __context__->code->makeValueNode<SimNode_PtrFieldDerefR2V>(r2vType, at, simV, field->offset + extraOffset);
            } else {
                return __context__->code->makeNode<SimNode_PtrFieldDeref>(at, simV, field->offset + extraOffset);
            }
        } else {
            if ( auto chain = value->trySimulate(extraOffset + field->offset, r2vType) ) {
                return chain;
            }
            auto simV = value->simulate();
            if ( r2vType!=Type::none ) {
                return __context__->code->makeValueNode<SimNode_FieldDerefR2V>(r2vType, at, simV, extraOffset + field->offset);
            } else {
                return __context__->code->makeNode<SimNode_FieldDeref>(at, simV, extraOffset + field->offset);
            }
        }
    }

    SimNode * ExprSafeField::simulate () const {
        if ( skipQQ ) {
            if ( annotation ) {
                auto resN = annotation->simulateSafeGetFieldPtr(name, at, value);
                if ( !resN ) {
                    __context__->thisProgram->error("integration error, simulateSafeGetFieldPtr returned null",
                                               at, CompilationError::missing_node );
                }
                return resN;
            } else {
                auto resN = __context__->code->makeNode<SimNode_SafeFieldDerefPtr>(at,value->simulate(),field->offset);
                if ( !resN ) {
                    __context__->thisProgram->error("integration error, simulateSafeFieldDerefPtr returned null",
                                               at, CompilationError::missing_node );
                }
                return resN;
            }
        } else {
            if ( annotation ) {
                auto resN = annotation->simulateSafeGetField(name, at, value);
                if ( !resN ) {
                    __context__->thisProgram->error("integration error, simulateSafeGetField returned null",
                                               at, CompilationError::missing_node );
                }
                return resN;
            } else {
                return __context__->code->makeNode<SimNode_SafeFieldDeref>(at,value->simulate(),field->offset);
            }
        }
    }

    SimNode * ExprStringBuilder::simulate () const {
        SimNode_StringBuilder * pSB = __context__->code->makeNode<SimNode_StringBuilder>(at);
        if ( int nArg = (int) elements.size() ) {
            pSB->arguments = (SimNode **) __context__->code->allocate(nArg * sizeof(SimNode *));
            pSB->types = (TypeInfo **) __context__->code->allocate(nArg * sizeof(TypeInfo *));
            pSB->nArguments = nArg;
            for ( int a=0; a!=nArg; ++a ) {
                pSB->arguments[a] = elements[a]->simulate();
                pSB->types[a] = __context__->thisHelper->makeTypeInfo(nullptr, elements[a]->type);
            }
        } else {
            pSB->arguments = nullptr;
            pSB->types = nullptr;
            pSB->nArguments = 0;
        }
        return pSB;
    }

    SimNode * ExprVar::trySimulate ( uint32_t extraOffset, Type r2vType ) const {
        if ( block ) {
        } else if ( local ) {
            if ( variable->type->ref ) {
                if ( r2vType!=Type::none ) {
                    return __context__->code->makeValueNode<SimNode_GetLocalRefR2VOff>(r2vType, at,
                                                    variable->stackTop, extraOffset);
                } else {
                    return __context__->code->makeNode<SimNode_GetLocalRefOff>(at,
                                                    variable->stackTop, extraOffset);
                }
            } else if ( variable->aliasCMRES ) {
                if ( r2vType!=Type::none ) {
                    return __context__->code->makeValueNode<SimNode_GetCMResOfsR2V>(r2vType, at,extraOffset);
                } else {
                    return __context__->code->makeNode<SimNode_GetCMResOfs>(at, extraOffset);
                }
            } else {
                if ( r2vType!=Type::none ) {
                    return __context__->code->makeValueNode<SimNode_GetLocalR2V>(r2vType, at,
                                                                            variable->stackTop + extraOffset);
                } else {
                    return __context__->code->makeNode<SimNode_GetLocal>(at, variable->stackTop + extraOffset);
                }
            }
        } else if ( argument ) {
            if ( variable->type->isRef() ) {
                if ( r2vType!=Type::none ) {
                    return __context__->code->makeValueNode<SimNode_GetArgumentR2VOff>(r2vType, at, argumentIndex, extraOffset);
                } else {
                    return __context__->code->makeNode<SimNode_GetArgumentOff>(at, argumentIndex, extraOffset);
                }
            }
        } else { // global

        }
        return nullptr;
    }

    SimNode * ExprVar::simulate () const {
        if ( block ) {
            auto blk = pBlock.lock();
            if (variable->type->isRef()) {
                if (r2v && !type->isRefType()) {
                    return __context__->code->makeValueNode<SimNode_GetBlockArgumentR2V>(type->baseType, at, argumentIndex, blk->stackTop);
                } else {
                    return __context__->code->makeNode<SimNode_GetBlockArgument>(at, argumentIndex, blk->stackTop);
                }
            } else {
                if (r2v && !type->isRefType()) {
                    return __context__->code->makeNode<SimNode_GetBlockArgument>(at, argumentIndex, blk->stackTop);
                }
                else {
                    return __context__->code->makeNode<SimNode_GetBlockArgumentRef>(at, argumentIndex, blk->stackTop);
                }
            }
        } else if ( local ) {
            if ( r2v ) {
                return trySimulate(0, type->baseType);
            } else {
                return trySimulate(0, Type::none);
            }
        } else if ( argument) {
            if (variable->type->isRef()) {
                if (r2v && !type->isRefType()) {
                    return __context__->code->makeValueNode<SimNode_GetArgumentR2V>(type->baseType, at, argumentIndex);
                } else {
                    return __context__->code->makeNode<SimNode_GetArgument>(at, argumentIndex);
                }
            } else {
                if (r2v && !type->isRefType()) {
                    return __context__->code->makeNode<SimNode_GetArgument>(at, argumentIndex);
                }
                else {
                    return __context__->code->makeNode<SimNode_GetArgumentRef>(at, argumentIndex);
                }
            }
        } else {
            assert(variable->index >= 0 && "using variable which is not used. how?");
            if ( r2v ) {
                return __context__->code->makeValueNode<SimNode_GetGlobalR2V>(type->baseType, at, variable->stackTop);
            } else {
                return __context__->code->makeNode<SimNode_GetGlobal>(at, variable->stackTop);
            }
        }
    }

    SimNode * ExprOp1::simulate () const {
        if ( func->builtIn && !func->callBased ) {
            auto pSimOp1 = static_cast<SimNode_Op1 *>(func->makeSimNode());
            pSimOp1->x = subexpr->simulate();
            return pSimOp1;
        } else {
            auto pCall = static_cast<SimNode_CallBase *>(func->makeSimNode());
            pCall->debugInfo = at;
            pCall->fnPtr = __context__->getFunction(func->index);
            pCall->arguments = (SimNode **) __context__->code->allocate(1 * sizeof(SimNode *));
            pCall->nArguments = 1;
            pCall->arguments[0] = subexpr->simulate();
            pCall->cmresEval = __context__->code->makeNode<SimNode_GetLocal>(at,stackTop);
            return pCall;
        }
    }

    SimNode * ExprOp2::simulate () const {
        if ( func->builtIn && !func->callBased ) {
            auto pSimOp2 = static_cast<SimNode_Op2 *>(func->makeSimNode());
            pSimOp2->l = left->simulate();
            pSimOp2->r = right->simulate();
            return pSimOp2;
        } else {
            auto pCall = static_cast<SimNode_CallBase *>(func->makeSimNode());
            pCall->debugInfo = at;
            pCall->fnPtr = __context__->getFunction(func->index);
            pCall->arguments = (SimNode **) __context__->code->allocate(2 * sizeof(SimNode *));
            pCall->nArguments = 2;
            pCall->arguments[0] = left->simulate();
            pCall->arguments[1] = right->simulate();
            pCall->cmresEval = __context__->code->makeNode<SimNode_GetLocal>(at,stackTop);
            return pCall;
        }
    }

    SimNode * ExprOp3::simulate () const {
        return __context__->code->makeNode<SimNode_IfThenElse>(at,
                                                    subexpr->simulate(),
                                                    left->simulate(),
                                                    right->simulate());
    }

    SimNode * ExprMove::simulate () const {
        auto retN = makeMove(at,left,right);
        if ( !retN ) {
            __context__->thisProgram->error("internal compilation error, can't generate move", at);
        }
        return retN;
    }

    SimNode * ExprCopy::simulate () const {
        if ( takeOverRightStack ) {
            auto sl = left->simulate();
            auto sr = right->simulate();
            return __context__->code->makeNode<SimNode_SetLocalRefAndEval>(at, sl, sr, stackTop);
        } else {
            auto retN = makeCopy(at, left, right);
            if ( !retN ) {
                __context__->thisProgram->error("internal compilation error, can't generate copy", at);
            }
            return retN;
        }
    }

    SimNode * ExprTryCatch::simulate () const {
        return __context__->code->makeNode<SimNode_TryCatch>(at,
                                                  try_block->simulate(),
                                                  catch_block->simulate());
    }

    SimNode * ExprReturn::simulate () const {
        SimNode * simSubE = subexpr ? subexpr->simulate() : nullptr;
        if (subexpr && subexpr->rtti_isConstant()) {
            if (subexpr->type->isSimpleType(Type::tString)) {
                auto cVal = static_pointer_cast<ExprConstString>(subexpr);
                char * str = __context__->code->allocateString(cVal->text);
                return __context__->code->makeNode<SimNode_ReturnConst>(at, cast<char *>::from(str));
            } else {
                auto cVal = static_pointer_cast<ExprConst>(subexpr);
                return __context__->code->makeNode<SimNode_ReturnConst>(at, cVal->value);
            }
        }
        if ( returnReference ) {
            if ( returnInBlock ) {
                return __context__->code->makeNode<SimNode_ReturnReferenceFromBlock>(at, simSubE);
            } else {
                return __context__->code->makeNode<SimNode_ReturnReference>(at, simSubE);
            }
        } else if ( returnInBlock ) {
            if ( returnCallCMRES ) {
                SimNode_CallBase * simRet = (SimNode_CallBase *) simSubE;
                simRet->cmresEval = __context__->code->makeNode<SimNode_GetBlockCMResOfs>(at,0,stackTop);
                return __context__->code->makeNode<SimNode_Return>(at, simSubE);
            } else if ( takeOverRightStack ) {
                return __context__->code->makeNode<SimNode_ReturnRefAndEvalFromBlock>(at,
                            simSubE, refStackTop, stackTop);
            } else if ( block->copyOnReturn  ) {
                return __context__->code->makeNode<SimNode_ReturnAndCopyFromBlock>(at,
                            simSubE, subexpr->type->getSizeOf(), stackTop);
            } else if ( block->moveOnReturn ) {
                return __context__->code->makeNode<SimNode_ReturnAndMoveFromBlock>(at,
                    simSubE, subexpr->type->getSizeOf(), stackTop);
            }
        } else if ( subexpr ) {
            if ( returnCallCMRES ) {
                SimNode_CallBase * simRet = (SimNode_CallBase *) simSubE;
                simRet->cmresEval = __context__->code->makeNode<SimNode_GetCMResOfs>(at,0);
                return __context__->code->makeNode<SimNode_Return>(at, simSubE);
            } else if ( returnCMRES ) {
                return __context__->code->makeNode<SimNode_Return>(at, simSubE);
            } else if ( takeOverRightStack ) {
                return __context__->code->makeNode<SimNode_ReturnRefAndEval>(at, simSubE, refStackTop);
            } else if ( func->copyOnReturn ) {
                return __context__->code->makeNode<SimNode_ReturnAndCopy>(at, simSubE, subexpr->type->getSizeOf());
            } else if ( func->moveOnReturn ) {
                return __context__->code->makeNode<SimNode_ReturnAndMove>(at, simSubE, subexpr->type->getSizeOf());
            }
        }
        return __context__->code->makeNode<SimNode_Return>(at, simSubE);
    }

    SimNode * ExprBreak::simulate () const {
        return __context__->code->makeNode<SimNode_Break>(at);
    }

    SimNode * ExprIfThenElse::simulate () const {
        ExpressionPtr zeroCond;
        bool condIfZero = false;
        if ( matchEquNequZero(cond, zeroCond, condIfZero) ) {
            if ( condIfZero ) {
                if ( if_false ) {
                    return __context__->code->makeNumericValueNode<SimNode_IfZeroThenElse>(zeroCond->type->baseType,
                                    at, zeroCond->simulate(), if_true->simulate(),
                                            if_false->simulate());

                } else {
                    return __context__->code->makeNumericValueNode<SimNode_IfZeroThen>(zeroCond->type->baseType,
                                    at, zeroCond->simulate(), if_true->simulate());
                }
            } else {
                if ( if_false ) {
                    return __context__->code->makeNumericValueNode<SimNode_IfNotZeroThenElse>(zeroCond->type->baseType,
                                    at, zeroCond->simulate(), if_true->simulate(),
                                            if_false->simulate());

                } else {
                    return __context__->code->makeNumericValueNode<SimNode_IfNotZeroThen>(zeroCond->type->baseType,
                                    at, zeroCond->simulate(), if_true->simulate());
                }
            }
        } else {
            // good old if
            if ( if_false ) {
                return __context__->code->makeNode<SimNode_IfThenElse>(at, cond->simulate(),
                                    if_true->simulate(), if_false->simulate());
            } else {
                return __context__->code->makeNode<SimNode_IfThen>(at, cond->simulate(),
                                    if_true->simulate());
            }
        }
    }

    SimNode * ExprWith::simulate () const {
        return body->simulate();
    }
    
    void ExprWhile::simulateFinal ( const ExpressionPtr & bod, SimNode_Block * blk ) {
        if ( bod->rtti_isBlock() ) {
            auto pBlock = static_pointer_cast<ExprBlock>(bod);
            pBlock->simulateBlock(blk);
            pBlock->simulateFinal(blk);
        } else {
            __context__->thisProgram->error("internal error, expecting block", bod->at);
        }
    }

    SimNode * ExprWhile::simulate () const {
        auto node = __context__->code->makeNode<SimNode_While>(at, cond->simulate());
        simulateFinal(body, node);
        return node;
    }

    SimNode * ExprFor::simulate () const {
        // determine iteration types
        bool nativeIterators = false;
        bool fixedArrays = false;
        bool dynamicArrays = false;
        bool rangeBase = false;
        uint32_t fixedSize = UINT16_MAX;
        for ( auto & src : sources ) {
            if ( !src->type ) continue;
            if ( src->type->isArray() ) {
                fixedSize = min(fixedSize, src->type->dim.back());
                fixedArrays = true;
            } else if ( src->type->isGoodArrayType() ) {
                dynamicArrays = true;
            } else if ( src->type->isGoodIteratorType() ) {
                nativeIterators = true;
            } else if ( src->type->isHandle() ) {
                nativeIterators = true;
            } else if ( src->type->isRange() ) {
                rangeBase = true;
            }
        }
        // create loops based on
        int  total = int(sources.size());
        int  sourceTypes = int(dynamicArrays) + int(fixedArrays) + int(rangeBase);
        bool hybridRange = rangeBase && (total>1);
        if ( (sourceTypes>1) || hybridRange || nativeIterators ) {
            SimNode_ForWithIteratorBase * result = (SimNode_ForWithIteratorBase *)
                __context__->code->makeNodeUnroll<SimNode_ForWithIterator>(total, at);
            for ( int t=0; t!=total; ++t ) {
                if ( sources[t]->type->isGoodIteratorType() ) {
                    result->source_iterators[t] = sources[t]->simulate();
                } else if ( sources[t]->type->isGoodArrayType() ) {
                    result->source_iterators[t] = __context__->code->makeNode<SimNode_GoodArrayIterator>(
                        sources[t]->at,
                        sources[t]->simulate(),
                        sources[t]->type->firstType->getStride());
                } else if ( sources[t]->type->isRange() ) {
                    result->source_iterators[t] = __context__->code->makeNode<SimNode_RangeIterator>(
                        sources[t]->at,
                        sources[t]->simulate());
                } else if ( sources[t]->type->isHandle() ) {
                    result->source_iterators[t] = sources[t]->type->annotation->simulateGetIterator(
                         sources[t]->at,
                         sources[t]->simulate()
                    );
                    if ( !result ) {
                        __context__->thisProgram->error("integration error, simulateGetIterator returned null",
                                                   at, CompilationError::missing_node );
                        return nullptr;
                    }
                } else if ( sources[t]->type->dim.size() ) {
                    result->source_iterators[t] = __context__->code->makeNode<SimNode_FixedArrayIterator>(
                        sources[t]->at,
                        sources[t]->simulate(),
                        sources[t]->type->dim.back(),
                        sources[t]->type->getStride());
                } else {
                    DAS_ASSERTF(0, "we should not be here. we are doing iterator for on an unsupported type.");
                    __context__->thisProgram->error("internal compilation error, generating for-with-iterator", at);
                    return nullptr;
                }
                result->stackTop[t] = iteratorVariables[t]->stackTop;
            }
            ExprWhile::simulateFinal(subexpr, result);
            return result;
        } else {
            auto flagsE = subexpr->getEvalFlags();
            bool NF = flagsE == 0;
            SimNode_ForBase * result;
            assert(subexpr->rtti_isBlock() && "there would be internal error otherwise");
            auto subB = static_pointer_cast<ExprBlock>(subexpr);
            bool loop1 = (subB->list.size() == 1);
            if ( dynamicArrays ) {
                if (loop1) {
                    result = (SimNode_ForBase *) __context__->code->makeNodeUnroll<SimNode_ForGoodArray1>(total, at);
                } else {
                    result = (SimNode_ForBase *) __context__->code->makeNodeUnroll<SimNode_ForGoodArray>(total, at);
                }
            } else if ( fixedArrays ) {
                if (loop1) {
                    result = (SimNode_ForBase *)__context__->code->makeNodeUnroll<SimNode_ForFixedArray1>(total, at);
                } else {
                    result = (SimNode_ForBase *)__context__->code->makeNodeUnroll<SimNode_ForFixedArray>(total, at);
                }
            } else if ( rangeBase ) {
                assert(total==1 && "simple range on 1 loop only");
                if ( NF ) {
                    if (loop1) {
                        result = __context__->code->makeNode<SimNode_ForRangeNF1>(at);
                    } else {
                        result = __context__->code->makeNode<SimNode_ForRangeNF>(at);
                    }
                } else {
                    if (loop1) {
                        result = __context__->code->makeNode<SimNode_ForRange1>(at);
                    } else {
                        result = __context__->code->makeNode<SimNode_ForRange>(at);
                    }
                }
            } else {
                DAS_ASSERTF(0, "we should not be here yet. logic above assumes optimized for path of some kind.");
                __context__->thisProgram->error("internal compilation error, generating for", at);
                return nullptr;
            }
            for ( int t=0; t!=total; ++t ) {
                result->sources[t] = sources[t]->simulate();
                if ( sources[t]->type->isGoodArrayType() ) {
                    result->strides[t] = sources[t]->type->firstType->getStride();
                } else {
                    result->strides[t] = sources[t]->type->getStride();
                }
                result->stackTop[t] = iteratorVariables[t]->stackTop;
            }
            result->size = fixedSize;
            ExprWhile::simulateFinal(subexpr, result);
            return result;
        }
    }

    vector<SimNode *> ExprLet::simulateInit(const ExprLet * pLet) {
        vector<SimNode *> simlist;
        simlist.reserve(pLet->variables.size());
        for (auto & var : pLet->variables) {
            SimNode * init;
            if (var->init) {
                init = ExprLet::simulateInit(var, true);
            } else if (var->aliasCMRES ) {
                init = __context__->code->makeNode<SimNode_InitLocalCMRes>(pLet->at, 0, var->type->getSizeOf());
            } else {
                init = __context__->code->makeNode<SimNode_InitLocal>(pLet->at, var->stackTop, var->type->getSizeOf());
            }
            if (init)
                simlist.push_back(init);
        }
        return simlist;
    }

    SimNode * ExprLet::simulateInit(const VariablePtr & var, bool local) {
        SimNode * get;
        if ( local ) {
            if ( var->init && var->init->rtti_isMakeLocal() ) {
                return var->init->simulate();
            } else {
                get = __context__->code->makeNode<SimNode_GetLocal>(var->init->at, var->stackTop);
            }
        } else {
            get = __context__->code->makeNode<SimNode_GetGlobal>(var->init->at, var->index);
        }
        if ( var->type->ref ) {
            return __context__->code->makeNode<SimNode_CopyReference>(var->init->at, get,
                                                                 var->init->simulate());
        } else if ( var->type->canCopy() ) {
            auto varExpr = make_shared<ExprVar>(var->at, var->name);
            varExpr->variable = var;
            varExpr->local = local;
            varExpr->type = make_shared<TypeDecl>(*var->type);
            auto retN = makeCopy(var->init->at, varExpr, var->init);
            if ( !retN ) {
                __context__->thisProgram->error("internal compilation error, can't generate copy", var->at);
            }
            return retN;
        } else if ( var->type->canMove() ) {
            auto varExpr = make_shared<ExprVar>(var->at, var->name);
            varExpr->variable = var;
            varExpr->local = local;
            varExpr->type = make_shared<TypeDecl>(*var->type);
            auto retN = makeMove(var->init->at, varExpr, var->init);
            if ( !retN ) {
                __context__->thisProgram->error("internal compilation error, can't generate move", var->at);
            }
            return retN;
        } else {
            __context__->thisProgram->error("internal compilation error, initializing variable which can't be copied or moved", var->at);
            return nullptr;
        }
    }

    SimNode * ExprLet::simulate () const {
        auto let = __context__->code->makeNode<SimNode_Let>(at);
        let->total = (uint32_t) variables.size();
        let->list = (SimNode **) __context__->code->allocate(let->total * sizeof(SimNode*));
        auto simList = ExprLet::simulateInit(this);
        copy(simList.data(), simList.data() + simList.size(), let->list);
        let->subexpr = subexpr ? subexpr->simulate() : nullptr;
        return let;
    }

    SimNode_CallBase * ExprCall::simulateCall (const FunctionPtr & func,
                                               const ExprLooksLikeCall * expr,
                                               SimNode_CallBase * pCall) {
        bool needTypeInfo = false;
        for ( auto & arg : func->arguments ) {
            if ( arg->type->baseType==Type::anyArgument )
                needTypeInfo = true;
        }
        pCall->debugInfo = expr->at;
        DAS_ASSERTF((func->builtIn || func->index>=0), "calling function which is not used. how?");
        pCall->fnPtr = __context__->getFunction(func->index);
        if ( int nArg = (int) expr->arguments.size() ) {
            pCall->arguments = (SimNode **) __context__->code->allocate(nArg * sizeof(SimNode *));
            if ( needTypeInfo ) {
                pCall->types = (TypeInfo **) __context__->code->allocate(nArg * sizeof(TypeInfo *));
            } else {
                pCall->types = nullptr;
            }
            pCall->nArguments = nArg;
            for ( int a=0; a!=nArg; ++a ) {
                pCall->arguments[a] = expr->arguments[a]->simulate();
                if ( pCall->types ) {
                    if ( func->arguments[a]->type->baseType==Type::anyArgument ) {
                        pCall->types[a] = __context__->thisHelper->makeTypeInfo(nullptr, expr->arguments[a]->type);
                    } else {
                        pCall->types[a] = nullptr;
                    }
                }
            }
        } else {
            pCall->arguments = nullptr;
            pCall->nArguments = 0;
        }
        return pCall;

    }

    SimNode * ExprCall::simulate () const {
        auto pCall = static_cast<SimNode_CallBase *>(func->makeSimNode());
        simulateCall(func->shared_from_this(), this, pCall);
        if ( !doesNotNeedSp ) {
            pCall->cmresEval = __context__->code->makeNode<SimNode_GetLocal>(at,stackTop);
        }
        return pCall;
    }

    bool Program::simulate ( TextWriter & logs ) {
        __context__->thisProgram = this;
        if ( auto optHeap = options.find("heap",Type::tInt) ) {
            __context__->heap.setInitialSize( uint32_t(optHeap->iValue) );
        }
        DebugInfoHelper helper(__context__->debugInfo);
        __context__->thisHelper = &helper;
        __context__->globalVariables = (GlobalVariable *) __context__->code->allocate( totalVariables*sizeof(GlobalVariable) );
        __context__->globalsSize = 0;
        for (auto & pm : library.modules ) {
            for (auto & it : pm->globals) {
                auto pvar = it.second;
                if (!pvar->used)
                    continue;
                DAS_ASSERTF(pvar->index >= 0, "we are simulating variable, which is not used");
                auto & gvar = __context__->globalVariables[pvar->index];
                gvar.name = __context__->code->allocateName(pvar->name);
                gvar.size = pvar->type->getSizeOf();
                gvar.debugInfo = helper.makeVariableDebugInfo(*it.second);
                gvar.offset = pvar->stackTop = __context__->globalsSize;
                __context__->globalsSize = (__context__->globalsSize + gvar.size + 0xf) & ~0xf;
            }
        }
        __context__->globals = (char *) das_aligned_alloc16(__context__->globalsSize);
        __context__->totalVariables = totalVariables;
        __context__->functions = (SimFunction *) __context__->code->allocate( totalFunctions*sizeof(SimFunction) );
        __context__->totalFunctions = totalFunctions;
        for (auto & pm : library.modules) {
            for (auto & it : pm->functions) {
                auto pfun = it.second;
                if (pfun->index < 0 || !pfun->used)
                    continue;
                auto & gfun = __context__->functions[pfun->index];
                gfun.name = __context__->code->allocateName(pfun->name);
                gfun.code = pfun->simulate();
                gfun.stackSize = pfun->totalStackSize;
                gfun.debugInfo = helper.makeFunctionDebugInfo(*pfun);
            }
        }
        for (auto & pm : library.modules ) {
            for (auto & it : pm->globals) {
                auto pvar = it.second;
                if (!pvar->used)
                    continue;
                auto & gvar = __context__->globalVariables[pvar->index];
                gvar.init = pvar->init ? ExprLet::simulateInit(pvar, false) : nullptr;
            }
        }
        __context__->globalInitStackSize = globalInitStackSize;
        __context__->simEnd();
        __context__->restart();
        __context__->runInitScript();
        __context__->restart();
        if (options.getOption("logMem")) {
            logs << "code  " << __context__->code->bytesAllocated() << "\n";
            logs << "debug " << __context__->debugInfo->bytesAllocated() << "\n";
            logs << "heap  " << __context__->heap.bytesAllocated() << "\n";
        }
        // log all functions
        if ( options.getOption("logNodes",false) ) {
            for ( int i=0; i!=__context__->totalFunctions; ++i ) {
                SimFunction * fn = __context__->getFunction(i);
                logs << "// " << fn->name << "\n";
                printSimNode(logs, fn->code);
                logs << "\n\n";
            }
        }
        return errors.size() == 0;
    }
}
