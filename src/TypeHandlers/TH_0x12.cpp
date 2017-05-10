/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#include "TypeHandlers.h"
#include "../utils.h"

using namespace std;

namespace tivars
{
    namespace TH_0x12
    {
        std::unordered_map<uint, std::vector<std::string>> tokens_BytesToName;
        std::unordered_map<std::string, uint> tokens_NameToBytes;
        uchar lengthOfLongestTokenName;
        std::vector<uchar> firstByteOfTwoByteTokens;
    }

    data_t TH_0x12::makeDataFromString(const string& str, const options_t& options)
    {
        (void)options;
        data_t data;

        /* TODO */

        return data;
    }

    string TH_0x12::makeStringFromData(const data_t& data, const options_t& options)
    {
        string str;

        /* TODO */

        return str;
    }

    string TH_0x12::reindentCodeString(const string& str_orig)
    {
        string str(str_orig);

        /* TODO */

        return str;
    }

    void TH_0x12::initTokens()
    {
        /* To redo, maybe */

        ifstream t("programs_tokens.csv");
        string csvFileStr((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

        if (csvFileStr.length() > 0)
        {
            vector<vector<string>> lines;
            ParseCSV(csvFileStr, lines);

            for (const auto& tokenInfo : lines)
            {
                uint bytes;
                if (tokenInfo[6] == "2") // number of bytes for the token
                {
                    if (!is_in_vector(firstByteOfTwoByteTokens, hexdec(tokenInfo[7])))
                    {
                        firstByteOfTwoByteTokens.push_back(hexdec(tokenInfo[7]));
                    }
                    bytes = hexdec(tokenInfo[8]) + (hexdec(tokenInfo[7]) << 8);
                } else {
                    bytes = hexdec(tokenInfo[7]);
                }
                tokens_BytesToName[bytes] = { tokenInfo[4], tokenInfo[5] }; // EN, FR
                tokens_NameToBytes[tokenInfo[4]] = bytes; // EN
                tokens_NameToBytes[tokenInfo[5]] = bytes; // FR
                uchar maxLenName = (uchar) max(tokenInfo[4].length(), tokenInfo[5].length());
                if (maxLenName > lengthOfLongestTokenName)
                {
                    lengthOfLongestTokenName = maxLenName;
                }
            }
        } else {
            throw runtime_error("Could not open the tokens csv file");
        }
    }

}