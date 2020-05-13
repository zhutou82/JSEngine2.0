#include "PCH.h"
#include "SubTexture2D.h"

namespace JSEngine
{



    SubTexture2D::SubTexture2D(const Ref<Texture>& texture, const std::vector<glm::vec2>& coord)
    {
        m_TextureCoord.reserve(4);
        m_Texture = texture;
        m_TextureCoord = coord;
    }

    Ref<SubTexture2D> SubTexture2D::Create(const Ref<Texture>& texture, const glm::ivec2& dim, const glm::ivec4& indexWithUnit)
    {
        //JS_CORE_INFO("{0}", (indexWithUnit.x >= dim.x && indexWithUnit.y <= dim.y));
        JS_CORE_ASSERT( (indexWithUnit.x <= dim.x && indexWithUnit.y <= dim.y), "Subtexture coord out of bound");

        glm::vec4 uvs; 
        int xTile = indexWithUnit.x % dim.x;
        int yTile = (indexWithUnit.y * dim.x) / dim.x;

        uvs.x = xTile / (float)dim.x;
        uvs.y = yTile / (float)dim.y;
        uvs.z = (1.f / dim.x) * indexWithUnit.z; 
        uvs.w = (1.f / dim.y) * indexWithUnit.w;

        std::vector<glm::vec2> m =
        {
                    { uvs.x        , uvs.y },
                    { uvs.x + uvs.z, uvs.y },
                    { uvs.x + uvs.z, uvs.y + uvs.w },
                    { uvs.x        , uvs.y + uvs.w }
        };
        return CreateRef<SubTexture2D>(texture, m);
    }

}