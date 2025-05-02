#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawCube.h"
#include<map>
#include "cube.h"
#include "curve.h"
using namespace std;




void ferrisWheel(unsigned int& cubeVAO,BezierCurve& ferrisWheelCurve, Shader& lightingShader, Shader& lightingShaderWithTexture, map<string, Cube>& textures, glm::mat4 als, float FERRIS_WHEEL_Z) {
	glm::mat4 identityMatrix = glm::mat4(1.0f);
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, rotationMatrix,baseTranslateMatrix;

	glm::vec3 baseTranslationVec = glm::vec3(2.7f, 3.5f, 7.0f);
	baseTranslateMatrix = glm::translate(identityMatrix, baseTranslationVec);
	float gap = 1.0f;

	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
	rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	rotationMatrix = glm::rotate(identityMatrix,glm::radians(FERRIS_WHEEL_Z), glm::vec3(0.0f, 0.0f, 1.0f)) * rotateYMatrix * rotateZMatrix ;

	for (int i = 0; i < 2; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1], baseTranslationVec[2]+(i * gap)));
		model = als * translateMatrix * rotationMatrix * scaleMatrix;
		ferrisWheelCurve.drawBezierCurvewithTexture(lightingShaderWithTexture, model,glm::vec3(1.0f,1.0f,1.0f));
	}

	//middle handle
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.2f, gap+1.0));
	rotateZMatrix = glm::rotate(identityMatrix, glm::radians(FERRIS_WHEEL_Z ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = als * baseTranslateMatrix * rotateZMatrix * scaleMatrix;
	model = model * glm::translate(identityMatrix, glm::vec3(-0.6f, -0.5f, -0.2f));
	textures["wood2"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//holder
	translateMatrix = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1]-0.5, baseTranslationVec[2]));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 4.f, 0.3f));
	model = als * translateMatrix * scaleMatrix;
	model = model * glm::translate(identityMatrix, glm::vec3(-0.4f, -0.8f, -1.6f));
	textures["wood3"].drawCubeWithTexture(lightingShaderWithTexture, model);

	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 4.0f, 0.3f));
	model = als * translateMatrix * scaleMatrix;
	model = model * glm::translate(identityMatrix, glm::vec3(-0.4f, -0.8f, 6.0+gap-1.6f));
	textures["wood3"].drawCubeWithTexture(lightingShaderWithTexture, model);
	
	for (int i = 0; i < 4; i++) {

		scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.2f, 0.1f, 0.1f));
		rotateZMatrix = glm::rotate(identityMatrix, glm::radians(FERRIS_WHEEL_Z+(i*90.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		model = als * baseTranslateMatrix * rotateZMatrix * scaleMatrix;
		textures["wood2"].drawCubeWithTexture(lightingShaderWithTexture, model);

		translateMatrix  = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1], baseTranslationVec[2]+gap));
		rotateZMatrix = glm::rotate(identityMatrix, glm::radians(FERRIS_WHEEL_Z + (i * 90.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		model = als * translateMatrix * rotateZMatrix * scaleMatrix;
		textures["wood2"].drawCubeWithTexture(lightingShaderWithTexture, model);
	}

	
	for (int i = 0; i < 4; i++) {
		//backbar-seat
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 0.1));
		rotateZMatrix = glm::rotate(identityMatrix, glm::radians(FERRIS_WHEEL_Z + (i * 90.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		translateMatrix = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1], baseTranslationVec[2]));
		model = als * translateMatrix * rotateZMatrix * scaleMatrix;
		translateMatrix = glm::translate(identityMatrix, glm::vec3(2.1f, -0.5f, 0.0f));
		model = model * translateMatrix;
		model = model * glm::rotate(identityMatrix, glm::radians(-(FERRIS_WHEEL_Z + (i * 90.0f))), glm::vec3(0.0f, 0.0f, 1.0f));
		model = model * glm::translate(identityMatrix, glm::vec3(-0.5f, -0.5f, 0.0f));
		textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

		//frontbar-seat
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 0.1));
		rotateZMatrix = glm::rotate(identityMatrix, glm::radians(FERRIS_WHEEL_Z + (i * 90.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		translateMatrix = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1], baseTranslationVec[2] + gap-0.4));
		model = als * translateMatrix * rotateZMatrix * scaleMatrix;
		translateMatrix = glm::translate(identityMatrix, glm::vec3(2.1f, -0.5f, 0.0));
		model = model * translateMatrix;
		model = model * glm::rotate(identityMatrix, glm::radians(-(FERRIS_WHEEL_Z + (i * 90.0f))), glm::vec3(0.0f, 0.0f, 1.0f));
		model = model * glm::translate(identityMatrix, glm::vec3(-0.5f, -0.5f, 0.0));
		textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

		//base-bar
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, gap-0.4));
		rotateZMatrix = glm::rotate(identityMatrix, glm::radians(FERRIS_WHEEL_Z + (i * 90.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		translateMatrix = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1] , baseTranslationVec[2]));
		model = als *translateMatrix * rotateZMatrix * scaleMatrix;
		translateMatrix = glm::translate(identityMatrix, glm::vec3(2.1f, -0.5f, 0.0f));
		model = model * translateMatrix;
		model = model * glm::rotate(identityMatrix, glm::radians(-(FERRIS_WHEEL_Z + (i * 90.0f))), glm::vec3(0.0f, 0.0f, 1.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0));
		model = model * glm::translate(identityMatrix, glm::vec3(-0.5f, -0.5f, 0.0f)) *scaleMatrix;
		textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

		//back-bar
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, gap - 0.4));
		rotateZMatrix = glm::rotate(identityMatrix, glm::radians(FERRIS_WHEEL_Z + (i * 90.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
		translateMatrix = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1], baseTranslationVec[2]));
		model = als * translateMatrix * rotateZMatrix * scaleMatrix;
		translateMatrix = glm::translate(identityMatrix, glm::vec3(2.1f, -0.5f, 0.0f));
		model = model * translateMatrix;
		model = model * glm::rotate(identityMatrix, glm::radians(-(FERRIS_WHEEL_Z + (i * 90.0f))), glm::vec3(0.0f, 0.0f, 1.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 1.0));
		model = model * glm::translate(identityMatrix, glm::vec3(0.0f, -0.5f, 0.0f)) * scaleMatrix;
		textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

	}


}


#pragma once
