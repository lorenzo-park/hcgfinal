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

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <list>
#include "logo.h"
#include "CircuitBase.h"
#include "BasicMaterial.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

enum EditMode {
    DEFAULT_MODE,
    ADD_MODE,
    DELETE_MODE
};

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    static bool isTransparent() { return m_transparent; }
    static void setTransparent(bool t) { m_transparent = t; }

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void SaveFile(QString Filename);
    void LoadFile(QString Filename);
    void Reset();

    float moveXdegree=0;
    float moveYdegree=0;

    float v_wide=0;
    float v_height=0;
    float viewport_x1, viewport_y1, viewport_x2, viewport_y2;
    float pr_left, pr_right, pr_top, pr_bottom;
    float origin_center_value[3]={0,0,0};
    float curPos[3]={0,0,0};
    float lastPos[3]={0,0,0};
    int check_mouse = 0;
    float center_value[3] = {0,0,0};
    float radius;
    float *axis_vec;
    float angle;
    float lastDistance, curDistance, cur_last_distance;
    float scale_value;
    float transl_x, transl_y, transl_z;
    float global_scale =1;


public slots:
    float* findZ(float x, float y);
    float findDepth(float x, float y);
    float* threePoint_crossProduct(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
    float* crossProduct(float x1, float y1, float z1, float x2, float y2, float z2);
    float find_angle(float x1, float y1, float z1, float x2, float y2, float z2);

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setScale(int s_value);
    void cleanup();

    void moveX(int degree);
    void moveY(int degree);

    void enableTranslation(boolean translationOnOff);
    void enableViewerMode(boolean mode);

    void setReferenceWidget(GLWidget* reference);
    void setReferenceWidgetData();

    EditMode getEditMode();
    void setEditMode(EditMode editmode);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void scaleChanged(int s_value);

    void changedXmove(int degree);
    void changedYmove(int degree);


protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
//    void keyPressEvent(QKeyEvent *event) override;
//    void keyReleaseEvent(QKeyEvent *event) override;


private:
    void setupVertexAttribs();

    bool m_core;
    int m_xRot;
    int m_yRot;
    int m_zRot;
    float m_scale;
    GLWidget* reference;
    QPoint m_lastPos;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_logoVbo;
    QOpenGLShaderProgram *m_program;
    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    static bool m_transparent;

    int total_vertices;
    int total_faces;

    boolean isTranslationOn = true;
    boolean isViewerMode = false;

    GLfloat coords[6][4][3] = {
        { { +1.0, -1.0, +1.0 }, { +1.0, -1.0, -1.0 }, { +1.0, +1.0, -1.0 }, { +1.0, +1.0, +1.0 } },
        { { -1.0, -1.0, -1.0 }, { -1.0, -1.0, +1.0 }, { -1.0, +1.0, +1.0 }, { -1.0, +1.0, -1.0 } },
        { { +1.0, -1.0, -1.0 }, { -1.0, -1.0, -1.0 }, { -1.0, +1.0, -1.0 }, { +1.0, +1.0, -1.0 } },
        { { -1.0, -1.0, +1.0 }, { +1.0, -1.0, +1.0 }, { +1.0, +1.0, +1.0 }, { -1.0, +1.0, +1.0 } },
        { { -1.0, -1.0, -1.0 }, { +1.0, -1.0, -1.0 }, { +1.0, -1.0, +1.0 }, { -1.0, -1.0, +1.0 } },
        { { -1.0, +1.0, +1.0 }, { +1.0, +1.0, +1.0 }, { +1.0, +1.0, -1.0 }, { -1.0, +1.0, -1.0 } }
    };

    CircuitBase* circuitBase;
    std::list<BasicMaterial*> materials;

    EditMode activeMode = DEFAULT_MODE;
};


#endif
