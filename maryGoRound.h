#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"
#include "cylinder.h"
#include "components.h"


void maryGoRound(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 als, float r) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, .02f, 0.9f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.3f, 2.0f, .4f));
	model = als * translateMatrix * scaleMatrix;
	Cylinder cylinder = Cylinder();
	cylinder.drawCylinder(lightingShader, model, 0.7, 0.33, 0.24);

	//rope

	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 1.8f, 0.9f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * identityMatrix * translateMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);

	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 1.8f, 0.9f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 90), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * identityMatrix * translateMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);

	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 1.8f, 0.9f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 180), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * identityMatrix * translateMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);



	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 1.8f, 0.9f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 270), glm::vec3(0.0f, 1.0f, 0.0f));
	model = als * identityMatrix * translateMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);

	float rr1 = r - 15.0f;
	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, -0.9f, 0.8f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rr1), glm::vec3(0.0f, 1.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 2.5f, 5.5f));
	model = als * model * translateMatrix * rotateYMatrix * scaleMatrix;
	object(cubeVAO, lightingShader, model);

	float rr2 = r - 105.0f;
	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, -0.9f, 0.8f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rr2), glm::vec3(0.0f, 1.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 2.5f, 5.5f));
	model = als * model * translateMatrix * rotateYMatrix * scaleMatrix;
	object(cubeVAO, lightingShader, model);

	float rr3 = r - 195.0f;
	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, -0.9f, 0.8f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rr3), glm::vec3(0.0f, 1.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 2.5f, 5.5f));
	model = als * model * translateMatrix * rotateYMatrix * scaleMatrix;
	object(cubeVAO, lightingShader, model);

	float rr4 = r - 285.0f;
	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, -0.9f, 0.8f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rr4), glm::vec3(0.0f, 1.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 2.5f, 5.5f));
	model = als * model * translateMatrix * rotateYMatrix * scaleMatrix;
	object(cubeVAO, lightingShader, model);

}
#pragma once
