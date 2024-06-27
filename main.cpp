#include <cmath>
#include <cstring>
#include<string>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"



// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES                  /      COLORS           //    transform               tex or color: 1 = tex, 0 = color
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,    0.0f, -0.15f,  0.0f,    0.0f,// Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,    0.0f, -0.15f,  0.0f,    0.0f,// Lower left corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f,    0.0f, -0.15f,  0.0f,    0.0f,// Lower left corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f,    0.0f, -0.15f,  0.0f,    0.0f,// Lower left corner
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f,    0.0f, -0.15f,  0.0f,    0.0f,// Lower left corner
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,    0.0f, -0.15f,  0.0f,    0.0f,// Lower left corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

// Vertices coordinates
GLfloat bgvertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  // tex or color: 1 = tex, 0 = color
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,    1.0f,// Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,    1.0f,// Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,    1.0f,// Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f,    1.0f // Lower right corner
};

// Indices for vertices order
GLuint bgindices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);


	Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(bgvertices, sizeof(bgvertices));
	EBO EBO1(bgindices, sizeof(bgindices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 4, 1, GL_FLOAT, 9 * sizeof(float), (void*)(8 * sizeof(float)));

	VAO VAO2;
	VAO2.Bind();
	VBO VBO2(vertices, sizeof(vertices));
	EBO EBO2(indices, sizeof(indices));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 10 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 10 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 3, GL_FLOAT, 10 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 4, 1, GL_FLOAT, 10 * sizeof(float), (void*)(9 * sizeof(float)));


	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Textures
	const std::string path = "../link.png";
	Texture link(&path[0], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	link.texUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		link.Bind();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		VAO2.Bind();
		glUniform1f(uniID,0.5f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	VAO2.Delete();
	VBO2.Delete();
	EBO2.Delete();
	link.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}