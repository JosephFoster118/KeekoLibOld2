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
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //std::lock_guard<std::mutex> lck (mtx);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
    glLoadIdentity();                 // Reset Projection matrix
    glViewport(0,0,1000,1000);
    gluOrtho2D(0.0, 1000.0, 1000.0, 0.0); // Set clipping area's left, right, bottom, top
    rect3.draw();

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, fb->getTexture()); 

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0);
        glVertex2f(100, 100);

        glTexCoord2f(1, 0);
        glVertex2f(600, 100);

        glTexCoord2f(1, 1);
        glVertex2f(600, 600);

        glTexCoord2f(0, 1);
        glVertex2f(100, 600);
    }
    glEnd();




    glFlush();  // Render now
    glutSwapBuffers();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
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

    
 
    // glGenFramebuffers(1, &fbo);
    // glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // glGenTextures(1, &tex);
    // glBindTexture(GL_TEXTURE_2D, tex);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 10, 10, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

    // glGenRenderbuffers(1, &rbo);
    // glBindRenderbuffer(GL_RENDERBUFFER, rbo);  
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 10, 10);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    
    
    
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, *fb);
    

    
    // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
    
    
    // glBlitNamedFramebuffer(*fb, fbo, 0, 0, 10, 10, 0, 0, 10, 10, GL_COLOR_BUFFER_BIT, GL_NEAREST);




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