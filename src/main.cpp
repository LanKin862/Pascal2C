#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/PascalToCTranslator.h"
#include "../include/TranslatorUtils.h"

void printUsage() {
    std::cout << "Usage: compiler -i <input_file>" << std::endl;
    std::cout << "output will be written to <input_file>.c" << std::endl;
}

// 将文件内容读入字符串的函数
std::string readFileContents(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        throw std::runtime_error("Failed to open input file: " + filePath);
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    inFile.close();

    return buffer.str();
}

// 将内容写入文件的函数
bool writeToFile(const std::string& filePath, const std::string& content) {
    std::ofstream outFile(filePath);
    if (!outFile) {
        return false;
    }

    outFile << content;
    outFile.close();
    return true;
}

int main(int argc, char* argv[]) {
    // 检查命令行参数
    if (argc < 3 || std::string(argv[1]) != "-i") {
        printUsage();
        return 1;
    }

    // 获取输入文件路径
    std::string inputFile = argv[2];
    std::string outputFile;

    // 默认输出文件名是输入文件名加.c扩展名
    size_t dotPos = inputFile.find_last_of('.');
    if (dotPos != std::string::npos) {
        outputFile = inputFile.substr(0, dotPos) + ".c";
    } else {
        outputFile = inputFile + ".c";
    }

    try {
        // 读取并显示输入文件的内容
        std::string inputFileContents = readFileContents(inputFile);

        // 创建翻译器
        PascalToCTranslator translator;

        // 翻译输入文件
        std::string cCode = translator.translate(inputFile);

        // 检查翻译是否成功
        if (cCode.empty()) {
            std::cerr << "Translation failed." << std::endl;
            return 1;
        }

        // 将翻译后的代码写入输出文件
        if (!writeToFile(outputFile, cCode)) {
            std::cerr << "Failed to open or write to output file: " << outputFile << std::endl;
            return 1;
        }

//        // 创建包含详细信息的额外文件（如需要）
//        std::string debugFile = outputFile + ".debug";
//        std::stringstream debugInfo;
//        debugInfo << "Original Pascal-S code:\n";
//        debugInfo << "=====================\n";
//        debugInfo << inputFileContents << "\n\n";
//        debugInfo << "Translated C code:\n";
//        debugInfo << "=====================\n";
//        debugInfo << cCode;

//        if (!writeToFile(debugFile, debugInfo.str())) {
//            std::cout << "Note: Could not create debug information file." << std::endl;
//        }

        std::cout << "Translation completed successfully. Output written to " << outputFile << std::endl;
//        std::cout << "Debug information written to " << debugFile << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
