#include "PCH.h"
#include "Mesh.h"
#include "JSEngine/Managers/ResourceManager.h"

namespace JSEngine
{

    Mesh::Mesh(MeshType meshType) :
        m_MeshType(meshType), m_ModelMat(1.f), m_RotationDegree(0), m_Scale({ 1, 1, 1 }), m_Position({0,0,0})
    {
        m_Texture = g_ResourceMgr.Acquire2DTexture();
        m_Meterial = Meterial::Create();

        switch (meshType)
        {
            case JSEngine::TRIANGLE:
                InitTriangle();
                break;
            case JSEngine::QUAD:
                InitQuad();
                break;
            case JSEngine::CUBE:
                InitCube();
                break;
        }

        m_VAO = VertexArray::Create();
        Ref<VertexBuffer> vbo = VertexBuffer::Create(m_VertexVec[0].GetData(), Vertex::GetSize() * (uint32_t)m_VertexVec.size());

        Layout layout =
        {
            {ElementType::VEC3, 0, "pos"},
            {ElementType::VEC3, 1, "normal"},
            {ElementType::VEC2, 2, "textCoor"},
        };
        vbo->SetLayout(layout);
        m_VAO->AddBuffer(vbo);

        m_VAO->AddIndexBuffer(IndexBuffer::Create(m_Indices.GetData(), m_Indices.GetCount()));

    }

    Mesh::~Mesh()
    {
        
    }

    void Mesh::AttachShader(uint32_t shaderID)
    {
        m_AttachedShaderID = shaderID;
    }

    void Mesh::AttachMeterial(uint32_t meterialID)
    {
        m_AttachedMeterialID = meterialID;
    }

    uint32_t Mesh::GetShaderID() const
    {
        return m_AttachedShaderID;
    }

    uint32_t Mesh::GetMeterialID() const
    {
        return m_AttachedMeterialID;
    }


    void Mesh::SetScale(const glm::vec3& scaleV)
    {
        m_Scale = scaleV;
        m_ModelMat = glm::scale(glm::mat4(1.f), m_Scale);
    }

    void Mesh::SetScale(float x, float y, float z)
    {
        m_Scale.x = x;
        m_Scale.y = y;
        m_Scale.z = z; 
    }

    void Mesh::SetScale(float scale)
    {
        m_Scale.x = scale;
        m_Scale.y = scale;
        m_Scale.z = scale;
    }

    void Mesh::SetPosition(const glm::vec3& posV)
    {
        m_Position = posV;
    }

    void Mesh::SetPosition(float x, float y, float z)
    {
        m_Position.x = x;
        m_Position.y = y;
        m_Position.z = z;
    }

