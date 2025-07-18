#pragma once

#include "HelloBaseVisitor.h"
#include "HelloParser.h"                // 包含 HelloParser，提供各 Context 的定义
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <any>
#include <vector>
#include <unordered_map>
#include "SymbolTable.h"  // 引入符号表头文件
#include <llvm/IR/Type.h>

class Analysis : public HelloBaseVisitor {
private:
    llvm::LLVMContext& context;  // 用于 LLVM 的上下文
    llvm::Module& module;        // LLVM 模块
    llvm::IRBuilder<>& builder;  // LLVM IR 构建器，用于生成 IR
    SymbolTable symbolTable;     // 符号表实例，用于存储和管理符号
    std::unordered_map<std::string, llvm::Function*> functionTable;
    llvm::Type* currentFunctionReturnType = nullptr; 
    
    // 用于while语句中的入栈出栈
    std::stack<llvm::BasicBlock*> condBBStack;
    std::stack<llvm::BasicBlock*> afterBBStack;

    // 获取基本类型对应的 LLVM 类型
    llvm::Type* getTypeFromBType(HelloParser::BTypeContext* ctx);

    // 处理常量初始化值
    llvm::Value* processConstInitVal(HelloParser::ConstInitValContext* ctx, llvm::Type* type);

    // 处理数组初始化，支持多维数组初始化
    void initArray_static(llvm::Value* arrayPtr,
                        llvm::Type* elemType,
                        HelloParser::ConstInitValContext* ctx,
                        const std::vector<int>& dims,
                        int currentDim = 0, std::vector<int>& indices = *(new std::vector<int>()));  // 保持默认值

    // ConstInitValArrayContext版本
    void initArray_static_new(llvm::Value* arrayPtr, 
                            llvm::Type* elemType,
                            HelloParser::ConstInitValArrayContext* ctx,
                            const std::vector<int>& dims, 
                            int currentDim);
                            
    std::string getLLVMTypeStr(llvm::Type* type) ;  
    // 处理变量声明
    void handleVarDecl(HelloParser::VardeclContext* ctx);

    // 处理常量声明
    void handleConstDecl(HelloParser::ConstdeclContext* ctx);

public:
    // 构造函数，传入 LLVM 上下文、模块和 IR 构建器

    Analysis(llvm::LLVMContext& ctx,
             llvm::Module& mod,
             llvm::IRBuilder<>& bld)
        : context(ctx), module(mod), builder(bld) {}
    llvm::Type* getReturnType(HelloParser::FuncDefContext* funcDef) ;

    // 访问语法树中的 CompilationUnit 节点
    std::any visitCompUnit(HelloParser::CompUnitContext* ctx) override;

    // 访问常量声明节点
    std::any visitConstDecl(HelloParser::ConstdeclContext* ctx) ;

