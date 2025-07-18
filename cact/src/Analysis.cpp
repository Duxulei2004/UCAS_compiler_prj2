#include "../include/Analysis.h"  // 引入分析模块的头文件
#include "../include/SymbolTable.h"  // 引入符号表模块的头文件
#include "HelloParser.h"  // 引入语法解析器的头文件
#include <llvm/IR/GlobalVariable.h>  // 引入LLVM的全局变量定义头文件
#include <llvm/IR/Function.h>  // 引入LLVM的函数定义头文件
#include <llvm/IR/BasicBlock.h>  // 引入LLVM的基本块定义头文件
#include <llvm/IR/Constant.h>  // 引入LLVM的常量定义头文件
#include <vector>  // 引入C++标准库的vector容器
#include <any>  // 引入C++标准库的any类型
#include <stdio.h>  // 引入C标准库的stdio头文件
#include <llvm/IR/Module.h>  // 引入LLVM的模块头文件
#include <llvm/IR/Type.h>

using namespace llvm;  // 使用LLVM命名空间

// 访问CompUnitContext节点（这是编译单元，表示程序的顶级结构）
Type* Analysis::getReturnType(HelloParser::FuncDefContext* funcDef) {
    // 获取函数的返回类型，这里根据你的语法规则返回相应类型
    if (funcDef->funcType()->INT_KW()) {
        return Type::getInt32Ty(context);  // 对应int类型
    } else if (funcDef->funcType()->FLOAT_KW()) {
        return Type::getFloatTy(context);  // 对应float类型
    } else if (funcDef->funcType()->VOID_KW()) {
        return Type::getVoidTy(context);  // 对应void类型
    }else if (funcDef->funcType()->CHAR_KW()) {
        return Type::getInt8Ty(context);  // 对应void类型
    } 
     else {
        // 处理其他类型或错误情况
        return nullptr;  // 或者可以抛出错误
    }
}
std::any Analysis::visitCompUnit(HelloParser::CompUnitContext *ctx) {

    // 先初始化CACT内建函数
    initBuiltins();

    symbolTable.enterScope();
    // 处理所有声明
    for (auto decl : ctx->decl()) {  // 遍历声明列表
       if(decl->constdecl()){
            visitConstDecl(decl->constdecl());
       }
        else if (decl->vardecl()) {  // 如果是变量声明
            visitVarDecl(decl->vardecl());
        }
    }

    // 处理所有函数定义
    for (auto funcDef : ctx->funcDef()) {  // 遍历函数定义
        visitFuncDef(funcDef);  // 处理函数定义
    }
    // 退出作用域
    symbolTable.print();  
    symbolTable.exitScope();
    // if (functionTable.find("main") == functionTable.end()) {
    //     std::cerr << "[Error]: main 函数未定义。" << std::endl;
    //     exit(1);
    // }

    std::string ir;
    raw_string_ostream os(ir);  // 创建输出流
    module.print(os, nullptr);  // 打印模块的IR代码
    return ir;  // 返回IR代码
}



Type* Analysis::getTypeFromBType(HelloParser::BTypeContext* ctx) {
    if (ctx->INT_KW()) return Type::getInt32Ty(context);  
    if (ctx->FLOAT_KW()) return Type::getFloatTy(context); 
    if (ctx->CHAR_KW()) return Type::getInt8Ty(context);  
    throw std::runtime_error("Unknown type"); 
}

llvm::Constant* Analysis::convertFlatToMultiDim(
    const std::vector<llvm::Constant*>& flatConstants,
    const std::vector<int>& dims,
    llvm::Type* elemType
) {
    // 最底层，一维数组
    if (dims.size() == 1) {
        auto *arrTy = llvm::ArrayType::get(elemType, dims[0]);
        return llvm::ConstantArray::get(arrTy, flatConstants);
    }

    // 计算每个子数组应有的元素个数
    int chunkSize = 1;
    for (size_t i = 1; i < dims.size(); ++i)
        chunkSize *= dims[i];

    // 先生成所有子 ConstantArray
    std::vector<llvm::Constant*> outer;
    for (size_t i = 0; i < dims[0]; ++i) {
        auto begin = flatConstants.begin() + i * chunkSize;
        auto end   = begin + chunkSize;
        std::vector<llvm::Constant*> sub(begin, end);

        // 递归构造子数组（dims[1..]）
        std::vector<int> subDims(dims.begin() + 1, dims.end());
        llvm::Constant* child = convertFlatToMultiDim(sub, subDims, elemType);
        outer.push_back(child);
    }

    // **关键**：用 child->getType()（它就是 [2 x i32]）来创建外层数组类型
    llvm::ArrayType* childArrTy = llvm::cast<llvm::ArrayType>(outer[0]->getType());
    llvm::ArrayType* thisArrTy  = llvm::ArrayType::get(childArrTy, dims[0]);
    return llvm::ConstantArray::get(thisArrTy, outer);
}

void Analysis::flattenConstInitValLinear(
        HelloParser::ConstInitValContext* ctx,
        llvm::Type* elemType,
        const std::vector<int>& dims,
        int dimIndex,
        std::vector<llvm::Constant*>& result
) {
        if (!ctx) return;
    
        // 叶子节点（constExp）
        if (ctx->constExp()) {
            auto valAny = visitConstExp(ctx->constExp());
            llvm::Value* val = std::any_cast<llvm::Value*>(valAny);
            if (auto* constVal = llvm::dyn_cast<llvm::Constant>(val)) {
                result.push_back(constVal);
            } else {
                std::cerr << "初始化中包含非常量" << std::endl;
                exit(1);
            }
            return;
        }
    
        // 当前维度下应填多少个元素
        int expected = dims[dimIndex];
        int count = ctx->constInitVal().size();
    
        for (int i = 0; i < count; ++i) {
            flattenConstInitValLinear(ctx->constInitVal(i), elemType, dims, dimIndex + 1, result);
        }
    
        // 补零
        for (int i = count; i < expected; ++i) {
            // 计算这一层需要补多少个叶子（乘以子维度所有大小）
            int subElements = 1;
            for (int j = dimIndex + 1; j < dims.size(); ++j) subElements *= dims[j];
    
            for (int k = 0; k < subElements; ++k) {
                result.push_back(llvm::Constant::getNullValue(elemType));
            }
        }
    }
    
void Analysis::flattenConstInitValArrayLinear(
        HelloParser::ConstInitValArrayContext* ctx,
        llvm::Type* elemType,
        const std::vector<int>& dims,
        int dimIndex,
        std::vector<llvm::Constant*>& result
) {
    if (!ctx) return;
    
    // 当前维度下应填多少个元素
    int expected = dims[dimIndex];
    int count = ctx->constInitVal().size();
    int i=0;
    // 处理所有子初始化项
    for(i;i<count;i++){
        flattenConstInitValLinear(ctx->constInitVal(i), elemType, dims, dimIndex + 1, result);
    }

    // 计算需要补零的数量
    if (count < expected) {
        int subElements = 1;
        // 计算子维度总元素数
        for (int j = dimIndex + 1; j < dims.size(); ++j) {
            subElements *= dims[j];
        }
        int zerosNeeded = (expected - count) * subElements;
        
        // 填充零值
        llvm::Constant* zero = llvm::Constant::getNullValue(elemType);
        for (int i = 0; i < zerosNeeded; ++i) {
            result.push_back(zero);
        }
    }
}


// -----------------------------------------------------
// 递归遍历初始化列表、对每个元素做以下两件事：
//   1. 计算当前元素的 多维索引 （vector<int> indices）
//   2. 根据 indices 用 GEP 找到 elemPtr，然后为其生成一个 Store
// 如果叶子节点是 c[2][1] 这种运算，就直接生成 GEP+Load 得到 Value*，再做 Store。
// 如果叶子节点只是常量（1,2,3…），同样统一处理：给 Store 一个 Constant*。
// 遍历完这一层后，若 count < expected，就对剩余位置“补零”。
// dims = {dim0, dim1, ..., dimN-1}
// dimIndex 表示当前正在处理 dims[dimIndex] 这一维。
// flatIndex 用作中间算多维坐标。
// -----------------------------------------------------
void Analysis::initConstInitValWithValues(
    HelloParser::ConstInitValContext* ctx,
    AllocaInst* allocaPtr,                // 目标数组在栈上的地址
    llvm::Type* elemType,                 // 数组元素类型 (e.g. i32)
    const std::vector<int>& dims,         // 各维度的长度
    int dimIndex,                         // 当前递归正在处理第 dimIndex 维
    std::vector<int>& indicesSoFar        // 用于记录当前定位的多维索引
) {
    // ctx 可能为 nullptr（比如没有写任何初始化）——直接 return
    if (!ctx) return;

    // 如果是叶子节点（constExp），就马上生成一个 Store
    if (ctx->constExp()) {
        // --------------- STEP1 生成这个初始化值的 Value* ---------------
        auto valAny = visitConstExp(ctx->constExp());
        llvm::Value* val = std::any_cast<llvm::Value*>(valAny);

        // --------------- STEP2 计算当前 indicesSoFar 数组元素地址 ---------------
        // 构造 GEP 索引：最前面先 push 一个 0，然后把 indicesSoFar 中所有维度依次 push
        std::vector<llvm::Value*> gepIdx;
        gepIdx.push_back(builder.getInt32(0));
        for (int idx : indicesSoFar) {
            gepIdx.push_back(builder.getInt32(idx));
        }
        Value* elemPtr = builder.CreateGEP(
            allocaPtr->getType()->getPointerElementType(),
            allocaPtr,
            gepIdx
        );

        // --------------- STEP3 生成 Store，把刚才的 val 存到 elemPtr 里 ---------------
        builder.CreateStore(val, elemPtr);
        return;
    }

    // 如果不是叶子节点，说明 ctx->constInitVal() 里会有若干个子项，需要遍历。
    int expected = dims[dimIndex];                         // 这一维需要“项数”
    int count = ctx->constInitVal().size();                // 这行实际给了多少项

    // 遍历已写出的项
    for (int i = 0; i < count; ++i) {
        // “定位”到第 i 项时，需要把 indicesSoFar.push_back(i)，
        indicesSoFar.push_back(i);
        // 递归处理下一维
        initConstInitValWithValues(ctx->constInitVal(i), allocaPtr, elemType, dims, dimIndex + 1, indicesSoFar);
        // 回退，为下一次循环复原状态
        indicesSoFar.pop_back();
    }

    // “补零”阶段：如果实际写了 count 项，但 expected 是这层维度的总数，
    // 那么剩下的 (expected - count) 项，都要全部展开到下一维“全零”。
    for (int i = count; i < expected; ++i) {
        // 在当前层补第 i 项：indicesSoFar.push_back(i)
        indicesSoFar.push_back(i);
        // 需要把下一层所有子元素都置零：
        // 计算子维度总元素数，比如 dims=[4,2]，dimIndex=0，那么子维度乘积=2，
        // 就要连同“所有子维度”一起补 2 次零；如果是 3 维，就补 dims[1]*dims[2] 次……
        int subElements = 1;
        for (int j = dimIndex + 1; j < (int)dims.size(); ++j) {
            subElements *= dims[j];
        }

        // 这 subElements 表示：在定位到 indicesSoFar（只给了前 dimIndex+1 维）之后，
        // 需要补的“最底层叶子节点”个数。Uniformly push zeros.
        // 举例：dims=[4,2], dimIndex=0, indicesSoFar=[i]，则 subElements = dims[1] = 2。
        // 我们需要把 a[i][0] 和 a[i][1] 都补零。

        // 下面做一个“临时 copy”indicesSoFar，把后面那 subElements 次每个“叶子”补零：
        for (int k = 0; k < subElements; ++k) {
            // 这里我们算出“叶子索引”的多维坐标：indicesSoFar + “最后一维” 
            // 例如 dims=[4,2], dimIndex=0, i=2 => indicesSoFar=[2]，  
            //   subElements=2 => k=0 leaves indices=[2,0], k=1 leaves [2,1]
            int lastDimSize = dims[dimIndex + 1];
            int leafIdx = k % lastDimSize;  // 最后一维的索引
            std::vector<int> fullIdx = indicesSoFar;
            fullIdx.push_back(leafIdx);

            // GEP 得到 &a[ fullIdx[0] ][ fullIdx[1] ] … &leaf
            std::vector<llvm::Value*> gepIdx2;
            gepIdx2.push_back(builder.getInt32(0));
            for (int idx2 : fullIdx) {
                gepIdx2.push_back(builder.getInt32(idx2));
            }
            Value* elemPtr2 = builder.CreateGEP(
                allocaPtr->getType()->getPointerElementType(),
                allocaPtr,
                gepIdx2
            );

            // Store 一个零值 Constant (elemType 全类型对应的零)
            builder.CreateStore(llvm::Constant::getNullValue(elemType), elemPtr2);
        }

        // 回退 indicesSoFar，准备补下一 i
        indicesSoFar.pop_back();
    }
}


