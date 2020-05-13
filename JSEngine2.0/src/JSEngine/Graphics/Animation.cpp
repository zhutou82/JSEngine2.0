#include "PCH.h"
#include "Animation.h"

namespace JSEngine
{
    Animation2D::Animation2D(const Ref<Texture>& texture, glm::ivec2 dim)
        : m_Texture(texture), m_Dim(dim), m_CurrentPlayingFrame(0)
    {
        m_TextureCoordVec.reserve(4);
        //compute SubTexutre Coord
        for (int i = 0; i < m_Dim.y; ++i)
        {
            for (int j = 0; j < m_Dim.x; ++j)
            {
                glm::vec4 uvs;
                int xTile = j % m_Dim.x;
                int yTile = i / m_Dim.x;

                uvs.x = xTile / (float)m_Dim.x;
                uvs.y = yTile / (float)m_Dim.y;
                uvs.z = 1.f / m_Dim.x;
                uvs.w = 1.f / m_Dim.y;

                std::vector<glm::vec2> coord
                {
                    { uvs.x        , uvs.y },
                    { uvs.x + uvs.z, uvs.y },
                    { uvs.x + uvs.z, uvs.y + uvs.w },
                    { uvs.x        , uvs.y + uvs.w }
                };
                m_IndexTextureCoordMap[i * m_Dim.x + j] = coord;
            }
        }

    }
    void Animation2D::OnUpdate(TimeStep delta)
    {
        m_Delta = delta;
    }
    void Animation2D::Play(uint32_t startFrame, uint32_t endFrame, float animationSpeed, bool isMirror)
    {

        JS_CORE_ASSERT((startFrame >= 0 && startFrame <= m_Dim.x * m_Dim.y &&
                        endFrame   >= 0 && endFrame   <= m_Dim.x * m_Dim.y), 
                        "Animation Frame Out of Bound");

        if (m_StartPlaying)
        {
            m_StartFrame = startFrame;
            m_EndFrame = endFrame;
            m_CurrentPlayingFrame = (float)m_StartFrame;
            m_StartPlaying = false;
        }

        if (m_IsPlaying)
        {
            //rate
            m_CurrentPlayingFrame += m_Delta * (1.f / animationSpeed);
            if (m_CurrentPlayingFrame >= (float)m_EndFrame)
            {
                m_CurrentPlayingFrame = (float)startFrame;
            }
            m_TextureCoordVec = m_IndexTextureCoordMap[(int)m_CurrentPlayingFrame];
        }
    }
    void Animation2D::Stop()
    {
        m_IsPlaying = false;
        m_CurrentPlayingFrame = (float)m_StartFrame;
    }

    void Animation2D::Pause()
    {
        m_IsPlaying = false;
    }

    void Animation2D::Resume()
    {
        m_IsPlaying = true;
    }

    void Animation2D::ReStart()
    {
        Stop();
        Resume();
    }
}