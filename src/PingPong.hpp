#ifndef PONG_PINGPONG_H
#define PONG_PINGPONG_H

#include <imgui_impl_glfw_gl3.h>
#include "GLwin.hpp"
#include "Slider.hpp"
#include "Ball.hpp"
#include "Shaders.hpp"
#include "Walls.hpp"

class PingPong
{
    private:
    GLFWwindow* window; Slider* slider; Ball* ball;
    GLuint shaderProgram; Walls* walls; bool pause;

    public:
    PingPong(GLuint width,GLuint height)
    {
        window = GLwin(width,height).ref;
        slider = new Slider(0.01,0.40);
        ball = new Ball(0.02,50);
        shaderProgram = Shaders("../res/sprite.vert","../res/sprite.frag").ID;
        walls=new Walls(); ImGui_ImplGlfwGL3_Init(window,false); pause=true;
    }

    void run()
    {
        while (!glfwWindowShouldClose(window))
        {
            processInput(window);
            glClearColor(0.0f,0.0f,0.0f,0.0f); // background color
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderProgram);

            walls->draw(); slider->draw(); ball->draw();
            if(!pause) {
                slider->checkCollision(ball);
                ball->move();
            }
            else showPaused();
            showInfo(ball->getScore(),ball->getSpeedY()*10000);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    ~PingPong(){ glfwTerminate(); }

    private:
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        else if (glfwGetKey(window,GLFW_KEY_LEFT)==GLFW_PRESS and !pause)
            slider->moveLeft();
        else if (glfwGetKey(window,GLFW_KEY_RIGHT)==GLFW_PRESS and !pause)
            slider->moveRight();
        else if (glfwGetKey(window,GLFW_KEY_P)==GLFW_PRESS)
            pause=true;
        else if (glfwGetKey(window,GLFW_KEY_O)==GLFW_PRESS)
            pause=false;
    }

    // some lines in this function are copied from the code given by the TA
    void showInfo(int score,int speed)
    {
        ImGui_ImplGlfwGL3_NewFrame();
        ImGui::SetNextWindowSize(ImVec2(0,0),ImGuiSetCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(0,0)); bool show_another_window = true;
        ImGui::Begin("Info",&show_another_window,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize);
        ImGui::Text("Score:%d\nSpeed:%d",score,abs(speed)); ImGui::End(); ImGui::Render();
    }

    void showPaused()
    {
        ImGui_ImplGlfwGL3_NewFrame();
        ImGui::SetNextWindowSize(ImVec2(0,0),ImGuiSetCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(230,270)); bool show_another_window = true;
        ImGui::Begin("paused",&show_another_window,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize);
        ImGui::Text("press 'O' to resume"); ImGui::End(); ImGui::Render();
    }
};

#endif //PONG_PINGPONG_H