void Analysis::initConstInitValArrayWithValues(
    HelloParser::ConstInitValArrayContext* ctx,
    AllocaInst* allocaPtr,
    llvm::Type* elemType,
    const std::vector<int>& dims,
    int dimIndex,
    std::vector<int>& indicesSoFar
) {
    if (!ctx) return;

    // 这一维在语法上一共应该有 dims[dimIndex] 项
    int expected = dims[dimIndex];
    // ctx->constInitVal() 返回所有由大括号包裹的子初始化项
    int count = ctx->constInitVal().size();

    // ── 1) 先处理所有用户显式写出的子初始化项 ──
    for (int i = 0; i < count; ++i) {
        // 将当前这一维度的索引 i 放进 indicesSoFar
        indicesSoFar.push_back(i);

        // 取出第 i 个子项（类型是 ConstInitValContext*）
        HelloParser::ConstInitValContext* subCtx = ctx->constInitVal(i);

        // 不再在此处写 if (subCtx->constExp()) ... 而是：
        // 递归调用你已经准备好的函数，让它负责“遇常量就 store 常量，遇 c[2][1] 就生成 GEP+Load 再 store”
        initConstInitValWithValues(
            subCtx,
            allocaPtr,
            elemType,
            dims,
            dimIndex + 1,
            indicesSoFar
        );

        // 恢复 indicesSoFar，准备下一个 i
        indicesSoFar.pop_back();
    }

    // ── 2) 补零逻辑：如果用户只写了 count 项，但应该有 expected 项，剩下的都置零 ──
    if (count < expected) {
        // 先计算“这一层每补 1 项，需要补多少个最底层叶子节点”
        int subElements = 1;
        for (int j = dimIndex + 1; j < (int)dims.size(); ++j) {
            subElements *= dims[j];
        }

        // 对于每个 i 从 count 到 expected-1，都要补 subElements 个零
        for (int i = count; i < expected; ++i) {
            // 把当前维度的索引 i push 进 indicesSoFar
            indicesSoFar.push_back(i);

            // 补 subElements 个“最底层元素”零
            // 举例：dims = {4,2}, dimIndex = 0 → subElements = 2
            // 那么当 i=1 时，就要补 a[1][0] = 0 和 a[1][1] = 0
            for (int k = 0; k < subElements; ++k) {
                // 计算最后一维的偏移 leafIdx
                int lastDimSize = dims[dimIndex + 1];
                int leafIdx = k % lastDimSize;

                // 构造完整的多维索引 fullIdx = indicesSoFar + leafIdx
                std::vector<int> fullIdx = indicesSoFar;
                fullIdx.push_back(leafIdx);

                // 用 GEP 定位到 &allocaPtr[ fullIdx[0] ][ fullIdx[1] ] … 最后一维
                std::vector<llvm::Value*> gepIdx2;
                gepIdx2.reserve(fullIdx.size() + 1);
                gepIdx2.push_back(builder.getInt32(0));
                for (int idx2 : fullIdx) {
                    gepIdx2.push_back(builder.getInt32(idx2));
                }
                Value* elemPtr2 = builder.CreateGEP(
                    allocaPtr->getType()->getPointerElementType(),
                    allocaPtr,
                    gepIdx2
                );

                // 存一个零值 Constant
                builder.CreateStore(llvm::Constant::getNullValue(elemType), elemPtr2);
            }

            // 补完一行（或一层）后，把 indicesSoFar 中最后的 i 弹出
            indicesSoFar.pop_back();
        }
    }
}


std::any Analysis::visitConstDecl(HelloParser::ConstdeclContext* ctx) {
    //std::cout <<"visitConstDecl"<<std::endl;
    Type* type = getTypeFromBType(ctx->bType());  // 获取常量类型

    for (auto def : ctx->constDef()) {  // 遍历常量定义
        std::string name = def->Ident()->getText();  // 获取常量名称
        
        // 处理数组维度
        std::vector<int> dims;
        for (size_t i = 0; i < def->LeftBracket().size(); ++i) {  // 处理数组维度
            dims.push_back(std::stoi(def->IntConst(i)->getText()));  // 将数组维度的字符串转换为整数
        }
        //std::cout << "Array dimensions: ";
        for (int dim : dims) {
            //std::cout << dim << " ";  // 打印每个维度大小
        }
        //std::cout << std::endl;  // 换行

        if (dims.empty()) {
            // 处理普通常量（非数组）

            Value* initVal = processConstInitVal(def->constInitVal(), type);
            llvm::Type* initType = initVal->getType();
            // if (initType != type) {
            //         std::cerr << "[Error]：类型不匹配 - visitConstDecl"<< std::endl;
            //         exit(1);
            // }
            
            auto scopeLevel = symbolTable.getCurrentScopeLevel();
            //std::cout << "scopeLevel:" << scopeLevel <<std::endl;
            if (scopeLevel == 1) {
                //std::cout <<"insert const in scopeLevel == 0"<<std::endl;
                // 全局作用域 -> 创建 GlobalVariable
                Constant* constVal = dyn_cast<Constant>(initVal);
                // if (!constVal) {
                //     std::cerr << "错误：全局变量必须使用 Constant 作为初值！" << std::endl;
                //     exit(1);
                // }
        
                GlobalVariable* gv = new GlobalVariable(
                    module,
                    type,
                    true,
                    GlobalValue::ExternalLinkage,
                    constVal,
                    name
                );
        
                symbolTable.insert(name, type, gv,true,false);
            } else {
                // 局部作用域 -> 创建 AllocaInst
                AllocaInst* alloca = builder.CreateAlloca(type, nullptr, name);
                builder.CreateStore(initVal, alloca);  // 存初始值
                symbolTable.insert(name, type, alloca,true,false);
            }
        
            symbolTable.print();
        }
        else {
            // 处理多维数组常量

            llvm::Type* arrayType = type;
            for (int i = dims.size() - 1; i >= 0; --i) {
                arrayType = llvm::ArrayType::get(arrayType, dims[i]);
            }

            bool isListInit = def->constInitVal()->LeftBrace() != nullptr;

            // if (!isListInit && dims.size() > 0) {
            //     std::cerr << "[Error] 数组变量不能用单个常量初始化: " << name << std::endl;
            //     exit(1);
            // }

            auto scopeLevel = symbolTable.getCurrentScopeLevel();
            if(scopeLevel == 1){
                Constant* initVal = nullptr;
                auto initVal_global = def->constInitVal();
                if (!initVal_global->constInitVal().empty()) {

                    std::vector<llvm::Constant*> flatConstants;

                    //flattenConstInitValLinear(initVal_global, type, flatConstants);
                    flattenConstInitValLinear(initVal_global, type, dims, 0, flatConstants);

                    // 计算总元素个数（用于 convert）
                    int totalElements = 1;
                    for (int dim : dims) totalElements *= dim;
            
                    // 如果 flatConstants 长度不足，补零
                    while (flatConstants.size() < totalElements) {
                        flatConstants.push_back(Constant::getNullValue(type));
                    }
            
                    initVal = convertFlatToMultiDim(flatConstants, dims, type);
                } else {
                    // 未初始化，填零
                    initVal = ConstantAggregateZero::get(arrayType);
                }
            
                GlobalVariable* gv = new GlobalVariable(
                    module,
                    arrayType,
                    true,  // 是否 const，看你语义需求
                    GlobalValue::ExternalLinkage,
                    initVal,
                    name
                );
            
                symbolTable.insert(name, arrayType, gv,true,false);
            
            }else{
                // 将数组常量插入符号表，暂时不赋初值（nullptr）
                AllocaInst* alloca = builder.CreateAlloca(arrayType, nullptr, name);
                symbolTable.insert(name, arrayType, alloca,true,false);

                auto initVal_not_global = def->constInitVal();
                // std::vector<llvm::Constant*> flatConstants;
                // flattenConstInitValLinear(initVal_not_global, type, dims, 0, flatConstants);
                std::cout<<"going to init array"<<std::endl;
                std::vector<int> indicesSoFar;
                initConstInitValWithValues(initVal_not_global,alloca,type,dims,0,indicesSoFar);

            }
            symbolTable.print(); 
        }
    }
    return nullptr;
}





