#include "MainWindow.h"
#include <QSurfaceFormat>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QOpenGLContext *context, QOpenGLWindow *parent)
	: QOpenGLWindow(context, QOpenGLWindow::UpdateBehavior::NoPartialUpdate, parent)
{
	//Do the *global init* here
}

void MainWindow::initializeGL()
{
	//Do the *OpenGL init* here
	QOpenGLContext *c = this->context();
	c->makeCurrent(this);
	f = c->extraFunctions();
	char AAAAA[512];
	sprintf(AAAAA, "QOpenGLExtraFunctions *f = %i\nOpenGL%s version %s\n", (int)f, (c->isOpenGLES() ? "ES" : ""), f->glGetString(GL_VERSION));
	qInfo() << AAAAA;
	qInfo() << "Widget OpenGl: " << format().majorVersion() << "." << format().minorVersion();
	qInfo() << "Context valid: " << context()->isValid();
	qInfo() << "Really used OpenGl: " << context()->format().majorVersion() << "." << context()->format().minorVersion();
	qInfo() << "OpenGl information: VENDOR:       " << (const char*)f->glGetString(GL_VENDOR);
	qInfo() << "                    RENDERDER:    " << (const char*)f->glGetString(GL_RENDERER);
	qInfo() << "                    VERSION:      " << (const char*)f->glGetString(GL_VERSION);
	qInfo() << "                    GLSL VERSION: " << (const char*)f->glGetString(GL_SHADING_LANGUAGE_VERSION);

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};
	GLuint indices[] = {
		0, 1, 2,
		1, 2, 3,
	};

	vao = new VAO(f);
	vao->create((GLuint*)(GLfloat*)vertices, sizeof(vertices), (GLuint*)(GLfloat*)indices, sizeof(indices), GL_FLOAT);

	sh = new Shader(f, "./Shader/basic.v", "./Shader/basic.f");

	f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void MainWindow::resizeGL(int w, int h)
{
	f->glViewport(0, 0, w, h);
	PROJ.setToIdentity();
	PROJ.perspective(FOV, w / (float)h, 0.1, 256);
	update();
}

void MainWindow::paintGL()
{
	makeCurrent();
	f->glClear(GL_COLOR_BUFFER_BIT);
	sh->use();

	vao->bind();
	f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	vao->unbind();
}
