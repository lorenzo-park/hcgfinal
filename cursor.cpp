#include "cursor.h"

Cursor::Cursor()
{

}


Cursor::Cursor(float x, float y, float depth)
{
    this->x = x;
    this->y = y;
    this->depth = -depth;
}

void Cursor::draw()
{
    // Draw base
    glPushMatrix();
    glTranslatef(x, -y, 0);
    glTranslatef(0, 0, depth * 2 * scale - 2 * scale);

    glColor3f(color[0], color[1], color[2]);


    for (int i = 0; i < 6; ++i) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; ++j) {
            glVertex3f(coords[i] [j] [0], coords[i] [j] [1], coords[i] [j] [2]);
        }
        glEnd();
    }
    glPopMatrix();
}

void Cursor::setScale(float x)
{
    scale = x;
}

float Cursor::getSizeX()
{
    return this->cellSizeX;
}

float Cursor::getSizeY()
{
    return this->cellSizeY;
}

float Cursor::getSizeZ()
{
    return this->cellSizeZ;
}

void Cursor::setColor(float r, float g, float b) {
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
}
