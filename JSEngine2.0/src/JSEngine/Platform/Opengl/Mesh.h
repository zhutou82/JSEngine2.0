#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
        MODEL,
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
        void SetTextureCoor(const glm::vec2& textCoor) { m_TextCoor = textCoor; }
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

    struct Index
    {
        uint32_t V1, V2, V3;
    };

    struct SubMesh
    {
        uint32_t BaseVertex = 0;
        uint32_t BaseIndex = 0;

        uint32_t VertexCount = 0;
        uint32_t IndexCount = 0;

        uint32_t MaterialIndex = 0;

        uint32_t AlbedoMapIndex = 0;
        uint32_t SpecularMapIndex = 0;

        std::string NodeName;

        glm::mat4 Transform;
    };


    class Mesh
    {
        
    public:

        Mesh(MeshType = TRIANGLE);
        Mesh(const std::string& fileName, FILE_TYPE f = FILE_TYPE::OBJ);
        ~Mesh() = default;

        void SetUpMesh();

        void AttachShader(uint32_t shaderID);
        void AttachMeterial(uint32_t meterialID);
        uint32_t GetShaderID() const;
        uint32_t GetMeterialID() const;

        void AttachMeterial(const Ref < Material>& meterial) { m_Meterial = meterial;  }
        const Ref<Material>& GetMeterial() const {  return m_Meterial; }

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

        const std::vector<Ref<Texture>>& GetTextures() const {return m_Texture2DVec; }
       
        void Bind() const;

        void AddVertex(const Vertex& vertex) { m_VertexVec.push_back(vertex); }
        void AddTexture(const Ref<Texture>& texture) { m_Texture2DVec.push_back(texture); }
        //void AddIndex(uint32_t index) { m_IndicesVec.push_back(index); }

        const std::vector<SubMesh>& GetSubMeshes() const { return m_SubMeshesVec; }

    public:

        static Ref<Mesh> Create(MeshType meshType = TRIANGLE);
        static Ref<Mesh> Create(const std::string& fileName);

    private:

        void InitTriangle();
        void InitQuad();
        void InitCube();


        void ProcessModelNode(aiNode* rootNode, const glm::mat4& transform = glm::mat4(1.f), uint32_t level = 0);
        SubMesh ProcessMesh(const aiScene* scene, aiMesh* mesh);

        void LoadTextureFromMaterial(const Ref<Mesh>& m, aiMaterial* material, aiTextureType aiType);


    private:

        MeshType            m_MeshType;
        std::vector<SubMesh> m_SubMeshesVec;
        std::vector<Vertex>  m_VertexVec;
        std::vector<Ref<Texture> > m_Texture2DVec;
        std::vector<Index> m_IndicesVec;

        Ref<VertexArray>   m_VAO;

        Ref<Texture> m_Texture;
        Ref<Texture2D> m_2DTexture;

        glm::mat4 m_ModelMat;
        glm::vec3 m_Scale;
        glm::vec3 m_Position;
        glm::vec3 m_RotationAxis;

        float m_RotationDegree;

        uint32_t m_AttachedShaderID;
        uint32_t m_AttachedMeterialID;

        Ref<Material> m_Meterial;
        Ref<Shader> m_Shader;

        JSFile m_ModelFile;

    };
}