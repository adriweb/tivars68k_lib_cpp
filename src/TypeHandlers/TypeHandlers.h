/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#ifndef TYPE_HANDLERS_H
#define TYPE_HANDLERS_H

#include "../autoloader.h"

namespace tivars
{

#define th()    data_t      makeDataFromString(const std::string& str,  const options_t& options = options_t()); \
                std::string makeStringFromData(const data_t& data,      const options_t& options = options_t())

    namespace DummyHandler { th(); }


    namespace TH_0x12 { th(); }  // Program

#undef th


    /* Additional things */

    namespace TH_0x12   // Program
    {
        std::string reindentCodeString(const std::string& str_orig);
        void initTokens();
    }


    typedef decltype(&DummyHandler::makeDataFromString) dataFromString_handler_t;
    typedef decltype(&DummyHandler::makeStringFromData) stringFromData_handler_t;
    typedef std::pair<dataFromString_handler_t, stringFromData_handler_t> handler_pair_t;

#define make_handler_pair(cls)   make_pair(&cls::makeDataFromString, &cls::makeStringFromData)

}

#endif