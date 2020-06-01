#include "window.h"


Window::Window()
{
    GLFWInit();
    std::cout << "GLFW Init Completed" << std::endl;

    if (WindowInit()) std::cout << "Mozna w sumie jakies ladne logi zrobic" << std::endl;
    else std::cout << "Window Init Completed" << std::endl;

    if (GladInit()) std::cout << "Taka mala ambicja" << std::endl;
    else std::cout << "GLAD Init Completed" << std::endl;

    if (ShadersInit()) std::cout << "Na przyszlosc" << std::endl;
    else std::cout << "Shaders Init Completed" << std::endl;

    std::cout << "Graphic dependiences ready" << std::endl;

    if (ObjectsInit()) std::cout << "Daleka przyszlosc" << std::endl;
    else std::cout << "Objects Init Completed" << std::endl;
}

void Window::GLFWInit()
{
    glfwInit();
   // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

bool Window::GladInit()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    return 0;
}


bool Window::WindowInit()
{
    window_ptr = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window_ptr == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window_ptr);
    glfwSetWindowUserPointer(window_ptr, this);

    glfwSwapInterval(1);
    glfwSetInputMode(window_ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    camera_ptr = std::make_unique<Camera>();

    glfwSetCursorPosCallback(window_ptr, ProcessMouse_call);
    glfwSetFramebufferSizeCallback(window_ptr, ChangeViewSize_call);


    return 0;
}

bool Window::ShadersInit()
{
    //glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	glClearColor(1.0f, 0.8f, 0.8f, 1.0f);

    //myShader = new ShaderProgram("src\\Dependiences\\v_lambert.glsl", NULL, "src\\Dependiences\\f_lambert.glsl");
    TexturedShader = std::make_shared<ShaderProgram>("src\\Dependiences\\v_lamberttextured.glsl", "no", "src\\Dependiences\\f_lamberttextured.glsl");
	//TexturedShader = std::make_shared<ShaderProgram>("src\\Dependiences\\v_simplest.glsl", "no", "src\\Dependiences\\f_simplest.glsl");
	ColorShader = std::make_shared<ShaderProgram>("src\\Dependiences\\v_lambert.glsl", "no", "src\\Dependiences\\f_lambert.glsl");

    return 0;
}

