#include "Rectangle.h"


Rectangle::Rectangle(float width, float height, Point position, Color color, DrawType dt)
{
    vectors[0] = Point(width/2.0,height/2.0);
    vectors[1] = Point(width/2.0,-height/2.0);
    vectors[2] = Point(-width/2.0,-height/2.0);
    vectors[3] = Point(-width/2.0,height/2.0);
    color_points.resize(4);
    setColor(color);
    this->position = position;
}


void Rectangle::draw()
{
    glPushMatrix();
    glTranslatef(position.x, position.y, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4,GL_FLOAT,0,color_points.data());
    glVertexPointer(2,GL_FLOAT,0,vectors);
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glPopMatrix();
}

void Rectangle::move(Point amount)
{
    position.x += amount.x;
    position.y += amount.y;
}

