/**
 * @file lzw.cpp
 * @brief Source file for class implementing LZW algorithm.
 * 
 * @author Adam Napieralski
 * @date 05.2020
 */

#include "../include/lzw.hpp"

#include <iostream>
#include <climits>
#include <cmath>
#include <sstream>
#include <algorithm>

LZW& LZW::getInstance() {
    static LZW instance;
    return instance;
}

LZW::LZW() {
    bitSize_ = 12;
    setMaxTableSize();
    compressionRate_ = 0.;
}

std::vector<uint16_t> LZW::encode(const std::string& str) {
    resetEncodeTable();
    std::vector<uint16_t> out;
    std::string p = "", c = "";
    if (str.empty()) return out;
    p += str.at(0);
    int count = UCHAR_MAX + 1;
    for (size_t i = 0; i < str.length(); ++i) {
        if (encodeTable_.size() >= maxTableSize_) {
            resetEncodeTable();
            count = UCHAR_MAX + 1;
        }
        if (i != str.length() - 1) {
            c += str.at(i + 1);
        }
        if (encodeTable_.find(p + c) != encodeTable_.end()) {
            p += c;
        }
        else {
            out.push_back(encodeTable_[p]);
            encodeTable_[p + c] = count;
            ++count;
            p = c;
        }
        c = "";
    }
    out.push_back(encodeTable_[p]);
    calculateCompressionRate(str, out);
    return out;
}

std::string LZW::encodeToString(const std::string& str) {
    auto vec = encode(str);
    return vectorToString(vec);
}


std::string LZW::decode(const std::vector<uint16_t>& code) {
    resetDecodeTable();
    std::string out = "";
    if (code.empty()) return out;
    int old = code.at(0);
    int codeNum;
    std::string s = decodeTable_[old];
    std::string c = s;
    out += s;
    int count = UCHAR_MAX + 1;

    for (size_t i = 0; i < code.size() - 1; ++i) {
        codeNum = code.at(i + 1);
        if (decodeTable_.size() >= maxTableSize_) {
            resetDecodeTable();
            count = UCHAR_MAX + 1;
        }
        if (decodeTable_.find(codeNum) != decodeTable_.end()) {
            s = decodeTable_.at(codeNum);
        }
        else {
            s = decodeTable_.at(old);
            s += c;
        }
        out += s;
        c = "";
        c += s.at(0);
        decodeTable_[count] = decodeTable_[old] + c;
        ++count;
        old = codeNum;
    }
    calculateCompressionRate(out, code);
    return out;
}

std::string LZW::decodeFromString(const std::string& code) {
    auto codeVec = stringToVector(code);
    return decode(codeVec);
}

void LZW::setBitSize(int bitSize) {
    bitSize_ = bitSize;
    setMaxTableSize();
    std::cout << bitSize_;
}


double LZW::getCompressionRate() const {
    return compressionRate_;
}


void LZW::initializeEncodeTable() {
    for (int i = 0; i < UCHAR_MAX; ++i) {
        std::string ch = "";
        ch += char(i);
        encodeTable_[ch] = i;
    }
}

void LZW::initializeDecodeTable() {
    for (int i = 0; i < UCHAR_MAX; ++i) {
        std::string ch = "";
        ch += char(i);
        decodeTable_[i] = ch;
    }
}

void LZW::resetEncodeTable() {
    encodeTable_.clear();
    initializeEncodeTable();
}

void LZW::resetDecodeTable() {
    decodeTable_.clear();
    initializeDecodeTable();
}

void LZW::setMaxTableSize() {
    maxTableSize_ = static_cast<int>(std::pow(2., bitSize_) - 1);
}

void LZW::calculateCompressionRate(const std::string& text, const std::vector<uint16_t>& code) {
    compressionRate_ = static_cast<double>(text.length() * CHAR_BIT) / (code.size() * bitSize_);
}

std::string LZW::vectorToString(const std::vector<uint16_t>& vec) {
    std::string out = "";
    for (auto& el : vec) {
        out += std::to_string(el) + ",";
    }
    out.pop_back();
    return out;
}

std::vector<uint16_t> LZW::stringToVector(const std::string& str) {
    auto strReplaced = str;
    std::replace(strReplaced.begin(), strReplaced.end(), ',', ' ');
    std::stringstream iss(strReplaced);
    uint16_t num;
    std::vector<uint16_t> vec;
    while (iss >> num) {
        vec.push_back(num);
    }
    return vec;
}

