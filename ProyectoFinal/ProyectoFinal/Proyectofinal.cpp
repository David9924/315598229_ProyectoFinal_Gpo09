
// Gómez Serna Carlos David
// 315598229
// Computación Grafica e Interacción Humano Computadora 
// GPO09

//Se manda a llamar todas las librerias y archivos que utilizamos para el proyecto ////


#include <iostream>
#include <cmath>                  

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes // Se crean las funciones que utilizaremos en nuestro ambiente, en este caso son 4.
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode); //KeyCallback para mandar a llamar las teclas.
void MouseCallback(GLFWwindow *window, double xPos, double yPos); //MouseCallBack se utiliza para el manejo de la camara
void DoMovement(); // DoMovement se utiliza para crear animaciones y mandarlos a llamar con las teclas
void animacion(); //Esta función se utilizara para la animación compleja

// Window dimensions //Colocamos las dimensiones de la ventana ejecutable.
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera 
Camera  camera(glm::vec3(0.0f, 20.0f, 3.0f)); //Se configura la posición de la camara
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes     
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-4.0f, 17.2f, -8.0f);
//Creamos las variables que utilizaremos
bool active;
bool active2;
bool active3;
bool active4;
float rot = 90;
float rot1 = 0.0f;
float rot2 = 0.0f;
bool anim = false;
bool anim2 = false;

//Animacion Navy //Creamos las variables que utilizaremos para la animación compleja. 
//Se inicializan tres variables en cero. 
float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0;

bool camino = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;

// Positions of the point lights //Posición de los puntos de luz. 
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,22.0f, -1.0f),
	glm::vec3(0.0f,22.0f, -1.0f),
	glm::vec3(0.0f,22.0f,  -1.0f),
	glm::vec3(0.0f,22.0f, -1.0f)
};

glm::vec3 pointLightPositions1[] = {
	glm::vec3(0.0f,22.0f, -2.0f),
	glm::vec3(0.0f,22.0f, -2.0f),
	glm::vec3(0.0f,22.0f,  -2.0f),
	glm::vec3(0.0f,22.0f, -2.0f)
};

glm::vec3 pointLightPositions2[] = {
	glm::vec3(0.0f,22.0f, 1.0f),
	glm::vec3(0.0f,22.0f, 1.0f),
	glm::vec3(0.0f,22.0f,  1.0f),
	glm::vec3(0.0f,22.0f, 1.0f)
};

glm::vec3 pointLightPositions3[] = {
	glm::vec3(0.0f,22.0f, -3.0f),
	glm::vec3(0.0f,22.0f, -3.0f),
	glm::vec3(0.0f,22.0f,  -3.0f),
	glm::vec3(0.0f,22.0f, -3.0f)
};

