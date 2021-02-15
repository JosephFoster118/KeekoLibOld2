#pragma once
#include <GL/glew.h>    /* Replace gl.h with glew.h */ 
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <memory>
#include <vector>
#include <chrono>
#include <iostream>
#include <GLFW/glfw3.h>

#include "Shape.h"
#include "Rectangle.h"
#include "FrameBuffer.h"
#include "MultisampledFrameBuffer.h"

#include <chrono>
#include <KeekoLib/PeriodicThread.h>


class TestClass
{
    
public:

    TestClass();

    void start(GLFWwindow* window);
    void display();

    void generateTexture();
    Rectangle rect3{200.0,20.0,Point(500,500),Color{1,0,0,1}};
private:

    void update();

    std::mutex mtx;
    std::unique_ptr<PeriodicThread> update_thread;

    std::unique_ptr<MultisampledFrameBuffer> fb;
    uint32_t tex{0};
    uint32_t fbo{0};
    uint32_t rbo{0};
    Rectangle rect{2.5f,1.5f,Point{2.0f, 2.0f},Color{0.0f,0.0f,1.0f,0.7f}};

    GLFWwindow* window;
};
