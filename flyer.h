#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"
#include <map>


void flyer(unsigned int& cubeVAO, Shader& lightingShader,Shader& lightingShaderWithTexture,map<string,Cube>& textures, glm::mat4 als, float FLYER_Y) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


	//BACK
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0f, 0.3f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 6.0f, 0.1f));
	model = als * translateMatrix * scaleMatrix;
	textures["mosaic2"].drawCubeWithTexture(lightingShaderWithTexture, model);
	/*drawCube(cubeVAO, lightingShader, model, 0.02, 0.21, 0.29);*/

	//LEFT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0f, 0.3f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 6.0f, 0.3f));
	model = als * translateMatrix * scaleMatrix;
	textures["mosaic2"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//RIGHT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f, 0.0f, 0.3f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 6.0f, 0.3f));
	model = als * translateMatrix * scaleMatrix;
	textures["mosaic2"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//ROPES
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5f, 0.0f, 0.4f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 6.0f, 0.05f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.75, 0.68, 0.98);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0f, 0.0f, 0.4f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 6.0f, 0.05f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.75, 0.68, 0.98);


	//CARRIER	BACK

	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.08f, (FLYER_Y + 0.1), 0.6f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.43f, 1.0f, 0.05f));
	model = als * translateMatrix * scaleMatrix;
	textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);


	//CARRIER SEAT 1

	//BASE
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.2f, (FLYER_Y + 0.3), 0.7f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.08f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//LEFT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.2f, (FLYER_Y + 0.3), 0.7f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//RIGHT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.6f, (FLYER_Y + 0.3), 0.7f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//CARRIER SEAT 2
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0f, (FLYER_Y + 0.3), 0.7f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.08f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//LEFT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0f, (FLYER_Y + 0.3), 0.7f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//RIGHT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.4f, (FLYER_Y + 0.3), 0.7f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);


}
#pragma once
