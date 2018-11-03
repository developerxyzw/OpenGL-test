#pragma once
#include "GraphicsObject.h"

//Textures: Z+, Z-, X-, X+, Y+, Y-
class Cube : public GraphicsObject
{
	GLuint tex;
public:
	Cube(QOpenGLExtraFunctions *functions, GLuint tex)
		: GraphicsObject(functions)
		, tex(tex)
	{}

	virtual void init()
	{
		float vertices[] = {
			//Front
			0.f, 0.f, 0.f,  0.0f, 0.0f,
			1.f, 0.f, 0.f,  1.0f, 0.0f,
			1.f, 1.f, 0.f,  1.0f, 1.0f,
			1.f, 1.f, 0.f,  1.0f, 1.0f,
			0.f, 1.f, 0.f,  0.0f, 1.0f,
			0.f, 0.f, 0.f,  0.0f, 0.0f,

			//Back
			0.f, 0.f, 1.f,  0.0f, 0.0f,
			1.f, 0.f, 1.f,  1.0f, 0.0f,
			1.f, 1.f, 1.f,  1.0f, 1.0f,
			1.f, 1.f, 1.f,  1.0f, 1.0f,
			0.f, 1.f, 1.f,  0.0f, 1.0f,
			0.f, 0.f, 1.f,  0.0f, 0.0f,

			//Left
			0.f, 1.f, 1.f,  1.0f, 0.0f,
			0.f, 1.f, 0.f,  1.0f, 1.0f,
			0.f, 0.f, 0.f,  0.0f, 1.0f,
			0.f, 0.f, 0.f,  0.0f, 1.0f,
			0.f, 0.f, 1.f,  0.0f, 0.0f,
			0.f, 1.f, 1.f,  1.0f, 0.0f,

			//Right
			1.f, 1.f, 1.f,  1.0f, 0.0f,
			1.f, 1.f, 0.f,  1.0f, 1.0f,
			1.f, 0.f, 0.f,  0.0f, 1.0f,
			1.f, 0.f, 0.f,  0.0f, 1.0f,
			1.f, 0.f, 1.f,  0.0f, 0.0f,
			1.f, 1.f, 1.f,  1.0f, 0.0f,

			//Up
			0.f, 1.f, 0.f,  0.0f, 1.0f,
			1.f, 1.f, 0.f,  1.0f, 1.0f,
			1.f, 1.f, 1.f,  1.0f, 0.0f,
			1.f, 1.f, 1.f,  1.0f, 0.0f,
			0.f, 1.f, 1.f,  0.0f, 0.0f,
			0.f, 1.f, 0.f,  0.0f, 1.0f,

			//Down
			0.f, 0.f, 0.f,  0.0f, 1.0f,
			1.f, 0.f, 0.f,  1.0f, 1.0f,
			1.f, 0.f, 1.f,  1.0f, 0.0f,
			1.f, 0.f, 1.f,  1.0f, 0.0f,
			0.f, 0.f, 1.f,  0.0f, 0.0f,
			0.f, 0.f, 0.f,  0.0f, 1.0f,
		};
		vao->create(vertices, sizeof(vertices));

		sh = new Shader(f, "./Shader/basic.v", "./Shader/basic.f");
	}

	virtual void render() Q_DECL_OVERRIDE
	{
		f->glActiveTexture(GL_TEXTURE0);
		f->glBindTexture(GL_TEXTURE_2D, tex);
		sh->setInt("texture0", tex);
		f->glDrawArrays(GL_TRIANGLES, 0, 36*3);
		f->glBindTexture(GL_TEXTURE_2D, 0);
	}
};