/**
 * @file Compressor.cpp
 * @brief Source file for Compressor class implementing LZW algorithm.
 * 
 * @author Adam Napieralski
 * @date 05.2020
 */

#include "../include/Compressor.hpp"

#include <climits>
#include <cmath>

Compressor& Compressor::getInstance() {
    static Compressor instance;
    return instance;
}

Compressor::Compressor() {
    bitSize_ = 12;
    setMaxTableSize();    
}

std::vector<uint16_t> Compressor::encode(std::string s) {
    resetEncodeTable();
    std::vector<uint16_t> out;
    std::string p = "", c = "";
    if (s.empty()) return out;
    p += s.at(0);
    int count = UCHAR_MAX + 1;
    for (int i = 0; i < s.length(); ++i) {
        if (encodeTable_.size() >= maxTableSize_) {
            resetEncodeTable();
            count = UCHAR_MAX + 1;
        }
        if (i != s.length() - 1) {
            c += s.at(i + 1);
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
    return out;
}

std::string Compressor::decode(std::vector<uint16_t> coded) {
    resetDecodeTable();
    std::string out = "";
    if (coded.empty()) return out;
    int old = coded.at(0);
    int codeNum;
    std::string s = decodeTable_[old];
    std::string c = s;
    out += s;
    int count = UCHAR_MAX + 1;

    for (int i = 0; i < coded.size() - 1; ++i) {
        codeNum = coded.at(i + 1);
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
    return out;
}

void Compressor::initializeEncodeTable() {
    for (int i = 0; i < UCHAR_MAX; ++i) {
        std::string ch = "";
        ch += char(i);
        encodeTable_[ch] = i;
    }
}

void Compressor::initializeDecodeTable() {
    for (int i = 0; i < UCHAR_MAX; ++i) {
        std::string ch = "";
        ch += char(i);
        decodeTable_[i] = ch;
    }
}

void Compressor::resetEncodeTable() {
    encodeTable_.clear();
    initializeEncodeTable();
}

void Compressor::resetDecodeTable() {
    decodeTable_.clear();
    initializeDecodeTable();
}

void Compressor::setMaxTableSize() {
    maxTableSize_ = static_cast<int>(std::pow(2., bitSize_) - 1);
}