#include "PCH.h"
#include "OpenGLTexture.h"
#include "JSEngine/Managers/ResourceManager.h"


namespace JSEngine
{

    uint32_t OpenGLTexture2D::s_UniqueTextureID = 0;

    OpenGLTexture2D::OpenGLTexture2D(const std::string& fileName, const glm::ivec2& dim, bool flipped) :
        m_TextureData(g_ResourceMgr.GetCoreFolderPaths(CoreFolderPath::ASSETS), fileName, flipped), m_Slot(0), m_TexutureID(0), m_Dim(dim)
    {
        Init();
        m_TexutureID = s_UniqueTextureID;
        ++s_UniqueTextureID;
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

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }

    void OpenGLTexture2D::UnBind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLTexture2D::SetDimension(const glm::ivec2& dimension)
    {
        m_Dim = dimension;  
        //compute SubTexutre Coord
        for (int i = 0; i < m_Dim.y; ++i)
        {
            for (int j = 0; i < m_Dim.x; ++j)
            {
                glm::vec4 uvs;
                int xTile = j % m_Dim.x;
                int yTile = i / m_Dim.x;

                uvs.x = xTile / (float)m_Dim.x;
                uvs.y = yTile / (float)m_Dim.y;
                uvs.z = 1.f / m_Dim.x;
                uvs.w = 1.f / m_Dim.y;

                glm::vec2 coord[4];

                coord[0] = { uvs.x        , uvs.y };
                coord[1] = { uvs.x + uvs.z, uvs.y };
                coord[2] = { uvs.x + uvs.z, uvs.y + uvs.w };
                coord[3] = { uvs.x        , uvs.y + uvs.w };

                m_SubTextureCoordVec.insert({ i * m_Dim.x + j, coord });

            }

        }
    }

    const glm::vec2* OpenGLTexture2D::GetSubTextureCoord(const glm::ivec2& index) const
    {
        JS_CORE_ASSERT( (index.x >= m_Dim.x && index.y <= m_Dim.y), "Index for SubTexutre out of bound");
        return m_SubTextureCoordVec.find(index.y * m_Dim.x + index.x)->second;
    }

}