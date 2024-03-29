#ifndef PONG_SLIDER_HPP
#define PONG_SLIDER_HPP

#include "Ball.hpp"

class Slider
{
    private:
    GLuint VAO,VBO,EBO,shaderProgram; GLfloat vert[8],height,width;

    public:
    Slider(GLfloat h,GLfloat w) : vert{-1*(w/2),-0.88f,w/2,-0.88f,-1*(w/2),-0.88f-h,w/2,-0.88f-h}
    {
        unsigned int indices[] = {0,1,2,1,2,3}; height=h; width=w;
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
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
    }

    void moveLeft()
    {
        if(vert[0]<=-0.95) return;
        for(int i=0;i<8;i+=2) vert[i]-=0.05;
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vert),vert);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    void moveRight()
    {
        if(vert[2]>=0.95) return;
        for(int i=0;i<8;i+=2) vert[i]+=0.05;
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vert),vert);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    void checkCollision(Ball* ball)
    {
        float up=ball->getLocY()+ball->getRad()+ball->getSpeedY(),x=ball->getLocX(),down=ball->getLocY()-ball->getRad()+ball->getSpeedY();
        if((up>=vert[1] and down<=vert[1] or down<=vert[5] and up>=vert[5]) and vert[0]<=x and vert[2]>=x)
            ball->collide();
    }

    ~Slider(){ glDeleteBuffers(1,&VBO); glDeleteBuffers(1,&EBO); glDeleteBuffers(1,&VAO); }
};

#endif //PONG_SLIDER_HPP
