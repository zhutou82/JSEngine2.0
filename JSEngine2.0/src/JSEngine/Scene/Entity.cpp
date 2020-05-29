#include "PCH.h"
#include "Entity.h"

namespace JSEngine
{
    Entity::Entity(const std::string& name)
        : m_Name(name)
    {
        ConstructModelMatrix();
    }
    void Entity::ConstructModelMatrix()
    {
        m_Transform = glm::mat4(1.f);
        m_Transform = glm::translate(m_Transform, m_Position);
        m_Transform = glm::scale(m_Transform, m_Scale);
        m_Transform = glm::rotate(m_Transform, glm::radians(m_RotationDegree), m_RotationAxis);

    }
}