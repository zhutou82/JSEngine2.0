#pragma once
#include <vector>
#include <unordered_map>

#include "glm/glm.hpp"
#include "Texture.h"
#include "JSEngine/Core/TimeStep.h"

namespace JSEngine
{
    class Animation2D
    {
    public:
        Animation2D(const Ref<Texture>& texture, glm::ivec2 dim);

        const std::vector<glm::vec2>& GetTextureCoord() const { return m_TextureCoordVec; }
        
        void OnUpdate(TimeStep delta);
        void Play(uint32_t startFrame, uint32_t endFrame, float animationSpeed, bool isMirror = false);


        void Stop();
        void Pause();
        void Resume();
        void ReStart();
    private:

        Ref<Texture> m_Texture;
        uint32_t m_StartFrame;
        uint32_t m_EndFrame;
        float m_CurrentPlayingFrame;
        
        glm::ivec2 m_Dim;
        std::vector<glm::vec2> m_TextureCoordVec;
        
        std::unordered_map<uint32_t, std::vector<glm::vec2> > m_IndexTextureCoordMap;

        float m_Delta;
        float m_Speed;

        bool m_StartPlaying = true;
        bool m_IsPlaying = true;
    };



}
