#include <GL/glew.h>    /* Replace gl.h with glew.h */ 
#include <GL/glu.h>  // GLUT, includes glu.h and gl.h
#include <GLFW/glfw3.h>
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <vector>
#include <chrono>
#include <iostream>
#include "Shape.h"
#include "Rectangle.h"
#include "TesterClass.h"
#include <chrono>
#include <KeekoLib/PeriodicThread.h>


std::mutex mtx;           // mutex for critical section

using std::cout;
using std::endl;
using namespace std::chrono_literals;

const GLfloat triangle[] =
   {
      -0.5, 0.5,
      0.5, 0.5,
      0.0, 0.0,
      0.0, 1.0
   };

Rectangle rect{2.0,2.0,Point(1.25,1.25),Color{0,1,0,1}};
Rectangle rect2{4.0,4.0,Point(5.2,6.5),Color{1,0,0,1}};


struct colors_t
{
   float r;
   float g;
   float b;
};

colors_t pixels[20 * 20] = {0,};
constexpr uint32_t full_size = 20 * 20;
std::vector<std::shared_ptr<Rectangle>> big_pixels(20*20);

TestClass test_class{};

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{

   GLFWwindow* window;

   /* Initialize the library */
   if (!glfwInit())
      return -1;


   /* Create a windowed mode window and its OpenGL context */
   window = glfwCreateWindow(500, 500, "Hello World", NULL, NULL);
   if (!window)
   {
      glfwTerminate();
      return -1;
   }

   /* Make the window's context current */
   glfwMakeContextCurrent(window);

   GLenum err=glewInit();
   if(err!=GLEW_OK) {
      // Problem: glewInit failed, something is seriously wrong.
      cout << "glewInit failed: " << glewGetErrorString(err) << endl;
      exit(1);
   }
   test_class.start(window);

   std::condition_variable cv;
   std::mutex cv_m;

   PeriodicThread draw_thread{66ms, "Draw", [&cv_m, &cv]()
   {
      cv.notify_all();
   }};
   draw_thread.start();

   /* Loop until the user closes the window */
   while (!glfwWindowShouldClose(window))
   {
      std::unique_lock<std::mutex> lk(cv_m);
      cv.wait(lk);
      test_class.display();
      /* Swap front and back buffers */
      

      /* Poll for and process events */
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}