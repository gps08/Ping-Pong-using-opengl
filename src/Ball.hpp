#ifndef PONG_BALL_HPP
#define PONG_BALL_HPP

#include <cmath>
#define PI 3.1415927410125732421875

class Ball
{
    private:
    GLuint VBO,VAO,shaderProgram; int noOfSides,score;
    float speedX,speedY,locX,locY,rad; GLdouble* v;

    void updateBuffer(float toAddX,float toAddY)
    {
        for(int i=0;i<2*noOfSides+4;i+=2) v[i]+=toAddX,v[i+1]+=toAddY;
        locX+=toAddX; locY+=toAddY;

        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(v[0])*(2*noOfSides+4),v);
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }

    public:
    Ball(float rad,int noOfSides):noOfSides(noOfSides),rad(rad)
    {
        v=new GLdouble[2*noOfSides+4]; v[0]=0; v[1]=0; int c=2;
        for(int i=0;i<=noOfSides;i++)
        { v[c++]=rad*cos(2.0*PI*i/noOfSides); v[c++]=rad*sin(2.0*PI*i/noOfSides); }

        glGenVertexArrays(1,&VAO); glGenBuffers(1,&VBO);
        glBindVertexArray(VAO); glBindBuffer(GL_ARRAY_BUFFER,VBO);

        glBufferData(GL_ARRAY_BUFFER,sizeof(v[0])*(2*noOfSides+4),v,GL_STATIC_DRAW);
        glVertexAttribPointer(0,2,GL_DOUBLE,GL_FALSE,0,(void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,0); glBindVertexArray(0);
        speedX=1.5*rad; speedY=-1.5*rad; locX=0; locY=0; score=0;
    }

    void draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN,0,noOfSides+2);
        glBindVertexArray(0);
    }

    void move()
    {
        float toAddX=0,toAddY=0;
        if(locX+rad+speedX<0.95 and locX+speedX-rad>-0.95) toAddX=speedX; else speedX*=-1;
        if(locY+rad+speedY<0.95 and locY+speedY-rad>-0.95) toAddY=speedY; else speedY*=-1;
        if(locY<0 and toAddY==0) score=0;
        updateBuffer(toAddX,toAddY);
    }

    void collide(){ score++; speedY*=-1; }

    float getLocX() const { return locX; }
    float getLocY() const { return locY; }
    float getRad()  const { return rad;  }
    int getScore() const { return score; }

    ~Ball(){ glDeleteBuffers(1,&VBO); glDeleteBuffers(1,&VAO); }
};

#endif //PONG_BALL_HPP