#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <optional>
#include <llvm/IR/Value.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/GlobalVariable.h>  // 引入LLVM的全局变量定义头文件
#include <llvm/IR/Function.h>  // 引入LLVM的函数定义头文件
#include <llvm/IR/BasicBlock.h>  // 引入LLVM的基本块定义头文件
#include <llvm/IR/Constant.h>  // 引入LLVM的常量定义头文件

struct Symbol {
    std::string name;
    llvm::Type* llvmType = nullptr;
    llvm::Value* irValue = nullptr;
    bool isArray = false;
    int arraySize = 0;
    bool isConst = false;
    std::vector<int> dimensions;
    bool isArrayinFunc = false;

    Symbol() = default;  // Default constructor
    
    //Symbol(const std::string& name, llvm::Type* type, llvm::Value* value = nullptr, bool isConst = false)
    // : name(name), llvmType(type), irValue(value), isConst(isConst) {}
    //Symbol(const std::string& name, llvm::Type* type, llvm::Value* value, bool isConst, const std::vector<int>& dimensions = {},bool isArrayinfunc)
    //    : name(name), llvmType(type), irValue(value), isConst(isConst), dimensions(dimensions),isArrayinFunc(isArrayinFunc) {}
    Symbol(const std::string& name,
        llvm::Type* type,
        llvm::Value* value,
        bool isConst,
        const std::vector<int>& dimensions = {},
        bool isArrayinfunc = false)
     : name(name),
       llvmType(type),
       irValue(value),
       isConst(isConst),
       dimensions(dimensions),
       isArrayinFunc(isArrayinfunc) {}
 
};


class SymbolTable {
public:
    SymbolTable() {
        enterScope();  // 默认进入全局作用域
    }

    void enterScope() {
        scopes.emplace_back();
    }

    void exitScope() {
        if (!scopes.empty()) {
            scopes.pop_back();
        }
    }
    size_t getCurrentScopeLevel() const {
        return scopes.size() - 1;
    }
/*
    void insert(const std::string& name, llvm::Type* type, llvm::Value* value = nullptr, bool isConst = false) {
        if (scopes.empty()) return;

        auto& current = scopes.back();
        if (current.count(name)) {
            std::cerr << "[Error]: 重复定义符号: " << name << std::endl;
            exit(1);
        }
        // 将 isConst 参数传递给 Symbol 构造函数
        Symbol symbol(name, type, value, isConst);
        current[name] = symbol;
    }
*/

    void insert(const std::string& name, llvm::Type* type, llvm::Value* value = nullptr, bool isConst = false,bool isArrayinFunc =false,std::vector<int> dims = {}) {
        if (scopes.empty()) return;

        auto& current = scopes.back();
        if (current.count(name)) {
            std::cerr << "[Error]: 重复定义符号: " << name << std::endl;
            exit(1);
        }

        // 自动提取数组维度信息
        std::vector<int> dimensions;
        if(isArrayinFunc){
            dimensions = dims;
        }else{
            // 检查类型是否为数组类型
            if (auto* arrType = llvm::dyn_cast<llvm::ArrayType>(type)) {
                // llvm获取数组的维度
                int numElements = arrType->getNumElements();
                dimensions.push_back(numElements);

                // 递归处理多维数组
                llvm::Type* elementType = arrType->getElementType();
                while (auto* nestedArrType = llvm::dyn_cast<llvm::ArrayType>(elementType)) {
                    numElements = nestedArrType->getNumElements();
                    dimensions.push_back(numElements);
                    elementType = nestedArrType->getElementType();
                }
            }
        }
        Symbol symbol(name, type, value, isConst, dimensions,isArrayinFunc);
        current[name] = symbol;
    }


    std::optional<Symbol> lookup(const std::string& name) const {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                return found->second;
            }
        }
        return std::nullopt;
    }
    std::optional<Symbol> lookupInCurrentScope(const std::string& name) const {
        // 获取当前作用域
        auto& currentScope = scopes.back();
        
        // 在当前作用域中查找符号
        auto found = currentScope.find(name);
        if (found != currentScope.end()) {
            return found->second; // 找到符号，返回该符号
        }
        
        return std::nullopt; // 如果当前作用域没有找到符号，返回空值
    }
    
    void print() const {
        std::cerr << "===== 符号表栈 =====\n";
        for (int i = scopes.size() - 1; i >= 0; --i) {
            std::cerr << "作用域 " << i << ":\n";
            for (const auto& [key, sym] : scopes[i]) {
                std::cerr << "  " << key << " -> LLVM类型: ";
                if (sym.llvmType) sym.llvmType->print(llvm::errs(), true);
                else std::cerr << "nullptr";
                if (sym.irValue) {
                    std::cerr << ", IR值: " << sym.irValue << std::endl;
                    auto name = lookup(key);
                    if (!name.has_value()) {
                        std::cerr << "Undefined variable: " << key << std::endl;
                    }
                    std::cout << name.has_value() << std::endl; 
                }
                std::cerr << "\n";
            }
        }
    }

private:
    std::vector<std::unordered_map<std::string, Symbol>> scopes;
};

#endif // SYMBOL_TABLE_H
