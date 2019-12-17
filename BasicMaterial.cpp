#include "BasicMaterial.h"

BasicMaterial::BasicMaterial(float x, float y, float depth)
{
    this->x = x;
    this->y = y;
    this->depth = -depth;
}

void BasicMaterial::draw()
{
    // Draw base
    glPushMatrix();
    glTranslatef(x, -y, 0);
    glTranslatef(0, 0, depth * scale - 1 * scale);

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

void BasicMaterial::setScale(float x)
{
    scale = x;
}

float BasicMaterial::getSizeX()
{
    return this->cellSizeX;
}

float BasicMaterial::getSizeY()
{
    return this->cellSizeY;
}

float BasicMaterial::getSizeZ()
{
    return this->cellSizeZ;
}
