#include "PCH.h"
#include "Mesh.h"
#include "JSEngine/Managers/ResourceManager.h"

namespace JSEngine
{

#define MESH_DEBUG_LOG 1
#if MESH_DEBUG_LOG
#define JS_MESH_LOG(...) JS_CORE_TRACE(__VA_ARGS__)
#else
#define HZ_MESH_LOG(...)
#endif

    static const uint32_t s_MeshImportFlags =
        aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
        aiProcess_Triangulate |             // Make sure we're triangles
        aiProcess_SortByPType |             // Split meshes by primitive type
        aiProcess_GenNormals |              // Make sure we have legit normals
        aiProcess_GenUVCoords |             // Convert UVs if required 
        aiProcess_OptimizeMeshes |          // Batch draws where possible
        aiProcess_ValidateDataStructure;    // Validation


    glm::mat4 Mat4FromAssimpMat4(const aiMatrix4x4& matrix)
    {
        glm::mat4 result;
        //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
        result[0][0] = matrix.a1; result[1][0] = matrix.a2; result[2][0] = matrix.a3; result[3][0] = matrix.a4;
        result[0][1] = matrix.b1; result[1][1] = matrix.b2; result[2][1] = matrix.b3; result[3][1] = matrix.b4;
        result[0][2] = matrix.c1; result[1][2] = matrix.c2; result[2][2] = matrix.c3; result[3][2] = matrix.c4;
        result[0][3] = matrix.d1; result[1][3] = matrix.d2; result[2][3] = matrix.d3; result[3][3] = matrix.d4;
        return result;
    }

    Mesh::Mesh(MeshType meshType, const std::string& shaderName) :
        m_MeshType(meshType)
    {
        m_Shader = g_ResourceMgr.AcquireShader(shaderName);
        m_Meterial = Material::Create(m_Shader);

        switch (meshType)
        {
            case TRIANGLE:
                InitTriangle();
                break;
            case QUAD:
                InitQuad();
                break;
            case CUBE:
                InitCube();
                break;
            case MODEL:
                return;
        }
        SetUpMesh();
    }

