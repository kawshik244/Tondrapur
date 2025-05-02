#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionLight.h"
#include "sphere.h"
#include "spotLight.h"
#include "cube.h"
#include "stb_image.h"
#include <iostream>
#include "base.h"
#include "cafe.h"
#include "flyer.h"
#include "maryGoRound.h"
#include <map>
#include <vector>
#include <string>
#include "circularRide.h"
#include "sphereWithTexture.h"
#include "curve.h"
#include "ferrisWheel.h"
#include "train.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void SkyDrop(Shader ourShader, glm::mat4 moveMatrix);



unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);


// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(6.0f, 2.0f, 20.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 33.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);
SpotLight spotlight(
    0.0f,1.0f,0.0f,
    .2f, .2f, .2f,
    .8f, .8f, .8f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    45.0f,
    0.03f,   //k_c
    0.09f,  //k_l
    0.032f //k_q
);

DirectionLight directlight(
    0.0f, 1.0f, 0.0f,
    .2f, .2f, .2f,
    .8f, .8f, .8f,
    1.0f, 1.0f, 1.0f,
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f //k_q
);
// positions of the point lights
glm::vec3 pointLightPositions[] = {
    //back lights-mid

       glm::vec3(-10.0f,  23.0f,  -4.0f),
       glm::vec3(-4.0f,  24.0f,  -6.0f),
       glm::vec3(2.0f,  28.0f,  -8.0f),
       glm::vec3(6.0f,  30.0f,  -10.0f),
       glm::vec3(10.0f,  28.0f,  -8.0f),
       glm::vec3(14.0f,  24.0f,  -6.0f),
       glm::vec3(18.0f,  23.0f,  -4.0f),


       //back lights
        glm::vec3(-25.0f,  18.0f,  -19.0f),
       glm::vec3(-15.0f,  15.0f,  -22.0f),
       glm::vec3(-5.0f,  15.0f,  -26.0f),
       glm::vec3(5.0f,  13.0f,  -29.0f),
       glm::vec3(15.0f,  13.0f,  -22.0f),
       glm::vec3(20.0f,  13.0f,  -20.0f),
       glm::vec3(25.0f,  13.0f,  -19.0f),

       glm::vec3(-25.0f,  7.0f,  -14.0f),
       glm::vec3(-15.0f,  7.0f,  -20.0f),
       glm::vec3(-5.0f,  7.0f,  -24.0f),
       glm::vec3(5.0f,  7.0f,  -27.0f),
       glm::vec3(15.0f,  7.0f,  -20.0f),
       glm::vec3(20.0f,  7.0f,  -18.0f),
       glm::vec3(25.0f,  7.0f,  -17.0f),

       //front lights
       glm::vec3(-25.0f,  16.0f,  10.0f),
       glm::vec3(-15.0f,  19.0f,  10.0f),
       glm::vec3(-5.0f,  22.0f,   10.0f),
       glm::vec3(5.0f,  25.0f,  10.0f),
       glm::vec3(15.0f,  23.0f,  10.0f),
       glm::vec3(20.0f,  21.0f,  10.0f),
       glm::vec3(25.0f,  19.0f,  10.0f),

       glm::vec3(-25.0f,  10.0f,  24.0f),
       glm::vec3(-15.0f,  10.0f,  30.0f),
       glm::vec3(-5.0f,  10.0f,   34.0f),
       glm::vec3(5.0f,  10.0f,  37.0f),
       glm::vec3(15.0f,  10.0f,  34.0f),
       glm::vec3(20.0f,  10.0f,  30.0f),
       glm::vec3(25.0f,  10.0f,  24.0f),

       // left lights
       glm::vec3(-25.0f,  16.0f,  -12.0f),
       glm::vec3(-28.0f,  19.0f,  -8.0f),
       glm::vec3(-35.0f,  22.0f,   -3.0f),
       glm::vec3(-28.0f,  25.0f,  5.0f),
       glm::vec3(-25.0f,  23.0f,  13.0f),
       glm::vec3(-23.0f,  21.0f,  18.0f),
       glm::vec3(-20.0f,  19.0f,  20.0f),

       glm::vec3(-25.0f,  10.0f,  -19.0f),
       glm::vec3(-15.0f,  10.0f,  -22.0f),
       glm::vec3(20.0f,  10.0f,  -20.0f),


};

vector<PointLight> pointLights = {};

