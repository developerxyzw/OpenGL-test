#include "Texture.h"
#include "STB_Image.h"
#include <QOpenGLExtraFunctions>
#include <qdebug.h>

//Just load texture
unsigned LoadTexture(QOpenGLExtraFunctions *f, char* path)
{
	unsigned int texture;
	f->glGenTextures(1, &texture);
	f->glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	f->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		f->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		f->glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		qInfo() << "Failed to load texture";
	}
	stbi_image_free(data);
	return texture;
}