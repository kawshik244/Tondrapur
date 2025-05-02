#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawCube.h"
#include<map>
#include "cube.h"
#include "curve.h"

void tree(unsigned int& cubeVAO,BezierCurve& treeCurve, BezierCurve& treeBaseCurve, Shader& lightingShader, Shader& lightingShaderWithTexture, map<string, Cube>& textures, glm::mat4 als) {

	glm::mat4 identityMatrix = glm::mat4(1.0f);
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, rotationMatrix, initModel, temp;

	translateMatrix = glm::translate(identityMatrix,glm::vec3(0.0f,1.0f,0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 3.0, 1.0));
	model = als * translateMatrix * scaleMatrix;
	treeCurve.drawBezierCurvewithTexture(lightingShaderWithTexture, model,glm::vec3(1.0,1.0,1.0));

	translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
	model = als * translateMatrix * scaleMatrix;
	treeBaseCurve.drawBezierCurvewithTexture(lightingShaderWithTexture, model, glm::vec3(1.0, 1.0, 1.0));

}
#pragma once
