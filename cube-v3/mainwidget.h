// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    ~MainWidget();

    QSize sizeHint() const override;

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();
    void initTextures();

private:
    QOpenGLShaderProgram program;
    GeometryEngine *geometries = nullptr;

    QOpenGLTexture *texture = nullptr;

    QMatrix4x4 projection;

    // Computed in paintGL(), used in mouseMoveEvent()
    QMatrix4x4 modelmatrix;       // object frame -> world frame
    QMatrix4x4 cameraposmatrix;   // view(camera) frame -> world frame

    QVector2D lastMousePosition;

    // Object pose (object frame w.r.t. world frame), initialized in initScene()
    QVector3D objectPosition;
    QQuaternion objectOrientation;

    // Camera pose (eye, look-at target, up vector in world frame), initialized in initScene()
    QVector3D cameraPosition;
    QVector3D cameraTarget;
    QVector3D cameraUp;

    void initScene();

    // Rotate the object about an axis given in view(camera) coordinates.
    // Shared by mouse drag and keyboard input.
    void rotateAboutViewAxis(const QVector3D &n_view, float angleDegrees);
};

#endif // MAINWIDGET_H
