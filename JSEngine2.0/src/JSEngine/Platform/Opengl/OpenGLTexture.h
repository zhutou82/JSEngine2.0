#pragma once
#include "JSEngine/Graphics/Texture.h"
#include "JSEngine/Platform/Opengl/OpenGLContext.h"
#include "JSEngine/FileSystem/FileSystem.h"
#include "stb_image.h"


namespace JSEngine
{
    struct TextureData
    {

        TextureData() {};
        TextureData(const std::string& folderPath, const std::string& fileName, bool flipped) :
            TextureFile(fileName, PNG, READ), Width(0), Height(0), NrChannels(0), Data(NULL)
        {
            TextureFile.Init(folderPath);
            stbi_set_flip_vertically_on_load(flipped);
            Data = stbi_load(TextureFile.GetFileFullPath().c_str(), &Width, &Height, &NrChannels, 0);

            JS_CORE_ASSERT(Data, "Failed to load texture");

            if (NrChannels == 1)
            {
                InternalFormat = GL_RED;
                DataFormat = GL_RED;
            }
            if (NrChannels == 3)
            {
                InternalFormat = GL_RGB8;
                DataFormat = GL_RGB;
            }
                
            if (NrChannels == 4)
            {
                InternalFormat = GL_RGBA8;
                DataFormat = GL_RGBA;
            }
               
        }
        
        ~TextureData()
        {
            if(Data) stbi_image_free(Data);
        }
        JSFile TextureFile;
        int Width;
        int Height;
        int NrChannels;
        uint32_t InternalFormat;
        uint32_t DataFormat;
        unsigned char* Data;
    };

    class OpenGLTexture2D : public Texture2D
    {
        static std::string s_FolderPath;

    public:
        static void SetFolderPath(const std::string& folderPath);

        OpenGLTexture2D() {};
        OpenGLTexture2D(const std::string& fileName, bool filp = true);
        ~OpenGLTexture2D();

        void Init();
        
        virtual uint32_t GetWidth() const override { return m_TextureData.Width; }
        virtual uint32_t GetHeight() const override { return m_TextureData.Height; }


        virtual void Bind() const override;
        virtual void UnBind() const override;    

        uint32_t GetSlot() const { return m_Slot; }
        void SetSlot(uint32_t val) { m_Slot = val; }

    private:

        TextureData m_TextureData;
        unsigned m_RendererID;
        uint32_t m_Slot;

    };


}