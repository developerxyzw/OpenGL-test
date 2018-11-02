#include "MainWindow.h"
#include "Texture.h"
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

	//Set up VAO
	GLfloat vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f    // top left 
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
	texture = LoadTexture(f, "d://SOURCE//c-cxx//qt//qmc//qmc//Textures//logo.png");

	//Finalizing OpenGL init
	f->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

//Set up viewport when we resize
void MainWindow::resizeGL(int w, int h)
{
	f->glViewport(0, 0, w, h);
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
	vao->bind();
	f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	vao->unbind();
}