    Mesh::Mesh(const std::string& fileName, FILE_TYPE fileType, const std::string& shaderName)
        : m_ModelFile(fileName, fileType, READ)
    {
        m_Shader = g_ResourceMgr.AcquireShader(shaderName);
        m_Meterial = Material::Create(m_Shader);

        JS_MESH_LOG("---------- Loading Model {0} ------------", fileName);

        m_ModelFile.Init(g_ResourceMgr.GetCoreFolderPaths(CoreFolderPath::MODEL));

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(m_ModelFile.GetFileFullPath(), s_MeshImportFlags);
        JS_CORE_ASSERT(scene, "Error Reading Model File");

        uint32_t vertexCnt = 0;
        uint32_t indexCnt = 0;
        m_SubMeshesVec.reserve(scene->mNumMeshes);
        for (uint32_t i = 0; i < scene->mNumMeshes; ++i)
        {
            auto& subMesh = m_SubMeshesVec.emplace_back();
            auto& sceneMesh = scene->mMeshes[i];
            subMesh.BaseVertex = vertexCnt; 
            subMesh.BaseIndex  = indexCnt;
            subMesh.IndexCount = sceneMesh->mNumFaces * 3;

            vertexCnt += sceneMesh->mNumVertices;
            indexCnt  += subMesh.IndexCount;

            //assign vertex to main mesh
            for (uint32_t j = 0; j < sceneMesh->mNumVertices; ++j)
            {
                Vertex& v = m_VertexVec.emplace_back();

                if (sceneMesh->HasPositions())
                {
                    v.SetPosition({ sceneMesh->mVertices[j].x, sceneMesh->mVertices[j].y, sceneMesh->mVertices[j].z });
                }

                if (sceneMesh->HasNormals())
                {
                    v.SetNormal({ sceneMesh->mNormals[j].x, sceneMesh->mNormals[j].y, sceneMesh->mNormals[j].z });
                }

                // TODO: Support multiple UV channels
                if (sceneMesh->HasTextureCoords(0))
                {
                    v.SetTextureCoord({ sceneMesh->mTextureCoords[0][j].x, sceneMesh->mTextureCoords[0][j].y });
                }
            }

            //assign index to main mesh
            
            for (uint32_t j = 0; j < sceneMesh->mNumFaces; ++j)
            {
                JS_CORE_ASSERT(sceneMesh->mFaces[i].mNumIndices == 3, "Must have 3 indices.");
                m_IndicesVec.emplace_back( Index{ sceneMesh->mFaces[j].mIndices[0],sceneMesh->mFaces[j].mIndices[1],sceneMesh->mFaces[j].mIndices[2] } );
            }

            if (sceneMesh->mMaterialIndex)
            {
                JS_MESH_LOG("---------------Materials -------");
                //for (uint32_t i = 0; i < sceneMesh->mMa; i++)
                {
                    auto& aiMaterial = scene->mMaterials[sceneMesh->mMaterialIndex];
                    const auto& materialName = aiMaterial->GetName();
                    JS_MESH_LOG("Material Name: {0}", materialName.C_Str());

                    aiString texturePath;
                    bool hasAlbedoMap = aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS;
                    if (hasAlbedoMap)
                    {
                        const std::string& s = texturePath.C_Str();
                        JS_MESH_LOG("Albedo Map Name: {0}", s);
                        Ref<Texture> texture = g_ResourceMgr.Acquire2DTexture(s.substr(0, s.find_first_of(".")));
                        m_Texture2DVec.push_back(texture);
                        subMesh.AlbedoMapIndex = texture->GetTextureID();
                    }
                    else
                    {
                        JS_MESH_LOG("Has no Albedo Map");
                    }

                    bool hasSpecularMap = aiMaterial->GetTexture(aiTextureType_SPECULAR, 0, &texturePath) == AI_SUCCESS;
                    if (hasSpecularMap)
                    {
                        const std::string& s = texturePath.C_Str();
                        JS_MESH_LOG("Specular Map Name: {0}", s);
                        Ref<Texture> texture = g_ResourceMgr.Acquire2DTexture(s.substr(0, s.find_first_of(".")));
                        m_Texture2DVec.push_back(texture);
                        subMesh.SpecularMapIndex = texture->GetTextureID();
                    }
                    else
                    {
                        JS_MESH_LOG("Has no Specular Map");
                    }
                }
                //get texture
                //if (sceneMesh->mMaterialIndex > 0)
                //{
                //    subMesh.MaterialIndex = sceneMesh->mMaterialIndex;
                //    aiMaterial* material = scene->mMaterials[sceneMesh->mMaterialIndex];



                //}
            }
        }
        
        JS_MESH_LOG("---Total Vertex Count: {0} ------", vertexCnt);
        JS_MESH_LOG("---Total Index  Count: {0} ------", indexCnt);
        JS_MESH_LOG("---Total SubMeshes   : {0} ------", m_SubMeshesVec.size());

        JS_MESH_LOG("Start Processing All Nodes");
        ProcessModelNode(scene->mRootNode);
        JS_MESH_LOG("End Processing All Nodes");


        SetUpMesh();

    }

    void Mesh::LoadTextureFromMaterial(const Ref<Mesh>& m, aiMaterial* material, aiTextureType aiType)
    {
        for (uint32_t i = 0; i < material->GetTextureCount(aiType); ++i)
        {
            aiString str;
            material->GetTexture(aiType, i, &str);
            std::string s(str.C_Str());
            Ref<Texture> texture = g_ResourceMgr.Acquire2DTexture(s.substr(0, s.find_first_of(".")));
            //texture->SetTextureType(GetTextureTypeFromAITextureType(aiType));
            m_Texture2DVec.push_back(texture);
        }
    }


    void Mesh::ProcessModelNode(aiNode* node, const glm::mat4& parentTransform, uint32_t level)
    {
        glm::mat4 tranform = parentTransform * Mat4FromAssimpMat4(node->mTransformation);
        for (uint32_t i = 0; i < node->mNumMeshes; ++i)
        {
            auto& nodeMesh = node->mMeshes[i];
            auto& subMesh = m_SubMeshesVec[nodeMesh];

            subMesh.NodeName = node->mName.C_Str();
            subMesh.Transform = tranform;
            JS_MESH_LOG("Node Name: {0}", subMesh.NodeName);

        }

        for (uint32_t i = 0; i < node->mNumChildren; ++i)
        {
            ProcessModelNode(node->mChildren[i], tranform, level + 1);
        }

    }

