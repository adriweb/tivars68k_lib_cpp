/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#include <cassert>

#include "src/autoloader.h"

#include "src/TIModels.h"
#include "src/TIVarTypes.h"
#include "src/BinaryFile.h"
#include "src/TIVarFile.h"
#include "src/TypeHandlers/TypeHandlers.h"

enum { LANG_EN = 0, LANG_FR };

using namespace std;
using namespace tivars;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    /* Init Stuff */

    TIModels::initTIModelsArray();
    TIVarTypes::initTIVarTypesArray();
    // TH_0x12::initTokens();

    /* Tests */

    TIVarFile testPrgm42 = TIVarFile::createNew(TIVarType::createFromName("Program"), "asdf");
    testPrgm42.setCalcModel(TIModel::createFromName("89T"));
    testPrgm42.setContentFromString("Hello WORLD!");
    testPrgm42.setVarName("Toto");
    assert(testPrgm42.getReadableContent() == "Hello WORLD!");
    testPrgm42.saveVarToFile("testData", "testPrgm_new");

    return 0;
}
