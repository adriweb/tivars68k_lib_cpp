/*
 * Part of tivars68k_lib_cpp
 * (C) 2017 Adrien 'Adriweb' Bertrand
 * https://github.com/adriweb/tivars68k_lib_cpp
 * License: MIT
 */

#include "TIVarFile.h"
#include "utils.h"
#include "TIModels.h"
#include <numeric>

using namespace std;

namespace tivars
{

    /*** Constructors ***/

    /**
     * Internal constructor, called from loadFromFile and createNew.
     * @param   string  filePath
     * @throws  \Exception
     */
    TIVarFile::TIVarFile(const string& filePath) : BinaryFile(filePath)
    {
        if (filePath != "")
        {
            this->isFromFile = true;
            /* TODO */
            /*
            if (this->fileSize < 76) // bare minimum for header + a var entry
            {
                throw runtime_error("This file is not a valid TI-[e]z80 variable file");
            }
            */
            this->makeHeaderFromFile();
            this->makeVarEntryFromFile();
            this->computedChecksum = this->computeChecksumFromFileData();
            this->inFileChecksum = this->getChecksumValueFromFile();
            if (this->computedChecksum != this->inFileChecksum)
            {
                // puts("[Warning] File is corrupt (read and calculated checksums differ)");
                this->corrupt = true;
            }
            this->type = TIVarType::createFromID(this->varEntry.typeID);
        } else {
            this->isFromFile = false;
        }
    }

    TIVarFile TIVarFile::loadFromFile(const string& filePath)
    {
        if (filePath != "")
        {
            TIVarFile varFile(filePath);
            return varFile;
        } else {
            throw runtime_error("No file path given");
        }
    }

    TIVarFile TIVarFile::createNew(const TIVarType& type, const string& name, const TIModel& model)
    {
        TIVarFile varFile;
        varFile.type = type;
        varFile.calcModel = model;

        string newName = varFile.fixVarName(name);

        if (!varFile.calcModel.supportsType(varFile.type))
        {
            throw runtime_error("This calculator model (" + varFile.calcModel.getName() + ") does not support the type " + varFile.type.getName());
        }

        /* TODO */

        return varFile;
    }

    TIVarFile TIVarFile::createNew(const TIVarType& type, const string& name)
    {
        return createNew(type, name, TIModel::createFromName("84+"));
    }

    TIVarFile TIVarFile::createNew(const TIVarType& type)
    {
        return createNew(type, "");
    }

    /*** Makers ***/

    void TIVarFile::makeHeaderFromFile()
    {
        rewind(this->file);

        /* TODO */
    }

    void TIVarFile::makeVarEntryFromFile()
    {
        fseek(this->file, TIVarFile::dataSectionOffset, SEEK_SET);

        /* TODO */
    }


    /*** Private actions ***/

    uint16_t TIVarFile::computeChecksumFromFileData()
    {
        if (this->isFromFile)
        {
            fseek(this->file, TIVarFile::dataSectionOffset, SEEK_SET);

            uint16_t sum = 0;
            for (size_t i = dataSectionOffset; i < this->fileSize - 2; i++)
            {
                sum += this->get_raw_bytes(1)[0];
            }
            return (uint16_t) (sum & 0xFFFF);
        } else {
            throw runtime_error("[Error] No file loaded");
        }
    }

    uint16_t TIVarFile::computeChecksumFromInstanceData()
    {
        uint16_t sum = 0;
        /* TODO */
        return (uint16_t) (sum & 0xFFFF);
    }

    uint16_t TIVarFile::getChecksumValueFromFile()
    {
        if (this->isFromFile)
        {
            fseek(this->file, this->fileSize - 2, SEEK_SET);
            return this->get_raw_bytes(1)[0] + (this->get_raw_bytes(1)[0] << 8);
        } else {
            throw runtime_error("[Error] No file loaded");
        }
    }

    /**
     *  Updates the length fields in both the header and the var entry, as well as the checksum
     */
    void TIVarFile::refreshMetadataFields()
    {
        // todo : recompute correctly for multiple var entries
        /* TODO */
    }

    string TIVarFile::fixVarName(const string& name)
    {
        string newName(name);
        if (newName == "")
        {
            newName = "FILE" + ((type.getExts().size() > 0) ? type.getExts()[0] : "");
        }
        newName = regex_replace(newName, regex("[^a-zA-Z0-9]"), "");

        /* TODO */

        return newName;
    }

    /*** Public actions **/

    /**
    * @param    array   data   The array of bytes
    */
    void TIVarFile::setContentFromData(const data_t& data)
    {
        if (data.size() > 0)
        {
            this->varEntry.data = data;
            this->refreshMetadataFields();
        } else {
            throw runtime_error("[Error] No data given");
        }
    }

    void TIVarFile::setContentFromString(const string& str, const options_t& options)
    {
        this->varEntry.data = (this->type.getHandlers().first)(str, options);
        this->refreshMetadataFields();
    }
    void TIVarFile::setContentFromString(const string& str)
    {
        setContentFromString(str, {});
    }

