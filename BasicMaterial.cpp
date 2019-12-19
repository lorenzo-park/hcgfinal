#include "BasicMaterial.h"
#include "materialchoose.h"
#include "glwidget.h"

BasicMaterial::BasicMaterial(GLWidget* parent, float x, float y, float depth, int layer, QString mat)
{
    parent_gl=parent;
    this->x = x;
    this->y = y;
    this->depth = -depth;
    this->layer = layer;
    materialTex=mat.toStdString();
}

void BasicMaterial::draw()
{



    // Draw base
    glPushMatrix();
    glTranslatef(x, -y, 0);
    glTranslatef(0, 0, depth * 2 * scale - 2 * scale);
    //qDebug()<<parent_gl->parent_window->materialchoose->material_text;
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

    glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->ambient[0]);
    glLightfv(GL_LIGHT0, GL_AMBIENT, parent_gl->diffuse[0]);
}

void BasicMaterial::drawTranslucent(float alpha)
{

    // Draw base
    glPushMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);

    glTranslatef(x, -y, 0);
    glTranslatef(0, 0, depth * 2 * scale - 2 * scale);

    glColor4f(color[0], color[1], color[2], alpha);

    for (int i = 0; i < 6; ++i) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < 4; ++j) {
            glVertex3f(coords[i] [j] [0], coords[i] [j] [1], coords[i] [j] [2]);
        }
        glEnd();
    }

    glDisable(GL_BLEND);
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
