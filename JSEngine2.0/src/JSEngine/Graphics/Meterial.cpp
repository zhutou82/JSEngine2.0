#include "PCH.h"
#include "Meterial.h"


namespace JSEngine
{
    uint32_t Meterial::s_UniqueID = 0;

    Meterial::Meterial(const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shinese)
        : m_Color(color), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Shinese(shinese), m_ID(s_UniqueID++)
    {

    }

    Ref<Meterial> Meterial::Create()
    {
        return CreateRef<Meterial>();
    }

}