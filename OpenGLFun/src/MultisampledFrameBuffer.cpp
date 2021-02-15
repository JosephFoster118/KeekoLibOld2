#include "MultisampledFrameBuffer.h"


MultisampledFrameBuffer::MultisampledFrameBuffer(uint32_t width, uint32_t height)
{
    glEnable( GL_MULTISAMPLE );
    this->width = width;
    this->height = height;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex);
    glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, num_samples, GL_RGBA8, width, height, false );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glBindFramebuffer( GL_FRAMEBUFFER, fbo );
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, tex, 0);

    // glGenRenderbuffers(1, &rbo);
    // glBindRenderbuffer(GL_RENDERBUFFER, rbo);  
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    
}

MultisampledFrameBuffer::~MultisampledFrameBuffer()
{
    glDeleteFramebuffers(1, &fbo);
}



MultisampledFrameBuffer::operator uint32_t() const
{
    return fbo;
}

uint32_t MultisampledFrameBuffer::getTexture()
{
    return tex;
}

uint32_t MultisampledFrameBuffer::getRender()
{
    return rbo;
}

