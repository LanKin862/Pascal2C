# Pascal2C 技术文档

本文档详细描述Pascal2C编译器的代码结构、功能实现和工作流程。

## 1. 核心文件及功能

### **转换规则说明：**

**Pascal-S** **到** **C** **的主要转换规则**

1. **程序结构:**

   - Pascal-S 的 program 声明映射到 C 的 main 函数及其包含头文件
   - Pascal-S 的程序参数列表转换为 C 的命令行参数

2. **数据类型:** 

   - integer -> int
   - real -> float
   - boolean -> int (0表示false, 非0表示true)
   - char -> char
   - array[m..n] of T -> T array[n-m+1] 并调整索引方式

3. **控制结构:** 

   - if-then-else -> if () {} else {}
   - for 循环 -> for 循环 (注意索引处理)
   - while 循环 -> while 循环

4. **过程和函数:** 

   - Pascal-S 过程 -> C 函数 (返回类型为 void)
   - Pascal-S 函数 -> C 函数 (带返回类型)
   - VAR 参数 -> 指针参数

5. **输入输出:** 

   - read -> scanf
    - write -> printf

6. **特殊处理:** 

   - Pascal-S 的作用域规则与 C 不同，需要特别处理嵌套子程序
   - C 不支持嵌套函数定义，需要将嵌套函数提升到全局作用域并传递上下文
   - Pascal-S 的布尔表达式需要转换为 C 的整数表达式

### 1.1 PascalToCTranslator 类 (主要转换器)

**文件**: `include/PascalToCTranslator.h`, `src/PascalToCTranslator.cpp`

**功能**:

- 实现Pascal源代码到C源代码的转换
- 解析Pascal语法树，生成等效的C代码
- 管理符号表和类型转换
- 处理Pascal特有的语言构造

**主要接口**:

```cpp
// 主要公共接口
std::string translate(const std::string &inputFile);  // 转换Pascal文件为C代码
```

**核心方法**:

- `visitProgram`: 处理整个程序结构，添加必要的C头文件和辅助函数
- `visitProgramBody`: 处理程序主体，包括常量声明、变量声明、子程序声明和复合语句
- `visitCompoundStatement`: 处理复合语句(BEGIN...END块)
- `visitIfStatement`/`visitForStatement`/`visitWhileStatement`: 处理条件和循环结构
- `visitReadStatement`/`visitWriteStatement`: 处理Pascal输入/输出语句转换为C对应函数
- `visitExpression`/`visitTerm`/`visitFactor`: 处理表达式、项和因子的解析转换

**工作原理**:

```
┌───────────────┐      ┌───────────────┐      ┌───────────────┐
│ Pascal源代码  │─────>│  ANTLR4解析器  │─────>│   语法树(AST)  │
└───────────────┘      └───────────────┘      └───────┬───────┘
                                                      │
                                                      ▼
                                              ┌───────────────┐
                                              │  访问者模式解析 │
                                              └───────┬───────┘
                                                      │
                                                      ▼
                                              ┌───────────────┐
                                              │    生成C代码   │
                                              └───────────────┘
```

**实现细节**:

1. 使用ANTLR4生成的解析器处理Pascal语法
2. 对语法树采用访问者模式逐节点转换生成C代码
3. 维护符号表来跟踪变量、常量和函数
4. 管理作用域层级以正确处理嵌套结构
5. 生成类型匹配的C代码并处理特殊情况

### 1.2 SymbolTable 类 (符号管理)

**文件**: `include/SymbolTable.h`, `src/SymbolTable.cpp`

**功能**:

- 管理变量、常量和函数的符号表
- 跟踪符号作用域和类型信息
- 提供符号查找和添加功能

**主要接口**:

```cpp
// 作用域管理
void enterScope(const std::string& scopeName);
void exitScope();
bool isInGlobalScope() const;

// 符号管理
bool addSymbol(const SymbolEntry& symbol);
bool hasSymbol(const std::string& name) const;
bool hasSymbolInCurrentScope(const std::string& name) const;
SymbolEntry& getSymbol(const std::string& name);
```

**工作原理**:

- 使用作用域栈管理嵌套作用域
- 每个作用域包含名称和符号映射
- 符号查找从当前作用域向外(直到全局作用域)搜索

**实现细节**:

1. `ScopeEntry` 类存储单一作用域的符号
2. `SymbolTable` 维护 `ScopeEntry` 栈
3. 符号包括变量、常量、函数和过程，以及它们的类型信息
4. 支持引用参数和数组类型

### 1.3 TypeConverter 类 (类型转换)

**文件**: `include/TypeConverter.h`, `src/TypeConverter.cpp`

**功能**:

