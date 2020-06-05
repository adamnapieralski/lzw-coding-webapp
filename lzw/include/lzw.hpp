/**
 * @file lzw.cpp
 * @brief Header file for class implementing LZW algorithm.
 * 
 * @author Adam Napieralski
 * @date 05.2020
 */

#ifndef _LZW_HPP_
#define _LZW_HPP_

#include <vector>
#include <unordered_map>

#define DEFAULT_BIT_SIZE 12

class LZW {
public:
	LZW();
    LZW(int bitSize);
    
    std::vector<uint16_t> encode(const std::string& str);
    std::string encodeToString(const std::string& str);

    std::string decode(const std::vector<uint16_t>& code);
    std::string decodeFromString(const std::string& code);
    
    int getBitSize() const;
    double getCompressionRate() const;

private:
    void resetEncodeTable();
    void resetDecodeTable();

    void calculateCompressionRate(const std::string& text, const std::vector<uint16_t>& code);

    std::string vectorToString(const std::vector<uint16_t>& vec);
    std::vector<uint16_t> stringToVector(const std::string& str);

    const int bitSize_;
    const size_t maxTableSize_;
    double compressionRate_;

    std::unordered_map<std::string, uint16_t> encodeTable_;
    std::unordered_map<uint16_t, std::string> decodeTable_;
};

#endif //_LZW_HPP_