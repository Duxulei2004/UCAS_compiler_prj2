#!/bin/bash

# 定义 LLVM 工具链路径
#LLVM_BIN="/home/compiler10/llvm-install/clang+llvm-11.1.0-x86_64-linux-gnu-ubuntu-16.04/bin"
LLVM_BIN="/root/llvm-install/clang+llvm-11.1.0-x86_64-linux-gnu-ubuntu-16.04/bin"
# 步骤 1: 将 LLVM IR 编译为目标文件
echo "编译 output.ll 为 output.o..."
"$LLVM_BIN"/clang -c output.ll -o output.o

# 步骤 2: 链接目标文件和运行时库，生成可执行文件
echo "链接 output.o 和 libcact_rt.a..."
"$LLVM_BIN"/clang output.o -L. -lcact_rt -o program

# 步骤 3: 运行程序并显示返回值
echo "运行程序..."
./program
EXIT_CODE=$?
echo "程序退出码: $EXIT_CODE"
