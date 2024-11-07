#include <cmath>
#include <cstring>
#include<string>
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"


GLfloat triForceVertices[] ={
	//               COORDINATES                  /      COLORS           //    tex or color: 1 = tex, 0 = color
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,   0.0f,
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,   0.0f,
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f,   0.0f,
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f,   0.0f,
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f,   0.0f,
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f,   0.0f
};

GLuint triForceIndices[] = {
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
};

GLfloat linkVertices[] ={
	//     COORDINATES     /        COLORS      /   TexCoord  // tex or color: 1 = tex, 0 = color
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,    1.0f,
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,    1.0f,
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,    1.0f,
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f,    1.0f
};


GLuint linkIndices[] ={
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};


GLfloat pyramidVertices[] ={
	// positions          // colors
	0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
   -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
};

GLuint pyramidIndices[] = {
	0, 1, 2,	// front
	0, 1, 3,	// right
	0, 3, 4,	// back
	0, 2, 4,	// left
	1, 2, 3,	// bottom
	2, 3, 4
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

GLfloat roomVertices[] = {
    // Positions          // Colors           // Normals
    // Floor
    -1.0f, -1.0f, -1.0f,  0.3f, 0.15f, 0.05f,   0.0f, -1.0f, 0.0f,
     1.0f, -1.0f, -1.0f,  0.3f, 0.15f, 0.05f,   0.0f, -1.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  0.3f, 0.15f, 0.05f,   0.0f, -1.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  0.3f, 0.15f, 0.05f,   0.0f, -1.0f, 0.0f,
    // Ceiling
    -1.0f,  1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  0.0f, -1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  0.0f, -1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  0.3f, 0.15f, 0.05f,  0.0f, -1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  0.3f, 0.15f, 0.05f,  0.0f, -1.0f, 0.0f,
    // Back Wall
    -1.0f, -1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  0.0f, 0.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  0.0f, 0.0f, -1.0f,
     1.0f,  1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  0.0f, 0.0f, -1.0f,
     1.0f, -1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  0.0f, 0.0f, -1.0f,
    // Left Wall
    -1.0f, -1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  -1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  0.3f, 0.15f, 0.05f,  -1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  0.3f, 0.15f, 0.05f,  -1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  -1.0f, 0.0f, 0.0f,
    // Right Wall
     1.0f, -1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  0.3f, 0.15f, 0.05f,  -1.0f, 0.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  0.3f, 0.15f, 0.05f,  -1.0f, 0.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  0.3f, 0.15f, 0.05f,  -1.0f, 0.0f, 0.0f,
};

GLuint roomIndices[] = {
	// Floor
	0, 1, 2,
	2, 3, 0,

	// Ceiling
	4, 5, 6,
	6, 7, 4,

	// Back Wall
	8, 9, 10,
	10, 11, 8,

	// Left Wall
	12, 13, 14,
	14, 15, 12,

	// Right Wall
	16, 17, 18,
	18, 19, 16
};


int main(){
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);


	Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");
	// create Link
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(linkVertices, sizeof(linkVertices));
	EBO EBO1(linkIndices, sizeof(linkIndices));
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 1, GL_FLOAT, 9 * sizeof(float), (void*)(8 * sizeof(float)));

	// create Tri Force
	VAO VAO2;
	VAO2.Bind();
	VBO VBO2(triForceVertices, sizeof(triForceVertices));
	EBO EBO2(triForceIndices, sizeof(triForceIndices));
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 1, GL_FLOAT, 7 * sizeof(float), (void*)(6 * sizeof(float)));

	// create pyramid
	VAO VAO3;
	VAO3.Bind();
	VBO VBO3(pyramidVertices, sizeof(pyramidVertices));
	EBO EBO3(pyramidIndices, sizeof(pyramidIndices));
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// create room
	VAO VAO4;
	VAO4.Bind();
	VBO VBO4(roomVertices, sizeof(roomVertices));
	EBO EBO4(roomIndices, sizeof(roomIndices));
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 4, 3, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
	VAO2.Unbind();
	VBO2.Unbind();
	EBO2.Unbind();
	VAO3.Unbind();
	VBO3.Unbind();
	EBO3.Unbind();
	VAO4.Unbind();
	VBO4.Unbind();
	EBO4.Unbind();

	// lighting
	Shader lightShader("../shaders/light.vert", "../shaders/light.frag");
	VAO lightVAO;
	lightVAO.Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// Textures
	const std::string path = "../link.png";
	Texture link(&path[0], GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	link.texUnit(shaderProgram, "tex0", 0);


	glEnable(GL_DEPTH_TEST);

	Camera camera(800, 800, glm::vec3(0.0f, 0.0f, 6.0f));

	while (!glfwWindowShouldClose(window)){
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// modify and draw light source
		lightShader.Activate();
		camera.Matrix(45.0f, 0.1f, 100.0f, lightShader, "camera");
		lightVAO.Bind();

		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::rotate(lightModel, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		lightModel = glm::rotate(lightModel, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		lightModel = glm::translate(lightModel, glm::vec3(0.0f, 0.0f, 3.0f));
		lightModel = glm::scale(lightModel, glm::vec3(1.20f, 1.20f, 1.20f));
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glm::vec3 lightPos = glm::vec3(lightModel[3]);

		shaderProgram.Activate();
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		// Handles camera inputs
		camera.Inputs(window);

		// Updates and exports the camera matrix to the Vertex Shader
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camera");


		float rotation = 0.0f;
		float width = 800.0f;
		float height = 800.0f;

		glm::mat4 model = glm::mat4(1.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		int opacityLoc = glGetUniformLocation(shaderProgram.ID, "opacity");

		// modify and draw Link
		link.Bind();
		VAO1.Bind();

		model = glm::translate(model, glm::vec3(0.0f, 0.1f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// modify and draw Tri Force
		VAO2.Bind();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		model = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0.0f, -0.06f, 0.1f));
		model = glm::scale(model, glm::vec3(0.9f, 1.1f, 1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(opacityLoc, 0.15f);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glDisable(GL_BLEND);

		// modify and draw pyramid
		VAO3.Bind();
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.05f, 1.0f));
		model = glm::scale(model, glm::vec3(0.20f, 0.20f, 0.20f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(opacityLoc, 0.15f);

		glDrawElements(GL_TRIANGLES, sizeof(pyramidIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

		// modify and draw room
		VAO4.Bind();
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1f(opacityLoc, 1.0f);
		glDrawElements(GL_TRIANGLES, sizeof(roomIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

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