/**
 * @file tests.cpp
 * @brief Source file for unit tests using Boost.Test.
 * 
 * @author Adam Napieralski
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LZWTests

#include <boost/test/unit_test.hpp>

#include "../include/lzw.hpp"

BOOST_AUTO_TEST_SUITE(LZW_TEST)

BOOST_AUTO_TEST_CASE(encode)
{
    auto lzw = LZW();
    std::vector<uint16_t> enc1 = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,122};
    BOOST_CHECK( lzw.encode("abcdefghijklmnopqrstuvwz") == enc1);
    BOOST_CHECK( lzw.encodeToString("abcdefghijklmnopqrstuvwz") == "97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,122" );
    
    std::vector<uint16_t> enc2 = {72,101,108,108,111,256,258,260,257,259,32,119,111,114,108,100,266,268,270,272,269,100};
    BOOST_CHECK( lzw.encode("HelloHelloHello world world world") == enc2 );
    BOOST_CHECK( lzw.encodeToString("HelloHelloHello world world world") == "72,101,108,108,111,256,258,260,257,259,32,119,111,114,108,100,266,268,270,272,269,100" );
}

BOOST_AUTO_TEST_CASE(decode)
{
    auto lzw = LZW();
    std::vector<uint16_t> enc1 = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,122};
    BOOST_CHECK( lzw.decode(enc1) == "abcdefghijklmnopqrstuvwz");
    BOOST_CHECK( lzw.decodeFromString("97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,122") == "abcdefghijklmnopqrstuvwz" );
    
    std::vector<uint16_t> enc2 = {72,101,108,108,111,256,258,260,257,259,32,119,111,114,108,100,266,268,270,272,269,100};
    BOOST_CHECK( lzw.decode(enc2) == "HelloHelloHello world world world");
    BOOST_CHECK( lzw.decodeFromString("72,101,108,108,111,256,258,260,257,259,32,119,111,114,108,100,266,268,270,272,269,100") == "HelloHelloHello world world world" );

    
}

BOOST_AUTO_TEST_CASE(comperssion_rate)
{
    auto lzw1 = LZW(9);
    lzw1.encode("HelloHelloHello world world world");
    BOOST_CHECK( lzw1.getCompressionRate() > 4/3. - .0001 && lzw1.getCompressionRate() < 4/3. + .0001);

    auto lzw2 = LZW(12);
    std::vector<uint16_t> enc1 = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,122};
    lzw2.decode(enc1);
    BOOST_CHECK( lzw2.getCompressionRate() > 2/3. - .0001 && lzw2.getCompressionRate() < 2/3. + .0001);
}



BOOST_AUTO_TEST_SUITE_END()
