#include "PCH.h"
#include "Model.h"
#include "JSEngine/Managers/ResourceManager.h"


namespace JSEngine
{
    static const uint32_t s_MeshImportFlags =
        aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
        aiProcess_Triangulate |             // Make sure we're triangles
        aiProcess_SortByPType |             // Split meshes by primitive type
        aiProcess_GenNormals |              // Make sure we have legit normals
        aiProcess_GenUVCoords |             // Convert UVs if required 
        aiProcess_OptimizeMeshes |          // Batch draws where possible
        aiProcess_ValidateDataStructure;    // Validation


    Model::Model(const std::string& modelFileName, ModelFileType /*= ModelFileType::OBJ*/)
    {
        LoadModel(modelFileName);
    }

    Ref<Model> Model::Create(const std::string& fileName, ModelFileType type)
    {
        return CreateRef<Model>(fileName, type);
    }

    TextureType Model::GetTextureTypeFromAITextureType(aiTextureType type)
    {
        switch (type)
        {
        case aiTextureType_NONE:
            break;
        case aiTextureType_DIFFUSE: return TextureType::DIFFUSE;
        case aiTextureType_SPECULAR: return TextureType::SPECULAR;
        case aiTextureType_AMBIENT:
            break;
        case aiTextureType_EMISSIVE:
            break;
        case aiTextureType_HEIGHT:
            break;
        case aiTextureType_NORMALS:
            break;
        case aiTextureType_SHININESS:
            break;
        case aiTextureType_OPACITY:
            break;
        case aiTextureType_DISPLACEMENT:
            break;
        case aiTextureType_LIGHTMAP:
            break;
        case aiTextureType_REFLECTION:
            break;
        case aiTextureType_BASE_COLOR:
            break;
        case aiTextureType_NORMAL_CAMERA:
            break;
        case aiTextureType_EMISSION_COLOR:
            break;
        case aiTextureType_METALNESS:
            break;
        case aiTextureType_DIFFUSE_ROUGHNESS:
            break;
        case aiTextureType_AMBIENT_OCCLUSION:
            break;
        case aiTextureType_UNKNOWN:
            break;
        case _aiTextureType_Force32Bit:
            break;
        default:
            break;
        }

        JS_CORE_ASSERT(false, "Unknow texture type");
        return TextureType();
    }

    void Model::LoadModel(const std::string& fileName)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(g_ResourceMgr.GetCoreFolderPaths(CoreFolderPath::MODEL) + fileName, s_MeshImportFlags);
        JS_CORE_ASSERT(scene, "Error Reading Model File");

        ProcessModelNode(scene, scene->mRootNode);

        for (const auto& elem : m_Meshes)
        {
            elem->SetUpMesh();
        }
    }

    void Model::ProcessModelNode(const aiScene* scene, aiNode* rootNode)
    {
        for (uint32_t  i = 0; i < rootNode->mNumMeshes; ++i)
        {
            m_Meshes.push_back(ProcessMesh(scene, scene->mMeshes[rootNode->mMeshes[i]]));
        }

        for (uint32_t  i = 0; i < rootNode->mNumChildren; ++i)
        {
            ProcessModelNode(scene, rootNode->mChildren[i]);
        }
    }

    Ref<Mesh> Model::ProcessMesh(const aiScene* scene, aiMesh* mesh)
    {
        Ref<Mesh> m = Mesh::Create(MODEL);
        //add vertex
        for (uint32_t  i = 0; i < mesh->mNumVertices; ++i)
        {
            Vertex v;
            v.SetPosition({ mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
            v.SetNormal({ mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });

            if (mesh->mTextureCoords[0])
                v.SetTextureCoor({ mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
            else
                v.SetTextureCoor({ 0.f, 0.f });

            m->AddVertex(v);
        }
        //add texture
        for (uint32_t  i = 0; i < mesh->mNumFaces; ++i)
        {
            auto face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; ++j)
            {
                //m->AddIndex(face.mIndices[j]);
            }
        }

        //add indices
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            auto i = material->GetTextureCount(aiTextureType_DIFFUSE);
            i = material->GetTextureCount(aiTextureType_SPECULAR);
            LoadTextureFromMaterial(m, material, aiTextureType_DIFFUSE);
            LoadTextureFromMaterial(m, material, aiTextureType_SPECULAR);
        }

        return m;
    }

    void Model::LoadTextureFromMaterial(const Ref<Mesh>& m, aiMaterial* material, aiTextureType aiType)
    {
        aiString str;
        material->GetTexture(aiTextureType_SPECULAR, 0, &str);
        aiGetMaterialTexture(material, aiTextureType_DIFFUSE, 0, &str);
        for (uint32_t i = 0; i < material->GetTextureCount(aiType); ++i)
        {
            aiString str;
            material->GetTexture(aiType, i, &str);
            std::string s(str.C_Str());
            Ref<Texture> texture = g_ResourceMgr.Acquire2DTexture(s.substr(0, s.find_first_of(".")));
            texture->SetTextureType(GetTextureTypeFromAITextureType(aiType));
            m->AddTexture(texture);
        }
    }

}