// 处理变量声明
std::any Analysis::visitVarDecl(HelloParser::VardeclContext* ctx) {
    std::cout <<"visiting Vardecl"<< std::endl;
    Type* type = getTypeFromBType(ctx->bType());  // 获取变量类型
    // if (type == nullptr) {
    //     std::cerr << "Error: type is nullptr!" << std::endl;
    //     exit(1);
    // }
    
// 处理普通变量定义
    for (auto def : ctx->varDef()) {  // 遍历变量定义
        
        std::string name = def->Ident()->getText();
        // 检查重定义
        if (symbolTable.lookupInCurrentScope(name)) {
            std::cerr << "[Error] Redefinition of variable: " << name << std::endl;
            exit(1);
        }

        std::cout << "visiting Vardecl - 普通变量 " << name << std::endl;
        auto scopeLevel = symbolTable.getCurrentScopeLevel();  // 获取当前作用域层级
        if (scopeLevel == 1) {
            // 全局作用域 -> 创建 GlobalVariable
            Value* initVal = nullptr;
            if (def->constInitVal()) {
                // 有显式初始化值
                initVal = processConstInitVal(def->constInitVal(), type);
                llvm::Type* initType = initVal->getType();
                Constant* constVal = dyn_cast<Constant>(initVal);
                GlobalVariable* gv = new GlobalVariable(
                    module,
                    type,
                    false,  // isConstant（变量是非 const 的）
                    GlobalValue::ExternalLinkage,  // 外部链接
                    constVal,
                    name
                );
                symbolTable.insert(name, type, gv,false,false);
            } else {
                // 全局变量未初始化 -> 初始化为零
                GlobalVariable* gv = new GlobalVariable(
                    module,
                    type,
                    false,
                    GlobalValue::ExternalLinkage,
                    Constant::getNullValue(type),
                    name
                );
                symbolTable.insert(name, type, gv,false,false);
            }
        } else {
            // 局部作用域 -> 创建 AllocaInst
            AllocaInst* alloca = builder.CreateAlloca(type, nullptr, name);

            symbolTable.insert(name, type, alloca,false,false);
    
            // 处理初始化值
            if (def->constInitVal()) {
                // 有显式初始化值
                Value* initVal = processConstInitVal(def->constInitVal(), type);
                llvm::Type* initType = initVal->getType();
                builder.CreateStore(initVal, alloca);
            } else{
                // 局部变量无显式初始化值 -> 初始化为零
                Value* zeroVal = llvm::Constant::getNullValue(type);
                builder.CreateStore(zeroVal, alloca);
            }
        }
    
        symbolTable.print();
    }

// 处理数组变量定义
    for (auto def : ctx->varDefArray()) {
        std::string name = def->Ident()->getText();
        
        auto scopeLevel = symbolTable.getCurrentScopeLevel();
        if (symbolTable.lookupInCurrentScope(name)) {
            std::cerr << "[Error] Redefinition of variable: " << name << std::endl;
            exit(1);
        }
        std::vector<int> dims;

        // 获取数组维度
        for (size_t i = 0; i < def->LeftBracket().size(); ++i) {
            dims.push_back(std::stoi(def->IntConst(i)->getText()));
        }
        
        // 创建数组类型
        llvm::Type* arrayType = type;
        for (int i = dims.size() - 1; i >= 0; --i) {
            arrayType = llvm::ArrayType::get(arrayType, dims[i]);
        }


        if (scopeLevel == 1) {
            // 全局作用域 -> 创建 GlobalVariable
            Constant* initVal = nullptr;
            //auto initValArray_global = def->constInitValArray();
            if (auto initValArray_global = def->constInitValArray()) {
                std::vector<llvm::Constant*> flatConstants;
                flattenConstInitValArrayLinear(initValArray_global, type, dims, 0, flatConstants);
                int totalElements = 1;
                for (int dim : dims) totalElements *= dim;
                while (flatConstants.size() < totalElements) {
                    flatConstants.push_back(Constant::getNullValue(type));
                }
                initVal = convertFlatToMultiDim(flatConstants, dims, type);
            } else {
                initVal = ConstantAggregateZero::get(arrayType);
            }
        
            GlobalVariable* gv = new GlobalVariable(
                module,
                arrayType,
                false,  // 是否 const，看你语义需求
                GlobalValue::ExternalLinkage,
                initVal,
                name
            );
        
            symbolTable.insert(name, arrayType, gv,false,false);
        }else {
            // 局部作用域 -> 创建 AllocaInst
            // 分配内存，如[2 x [2 x i32]]
            AllocaInst* alloca = builder.CreateAlloca(arrayType, nullptr, name);
            // 插入符号表
            symbolTable.insert(name, arrayType, alloca,false,false);
            std::cout<<"going to init array"<<std::endl;
            if(auto initValArray_not_global = def->constInitValArray()){
                //std::vector<llvm::Constant*> flatConstants;
                //flattenConstInitValArrayLinear(initValArray_not_global, type, dims, 0, flatConstants);

                std::vector<int> indicesSoFar;

                // ctx 取自你的 constInitValArrayContext
                initConstInitValArrayWithValues(
                    initValArray_not_global,  // 这是 HelloParser::ConstInitValArrayContext*
                    alloca,
                    type,                 // 单元素类型 (i32、i64……)
                    dims,                 // e.g. {4, 2} 表示 a[4][2]
                    0,                    // 从第 0 维开始
                    indicesSoFar
                );


            }else{
                // 计算总元素数
                int totalElements = 1;
                for (int d : dims) totalElements *= d;
                
                // 创建零常量
                llvm::Constant* zero = llvm::Constant::getNullValue(type);
 
                for (int flatIndex = 0; flatIndex < totalElements; ++flatIndex) {
                    // 计算多维索引（与初始化列表处理相同）
                    std::vector<int> indices(dims.size(), 0);
                    int remaining = flatIndex;
                    for (int d = dims.size() - 1; d >= 0; --d) {
                        indices[d] = remaining % dims[d];
                        remaining /= dims[d];
                    }
                
                    // 构造 GEP 索引
                    std::vector<Value*> gepIndices = {builder.getInt32(0)};
                    for (int idx : indices) {
                        gepIndices.push_back(builder.getInt32(idx));
                    }
                
                    // 获取元素指针
                    Value* elemPtr = builder.CreateGEP(
                        alloca->getType()->getPointerElementType(),
                        alloca,
                        gepIndices
                    );
                
                    // 写入零值
                    builder.CreateStore(zero, elemPtr);
                }
            }
        }
        symbolTable.print();
    }
    return nullptr;
}

// 处理数组的常量初始化值
// 遍历花括号中的每一个元素，对每个元素，如果是数字，递归构造GEP，存入b[][];
//                                    如果是子数组{x, y}，递归调用initArray_static（这个函数逻辑好像不是这样？）
Value* Analysis::processConstInitVal(HelloParser::ConstInitValContext* ctx, Type* type) {

    std::cout << "enter processConstInitVal"  << std::endl;
    if (ctx->constExp()) {  // 如果有常量表达式
        auto result = visit(ctx->constExp());  // 访问常量表达式
        std::cout << "visit constExp got type: " << result.type().name() << std::endl;

        try {
            std ::cout <<"got result value"<< std::endl;
            return std::any_cast<Value*>(result);  // 获取表达式的值
        } 
        catch (const std::bad_any_cast&) {
            std::cerr << "[Error] constExp does not return a Value*" << std::endl;
            exit(1);
        }
    }
    
    // 如果没有表达式，返回空值
    return Constant::getNullValue(type);
    // 处理完回到visitVardecl()，完成该数组变量的处理，继续处理下一个变量
}




// 初始化数组
// 用当前维度生成GEP地址（指到具体的子元素），用builder生成store

std::pair<llvm::Type*, std::vector<int>> Analysis::getParamType(HelloParser::FuncFParamContext* param)
{
    Type* baseType = getTypeFromBType(param->bType());

    // 没有括号就是普通变量
    if (param->LeftBracket().empty()) {
        return {baseType,{}};
    }

    // 处理维度信息（数组参数）
    std::vector<int> dims;

    // 第一个维度可能省略（隐式），如 int a[][4]，跳过维度 0
    
  
    int dimCount = param->IntConst().size();
    int BracketCount = param ->LeftBracket().size();
    if(BracketCount == (dimCount + 1)){
        int i = 1;
        dims.push_back(i);
    }
    

    // 提取所有维度
    for (int i = 0; i < dimCount; ++i) {
        int dimSize = std::stoi(param->IntConst(i)->getText());
        dims.push_back(dimSize);
    }

    // 构造内层数组类型（不包括最外层）
    Type* innerType = baseType;
    for (int i = dims.size() - 1; i >= 0; --i) {
        innerType = ArrayType::get(innerType, dims[i]);
    }

    // 最外层退化为指针
    return {innerType,dims};
}



std::any Analysis::visitFuncDef(HelloParser::FuncDefContext* ctx) {
    // 获取函数返回类型
    Type* returnType = getReturnType(ctx);  // 你需要在这个函数中处理如何获取返回类型

    // 获取函数名称
    std::string funcName = ctx->Ident()->getText();
    std::cout << "Function name: " << funcName << std::endl; 


    // 获取函数参数类型列表
    std::vector<Type*> paramTypes;
    for (auto param : ctx->funcFParams()->funcFParam()) {
        Type* paramType = nullptr;
        if (param->LeftBracket().empty()) {
            auto paramInfo = getParamType(param);
            paramType = paramInfo.first;
        }else{
            //paramType = PointerType::get(getParamType(param), 0);
            auto paramInfo = getParamType(param);
            Type* elementType = paramInfo.first; 
            // 如果elementType是数组类型，取元素类型
            if (elementType->isArrayTy()) {
                std::cout<<"[Debug]elementType是数组类型"<<std::endl;
                elementType = elementType->getArrayElementType();
            }
            paramType = llvm::PointerType::get(elementType, 0);  //退化
        }
        paramTypes.push_back(paramType);
    }


    // 创建函数类型，false 表示该函数不接受可变参数
    FunctionType* funcType = FunctionType::get(returnType, paramTypes, false);

    // 检查函数是否已经定义过
    if (functionTable.count(funcName)) {
        std::cerr << "[Error]: 函数 '" << funcName << "' 已经定义过。" << std::endl;
        exit(1);
    }


    // 创建函数并添加到模块中
    Function* func = Function::Create(funcType, Function::ExternalLinkage, funcName, module);
    functionTable[funcName] = func;
    currentFunctionReturnType = returnType;

    // 创建函数的基本块
    BasicBlock* entry = BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);  // 设置插入点为函数的入口基本块

    // 处理函数体中的变量声明
    // 处理函数参数
    symbolTable.enterScope();  // 进入新的作用域
    unsigned paramIdx = 0;
    // if (funcName == "main") {
    //     if (ctx->funcFParams() != nullptr && !ctx->funcFParams()->funcFParam().empty()) {
    //         std::cerr << "[Error]: main 函数不能有参数" << std::endl;
    //         exit(1);
    //     }
    // }
    
    for (auto param : ctx->funcFParams()->funcFParam()) {
        std::string paramName = param->Ident()->getText();
        //Type* paramType = getTypeFromBType(param->bType());
        auto paramInfo = getParamType(param);
        Type* paramType = paramInfo.first;
        std::vector<int> dims = paramInfo.second;
        std::cout << "dims = { ";
        for (int d : dims) {
            std::cout << d << " ";
        }
        std::cout << "}" << std::endl;

        Type* paramType_insert;
        AllocaInst* alloca = nullptr;
        if (param->LeftBracket().empty()) {
            paramType_insert = paramType;
            alloca = builder.CreateAlloca(paramType_insert, nullptr, paramName);
            //bool isArrayParam = param->LeftBracket().size() > 0;
            symbolTable.insert(paramName, paramType, alloca, false,false);
        }else{
            paramType_insert = paramType->getArrayElementType();
            //paramType_insert = PointerType::get(getParamType(param), 0);
            paramType_insert = llvm::PointerType::get(paramType_insert, 0); 
            alloca = builder.CreateAlloca(paramType_insert, nullptr, paramName);
            //bool isArrayParam = param->LeftBracket().size() > 0;
            symbolTable.insert(paramName, paramType_insert, alloca, false,true,dims);
        }

        std::cout<<"函数的参数插入符号表："<<paramName<<std::endl;
        symbolTable.print();
        std::cout<<"test point "<<paramName<<std::endl;

        // 获取函数参数的值（通过函数参数列表）
        Value* paramValue = func->getArg(paramIdx++);  // 从 Function 对象中获取参数
        std::cout<<"test point "<<paramName<<std::endl;
        // 将参数值存储到 alloca 的内存中
        builder.CreateStore(paramValue, alloca);

    }
        
    // 处理函数体中的语句
    if (ctx->block()) {
        visitBlock(ctx->block());  // 访问函数体（块）
    }
    if (returnType->isVoidTy() && !builder.GetInsertBlock()->getTerminator()) {
        builder.CreateRetVoid();
    }
    symbolTable.exitScope();  // 退出当前作用域

    // if (!returnType->isVoidTy() && !blockAlwaysReturns(ctx->block())) {
    //     std::cerr << "[Error] Function '" << funcName
    //               << "' may exit without returning a value\n";
    //     exit(1);
    // }
      
    return nullptr;  // 访问函数定义时不需要返回值
}


