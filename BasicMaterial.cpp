#include "BasicMaterial.h"

BasicMaterial::BasicMaterial(float x, float y, float depth, float cellHeight)
{
    this->x = x;
    this->y = y;
    this->cellSizeX = 0.083f;
    this->cellSizeY = 0.083f;
    this->cellSizeZ = cellHeight * 0.083f;
    this->depth = -depth * 0.083f;
}

void BasicMaterial::draw()
{
    // Draw base
    glPushMatrix();
    glTranslatef(x, -y, 0);

    glTranslatef(0, 0, depth - 0.4f);
    glScalef(cellSizeX, cellSizeY, cellSizeZ);
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
    return this->cellSizeX * scale;
}

float BasicMaterial::getSizeY()
{
    return this->cellSizeY * scale;
}

float BasicMaterial::getSizeZ()
{
    return this->cellSizeZ * scale;
}
