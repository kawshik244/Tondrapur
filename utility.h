#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"
#include <map>

void drawCircle(unsigned int& cubeVAO, Shader& lightingShader, glm::vec3 translateVec, glm::vec3 scaleVec, glm::vec3 rotateVec, glm::vec3 colorVec, glm::mat4 als) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateMatrix, scaleMatrix, model;

	for (int i = 0; i < 360; i++) {
		translateMatrix = glm::translate(identityMatrix, translateVec);
		rotateMatrix = glm::rotate(identityMatrix, glm::radians((float)i), rotateVec);
		scaleMatrix = glm::scale(identityMatrix, scaleVec);

		model = als * translateMatrix * rotateMatrix * scaleMatrix;
		drawCube(cubeVAO, lightingShader, model, colorVec[0], colorVec[1], colorVec[2]);
	}

}
#pragma once

void drawCircleWithTexture(unsigned int& cubeVAO, Shader& lightingShaderWithTexture, glm::vec3 translateVec, glm::vec3 scaleVec, glm::vec3 rotateVec, glm::vec3 colorVec, map<string, Cube>& textures, glm::mat4 als) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateMatrix, scaleMatrix, model;

	for (int i = 0; i < 360; i++) {
		translateMatrix = glm::translate(identityMatrix, translateVec);
		rotateMatrix = glm::rotate(identityMatrix, glm::radians((float)i), rotateVec);
		scaleMatrix = glm::scale(identityMatrix, scaleVec);

		model = als * translateMatrix * rotateMatrix * scaleMatrix;
		textures["wood3"].drawCubeWithTexture( lightingShaderWithTexture,model);
	}

}

#pragma once
