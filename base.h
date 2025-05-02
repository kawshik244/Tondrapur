#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawCube.h"
#include<map>
#include "tree.h"

void base(unsigned int& cubeVAO,BezierCurve& treeCurve, BezierCurve& treeBaseCurve, Shader& lightingShader,Shader& lightingShaderWithTexture,map<string,Cube>& textures, glm::mat4 als,float GATE_ANGLE) {

    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, rotationMatrix, initModel, temp;

    //global base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-25.0f, -0.15, -10.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50.0f, 0.1f, 35.0f));
    rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
    model = als * translateMatrix * scaleMatrix;
    textures["grass2"].drawCubeWithTexture(lightingShaderWithTexture, model);

    for (int i = 0; i < 20; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-6.0+(i*1.5), 0.1, -7.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 1.0f, 3.0f));
        model = als * translateMatrix * scaleMatrix;
        textures["flower"].drawCubeWithTexture(lightingShaderWithTexture, model);
    }

    //rock flower base
    for (int i = 0; i < 7; i++) {

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-25.0f, -0.1, -10.0 + (i * 5.0)));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.1f, 5.0f));
        rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
        model = als * translateMatrix * scaleMatrix;
        textures["rockFlower"].drawCubeWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-21.0f, -0.1, -10.0 + (i * 5.0)));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.1f, 5.0f));
        rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
        model = als * translateMatrix * scaleMatrix;
        textures["rockFlower"].drawCubeWithTexture(lightingShaderWithTexture, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-17.0f, -0.1, -10.0 + (i * 5.0)));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.1f, 5.0f));
        rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
        model = als * translateMatrix * scaleMatrix;
        textures["rockFlower"].drawCubeWithTexture(lightingShaderWithTexture, model);
    }


    //hills

    //for (int i = 0; i < 6; i++) {
    //    translateMatrix = glm::translate(identityMatrix, glm::vec3(-25.0+(i*9.0), -0.1, -9.5f));
    //    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.0f, 10.0f, 1.0f));
    //    rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
    //    model = als * translateMatrix * scaleMatrix;
    //    textures["hill1"].drawCubeWithTexture(lightingShaderWithTexture, model);
    //}

    //trees-beside railway tract

    for (int i = 0; i < 12; i++) {
        model = als * glm::translate(identityMatrix, glm::vec3(-12.0f, 0.0,-10.0+(i*3.0)));
        tree(cubeVAO, treeCurve, treeBaseCurve, lightingShader, lightingShaderWithTexture, textures, model);

       /* model = als * glm::translate(identityMatrix, glm::vec3(-15.0f, 0.0, -9.0 + (i * 3.0)));
        tree(cubeVAO, treeCurve, treeBaseCurve, lightingShader, lightingShaderWithTexture, textures, model);

        model = als * glm::translate(identityMatrix, glm::vec3(-18.0f, 0.0, -8.0 + (i * 2.8)));
        tree(cubeVAO, treeCurve, treeBaseCurve, lightingShader, lightingShaderWithTexture, textures, model);

        model = als * glm::translate(identityMatrix, glm::vec3(-20.0f, 0.0, -8.0 + (i * 3.0)));
        tree(cubeVAO, treeCurve, treeBaseCurve, lightingShader, lightingShaderWithTexture, textures, model);*/
    }


    for (int i = 0; i < 7; i++) {
        model = als * glm::translate(identityMatrix, glm::vec3(-6.0f, 0.0,  5.0+(i * 3.0)));
        tree(cubeVAO, treeCurve, treeBaseCurve, lightingShader, lightingShaderWithTexture, textures, model);
    }
   


    //park base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 0.0, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(20.0f, 0.1f, 12.0f));
    rotationMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;
    model = als * translateMatrix * scaleMatrix;
    textures["grass"].drawCubeWithTexture(lightingShaderWithTexture, model);





    //field
    translateMatrix = glm::translate(identityMatrix, glm::vec3(7.0f, 0.1, 12.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.0f, 0.05f, 12.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
    model = als * translateMatrix * scaleMatrix * rotateYMatrix;
    textures["field"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //bar 1-l
    translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0f, 0.1, 0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
    model = als * translateMatrix * scaleMatrix * rotateXMatrix;
    Cube().drawCube(lightingShader, model,1.0,1.0,1.0);


    //bar 1-r
    translateMatrix = glm::translate(identityMatrix, glm::vec3(11.87f, 0.1, 0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
    model = als * translateMatrix * scaleMatrix * rotateXMatrix;
    Cube().drawCube(lightingShader, model, 1.0, 1.0, 1.0);

    //bar 1-t
    translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0f, 1.0, 0.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.87f, 0.1f, 0.1f));
    model = als * translateMatrix * scaleMatrix * rotateXMatrix;
    Cube().drawCube(lightingShader, model, 1.0, 1.0, 1.0);


    //bar 2-l
    translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0f, 0.1, 11.6f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
    model = als * translateMatrix * scaleMatrix * rotateXMatrix;
    Cube().drawCube(lightingShader, model, 1.0, 1.0, 1.0);


    //bar 2-r
    translateMatrix = glm::translate(identityMatrix, glm::vec3(11.87f, 0.1, 11.6f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
    model = als * translateMatrix * scaleMatrix * rotateXMatrix;
    Cube().drawCube(lightingShader, model, 1.0, 1.0, 1.0);

    //bar 2-t
    translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0f, 1.0, 11.6f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.87f, 0.1f, 0.1f));
    model = als * translateMatrix * scaleMatrix * rotateXMatrix;
    Cube().drawCube(lightingShader, model, 1.0, 1.0, 1.0);



    //street-road-(beside field)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.8f, 0.1, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.05f, 12.0f));
    model = als * translateMatrix * scaleMatrix;
    textures["street"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //street-road (beside coffe shop)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 0.1, 3.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(11.0f, 0.05f, 1.0f));
    model = als * translateMatrix * scaleMatrix;
    textures["street"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //field-left-boundary-1 (beside field)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.8f, 0.1, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.25f, 5.0f));
    model = als * translateMatrix * scaleMatrix;
    textures["leaf"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //field-left-boundary-2 (beside field)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.8f, 0.1, 7.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.25f, 5.0f));
    model = als * translateMatrix * scaleMatrix;
    textures["leaf"].drawCubeWithTexture(lightingShaderWithTexture, model);




    //front -grass-boundary-1 (beside cafe)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.9f, 0.0, 3.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.4f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    textures["leaf"].drawCubeWithTexture(lightingShaderWithTexture, model);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.9f, 0.0, 4.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.4f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    textures["leaf"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //front -grass-boundary-2 (beside cafe)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2f, 0.0, 3.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5f, 0.4f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    textures["leaf"].drawCubeWithTexture(lightingShaderWithTexture, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(1.2f, 0.0, 4.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5f, 0.4f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    textures["leaf"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //front -grass-boundary-2 ( beside flyer)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.7f, 0.0, 0.1f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.4f, 3.8f));
    model = als * translateMatrix * scaleMatrix;
    textures["leaf"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //front -grass-boundary-2 ( beside flyer)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.7f, 0.0, 4.8f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.4f, 3.8f));
    model = als * translateMatrix * scaleMatrix;
    textures["leaf"].drawCubeWithTexture(lightingShaderWithTexture, model);


   /* drawCube(cubeVAO, lightingShader, model, 0.23, 0.3, 0.22);*/

    //left barrier
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 0.0, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 3.8f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.31, 0.29, 0.27);
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //left barrier
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 0.0, 4.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 7.0f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.31, 0.29, 0.27);
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //right barrier
    translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0f, 0.0, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 12.0f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.31, 0.29, 0.27);
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //back barrier
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 0.0, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(20.0f, 0.5f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.31, 0.29, 0.27);
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //frontbarrier-left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 0.0, 11.9f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.8f, 0.5f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.31, 0.29, 0.27);
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //frontbarrier-right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(6.8f, 0.0, 11.95f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.2f, 0.5f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    //drawCube(cubeVAO, lightingShader, model, 0.31, 0.29, 0.27);
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //borders-l
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 0.0, 12.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 4.0f));
    model = als * translateMatrix * scaleMatrix;
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //borders-r
    translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0f, 0.0, 12.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.5f, 4.0f));
    model = als * translateMatrix * scaleMatrix;
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //borders-f-l
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-5.0f, 0.0, 16.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.0f, 0.5f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //borders-f-r
    translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0f, 0.0, 16.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.0f, 0.5f, 0.1f));
    model = als * translateMatrix * scaleMatrix;
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //gate-PILLER-l
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0, 15.7f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 3.0f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);


    //gate-PILLER-t
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 3.0, 15.7f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5f, 0.5f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //gate-PILLER-r
    translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0f, 0.0, 15.7f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 3.0f, 0.5f));
    model = als * translateMatrix * scaleMatrix;
    textures["brick"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //GATE-l
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0, 15.78f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 2.5f, 0.2f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(GATE_ANGLE), glm::vec3(0.0, 1.0, 0.0));
    model = als * translateMatrix * rotateXMatrix * scaleMatrix;
    textures["gate"].drawCubeWithTexture(lightingShaderWithTexture, model);

    //GATE-R
    translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.0, 15.5f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 2.5f, 0.2f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(180.0f - GATE_ANGLE), glm::vec3(0.0, 1.0, 0.0));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(8.0f, 0.0, 16.0f));
    model = als * translateMatrix * rotateXMatrix * scaleMatrix;
    textures["gate"].drawCubeWithTexture(lightingShaderWithTexture, model);

    for (int i = 0; i < 3; i++) {
        model = als * glm::translate(identityMatrix, glm::vec3(-4.0f+(i*3.0), 0.0, 14.0f));
        tree(cubeVAO, treeCurve, treeBaseCurve, lightingShader, lightingShaderWithTexture, textures, model);
    }

    for (int i = 0; i < 2; i++) {
        model = als * glm::translate(identityMatrix, glm::vec3(9.5f + (i * 3.0), 0.0, 14.0f));
        tree(cubeVAO, treeCurve, treeBaseCurve, lightingShader, lightingShaderWithTexture, textures, model);
    }



}
#pragma once
