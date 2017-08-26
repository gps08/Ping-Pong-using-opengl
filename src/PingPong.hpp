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
    GLuint shaderProgram; Walls* walls;

    public:
    PingPong(GLuint width,GLuint height)
    {
        window = GLwin(width,height).ref;
        slider = new Slider(0.01,0.40);
        ball = new Ball(0.02,50);
        shaderProgram = Shaders("../res/sprite.vert","../res/sprite.frag").ID;
        walls=new Walls(); ImGui_ImplGlfwGL3_Init(window,false);
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
            slider->checkCollision(ball); ball->move();
            showScore(ball->getScore());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    ~PingPong(){ glfwTerminate(); }

    private:
    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            slider->moveLeft();
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            slider->moveRight();
    }

    // this function is copied from the code given by the TA
    void showScore(int score)
    {
        ImGui_ImplGlfwGL3_NewFrame();
        ImGui::SetNextWindowSize(ImVec2(0,0),ImGuiSetCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(0,0)); bool show_another_window = true;
        ImGui::Begin("Score",&show_another_window,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize);
        ImGui::Text("Score %d   ",score); ImGui::End(); ImGui::Render();
    }
};

#endif //PONG_PINGPONG_H