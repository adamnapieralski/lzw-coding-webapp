/**
 * @file lzwpy.cpp
 * @brief Source file for implementation of Python module based on cpp Compressor.
 * 
 * @author Adam Napieralski
 * @date 05.2020
 */

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "../include/lzw.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(lzw)
{
    class_<LZW, boost::noncopyable>("LZW", no_init)
        .def("getInstance", &LZW::getInstance, return_value_policy<reference_existing_object>())
            .staticmethod("getInstance")
        .def("encodeToString", &LZW::encodeToString)
        .def("decodeFromString", &LZW::decodeFromString)
        .def("getCompressionRate", &LZW::getCompressionRate)
        .def("setBitSize", &LZW::setBitSize)
    ;
}