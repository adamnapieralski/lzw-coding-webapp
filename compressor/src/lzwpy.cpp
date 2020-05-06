/**
 * @file lzwpy.cpp
 * @brief Source file for implementation of Python module based on cpp Compressor.
 * 
 * @author Adam Napieralski
 * @date 05.2020
 */

#include <boost/python.hpp>
#include "../include/lzw.hpp"

using namespace boost::python;

BOOST_PYTHON_MODULE(lzw)
{
    class_<LZW, boost::noncopyable>("LZW", no_init)
        .def("getInstance", &LZW::getInstance, return_value_policy<reference_existing_object>())
            .staticmethod("getInstance")
    ;
}