float vertices[] = { //Se crean los vertices para los pointlights //Make pointlights vertex
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



glm::vec3 Light1 = glm::vec3(0);
glm::vec3 Light2 = glm::vec3(0);
glm::vec3 Light3 = glm::vec3(0);
glm::vec3 Light4 = glm::vec3(0);


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame  //Tiempo entre el primer frame y el ultimo. 
GLfloat lastFrame = 0.0f;  	// Time of last frame  //Tiempo del ultimo frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions //Se crea el objeto GLFWwindoes para poder usar las funciones GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final 315598229_GPO9", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions //Mandamos a llamar la función con las siguientes glfw
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers // Se inicializan GLEW 
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions // Se definen las dimensiones del viewport
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Se manda a llamar a los objetos que utilizaremos // The models are called 

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader anim("Shaders/anim2.vs", "Shaders/anim2.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
	
	Model Piso((char*)"Models/Esfera/Piso2.obj");
	Model Mesa((char*)"Models/Mesa/mesa.obj");
	Model Box((char*)"Models/Box/Box.obj");
	Model Espada((char*)"Models/Espada/Espada.obj");
	Model Jarron((char*)"Models/Jarron/Jarron.obj");
	Model Cofreab((char*)"Models/Cofre/Cofreab.obj");
	Model Cofreabaj((char*)"Models/Cofre/Cofreabaj.obj");
	Model Navy((char*)"Models/Navy/navycuerpo.obj");
	Model Navyala((char*)"Models/Navy/navyala1.obj");
	Model Navyala2((char*)"Models/Navy/navyala2.obj");
	Model Cama((char*)"Models/Cama/Cama.obj");
	Model Linkcab((char*)"Models/Link/Cabeza.obj");
	Model Linkcuerpo1((char*)"Models/Link/Cuerpo.obj");
	Model Linkcuerpo2((char*)"Models/Link/Cuerpo2.obj");
	Model Linkmano1((char*)"Models/Link/Mano1.obj");
	Model Linkbrazo1((char*)"Models/Link/Brazo1.obj");
	Model Linkmano2((char*)"Models/Link/Mano2.obj");
	Model Linkbrazo2((char*)"Models/Link/Brazo2.obj");
	Model Linkpierna1((char*)"Models/Link/Pierna1.obj");
	Model Linkpierna2((char*)"Models/Link/Pierna2.obj");
	Model Casa((char*)"Models/Casa/Casa.obj");
	Model Ventana((char*)"Models/Casa/Ventana.obj");
	Model mesa2((char*)"Models/Hogar/mesa.obj");

	GLfloat skyboxVertices[] = {   //Se crean los vertices para el skybox. // Vertex are created for the skybox 
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"),1);

	//SkyBox  //Se crea el VBO de SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Load textures //Se cargan las texturas del Skybox
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame //Calculos del deltatime
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		//Checamos si algun evento ha sido activado (tecla, movimiento de mouse ect.) y se manda a llamar la función responsable
		glfwPollEvents();
		DoMovement();
		animacion();

		// Clear the colorbuffer //Se limpia el colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);



		//Load Model //Cargando modelos


		// Use cooresponding shader when setting uniforms/drawing objects 
		//Se usa el shader correspondiente para mandar a dibujar los objetos.
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light //Direcciones de luz
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.4f, 0.4f, 0.4f);

		//Se crean los point lights que en total son 4.

		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.8f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.8f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.8f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.8f);

		//POINTLIGHT2

		// Point light 1
		glm::vec3 lightColor2;
		lightColor2.x = abs(sin(glfwGetTime() * Light2.x));
		lightColor2.y = abs(sin(glfwGetTime() * Light2.y));
		lightColor2.z = sin(glfwGetTime() * Light2.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[0].position"), pointLightPositions1[0].x, pointLightPositions1[0].y, pointLightPositions1[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[0].ambient"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[0].diffuse"), lightColor2.x, lightColor2.y, lightColor2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[0].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[0].linear"), 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[0].quadratic"), 0.8f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[1].position"), pointLightPositions1[1].x, pointLightPositions1[1].y, pointLightPositions1[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[1].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[1].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[1].quadratic"), 0.0f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[2].position"), pointLightPositions1[2].x, pointLightPositions1[2].y, pointLightPositions1[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[2].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[2].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[2].quadratic"), 0.0f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[3].position"), pointLightPositions1[3].x, pointLightPositions1[3].y, pointLightPositions1[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights1[3].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[3].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights1[3].quadratic"), 0.0f);

		//POINT LIGHT 3 

		// Point light 1
		glm::vec3 lightColor3;
		lightColor3.x = abs(sin(glfwGetTime() * Light3.x));
		lightColor3.y = abs(sin(glfwGetTime() * Light3.y));
		lightColor3.z = sin(glfwGetTime() * Light3.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[0].position"), pointLightPositions2[0].x, pointLightPositions2[0].y, pointLightPositions2[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[0].ambient"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[0].diffuse"), lightColor3.x, lightColor3.y, lightColor3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[0].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[0].linear"), 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[0].quadratic"), 0.8f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[1].position"), pointLightPositions2[1].x, pointLightPositions2[1].y, pointLightPositions2[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[1].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[1].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[1].quadratic"), 0.0f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[2].position"), pointLightPositions2[2].x, pointLightPositions2[2].y, pointLightPositions2[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[2].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[2].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[2].quadratic"), 0.0f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[3].position"), pointLightPositions2[3].x, pointLightPositions2[3].y, pointLightPositions2[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights2[3].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[3].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights2[3].quadratic"), 0.0f);

		//POINTLIGHT 3

		// Point light 1
		glm::vec3 lightColor4;
		lightColor4.x = abs(sin(glfwGetTime() * Light4.x));
		lightColor4.y = abs(sin(glfwGetTime() * Light4.y));
		lightColor4.z = sin(glfwGetTime() * Light4.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[0].position"), pointLightPositions3[0].x, pointLightPositions3[0].y, pointLightPositions3[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[0].ambient"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[0].diffuse"), lightColor4.x, lightColor4.y, lightColor4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[0].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[0].linear"), 0.5f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[0].quadratic"), 0.2f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[1].position"), pointLightPositions3[1].x, pointLightPositions3[1].y, pointLightPositions3[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[1].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[1].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[1].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[1].quadratic"), 0.0f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[2].position"), pointLightPositions3[2].x, pointLightPositions3[2].y, pointLightPositions3[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[2].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[2].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[2].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[2].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.0f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[3].position"), pointLightPositions3[3].x, pointLightPositions3[3].y, pointLightPositions3[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[3].ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[3].diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights3[3].specular"), 0.964f, 0.956f, 0.913f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[3].linear"), 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights3[3].quadratic"), 0.0f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.44f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));



		// Set material properties
		//Se crena las propiedades del material. 
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

		// Create camera transformations
		//Se crea la transformación de la camara
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		//Pasamos las matrices al shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);

		// A partir de este punto, se dibujan los modelos que mandamos a llamar en funciones anteriores 

		//Mdels that we send to call in previous functions are drawn

		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-0.2f, 7.2f, -1.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		Mesa.Draw(lightingShader);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 10.0f));

		//Cofre

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-5.7f, 15.1f, -2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rot1), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Cofreab.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-5.7f, 15.1f, -2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		Cofreabaj.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);
		
		//Navy 

		model = glm::mat4(1);
		model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		Navy.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		Navyala.Draw(anim);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1);
		model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		model = glm::rotate(model, glm::radians(rotKit), glm::vec3(0.0f, 1.0f, 0.0));
		Navyala2.Draw(anim);

		//Espada

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.23f, 0.3f, 0.3f));
		model = glm::translate(model, glm::vec3(-0.6f, 50.5f, -9.4f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		Espada.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//Jarron

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::translate(model, glm::vec3(10.0f, 27.8f, 13.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		Jarron.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.2f, 14.6f, -9.5f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		Cama.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//Link

		//LinkCabeza


		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		Linkcab.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);
		
		//LinkCuerpo

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		Linkcuerpo1.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);
		
		//LinkCuerpo2

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		Linkcuerpo2.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//LinkMano

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		Linkmano1.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//LinkBrazo1

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		Linkbrazo1.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//LinkMano2

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		Linkmano2.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//LinkBrazo2

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		Linkbrazo2.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//LinkPierna1

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		Linkpierna1.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//LinkPierna2

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 7.9f, -3.5f));
		Linkpierna2.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);


		//Casa

		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 8.0f, -1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		Casa.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//Ventana
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 8.0f, -1.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rot2), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		Ventana.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);

		//Objetos 
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(-1.2f, 3.6f, -1.4f));
		glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		mesa2.Draw(lightingShader);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 1.0f, 1.0f, 1.0f);


		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glBindVertexArray(0);
	

		// Also draw the lamp object, again binding the appropriate shader 
		//Además de dibujar el objeto lamp, lo unimos con el shader apropiado.
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		// Obtenemos la ubicación de los objetos de las matrices del lamp shader
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		//Dibujamos el light object (utilizando los vertices creados anteriormente)
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube //Creamos un pequeño cubo
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions1[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube // Creamos un pequeño cubo
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions2[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube //Creamos un pequeño cubo
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions3[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube //Creamos un pequeño cubo
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// Draw skybox as last //Se dibuja el skybox 
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix 
																//Quitamos cualquier traslasión del componente vista en la matriz
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube //Creamos el cubo skybox
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default


		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW. //Terminamos GLFW, limpiando cualquier recurso.
	glfwTerminate();

	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);


	return 0;
}

// Moves/alters the camera positions based on user input 
//Movimientos/alteración de la posición de la camara basada en las entradas
void DoMovement()
{

	// Camera controls //Control de la camara
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
		pointLightPositions1[0].x -= 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}

	//La variable bool camino aparecera como true al ingresar la tecla O
	if (keys[GLFW_KEY_O])
	{
		camino = true;
	}
	//En caso contrario el bool camino aparecera como false al presionar la tecla P
	if (keys[GLFW_KEY_P])
	{
		camino = false;
	}

	//Se crea una animación para que el cofre y la ventana cierren y abran. 
	if (anim && rot1 < 45) {
		rot1 += 0.5f;
	}
	else if (!anim && rot1 > 0) {
		rot1 -= 0.5f;
	}

	if (anim2 && rot2 < 4) {
		rot2 += 0.5f;
	}
	else if (!anim2 && rot2 > 0) {
		rot2 -= 0.5f;
	}
	
}