bool Window::ObjectsInit()
{
        
	CreateTemplate("data\\Castle\\Castle OBJ.obj", "castle", TexturedShader);

	CreateTemplate("data\\cube.obj", "cube", TexturedShader);
	CreateTemplate("data\\medieval-house.obj", "house", TexturedShader);
	CreateTemplate("data\\mur.obj", "mur", TexturedShader);
	CreateTemplate("data\\stragan.obj", "stragan", TexturedShader);

	scale_x = 0.2;
	scale_y = 0.2;
	scale_z = 0.2;

	// ty
	player_ptr = std::make_unique<Model>(FindTemplate("cube"), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 1.0f));

	//podloga

    CreateObject("cube", glm::vec3(-10*scale_x, -0.45f, 40*scale_z), glm::vec3(150*scale_x, 0.1, 160*scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	CreateObject("house", glm::vec3(50.4f, 0.2f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	CreateObject("castle", glm::vec3(40.4f, 0.2f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0, glm::vec3(1.0f, 0.0f, 0.0f));
	//mury
 
	CreateObject("mur", glm::vec3(140*scale_x, 0 * scale_y, 40*scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0,  glm::vec3(0.0f, 1.0f, 0.0f));                                //0.0f, 0.0f, 0.0f
	CreateObject("mur", glm::vec3(0.0f, 0.0f, -120*scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));                                //-1.0f, 0.0f, 13.5f
	CreateObject("mur", glm::vec3(-160*scale_x, 0.0f,40*scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI, glm::vec3(0.0f, 1.0f, 0.0f));                           //13.5f, 0.0f, 14.5f
	CreateObject("mur", glm::vec3(-20*scale_x, 0.0f, 200*scale_z), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI * 3 / 2, glm::vec3(0.0f, 1.0f, 0.0f));                    //14.5f, 0.0f, 1.0f

	//stragany
    scale_x = 0.3;
    scale_y = 0.3;
    scale_z = 0.3;
    for (int i = 0; i < 20; i += 3)
    {
		CreateObject("stragan", glm::vec3(-103 * scale_x, -0.5f, i), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f,  glm::vec3(0.0f, 0.0f, 1.0f));
		CreateObject("stragan", glm::vec3(-103 * scale_x, -0.5f, i+1), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f,  glm::vec3(0.0f, 0.0f, 1.0f));

		CreateObject("stragan", glm::vec3(-90 * scale_x, -0.5f, i), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI,  glm::vec3(0.0f, 0.0f, 1.0f));
		CreateObject("stragan", glm::vec3(-90 * scale_x, -0.5f, i + 1), glm::vec3(scale_x, scale_y, scale_z), glm::vec3(0.0f, 1.0f, 0.0f), PI,  glm::vec3(0.0f, 0.0f, 1.0f));
    }
    return 0;
}

void Window::CreateTemplate(std::string path, std::string name, std::shared_ptr<ShaderProgram> shader)
{
	modelTemplates.push_back(std::make_shared<ModelTemplate>(path, name, shader));
}

std::shared_ptr<ModelTemplate> Window::FindTemplate(std::string name)
{
	for (auto temp : this->modelTemplates)
		if (name == temp->GetName()) return temp;
}

void Window::CreateObject(std::string name, glm::vec3 position, glm::vec3 scale, glm::vec3 rotate, float angle, glm::vec3 color)
{
	this->objects.push_back(Model(FindTemplate(name), position, scale, rotate, angle, color));
}

void Window::ChangeViewSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//PETLA
bool Window::StartWindow()
{

    glfwSetTime(0); //Wyzeruj timer
    frameTime = 0;
    timer = 0;

    while (!glfwWindowShouldClose(window_ptr))
    {

        //INPUT
        ProcessInput();

        //RENDER
        RenderWindow();

        //FINISH
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void Window::RenderWindow()
{

    //RandomClearColor();
    ClearWindow();
    glm::mat4 V = glm::lookAt(camera_ptr->cameraCoords, camera_ptr->cameraViewCoords + camera_ptr->cameraCoords, camera_ptr->cameraDefUpCoords); //Wylicz macierz widoku
    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 100.0f); //Wylicz macierz rzutowania

    TexturedShader->use(); //Aktywuj program cieniuj¹cy
    glUniformMatrix4fv(TexturedShader->u("P"), 1, false, glm::value_ptr(P)); //Za³aduj do programu cieniuj¹cego macierz rzutowania
    glUniformMatrix4fv(TexturedShader->u("V"), 1, false, glm::value_ptr(V)); //Za³aduj do programu cieniuj¹cego macierz widoku


    //MODELE
	auto color = player_ptr->GetColor();
	glUniform4f(TexturedShader->u("color"), color.x, color.y, color.z, 1);
	glUniformMatrix4fv(TexturedShader->u("M"), 1, false, glm::value_ptr(player_ptr->GetMatrix()));
	player_ptr->DrawWire();
  
    for (auto model : objects)
    {
		color = model.GetColor();
		glUniform4f(TexturedShader->u("color"), color.x, color.y, color.z, 1);
        glUniformMatrix4fv(TexturedShader->u("M"), 1, false, glm::value_ptr(model.GetMatrix()));
        model.Draw();
    }

    glfwSwapBuffers(window_ptr);
}

void Window::ProcessMouse(GLFWwindow* window, double xpos, double ypos)
{
    camera_ptr->ChangeViewPosition(xpos, ypos);
}


void Window::ProcessInput()
{
    timer += glfwGetTime() - frameTime;
    lastFrameTime = frameTime;
    frameTime = glfwGetTime();
	//std::cout << camera_ptr->cameraCoords.x << " " << camera_ptr->cameraCoords.y << " " << camera_ptr->cameraCoords.z << std::endl;
    if (timer > 5.0)
    {
        timer = 0;
       std::cout << "Pozycja kamer" << std::endl;
       camera_ptr->printCoords();
    }

	ProcessMovement();

	ProcessOther();
}

void Window::ProcessMovement()
{
	float przesuniecie = frameTime - lastFrameTime;

	if (glfwGetKey(window_ptr, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(FORWARD, przesuniecie);
		for (auto model : objects)
			if (model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(BACKWARD, przesuniecie);
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(BACKWARD, przesuniecie);
		for (auto model : objects)
			if (model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(FORWARD, przesuniecie);
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(LEFT, przesuniecie);
		for (auto model : objects)
			if (model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(RIGHT, przesuniecie);
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(RIGHT, przesuniecie);
		for (auto model : objects)
			if (model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(LEFT, przesuniecie);
	}

	if (glfwGetKey(window_ptr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(UP, przesuniecie);
		for (auto model : objects)
			if (model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(DOWN, przesuniecie);
	}

	if (glfwGetKey(window_ptr, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(DOWN, przesuniecie);
		for (auto model : objects)
			if (model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(UP, przesuniecie);
	}

	player_ptr->SetPosition(camera_ptr->cameraCoords);
}

void Window::ProcessOther()
{
	if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window_ptr, true);

	if (glfwGetKey(window_ptr, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		camera_ptr->IncreaseSpeed();

	if (glfwGetKey(window_ptr, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		camera_ptr->DecreaseSpeed();

	if (glfwGetKey(window_ptr, GLFW_KEY_KP_MULTIPLY) == GLFW_PRESS)
		camera_ptr->ResetSpeed();
}

void Window::ClearWindow()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ChangeViewSize_call(GLFWwindow* window, int width, int height)
{
	Window* wind = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	wind->ChangeViewSize(window, width, height);
}
void ProcessMouse_call(GLFWwindow* window, double xpos, double ypos)
{
	Window* wind = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	wind->ProcessMouse(window, xpos, ypos);
}