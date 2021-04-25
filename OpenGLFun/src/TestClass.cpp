#include "TesterClass.h"
using namespace std::chrono_literals;


TestClass::TestClass()
{
    update_thread = std::make_unique<PeriodicThread>(66ms,"Update",[this]()
    {
        update();
    });
}

void TestClass::display()
{
    std::lock_guard<std::mutex> lck (mtx);
    //generateTexture();

    glBindFramebuffer(GL_FRAMEBUFFER, *fb);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

       
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
    glLoadIdentity();                 // Reset Projection matrix
    gluOrtho2D(0.0, 32.0, 0.0, 32.0); // Set clipping area's left, right, bottom, top
    glViewport(0,0,32,32);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotated(-30.0,0,0,1);
    rect.draw();
    glPopMatrix();
    rect2.draw();
    if(glGetError())
    {
        printf("Got error!\n");
    }
    fb->blitBuffers();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // //std::lock_guard<std::mutex> lck (mtx);
    // glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color to black and opaque
    // glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    // glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
    glLoadIdentity();                 // Reset Projection matrix
    glViewport(0,0,500,500);
    gluOrtho2D(0.0, 500.0, 500.0, 0.0); // Set clipping area's left, right, bottom, top

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, fb->getTexture()); 
    glPushMatrix();
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0);
        glVertex2f(000, 000);

        glTexCoord2f(1, 0);
        glVertex2f(500, 000);

        glTexCoord2f(1, 1);
        glVertex2f(500, 500);

        glTexCoord2f(0, 1);
        glVertex2f(000, 500);
    }
    glEnd();
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0); 
    glFlush();  // Render now
    glfwSwapBuffers(window);
}

void TestClass::generateTexture()
{
    fb = std::make_unique<MultisampledFrameBuffer>(64,64,8);
}

void TestClass::start(GLFWwindow* window)
{
    this->window = window;
    generateTexture();
    update_thread->start();
}

void TestClass::update()
{
    static int counter = 0;
    std::lock_guard<std::mutex> lck (mtx);
    if(counter % 60 == 59)
    {
        rect = Rectangle{10.0f,10.0f,Point{4.0f, 6.0f},Color{0.0f,0.0f,1.0f,1.0f}};
        rect2 = Rectangle{7.0f,5.0f,Point{10.0f, 10.0f},Color{1.0f,0.0f,0.0f,0.5f}};
    }
    counter++;
    rect.move(Point{0.1,0.1});
    rect2.move(Point{-0.1,-0.1});

    //std::cout << static_cast<int>(*fb) << std::endl;
}