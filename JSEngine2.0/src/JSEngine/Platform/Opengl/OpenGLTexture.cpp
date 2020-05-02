#include "PCH.h"
#include "OpenGLTexture.h"


namespace JSEngine
{
    std::string OpenGLTexture2D::s_FolderPath = "../Resource/Texture/";

    void OpenGLTexture2D::SetFolderPath(const std::string& folderPath)
    {
        s_FolderPath = folderPath;
    }
    OpenGLTexture2D::OpenGLTexture2D(const std::string& fileName, bool flipped) :
        m_TextureData(s_FolderPath, fileName, flipped), m_Slot(0)
    {
        Init();
    }

    void OpenGLTexture2D::Init()
    {
        //glGenTextures(1, &m_RendererID);
        //glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_TextureData.InternalFormat, m_TextureData.Width, m_TextureData.Height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //glTexImage2D(GL_TEXTURE_2D, 0, m_TextureData.Format, m_TextureData.Width, m_TextureData.Height, 0, m_TextureData.Format, GL_UNSIGNED_BYTE, m_TextureData.Data);
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_TextureData.Width, m_TextureData.Height, m_TextureData.DataFormat, GL_UNSIGNED_BYTE, m_TextureData.Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }


    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind() const
    {
        glBindTextureUnit(m_Slot, m_RendererID);
    }

    void OpenGLTexture2D::UnBind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}