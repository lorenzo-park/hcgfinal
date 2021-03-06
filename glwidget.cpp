/******************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include "CircuitBase.h"
#include "BasicMaterial.h"
#include "cursor.h"
#include "materialchoose.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <fstream>
#include <QMatrix4x4>
#include <iterator>
#include <list>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <list>

bool GLWidget::m_transparent = false;

GLWidget::GLWidget(Window *parent_w,QWidget *parent)
    : QOpenGLWidget(parent)
{
    parent_window=parent_w;
    m_xRot=0;
    m_yRot=0;
    m_zRot=0;
    m_scale=0;
    m_program=0;

    check_mouse = 0;

    axis_vec = new float[3];
    axis_vec[0] = 0;
    axis_vec[1] = 0;
    axis_vec[2] = 0;
    angle = 0;

    this->setMouseTracking(true);
}

GLWidget::~GLWidget()
{
    cleanup();
}

float GLWidget::find_angle(float x1, float y1, float z1, float x2, float y2, float z2) {
    float abs_1 = sqrt(x1 * x1 + y1 * y1 + z1 * z1);
    float abs_2 = sqrt(x2 * x2 + y2 * y2 + z2 * z2);
    float innerProduct_12 = x1 * x2 + y1 * y2 + z1 * z2;
    float cos_angle = innerProduct_12 / (abs_1 * abs_2);
    float rad = acos(cos_angle);
    float pi = 2 * acos(0.0);
    float degree = rad * 180 / pi;

    return degree;
}

float* GLWidget::findZ(float x, float y) {
    float buffer_x, buffer_y;
    float global_x, global_y, global_z;
    viewport_x1 = 0;
    viewport_y1 = 0;
    viewport_x2 = v_wide;
    viewport_y2 = v_height;

    buffer_x = x - viewport_x1;
    buffer_y = viewport_y2 - y + viewport_y1;
    global_x = pr_left + (buffer_x * (pr_right - pr_left)) / viewport_x2;
    global_y = pr_bottom + (buffer_y * (pr_top - pr_bottom)) / viewport_y2;
    radius = sqrt((pr_right - pr_left) * (pr_right - pr_left) + (pr_top - pr_bottom) * (pr_top - pr_bottom));
    global_z = center_value[2] + sqrt(radius * radius
                - (global_x - center_value[0]) * (global_x - center_value[0]) - (global_y - center_value[1]) * (global_y - center_value[1]));
    float* global_coord;
    global_coord = new float[3];
    global_coord[0] = global_x;
    global_coord[1] = global_y;
    global_coord[2] = global_z;

    return global_coord;
}

float GLWidget::findDepth(float x, float y) {
    float depth = 0;
    for (auto material : materials) {
        if (material->x == x && material->y == y) {
            depth += material->getSizeZ();
        }
    }

    return depth;
}

float* GLWidget::crossProduct(float x1, float y1, float z1, float x2, float y2, float z2) {
    float* out;
    out = new float[3];
    out[0] = (y1 * z2 - z1 * y2);
    out[1] = (z1 * x2 - x1 * z2);
    out[2] = (x1 * y2 - y1 * x2);
    float w = sqrt(out[0] * out[0] + out[1] * out[1] + out[2] * out[2]);
    out[0] /=w ;
    out[1] /=w;
    out[2] /=w;
    return out;
}

float* GLWidget::threePoint_crossProduct(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
    float nine[9] = { x1, y1, z1, x2, y2, z2, x3, y3, z3 };
    float* vector = crossProduct(nine[3] - nine[0], nine[4] - nine[1], nine[5] - nine[2], nine[6] - nine[0], nine[7] - nine[1], nine[8] - nine[2]);
    return vector;
}

void GLWidget::setReferenceWidget(GLWidget* reference)
{
    this->reference = reference;
}

void GLWidget::moveX(int degree){
    if(float(degree)/1000-0.5!= moveXdegree){
        moveXdegree=(float(degree)/1000-0.5);
        emit changedXmove(degree);
        update();
    }
}
void GLWidget::moveY(int degree){
    if(float(degree)/1000-0.5!= moveYdegree){
        moveYdegree=(float(degree)/1000-0.5);
        emit changedYmove(degree);
        update();
    }
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(600, 600);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::setScale(int s_value)
{
    float value=float(s_value)/100;
    if(value != m_scale){
        m_scale = (GLfloat) pow(2.3, value);
        emit scaleChanged(s_value);
        update();
    }
}

void GLWidget::enableTranslation(boolean translationOnOff)
{
    isTranslationOn = translationOnOff;
}

void GLWidget::enableViewerMode(boolean mode)
{
    isViewerMode = mode;
}

void GLWidget::setReferenceWidgetData()
{
    if (!isViewerMode) {
        reference->materials = materials;
        reference->cursor = cursor;
        reference->filteredLayers = filteredLayers;
        reference->update();
    } else {
        return;
    }
}

void GLWidget::setEditMode(EditMode editmode)
{
    this->activeMode = editmode;
}

EditMode GLWidget::getEditMode()
{
    return this->activeMode;
}

void GLWidget::cleanup()
{

}

void GLWidget::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.

    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);

    glEnable(GL_LIGHTING);

    ambient[0][0] = 1;
    ambient[0][1] = 1;
    ambient[0][2] = 1;
    ambient[0][3] = 1;
    diffuse[0][0] = 1;
    diffuse[0][1] = 1;
    diffuse[0][2] = 1;
    diffuse[0][3] = 1;

    ambient[1][0] = 0;
    ambient[1][1] = 0;
    ambient[1][2] = 1;
    ambient[1][3] = 1;
    diffuse[1][0] = 0;
    diffuse[1][1] = 0;
    diffuse[1][2] = 1;
    diffuse[1][3] = 1;

    ambient[2][0] = 0;
    ambient[2][1] = 1;
    ambient[2][2] = 0;
    ambient[2][3] = 1;
    diffuse[2][0] = 0;
    diffuse[2][1] = 1;
    diffuse[2][2] = 0;
    diffuse[2][3] = 1;

    ambient[3][0] = 0;
    ambient[3][1] = 1;
    ambient[3][2] = 1;
    ambient[3][3] = 1;
    diffuse[3][0] = 0;
    diffuse[3][1] = 1;
    diffuse[3][2] = 1;
    diffuse[3][3] = 1;

    ambient[4][0] = 1;
    ambient[4][1] = 0;
    ambient[4][2] = 0;
    ambient[4][3] = 1;
    diffuse[4][0] = 1;
    diffuse[4][1] = 0;
    diffuse[4][2] = 0;
    diffuse[4][3] = 1;

    ambient[5][0] = 1;
    ambient[5][1] = 0;
    ambient[5][2] = 1;
    ambient[5][3] = 1;
    diffuse[5][0] = 1;
    diffuse[5][1] = 0;
    diffuse[5][2] = 1;
    diffuse[5][3] = 1;

    ambient[6][0] = 1;
    ambient[6][1] = 1;
    ambient[6][2] = 0;
    ambient[6][3] = 1;
    diffuse[6][0] = 1;
    diffuse[6][1] = 1;
    diffuse[6][2] = 0;
    diffuse[6][3] = 1;

    ambient[7][0] = 0.3;
    ambient[7][1] = 0.5;
    ambient[7][2] = 0.7;
    ambient[7][3] = 1;
    diffuse[7][0] = 0.3f;
    diffuse[7][1] = 0.5f;
    diffuse[7][2] = 0.7f;
    diffuse[7][3] = 1;

    ambient[8][0] = 0.7f;
    ambient[8][1] = 0.5f;
    ambient[8][2] = 0.9f;
    ambient[8][3] = 1;
    diffuse[8][0] = 0.7f;
    diffuse[8][1] = 0.5f;
    diffuse[8][2] = 0.9f;
    diffuse[8][3] = 1;

    ambient[9][0] = 0;
    ambient[9][1] = 0;
    ambient[9][2] = 0;
    ambient[9][3] = 1;
    diffuse[9][0] = 0;
    diffuse[9][1] = 0;
    diffuse[9][2] = 0;
    diffuse[9][3] = 1;


    lightPos[0] = 10;
    lightPos[1] = 10;
    lightPos[2] = 0;
    lightPos[3] = 1;
    specular[0] = 1;
    specular[1] = 1;
    specular[2] = 1;
    specular[3] = 1;
    //for bacsic material
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse[0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient[0]);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    //for circuit base

    // Initialize base
    circuitBase = new CircuitBase();

    qDebug()<<"init ok";
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (check_mouse == 1) {
            float curMM[16];
            glGetFloatv(GL_MODELVIEW_MATRIX, curMM);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(center_value[0], center_value[1], center_value[2]);
            glRotatef(angle * 4, axis_vec[0], axis_vec[1], axis_vec[2]);
            glTranslatef(-center_value[0], -center_value[1], -center_value[2]);
            angle = 0;
            glMultMatrixf(curMM);
        }
        //right_zooming
        else if (check_mouse == 2) {
                float curMM[16];
                glGetFloatv(GL_MODELVIEW_MATRIX, curMM);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
       if (global_scale * scale_value < 0.01) scale_value = 1;
                global_scale *= scale_value;
                glTranslatef(center_value[0], center_value[1], center_value[2]);
                glScalef(scale_value, scale_value, scale_value);
                glTranslatef(-center_value[0], -center_value[1], -center_value[2]);
                glMultMatrixf(curMM);
                scale_value = 1;
        }
        //middle_translation
        else if (check_mouse == 3) {
            float curMM[16];
            glGetFloatv(GL_MODELVIEW_MATRIX, curMM);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(transl_x, transl_y, transl_z);
            transl_x = 0;
            transl_y = 0;
            transl_z = 0;

            glMultMatrixf(curMM);
        }

    GLfloat lightPos1[] = { 0, 2, -5, 1 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
    glPushMatrix();

    if (isViewerMode)
    {
        glRotatef(-60.0f, 1, 0, 0);
    }

    glRotatef(180.0f, 0, 1, 0);
    glRotatef(180.0f, 0, 0, 1);


//    glMatrixMode(GL_MODELVIEW);

//    glPushMatrix();

//    glTranslatef(moveXdegree,moveYdegree,0);

//    glRotatef(m_xRot / 16.0f, 1, 0, 0);
//    glRotatef(m_yRot / 16.0f, 0, 1, 0);
//    glRotatef(m_zRot / 16.0f, 0, 0, 1);

//    glScalef(m_scale, m_scale, m_scale);


//    qDebug()<<"rot x" << m_xRot << "rot y" << m_yRot << "rot z" << m_zRot;

//    qDebug()<<"scale" << m_scale;


    circuitBase->draw();

//    glPopMatrix();

    glEnable(GL_CULL_FACE);
    for (auto material : materials) {
        if (std::find(filteredLayers.begin(), filteredLayers.end(), material->layer)
                != filteredLayers.end()) {
            if (isViewerMode)
                material->drawTranslucent(0.5f);
            continue;
        }

        material->draw();
    }

    glDisable(GL_CULL_FACE);

    qDebug() << this->filteredLayers.size();
    if (cursor != 0) {
        cursor -> draw(parent_window->materialchoose->material_text.toStdString());
    }

    glPopMatrix();
}

void GLWidget::resizeGL(int w, int h)
{
    v_wide = w;
    v_height = h;
    glViewport(0, 0, w, h);
    qDebug() << w << h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    pr_left = origin_center_value[0] - 5;
    pr_right = origin_center_value[0] + 5;
    pr_bottom = origin_center_value[1] - 5;
    pr_top = origin_center_value[1] + 5;
    glOrtho(pr_left, pr_right, pr_bottom, pr_top, origin_center_value[2] - 30, origin_center_value[2] + 30);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
    float* global_coord = findZ(event->x(),event->y());
        //left_rotation
        if (event->buttons() == Qt::LeftButton) {
            angle = 0;
            check_mouse = 1;
            lastPos[0] = global_coord[0];
            lastPos[1] = global_coord[1];
            lastPos[2] = global_coord[2];

            if (!isViewerMode)
            {
                switch(activeMode) {
                case DEFAULT_MODE: {
                    break;
                }
                case ADD_MODE:{


                    float x = global_coord[0];
                    float y = global_coord[1];

                    float posX = round(2*x) / 2.0f;
                    float posY = round(2*y) / 2.0f;


                    float depth = findDepth(posX, posY);

                    if (pressedCoordX + 100.0f == 0.0f && pressedCoordY + 100.0f == 0.0f) {
                        pressedCoordX = posX;
                        pressedCoordY = posY;
                    }

                    qDebug() << "Added at" << x << y << posX << posY << depth;

//                    BasicMaterial* material = new BasicMaterial(posX, posY, depth);
//                    materials.push_back(material);
//                    setReferenceWidgetData();
//                    update();

                    break;
                }
                case DELETE_MODE: {
                    qDebug() << "delete mode check";
                    float x = global_coord[0];
                    float y = global_coord[1];

                    float posX = round(2*x) / 2.0f;
                    float posY = round(2*y) / 2.0f;

                    if (pressedCoordX + 100.0f == 0.0f && pressedCoordY + 100.0f == 0.0f) {
                        pressedCoordX = posX;
                        pressedCoordY = posY;
                    }

                    break;
                }
                }
            }
        }
        //right_zooming
        else if (event->buttons() == Qt::RightButton) {
            check_mouse = 2;
            scale_value = 1;
            lastPos[0] = global_coord[0];
            lastPos[1] = global_coord[1];
            lastPos[2] = global_coord[2];
        }
        //middle_translation
        else if(event->buttons() == Qt::MiddleButton){
            check_mouse = 3;
            lastPos[0] = global_coord[0];
            lastPos[1] = global_coord[1];
            lastPos[2] = global_coord[2];
        }


}

void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    if (!isViewerMode) {
        if (releasedCoordX + 100.0f == 0.0f && releasedCoordY + 100.0f == 0.0f &&
                pressedCoordX + 100.0f != 0.0f && pressedCoordY + 100.0f != 0.0f) {

            switch(activeMode) {
            case DEFAULT_MODE: {
                break;
            }
            case ADD_MODE: {
                float* global_coord = findZ(event->x(),event->y());

                float x = global_coord[0];
                float y = global_coord[1];

                float posX = round(2*x) / 2.0f;
                float posY = round(2*y) / 2.0f;

                releasedCoordX = posX;
                releasedCoordY = posY;

                qDebug() << pressedCoordX << pressedCoordY << releasedCoordX << releasedCoordY;
                fillMaterial(pressedCoordX, pressedCoordY, releasedCoordX, releasedCoordY);

                pressedCoordX = -100.0f;
                pressedCoordY = -100.0f;
                releasedCoordX = -100.0f;
                releasedCoordY = -100.0f;

                break;
            }
            case DELETE_MODE: {
                float* global_coord = findZ(event->x(),event->y());

                float x = global_coord[0];
                float y = global_coord[1];

                float posX = round(2*x) / 2.0f;
                float posY = round(2*y) / 2.0f;

                releasedCoordX = posX;
                releasedCoordY = posY;

                qDebug() << pressedCoordX << pressedCoordY << releasedCoordX << releasedCoordY;
                eraseMaterial(pressedCoordX, pressedCoordY, releasedCoordX, releasedCoordY);

                pressedCoordX = -100.0f;
                pressedCoordY = -100.0f;
                releasedCoordX = -100.0f;
                releasedCoordY = -100.0f;

                break;
            }
            }


        }
    }
    else
    {
        if(event->buttons() == Qt::LeftButton){
            check_mouse = 0;
            angle = 0;
        }
        else if(event->buttons() == Qt::RightButton){
            check_mouse = 0;
            scale_value = 1;
        }
        else if(event->buttons() == Qt::MiddleButton){
            check_mouse = 0;
        }
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    float* global_coord = findZ(event->x(),event->y());
    float x = global_coord[0];
    float y = global_coord[1];

    float posX = round(2*x) / 2.0f;
    float posY = round(2*y) / 2.0f;

    float depth = findDepth(posX, posY);
    switch(activeMode) {
    case ADD_MODE:{
        cursor = new Cursor(posX, posY, depth,this);
        setReferenceWidgetData();
        update();
        break;
    }
    case DELETE_MODE:{
        cursor = new Cursor(posX, posY, depth,this);
        cursor->setColor(1.0f, 1.0f, 1.0f);
        setReferenceWidgetData();
        update();
        break;
    }
    default:{
        cursor = 0;
        setReferenceWidgetData();
        update();
        break;
    }
    }

    if( event->buttons() ) {
        if (isTranslationOn) {

            float* global_coord = findZ(event->x(), event->y());

                curPos[0] = global_coord[0];
                curPos[1] = global_coord[1];
                curPos[2] = global_coord[2];
                if (sqrt((curPos[0]-center_value[0])* (curPos[0] - center_value[0])+(curPos[1] - center_value[1])* (curPos[1] - center_value[1])) > radius*4
                    || sqrt((lastPos[0] - center_value[0])* (lastPos[0] - center_value[0])+ (lastPos[1] - center_value[1])* (lastPos[1] - center_value[1]) > radius*4)) {
                    return;
                }

                if (curPos[0] == lastPos[0] && curPos[1] == lastPos[1] && curPos[2] == lastPos[2]) {
                    return;
                }

                //left point _ rotation
                if (check_mouse == 1) {
                    float sphere_center[3] = { center_value[0], center_value[1], center_value[2] };
                    axis_vec = threePoint_crossProduct(sphere_center[0], sphere_center[1], sphere_center[2],
                                                         lastPos[0], lastPos[1], lastPos[2],
                                                         curPos[0], curPos[1], curPos[2]);
                    angle = find_angle(lastPos[0] - sphere_center[0], lastPos[1] - sphere_center[1], lastPos[2] - sphere_center[2],
                                       curPos[0] - sphere_center[0], curPos[1] - sphere_center[1], curPos[2] - sphere_center[2]);

                }
                //right point _ zooming
                else if (check_mouse == 2) {
                        lastDistance = sqrt((lastPos[0] - center_value[0]) * (lastPos[0] - center_value[0])
                                          + (lastPos[1] - center_value[1]) * (lastPos[1] - center_value[1]));
                        curDistance = sqrt((curPos[0] - center_value[0]) * (curPos[0] - center_value[0])
                                          + (curPos[1] - center_value[1]) * (curPos[1] - center_value[1]));
                        cur_last_distance = sqrt((curPos[0] - lastPos[0]) * (curPos[0] - lastPos[0])
                                          + (curPos[1] - lastPos[1]) * (curPos[1] - lastPos[1]));
                        scale_value = cur_last_distance / lastDistance;
                        if (curDistance > lastDistance) {
                            scale_value = 1 + scale_value;
                        }
                        else if (lastDistance > curDistance) {
                            scale_value = 1 - scale_value;
                        }
                        else scale_value = 1;

                        if (scale_value < 0) {
                            scale_value = 1;
                        }
                }
                //middle point _ translation
                else if (check_mouse == 3) {
                    transl_x = curPos[0] - lastPos[0];
                    transl_y = curPos[1] - lastPos[1];

                    center_value[0] += transl_x;
                    center_value[1] += transl_y;

                }


                lastPos[0] = curPos[0];
                lastPos[1] = curPos[1];
                lastPos[2] = curPos[2];

        update();
        }
    }
}

void GLWidget::SaveFile(QString Filename) {

    qDebug() << "SaveFile:" << Filename;
    // Open file
    std::ofstream file( Filename.toStdString() ) ;
    for( const auto& material : materials )
        file << (*material).x << " " << (*material).y << " " << (*material).depth << '\n';

    // Close file
    file.close();
}

void GLWidget::Reset() {

    while (!materials.empty())
       materials.pop_back();
    setReferenceWidgetData();
    update();

}

float str2float (const std::string &str) {
  std::stringstream ss(str);
  float num;
  if((ss >> num).fail())
  {
      /* 에러 */
  }
  return num;
}

