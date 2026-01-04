cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(HighPrecision VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 创建库（静态库）
add_library(high-precision STATIC
    high-precision.h
    high-precision.cpp
)

# 设置库的包含目录
target_include_directories(high-precision PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 创建示例可执行文件
add_executable(example
    example/example.cpp
)

# 链接库到示例
target_link_libraries(example PRIVATE high-precision)

# 安装规则
install(TARGETS high-precision
    ARCHIVE DESTINATION high-precision/lib
    LIBRARY DESTINATION high-precision/lib
)

install(FILES high-precision.h
    DESTINATION include
)

# 设置输出目录
set_target_properties(high-precision PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/high-precision/lib"
)

set_target_properties(example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 拷贝包含文件到构建目录
configure_file(high-precision.h
    ${CMAKE_BINARY_DIR}/high-precision/include/high-precision.h
    COPYONLY
)

# 打印配置信息
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
