#include "Shape.h"


void Shape::setColor(Color c)
{
    for(int i = 0; i < color_points.size(); i++)
    {
        color_points[i] = c;
    }
}
