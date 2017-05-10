/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#include "TIVarTypes.h"
#include "utils.h"

using namespace std;

namespace tivars
{

    unordered_map<string, TIVarType> types;

    /**
     *  Make and insert the associative arrays for the type.
     *
     * @param string    name        The name of the type
     * @param int       id          The ID of the type
     * @param vector    exts        The extensions the type can have, ordered by feature flags.
     * @param pair      handlers    The data2str and str2data funcs
     */
    void TIVarTypes::insertType(string name, int id, const vector<string>& exts, const handler_pair_t& handlers)
    {
        TIVarType varType(id, name, exts, handlers);

        string id_str = to_string(id);
        types[name]   = varType;
        types[id_str] = varType;
        for (const string ext : exts)
        {
            if (ext != "" && !types.count(ext))
            {
                types[ext] = varType;
            }
        }
    }

    void TIVarTypes::initTIVarTypesArray() // order: 89    92(II)    92+   V200     89T
    {
        insertType("Unknown",                -1,  {  "" ,    "" ,    "" ,   "",     "" });

        /* Standard types */
        insertType("Program",              0x12,  { "89p" , "92p" , "9xp", "v2p" , "89p" },  make_handler_pair(TH_0x12) );

        /* TODO */
    }

    /**
     * @param   int     id     The type ID
     * @return  string          The type name for that ID
     */
    string TIVarTypes::getNameFromID(int id)
    {
        string id_str = to_string(id);
        if (id != -1 && types.count(id_str))
        {
            return types[id_str].getName();
        } else {
            return "Unknown";
        }
    }

    /**
     * @param   string  name   The type name
     * @return  int             The type ID for that name
     */
    int TIVarTypes::getIDFromName(string name)
    {
        if (name != "" && types.count(name))
        {
            return types[name].getId();
        } else {
            return -1;
        }
    }

    /**
     * @param   int     id     The type ID
     * @return  string[]        The array of extensions for that ID
     */
    vector<string> TIVarTypes::getExtensionsFromTypeID(int id)
    {
        string id_str = to_string(id);
        if (id != -1 && types.count(id_str))
        {
            return types[id_str].getExts();
        } else {
            return {};
        }
    }

    /**
     * @param   string  name
     * @return  string[]        The array of extensions for that ID
     */
    vector<string> TIVarTypes::getExtensionsFromName(string name)
    {
        if (name != "" && types.count(name))
        {
            return types[name].getExts();
        } else {
            return {};
        }
    }

    bool TIVarTypes::isValidID(int id)
    {
        string id_str = to_string(id);
        return (id != -1 && types.count(id_str));
    }

    bool TIVarTypes::isValidName(const string& name)
    {
        return (name != "" && types.count(name));
    }
}

//TIVarTypes::initTIVarTypesArray();
