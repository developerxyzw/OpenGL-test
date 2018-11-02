#pragma once
#include <QOpenGLExtraFunctions>
#include <QMatrix4x4>
#include <QVector3D>
#include "Shader.h"
#include "VAO.h"

//QMatrix4x4::data() : Column-major (pos * MODEL * VIEW * PROJECTION)

class GraphicsObject
{
	QOpenGLExtraFunctions *f;
	Shader *sh;
	VAO *vao;
	QVector3D pos;
public:
	GraphicsObject(QOpenGLExtraFunctions *functions)
		: f(functions)
	{}

	virtual void init() {}

	void draw(QMatrix4x4 PROJ, QMatrix4x4 VIEW)
	{
		sh->use();
		QMatrix4x4 MODEL;
		MODEL.setToIdentity();
		MODEL.translate(-pos.x, -pos.y, -pos.z);
		sh->setMat4("model", MODEL);
		sh->setMat4("view", VIEW);
		sh->setMat4("proj", PROJ);
		vao->bind();
		render(PROJ, VIEW);
		vao->unbind();
	}

	virtual void render(QMatrix4x4 PROJ, QMatrix4x4 VIEW) {}

	void setPos(QVector3D pos)
	{
		this->pos = pos;
	}
};