    const glm::mat4& Mesh::ConstructModelMatrix()
    {
        m_ModelMat = glm::mat4(1.f);
        m_ModelMat = glm::translate(m_ModelMat, m_Position);
        m_ModelMat = glm::scale(m_ModelMat, m_Scale);
        m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_RotationDegree), m_RotationAxis);
        return m_ModelMat;
    }

    void Mesh::Bind() const
    {
        m_VAO->Bind();
        m_VAO->GetIndexBuffer()->Bind();
    }

    Ref<Mesh> Mesh::Create(MeshType meshType)
    {
        return std::make_shared<Mesh>(meshType);
    }

    void Mesh::InitTriangle()
    {
        m_VertexVec.reserve(3);
        m_VertexVec.push_back({ -0.5f, -0.5f, 0.f,  0.f, 0.f, 1.f,  0.f,  0.f });
        m_VertexVec.push_back({ 0.15f,  -0.5f, 0.f,  0.f, 0.f, 1.f,  1.f,  0.f });
        m_VertexVec.push_back({ 0.f,    0.5f, 0.f,  0.f, 0.f, 1.f,  0.5f, 1.f });

        unsigned int indices[] =
        {
            0, 1, 2,
        };
        //ini IBO
        m_Indices.SetData(indices, sizeof(indices) / sizeof(indices[0]));
    }

    void Mesh::InitQuad()
    {
        m_VertexVec.reserve(4);
        m_VertexVec.push_back({ -0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f,  0.f, 0.f });
        m_VertexVec.push_back({ 0.5f,  -0.5f, 0.f, 0.f, 0.f, 1.f,  1.f, 0.f });
        m_VertexVec.push_back({ 0.5f,   0.5f, 0.f, 0.f, 0.f, 1.f,  1.f, 1.f });
        m_VertexVec.push_back({ -0.5f , 0.5f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f });

        uint32_t indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };
        m_Indices.SetData(indices, sizeof(indices) / sizeof(indices[0]));
    }

    void Mesh::InitCube()
    {
        m_VertexVec.reserve(24);

        m_VertexVec.push_back({-0.5f, -0.5f, -0.5f,  0.f, 0.f, -1.f,   0.0f, 0.0f});   
        m_VertexVec.push_back({ 0.5f, -0.5f, -0.5f,  0.f, 0.f, -1.f,   1.0f, 0.0f});   
        m_VertexVec.push_back({ 0.5f,  0.5f, -0.5f,  0.f, 0.f, -1.f,   1.0f, 1.0f});   
        m_VertexVec.push_back({-0.5f,  0.5f, -0.5f,  0.f, 0.f, -1.f,   0.0f, 1.0f}); 

        m_VertexVec.push_back({-0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,    0.0f, 0.0f });  
        m_VertexVec.push_back({ 0.5f, -0.5f,  0.5f,  0.f, 0.f, 1.f,    1.0f, 0.0f });  
        m_VertexVec.push_back({ 0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,    1.0f, 1.0f });  
        m_VertexVec.push_back({-0.5f,  0.5f,  0.5f,  0.f, 0.f, 1.f,    0.0f, 1.0f });  

        m_VertexVec.push_back({-0.5f,  0.5f,  0.5f,  -1.f, 0.f, 0.f,   1.0f, 0.0f});   
        m_VertexVec.push_back({-0.5f,  0.5f, -0.5f,  -1.f, 0.f, 0.f,   1.0f, 1.0f});   
        m_VertexVec.push_back({-0.5f, -0.5f, -0.5f,  -1.f, 0.f, 0.f,   0.0f, 1.0f});   
        m_VertexVec.push_back({-0.5f, -0.5f,  0.5f,  -1.f, 0.f, 0.f,   0.0f, 0.0f});   

        m_VertexVec.push_back({ 0.5f,  0.5f,  0.5f,  1.f, 0.f, 0.f,    1.0f, 0.0f });  
        m_VertexVec.push_back({ 0.5f,  0.5f, -0.5f,  1.f, 0.f, 0.f,    1.0f, 1.0f });  
        m_VertexVec.push_back({ 0.5f, -0.5f, -0.5f,  1.f, 0.f, 0.f,    0.0f, 1.0f });  
        m_VertexVec.push_back({ 0.5f, -0.5f,  0.5f,  1.f, 0.f, 0.f,    0.0f, 0.0f });  

        m_VertexVec.push_back({-0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,   0.0f, 1.0f});   
        m_VertexVec.push_back({ 0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,   1.0f, 1.0f});   
        m_VertexVec.push_back({ 0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,   1.0f, 0.0f});   
        m_VertexVec.push_back({-0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,   0.0f, 0.0f});   

        m_VertexVec.push_back({-0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    0.0f, 1.0f });  
        m_VertexVec.push_back({ 0.5f,  0.5f, -0.5f,  0.f, 1.f, 0.f,    1.0f, 1.0f });  
        m_VertexVec.push_back({ 0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,    1.0f, 0.0f });  
        m_VertexVec.push_back({-0.5f,  0.5f,  0.5f,  0.f, 1.f, 0.f,    0.0f, 0.0f });  


        uint32_t indices[] =
        {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            8, 9, 10,
            8, 10,11,
            12,13,14,
            12,14,15,
            16,17,18,
            16,18,19,
            20,21,22,
            20,22,23,
        };

        m_Indices.SetData(indices, sizeof(indices) / sizeof(indices[0]));

    }

}