std::vector<float> split(std::string str, char delimiter) {
    std::vector<float> internal;
    std::stringstream ss(str);
    std::string temp;

    while (getline(ss, temp, delimiter)) {
        internal.push_back( str2float(temp) );
    }

    return internal;
}

void GLWidget::LoadFile(QString Filename) {
    std::ifstream openFile(Filename.toStdString() );

    if (openFile.is_open()) {
        std::string line;
        float x, y, z;

        while (getline(openFile, line)) {
            std::vector<float> line_vector = split(line, ' ');

            x = line_vector[0];
            y = line_vector[1];
            z = line_vector[2];

            // Need to be modified!float depth = findDepth(posX, posY);
            float depth = findDepth(x, y);
            BasicMaterial* material = new BasicMaterial(this,x, y, depth, currentLayer, parent_window->materialchoose->material_text);
            materials.push_back(material);
            setReferenceWidgetData();
            update();
        }
    }
}

void GLWidget::fillMaterial(float ax, float ay, float bx, float by) {
    float beginX = fmin(ax, bx);
    float endX = fmax(ax, bx);
    int stepX = (int) ((endX - beginX) / 0.5f);

    float beginY = fmin(ay, by);
    float endY = fmax(ay, by);
    int stepY = (int) ((endY - beginY) / 0.5f);

    float maxDepth = 0;
    for (int i=0; i < stepX + 1; i++) {
        for (int j=0; j < stepY + 1; j++) {
            float posX = beginX + 0.5f * i;
            float posY = beginY + 0.5f * j;
            float depth = findDepth(posX, posY);
            if (maxDepth < depth) {
                maxDepth = depth;
            }
        }
    }

    for (int i=0; i < stepX + 1; i++) {
        for (int j=0; j < stepY + 1; j++) {
            float posX = beginX + 0.5f * i;
            float posY = beginY + 0.5f * j;
            BasicMaterial* material = new BasicMaterial(this,posX, posY, maxDepth, currentLayer, parent_window->materialchoose->material_text);
            materials.push_back(material);
        }
    }

    setReferenceWidgetData();
    update();
}

