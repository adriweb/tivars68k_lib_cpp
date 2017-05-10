/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#include "../autoloader.h"

namespace tivars
{

    data_t DummyHandler::makeDataFromString(const std::string& str, const options_t& options)
    {
        (void)str;
        (void)options;
        throw std::runtime_error("This type is not supported / implemented (yet?)");
    }

    std::string DummyHandler::makeStringFromData(const data_t& data, const options_t& options)
    {
        (void)data;
        (void)options;
        throw std::runtime_error("This type is not supported / implemented (yet?)");
    }

}
