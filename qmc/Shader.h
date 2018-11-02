#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLExtraFunctions>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;
	QOpenGLExtraFunctions *f;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------
	Shader(QOpenGLExtraFunctions *functions, const char* vertexPath, const char* fragmentPath)
		: f(functions)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			qInfo() << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ";
		}
		const char* vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = f->glCreateShader(GL_VERTEX_SHADER);
		f->glShaderSource(vertex, 1, &vShaderCode, NULL);
		f->glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = f->glCreateShader(GL_FRAGMENT_SHADER);
		f->glShaderSource(fragment, 1, &fShaderCode, NULL);
		f->glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		ID = f->glCreateProgram();
		f->glAttachShader(ID, vertex);
		f->glAttachShader(ID, fragment);
		f->glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		f->glDeleteShader(vertex);
		f->glDeleteShader(fragment);
	}
	// activate the shader
	// ------------------------------------------------------------------------
	void use()
	{
		f->glUseProgram(ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string &name, bool value) const
	{
		f->glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value) const
	{
		f->glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value) const
	{
		f->glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			f->glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				f->glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				qInfo() << "ERROR::SHADER_COMPILATION_ERROR of type: " << type.c_str() << "\n" << infoLog << "\n -- --------------------------------------------------- -- ";
			}
		}
		else
		{
			f->glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				f->glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				qInfo() << "ERROR::PROGRAM_LINKING_ERROR of type: " << type.c_str() << "\n" << infoLog << "\n -- --------------------------------------------------- -- ";
			}
		}
	}
};
#endif