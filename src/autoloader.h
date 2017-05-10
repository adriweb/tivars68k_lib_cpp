/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#ifndef AUTOLOADER_H
#define AUTOLOADER_H

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <cfloat>

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <map>
#include <unordered_map>

typedef unsigned int    uint;
typedef unsigned char   uchar;
typedef std::vector<uchar>   data_t;
typedef std::map<std::string, int>   options_t;

#include "TypeHandlers/TypeHandlers.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif

#endif