// light settings
bool pointLightOn = true;
bool directionLighton = true;
bool spotlighton = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;

float FLYER_Y = 0;
bool  FLYER_Y_INCREASE = true;
float CIRCULAR_RIDE_ANGLE = 0.0f;
float ROTATE_ANGLE_SKY = 0.0f;
float TRAIN_Z = 0.0f;

float angle_t = 0.0f;
float t = 0.0f;
float r = 0.0;
float speed = 0.5f;
float GATE_OPEN_ANGLE = 0.0f;

bool IS_CIRCULAR_RIDE_ON = false;
bool IS_FERRIS_WHEEL_ON = false;
bool IS_FLYER_ON = false;
float CIRCULAR_RIDE_SPEED = 0.5f;
float FERRIS_WHEEL_ANGLE = 0.0f;
float FERRIS_WHEEL_SPEED = 2.0f;
float TRAIN_SPEED = 0.2f;
bool GATE_OPEN = false;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

float lastTime = 0.0f, lastTimeSky = 0.0f;


bool dark = false;
bool isSkyDropOn = true;
float skyDropMax = 8.03f;
float skyDropMin = 0.0f;
float skyDropUpSpeed = 0.04f;
float skyDropDownSpeed = 0.09f;
float skyDropY = 0.0f;
float skyDropCurrent = 1.0f;
// Skybox

float skyboxVertices[] =
{
    -1.0f, -1.0f, 1.0f,
     1.0f, -1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f
};

unsigned int skyboxIndices[] =
{
    // Right
    1, 2, 6,
    6, 5, 1,
    //Left
    0, 4, 7,
    7, 3, 0,
    //Top
    4, 5, 6,
    6, 7, 4,
    //Bottom
    0, 3, 2,
    2, 1, 0,
    //Back
    0, 1, 5,
    5, 4, 0,
    //Front
    3, 7, 6,
    6, 2, 3
};




