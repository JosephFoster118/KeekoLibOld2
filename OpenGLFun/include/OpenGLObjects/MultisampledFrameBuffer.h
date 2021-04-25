#pragma once
#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdint>
#include <memory>
#include <iostream>
#include "FrameBuffer.h"
class MultisampledFrameBuffer
{
public:
    MultisampledFrameBuffer() = delete;
    MultisampledFrameBuffer(const MultisampledFrameBuffer&) = delete;//Removes the copy constructor
    MultisampledFrameBuffer(uint32_t width, uint32_t height, uint16_t samples);
    virtual ~MultisampledFrameBuffer();

    operator uint32_t() const;

    uint32_t getTexture();
    uint32_t getRender();

    void blitBuffers();
    void bindBuffer();


private:
    uint32_t tex;
    uint32_t fbo;
    uint32_t rbo;
    uint16_t samples;
    uint32_t width;
    uint32_t height;

    std::unique_ptr<FrameBuffer> proxy_frame_buffer;

};
