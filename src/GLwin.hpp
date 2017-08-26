#ifndef PONG_GLWIN_H
#define PONG_GLWIN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

using namespace std;

class GLwin
{
    public:
    GLFWwindow* ref;
    GLwin(unsigned int width,unsigned int height)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        ref=glfwCreateWindow(width,height,"MainWindow",NULL,NULL);
        if(ref==NULL) {
            cout<<"Failed to create GLFW window"<<endl;
            glfwTerminate(); exit(-1);
        }
        glfwMakeContextCurrent(ref);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            cout<<"Failed to initialize OpenGL context"<<endl,exit(-1);
        glfwSetFramebufferSizeCallback(ref,framebuffer_size_callback);
    }
    void static framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0,0,width,height);
    }
};

#endif //PONG_GLWIN_H