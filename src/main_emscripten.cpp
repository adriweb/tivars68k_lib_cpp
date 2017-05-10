/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#ifdef __EMSCRIPTEN__

#include "TIModels.h"
#include "TIVarTypes.h"
#include "TypeHandlers/TypeHandlers.h"

#include <emscripten.h>

using namespace tivars;

extern "C" int EMSCRIPTEN_KEEPALIVE main(int, char**)
{
    TIModels::initTIModelsArray();
    TIVarTypes::initTIVarTypesArray();
    TH_0x12::initTokens();

    puts("tivars_lib ready!");

    return 0;
}

#endif