- 处理Pascal和C类型系统之间的转换
- 维护类型映射和转换规则
- 支持基本类型和数组类型转换

**主要接口**:

```cpp
std::string convertType(PascalType type) const;
std::string convertArrayType(PascalType elementType, const std::vector<ArrayBounds>& dimensions) const;
std::string convertOperator(const std::string& op) const;
std::string convertBooleanValue(const std::string& value) const;
```

**工作原理**:

- 使用类型映射表在Pascal类型和C类型之间转换
- 为数组类型生成特殊处理逻辑
- 转换Pascal特定的运算符和布尔值

**实现细节**:

1. Pascal布尔值 -> C 整数 (0/1)
2. Pascal运算符 -> C等效运算符 (例如 AND -> &&)
3. Pascal数组 -> C带维度的数组

### 1.4 TranslatorUtils 类 (工具函数)

**文件**: `include/TranslatorUtils.h`, `src/TranslatorUtils.cpp`

**功能**:

- 提供通用的转换工具函数
- 处理日志、错误和警告信息
- 字符串和标识符处理

**主要接口**:

```cpp
static void logError(const std::string& message);
static void logWarning(const std::string& message);
static void logInfo(const std::string& message);
static std::string toCIdentifier(const std::string& pascalIdentifier);
static std::string escapeString(const std::string& str);
static bool isValidIdentifier(const std::string& str);
```

**工作原理**:

- 提供纯工具函数，无状态
- 实现字符串和标识符转换规则
- 处理错误和异常报告

**实现细节**:

1. 将Pascal标识符(不区分大小写)转换为C标识符(区分大小写)
2. 检查C关键字冲突并添加前缀
3. 转义字符串中的特殊字符

### 1.5 Main函数 (程序入口)

**文件**: `src/main.cpp`

**功能**:

- 处理命令行参数
- 调用转换器
- 管理输入/输出文件操作

**工作流程**:

1. 解析命令行参数
2. 读取输入Pascal文件
3. 创建PascalToCTranslator实例
4. 调用translate方法执行转换
5. 将生成的C代码写入输出文件

**实现细节**:

- 支持 `-i` 参数指定输入文件
- 自动根据输入文件名生成输出文件名(.c后缀)
- 提供错误处理和用户反馈

## 2. 数据结构

### 2.1 符号表结构

**SymbolEntry** - 符号条目:

```cpp
struct SymbolEntry {
    std::string name;               // 符号名称
    SymbolType symbolType;          // 符号类型(变量/常量/函数/过程)
    PascalType dataType;            // 数据类型
    std::string value;              // 常量值
    bool isReference = false;       // 是否为引用参数
    PascalType arrayElementType;    // 数组元素类型
    std::vector<ArrayBounds> arrayDimensions; // 数组维度信息
};
```

**ScopeEntry** - 作用域条目:

```cpp
class ScopeEntry {
private:
    std::map<std::string, SymbolEntry> symbols;  // 符号表映射
    std::string scopeName;                       // 作用域名称
    std::vector<SymbolEntry> parameters;  		 // 判断是否为引用调用参数
};
```

**ArrayBounds** - 数组边界:

```cpp
struct ArrayBounds {
    int lowerBound;  // 下界
    int upperBound;  // 上界
};
```

**SymbolTable** - 管理符号和作用域:

```cpp
class SymbolTable {
private:
    std::vector<std::unique_ptr<ScopeEntry>> scopes;	// 管理所有符号和作用域
    int currentScopeIndex;								// 当前作用域索引
};
```



### 2.2. 类型系统

**PascalType** - Pascal类型枚举:

```cpp
enum class PascalType {
    INTEGER,
    REAL,
    BOOLEAN,
    CHAR,
    ARRAY,
    STRING
    // 其他类型...
};
```

**SymbolType** - 符号类型枚举:

```cpp
enum class SymbolType {
    VARIABLE,
    CONSTANT,
    FUNCTION,
    PROCEDURE,
    PARAMETER
};
```

## 3. 转换流程

### 3.1 整体转换流程

1. **初始化阶段**:
   - 创建转换器实例
   - 初始化符号表和类型转换器
   - 重置内部状态(缩进、作用域标志等)

2. **解析阶段**:
   - 使用ANTLR4设置输入流
   - 创建词法分析器和解析器
   - 执行语法解析生成抽象语法树(AST)

3. **转换阶段**:
   - 访问AST的程序节点开始转换
   - 生成标准C包含文件和辅助定义
   - 访问并转换每个程序部分:
     - 常量声明
     - 变量声明
     - 子程序声明
     - 主体语句
   - 管理作用域进入和退出
   - 为每种Pascal构造生成对应C代码

4. **完成阶段**:
   - 返回生成的C代码
   - 输出到文件

