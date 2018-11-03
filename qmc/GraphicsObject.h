#pragma once
#include <QOpenGLExtraFunctions>
#include <QMatrix4x4>
#include <QVector3D>
#include "Shader.h"
#include "VAO.h"

class GraphicsObject
{
protected:
	QOpenGLExtraFunctions *f;
	Shader *sh;
	VAO *vao;
	QVector3D pos;
	float xa=0, ya=0, za=0;
public:
	GraphicsObject(QOpenGLExtraFunctions *functions)
		: f(functions)
	{
		vao = new VAO(f);
	}

	~GraphicsObject()
	{
		delete vao;
	}

	virtual void init() {}

	void draw(QMatrix4x4 PROJ, QMatrix4x4 VIEW)
	{
		sh->use();
		QMatrix4x4 MODEL;
		MODEL.setToIdentity();
		MODEL.translate(pos.x(), pos.y(), pos.z());
		MODEL.rotate(xa, 1, 0, 0);
		MODEL.rotate(ya, 0, 1, 0);
		MODEL.rotate(za, 0, 0, 1);
		sh->setMat4("model", MODEL);
		sh->setMat4("view", VIEW);
		sh->setMat4("proj", PROJ);
		vao->bind();
		render();
		vao->unbind();
	}

	virtual void render() {}

	void setPos(QVector3D pos)
	{
		this->pos = pos;
	}

	void setA(float x, float y, float z)
	{
		xa = x, ya = y, za = z;
	}
};