std::any Analysis::visitBlock(HelloParser::BlockContext *ctx) {
    std::cout << "visiting block"  << std::endl; 

    // 遍历每个 blockItem
    std::cout << "blockItem count: " << ctx->blockItem().size() << std::endl;
    for (auto item : ctx->blockItem()) {
        
        // 递归访问每个 blockItem，可能是声明或语句
        if (auto decl = item->decl()) {
             
            if(auto constdecl = decl -> constdecl()){
                visitConstDecl(constdecl);
            }else{
                std::cout << "visiting block - decl"  << std::endl;
                visitVarDecl(decl -> vardecl());
                std::cout << "visiting block - decl - end"  << std::endl;
            }
        } else if (auto stmt = item->stmt()) {
            std::cout << "visiting block - stmt"  << std::endl; 
            visitStmt(stmt);  // 处理语句
            // if(stmt->block()){
            //     symbolTable.exitScope();
            // }
        }
    }
    if (auto funcDefCtx = dynamic_cast<HelloParser::FuncDefContext*>(ctx->parent)) {
        std::cout << "Block belongs to a function body." << std::endl;
    }else{
        symbolTable.exitScope();
    }
    
    return nullptr;
}

llvm::Value* Analysis::getValueForVar(HelloParser::ExpContext* ctx) {
    std::string varName = ctx->getText();
    
    // 使用 lookup 查找变量
    auto symbolOpt = symbolTable.lookup(varName);
    if (symbolOpt) {
        // 查找到符号，返回其 LLVM 值
        return symbolOpt->irValue;
    } else {
        // 未找到符号，返回 nullptr
        std::cerr << "未找到变量: " << varName << std::endl;
        return nullptr;
    }
}
std::string typeToString(llvm::Type* type) {
    if (type->isIntegerTy(32)) return "int";
    if (type->isFloatTy()) return "float";
    if (type->isVoidTy()) return "void";
    return "unknown";
}
std::string getLLVMTypeStr(llvm::Type* type) {
    std::string str;
    llvm::raw_string_ostream rso(str);
    type->print(rso);
    return rso.str();
}
std::string extractVarName(HelloParser::ExpContext* ctx) {
    // 如果 ctx 是 LValContext，直接获取标识符
    auto lvalCtx = dynamic_cast<HelloParser::LValContext*>(ctx);
    if (lvalCtx) {
        // 返回第一个标识符的文本，即 "b" 而不是 "b[1][1]"
        return lvalCtx->Ident()->getText();
    }

    // // 如果 ctx 不是 LValContext，报错
    // std::cerr << "[Error] Left-hand side is not a valid LVal" << std::endl;
    // exit(1);
}

std::string Analysis::extractVarNameFromExp(HelloParser::ExpContext* ctx) {
    if (!ctx || !ctx->addExp()) return "";

    auto addExp = ctx->addExp();
    if (addExp->mulExp().empty()) return "";

    auto mulExp = addExp->mulExp(0);
    if (!mulExp || mulExp->unaryExp().empty()) return "";

    auto unaryExp = mulExp->unaryExp(0);
    if (!unaryExp || !unaryExp->primaryExp()) return "";

    auto primaryExp = unaryExp->primaryExp();
    if (!primaryExp || !primaryExp->lVal()) return "";

    auto lval = primaryExp->lVal();
    return lval->Ident()->getText();
}

llvm::Value* Analysis::getLValuePtr(HelloParser::ExpContext* ctx) {
    // 1. 从 ExpContext 里定位到 LValContext
    //    exp -> addExp -> mulExp[0] -> unaryExp[0] -> primaryExp -> lVal
    auto* add    = ctx->addExp();
    auto* mul    = add->mulExp()[0];
    auto* unary  = mul->unaryExp()[0];
    auto* prim   = unary->primaryExp();
    auto* lval   = prim->lVal();
    std::string varName = lval->Ident()->getText();

    // 2. 符号表查表拿到 basePtr（GlobalVariable* 或 AllocaInst*）
    symbolTable.print();
    auto symOpt = symbolTable.lookup(varName);
    if (!symOpt) {
        std::cerr << "[Error] Variable not found: " << varName << std::endl;
        exit(1);
    }
    llvm::Value* basePtr = symOpt->irValue;      // pointer to whole variable
    llvm::Type*  baseTy  = symOpt->llvmType;     // its LLVM 类型

    // 3. 为 GEP 准备索引：第一个 0 用来“进入”pointer
    std::vector<llvm::Value*> indices;
    //

    Value* arrayPtr = nullptr;
    if(1){
        //Value* arrayPtr = builder.CreateLoad(baseTy, basePtr, baseName + "_ptr");
        std::cout << "[Debug] basePtr Type: "<<std::endl;
        basePtr->getType()->print(llvm::outs());
        llvm::outs() << "\n";

        std::cout << "[Debug] basePtr Value: "<<std::endl;
        basePtr->print(llvm::outs());
        llvm::outs() << "\n";
        //indices.push_back(builder.getInt32(0));
        if(!symOpt->isArrayinFunc){
            indices.push_back(builder.getInt32(0));
        }
    }


    //    然后每个 [exp] 都要 visit 出一个 i32 索引
    for (auto* expCtx : lval->exp()) {
        llvm::Value* idxVal = std::any_cast<llvm::Value*>(visit(expCtx));
        // 如果是 i1（bool），拓展成 i32
        if (idxVal->getType()->isIntegerTy(1)) {
            idxVal = builder.CreateZExt(idxVal, builder.getInt32Ty(), "bool_to_i32");
        }
        indices.push_back(idxVal);
    }

    // 4. 调用 GEP
    //    basePtr->getType() 是 PtrType，pointerElementType() 才是数组或标量本身
    llvm::Value* elementPtr = nullptr;
    basePtr->getType()->getPointerElementType()->print(llvm::outs());
    llvm::outs() << "\n";
    if(symOpt->dimensions.size() && !symOpt->isArrayinFunc){
        
        std::cout<<"elementPtr = builder.CreateInBoundsGEP - start"<<std::endl;
        elementPtr = builder.CreateInBoundsGEP(
            basePtr->getType()->getPointerElementType(), // [3 x i32]
            basePtr,                                     // [3 x i32]*
            indices,                                     // {0, idx0, idx1, ...}
             varName + "_elem_ptr"
        );     
    }else if(symOpt->isArrayinFunc){
        std::cout<<"elementPtr = builder.CreateInBoundsGEP - array in func start"<<std::endl;
        // 先 Load 出真正的指针 T*（如果你存的是指向它的 i32**）
        llvm::Value* arrayPtr = builder.CreateLoad(
            basePtr->getType()->getPointerElementType(), // T*
            basePtr
        );
        // 然后对 T* 做 GEP，用一个 idx
        elementPtr = builder.CreateInBoundsGEP(
            arrayPtr->getType()->getPointerElementType(), // T
            arrayPtr,                                      // T*
            indices,                         // { idx }
            varName + "_elem_ptr"
        );

        std::cout<<"elementPtr = builder.CreateInBoundsGEP - end"<<std::endl;
    }else{
        
        elementPtr = builder.CreateInBoundsGEP(
            basePtr->getType()->getPointerElementType(), // element type
            basePtr,                                     // the pointer itself
            indices,
            varName + "_elem_ptr"
        );
        std::cout<<"elementPtr = builder.CreateInBoundsGEP - end"<<std::endl;
    }

    
    return elementPtr;  // 这个指针可直接用来 Store 或者 Load
}

bool Analysis::blockAlwaysReturns(HelloParser::BlockContext* blk) {
    for (auto item : blk->blockItem()) {
      if (item->stmt() && stmtAlwaysReturns(item->stmt()))
        return true;   // 一旦看到 return，就可以确定这一分支必定返回
    }
    return false;      // 遍历完都没碰到 return
}
  // if (cond) S1 else S2
//   → 只有当 S1 和 S2 都“必定返回”时，整个 if 才“必定返回”
bool Analysis::stmtAlwaysReturns(HelloParser::StmtContext* ctx) {
    if(ctx->RETURN_KW()){
        if(ctx->exp().empty()){
            return false;
        }
        return true;
    }else if(ctx->block()){
        return blockAlwaysReturns(ctx->block());
    }else if(ctx->stmt().empty()){
        return false;
    }else if(!ctx->stmt(1)){
        return stmtAlwaysReturns(ctx->stmt(0));
    }else{
        return stmtAlwaysReturns(ctx->stmt(0))
        && stmtAlwaysReturns(ctx->stmt(1));
    }
  }
  