    void TIVarFile::setCalcModel(const TIModel& model)
    {
        this->calcModel = model;
        string signature = model.getSig();
        std::copy(signature.begin(), signature.end(), this->header.signature);
    }

    void TIVarFile::setVarName(const string& name)
    {
        string varname = TIVarFile::fixVarName(name);
        std::copy(varname.begin(), varname.begin() + 7, this->varEntry.varname);
        this->refreshMetadataFields();
    }


    data_t TIVarFile::getRawContent()
    {
        return this->varEntry.data;
    }

    string TIVarFile::getReadableContent(const options_t& options)
    {
        return (this->type.getHandlers().second)(this->varEntry.data, options);
    }
    string TIVarFile::getReadableContent()
    {
        return getReadableContent({});
    }

    data_t TIVarFile::make_bin_data()
    {
        data_t bin_data;

        /* TODO */

        return bin_data;
    }

    /**
     * Writes a variable to an actual file on the FS
     * If the variable was already loaded from a file, it will be used and overwritten,
     * except if a specific directory and name are provided.
     *
     * @param   string  directory  Directory to save the file to
     * @param   string  name       Name of the file, without the extension
     */
    string TIVarFile::saveVarToFile(string directory, string name)
    {
        string fullPath;
        FILE* handle;

        if (this->isFromFile && directory == "")
        {
            this->close();
            fullPath = this->filePath;
            handle = fopen(this->filePath.c_str(), "wb");
        } else {
            if (name == "")
            {
                string tmp("");
                for (uint i=0; i<8; i++)
                {
                    if (this->varEntry.varname[i])
                    {
                        tmp += this->varEntry.varname[i];
                    } else {
                        break;
                    }
                }
                name = tmp;
            }
            int extIndex = this->calcModel.getOrderId();
            if (extIndex < 0)
            {
                extIndex = 0;
            }
            string fileName = name + "." + this->getType().getExts()[extIndex];
            if (directory == "")
            {
                directory = ".";
            }
            fullPath = directory + "/" + fileName;
            handle = fopen(fullPath.c_str(), "wb");
        }

        this->refreshMetadataFields();

        // Make and write file data
        data_t bin_data = make_bin_data();
        fwrite(&bin_data[0], bin_data.size(), sizeof(uchar), handle);

        // Write checksum
        const char buf[2] = {(char) (this->computedChecksum & 0xFF), (char) ((this->computedChecksum >> 8) & 0xFF)};
        fwrite(buf, sizeof(char), 2, handle);

        fclose(handle);

        this->corrupt = false;

        return fullPath;
    }

    string TIVarFile::saveVarToFile()
    {
        return saveVarToFile("", "");
    }


#ifdef __EMSCRIPTEN__
    using namespace emscripten;
    EMSCRIPTEN_BINDINGS(_tivarfile) {

            register_map<std::string, int>("options_t");

            class_<TIVarFile>("TIVarFile")
                    .constructor<>()
                    .constructor<const std::string &>()

                    .function("getHeader"                , &TIVarFile::getHeader)
                    .function("getVarEntry"              , &TIVarFile::getVarEntry)
                    .function("getType"                  , &TIVarFile::getType)
                    .function("getInstanceChecksum"      , &TIVarFile::getInstanceChecksum)

                    .function("getChecksumValueFromFile" , &TIVarFile::getChecksumValueFromFile)
                    .function("setContentFromData"       , &TIVarFile::setContentFromData)
                    .function("setContentFromString"     , select_overload<void(const std::string&, const options_t&)>(&TIVarFile::setContentFromString))
                    .function("setContentFromString"     , select_overload<void(const std::string&)>(&TIVarFile::setContentFromString))
                    .function("setCalcModel"             , &TIVarFile::setCalcModel)
                    .function("setVarName"               , &TIVarFile::setVarName)
                    .function("getRawContent"            , &TIVarFile::getRawContent)
                    .function("getReadableContent"       , select_overload<std::string(const options_t&)>(&TIVarFile::getReadableContent))
                    .function("getReadableContent"       , select_overload<std::string(void)>(&TIVarFile::getReadableContent))

                    .function("saveVarToFile"            , select_overload<std::string(std::string, std::string)>(&TIVarFile::saveVarToFile))
                    .function("saveVarToFile"            , select_overload<std::string(void)>(&TIVarFile::saveVarToFile))

                    .class_function("loadFromFile", &TIVarFile::loadFromFile)
                    .class_function("createNew", select_overload<TIVarFile(const TIVarType&, const std::string&, const TIModel&)>(&TIVarFile::createNew))
                    .class_function("createNew", select_overload<TIVarFile(const TIVarType&, const std::string&)>(&TIVarFile::createNew))
                    .class_function("createNew", select_overload<TIVarFile(const TIVarType&)>(&TIVarFile::createNew))
            ;
    }
#endif

}