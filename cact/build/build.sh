#实验1的命令集合
#运行之后运行./compiler ../test/samples_lex_and_syntax/00_true_main.cact即可
#dxl 2025/3/28

#!/bin/bash

# 设置错误处理，遇到错误时终止执行
set -e

# 进入语法文件目录
echo "切换到 grammar 目录..."
cd ../grammar/

# 运行 ANTLR 生成 C++ 代码
echo "运行 ANTLR 生成 C++ 代码..."
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp -no-listener -visitor ./Hello.g4

# 切换到 build 目录
echo "切换到 build 目录..."
cd ../build/

# 运行 CMake 配置项目
echo "运行 CMake..."
cmake ..

# 编译项目
echo "开始编译..."
make -j$(nproc)

echo "编译完成！"