std::any Analysis::visitStmt(HelloParser::StmtContext* ctx) {
    std::cout << "visiting Stmt - start"  << std::endl;

    bool hasReturnWithValue = false; // 用于记录非void函数是否有含返回值的return语句

    if (!ctx->exp().empty()) {  // 确保 exp 存在
        std::cout << "visiting Stmt - exp not empty"  << std::endl;
        // 处理表达式
        if (ctx->Assign()) {

            std::cout << "visiting Stmt - Assign" << std::endl;

            // 提取变量名
            std::string varName = extractVarNameFromExp(ctx->exp()[0]);
            std::cout << "visiting Stmt - Assign -varname:"<< varName << std::endl;
            // if (varName.empty()) {
            //     std::cerr << "[Error] Failed to extract var name from LHS expression" << std::endl;
            //     exit(1);
            // }

            std::optional<Symbol> lhs_name = symbolTable.lookup(varName);
            llvm::Value* lhs = nullptr;
            try {
                //lhs = std::any_cast<llvm::Value*>(visit(ctx->exp()[0]));
                std::cout<<"lhs = getLValuePtr(ctx->exp()[0]) begin"<<std::endl;
  
                lhs = getLValuePtr(ctx->exp()[0]); 
                std::cout<<"lhs = getLValuePtr(ctx->exp()[0]) finish"<<std::endl;
            } catch (const std::bad_any_cast& e) {
                std::cerr << "[Error] LHS is not a valid llvm::Value*: " << e.what() << std::endl;
                exit(1);
            }
    

            // 检查 const 属性
            auto symbolOpt = symbolTable.lookup(varName);
            // if (symbolOpt && symbolOpt->isConst) {
            //     std::cerr << "[Error] Cannot assign to const variable: " << varName << std::endl;
            //     exit(1);
            // }
    
            // 获取 RHS 表达式
            llvm::Value* rhs = nullptr;
            try {
                rhs = std::any_cast<llvm::Value*>(visit(ctx->exp()[1]));
            } catch (const std::bad_any_cast& e) {
                std::cerr << "[Error] RHS is not a valid llvm::Value*: " << e.what() << std::endl;
                exit(1);
            }
    
            // 类型匹配 & 转换
            llvm::Type* lhsType = lhs->getType()->getPointerElementType(); // 获取左值的实际类型
            //llvm::Type* lhsType = lhs->getType();
            llvm::Type* rhsType = rhs->getType();
            llvm::errs() << "LHS Type: ";
            
            lhsType->print(llvm::errs());
            llvm::errs() << "\n";

            llvm::errs() << "RHS Type: ";
            rhsType->print(llvm::errs());
            llvm::errs() << "\n";

            if (lhsType != rhsType) {
                if (rhsType->isIntegerTy(1) && lhsType->isIntegerTy(32)) {
                    rhs = builder.CreateZExt(rhs, llvm::Type::getInt32Ty(context), "booltoint");
                } 
                // else {
                //     std::cerr << "[Error] Type mismatch in assignment" << std::endl;
                //     exit(1);
                // }
            }
    
        
            builder.CreateStore(rhs, lhs);
        }        
        else if (ctx->RETURN_KW()) {
                size_t current = symbolTable.getCurrentScopeLevel();


                std::cerr << "处理 return 语句...scopelevel:" << current << std::endl;
        
                // 检查当前函数是否在作用域内
                // if (!currentFunctionReturnType) {
                //     std::cerr << "错误：return 语句不在函数内部！" << std::endl;
                //     exit(1);
                // }
        
                // 处理返回值
                if (ctx->exp().empty()) { 
                    // 无返回值的 return（仅允许 void 函数）
                    // if (!currentFunctionReturnType->isVoidTy()) {
                    //     std::cerr << "错误：非 void 函数缺少返回值！" << std::endl;
                    //     exit(1);
                    // }
                    builder.CreateRetVoid();
                } else { 
                    // 有返回值的 return
                    // if (currentFunctionReturnType->isVoidTy()) {
                    //     std::cerr << "错误：void 函数不能返回值！" << std::endl;
                    //     exit(1);
                    // }
        
                    auto returnExpr = visit(ctx->exp()[0]);
                    Value* returnValue= nullptr;
                    try {
                        returnValue = std::any_cast<Value*>(returnExpr);
                    } catch (const std::bad_any_cast& e) {
                        std::cerr << "[Error] returnValue did not return llvm::Value*: " << e.what() << std::endl;
                        exit(1);  // 或者你可以选择抛出异常 throw 或返回 nullptr
                    }
                    // if (returnValue->getType() != currentFunctionReturnType) {
                    //     std::cerr << "错误：返回值类型不匹配！" 
                    //                << "期望类型: " << typeToString(currentFunctionReturnType)
                    //                << "，实际类型: " << typeToString(returnValue->getType())
                    //                << std::endl;
                    //     exit(1);
                    // }
                    hasReturnWithValue = true; // 有含返回值的return语句
        
                    builder.CreateRet(returnValue);
                }
        }else{
            //这个地方会是一个void类型的函数调用
            // 处理其他表达式（如 void 函数调用）
            auto exprResult = visit(ctx->exp()[0]);
        }
        
        
    }
    // 处理 RETURN_KW
    
    // 进入新 block
    if(ctx -> block()){
        symbolTable.enterScope();
        return visitBlock(ctx->block());
        
    }

    if (ctx->IF_KW()) {

        llvm::Function* function = builder.GetInsertBlock()->getParent();

        // 创建 then、else 两个基本块
        llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(context, "then", function);
        llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(context, "else", function);
        //llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(context, "merge", function);
        llvm::BasicBlock* mergeBB = nullptr;
        bool needMerge = false;

        // 新增：使用短路逻辑构造的条件跳转语句，生成跳转到then或else的控制流
        genCond(ctx->cond(), thenBB, elseBB);
        
        // 创建条件跳转语句，根据 condValue 跳转到 then 或 else
        //builder.CreateCondBr(condValue, thenBB, elseBB);

        // 插入 thenBB 块中的语句
        builder.SetInsertPoint(thenBB);
        symbolTable.enterScope(); // 进入一层作用域
        std::cout << "visiting IF - thenBB"  << std::endl;
        visit(ctx->stmt(0));  // if 分支
        //builder.CreateBr(mergeBB);  // 无条件跳转到 merge 块
        // 只有在没有terminator时才跳转到merge块
        if (!builder.GetInsertBlock()->getTerminator()) {
            std::cout << "visiting IF - thenBB jump to mergeBB"  << std::endl;
            //if (!mergeBB && needMerge == false) {
            if (needMerge == false) {
                mergeBB = llvm::BasicBlock::Create(context, "merge", function);
                std::cout << "visiting IF - create mergeBB"  << std::endl;
            }
            builder.CreateBr(mergeBB);
            needMerge = true;
        }    

        symbolTable.exitScope(); // 退出一层作用域
        size_t current = symbolTable.getCurrentScopeLevel();
        std::cout << "visiting IF - thenBB end current scope level" << current << std::endl;
        
        symbolTable.print();
        // 插入 elseBB 块中的语句（如果有 else）
        builder.SetInsertPoint(elseBB);
        
        std::cout << "visiting IF - elseBB"  << std::endl;
        if (ctx->ELSE_KW()) {
            symbolTable.enterScope();
            visit(ctx->stmt(1));  // else 分支
            symbolTable.exitScope();
        }
        //builder.CreateBr(mergeBB);  // 无条件跳转到 merge 块
        // 只有在没有terminator时才跳转到merge块
        if (!builder.GetInsertBlock()->getTerminator()) {
            std::cout << "visiting IF - elseBB jump to mergeBB"  << std::endl;
            //if (!mergeBB && needMerge == false) {
            if (needMerge == false) {
                mergeBB = llvm::BasicBlock::Create(context, "merge", function);
                std::cout << "visiting IF - create mergeBB"  << std::endl;
            }
            builder.CreateBr(mergeBB);
            needMerge = true;
        } 

        

        // 设置插入点到 mergeBB，供后续代码插入
        //builder.SetInsertPoint(mergeBB);
        // 如果至少有一个分支没有终结，就设置 mergeBB
        //if (needMerge && mergeBB) {
        if (needMerge) {
            std::cout << "visiting IF - set insert point to mergeBB"  << std::endl;
            builder.SetInsertPoint(mergeBB);
        }
    }


    if (ctx->WHILE_KW()) {

        std::cout << "visiting Stmt - WHILE"  << std::endl;    
        
        // 获取当前函数作用域
        llvm::Function* function = builder.GetInsertBlock()->getParent();

        // 创建 cond、body、end三个基本块，命名基本块的名字
        llvm::BasicBlock* condBB = llvm::BasicBlock::Create(context, "while.cond", function);
        llvm::BasicBlock* bodyBB = llvm::BasicBlock::Create(context, "while.body", function);
        llvm::BasicBlock* afterBB = llvm::BasicBlock::Create(context, "while.after", function);

        // 进入while之前跳转到条件块
        builder.CreateBr(condBB);

        // 条件块，插入 condBB 块中的语句
        builder.SetInsertPoint(condBB);
        
        // 入栈
        std::cout << "WHILE - pushing condBB and afterBB" << std::endl;
        condBBStack.push(condBB);// 将当前循环的condBB压入一个栈中
        afterBBStack.push(afterBB);
        
        // 创建条件跳转语句，根据 condValue 跳转到 then 或 else
        //builder.CreateCondBr(condValue, bodyBB, afterBB);

        // 新增：使用短路逻辑构造的条件跳转语句，生成跳转到body或after的控制流
        std::cout << "WHILE - generating conditional branch" << std::endl;
        genCond(ctx->cond(), bodyBB, afterBB);

        // 循环体块
        std::cout << "WHILE - entering body" << std::endl;
        builder.SetInsertPoint(bodyBB);
        symbolTable.enterScope();
        visit(ctx->stmt(0));  // 假设stmt是循环体

        // 循环体执行完回到条件判断
        std::cout << "WHILE - jumping back to condBB" << std::endl;
        //builder.CreateBr(condBB);
        // 检查当前body中是否已经有终止指令（terminator）
        // 若有，不应该再生成跳转到while.cond的指令
        if (!builder.GetInsertBlock()->getTerminator()) {
            builder.CreateBr(condBB);
        }


        // 出栈（循环结束）
        std::cout << "WHILE - popping condBB and afterBB" << std::endl;
        condBBStack.pop();
        afterBBStack.pop();
        symbolTable.exitScope();
        // 结束块
        builder.SetInsertPoint(afterBB);
    }


    if (ctx->BREAK_KW()) {
        std::cout << "visiting Stmt - BREAK" << std::endl;

        // 跳转到当前循环的结束块（即 afterBB）
        std::cout << "BREAK - jumping to afterBB" << std::endl;
        builder.CreateBr(afterBBStack.top());
    }

    if (ctx->CONTINUE_KW()) {
        std::cout << "visiting Stmt - CONTINUE" << std::endl;

        // 跳转到当前循环的条件判断块（即 condBB）
        std::cout << "CONTINUE - jumping to condBB" << std::endl;
        builder.CreateBr(condBBStack.top());
    }
    
    if(ctx->Semi()){
        ;
    }
    return nullptr;
}


std::any Analysis::visitExp(HelloParser::ExpContext* ctx) {
    return visit(ctx->addExp());
}
std::any Analysis::visitAddExp(HelloParser::AddExpContext* ctx) {
    // 只有一个 mulExp
    if (ctx->children.size() == 1) {
        return visit(ctx->mulExp(0));
    }

    llvm::Value* lhs = nullptr;
    try {
        lhs = std::any_cast<llvm::Value*>(visit(ctx->mulExp(0)));
    } catch (const std::bad_any_cast& e) {
        std::cerr << "[Error] lhs expression did not return llvm::Value*: " << e.what() << std::endl;
        exit(1);  
    }
    for (size_t i = 1; i < ctx->mulExp().size(); ++i) {
        llvm::Value* rhs = nullptr;
        try {
            rhs = std::any_cast<llvm::Value*>(visit(ctx->mulExp(i)));
        } catch (const std::bad_any_cast& e) {
            std::cerr << "[Error] rhs expression did not return llvm::Value*: " << e.what() << std::endl;
            exit(1);  
        }

        llvm::Type* lhsType = lhs->getType();
        llvm::Type* rhsType = rhs->getType();


        // 再检查类型是否一致
        // if (lhsType != rhsType) {
        //     std::cerr << "[Error] Type mismatch in AddExp "<< std::endl;
        //     exit(1);
        // }

        std::string op = ctx->children[i * 2 - 1]->getText(); // Plus or Minus

        if (op == "+") {
            lhs = lhsType->isFloatTy() ? 
                builder.CreateFAdd(lhs, rhs, "faddtmp") :
                builder.CreateAdd(lhs, rhs, "addtmp");
        } else if (op == "-") {
            lhs = lhsType->isFloatTy() ? 
                builder.CreateFSub(lhs, rhs, "fsubtmp") :
                builder.CreateSub(lhs, rhs, "subtmp");
        } 
        // else {
        //     std::cerr << "Unsupported addExp op: " << op << std::endl;
        //     exit(1);
        // }
    }

    return lhs;
}

std::any Analysis::visitMulExp(HelloParser::MulExpContext* ctx) {
    if (ctx->children.size() == 1) {
        return visit(ctx->unaryExp(0));
    }

    std::cout<<"------visitMulExp------"<<std::endl;
    llvm::Value* lhs = std::any_cast<llvm::Value*>(visit(ctx->unaryExp(0)));

    for (size_t i = 1; i < ctx->unaryExp().size(); ++i) {
        llvm::Value* rhs = std::any_cast<llvm::Value*>(visit(ctx->unaryExp(i)));
        std::string op = ctx->children[i * 2 - 1]->getText();


        //类型检查
        llvm::Type* lhsType = lhs->getType();
        llvm::Type* rhsType = rhs->getType();
        // 类型检查
        // if(lhsType != rhsType){
        //     std::cout<<"[Error: 乘除法类型不匹配]"<<std::endl;
        //     exit(1);
        // }

    // 确保 lhs 和 rhs 类型一致后再判断类型
    if (lhsType->isIntegerTy()) {
        if (op == "*") {
            lhs = builder.CreateMul(lhs, rhs, "multmp");
        } else if (op == "/") {
            lhs = builder.CreateSDiv(lhs, rhs, "divtmp");
        } else if (op == "%") {
            lhs = builder.CreateSRem(lhs, rhs, "modtmp");
        } 
        // else {
        //     std::cerr << "[Error] 不支持的整数操作符: " << op << std::endl;
        //     exit(1);
        // }
    } else if (lhsType->isFloatingPointTy()) {
        std::cout<<"乘除法是float类型"<<std::endl;
        if (op == "*") {
            lhs = builder.CreateFMul(lhs, rhs, "fmultmp");
        } else if (op == "/") {
            lhs = builder.CreateFDiv(lhs, rhs, "fdivtmp");
        } 
        // else if (op == "%") {
        //     std::cerr << "[Error] LLVM 不支持浮点类型的模运算（%）" << std::endl;
        //     exit(1);
        // } else {
        //     std::cerr << "[Error] 不支持的浮点操作符: " << op << std::endl;
        //     exit(1);
        // }
    } 
    // else {
    //     std::cerr << "[Error] 不支持的类型（非整数也非浮点）" << std::endl;
    //     exit(1);
    // }
    }
    return lhs;

}

