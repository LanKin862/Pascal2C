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
    PROCEDURE_IN_ASSIGNMENT
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


template<typename T>
void UndefinedFunctionStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "未定义的函数/过程 " << errorContext->id
              << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << " , 行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 未定义的函数/过程 ：" << errorContext->id << std::endl;
}


template<typename T>
static void ArgumentCountMismatchStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "函数调用时实参与形参数量不匹配：" << errorContext->id
              << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << "，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 函数调用时实参与形参数量不匹配 ：" << errorContext->id << std::endl;
}

template<typename T>
static void MissingArgumentsStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "该函数参数有漏缺：" << errorContext->id
              << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << "，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 该函数参数有漏缺 ：" << errorContext->id << std::endl;
}

template<typename T>
static void InvalidArrayIndexStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "数组索引不合法"
              << "，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 数组索引不合法" << std::endl;
}


template<typename T>
static void UndefinedVariableStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "未定义的变量 " << errorContext->id
              << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << "，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 未定义的变量 ：" << errorContext->id << std::endl;
}


template<typename T>
static void TypeMismatchInAssignmentStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "类型不匹配 - 将 " << TranslatorUtils::pascalTypeToString(errorContext->rightType)
              << " 类型的值赋给 " << TranslatorUtils::pascalTypeToString(errorContext->leftType)
              << " 类型的变量 " << errorContext->id
              << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << "，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 等式两边类型不匹配 " << std::endl;
}


template<typename T>
static void NonBooleanConditionStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "条件语句条件表达式须是布尔类型：" << errorContext->cond
              << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << "，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 条件表达式须是布尔类型 ：" << errorContext->cond << std::endl;
}


template<typename T>
static void IgnoredFunctionReturnStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "该函数返回值被忽略：" << errorContext->id
              << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << "，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 该函数返回值被忽略 ：" << errorContext->id << std::endl;
}


template<typename T>
static void IncompatibleComparisonStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "比较操作类型不兼容 - 操作 " << TranslatorUtils::pascalTypeToString(errorContext->leftType)
              << " 类型与 " << TranslatorUtils::pascalTypeToString(errorContext->rightType)
              << " 类型，在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << " ，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 比较操作类型不兼容 " << std::endl;
}


template<typename T>
static void ProcedureInAssignmentStrategy(ErrorContext<T> *errorContext) {
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "警告：";
    std::cout << "错误地将过程加入赋值操作 " << errorContext->id
              << " 在 " << errorContext->symbolTable->getCurrentScope().getScopeName()
              << " ，行：" << errorContext->context->start->getLine() << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
    *(errorContext->ss) << "//[Warning] 错误地将过程加入赋值操作 ：" << errorContext->id << std::endl;
}

