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

// Function to read file contents into a string
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

// Function to write content to a file
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
    // Check command line arguments
    if (argc < 3 || std::string(argv[1]) != "-i") {
        printUsage();
        return 1;
    }

    // Get input file path
    std::string inputFile = argv[2];
    std::string outputFile;

    // Default output file name is input file name with .c extension
    size_t dotPos = inputFile.find_last_of('.');
    if (dotPos != std::string::npos) {
        outputFile = inputFile.substr(0, dotPos) + ".c";
    } else {
        outputFile = inputFile + ".c";
    }

    try {
        // Read and display the contents of the input file
        std::string inputFileContents = readFileContents(inputFile);

        // Create translator
        PascalToCTranslator translator;

        // Translate the input file
        std::string cCode = translator.translate(inputFile);

        // Check if translation was successful
        if (cCode.empty()) {
            std::cerr << "Translation failed." << std::endl;
            return 1;
        }

        // Write the translated code to the output file
        if (!writeToFile(outputFile, cCode)) {
            std::cerr << "Failed to open or write to output file: " << outputFile << std::endl;
            return 1;
        }

//        // Create additional files with detailed information if needed
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
