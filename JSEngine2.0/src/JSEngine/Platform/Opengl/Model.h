#pragma once


namespace JSEngine
{
    class Model
    {
        


    public:
        Model();
        ~Model();
        const float * GetVextex() const { return m_Vertex; }
        unsigned int GetVBO() const { return m_VBO; }
        void SetVBO(unsigned int vbo) { m_VBO = vbo; }
        //float* GetVertex() const { return m_Vertex; }


    private:
        float m_Vertex[32];

        size_t m_SizeOfVertex;
        unsigned int m_VBO;
        

    };
}