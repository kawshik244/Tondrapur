//
//  pointLight.h
//  test
//
//  Created by Nazirul Hasan on 22/9/23.
//

#ifndef pointLight_h
#define pointLight_h
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <string>
using namespace std;

class PointLight {
public:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float k_c;
    float k_l;
    float k_q;
    int lightNumber;
    string pos, amb, diff, spec, s_k_c, s_k_l, s_k_q;


    PointLight(float posX, float posY, float posZ, float ambR, float ambG, float ambB, float diffR, float diffG, float diffB, float specR, float specG, float specB, float constant, float linear, float quadratic, int num) {

        position = glm::vec3(posX, posY, posZ);
        ambient = glm::vec3(ambR, ambG, ambB);
        diffuse = glm::vec3(diffR, diffG, diffB);
        specular = glm::vec3(specR, specG, specB);
        k_c = constant;
        k_l = linear;
        k_q = quadratic;
        lightNumber = num;
    }
    void setUpPointLight(Shader& lightingShader, int i)
    {
        lightingShader.use();

        string temp = to_string(i);

        pos = "pointLights[" + temp + "].position";
        amb = "pointLights[" + temp + "].ambient";
        diff = "pointLights[" + temp + "].diffuse";
        spec = "pointLights[" + temp + "].specular";
        s_k_c = "pointLights[" + temp + "].k_c";
        s_k_l = "pointLights[" + temp + "].k_l";
        s_k_q = "pointLights[" + temp + "].k_q";


        lightingShader.setVec3(pos, position);
        lightingShader.setVec3(amb, ambientOn * ambient);
        lightingShader.setVec3(diff, diffuseOn * diffuse);
        lightingShader.setVec3(spec, specularOn * specular);
        lightingShader.setFloat(s_k_c, k_c);
        lightingShader.setFloat(s_k_l, k_l);
        lightingShader.setFloat(s_k_q, k_q);

    }
    void turnOff()
    {
        ambientOn = 0.0;
        diffuseOn = 0.0;
        specularOn = 0.0;
    }
    void turnOn()
    {
        ambientOn = 1.0;
        diffuseOn = 1.0;
        specularOn = 1.0;
    }
    void turnAmbientOn()
    {
        ambientOn = 1.0;
    }
    void turnAmbientOff()
    {
        ambientOn = 0.0;
    }
    void turnDiffuseOn()
    {
        diffuseOn = 1.0;
    }
    void turnDiffuseOff()
    {
        diffuseOn = 0.0;
    }
    void turnSpecularOn()
    {
        specularOn = 1.0;
    }
    void turnSpecularOff()
    {
        specularOn = 0.0;
    }
private:
    float ambientOn = 1.0;
    float diffuseOn = 1.0;
    float specularOn = 1.0;
};

#endif /* pointLight_h */
