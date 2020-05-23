#pragma once
#include <string>

#include "JSEngine/Core/Core.h"


namespace JSEngine
{
    enum FILE_TYPE
    {
        TEXT,
        XML ,
        BIN ,
        PNG ,
        JPEG,
        VS,
        FS,
        GLSL,
        JSON,
        OBJ,
        FBX,
        NUM_OF_FILE_TYPE
    };
    static constexpr const char* FILETYPE_ARR[NUM_OF_FILE_TYPE] =
    {
        ".txt",
        ".xml",
        ".bin",
        ".png",
        ".jpeg",
        ".vs",
        ".fs",
        ".glsl",
        ".json",
        ".obj",
        ".fbx"

    };

    enum FILE_MODE
    {
        READ_BINARY,
        WRITE_BINARY,
        WRITE,
        READ,
        APPEND,
        NUM_OF_FILE_MODE
    };
    static constexpr const char* FILEMODE_ARR[NUM_OF_FILE_MODE] =
    {
        "wb",
        "rb",
        "w",
        "r",
        "a"
    };

    class JSFile
    {
    public:
        JSFile() : m_File(NULL) {}
        JSFile(const std::string& fileName, FILE_TYPE fileType, FILE_MODE mode = WRITE);
        ~JSFile();

    public:

        void SetFile(const std::string& fileName, FILE_TYPE fileType, FILE_MODE mode = WRITE);
        FILE* GetFile() const                       { return m_File;         }
        const std::string& GetFileName()            { return m_FileName;     }
        const std::string& GetFileExtension() const { return m_FileType;     }
        const std::string& GetFileMode()      const { return m_FileMode;     }
        const std::string& GetFileFullPath()  const { return m_FileFullPath; }
        void Init(const std::string& folderPath);


    private:
        FILE*        m_File;
        std::string  m_FileName;
        std::string  m_FileType;
        std::string  m_FileMode;
        std::string  m_FileFullPath;
    };


}