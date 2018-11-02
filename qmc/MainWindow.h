#pragma once

#include <QOpenGLWindow>
#include <qopenglextrafunctions.h>
#include <qmatrix4x4.h>
#include <Shader.h>
#include <VAO.h>

class MainWindow : public QOpenGLWindow
{
	Q_OBJECT;
	QOpenGLExtraFunctions *f;

	VAO *vao;
	Shader *sh;

	GLuint texture;

public:
	MainWindow(QOpenGLContext *context, QOpenGLWindow *parent = Q_NULLPTR);

public:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};
