#include "TesterClass.h"
using namespace std::chrono_literals;


TestClass::TestClass()
{
    update_thread = std::make_unique<PeriodicThread>(20ms,"Update",[this]()
    {
        update();
    });
}

void TestClass::display()
{
    std::lock_guard<std::mutex> lck (mtx);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //std::lock_guard<std::mutex> lck (mtx);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    glEnable(GL_BLEND);
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
        glVertex2f(100, 100);

        glTexCoord2f(1, 0);
        glVertex2f(300, 100);

        glTexCoord2f(1, 1);
        glVertex2f(300, 300);

        glTexCoord2f(0, 1);
        glVertex2f(100, 300);
    }
    glPopMatrix();
    glEnd();
    glFlush();  // Render now
}

void TestClass::generateTexture()
{
    fb = std::make_unique<MultisampledFrameBuffer>(10,10,16);
    glBindFramebuffer(GL_FRAMEBUFFER, *fb);

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

       
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
    glLoadIdentity();                 // Reset Projection matrix
    gluOrtho2D(0.0, 10.0, 0.0, 10.0); // Set clipping area's left, right, bottom, top
    glViewport(0,0,10,10);
    glMatrixMode(GL_MODELVIEW);
    Rectangle rect{4.0f,4.0f,Point{6.5f,6.5f},Color{1.0f,1.0f,1.0f,1.0f}};
    rect.draw();
    glFlush();
    if(glGetError())
    {
        printf("Got error!\n");
    }
    fb->blitBuffers();


    struct color
    {
        float r;
        float g;
        float b;
        float a;
    };

    std::unique_ptr<color[]> data(new color[20*20]);
    int maxSamples;
    glGetIntegerv ( GL_MAX_SAMPLES, &maxSamples );
    printf("%d\n", maxSamples);

}

void TestClass::start()
{
    generateTexture();
    update_thread->start();
}

void TestClass::update()
{
    std::lock_guard<std::mutex> lck (mtx);
    //std::cout << static_cast<int>(*fb) << std::endl;
}