### 3.2 详细调用流程

程序启动调用流程:

```
main()
  ├── 解析命令行参数
  ├── readFileContents(inputFile)
  ├── PascalToCTranslator translator;
  ├── translator.translate(inputFile)
  │     ├── 设置ANTLR输入流
  │     ├── 创建解析器和词法分析器
  │     ├── 解析程序生成AST
  │     └── visitProgram(tree)
  │           ├── 生成标准头文件
  │           ├── 生成辅助函数定义
  │           └── visit(context->programStruct())
  │                 ├── visit(context->programHead())
  │                 └── visit(context->programBody())
  │                       ├── visit(context->constDeclarations())
  │                       ├── visit(context->varDeclarations())
  │                       ├── visit(context->subprogramDeclarations())
  │                       └── visit(context->compoundStatement())
  └── writeToFile(outputFile, cCode)
```

### 3.3 关键翻译示例

1. **Pascal `if` 语句转换为C `if` 语句**:

   ```pascal
   if condition then
     statement1
   else
     statement2
   ```

   转换为:

   ```c
   if (condition) {
     statement1;
   } else {
     statement2;
   }
   ```

2. **Pascal `for` 循环转换为C `for` 循环**:

   ```pascal
   for i := 1 to 10 do
     statement
   ```

   转换为:

   ```c
   for (i = 1; i <= 10; ++i) {
     statement;
   }
   ```

3. **Pascal过程调用转换为C函数调用**:

   ```pascal
   procedure test(var x: integer; y: real);
   ```

   转换为:

   ```c
   void test(int* x, float y);
   ```

4. **Pascal数组声明转换为C数组**:

   ```pascal
   var arr: array[1..10] of integer;
   ```

   转换为:

   ```c
   int arr[10];
   ```

5. **Pascal输入/输出转换为C函数**:

   ```pascal
   write('Value: ', x);
   ```

   转换为:

   ```c
   printf("Value: %d", x);
   ```

## 4. 符号表管理

符号表管理在转换过程中的作用:

1. **作用域管理**:
   - 进入新作用域: `symbolTable->enterScope(name)`
   - 退出当前作用域: `symbolTable->exitScope()`
   - 作用域层次结构追踪嵌套的子程序和程序块

2. **符号解析**:
   - 添加新符号: `symbolTable->addSymbol(entry)`
   - 查找符号: `symbolTable->hasSymbol(name)`
   - 获取符号信息: `symbolTable->getSymbol(name)`

3. **类型检查**:
   - 获取变量类型以生成正确的C代码
   - 确定函数返回类型
   - 检查数组访问的有效性

示例调用链:

```
visitVarDeclaration
  ├── 获取标识符列表: visitIdList
  ├── 获取类型信息: visitType
  ├── 为每个标识符生成C声明
  └── 将每个变量添加到符号表: symbolTable->addSymbol(entry)
```

## 5. 异常处理

**异常处理策略:**

1. **TranslatorException 类**:
   - 包含错误消息的自定义异常
   - 用于报告语法和语义错误

2. **错误报告**:
   - `TranslatorUtils::logError`: 报告严重错误
   - `TranslatorUtils::logWarning`: 报告警告但继续处理
   - `TranslatorUtils::logInfo`: 报告信息性消息

3. **异常捕获点**:
   - `translate()` 方法捕获所有异常
   - `main()` 函数捕获所有未处理异常

**转换后C语言错误处理：**

+ 当出现了在当前作用域中未定义的变量时，报错。在控制台输出错误位置。

## 6. 局限性和扩展点

当前实现的局限性:

1. 不支持复杂的Pascal类型(记录、集合、枚举)
2. 有限的标准函数库支持
3. 可能不完全处理所有Pascal语言特性

潜在扩展点:

1. 添加更多Pascal类型支持
2. 增强错误检测和报告功能
3. 添加调试信息和源映射
4. 支持更多的Pascal语言构造
5. 增加优化选项

## 7. 总结

Pascal2C是一个使用访问者模式进行源码转换的编译器，使用ANTLR4进行语法分析。主要组件包括:

1. **PascalToCTranslator**: 核心转换引擎，实现主要转换逻辑
2. **SymbolTable**: 管理符号和作用域
3. **TypeConverter**: 处理类型系统转换
4. **TranslatorUtils**: 提供辅助工具函数

程序处理流程为:

1. 解析命令行参数
2. 读取Pascal源文件 
3. 生成抽象语法树
4. 遍历语法树生成C代码
5. 输出转换后的C代码到文件

该项目展示了一个完整的源码转换实现，利用符号表和类型系统实现两种语言之间的映射，并通过访问者模式处理复杂的语法结构。 