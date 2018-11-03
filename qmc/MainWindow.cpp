#include "MainWindow.h"
#include "Texture.h"
#include <QSurfaceFormat>
#include <QThread>
#include <QTime>
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
	sprintf(AAAAA, "QOpenGLExtraFunctions *f = %i", (int)f);
	qInfo() << AAAAA;
	qInfo() << "Widget OpenGl: " << format().majorVersion() << "." << format().minorVersion();
	qInfo() << "Context valid: " << context()->isValid();
	qInfo() << "Really used OpenGl: " << context()->format().majorVersion() << "." << context()->format().minorVersion();
	qInfo() << "OpenGl information: VENDOR:       " << (const char*)f->glGetString(GL_VENDOR);
	qInfo() << "                    RENDERDER:    " << (const char*)f->glGetString(GL_RENDERER);
	qInfo() << "                    VERSION:      " << (const char*)f->glGetString(GL_VERSION);
	qInfo() << "                    GLSL VERSION: " << (const char*)f->glGetString(GL_SHADING_LANGUAGE_VERSION);

	f->glEnable(GL_BLEND);// you enable blending function
	f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	f->glEnable(GL_TEXTURE_2D_MULTISAMPLE);

	//Set up VAO
	GLfloat vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f   // top left 
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3,
	};

	vao = new VAO(f);
	vao->create(vertices, sizeof(vertices), indices, sizeof(indices));

	//Create Shaders
	sh = new Shader(f, "./Shader/basic.v", "./Shader/basic.f");

	//Load textures
	texture = LoadTexture(f, "./Textures/logo.png", true);
	texture2 = LoadTexture(f, "./Textures/logo2.png", true);

	//Finalizing OpenGL init
	f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

//Set up viewport when we resize
void MainWindow::resizeGL(int w, int h)
{
	f->glViewport(0, 0, w, h);
	PROJ.setToIdentity();
	PROJ.perspective(45, w / (float)h, 0.1, 256);
	update();
}

//Render everything
void MainWindow::paintGL()
{
	makeCurrent();
	f->glClear(GL_COLOR_BUFFER_BIT);

	sh->use();
	f->glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	f->glBindTexture(GL_TEXTURE_2D, texture);
	sh->setInt("texture0", texture);
	f->glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
	f->glBindTexture(GL_TEXTURE_2D, texture2);
	//sh->setInt("texture1", texture2); //IDK Y I dun need it there, but in tex0 I need it..
	QMatrix4x4 MODEL;
	MODEL.rotate(-55.f, 1.f, 0.f, 0.f);
	sh->setMat4("model", MODEL);
	VIEW.setToIdentity();
	VIEW.translate(0.f, 0.f, -3.f);
	sh->setMat4("view", VIEW);
	sh->setMat4("proj", PROJ);
	vao->bind();
	f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	vao->unbind();

	QThread::currentThread()->msleep(1000 / 30);
	update();
}
