#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
class Shader {
public:
    unsigned int ID;
	Shader() {
		ID = 0;
	}

	Shader(Shader& other) {
		this->ID = other.ID;
	}
    Shader(const char *vertexPath, const char *fragmentPath) {
    	// Reading file
    	std::string vertexCode, fragmentCode;
		try {
			std::stringstream vShaderStream, fShaderStream;
			
			std::ifstream vShaderFile(vertexPath);
    		std::ifstream fShaderFile(fragmentPath);				
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			
			vShaderFile.close();
			fShaderFile.close();
			
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();			
		}	
		catch(std::ifstream::failure& e) {
			std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "<<e.what()<<std::endl;
		}
		
		const char *vShaderCode = vertexCode.c_str();
		const char *fShaderCode = fragmentCode.c_str();
		// Create shader	
		unsigned int vertexShader;
		
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);		
		checkCompileErrors(vertexShader, "VERTEX");
		
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		checkCompileErrors(fragmentShader, "FRAGMENT");
		
		// Create program
		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		
		// delete shader
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	
	void use() {
		glUseProgram(ID);
	}
	
	void setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	
	void setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	
	void setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
private:
	void checkCompileErrors(unsigned int shader, std::string type) {
		int success;
		char infoLog[1024];
		if(type == "PROGRAM") {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if(!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout<<"ERROR::PROGRAM::LINK: "<<infoLog<<std::endl;
			}
		}
		else {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if(!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout<<"ERROR::SHADER"<<type<<"::LINK: "<<infoLog<<std::endl;
			}
		}
	}
};
#endif