std::any Analysis::visitUnaryExp(HelloParser::UnaryExpContext* ctx) {
    std::cout << "visitUnaryExp" << std::endl;
    // Case 1: 是 primaryExp
    if (ctx->primaryExp()) {
        std::cout << "---visitUnaryExp---entering case1" << std::endl;
        return visit(ctx->primaryExp());
    }


    // Case 2: 是函数调用
    if (ctx->Ident()) {
        std::cout << "visitUnaryExp - func call" << std::endl;
        std::string funcName = ctx->Ident()->getText();

        // 查找函数
        llvm::Function* calleeFunc = functionTable[funcName];
        // if (!calleeFunc) {
        //     std::cerr << "[Error]Unknown function: " << funcName << std::endl;
        //     exit(1);
        // }

        std::vector<llvm::Value*> args;

        // 如果有实参
        if (ctx->funcRParams()) {
            std::cout << "func going to get Params " << funcName << std::endl;
            for (auto expCtx : ctx->funcRParams()->exp()) {
                auto arg = std::any_cast<llvm::Value*>(visit(expCtx));
                args.push_back(arg);
            }
        }
        std::cout << "func going to get Params -finish -funcname:" << funcName << std::endl;

        std::cout << "ready to call" << std::endl;
        if (calleeFunc->getReturnType()->isVoidTy()) {
            // void 函数调用：不指定名称
            builder.CreateCall(calleeFunc, args);
            return nullptr;
        } else {
            // 非 void 函数调用：指定名称
            llvm::Value* callResult = builder.CreateCall(calleeFunc, args, "calltmp");
            return static_cast<llvm::Value*>(callResult);
        }
    }

    // Case 3: 是一元操作
    if (ctx->unaryExp() && (ctx->Plus() || ctx->Minus() || ctx->Not())) {
        std::cout << "---visitUnaryExp---entering case3" << std::endl;
        llvm::Value* operand = std::any_cast<llvm::Value*>(visit(ctx->unaryExp()));
        if (ctx->Plus()) {
            return operand;
        } 
        else if (ctx->Minus()) {
            if (operand->getType()->isFloatingPointTy()) {
                return builder.CreateFNeg(operand, "fnegtmp");
            } else {
                return builder.CreateNeg(operand, "negtmp");
            }
        } 
        else if (ctx->Not()) {
            std::cout <<"-------------test 29.cact ----------------"<<std::endl;
            llvm::Value* zero = llvm::ConstantInt::get(operand->getType(), 0);

            return builder.CreateICmpEQ(operand, zero, "nottmp");
        }
    }

    std::cerr << "Unhandled unaryExp!" << std::endl;
    return nullptr;
}

std::optional<int> tryEvaluateConstIndex(HelloParser::ExpContext* expCtx) {
    auto addCtx = expCtx->addExp();
    if (!addCtx) return std::nullopt;

    auto mulCtx = addCtx->mulExp(0);
    if (!mulCtx) return std::nullopt;

    auto unaryCtx = mulCtx->unaryExp(0);
    if (!unaryCtx) return std::nullopt;

    auto primaryCtx = unaryCtx->primaryExp();
    if (!primaryCtx) return std::nullopt;

    // 是否是一个 number
    auto numberCtx = primaryCtx->number();
    if (!numberCtx) return std::nullopt;

    // 解析 number
    if (numberCtx->IntConst()) {
        return std::stoi(numberCtx->IntConst()->getText());
    }
    return std::nullopt; // 你也可以支持 FloatConst，这里暂时只支持 int
}

std::any Analysis::visitPrimaryExp(HelloParser::PrimaryExpContext* ctx) {
    // 括号表达式
    if (ctx->exp()) {
        return visit(ctx->exp());
    }

    // 整数常量
    if (ctx->number()) {
        std::cout<<"got return number"<<std::endl;
        //auto val = visitNumber(ctx->number());
        return visitNumber(ctx->number());
    }

    // 左值变量引用
    if (ctx->lVal()) { 
    std::cout<<"ctx->lVal()"<<std::endl;
        std::cout<<"----- is 32.cact stop there -----"<<std::endl;
        return visitLVal(ctx->lVal());
    }

    std::cerr << "Unhandled primaryExp!" << std::endl;
    return nullptr;
}

std::any Analysis::visitLVal(HelloParser::LValContext* lValCtx) {
    // 1) 基础名字
    std::string baseName = lValCtx->Ident()->getText();
    auto symOpt = symbolTable.lookup(baseName);
    if (!symOpt) {
        std::cerr << "[Error]: Undefined variable: " << baseName << std::endl;
        exit(1);
    }

    std::cout<<"symOpt is "<<baseName<<std::endl;
    // sym->irValue 是 GlobalVariable* 或 AllocaInst*
    llvm::Value* basePtr = symOpt->irValue;
    llvm::Type*  baseTy  = symOpt->llvmType;

    // 2) 看它是不是带下标的数组访问
    llvm::Value* returnValue = nullptr;

    if (lValCtx->exp().empty()) {

        // —— 普通标量变量（或指针）访问
        // 直接 load 这个 pointer
        //std::cout<<"lval is not 带下标的数组访问"<<std::endl;
        if(symOpt -> isArrayinFunc){                  
            llvm::Value* arrayPtr = builder.CreateLoad(basePtr->getType()->getPointerElementType(), basePtr, "loaded_array_ptr");
            // std::cout<<"lval is not 带下标的数组访问 - isArrayinFunc"<<std::endl;
            // llvm::Value* firstElemPtr = builder.CreateInBoundsGEP(
            //     baseTy,                  // 例如 [M x [N x float]]
            //     arrayPtr,                 // [M x [N x float]]*
            //     { builder.getInt32(0),   // 先“进”到第 0 个数组
            //     builder.getInt32(0)}, // 再“进”到第 0 个子数组的第 0 个元素
            //     baseName + "_decay"
            // );
            return arrayPtr;
        }else if(!symOpt->dimensions.empty()){            
            llvm::Value* firstElemPtr = builder.CreateInBoundsGEP(
                baseTy,                  // 例如 [M x [N x float]]
                basePtr,                 // [M x [N x float]]*
                { builder.getInt32(0) ,  // 先“进”到第 0 个数组
                    builder.getInt32(0) }, // 再“进”到第 0 个子数组的第 0 个元素
                baseName + "_decay"
            );
            // firstElemPtr 的类型就是 float*（或者更深维度的子数组指针）
            return firstElemPtr;

        }else{
            std::cout<<"----- 普通变量 -----"<<std::endl;
            returnValue = builder.CreateLoad(symOpt->llvmType, symOpt->irValue, baseName +"_var");
            return returnValue;
        }
        
    } else {
        std::cout << "[Debug] lval is 数组"<<std::endl;
        std::vector<llvm::Value*> indices;
        Value* arrayPtr = nullptr;
        if(!symOpt->isArrayinFunc){
            //Value* arrayPtr = builder.CreateLoad(baseTy, basePtr, baseName + "_ptr");
            std::cout << "[Debug] basePtr Type: ";
            basePtr->getType()->print(llvm::outs());
            llvm::outs() << "\n";
    
            std::cout << "[Debug] basePtr Value: ";
            basePtr->print(llvm::outs());
            llvm::outs() << "\n";
            indices.push_back(builder.getInt32(0));
        }else{
            arrayPtr = builder.CreateLoad(basePtr->getType()->getPointerElementType(), basePtr, "loaded_array_ptr");
            std::cout << "[Debug] arrayPtr Type: ";
            arrayPtr->getType()->print(llvm::outs());
            llvm::outs() << "\n";
            std::cout << "[Debug] arrayPtr Value: ";
            arrayPtr->print(llvm::outs());
            llvm::outs() << "\n";
            //indices.push_back(builder.getInt32(0));
        }


        // 遍历每一个下标表达式
        for (auto* expCtx : lValCtx->exp()) {
            llvm::Value* idx = std::any_cast<llvm::Value*>(visit(expCtx));
            llvm::Type* idxType = idx->getType()
            ;
            std::cout << "[Debug] Index "  <<std::endl;
            idxType->print(llvm::outs());
            llvm::outs() << "\n";

            // if (!idxType->isIntegerTy(32)) {
            //     std::cerr << "[Error]: Array index expression must be of type int (i32), "
            //             << "but got: ";
            //     idxType->print(llvm::errs());
            //     std::cerr << std::endl;
            //     exit(1);
            // }
            indices.push_back(idx);
        }
        const auto& dims = symOpt->dimensions;
        std::cout<<"dims.size() is "<<dims.size()<<std::endl;
        std::cout<<"lValCtx->exp().size() is "<<lValCtx->exp().size()<<std::endl;
        

        std::cout<<"going to ex llvm::Value* elemPtr = builder.CreateInBoundsGEP"<<std::endl;
        llvm::Value* elemPtr = nullptr;
        if(!symOpt->isArrayinFunc){
            if(symOpt->dimensions.size() && !(lValCtx->exp().size() == dims.size())){
                indices.push_back(builder.getInt32(0));
            }
            elemPtr = builder.CreateInBoundsGEP(
                basePtr->getType()->getPointerElementType(), // 即 [2 x [2 x float]]
                basePtr, // 不应该是 load 出来的值，而是变量地址
                indices,
                baseName + "_elem_ptr"
            );   

        }else{
            if(!(lValCtx->exp().size() == dims.size())){
                indices.push_back(builder.getInt32(0));
            }
            elemPtr = builder.CreateInBoundsGEP(
                arrayPtr->getType()->getPointerElementType(), // 即 [2 x [2 x float]]
                arrayPtr, // 不应该是 load 出来的值，而是变量地址
                indices,
                baseName + "_elem_ptr"
            );  
        } 
        std::cout<<"elemPtr gepped"<<std::endl;

        int size_indices = indices.size();
        if(symOpt->isArrayinFunc){
            size_indices++;
        }

        if(symOpt->dimensions.size() && !(lValCtx->exp().size() == dims.size())){
            size_indices--;
        }

        //const auto& dims = symOpt->dimensions;
        // 用正确的元素类型来创建 Load
        if (size_indices-1 < dims.size() ) {
            std::cout<<"返回的是elemPtr"<<std::endl;
            // 返回子数组指针（用于函数参数传递）
            std::cout << "[Debug] elemPtr Type: "<<std::endl;
            elemPtr->getType()->print(llvm::outs());
            llvm::outs() << "\n";
            std::cout << "[Debug] elemPtr Value: "<<std::endl;
            elemPtr->print(llvm::outs());
            llvm::outs() << "\n";
            return elemPtr;
        } else {
            std::cout<<"返回的不是elemPtr"<<std::endl;
            llvm::Value* returnValue =builder.CreateLoad(
                elemPtr->getType()->getPointerElementType(),
                elemPtr,
                baseName + "_val"
            );
            // 加载最终元素值
            return returnValue;
        }
    
    }
}