//En esta función, se pondra la animación compleja de un modelo.
void animacion()
{

	//Movimiento de Navi
	if (camino)
	{
		if (recorrido1)
		{
			movKitZ += 0.1f;
			if (movKitZ > 2)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			rotKit = 90;
			movKitX += 0.1f;
			if (movKitX > 8)
			{
				recorrido2 = false;
				recorrido3 = true;

			}
		}

		if (recorrido3)
		{
			rotKit = 180;
			movKitZ -= 0.1f;
			if (movKitZ < 0)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}

		if (recorrido4)
		{
			rotKit = 270;
			movKitX -= 0.1f;
			if (movKitX < 0)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if (recorrido5)
		{
			rotKit = 0;
			movKitZ += 0.1f;
			if (movKitZ > 0)
			{
				recorrido5 = false;
				recorrido1 = true;
			}
		}


	}
}

// Is called whenever a key is pressed/released via GLFW //Se manda a llamar cuando una tecla es presionada
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 0.0f);

		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
								  // When is only one value in the 3 vectors can leave only one component 
		}

		active2 = !active2;
		if (active2)
		{
			Light2 = glm::vec3(1.0f, 0.0f, 0.0f);

		}
		else
		{
			Light2 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
								  // When is only one value in the 3 vectors can leave only one component 
		}

		active3 = !active3;
		if (active3)
		{
			Light3 = glm::vec3(1.0f, 0.717f, 0.160f);

		}
		else
		{
			Light3 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
			                       //When is only one value in the 3 vectors can leave only one component
		}

		active4 = !active4;
		if (active4)
		{
			Light4 = glm::vec3(0.027f, 1.0f, 0.0f);

		}
		else
		{
			Light4 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
								  // When is only one value in the 3 vectors can leave only one component 
		}

	}

	if (keys[GLFW_KEY_L])
		anim = !anim;

	if (keys[GLFW_KEY_K])
		anim2 = !anim2;
}

//Se manda a llamar esta función cuando se utiliza el mouse. Quiere decir que con esta función podemos manejar el mouse libremente en el ambiente.
//This function is called when the mouse is used. It means that with this function we can handle the mouse freely in the environment. 
void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}