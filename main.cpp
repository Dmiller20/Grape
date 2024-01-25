#include <iostream>
#include<glad/glad.h>
#include <GLFW/glfw3.h>

const int width = 720;
const int height = 1280;
unsigned int VBO;  // vertex buffer object
//const char *vertexShaderSource = 
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

const char* v_shader = "#version 330 core\n"
"layout (location = 0) in vec3 _pos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(_pos.x, _pos.y, _pos.z, 1.0f); \n"
"} \0";

const char* f_shader = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";



float vertices[] =
	{
		//x    //y   //z
		-.75f, 0.0f, 0.0f,
		.25f, .85f, 0.0f,
		0.0f, -.95f, 0.0f
	};


void processInput(GLFWwindow * window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
		
}

int main()
{
	std::cout << "Grape Engine. Dylan Miller. 2024" << std::endl;


	GLFWwindow* window;
	glfwInit();

	if(!glfwInit())
	{
		return -1;
	}

	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(height, width, "Grape", NULL, NULL);

	if(!window)
	{
		std::cout << "Failed to create GLFW window nigga" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad" << std::endl;
		return -1;
	}
	//vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &v_shader, NULL);
	glCompileShader(vertexShader);

	//fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &f_shader, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//if error, replace vbo with gl array buffer
	glBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	

	while(!glfwWindowShouldClose(window))
	{
		
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	glfwTerminate();
	return 0;
}