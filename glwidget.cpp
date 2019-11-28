/****************************************************************************
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
    return QSize(400, 400);
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
    float value=float(s_value)/10;
    if(value != m_scale){
        m_scale = value;
        emit scaleChanged(s_value);
        update();
    }
}

void GLWidget::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_logoVbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}

float* GLWidget::crossProduct(float x1,float y1, float z1, float x2,float y2, float z2){
    float* result = new float[3];
    result[0] = (y1 * z2 - z1 *y2);
    result[1] = (z1 * x2 - x1 *z2);
    result[2] = (x1 * y2 - y1 *x2);
    float normal = sqrt(result[0] * result[0] + result[1] * result[1] + result[2] * result[2]);
    result[0]/=normal;
    result[1]/=normal;
    result[2]/=normal;
    return result;
}


float* GLWidget::threePoint_crossProduct(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3){
    float* vector = crossProduct(x2-x1, y2-y1, z2-z1, x3-x1, y3-y1, z3-z1);
    return vector;
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

    std::ifstream read;
    read.open("C:/Users/p/Desktop/Graphics/assignment/Assign-1/mesh-data/bunny.off");
    qDebug()<<"read ok";
    char tt[10];
    read.getline(tt,10);
    qDebug()<<tt;
    int zero, three;
    read >> total_vertices >> total_faces >> zero;
    float* vertex_coordinates = new float[total_vertices * 3];
    unsigned int* vertex_indices = new unsigned int[total_faces * 3];
    for(int i=0; i<total_vertices; i++){
        read >> vertex_coordinates[i*3+0] >> vertex_coordinates[i*3+1] >> vertex_coordinates[i*3+2];
    }
    for(int i=0; i<total_faces; i++){
        read >> three >> vertex_indices[i*3+0] >> vertex_indices[i*3+1] >> vertex_indices[i*3+2];
    }
    qDebug()<<tt;

    float* face_normal = new float[total_faces * 3];
    for(int i=0; i<total_faces; i++){
        float* face_cross = threePoint_crossProduct(vertex_coordinates[vertex_indices[i*3+0]*3+0],vertex_coordinates[vertex_indices[i*3+0]*3+1],vertex_coordinates[vertex_indices[i*3+0]*3+2],
                                                    vertex_coordinates[vertex_indices[i*3+1]*3+0],vertex_coordinates[vertex_indices[i*3+1]*3+1],vertex_coordinates[vertex_indices[i*3+1]*3+2],
                                                    vertex_coordinates[vertex_indices[i*3+2]*3+0],vertex_coordinates[vertex_indices[i*3+2]*3+1],vertex_coordinates[vertex_indices[i*3+2]*3+2]);
        face_normal[3*i+0] = face_cross[0];
        face_normal[3*i+1] = face_cross[1];
        face_normal[3*i+2] = face_cross[2];
    }
    float* vertex_normal = new float[total_vertices * 3];
    for(int i=0; i<total_vertices*3 ;i++){
        vertex_normal[i] = 0;
    }
    float* count = new float[total_vertices];
    for(int i=0; i<total_vertices;i++){
        count[i] = 0;
    }
    for(int i=0; i<total_faces; i++){
        for(int j=0; j<3; j++){
            vertex_normal[vertex_indices[i*3+j]*3+0]+=face_normal[i*3+0];
            vertex_normal[vertex_indices[i*3+j]*3+1]+=face_normal[i*3+1];
            vertex_normal[vertex_indices[i*3+j]*3+2]+=face_normal[i*3+2];
            count[vertex_indices[i*3+j]]++;
        }
    }
    for(int i=0;i<total_vertices;i++){
        vertex_normal[i*3+0]/=count[i];
        vertex_normal[i*3+1]/=count[i];
        vertex_normal[i*3+2]/=count[i];
    }
    read.close();

    qDebug()<<"ok for now";


    float* vertexArray = new float[total_faces * 3 * 6];
    for(int i=0; i<total_faces; i++){
        for(int j=0;j<3;j++){
            vertexArray[(6*(3*i+j)+0)]=vertex_coordinates[vertex_indices[i*3+j]*3+0];
            vertexArray[(6*(3*i+j)+1)]=vertex_coordinates[vertex_indices[i*3+j]*3+1];
            vertexArray[(6*(3*i+j)+2)]=vertex_coordinates[vertex_indices[i*3+j]*3+2];
            vertexArray[(6*(3*i+j)+3)]=vertex_normal[vertex_indices[i*3+j]*3+0];
            vertexArray[(6*(3*i+j)+4)]=vertex_normal[vertex_indices[i*3+j]*3+1];
            vertexArray[(6*(3*i+j)+5)]=vertex_normal[vertex_indices[i*3+j]*3+2];
        }
    }


    QOpenGLShader *vertS = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vertS->compileSourceFile("C:/Users/p/Desktop/Graphics/team_project/qt/basic.vert");

    QOpenGLShader *fragS = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fragS->compileSourceFile("C:/Users/p/Desktop/Graphics/team_project/qt/basic.frag");

    qDebug()<<"shader ok";


    m_program = new QOpenGLShaderProgram;

    m_program->addShader(vertS);
    m_program->addShader(fragS);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);
    m_program->link();
    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("matProj");
    m_mvMatrixLoc = m_program->uniformLocation("matModel");
//    m_normalMatrixLoc = m_program->uniformLocation("normal");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    m_logoVbo.create();
    m_logoVbo.bind();
    m_logoVbo.allocate(vertexArray, total_faces * 3 * 6 * sizeof(GLfloat));
//    m_logoVbo.allocate(vertexArray, total_faces * 3 * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Our camera never changes in this example.
    m_camera.setToIdentity();
    m_camera.translate(0, 0, -1);

    // Light position is fixed.
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();

    qDebug()<<"init ok";

}

void GLWidget::setupVertexAttribs()
{
    m_logoVbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_logoVbo.release();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();
    m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    m_world.scale(m_scale);
    m_world.translate(moveXdegree,moveYdegree);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
//    QMatrix3x3 normalMatrix = m_world.normalMatrix();
//    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

//       glDrawArrays(GL_TRIANGLES, 0, total_faces*3);
   glDrawArrays(GL_TRIANGLES, 0, total_faces * 3 * 6);
//    glDrawElements(GL_TRIANGLES, total_faces*3, GL_UNSIGNED_INT, 0);
    m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
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
