# Pascal2C 编译器

这是一个将Pascal语言代码转换为C语言代码的编译器项目。该项目使用ANTLR4作为解析器生成工具，实现了Pascal到C的语法转换。

## 项目结构

```
Pascal2C/
├── antlr/           # ANTLR4生成的解析器代码
├── cmake/           # CMake配置文件
├── include/         # 头文件目录
│   ├── PascalToCTranslator.h  # 主要的转换器类头文件
│   ├── SymbolTable.h          # 符号表相关定义
│   ├── TypeConverter.h        # 类型转换工具
│   └── TranslatorUtils.h      # 转换工具函数
│	└── ErrorDealer.h		   # 错误处理功能函数
├── src/             # 源代码目录
│   ├── main.cpp              # 程序入口
│   ├── PascalToCTranslator.cpp # 转换器实现
│   ├── SymbolTable.cpp       # 符号表实现
│   ├── TypeConverter.cpp     # 类型转换实现
│   └── TranslatorUtils.cpp   # 工具函数实现
└── CMakeLists.txt   # CMake构建配置文件
```

## 主要组件说明

### 1. PascalToCTranslator
- 核心转换器类，负责将Pascal代码转换为C代码
- 实现了语法树的遍历和转换逻辑
- 处理变量声明、函数定义、控制结构等

### 2. SymbolTable
- 符号表实现，用于管理变量和函数的作用域
- 支持变量类型检查和作用域管理
- 处理变量声明和引用

### 3. TypeConverter
- 处理Pascal和C语言之间的类型转换
- 支持基本数据类型和复杂类型的转换
- 确保类型安全

### 4. TranslatorUtils
- 提供通用的转换工具函数
- 处理字符串操作和代码格式化
- 提供辅助功能支持

### 5. ErrorDealer

+ 提供错误收集器结构体
+ 提供对Pascal的语法错误在转换为C语言的错误处理

## 项目配置

### 构建要求

- CMake 3.20或更高版本
- C++11兼容的编译器
- ANTLR4运行时库

### 依赖项
- ANTLR4 C++运行时库
- C++标准库

### 构建步骤
1. 创建构建目录：
```bash
mkdir build
cd build
```

2. 配置项目：
```bash
cmake ..
```

3. 编译项目：
```bash
cmake --build .
```

4. 编译完成后，可执行文件将被复制到 `../bin` 目录

## 使用方法

1. 准备Pascal源代码文件（.pascc扩展名）
2. 运行转换器：
```bash
./pascc -i input.pascc
```

## 注意事项

- 确保系统已正确安装ANTLR4运行时库
- 转换过程中会进行语法检查，确保输入的Pascal代码符合语法规范
- 转换后的C代码可能需要手动优化

## 开发说明

- 项目使用CMake作为构建系统
- 代码遵循C++11标准
- 使用ANTLR4进行语法解析
- 支持基本的Pascal语言特性转换