std::any Analysis::visitConstExp(HelloParser::ConstExpContext *ctx) {
    return visit(ctx->addExp());
}
/*
std::any Analysis::visitNumber(HelloParser::NumberContext *ctx) {

    std::string text = ctx->getText();
    std::cout << "get const number "<< text << std::endl;
    llvm::Value* value = nullptr;
    if (text.length() == 3 && text.front() == '\'' && text.back() == '\'') {
        std::string content = text.substr(1, text.length() - 2);  // 去掉两侧单引号
        char c = 0;

        if (content.length() == 1) {
            c = content[0];  // 普通字符
        } 

        value = llvm::ConstantInt::get(llvm::Type::getInt8Ty(context), static_cast<uint8_t>(c), true);

        std::cout << "构造出的ConstantInt字符值（ASCII）: " << static_cast<int>(c) << std::endl;
        return value;
    }
    // 判断是否是浮点常量（含 '.' 或 e/E 或 f/F）
    else if (text.find('.') != std::string::npos || text.find('e') != std::string::npos ||
        text.find('E') != std::string::npos || text.find('f') != std::string::npos ||
        text.find('F') != std::string::npos) {
        float floatVal = std::stof(text);
        value = llvm::ConstantFP::get(llvm::Type::getFloatTy(context), floatVal);
    } else {
        int intVal = 0;
        if (text.compare(0, 2, "0x") == 0 || text.compare(0, 2, "0X") == 0) {
            intVal = std::stoi(text, nullptr, 16); // 十六进制
        } else if (text[0] == '0' && text.size() > 1) {
            intVal = std::stoi(text, nullptr, 8); // 八进制
        } else {
            intVal = std::stoi(text); // 十进制
            std::cout << "get const number - 十进制"<< intVal << std::endl;
        }
        value = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), intVal, true);
        if (auto *constInt = llvm::dyn_cast<llvm::ConstantInt>(value)) {
            std::cout << "构造出的ConstantInt值: " << constInt->getSExtValue() << std::endl;
        } else {
            std::cerr << "构造的value不是ConstantInt!" << std::endl;
        }
    }

    return value;
}


std::any Analysis::visitNumber(HelloParser::NumberContext *ctx) {
    std::string text = ctx->getText();
    std::cout << "get const number: " << text << std::endl;

    llvm::Value* value = nullptr;

    // 1. 字符常量：形如 'a'（长度3，首尾单引号）
    if (text.length() == 3 && text.front() == '\'' && text.back() == '\'') {
        char c = text[1];  // 去掉两侧单引号之后的字符
        value = llvm::ConstantInt::get(
            llvm::Type::getInt8Ty(context),
            static_cast<uint8_t>(c),
            true  // 有符号
        );
        std::cout << "  构造出的 ConstantInt 字符值 (ASCII): " << static_cast<int>(c) << std::endl;
        return value;
    }

    // 2. 十六进制整数：以 "0x" 或 "0X" 开头
    if (text.size() > 2 && (text.rfind("0x", 0) == 0 || text.rfind("0X", 0) == 0)) {
        // stoi 第二个参数 nullptr，第三个参数 16 表示十六进制
        long long intVal = 0;
        try {
            intVal = std::stoll(text, nullptr, 16);
        } catch (...) {
            std::cerr << "[Error] 无法将 \"" << text << "\" 解析为十六进制整数！" << std::endl;
            exit(1);
        }
        value = llvm::ConstantInt::get(
            llvm::Type::getInt32Ty(context),
            intVal,
            true
        );
        std::cout << "  解析为十六进制整数: " << intVal << std::endl;
        return value;
    }

    // 3. 八进制整数：以 '0' 开头且后续全部是 [0-7]
    if (text.size() > 1 && text[0] == '0') {
        bool allOctal = true;
        for (size_t i = 1; i < text.size(); ++i) {
            if (text[i] < '0' || text[i] > '7') {
                allOctal = false;
                break;
            }
        }
        if (allOctal) {
            long long intVal = 0;
            try {
                intVal = std::stoll(text, nullptr, 8);
            } catch (...) {
                std::cerr << "[Error] 无法将 \"" << text << "\" 解析为八进制整数！" << std::endl;
                exit(1);
            }
            value = llvm::ConstantInt::get(
                llvm::Type::getInt32Ty(context),
                intVal,
                true
            );
            std::cout << "  解析为八进制整数: " << intVal << std::endl;
            return value;
        }
    }

    // 4. 浮点常量：含 '.' 或 'e'/'E' 或后缀 'f'/'F'
    bool hasDot = (text.find('.') != std::string::npos);
    bool hasExp = (text.find('e') != std::string::npos) || (text.find('E') != std::string::npos);
    bool hasSuffixF = (!text.empty() && (text.back() == 'f' || text.back() == 'F'));
    if (hasDot || hasExp || hasSuffixF) {
        // 如果末尾是 'f' 或 'F'，先去掉后缀
        std::string tmp = text;
        if (hasSuffixF) {
            tmp.pop_back();
        }
        float floatVal = 0.0f;
        try {
            floatVal = std::stof(tmp);
        } catch (...) {
            std::cerr << "[Error] 无法将 \"" << text << "\" 解析为浮点数！" << std::endl;
            exit(1);
        }
        value = llvm::ConstantFP::get(
            llvm::Type::getFloatTy(context),
            floatVal
        );
        std::cout << "  解析为浮点数: " << floatVal << std::endl;
        return value;
    }

    // 5. 其他情形统统当十进制整数处理
    long long intVal = 0;
    try {
        intVal = std::stoll(text, nullptr, 10);
    } catch (...) {
        std::cerr << "[Error] 无法将 \"" << text << "\" 解析为十进制整数！" << std::endl;
        exit(1);
    }
    value = llvm::ConstantInt::get(
        llvm::Type::getInt32Ty(context),
        intVal,
        true
    );
    std::cout << "  解析为十进制整数: " << intVal << std::endl;
    return value;
}
*/

std::any Analysis::visitNumber(HelloParser::NumberContext *ctx) {
    std::string text = ctx->getText();
    std::cout << "get const number: " << text << std::endl;

    // 1. 字符常量：形如 'a'（长度3，首尾单引号）
    if (text.length() == 4 && text.front() == '\'' && text.back() == '\'') {
        char c;
        if(text[2] == 'n'){
            c = '\n';
        }else if(text[2] == 't'){
            c = '\t';
        }else if(text[2] == 'b'){
            c = '\b';
        }else if(text[2] == 'r'){
            c = '\r';
        }
        
        auto value = llvm::ConstantInt::get(
            llvm::Type::getInt8Ty(context),
            static_cast<uint8_t>(c),
            true  // 有符号
        );
        std::cout << "  构造出的 ConstantInt 字符值 (ASCII): " << static_cast<int>(c) << std::endl;
        return std::any(static_cast<llvm::Value*>(value));
    }

    if (text.length() == 3 && text.front() == '\'' && text.back() == '\'') {
        char c = text[1];  // 去掉两侧单引号之后的字符
        auto value = llvm::ConstantInt::get(
            llvm::Type::getInt8Ty(context),
            static_cast<uint8_t>(c),
            true  // 有符号
        );
        std::cout << "  构造出的 ConstantInt 字符值 (ASCII): " << static_cast<int>(c) << std::endl;
        return std::any(static_cast<llvm::Value*>(value));
    }

    // 2. 浮点数常量处理
    if (ctx->FloatConst()) {
        return parseFloatConstant(text);
    }

    // 3. 整数常量处理
    return parseIntConstant(text);
}

llvm::Value* Analysis::parseFloatConstant(const std::string& text) {
    // 检查并处理后缀
    bool isFloat = false;
    bool isLongDouble = false;
    std::string numText = text;
    
    if (!text.empty()) {
        char last = text.back();
        if (last == 'f' || last == 'F') {
            isFloat = true;
            numText = text.substr(0, text.size() - 1);
        }
    }

    // 十六进制浮点数处理 (0x...p...)
    if (numText.size() > 2 && (numText[0] == '0' && (numText[1] == 'x' || numText[1] == 'X'))) {
        // 使用strtod处理十六进制浮点数
        char* endPtr;
        float floatVal = strtof(numText.c_str(), &endPtr);
        std::cout << "  解析为十六进制浮点数 (float): " << floatVal << std::endl;
        return llvm::ConstantFP::get(
            llvm::Type::getFloatTy(context),
            floatVal
        );
    }
    // 十进制浮点数处理
    else {
        char* endPtr;
        float floatVal = strtof(numText.c_str(), &endPtr);
        std::cout << "  解析为十进制浮点数 (float): " << floatVal << std::endl;
        return llvm::ConstantFP::get(
            llvm::Type::getFloatTy(context),
            floatVal
        );    
    }
}

llvm::Value* Analysis::parseIntConstant(const std::string& text) {
    // 十六进制整数：以 "0x" 或 "0X" 开头
    if (text.size() > 2 && (text.rfind("0x", 0) == 0 || text.rfind("0X", 0) == 0)) {
        long long intVal = 0;
        try {
            intVal = std::stoll(text, nullptr, 16);
        } catch (...) {
            std::cerr << "[Error] 无法将 \"" << text << "\" 解析为十六进制整数！" << std::endl;
            exit(1);
        }
        auto value = llvm::ConstantInt::get(
            llvm::Type::getInt32Ty(context),
            intVal,
            true
        );
        std::cout << "  解析为十六进制整数: " << intVal << std::endl;
        return value;
    }

    // 八进制整数：以 '0' 开头且后续全部是 [0-7]
    if (text.size() > 1 && text[0] == '0') {
        bool allOctal = true;
        for (size_t i = 1; i < text.size(); ++i) {
            if (text[i] < '0' || text[i] > '7') {
                allOctal = false;
                break;
            }
        }
        if (allOctal) {
            long long intVal = 0;
            try {
                intVal = std::stoll(text, nullptr, 8);
            } catch (...) {
                std::cerr << "[Error] 无法将 \"" << text << "\" 解析为八进制整数！" << std::endl;
                exit(1);
            }
            auto value = llvm::ConstantInt::get(
                llvm::Type::getInt32Ty(context),
                intVal,
                true
            );
            std::cout << "  解析为八进制整数: " << intVal << std::endl;
            return value;
        }
    }

    // 其他情形当十进制整数处理
    long long intVal = 0;
    try {
        intVal = std::stoll(text, nullptr, 10);
    } catch (...) {
        std::cerr << "[Error] 无法将 \"" << text << "\" 解析为十进制整数！" << std::endl;
        exit(1);
    }
    auto value = llvm::ConstantInt::get(
        llvm::Type::getInt32Ty(context),
        intVal,
        true
    );
    std::cout << "  解析为十进制整数: " << intVal << std::endl;
    return value;
}


std::any Analysis::visitCond(HelloParser::CondContext *ctx) {
    std::cout << "visiting Cond - going to visit lOrExp"  << std::endl;
    return visit(ctx->lOrExp());
}

// 有控制参数的重载版本：不返回 Value，而是根据条件控制跳转到对应的基本块
void Analysis::genCond(HelloParser::CondContext* ctx, llvm::BasicBlock* trueBB, llvm::BasicBlock* falseBB) {
    std::cout << "visiting genCond - generating control flow from lOrExp" << std::endl;

    // Cond → LOrExp
    // 短路求值逻辑在 genLOrExp() 中实现：
    // 只要 LOrExp 中有一个子项为真，就跳 trueBB；否则跳 falseBB
    if (!builder.GetInsertBlock()->getTerminator()) {
        genLOrExp(ctx->lOrExp(), trueBB, falseBB);
    }
}


