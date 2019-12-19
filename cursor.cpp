#include "cursor.h"
#include "glwidget.h"
Cursor::Cursor()
{

}


Cursor::Cursor(float x, float y, float depth,GLWidget *gl)
{
    parent_gl=gl;
    this->x = x;
    this->y = y;
    this->depth = -depth;
}

void Cursor::draw(std::string materialTex)
{


    // Draw base
    glPushMatrix();
    glTranslatef(x, -y, 0);
    glTranslatef(0, 0, depth * 2 * scale - 2 * scale);

    if(materialTex == "poly"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[1]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[1]);
    }
    else if(materialTex == "nwell"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[2]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[2]);
    }
    else if(materialTex == "pwell"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[3]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[3]);
    }
    else if(materialTex == "nselect"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[4]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[4]);
    }
    else if(materialTex == "pselect"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[5]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[5]);
    }
    else if(materialTex == "nactive"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[6]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[6]);
    }
    else if(materialTex == "pactive"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[7]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[7]);
    }
    else if(materialTex == "contact"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[8]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[8]);
    }
    else if(materialTex == "metal"){
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[9]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[9]);
    }
    else {
        glColor3f(color[0], color[1], color[2]);
    }


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
