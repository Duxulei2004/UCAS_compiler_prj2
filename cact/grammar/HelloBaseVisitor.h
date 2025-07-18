
    #include <vector>


// Generated from ./Hello.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "HelloVisitor.h"


/**
 * This class provides an empty implementation of HelloVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  HelloBaseVisitor : public HelloVisitor {
public:

  virtual std::any visitCompUnit(HelloParser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(HelloParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstdecl(HelloParser::ConstdeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBType(HelloParser::BTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDef(HelloParser::ConstDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstInitVal(HelloParser::ConstInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVardecl(HelloParser::VardeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDefArray(HelloParser::VarDefArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstInitValArray(HelloParser::ConstInitValArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(HelloParser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(HelloParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncType(HelloParser::FuncTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParams(HelloParser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParam(HelloParser::FuncFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(HelloParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItem(HelloParser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(HelloParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExp(HelloParser::ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExp(HelloParser::ConstExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCond(HelloParser::CondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLVal(HelloParser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(HelloParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncRParams(HelloParser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExp(HelloParser::PrimaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExp(HelloParser::UnaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExp(HelloParser::MulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExp(HelloParser::AddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelExp(HelloParser::RelExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExp(HelloParser::EqExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLAndExp(HelloParser::LAndExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLOrExp(HelloParser::LOrExpContext *ctx) override {
    return visitChildren(ctx);
  }


};

