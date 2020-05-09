#include "PCH.h"
#include "FileSystem.h"

namespace JSEngine
{

    JSFile::JSFile(const std::string& fileName, FILE_TYPE fileType, FILE_MODE mode)
        : 
    m_FileName(fileName),
    m_FileType(FILETYPE_ARR[fileType]),
    m_FileMode(FILEMODE_ARR[mode])
    {

    }

    void JSFile::Init(const std::string& folderPath)
    {
        m_FileFullPath = folderPath + m_FileName + m_FileType;
        m_File = fopen(m_FileFullPath.c_str(), m_FileMode.c_str());
        JS_CORE_ASSERT(m_File, "File not found/corrupted");
    }

    JSFile::~JSFile()
    {
        JS_CORE_ASSERT(m_File, "File is not being initialized");
        fclose(m_File);
    }

    void JSFile::SetFile(const std::string& fileName, FILE_TYPE fileType, FILE_MODE mode)
    {
        m_FileName = fileName;
        m_FileType = FILETYPE_ARR[fileType];
        m_FileMode = FILEMODE_ARR[mode];
    }

}