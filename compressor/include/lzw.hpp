/**
 * @file lzw.cpp
 * @brief Header file for class implementing LZW algorithm.
 * 
 * @author Adam Napieralski
 * @date 05.2020
 */

#ifndef _LZW_HPP_
#define _LZW_HPP

#include <vector>
#include <unordered_map>

class LZW {
public:
    static LZW& getInstance();

    std::vector<uint16_t> encode(std::string s);
    std::string decode(std::vector<uint16_t> coded);

    double getCompressionRate() const;

private:
	LZW();

    void initializeEncodeTable();
    void initializeDecodeTable();

    void resetEncodeTable();
    void resetDecodeTable();

    void setMaxTableSize();
    void calculateCompressionRate(const std::string& text, const std::vector<uint16_t>& code);

    int bitSize_;
    int maxTableSize_;
    double compressionRate_;
    std::unordered_map<std::string, uint16_t> encodeTable_;
    std::unordered_map<uint16_t, std::string> decodeTable_;
};



#endif //_LZW_HPP_