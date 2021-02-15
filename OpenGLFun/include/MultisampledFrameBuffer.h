#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdint>
#include <memory>
#include <iostream>
class MultisampledFrameBuffer
{
public:
    MultisampledFrameBuffer() = delete;
    MultisampledFrameBuffer(const MultisampledFrameBuffer&) = delete;//Removes the copy constructor
    MultisampledFrameBuffer(uint32_t width, uint32_t height);
    virtual ~MultisampledFrameBuffer();

    operator uint32_t() const;

    uint32_t getTexture();
    uint32_t getRender();


private:
    uint32_t tex{0};
    uint32_t fbo{0};
    uint32_t rbo{0};
    uint32_t width;
    uint32_t height;

    int num_samples{16};

};
