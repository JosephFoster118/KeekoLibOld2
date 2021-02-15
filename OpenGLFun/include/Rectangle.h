#pragma once

#include "Shape.h"

class Rectangle: public Shape
{
protected:
    enum DrawType 
    {
        CENTER,
        TOP_LEFT
    };
    Point vectors[4];
    Point position;

public:
    Rectangle() = delete;
    Rectangle(float width, float height, Point position, Color color, DrawType dt = CENTER);
    virtual void draw() override;
};

