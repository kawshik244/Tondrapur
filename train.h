#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawCube.h"
#include<map>
#include "cube.h"
using namespace std;

void train(unsigned int& cubeVAO, BezierCurve& hollowCircleCurve, Shader& lightingShader, Shader& lightingShaderWithTexture, map<string, Cube>& textures,SphereWithTexture& trainWheel, glm::mat4 als,float TRAIN_Z) {
	
	glm::mat4 identityMatrix = glm::mat4(1.0f);
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, rotationMatrix, initModel, temp;
	glm::vec3 baseTranslationVec;


	float gap = 1.0f;
	float TRAIN_BODY_LENGTH = 2.5f;
     
	
	for (int i = 0; i < 12; i++) {

		translateMatrix = glm::translate(identityMatrix, glm::vec3(-10.0f, 0.075, -10.0+(i*3.0)));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(gap + 2.2, 0.05f, 3.0f));
		model = als * translateMatrix * scaleMatrix;
		textures["stone"].drawCubeWithTexture(lightingShaderWithTexture, model);
	}

	//railway tracks
	translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0f, 0.13, -10.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.15f, 35.0f));
	rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
	model = als * translateMatrix * scaleMatrix;
	textures["steel"].drawCubeWithTexture(lightingShaderWithTexture, model);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0+gap, 0.1, -10.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.15f, 35.0f));
	rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
	model = als * translateMatrix * scaleMatrix;
	textures["steel"].drawCubeWithTexture(lightingShaderWithTexture, model);

	//rail tracks
	for (int i = 0; i < 36; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.3, 0.11, -10.0+(i*1.0)));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(gap+0.8, 0.1f, 0.5f));
		rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
		model = als * translateMatrix * scaleMatrix;
		textures["wood3"].drawCubeWithTexture(lightingShaderWithTexture, model);
	}


	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
	rotateZMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix =  rotateYMatrix * rotateZMatrix;
	baseTranslationVec = glm::vec3(-8.5, 0.5, -7.0);

	for (int i = 0; i < 10; i++) {
		translateMatrix = glm::translate(identityMatrix, glm::vec3(baseTranslationVec[0], baseTranslationVec[1], baseTranslationVec[2] + (i * 1.1)));
		model = als * translateMatrix * rotationMatrix * scaleMatrix;
		hollowCircleCurve.drawBezierCurvewithTexture(lightingShaderWithTexture, model, glm::vec3(1.0f, 1.0f, 1.0f));
	}




	for (int i = 0; i < 6; i++) {

		//train body
		
		translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0f, 0.5, -10.0+(i*TRAIN_BODY_LENGTH*1.2)+TRAIN_Z));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(gap+0.2, 1.0, TRAIN_BODY_LENGTH));
		model = als * translateMatrix * scaleMatrix;
		textures["abstract1"].drawCubeWithTexture(lightingShaderWithTexture,model);

		//connector
		if (i < 5) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0f + 0.5f, 0.6, -10.0 + TRAIN_BODY_LENGTH + (i * TRAIN_BODY_LENGTH * 1.2) + TRAIN_Z));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2, 0.2, 0.8));
			model = als * translateMatrix * scaleMatrix;
			textures["abstract1"].drawCubeWithTexture(lightingShaderWithTexture, model);
		}
		else {
			//front glass
			translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.9f, 0.9, -10.0 + TRAIN_BODY_LENGTH + 0.01 + (i * TRAIN_BODY_LENGTH * 1.2) + TRAIN_Z));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(gap, 0.5, 0.05));
			model = als * translateMatrix * scaleMatrix;
			//drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
			textures["glass"].drawCubeWithTexture(lightingShaderWithTexture, model);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.05f, 0.5, -10.0 + TRAIN_BODY_LENGTH + (i * TRAIN_BODY_LENGTH * 1.2) + TRAIN_Z));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(gap+0.3, 0.5, 0.1));
			model = als * translateMatrix * scaleMatrix;
			textures["abstract1"].drawCubeWithTexture(lightingShaderWithTexture, model);

		}


		//SIDE GLASS
		translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0 - 0.01, 0.9, 0.1 - 10.0 + (i * TRAIN_BODY_LENGTH * 1.2) + TRAIN_Z));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.5, TRAIN_BODY_LENGTH - 0.2));
		model = als * translateMatrix * scaleMatrix;
		//drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
		textures["glass"].drawCubeWithTexture(lightingShaderWithTexture, model);

		translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0+gap+0.11, 0.9,0.1 -10.0 + (i * TRAIN_BODY_LENGTH * 1.2) + TRAIN_Z));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, 0.5, TRAIN_BODY_LENGTH-0.2));
		model = als * translateMatrix * scaleMatrix;
		//drawCube(cubeVAO, lightingShader, model, 1.0f, 1.0f, 1.0f);
		textures["glass"].drawCubeWithTexture(lightingShaderWithTexture, model);

		//train wheels
		for (int j = 0; j < 2; j++) {
			translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.9f, 0.3, -9.7 + (j * (TRAIN_BODY_LENGTH*0.75))+ (i * TRAIN_BODY_LENGTH * 1.2) + TRAIN_Z));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 1.0, 1.0));
			rotateXMatrix = glm::rotate(identityMatrix, glm::radians(TRAIN_Z + 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = als * translateMatrix * rotateXMatrix * scaleMatrix;
			trainWheel.drawSphereWithTexture(lightingShaderWithTexture, model);

			translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.9 + gap, 0.3, -9.7 + (j * (TRAIN_BODY_LENGTH * 0.75))+ (i * TRAIN_BODY_LENGTH * 1.2) + TRAIN_Z));
			scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3, 1.0, 1.0));
			rotateXMatrix = glm::rotate(identityMatrix, glm::radians(TRAIN_Z + 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			model = als * translateMatrix * rotateXMatrix * scaleMatrix;
			trainWheel.drawSphereWithTexture(lightingShaderWithTexture, model);
		}

	}


}
#pragma once
