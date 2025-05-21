#pragma once

#include <iostream>
#include <string>
#include "SymbolTable.h"
#include "../antlr/PascalSParser.h"
#include "TranslatorUtils.h"

enum class ErrorType {
    UNDEFINED_FUNCTION,
    ARGUMENT_COUNT_MISMATCH,
    MISSING_ARGUMENTS,
    INVALID_ARRAY_INDEX,
    UNDEFINED_VARIABLE,
    TYPE_MISMATCH_IN_ASSIGNMENT,
    NON_BOOLEAN_CONDITION,
    IGNORED_FUNCTION_RETURN,
    INCOMPATIBLE_COMPARISON,
    PROCEDURE_IN_ASSIGNMENT,
    ARRAY_INDEX_OUT_OF_BOUNDS
};

template<typename T>
struct ErrorContext {
    T *context = nullptr;
    SymbolTable *symbolTable = nullptr;
    std::string id;
    PascalType leftType = PascalType::INTEGER;
    PascalType rightType = PascalType::INTEGER;
    std::string cond;
    std::ostream *ss = nullptr;
};

// Helper函数用于在使用后安全地删除ErrorContext
template<typename T>
void deleteErrorContext(ErrorContext<T>* errorContext) {
    if (errorContext != nullptr) {
        delete errorContext;
    }
}

template<typename T>
void UndefinedFunction(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "未定义的函数/过程 " << errorContext->id;
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << " , 行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 未定义的函数/过程 ：" << errorContext->id << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void ArgumentCountMismatch(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "函数调用时实参数量多余与形参数量：" << errorContext->id;
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << "，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 函数调用时实参数量多余与形参数量 ：" << errorContext->id << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void MissingArguments(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "该函数参数有漏缺：" << errorContext->id;
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << "，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 该函数参数有漏缺 ：" << errorContext->id << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void InvalidArrayIndex(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "数组索引定义不合法";
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << "，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 原Pascal数组索引定义不合法" << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void UndefinedVariable(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "未定义的变量 " << errorContext->id;
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << "，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 未定义的变量 ：" << errorContext->id << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void TypeMismatchInAssignment(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "类型不匹配 - 将 " << TranslatorUtils::pascalTypeToString(errorContext->rightType)
              << " 类型的值赋给 " << TranslatorUtils::pascalTypeToString(errorContext->leftType)
              << " 类型的变量 " << errorContext->id;
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << "，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 等式两边类型不匹配 " << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void NonBooleanCondition(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "条件语句中使用了非布尔类型的条件 " << errorContext->cond;
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << "，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 条件语句中使用了非布尔类型的条件" << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void IgnoredFunctionReturn(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "忽略了函数的返回值 " << errorContext->id;
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << "，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 忽略了函数的返回值 ：" << errorContext->id << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void IncompatibleComparison(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "比较操作类型不兼容 - 操作 " << TranslatorUtils::pascalTypeToString(errorContext->leftType)
              << " 类型与 " << TranslatorUtils::pascalTypeToString(errorContext->rightType);
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << "，在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << " ，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 比较操作类型不兼容 " << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void ProcedureInAssignment(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;
    
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "错误地将过程加入赋值操作 " << errorContext->id;
    
    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }
    
    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << " ，行：" << errorContext->context->start->getLine();
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 错误地将过程加入赋值操作 ：" << errorContext->id << std::endl;
    
    deleteErrorContext(errorContext);
}

template<typename T>
static void ArrayIndexOutOfBounds(ErrorContext<T> *errorContext) {
    if (errorContext == nullptr || errorContext->ss == nullptr) return;

    std::cout << "-" << std::endl;
    std::cout << "警告：";
    std::cout << "数组索引使用不合法";

    if (errorContext->symbolTable != nullptr) {
        std::cout << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName();
    }

    if (errorContext->context != nullptr && errorContext->context->start != nullptr) {
        std::cout << " ，行：" << errorContext->context->start->getLine();
    }

    std::cout << std::endl;
    std::cout << "-" << std::endl;
    *(errorContext->ss) << "//[Warning] 数组索引使用不合法" << std::endl;

    deleteErrorContext(errorContext);
}
