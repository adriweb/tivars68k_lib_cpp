/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#ifndef TIVARTYPES_H
#define TIVARTYPES_H

#include "autoloader.h"
#include "TIVarType.h"

namespace tivars
{
    extern std::unordered_map<std::string, TIVarType> types;

    class TIVarTypes
    {

    public:
        static void initTIVarTypesArray();

        static bool isValidName(const std::string& name);

        static bool isValidID(int id);

        static std::vector<std::string> getExtensionsFromName(std::string name);
        static std::vector<std::string> getExtensionsFromTypeID(int id);
        static int getIDFromName(std::string name);
        static std::string getNameFromID(int id);

    private:
        static void insertType(std::string name, int id, const std::vector<std::string>& exts, const handler_pair_t& handlers = make_handler_pair(DummyHandler));

    };
}

#endif //TIVARTYPES_H
