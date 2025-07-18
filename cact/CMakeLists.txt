cmake_minimum_required(VERSION 3.5)
project(Compiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# 1. 包含目录配置（保留原有+新增）
include_directories(
    deps/antlr4-runtime/
    grammar
    src
    ${CMAKE_CURRENT_SOURCE_DIR}/include  # 新增：用于IRGenerator.h等头文件
    ${LLVM_INCLUDE_DIRS}                # 新增：LLVM头文件
)

# 2. 查找LLVM（新增）
# 设置LLVM路径（使用绝对路径，注意去掉~）
set(LLVM_DIR "/root/llvm-install/clang+llvm-11.1.0-x86_64-linux-gnu-ubuntu-16.04/lib/cmake/llvm")

# 查找LLVM包
find_package(LLVM REQUIRED CONFIG)
message(STATUS "LLVM_DIR = ${LLVM_DIR}")
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# 3. 源文件收集（保留）
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "grammar/*.cpp")
file(GLOB_RECURSE ANTLR_LIB_FILES "deps/antlr4-runtime/*.cpp")

# 4. 编译选项（保留）
add_definitions(-w -g)

# 5. 构建ANTLR静态库（保留）
add_library(antlr STATIC ${ANTLR_LIB_FILES})

# 6. 构建可执行文件（保留）
add_executable(compiler ${SOURCE_FILES})

# 7. 获取LLVM组件（新增）
llvm_map_components_to_libnames(llvm_libs
    core      # 必需
    irreader  # 用于IR生成
    support   # 基础支持
)

# 8. 链接库配置（保留原有+新增）
find_package(Threads REQUIRED)
target_link_libraries(compiler
    antlr             # 保留：ANTLR库
    Threads::Threads  # 保留：线程库
    ${llvm_libs}      # 新增：LLVM库
    # 可选：Linux系统可能需要
    ${CMAKE_DL_LIBS}  # 动态加载库
    z                 # 压缩库
)
