#pragma once
#include <QOpenGLExtraFunctions>

class VAO
{
	GLuint vbo, vao, ebo;
	QOpenGLExtraFunctions *f;
public:
	VAO(QOpenGLExtraFunctions *functions)
		: f(functions)
	{
		//
	}
	~VAO() {}

	void bind()
	{
		f->glBindVertexArray(vao);
	}

	void unbind()
	{
		f->glBindVertexArray(0);
	}

	void create(GLuint *vertices, GLuint vert_size, GLuint *indices, GLuint ind_size, GLenum type)
	{
		f->glGenBuffers(1, &vbo);
		f->glGenBuffers(1, &ebo);
		f->glGenVertexArrays(1, &vao);
		f->glBindVertexArray(vao);
		f->glBindBuffer(GL_ARRAY_BUFFER, vbo);
		f->glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_DYNAMIC_DRAW);
		f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, GL_STATIC_DRAW);
		f->glVertexAttribPointer(0, 3, type, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		f->glEnableVertexAttribArray(0);
		f->glBindVertexArray(0);
	}
};