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
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <fstream>

bool GLWidget::m_transparent = false;

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_xRot=0;
    m_yRot=0;
    m_zRot=0;
    m_scale=0;
    m_program=0;

}

GLWidget::~GLWidget()
{
    cleanup();
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
        reference->update();
    } else {
        return;
    }
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
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_FLAT);

    // Initialize base
    circuitBase = new CircuitBase();

    qDebug()<<"init ok";
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    if (isViewerMode)
    {
        glRotatef(120.0f, 1, 0, 0);
        glRotatef(180.0f, 0, 1, 0);
        glRotatef(180.0f, 0, 0, 1);
    }

    glRotatef(m_xRot / 16.0f, 1, 0, 0);
    glRotatef(m_yRot / 16.0f, 0, 1, 0);
    glRotatef(m_zRot / 16.0f, 0, 0, 1);

    glScalef(m_scale, m_scale, m_scale);


    qDebug()<<"rot x" << m_xRot << "rot y" << m_yRot << "rot z" << m_zRot;

    qDebug()<<"scale" << m_scale;

    circuitBase->draw();
    for (auto material : materials) {
        material->draw();
        qDebug() << "Drew at" << material->x << material->y << material->depth;
    }
    glPopMatrix();

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    qDebug() << w << h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (isViewerMode)
    {
        glFrustum(-1.5f, 1.5f, -1.5f, 1.5f, 3.0f, 30.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, 0, -10.0f);
    } else {
        glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, 0, -5.0f);
    }

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();

    if (!isViewerMode)
    {
        float x = 2.0f * (m_lastPos.x() / 600.0f) - 1.0f;
        float y = 1.0f - 2.0f * (m_lastPos.y() / 600.0f);
        qDebug() << "Added at" << x << y;
        BasicMaterial* material = new BasicMaterial(x*80, y*80, 1.0f, 0.1f, 0.1f, 0.1f);
        materials.push_back(material);
        setReferenceWidgetData();
        update();
    }

}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isTranslationOn) {
        int dx = event->x() - m_lastPos.x();
        int dy = event->y() - m_lastPos.y();

        if (event->buttons() & Qt::LeftButton) {
            moveX(1000*((float(dx)/this->width())+moveXdegree+0.5));
            moveY(1000*((float(dy)/this->height())+moveYdegree+0.5));
            //        setXRotation(m_xRot + 8 * dy);
    //        setYRotation(m_yRot + 8 * dx);
        } else if (event->buttons() & Qt::RightButton) {
            if(dy<0)setScale(m_scale*10+1);
            else setScale(m_scale*10-1);
        }
        m_lastPos = event->pos();
    }

}

