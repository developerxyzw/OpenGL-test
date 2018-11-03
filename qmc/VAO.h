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

	//Vertices structure: X-Y-Z-S-T
	//***_size = size in BYTES
	//Type: GL_FLOAT
	void create(GLfloat *vertices, GLuint vert_size, GLuint *indices, GLuint ind_size)
	{
		f->glGenBuffers(1, &vbo);
		f->glGenBuffers(1, &ebo);
		f->glGenVertexArrays(1, &vao);
		f->glBindVertexArray(vao);
		f->glBindBuffer(GL_ARRAY_BUFFER, vbo);
		f->glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);
		f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, GL_STATIC_DRAW);
		f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (GLvoid*)0);
		f->glEnableVertexAttribArray(0);
		f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (GLvoid*)12);
		f->glEnableVertexAttribArray(1);
		f->glBindVertexArray(0);
	}
	void create(GLfloat *vertices, GLuint vert_size)
	{
		f->glGenBuffers(1, &vbo);
		f->glGenVertexArrays(1, &vao);
		f->glBindVertexArray(vao);
		f->glBindBuffer(GL_ARRAY_BUFFER, vbo);
		f->glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);
		f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (GLvoid*)0);
		f->glEnableVertexAttribArray(0);
		f->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (GLvoid*)12);
		f->glEnableVertexAttribArray(1);
		f->glBindVertexArray(0);
	}
};