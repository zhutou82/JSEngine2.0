#pragma once
#include "OpenGLBuffer.h"
#include "OpenGLVertexArray.h"
#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "JSEngine/Graphics/Meterial.h"


namespace JSEngine
{
    enum MeshType
    {
        TRIANGLE,
        QUAD,
        CUBE,
        SPHARE,
        MAX_NUM_OF_MESH_TYPE
    };

    class Vertex
    {
        static constexpr const uint32_t s_Count = 8;
        static constexpr const uint32_t s_ElementSize = sizeof(float);
        static constexpr const uint32_t s_Size = s_Count * s_ElementSize;

    public:
        Vertex(float posX = 0.f, float posY = 0.f, float posZ = 0.f, 
               float normX = 0.f, float normY = 0.f, float normZ = 0.f,
               float s = 0.f, float t = 0.f) :
            m_Pos(posX, posY ,posZ),
            m_Normal(normX, normY, normZ),
            m_TextCoor(s, t)
        {
            
        }

    public:
        void SetPosition    (const glm::vec3& pos)   { m_Pos = pos; }
        void SetNormal      (const glm::vec3& norm)  { m_Normal= norm; }
        const float* GetData() const                 { return &m_Pos[0]; }


    public:
        static uint32_t GetSize       () { return s_Size; }
        static uint32_t GetCount      () { return  s_Count; }
        static uint32_t GetElementSize() { return s_ElementSize; }

    private:

        glm::vec3 m_Pos;
        glm::vec3 m_Normal;
        glm::vec2 m_TextCoor;
        
    };


    class Indices
    {
    public:
        Indices() {}
        ~Indices() { if (m_Data) free(m_Data); }

        void SetData(uint32_t* data, uint32_t count)
        {
            m_Count = count;
            m_Data = (uint32_t*)calloc(count, sizeof(uint32_t));
            memcpy(m_Data, data, count * sizeof(uint32_t));
        }

        uint32_t GetCount() const { return m_Count; }
        uint32_t* GetData() const { return m_Data; }

    private:
        uint32_t m_Count;
        uint32_t* m_Data;
    };

    class Mesh
    {
        
    public:

        Mesh(MeshType = TRIANGLE);
        ~Mesh();
        void AttachShader(uint32_t shaderID);
        void AttachMeterial(uint32_t meterialID);
        uint32_t GetShaderID() const;
        uint32_t GetMeterialID() const;

        void AttachMeterial(const Ref < Meterial>& meterial) { m_Meterial = meterial;  }
        const Ref<Meterial>& GetMeterial() const {  return m_Meterial; }

        void AddTexture();

        void SetScale(const glm::vec3& scaleV);
        void SetScale(float x, float y, float z);
        void SetScale(float scale);

        void SetPosition(const glm::vec3& posV);
        void SetPosition(float x, float y, float z);

        void SetRotation(float degree, const glm::vec3& rotationAxis = glm::vec3(0, 0, 1)) { m_RotationDegree = degree; m_RotationAxis = rotationAxis; }
        float GetRotation() const { return m_RotationDegree;  }


        glm::vec3 GetScale() const                                     { return m_Scale;          }
        glm::vec3 GetPosition() const                                  { return m_Position;       }
        glm::vec3 GetRotationAxis() const                              { return m_RotationAxis;   }
        float GetRotationDegree() const                                { return m_RotationDegree; }
        const glm::mat4& GetModelMatrix() const                        { return m_ModelMat;       }
        const glm::mat4& ConstructModelMatrix();

        const Ref<VertexArray>& GetVAO() const { return m_VAO; }
        const Ref<Texture>& GetTexture() const { return m_Texture; }
        
        void Bind() const;
        
        static Ref<Mesh> Create(MeshType meshType = TRIANGLE);

    private:

        void InitTriangle();
        void InitQuad();
        void InitCube();

    private:

        MeshType            m_MeshType;

        Ref<VertexArray>   m_VAO;

        
        std::vector<Vertex> m_VertexVec;
        Indices m_Indices;
        Ref<Texture> m_Texture;
        Ref<Texture2D> m_2DTexture;

        glm::mat4 m_ModelMat;

        glm::vec3 m_Scale;
        glm::vec3 m_Position;
        glm::vec3 m_RotationAxis;

        float m_RotationDegree;

        uint32_t m_AttachedShaderID;
        uint32_t m_AttachedMeterialID;

        Ref<Meterial> m_Meterial;

    };
}