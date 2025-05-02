#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"
#include "utility.h"
#include <map>



void drawChair(unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::vec3 translateVec, glm::mat4 rotateMatrix,map<string,Cube>& textures, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //Sofa Seat
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.05, 0.3, -0.9));
    translateVec[1] = translateVec[1] + 0.3;
    translateMatrix = glm::translate(identityMatrix, translateVec);
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, .03f, 0.3f));
    model = als * translateMatrix * rotateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.51, 0.36, 0.36);
    textures["wood2"].drawCubeWithTexture( lightingShaderWithTexture, model);

    //Sofa Head
    translateMatrix = glm::translate(identityMatrix, translateVec);
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, .28f, 0.01f));
    model = als * translateMatrix * rotateMatrix * scaleMatrix;
    textures["wood2"].drawCubeWithTexture(lightingShaderWithTexture, model);


    translateVec[1] = 0.09;

    //Sofa leg1
    translateMatrix = glm::translate(identityMatrix, translateVec);
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, .24f, 0.03f));
    model = als * translateMatrix * rotateMatrix * scaleMatrix;
    textures["wood2"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //Sofa leg2
    translateMatrix = glm::translate(identityMatrix, translateVec);
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, .02f, 0.3f));
    model = als * translateMatrix * rotateMatrix * scaleMatrix;
    textures["wood2"].drawCubeWithTexture(lightingShaderWithTexture, model);

}
#pragma once

void drawRoundTable(unsigned int& cubeVAO, Shader& lightingShader,Shader& lightingShaderWithTexture, glm::vec3 translateVec,map<string,Cube>& textures, glm::mat4 als)
{

    //drawCircle(cubeVAO, lightingShader, translateVec, glm::vec3(0.02f, 0.4f, 0.02f),
    //    glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.31, 0.29, 0.27), als);
    //translateVec[1] += 0.4;
    //drawCircle(cubeVAO, lightingShader, translateVec, glm::vec3(0.2f, 0.05f, 0.2f),
    //    glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.31, 0.29, 0.27), als);

    drawCircleWithTexture(cubeVAO, lightingShaderWithTexture, translateVec, glm::vec3(0.02f, 0.4f, 0.02f),
        glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.31, 0.29, 0.27),textures, als);
    translateVec[1] += 0.4;
    drawCircleWithTexture(cubeVAO, lightingShaderWithTexture, translateVec, glm::vec3(0.2f, 0.05f, 0.2f),
        glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.31, 0.29, 0.27),textures, als);
}
#pragma once


void object(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    model = identityMatrix;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15, 0.375, 0.235));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.15f, 0.05f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.75, 0.51, 0.38);
}
#pragma once