    SubMesh Mesh::ProcessMesh(const aiScene* scene, aiMesh* mesh)
    {
        //SubMesh subMesh;
        ////add vertex
        //for (uint32_t i = 0; i < mesh->mNumVertices; ++i)
        //{
        //    Vertex v;
        //    v.SetPosition({ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
        //    v.SetNormal({ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });

        //    if (mesh->mTextureCoords[0])
        //        v.SetTextureCoor({ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
        //    else
        //        v.SetTextureCoor({ 0.f, 0.f });

        //    m->AddVertex(v);
        //}
        return SubMesh();
    }

    void Mesh::SetUpMesh()
    {
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
        m_VAO->AddIndexBuffer(IndexBuffer::Create((uint32_t*)m_IndicesVec.data(), (uint32_t)m_IndicesVec.size() * 3));
        
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
    void Mesh::InitTriangle()
    {
        m_VertexVec.reserve(3);
        m_IndicesVec.reserve(3);

        m_VertexVec.push_back({ -0.5f, -0.5f, 0.f,  0.f, 0.f, 1.f,  0.f,  0.f });
        m_VertexVec.push_back({ 0.15f,  -0.5f, 0.f,  0.f, 0.f, 1.f,  1.f,  0.f });
        m_VertexVec.push_back({ 0.f,    0.5f, 0.f,  0.f, 0.f, 1.f,  0.5f, 1.f });

        m_IndicesVec.push_back(Index{  0, 1, 2 });

        SubMesh& mesh = m_SubMeshesVec.emplace_back();
        mesh.BaseIndex = 0;
        mesh.BaseVertex = 0;
        mesh.IndexCount = 3;
        mesh.VertexCount = 3;

        
    }
    void Mesh::InitQuad()
    {
        m_VertexVec.reserve(4);
        m_IndicesVec.reserve(6);

        m_VertexVec.push_back({ -0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f,  0.f, 0.f });
        m_VertexVec.push_back({ 0.5f,  -0.5f, 0.f, 0.f, 0.f, 1.f,  1.f, 0.f });
        m_VertexVec.push_back({ 0.5f,   0.5f, 0.f, 0.f, 0.f, 1.f,  1.f, 1.f });
        m_VertexVec.push_back({ -0.5f , 0.5f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f });

        m_IndicesVec.push_back(Index{ 0, 1, 2 });
        m_IndicesVec.push_back(Index{ 0, 2, 3 });
        SubMesh& mesh = m_SubMeshesVec.emplace_back();
        mesh.IndexCount  = 6;
        mesh.VertexCount = 4;

    }
    void Mesh::InitCube()
    {
        JS_MESH_LOG("---------- Loading Cube ------------");

        m_VertexVec.reserve(24);
        m_IndicesVec.reserve(36);

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

        uint32_t  offset = 0;
        for (uint32_t i = 0; i < 6; ++i)
        {
            m_IndicesVec.emplace_back(Index{ offset + 0,offset + 1, offset + 2 });
            m_IndicesVec.emplace_back(Index{ offset + 0,offset + 2, offset + 3 });
            offset += 4;
        }

        SubMesh& mesh = m_SubMeshesVec.emplace_back();
        mesh.IndexCount  = 36;
        mesh.VertexCount = 24;
        
        auto diffuse = g_ResourceMgr.Acquire2DTexture("container2");
        auto specular = g_ResourceMgr.Acquire2DTexture("container2_specular");

        m_Texture2DVec.push_back(diffuse);
        m_Texture2DVec.push_back(specular);

        mesh.AlbedoMapIndex = diffuse->GetTextureID();
        mesh.SpecularMapIndex = specular->GetTextureID();

        JS_MESH_LOG("---------- End Loading Cube ------------");
    }

    Ref<Mesh> Mesh::Create(MeshType meshType, const std::string& shader)
    {
        return CreateRef<Mesh>(meshType, shader);
    }

    Ref<Mesh> Mesh::Create(const std::string& fileName, const std::string& shader)
    {
        return CreateRef<Mesh>(fileName, FILE_TYPE::OBJ, shader);
    }

}