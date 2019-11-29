#include "BasicMaterial.h"

BasicMaterial::BasicMaterial(float x, float y, float depth, float cellSizeX, float cellSizeY, float cellSizeZ)
{
    this->x = x;
    this->y = y;
    this->depth = depth;
    this->cellSizeX = cellSizeX;
    this->cellSizeY = cellSizeY;
    this->cellSizeZ = cellSizeZ;
}

void BasicMaterial::draw()
{
    // Draw base
    glPushMatrix();
    glScalef(cellSizeX, cellSizeY, cellSizeZ);
    glTranslatef(x, y, depth);
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
