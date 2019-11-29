#include "CircuitBase.h"
#include <QOpenGLFunctions>

// 회로판
CircuitBase::CircuitBase()
{

}

void CircuitBase::draw()
{
    // Draw base
    glPushMatrix();
    glScalef(1.0f, 1.0f, 0.1f);
    for (int i = 0; i < 6; ++i) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; ++j) {
            glVertex3f(coords[i] [j] [0], coords[i] [j] [1], coords[i] [j] [2]);
        }
        glEnd();
    }
    glPopMatrix();
}

void CircuitBase::setScale(float x)
{
    scale = x;
}
