/**
 * @file Compressor.cpp
 * @brief Header file for Compressor class implementing LZW algorithm.
 * 
 * @author Adam Napieralski
 * @date 05.2020
 */

#ifndef _COMPRESSOR_HPP_
#define _COMPRESSOR_HPP_

#include <vector>
#include <unordered_map>

class Compressor {
public:
    static Compressor& getInstance();

    std::vector<uint16_t> encode(std::string s);
    std::string decode(std::vector<uint16_t> coded);

private:
	Compressor();

    void initializeEncodeTable();
    void initializeDecodeTable();

    void resetEncodeTable();
    void resetDecodeTable();
    
    void setMaxTableSize();

    int bitSize_;
    int maxTableSize_;
    std::unordered_map<std::string, uint16_t> encodeTable_;
    std::unordered_map<uint16_t, std::string> decodeTable_;
};

#endif //_COMPRESSOR_HPP_