std::any Analysis::visitLAndExp(HelloParser::LAndExpContext *ctx) {
    std::cout << "visiting LAndExp"  << std::endl;
    llvm::Value* lhs = std::any_cast<llvm::Value*>(visit(ctx->eqExp(0)));

    // 将 lhs 转换为i1，非零即真
    lhs = builder.CreateICmpNE(lhs, llvm::ConstantInt::get(lhs->getType(), 0), "cmp_lhs");

    for (size_t i = 1; i < ctx->eqExp().size(); ++i) {
        llvm::Value* rhs = std::any_cast<llvm::Value*>(visit(ctx->eqExp(i)));

        // 将 rhs 转换为i1，非零即真
        rhs = builder.CreateICmpNE(rhs, llvm::ConstantInt::get(rhs->getType(), 0), "cmp_rhs");
        // 生成逻辑与：i1 and i1 -> i1
        lhs = builder.CreateAnd(lhs, rhs, "and_tmp");
    }

    return lhs; // 返回的是 i1 类型
}

// 生成一个逻辑与表达式（LAndExp）的短路逻辑代码：a && b && c ... 形式
// 参数 trueBB: 所有子表达式都为真时跳转的目标基本块
// 参数 falseBB: 一旦有一个为假就跳转的目标基本块
void Analysis::genLAndExp(HelloParser::LAndExpContext* ctx, llvm::BasicBlock* trueBB, llvm::BasicBlock* falseBB) {
    std::cout << "visiting LAndExp - Short-circuit Evaluation"  << std::endl;
    size_t n = ctx->eqExp().size();  // n 为 EqExp 的个数（LAndExp 是多个 EqExp 用 '&&' 连接而成）

    llvm::Function* func = builder.GetInsertBlock()->getParent();  // 当前所在函数

    for (size_t i = 0; i < n; ++i) {
        std::cout << "-----entering genLAndExp for loop-----"  << std::endl;
        // 获取第 i 个子表达式
        HelloParser::EqExpContext* eq = ctx->eqExp(i);

        // 调用 visit(eq) 得到这个子表达式的结果值（通常是 i32 类型）
        llvm::Value* cond = std::any_cast<llvm::Value*>(visit(eq));

        // 将 cond 转换为 i1 类型，非零即真
        //cond = castToBool(cond);  // 转换为 i1（布尔值）
        cond = builder.CreateICmpNE(cond, llvm::ConstantInt::get(cond->getType(), 0), "cmp_tmp");

        if (i == n - 1) {
            // 最后一个子表达式，直接跳到 true 或 false
            builder.CreateCondBr(cond, trueBB, falseBB);
        } else {
            // 中间表达式：真则继续判断下一个子条件，假则直接跳 falseBB

            // 创建一个临时基本块，用于接下一个条件判断
            
            llvm::BasicBlock* nextBB = llvm::BasicBlock::Create(context, "land_next", func);
            std::cout << "----create a land_next----"  << std::endl;

            builder.CreateCondBr(cond, nextBB, falseBB);
            builder.SetInsertPoint(nextBB);


        }
    }
}

std::any Analysis::visitLOrExp(HelloParser::LOrExpContext *ctx) {
    std::cout << "visiting LOrExp"  << std::endl;
    llvm::Value* lhs = std::any_cast<llvm::Value*>(visit(ctx->lAndExp(0)));

    // 将 lhs 转换为 i1 类型
    lhs = builder.CreateICmpNE(lhs, llvm::ConstantInt::get(lhs->getType(), 0), "cmp_lhs");

    std::cout << "visited LOrExp - first lAndExp"  << std::endl;
    for (size_t i = 1; i < ctx->lAndExp().size(); ++i) {
        llvm::Value* rhs = std::any_cast<llvm::Value*>(visit(ctx->lAndExp(i)));

        // 将 rhs 转换为 i1 类型
        rhs = builder.CreateICmpNE(rhs, llvm::ConstantInt::get(rhs->getType(), 0), "cmp_rhs");

        lhs = builder.CreateOr(lhs, rhs, "or_tmp");
    }

    return lhs;
}

// 生成一个逻辑或表达式（LOrExp）的短路逻辑代码：a || b || c ... 形式
// 参数 trueBB: 一旦有一个为真就跳转的目标基本块
// 参数 falseBB: 所有都为假时跳转的目标基本块
void Analysis::genLOrExp(HelloParser::LOrExpContext* ctx, llvm::BasicBlock* trueBB, llvm::BasicBlock* falseBB) {
    std::cout << "visiting LOrExp - Short-circuit Evaluation"  << std::endl;
    size_t n = ctx->lAndExp().size();  // n 为 LAndExp 的个数（LOrExp 是多个 LAndExp 用 '||' 连接而成）

    llvm::Function* func = builder.GetInsertBlock()->getParent();

    for (size_t i = 0; i < n; ++i) {
        std::cout << "-----entering genLOrExp for loop-----"  << std::endl;
        HelloParser::LAndExpContext* land = ctx->lAndExp(i);

        // debug:lor_next空块
        // 只有不是最后一个时才创建 lor_next
        llvm::BasicBlock* nextBB = nullptr;
        if (i != n - 1) {
            nextBB = llvm::BasicBlock::Create(context, "lor_next", func);
            std::cout << "----create a lor_next----" << std::endl;
        }

        genLAndExp(land, trueBB, (i == n - 1 ? falseBB : nextBB));

        if (i != n - 1) {
            builder.SetInsertPoint(nextBB);
        }
    }
}


std::any Analysis::visitEqExp(HelloParser::EqExpContext *ctx) {
    llvm::Value* lhs = std::any_cast<llvm::Value*>(visit(ctx->relExp(0)));
    for (size_t i = 1; i < ctx->relExp().size(); ++i) {
        llvm::Value* rhs = std::any_cast<llvm::Value*>(visit(ctx->relExp(i)));
        llvm::errs() << "lhs type: ";
        lhs->getType()->print(llvm::errs());
        llvm::errs() << "\n";
        llvm::errs() << "rhs type: ";
        rhs->getType()->print(llvm::errs());
        llvm::errs() << "\n";
        
        if (ctx->Equal(i - 1)) {
            lhs = builder.CreateICmpEQ(lhs, rhs, "eq_tmp");
            

            std::cout <<"-------------test 29.cact ----------------"<<std::endl;
        } else if (ctx->NotEqual(i - 1)) {
            lhs = builder.CreateICmpNE(lhs, rhs, "ne_tmp");
        }
    }

    return lhs;
}


std::any Analysis::visitRelExp(HelloParser::RelExpContext *ctx) {
    llvm::Value* lhs = std::any_cast<llvm::Value*>(visit(ctx->addExp(0)));

    for (size_t i = 1; i < ctx->addExp().size(); ++i) {
        llvm::Value* rhs = std::any_cast<llvm::Value*>(visit(ctx->addExp(i)));

        llvm::Type* lhsType = lhs->getType();
        llvm::Type* rhsType = rhs->getType();

        // if(lhsType != rhsType){
        //     std::cout<<"[Error] rel Exp lhs and rhs type does not match"<<std::endl;
        //     exit(1);
        // }
        // 执行比较
        if (lhsType->isFloatTy()) {
            if (ctx->Less(i - 1)) {
                lhs = builder.CreateFCmpOLT(lhs, rhs, "flt_tmp");
            } else if (ctx->Greater(i - 1)) {
                lhs = builder.CreateFCmpOGT(lhs, rhs, "fgt_tmp");
            } else if (ctx->LessEqual(i - 1)) {
                lhs = builder.CreateFCmpOLE(lhs, rhs, "fle_tmp");
            } else if (ctx->GreaterEqual(i - 1)) {
                lhs = builder.CreateFCmpOGE(lhs, rhs, "fge_tmp");
            }
        } else if (lhsType->isIntegerTy(32)) {
            if (ctx->Less(i - 1)) {
                lhs = builder.CreateICmpSLT(lhs, rhs, "ilt_tmp");
            } else if (ctx->Greater(i - 1)) {
                lhs = builder.CreateICmpSGT(lhs, rhs, "igt_tmp");
            } else if (ctx->LessEqual(i - 1)) {
                lhs = builder.CreateICmpSLE(lhs, rhs, "ile_tmp");
            } else if (ctx->GreaterEqual(i - 1)) {
                lhs = builder.CreateICmpSGE(lhs, rhs, "ige_tmp");
            }
        } 
        // else {
        //     std::cerr << "[Error] RelExp 仅支持 i32 和 float 类型比较，目前 lhs 类型为：";
        //     lhsType->print(llvm::errs());
        //     std::cerr << std::endl;
        //     exit(1);
        // }
    }

    return lhs;
}


// 声明CACT内置函数
// 初始化 CACT 内置函数，在 LLVM 模块中声明它们，便于后续生成调用指令
void Analysis::initBuiltins() {
    // 获取 LLVM 中的基本类型对象，用于构建函数签名

    // 定义int、float、char、void类型
    // int 类型是 i32，对应 int32_t
    llvm::Type* intType = llvm::Type::getInt32Ty(context);
    // float 类型是 32 位 IEEE 浮点数
    llvm::Type* floatType = llvm::Type::getFloatTy(context);
    // char 类型用 i8 表示（LLVM 没有专门的 char 类型）
    llvm::Type* charType = llvm::Type::getInt8Ty(context);
    // void 类型用于无返回值函数
    llvm::Type* voidType = llvm::Type::getVoidTy(context);

    // void print_int(int) 
    // 定义printIntType函数类型（返回值void，参数int）
    llvm::FunctionType* printIntType = llvm::FunctionType::get(voidType, {intType}, false);
    // 创建函数对象print_int，并将其加入LLVM模块中
    // llvm::Function::ExternalLinkage：设为外部链接，实际实现由运行时库提供
    llvm::Function* printIntFunc = llvm::Function::Create(printIntType, llvm::Function::ExternalLinkage, "print_int", module);
    // 加入函数表，便于之后通过名字引用
    functionTable["print_int"] = printIntFunc;

    // void print_float(float)
    llvm::FunctionType* printFloatType = llvm::FunctionType::get(voidType, {floatType}, false);
    llvm::Function* printFloatFunc = llvm::Function::Create(printFloatType, llvm::Function::ExternalLinkage, "print_float", module);
    functionTable["print_float"] = printFloatFunc;

    llvm::FunctionType* printCharType = llvm::FunctionType::get(voidType, {charType}, false);
    llvm::Function* printCharFunc = llvm::Function::Create(printCharType, llvm::Function::ExternalLinkage, "print_char", module);
    functionTable["print_char"] = printCharFunc;

    llvm::FunctionType* getIntType = llvm::FunctionType::get(intType, {}, false);// 无参数，返回 int
    llvm::Function* getIntFunc = llvm::Function::Create(getIntType, llvm::Function::ExternalLinkage, "get_int", module);
    functionTable["get_int"] = getIntFunc;

    llvm::FunctionType* getFloatType = llvm::FunctionType::get(floatType, {}, false);
    llvm::Function* getFloatFunc = llvm::Function::Create(getFloatType, llvm::Function::ExternalLinkage, "get_float", module);
    functionTable["get_float"] = getFloatFunc;

    llvm::FunctionType* getCharType = llvm::FunctionType::get(charType, {}, false);
    llvm::Function* getCharFunc = llvm::Function::Create(getCharType, llvm::Function::ExternalLinkage, "get_char", module);
    functionTable["get_char"] = getCharFunc;
}
