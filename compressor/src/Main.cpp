#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/lzw.hpp"

int main() {

    auto lzw = LZW::getInstance();

    std::ifstream inFile;
    inFile.open("input.txt");

    std::stringstream strStream;
    strStream << inFile.rdbuf();

    std::string in = strStream.str();

    auto vec = lzw.encode(in);
    // for (auto& el  : vec) {
    //     std::cout << el << " ";
    // }
    auto out = lzw.decode(vec);
    // std::cout << std::endl << out << std::endl;
    bool eq = (in == out);
    std::cout << eq << std::endl << lzw.getCompressionRate();
    
    return 0;
}