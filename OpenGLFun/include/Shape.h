#pragma once
#include <GL/glut.h>  // GLUT, includes glu.h and gl.h
#include <string.h>
#include <vector>

struct Point
{
    float x;
    float y;
    Point(float x,float y)
    {
        this->x = x;
        this->y = y;
    }
    Point()
    {
        this->x = 0.0;
        this->y = 0.0;
    }
};

struct Color
{
    float r;
    float g;
    float b;
    float a;
    // Color(const Color &c2)
    // {
    //     memcpy(this,&c2,sizeof(Color));
    //     r = c2.r;
    //     g = c2.g;
    //     b = c2.b;
    //     a = c2.a;
    // }
};


class Shape
{
public:
    Shape() {};
    virtual void draw() = 0;
    void setColor(Color c);
protected:
    std::vector<Color> color_points;
};

