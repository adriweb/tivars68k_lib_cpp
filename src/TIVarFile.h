/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#ifndef TIVARS68K_LIB_CPP_TIVARFILE_H
#define TIVARS68K_LIB_CPP_TIVARFILE_H

#include "autoloader.h"
#include "BinaryFile.h"
#include "TIVarType.h"
#include "TIModel.h"

namespace tivars
{

    class TIVarFile : public BinaryFile
    {
        struct var_header_t
        {
            uchar    signature[8]  = {0};
            uchar    sig_extra[3]  = {0};
            uchar    comment[42]   = {0};
            uint16_t entries_len   = 0;
        };

        struct var_entry_t
        {
            uint16_t meta_length   = {0}; // byte count of the next 3 or 5 fields (== 11 or 13) depending on calcFlags, see below
            uint16_t data_length   = {0};
            uchar    typeID        = 0;
            uchar    varname[8]    = {0};
            uchar    version       = 0;   // present only if calcFlags >= TIFeatureFlags::hasFlash
            uchar    archivedFlag  = 0;   // present only if calcFlags >= TIFeatureFlags::hasFlash
            uint16_t data_length2  = {0}; // same as data_length
            data_t   data;
        };

        static const constexpr uint16_t headerLength      = 55;   // size of packed struct var_header_t
        static const constexpr uint16_t dataSectionOffset = 55;   // == headerLength;
        static const constexpr uint16_t varEntryOldLength = 0x0B; // 2+1+8     (if calcFlags <  TIFeatureFlags::hasFlash)
        static const constexpr uint16_t varEntryNewLength = 0x0D; // 2+1+8+1+1 (if calcFlags >= TIFeatureFlags::hasFlash)

    public:
        TIVarFile()
        {}

        TIVarFile(const std::string& filePath);

        const var_header_t& getHeader() const { return header; }
        const var_entry_t& getVarEntry() const { return varEntry; }
        const TIVarType& getType() const { return type; }
        uint16_t getInstanceChecksum() const { return computedChecksum; }

        static TIVarFile loadFromFile(const std::string& filePath);

        static TIVarFile createNew(const TIVarType& type, const std::string& name, const TIModel& model);
        static TIVarFile createNew(const TIVarType& type, const std::string& name);
        static TIVarFile createNew(const TIVarType& type);

        void makeHeaderFromFile();

        void makeVarEntryFromFile();

        uint16_t getChecksumValueFromFile();

        void setContentFromData(const data_t& data);

        void setContentFromString(const std::string& str, const options_t& options);
        void setContentFromString(const std::string& str);

        void setCalcModel(const TIModel& model);
        void setVarName(const std::string& name);

        data_t getRawContent();

        std::string getReadableContent(const options_t& options);
        std::string getReadableContent();

        std::string saveVarToFile(std::string directory, std::string name);
        std::string saveVarToFile();

    private:
        void refreshMetadataFields();
        std::string fixVarName(const std::string& name);

        uint16_t computeChecksumFromInstanceData();
        uint16_t computeChecksumFromFileData();


        var_header_t header;
        var_entry_t  varEntry;
        TIVarType    type;
        TIModel      calcModel;
        uint16_t     computedChecksum = 0;
        uint16_t     inFileChecksum   = 0;
        bool         isFromFile       = false;
        bool         corrupt          = false;

        data_t make_bin_data();

    };
}

#endif //TIVARS68K_LIB_CPP_BINARYFILE_H
