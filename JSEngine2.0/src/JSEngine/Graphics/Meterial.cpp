#include "PCH.h"
#include "Meterial.h"


namespace JSEngine
{

    Material::Material(const Ref<Shader>& shader)
    {
        m_Shader = shader;

    }

    void Material::Bind() const
    {
        m_Shader->Bind();

    }

    Ref<Material> Material::Create(const Ref<Shader>& shader)
    {
        return CreateRef<Material>(shader);
    }


}