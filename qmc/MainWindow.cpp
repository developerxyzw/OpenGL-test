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

	GLuint VBO, EBO;
	f->glGenBuffers(1, &VBO);
	f->glGenBuffers(1, &EBO);

	f->glGenVertexArrays(1, &VAO);
	f->glBindVertexArray(VAO);
	f->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	f->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	f->glEnableVertexAttribArray(0);
	f->glBindVertexArray(0);


	const char *vsh_s = "#version 300 es\n"
		"layout(location = 0) in vec3 position;"
		"void main()"
		"{"
		"	gl_Position = vec4(position.x, position.y, position.z, 1.0);"
		"}";
	GLuint vsh_p;
	vsh_p = f->glCreateShader(GL_VERTEX_SHADER);
	f->glShaderSource(vsh_p, 1, &vsh_s, NULL);
	f->glCompileShader(vsh_p);
	GLint success;
	GLchar infoLog[512];
	f->glGetShaderiv(vsh_p, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		f->glGetShaderInfoLog(vsh_p, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const char *fsh_s = "#version 300 es\n"
		"precision lowp float;"
		"out vec4 color;"
		"void main()"
		"{"
		"	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
		"}";
	GLuint fsh_p;
	fsh_p = f->glCreateShader(GL_FRAGMENT_SHADER);
	f->glShaderSource(fsh_p, 1, &fsh_s, NULL);
	f->glCompileShader(fsh_p);
	f->glGetShaderiv(fsh_p, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		f->glGetShaderInfoLog(fsh_p, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	sh_p = f->glCreateProgram();
	f->glAttachShader(sh_p, vsh_p);
	f->glAttachShader(sh_p, fsh_p);
	f->glLinkProgram(sh_p);
	f->glDeleteShader(vsh_p);
	f->glDeleteShader(fsh_p);
	f->glGetProgramiv(fsh_p, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		f->glGetProgramInfoLog(fsh_p, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

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
	f->glUseProgram(sh_p);



	f->glBindVertexArray(VAO);
	f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	f->glBindVertexArray(0);
}
