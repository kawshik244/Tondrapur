#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"
#include "components.h"
#include <map>


void drawTableChairPair(unsigned int& cubeVAO, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::vec3 translateVec,map<string,Cube>& textures, glm::mat4 als) {
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    drawRoundTable(cubeVAO, lightingShader, lightingShaderWithTexture, translateVec,textures, als);
    translateVec[0] -= 0.2;
    translateVec[2] -= 0.5f;
    drawChair(cubeVAO, lightingShader,lightingShaderWithTexture, translateVec, identityMatrix, textures, als);

    translateVec[0] += 0.3f;
    translateVec[2] += 1.0f;

    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0));
    drawChair(cubeVAO, lightingShader,lightingShaderWithTexture, translateVec,  rotateYMatrix, textures, als);

}
#pragma once


void cafe(unsigned int& cubeVAO, Shader& lightingShader,Shader& lightingShaderWithTexture,map<string,Cube>& textures, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.95f, 0.0, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.3f, 0.15f, 3.5f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.53, 0.29, 0.22);
    textures["floor"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //back wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.8f, 0.0, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 1.0f, 0.08f));

    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.53, 0.29, 0.22);
    textures["wood"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //left wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.8f, 0.0, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.08f, 1.0f, 0.7f));

    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.53, 0.29, 0.22);
    textures["wood3"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //right wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.8f, 0.0, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.08f, 1.0f, 0.7f));

    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.53, 0.29, 0.22);
    textures["wood3"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //front wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.4f, 0.0, 0.7f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.6f, 0.5f, 0.08f));

    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.73, 0.44, 0.31);
    textures["wood3"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //Top wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.9f, 1.0, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.3f, 0.05f, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.73, 0.44, 0.31);
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //lower fridge
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.0, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.18f, 0.3f, 0.4f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.21, 0.18, 0.27);

    //upper frige
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-3.0f, 0.3, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.18f, 0.3f, 0.4f));
    model = als * translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.24, 0.19, 0.30);



    //cafe table and chairs
    drawTableChairPair(cubeVAO, lightingShader,lightingShaderWithTexture, glm::vec3(-4.3f, 0.0, 2.5f), textures, als);

    drawTableChairPair(cubeVAO, lightingShader, lightingShaderWithTexture, glm::vec3(-3.5f, 0.0, 2.5f), textures, als);

    drawTableChairPair(cubeVAO, lightingShader, lightingShaderWithTexture, glm::vec3(-2.8f, 0.0, 2.5f), textures, als);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 1.0, 0.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 1.5f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.53, 0.29, 0.22);
    textures["movie"].drawCubeWithTexture(lightingShaderWithTexture, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 0.0, 0.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 1.0f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.53, 0.29, 0.22);
    textures["floor"].drawCubeWithTexture(lightingShaderWithTexture, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.85f, 0.0, 0.3f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 1.0f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.53, 0.29, 0.22);
    textures["floor"].drawCubeWithTexture(lightingShaderWithTexture, model);

}
#pragma once
