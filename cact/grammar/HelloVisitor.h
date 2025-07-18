
    #include <vector>


// Generated from ./Hello.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "HelloParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by HelloParser.
 */
class  HelloVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by HelloParser.
   */
    virtual std::any visitCompUnit(HelloParser::CompUnitContext *context) = 0;

    virtual std::any visitDecl(HelloParser::DeclContext *context) = 0;

    virtual std::any visitConstdecl(HelloParser::ConstdeclContext *context) = 0;

    virtual std::any visitBType(HelloParser::BTypeContext *context) = 0;

    virtual std::any visitConstDef(HelloParser::ConstDefContext *context) = 0;

    virtual std::any visitConstInitVal(HelloParser::ConstInitValContext *context) = 0;

    virtual std::any visitVardecl(HelloParser::VardeclContext *context) = 0;

    virtual std::any visitVarDefArray(HelloParser::VarDefArrayContext *context) = 0;

    virtual std::any visitConstInitValArray(HelloParser::ConstInitValArrayContext *context) = 0;

    virtual std::any visitVarDef(HelloParser::VarDefContext *context) = 0;

    virtual std::any visitFuncDef(HelloParser::FuncDefContext *context) = 0;

    virtual std::any visitFuncType(HelloParser::FuncTypeContext *context) = 0;

    virtual std::any visitFuncFParams(HelloParser::FuncFParamsContext *context) = 0;

    virtual std::any visitFuncFParam(HelloParser::FuncFParamContext *context) = 0;

    virtual std::any visitBlock(HelloParser::BlockContext *context) = 0;

    virtual std::any visitBlockItem(HelloParser::BlockItemContext *context) = 0;

    virtual std::any visitStmt(HelloParser::StmtContext *context) = 0;

    virtual std::any visitExp(HelloParser::ExpContext *context) = 0;

    virtual std::any visitConstExp(HelloParser::ConstExpContext *context) = 0;

    virtual std::any visitCond(HelloParser::CondContext *context) = 0;

    virtual std::any visitLVal(HelloParser::LValContext *context) = 0;

    virtual std::any visitNumber(HelloParser::NumberContext *context) = 0;

    virtual std::any visitFuncRParams(HelloParser::FuncRParamsContext *context) = 0;

    virtual std::any visitPrimaryExp(HelloParser::PrimaryExpContext *context) = 0;

    virtual std::any visitUnaryExp(HelloParser::UnaryExpContext *context) = 0;

    virtual std::any visitMulExp(HelloParser::MulExpContext *context) = 0;

    virtual std::any visitAddExp(HelloParser::AddExpContext *context) = 0;

    virtual std::any visitRelExp(HelloParser::RelExpContext *context) = 0;

    virtual std::any visitEqExp(HelloParser::EqExpContext *context) = 0;

    virtual std::any visitLAndExp(HelloParser::LAndExpContext *context) = 0;

    virtual std::any visitLOrExp(HelloParser::LOrExpContext *context) = 0;


};