void GLWidget::eraseMaterial(float ax, float ay, float bx, float by) {
    float beginX = fmin(ax, bx);
    float endX = fmax(ax, bx);
    int stepX = (int) ((endX - beginX) / 0.5f);

    float beginY = fmin(ay, by);
    float endY = fmax(ay, by);
    int stepY = (int) ((endY - beginY) / 0.5f);

    for (int i=0; i < stepX + 1; i++) {
        for (int j=0; j < stepY + 1; j++) {
            float x = beginX + 0.5f * i;
            float y = beginY + 0.5f * j;

            float depthMax = -1;
            for (auto material : materials) {
                if (material->x - material->getSizeX() / 2 <= x && x <= material->x + material->getSizeX() / 2 &&
                        material->y - material->getSizeY() / 2 <= y && y <= material->y + material->getSizeY() / 2) {
                    if (depthMax == -1 || depthMax < abs(material->depth)) {
                        depthMax = abs(material->depth);

                    }
                }
            }

            std::list<BasicMaterial*> updatedMaterials;
            for (auto material : materials) {
                if (material->x - material->getSizeX() / 2 <= x && x <= material->x + material->getSizeX() / 2 &&
                        material->y - material->getSizeY() / 2 <= y && y <= material->y + material->getSizeY() / 2 &&
                        depthMax - abs(material->depth) == 0.0f) {
                    continue;
                }
                updatedMaterials.push_back(material);
            }
            materials.clear();
            materials = updatedMaterials;
        }
    }

    setReferenceWidgetData();
    update();
}