int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    Shader skyboxShader("skybox.vert", "skybox.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };





    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //For Skybox
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Day
    string facesCubemapDay[6] = {
        "right.png",
        "left.png",
        "top.png",
        "bottom.png",
        "front.png",
        "back.png"
    };

    unsigned int cubemapTextureDay;
    glGenTextures(1, &cubemapTextureDay);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureDay);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemapDay[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
        }
        else
            cout << "Failed to load texture: " << facesCubemapDay[i] << endl;
        stbi_image_free(data);
    }


    //Night
    string facesCubemapNight[6] = {
        "right1.jpg",
        "left1.jpg",
        "top1.jpg",
        "bottom1.jpg",
        "front1.jpg",
        "back1.jpg"
    };

    unsigned int cubemapTextureNight;
    glGenTextures(1, &cubemapTextureNight);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureNight);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++)
    {
        int width, height, nrChannels;
        unsigned char* data = stbi_load(facesCubemapNight[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            stbi_set_flip_vertically_on_load(false);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
        }
        else
            cout << "Failed to load texture: " << facesCubemapNight[i] << endl;
        stbi_image_free(data);
    }

    Sphere sphere = Sphere();
   

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    //Shader ourShader("vertexShader.vs", "fragmentShader.fs");

    string diffuseMapPath = "container2.png";
    string specularMapPath = "container2_specular.png";
    string grassPath = "grass.jpg";
    string grass2Path = "grass2.jpg";
    string brickPath = "brick.jpg";
    string woodPath = "wood.jpg";
    string floorPath = "floor.jpg";
    string wood2Path = "wood2.jpg";
    string mosaic1Path = "mosaic1.jpg";
    string wood3Path = "wood3.jpg";
    string mosaic2Path = "mosaic2.jpg";
    string moviePath = "movie.jpeg";
    string fieldPath = "field.png";
    string leafPath = "leaf.png";
    string leaf2Path = "leaf2.png";
    string streetPath = "street.png";
    string skyPath = "sky.jpeg";
    string steelPath = "steel.jpeg";
    string glassPath = "glass.jpeg";
    string abstract1Path = "abstract1.jpeg";
    string soil1Path = "soil1.jpg";
    string stonePath = "stone.jpg";
    string hill1Path = "hill1.jpg";
    string treePath = "tree.jpg";
    string rockFlowerPath = "rockFlower.jpg";
    string flowerPath = "flower.png";
    string gatePath = "gate.png";
    string footballPath = "football.jpg";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int grass2Map = loadTexture(grass2Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int grassMap = loadTexture(grassPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int brickMap = loadTexture(brickPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int woodMap = loadTexture(woodPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int floorMap = loadTexture(floorPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wood2Map = loadTexture(wood2Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int mosaic1Map = loadTexture(mosaic1Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wood3Map = loadTexture(wood3Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int mosaic2Map = loadTexture(mosaic2Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int movieMap = loadTexture(moviePath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int fieldMap = loadTexture(fieldPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int leafMap = loadTexture(leafPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int leaf2Map = loadTexture(leaf2Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int streetMap = loadTexture(streetPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int skyMap = loadTexture(skyPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int steelMap = loadTexture(steelPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int glassMap = loadTexture(glassPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int abstract1Map = loadTexture(abstract1Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int soil1Map = loadTexture(soil1Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int stoneMap = loadTexture(stonePath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int hill1Map = loadTexture(hill1Path.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int treeMap = loadTexture(treePath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int rockFlowerMap = loadTexture(rockFlowerPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int flowerMap = loadTexture(flowerPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int gateMap = loadTexture(gatePath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int footballMap = loadTexture(footballPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    


    Cube grass = Cube(grassMap, grassMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube grass2 = Cube(grass2Map, grass2Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube brick = Cube(brickMap, brickMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wood = Cube(woodMap, woodMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube floor = Cube(floorMap, floorMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wood2 = Cube(wood2Map, wood2Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube mosaic1 = Cube(mosaic1Map, mosaic1Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wood3 = Cube(wood3Map, wood3Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube mosaic2 = Cube(mosaic2Map, mosaic2Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube movie = Cube(movieMap, movieMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube field = Cube(fieldMap, fieldMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube leaf = Cube(leafMap, leafMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube leaf2 = Cube(leaf2Map, leaf2Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube street = Cube(streetMap, streetMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube steel = Cube(steelMap, steelMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube glass = Cube(glassMap, glassMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube abstract1 = Cube(abstract1Map, abstract1Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube stone = Cube(stoneMap, stoneMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube soil1 = Cube(soil1Map, soil1Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube hill1 = Cube(hill1Map, hill1Map, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube tree = Cube(treeMap, treeMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube rockFlower = Cube(rockFlowerMap, rockFlowerMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube flower = Cube(flowerMap, flowerMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube gate = Cube(gateMap, gateMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube football = Cube(footballMap, footballMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

     map<string, Cube> textures;
     textures["grass"] = grass;
     textures["grass2"] = grass2;
     textures["cube"] = cube;
     textures["brick"] = brick;
     textures["wood"] = wood;
     textures["floor"] = floor;
     textures["wood2"] = wood2;
     textures["mosaic1"] = mosaic1;
     textures["wood3"] = wood3;
     textures["mosaic2"] = mosaic2;
     textures["movie"] = movie;
     textures["field"] = field;
     textures["leaf"] = leaf;
     textures["leaf2"] = leaf2;
     textures["street"] = street;
     textures["steel"] = steel;
     textures["glass"] = glass;
     textures["abstract1"] = abstract1;
     textures["stone"] = stone;
     textures["soil1"] = soil1;
     textures["hill1"] = hill1;
     textures["tree"] = tree;
     textures["rockFlower"] = rockFlower;
     textures["flower"] = flower;
     textures["gate"] = gate;
     textures["football"] = football;

     SphereWithTexture sphereWithTexture = SphereWithTexture(0.25f, 144, 44, glm::vec3(0.898f, 0.459f, 0.125f), glm::vec3(0.898f, 0.459f, 0.125f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, footballMap, footballMap, 0.0f, 0.0f, 1.0f, 1.0f);
     SphereWithTexture trainWheelSphere = SphereWithTexture(0.3f, 144, 50, glm::vec3(0.898f, 0.459f, 0.125f), glm::vec3(0.898f, 0.459f, 0.125f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, wood2Map, wood2Map, 0.0f, 0.0f, 1.0f, 1.0f);
     float ferrisPoints[] = {
        -1.6250, -0.0900, 5.1000,
       -1.4450, -0.0750, 5.1000,

     };

     float hollowCirclePoints[] = {
        -1.6250, -0.0900, 5.1000,
       -1.4450, -0.0750, 5.1000,
     };

     float tentTopPoints[] = {
        0.0300, 0.9850, 5.1000,
        -0.1050, 0.9350, 5.1000,
        -0.1750, 0.8750, 5.1000,
        -0.3050, 0.7750, 5.1000,
        -0.3950, 0.7100, 5.1000,
        -0.5000, 0.6250, 5.1000,
        -0.6100, 0.5450, 5.1000,
        -0.7750, 0.4100, 5.1000,
        -0.8900, 0.3550, 5.1000,
        -0.9950, 0.2800, 5.1000,
        -1.1050, 0.2000, 5.1000,
        -1.2100, 0.1500, 5.1000,
        -1.3250, 0.0650, 5.1000,
        -1.4400, 0.0150, 5.1000,
     };

     float ballonPoints[] = {
         0.0000, 2.3600, 5.1000,
        -0.1700, 2.3400, 5.1000,
        -0.3100, 2.3150, 5.1000,
        -0.5000, 2.2500, 5.1000,
        -0.6550, 2.1700, 5.1000,
        -0.8000, 2.0650, 5.1000,
        -0.9250, 1.9350, 5.1000,
        -1.0100, 1.8050, 5.1000,
        -1.0750, 1.6200, 5.1000,
        -1.1100, 1.4400, 5.1000,
        -1.1150, 1.2700, 5.1000,
        -1.0200, 1.0950, 5.1000,
        -0.8650, 0.9150, 5.1000,
        -0.6900, 0.6900, 5.1000,
        -0.5150, 0.4950, 5.1000,
        -0.3400, 0.2900, 5.1000,
        -0.1700, 0.1000, 5.1000,
        0.0000, -0.0100, 5.1000,
        2.7214, 2.1512, 6.6502,
     };

     float treePoints[] = {
        -0.0800, -0.0300, 5.1000,
        -0.1700, -0.0300, 5.1000,
        -0.2150, -0.0300, 5.1000,
        -0.3350, -0.0250, 5.1000,
        -0.3900, 0.0300, 5.1000,
        -0.4500, 0.0300, 5.1000,
        -0.4950, 0.0350, 5.1000,
        -0.5500, 0.0350, 5.1000,
        -0.6550, 0.0400, 5.1000,
        -0.7100, 0.0400, 5.1000,
        -0.7700, 0.0800, 5.1000,
        -0.7900, 0.1150, 5.1000,
        -0.8350, 0.1450, 5.1000,
        -0.8750, 0.1650, 5.1000,
        -0.8600, 0.2450, 5.1000,
        -0.8450, 0.2950, 5.1000,
        -0.8450, 0.3300, 5.1000,
        -0.8950, 0.3900, 5.1000,
        -0.9000, 0.4700, 5.1000,
        -0.9000, 0.5050, 5.1000,
        -0.8550, 0.5700, 5.1000,
        -0.8150, 0.5850, 5.1000,
        -0.7400, 0.5800, 5.1000,
        -0.6950, 0.5600, 5.1000,
        -0.6450, 0.5600, 5.1000,
        -0.6000, 0.5700, 5.1000,
        -0.5350, 0.6200, 5.1000,
        -0.5350, 0.6450, 5.1000,
        -0.5700, 0.7350, 5.1000,
        -0.6200, 0.7650, 5.1000,
        -0.6200, 0.7650, 5.1000,
        -0.6350, 0.8100, 5.1000,
        -0.6550, 0.8500, 5.1000,
        -0.6450, 0.9100, 5.1000,
        -0.6250, 0.9450, 5.1000,
        -0.5850, 0.9600, 5.1000,
        -0.5400, 0.9700, 5.1000,
        -0.4750, 1.0500, 5.1000,
        -0.4200, 1.0400, 5.1000,
        -0.3700, 1.0100, 5.1000,
        -0.3300, 1.0600, 5.1000,
        -0.3200, 1.1400, 5.1000,
        -0.3500, 1.1750, 5.1000,
        -0.3200, 1.2500, 5.1000,
        -0.2600, 1.2900, 5.1000,
        -0.2050, 1.3400, 5.1000,
        -0.1450, 1.3800, 5.1000,
        -0.0850, 1.4000, 5.1000,
        -0.0500, 1.4000, 5.1000,
        0.0000, 1.4150, 5.1000,
     };

     float treeBasePoints[] = {
        -0.0850, 1.6900, 5.1000,
        -0.1100, 1.5650, 5.1000,
        -0.1400, 1.5200, 5.1000,
        -0.1450, 1.4650, 5.1000,
        -0.1450, 1.4050, 5.1000,
        -0.1450, 1.3250, 5.1000,
        -0.1500, 1.2700, 5.1000,
        -0.1850, 1.2300, 5.1000,
        -0.2050, 1.2100, 5.1000,
        -0.1900, 1.1350, 5.1000,
        -0.1700, 1.0850, 5.1000,
        -0.1650, 1.0050, 5.1000,
        -0.1650, 0.9400, 5.1000,
        -0.2000, 0.8750, 5.1000,
        -0.2150, 0.8400, 5.1000,
        -0.2150, 0.7700, 5.1000,
        -0.2100, 0.7150, 5.1000,
        -0.1950, 0.6600, 5.1000,
        -0.2000, 0.6000, 5.1000,
        -0.2400, 0.5650, 5.1000,
        -0.2400, 0.5150, 5.1000,
        -0.2050, 0.4650, 5.1000,
        -0.1900, 0.3800, 5.1000,
        -0.2400, 0.2850, 5.1000,
        -0.2750, 0.2200, 5.1000,
        -0.2850, 0.1600, 5.1000,
        -0.3400, 0.0850, 5.1000,
        -0.3400, 0.0500, 5.1000,
        -0.3100, -0.0150, 5.1000,
     };

     BezierCurve ferrisWheelCurve = BezierCurve(ferrisPoints, sizeof(ferrisPoints)/sizeof(ferrisPoints[0])); 
     BezierCurve tentTopCurve = BezierCurve(tentTopPoints, sizeof(tentTopPoints)/sizeof(tentTopPoints[0]));
     BezierCurve ballonCurve = BezierCurve(ballonPoints, sizeof(ballonPoints)/sizeof(ballonPoints[0]));
     BezierCurve hollowCircleCurve = BezierCurve(hollowCirclePoints, sizeof(hollowCirclePoints)/sizeof(hollowCirclePoints[0]));
     BezierCurve treeCurve = BezierCurve(treePoints, sizeof(treePoints)/sizeof(treePoints[0]));
     BezierCurve treeBaseCurve = BezierCurve(treeBasePoints, sizeof(treeBasePoints)/sizeof(treeBasePoints[0]));

     hollowCircleCurve.setTextureProperty(wood2Map, wood2Map, 32.0);
     treeCurve.setTextureProperty(leaf2Map, leaf2Map, 32.0);
     treeBaseCurve.setTextureProperty(treeMap, treeMap, 32.0);
     ferrisWheelCurve.setTextureProperty(wood2Map, wood2Map, 32.0);


     //point light initialization
     for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++) {
         //cout << "Point light created" << endl;
         pointLights.push_back(
             PointLight(
                 pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z,  // position
                 0.05f, 0.05f, 0.05f,     // ambient
                 0.8f, 0.8f, 0.8f,     // diffuse
                 1.0f, 1.0f, 1.0f,        // specular
                 0.0005f,   //k_c
                 0.0005f,  //k_l
                 0.032f, //k_q
                 i + 1      // light number
             )
         );
     }

    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);


        for (int i = 0; i < pointLights.size(); i++)
        {
            pointLights[i].setUpPointLight(lightingShader, i);
            //cout << "point light set up with lighting shader"<<endl;
        }

        directlight.setUpDirectionLight(lightingShader);

        spotlight.setUpSpotLight(lightingShader);

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);
       // board(cubeVAO, lightingShader, model);



            


        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);


        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        //glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);

        lightingShaderWithTexture.use();

        for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
        {
            pointLights[i].setUpPointLight(lightingShaderWithTexture, i);
        }

        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        modelMatrixForContainer = glm::translate(identityMatrix, glm::vec3(-0.45f, -0.4f, -2.8f));
        //cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);


        base(cubeVAO,treeCurve,treeBaseCurve,lightingShader, lightingShaderWithTexture, textures, model,GATE_OPEN_ANGLE);

        if (GATE_OPEN) {
            if (GATE_OPEN_ANGLE < 90.0) {
                GATE_OPEN_ANGLE += 2.0;
            }
        }
        else
        {
            if (GATE_OPEN_ANGLE > 0.0) {
                GATE_OPEN_ANGLE -= 2.0;
            }
        }


        cafe(cubeVAO, lightingShader, lightingShaderWithTexture,textures, model);


        model = glm::translate(model, glm::vec3(22.5f, 0.0f, 0.0f))*glm::scale(identityMatrix, glm::vec3(1.4f, 1.4, 1.4));
       // model = glm::translate(model, glm::vec3(23.0f, 0.0f, 0.0f));
        
        cafe(cubeVAO, lightingShader, lightingShaderWithTexture, textures, model);

       // model = glm::rotate(identityMatrix, glm::radians(ROTATE_ANGLE_SKY), glm::vec3(0.0f, 0.0f, 1.0f))
        
        model = glm::translate(model, glm::vec3(1.2f, 0.0f, 14.0f)) * glm::rotate(identityMatrix, glm::radians(-90.f), glm::vec3(0.0f, 1.0f, 0.0f))* glm::scale(identityMatrix, glm::vec3(1.4f, 1.4, 1.4));
        //model = glm::rotate(identityMatrix, glm::radians(-90.f), glm::vec3(0.0f, 1.0f, 0.0f));

        cafe(cubeVAO, lightingShader, lightingShaderWithTexture, textures, model);









        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;

        

        train(cubeVAO, hollowCircleCurve, lightingShader, lightingShaderWithTexture, textures,trainWheelSphere, model,TRAIN_Z);


        flyer(cubeVAO, lightingShader, lightingShaderWithTexture, textures, model, FLYER_Y);
       
        if (IS_FLYER_ON) {
            if (FLYER_Y_INCREASE) FLYER_Y += 0.05;
            else FLYER_Y -= 0.2;
            if (FLYER_Y > 4.8) {
                FLYER_Y = 4.8;
                FLYER_Y_INCREASE = false;
            }
            else if (FLYER_Y < 0.0) {
                FLYER_Y = 0;
                FLYER_Y_INCREASE = true;
            }
        }

        ferrisWheel(cubeVAO,ferrisWheelCurve, lightingShader, lightingShaderWithTexture, textures, model, FERRIS_WHEEL_ANGLE);

       
        if (IS_FERRIS_WHEEL_ON){

            FERRIS_WHEEL_ANGLE += FERRIS_WHEEL_SPEED;
            if (FERRIS_WHEEL_ANGLE > 360) FERRIS_WHEEL_ANGLE = 0.0f;
        }

        if (TRAIN_Z < 20.0) {
            TRAIN_Z += TRAIN_SPEED;
        }
        else {
            TRAIN_Z = 0.0;
        }




        model = identityMatrix;
        circularRide(cubeVAO, lightingShader, lightingShaderWithTexture, textures, model, CIRCULAR_RIDE_ANGLE) ;
        if (IS_CIRCULAR_RIDE_ON) {
            CIRCULAR_RIDE_ANGLE += CIRCULAR_RIDE_SPEED;
        }


        model =  glm::rotate(identityMatrix, glm::radians(ROTATE_ANGLE_SKY), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(identityMatrix, glm::vec3(1.0f,1.0,1.0));
        model = glm::translate(model, glm::vec3(11.0f, 0.35f, 6.0f));
        sphereWithTexture.drawSphereWithTexture(lightingShaderWithTexture, model);
        //ROTATE_ANGLE_SKY += 0.3;

        //if (ROTATE_ANGLE_SKY >= 360) ROTATE_ANGLE_SKY = 0.0F;


       




        // we now draw as many light bulbs as we have point lights.
        //glBindVertexArray(lightCubeVAO);
        //for (unsigned int i = 0; i < sizeof(pointLightPositions)/sizeof(pointLightPositions[0]); i++)
        //{
        //    model = glm::mat4(1.0f);
        //    model = glm::translate(model, pointLightPositions[i]);
        //    model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
        //    ourShader.setMat4("model", model);
        //    ourShader.setVec3("color", glm::vec3(0.8f, 0.8f, 0.8f));
        //    cube.drawCube(lightingShader, model,1.0,1.0,1.0);
        //    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //}

        //skyboxShader
        for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
        {
            pointLights[i].setUpPointLight(skyboxShader, i);
        }
       
        //Texture drawing
        glDepthFunc(GL_LEQUAL);

        skyboxShader.use();
        glm::mat4 view1 = glm::mat4(1.0f);
        glm::mat4 projection1 = glm::mat4(1.0f);
        view1 = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up)));
        projection1 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        skyboxShader.setMat4("view", view1);
        skyboxShader.setMat4("projection", projection1);

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        if (dark)
        {
            
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureNight);
        }
        else
        {
            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureDay);
        }
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glDepthFunc(GL_LESS);
      
     

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

//void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
//{
//    lightingShader.use();
//
//    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
//    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
//    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
//    lightingShader.setFloat("material.shininess", 22.0f);
//
//    lightingShader.setMat4("model", model);
//
//    glBindVertexArray(cubeVAO);
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(YAW_L, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        camera.ProcessKeyboard(YAW_R, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(PITCH_U, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(PITCH_D, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(ROLL_R, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(ROLL_L, deltaTime);
    }
    
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UP, -deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        IS_CIRCULAR_RIDE_ON = true;
         CIRCULAR_RIDE_SPEED = 1.0F;
        
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        IS_CIRCULAR_RIDE_ON = false;
        CIRCULAR_RIDE_SPEED = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        if (IS_CIRCULAR_RIDE_ON) CIRCULAR_RIDE_SPEED += 0.5f;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        //GATE OPEN
        GATE_OPEN = true;
        //GATE_OPEN_ANGLE = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        //GATE CLOSE
        GATE_OPEN = false;
        //GATE_OPEN_ANGLE = 90.0;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        
        if (IS_CIRCULAR_RIDE_ON) CIRCULAR_RIDE_SPEED -= 0.5f;
        if(CIRCULAR_RIDE_SPEED < 0.0f) CIRCULAR_RIDE_SPEED = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)                   //SkyDrop On/Off
    {
        dark = true;
    }


    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)                   //SkyDrop On/Off
    {
        dark = false;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)                   //SkyDrop On/Off
    {
         IS_FERRIS_WHEEL_ON = true;

    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)                   //SkyDrop On/Off
    {

        IS_FERRIS_WHEEL_ON = false;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)                   //SkyDrop On/Off
    {
        IS_FLYER_ON = true;

    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)                   //SkyDrop On/Off
    {

        IS_FLYER_ON  = false;
    }

    

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{   
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (directionLighton)
        {
            directlight.turnOff();
            directionLighton = !directionLighton;
        }
        else
        {
            directlight.turnOn();
            directionLighton = !directionLighton;
        }
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            for (int i = 0; i < (sizeof(pointLightPositions) / sizeof(pointLightPositions[0]))-20; i++)
            {
                pointLights[i].turnOff();
            }
            pointLightOn = !pointLightOn;
        }
        else
        {
            for (int i = 0; i < (sizeof(pointLightPositions) / sizeof(pointLightPositions[0])) - 20; i++)
            {
                pointLights[i].turnOn();
            }
            pointLightOn = !pointLightOn;
        }
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (spotlighton)
        {
            spotlight.turnOff();
            spotlighton = !spotlighton;
        }
        else
        {
            spotlight.turnOn();
            spotlighton = !spotlighton;
        }
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
            {
                pointLights[i].turnAmbientOff();
            }
            spotlight.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {
            for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
            {
                pointLights[i].turnAmbientOn();
            }
            spotlight.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
            {
                pointLights[i].turnDiffuseOff();
            }
            spotlight.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
            {
                pointLights[i].turnDiffuseOn();
            }
            spotlight.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
            {
                pointLights[i].turnSpecularOff();
            }
            spotlight.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            for (int i = 0; i < sizeof(pointLightPositions) / sizeof(pointLightPositions[0]); i++)
            {
                pointLights[i].turnSpecularOn();
            }
            spotlight.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void SkyDrop(Shader ourShader, glm::mat4 moveMatrix)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;


    glm::vec4 color = glm::vec4(0.5f);
    float currentTime = static_cast<float>(glfwGetTime());
    if ((currentTime - lastTimeSky < 0.2) && skyDropCurrent == 1.0f)
    {
    }
    else if (isSkyDropOn)
    {
        if (skyDropCurrent == 1.0f)
            skyDropY += skyDropUpSpeed;
        else
            skyDropY -= skyDropDownSpeed;

        if (skyDropY >= skyDropMax)
            skyDropCurrent = -1.0f;
        if (skyDropY <= skyDropMin)
        {
            skyDropCurrent = 1.0f;
            lastTimeSky = static_cast<float>(glfwGetTime());
            skyDropY = skyDropMin;
        }

    }


}
