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

class LZW {
public:
    static LZW& getInstance();

    std::vector<uint16_t> encode(const std::string& str);
    std::string encodeToString(const std::string& str);

    std::string decode(const std::vector<uint16_t>& code);
    std::string decodeFromString(const std::string& code);

    double getCompressionRate() const;

private:
	LZW();

    void initializeEncodeTable();
    void initializeDecodeTable();

    void resetEncodeTable();
    void resetDecodeTable();

    void setMaxTableSize();
    void calculateCompressionRate(const std::string& text, const std::vector<uint16_t>& code);

    std::string vectorToString(const std::vector<uint16_t>& vec);
    std::vector<uint16_t> stringToVector(const std::string& str);

    int bitSize_;
    size_t maxTableSize_;
    double compressionRate_;
    std::unordered_map<std::string, uint16_t> encodeTable_;
    std::unordered_map<uint16_t, std::string> decodeTable_;
};

#endif //_LZW_HPP_