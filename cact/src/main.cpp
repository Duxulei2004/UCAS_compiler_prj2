#include <iostream>
#include <fstream>
#include <any>
#include "antlr4-runtime.h"
#include "HelloLexer.h"
#include "HelloParser.h"
#include "../include/Analysis.h"
#include <vector>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "tree/ErrorNode.h"

using namespace antlr4;
class AnalysisTree : public antlr4::tree::ParseTreeListener {
    public:
        virtual void enterEveryRule(ParserRuleContext* ctx) override {}
        virtual void visitTerminal(tree::TerminalNode* node) override {}
        virtual void visitErrorNode(tree::ErrorNode* node) override {
            std::cout << "1" << std::endl;
            std::ofstream outfile("output.txt", std::ios::app); 
            if (outfile.is_open()) {
                outfile << "1" << std::endl;
                outfile.close();
            } else {
                std::cerr << "无法打开output.txt文件" << std::endl;
            }
            exit(1);}
        virtual void exitEveryRule(ParserRuleContext* ctx) override {}
    };
    
int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./compiler <input_file>" << std::endl;
        return -1;
    }

    // 打开输入文件


    std::ifstream stream;
    stream.open(argv[1]);
    ANTLRInputStream   input(stream);
    HelloLexer         lexer(&input);
    CommonTokenStream  tokens(&lexer);
    HelloParser        parser(&tokens);
    tree::ParseTree *tree = parser.compUnit();
    std::cout << "-------" << std::endl;
    std::cout << tree->toStringTree(&parser) << std::endl;
    AnalysisTree listener;
    tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    
    std::cout << "0" << std::endl;
    try {
        llvm::LLVMContext context;
        llvm::Module module("main", context);
        llvm::IRBuilder<> builder(context);
        // 进行语法分析并生成IR
         // 显示尝试将 Any 类型转换为字符串
         Analysis visitor(context, module, builder);

        antlrcpp::Any result = visitor.visit(tree); // 调用访问器生成IR  //显式声明类型为 antlrcpp::Any
       
        try {
          std::string llvmIR = std::any_cast<std::string>(result);
          std::cout << "IR 结果类型：" << typeid(result).name() << std::endl;  // 输出类型信息
          std::cout << "IR 结果内容：" << llvmIR << std::endl;
      } catch (const std::bad_any_cast& e) {
          std::cerr << "错误: 无法将结果转换为字符串类型" << std::endl;
      }

        // 使用 std::any_cast 进行类型转换
        try {
            std::string llvmIR = std::any_cast<std::string>(result);

            // 写入IR文件
            std::ofstream irFile("output.ll");
            irFile << llvmIR;

            // 写入成功标志
            std::ofstream("output.txt", std::ios::app) << "0\n";
            return 0;

        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("生成的IR不是字符串类型");
        }

    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        std::ofstream("output.txt", std::ios::app) << "1\n";
        return -1;
    }
}
