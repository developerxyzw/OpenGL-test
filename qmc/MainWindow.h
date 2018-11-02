#pragma once

#include <QOpenGLWindow>
#include <qopenglextrafunctions.h>
#include <qmatrix4x4.h>

class MainWindow : public QOpenGLWindow
{
	Q_OBJECT;
	QOpenGLExtraFunctions *f;
	QMatrix4x4 PROJ, VIEW, MODEL;
	qreal FOV = 90;

	GLuint VAO;
	GLuint sh_p;
	

public:
	MainWindow(QOpenGLContext *context, QOpenGLWindow *parent = Q_NULLPTR);

public:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
};
