#pragma once
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "JSEngine/Core/Core.h"
#include "JSEngine/FileSystem/FileSystem.h"
#include "JSEngine/Platform/Opengl/Mesh.h"



namespace JSEngine
{
    enum class ModelFileType
    {
        OBJ,
        FBX,
        MAX_NUM_MODEL_FILE_TYPE

    };

    class Model
    {
    public:

        Model(const std::string& modelFileName, ModelFileType modelType);
        ~Model() = default;


        static Ref<Model> Create(const std::string& fileName, ModelFileType = ModelFileType::OBJ);
        static TextureType GetTextureTypeFromAITextureType(aiTextureType type);

        const std::vector<Ref<Mesh>>& GetMeshVec() const { return m_Meshes; }

    private:

        void LoadModel(const std::string& path);
        void ProcessModelNode(const aiScene* scene, aiNode* rootNode);
        Ref<Mesh> ProcessMesh(const aiScene* scene, aiMesh* mesh);

        void LoadTextureFromMaterial(const Ref<Mesh>& m, aiMaterial* material, aiTextureType aiType);
        
    private:

        //JSFile m_File;
        
        std::vector<Ref<Mesh>> m_Meshes;
        

    };
}