    // 访问变量声明节点
    std::any visitVarDecl(HelloParser::VardeclContext* ctx) ;
    std::any visitFuncDef(HelloParser::FuncDefContext* ctx) ;
    std::any visitBlock(HelloParser::BlockContext *ctx) ;
    std::any visitStmt(HelloParser::StmtContext *ctx);
    llvm::Value* getValueForVar(HelloParser::ExpContext* ctx) ;
    std::any visitExp(HelloParser::ExpContext* ctx) ;
    std::any visitAddExp(HelloParser::AddExpContext* ctx);
    std::any visitMulExp(HelloParser::MulExpContext* ctx);
    std::any visitUnaryExp(HelloParser::UnaryExpContext* ctx);
    std::any visitPrimaryExp(HelloParser::PrimaryExpContext* ctx);
    std::any visitConstExp(HelloParser::ConstExpContext *ctx) ;
    std::any visitRelExp(HelloParser::RelExpContext *ctx) ;
    std::any visitEqExp(HelloParser::EqExpContext *ctx);
    std::any visitCond(HelloParser::CondContext *ctx) ;
    void genCond(HelloParser::CondContext* ctx, llvm::BasicBlock* trueBB, llvm::BasicBlock* falseBB); // 有控制参数的visitCond版本
    std::any visitLOrExp(HelloParser::LOrExpContext *ctx) ;
    std::any visitLAndExp(HelloParser::LAndExpContext *ctx);
    void genLAndExp(HelloParser::LAndExpContext* ctx, llvm::BasicBlock* trueBB, llvm::BasicBlock* falseBB); // 短路与（&&）的控制流生成器
    std::any visitNumber(HelloParser::NumberContext *ctx) ;
    void genLOrExp(HelloParser::LOrExpContext* ctx, llvm::BasicBlock* trueBB, llvm::BasicBlock* falseBB); // 短路或（||）的控制流生成器
    llvm::Constant* convertFlatToMultiDim(
        const std::vector<llvm::Constant*>& flatConstants,
        const std::vector<int>& dims,
        llvm::Type* elemType
    ) ;
    //void flattenConstInitVal(HelloParser::ConstInitValContext* ctx, llvm::Type* type, std::vector<llvm::Constant*>& result);
    llvm::Constant* buildNestedConstantArray(llvm::Type* type, std::vector<llvm::Constant*>::iterator& it);
    std::any visitLVal(HelloParser::LValContext* lValCtx) ;
    std::string extractVarNameFromExp(HelloParser::ExpContext* ctx);
    llvm::Value* getLValuePtr(HelloParser::ExpContext* ctx) ;
    
    // 不需要声明 visitConstInitVal，除非你要对常量的初始化进行自定义处理。
    void initBuiltins();// 用于处理CACT内置函数
    llvm::Constant* getZeroConstant(llvm::Type* elemType, llvm::LLVMContext& context);
    void flattenConstInitVal(
        HelloParser::ConstInitValContext* ctx,
        llvm::Type* elemType,                     // 数组元素类型（如int/float）
        const std::vector<int>& dims,        // 当前处理维度的剩余尺寸
        std::vector<llvm::Constant*>& result
    );
    void flattenConstInitValLinear(
        HelloParser::ConstInitValContext* ctx,
        llvm::Type* elemType,
        const std::vector<int>& dims,
        int dimIndex,
        std::vector<llvm::Constant*>& result
    );
    void flattenConstInitValArrayLinear(
        HelloParser::ConstInitValArrayContext* ctx,
        llvm::Type* elemType,
        const std::vector<int>& dims,
        int dimIndex,
        std::vector<llvm::Constant*>& result
    );
    void padZeros(
        llvm::Type* elemType,
        const std::vector<int>& dims,
        std::vector<llvm::Constant*>& result
    );

    llvm::Constant* buildNestedArrayConstant(
        llvm::Type* elemType,
        const std::vector<int>& dims,
        std::vector<llvm::Constant*>& flatVals,
        int& index,
        llvm::LLVMContext& context
    );
    std::pair<llvm::Type*, std::vector<int>> getParamType(HelloParser::FuncFParamContext* param);

    //llvm::Value* castToBool(llvm::Value* val); // 用于genLAndExp()的类型检查

    bool stmtAlwaysReturns(HelloParser::StmtContext* ctx);
    bool blockAlwaysReturns(HelloParser::BlockContext* blk) ;
    void initConstInitValWithValues(
        HelloParser::ConstInitValContext* ctx,
        llvm::AllocaInst* allocaPtr,                // 目标数组在栈上的地址
        llvm::Type* elemType,                 // 数组元素类型 (e.g. i32)
        const std::vector<int>& dims,         // 各维度的长度
        int dimIndex,                         // 当前递归正在处理第 dimIndex 维
        std::vector<int>& indicesSoFar        // 用于记录当前定位的多维索引
    );
    void initConstInitValArrayWithValues(
        HelloParser::ConstInitValArrayContext* ctx,
        llvm::AllocaInst* allocaPtr,
        llvm::Type* elemType,
        const std::vector<int>& dims,
        int dimIndex,
        std::vector<int>& indicesSoFar
    ) ;
    llvm::Value* parseFloatConstant(const std::string& text);
    llvm::Value* parseIntConstant(const std::string& text);
    
};
