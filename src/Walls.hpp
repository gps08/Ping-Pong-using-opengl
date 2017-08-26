#ifndef PONG_WALLS_HPP
#define PONG_WALLS_HPP

class Walls
{
    private:
    GLuint VAO,VBO,EBO;

    public:
    Walls()
    {
        float vert[]= {-1.0f,1.0f, 1.0f,1.0f, 1.0f,-1.0f, -1.0f,-1.0f, -0.95f,0.95f, 0.95f,0.95f, 0.95f,-0.95f, -0.95f,-0.95f};
        unsigned int indices[] = {0,4,1, 4,1,5, 0,4,3, 4,3,7, 7,3,6, 2,6,3, 2,6,5, 2,5,1};
        glGenVertexArrays(1, &VAO); glGenBuffers(1, &VBO); glGenBuffers(1, &EBO);
        glBindVertexArray(VAO); glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vert),vert,GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
        glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,0); glBindVertexArray(0); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }

    void draw()
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,24,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
    }

    ~Walls(){ glDeleteBuffers(1,&VBO); glDeleteBuffers(1,&EBO); glDeleteBuffers(1,&VAO); }
};

#endif //PONG_WALLS_HPP