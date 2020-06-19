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
    glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glClearColor(1.0f, 0.8f, 0.8f, 1.0f);
    //myShader = new ShaderProgram("src\\Dependiences\\v_lambert.glsl", NULL, "src\\Dependiences\\f_lambert.glsl");
    TexturedShader = std::make_shared<ShaderProgram>("src\\Dependiences\\v_lamberttextured.glsl", "no", "src\\Dependiences\\f_lamberttextured.glsl");
	//TexturedShader = std::make_shared<ShaderProgram>("src\\Dependiences\\v_simplest.glsl", "no", "src\\Dependiences\\f_simplest.glsl");
	ColorShader = std::make_shared<ShaderProgram>("src\\Dependiences\\v_lambert.glsl", "no", "src\\Dependiences\\f_lambert.glsl");

    return 0;
}

bool Window::ObjectsInit()
{
    initcastle = std::make_unique<InitCastle>(this->TexturedShader);

    this->handled = 0;

    this->clicker = true;

    this->editorMode = false;

    this->modelTemplates = initcastle->LoadTemplates();
    
    this->player_ptr = initcastle->LoadPlayer();

    this->objects = initcastle->LoadObjects();

    this->lights = initcastle->LoadLights();

    initializeSystem();

    return 0;
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

    glUniform1i(TexturedShader->u("LightsCount"), lights.size());
    glUniform3fv(TexturedShader->u("CameraPos"), 1, glm::value_ptr(camera_ptr->cameraCoords));
    for (int i = 0; i < lights.size(); i++)
    {
        std::string a = "Lights[" + std::to_string(i) + "].Color";
        std::string b = "Lights[" + std::to_string(i) + "].Pos";
        glUniform3fv(TexturedShader->u(a.c_str()), 1, glm::value_ptr(this->lights[i].color));
        glUniform3fv(TexturedShader->u(b.c_str()), 1, glm::value_ptr(this->lights[i].pos));
    }

    //MODELE
  
	auto color = player_ptr->GetColor();
 
	
	//glUniformMatrix4fv(TexturedShader->u("M"), 1, false, glm::value_ptr(player_ptr->GetMatrix()));
    player_ptr->DrawWire();
    for (int i = 100; i < 104; i++) objects[i].move_flag();
    ProcessSystem();
    for (int i = 0; i < 100; i++)
    {
        objects[i].SetPosition(system[i].position);
    }
    for (auto model : objects)
    {

		//color = model.GetColor();
        // glUniform1i(TexturedShader->u("TEX"), 0);
		//glUniform4f(TexturedShader->u("color"), color.x, color.y, color.z, 1);
        glUniformMatrix4fv(TexturedShader->u("M"), 1, false, glm::value_ptr(model.GetMatrix()));
        glUniformMatrix3fv(TexturedShader->u("NormalMatrix"), 1, false, glm::value_ptr(model.GetInvMatrix()));

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
    if (timer > 5.0 && !this->editorMode)
    {
       timer = 0;
       std::cout << "Pozycja kamer" << std::endl;
       camera_ptr->printCoords();

    }

	ProcessMovement();

	ProcessOther();

    //poruszanie obiektow
    if (this->editorMode)
        ProcessObjectMovement();


}

void Window::ProcessMovement()
{
	float przesuniecie = frameTime - lastFrameTime;

	if (glfwGetKey(window_ptr, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(FORWARD, przesuniecie);
		for (auto model : objects)
			if (!camera_ptr->noclip && model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(BACKWARD, przesuniecie);
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(BACKWARD, przesuniecie);
		for (auto model : objects)
			if (!camera_ptr->noclip && model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(FORWARD, przesuniecie);
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(LEFT, przesuniecie);
		for (auto model : objects)
			if (!camera_ptr->noclip && model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(RIGHT, przesuniecie);
	}
	if (glfwGetKey(window_ptr, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(RIGHT, przesuniecie);
		for (auto model : objects)
			if (!camera_ptr->noclip && model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(LEFT, przesuniecie);
	}

	if (glfwGetKey(window_ptr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(UP, przesuniecie);
		for (auto model : objects)
			if (!camera_ptr->noclip && model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(DOWN, przesuniecie);
	}

	if (glfwGetKey(window_ptr, GLFW_KEY_C) == GLFW_PRESS)
	{
		camera_ptr->ChangePosition(DOWN, przesuniecie);
		for (auto model : objects)
			if (!camera_ptr->noclip && model.Collision(camera_ptr->cameraCoords)) camera_ptr->ChangePosition(UP, przesuniecie);
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

    if (glfwGetKey(window_ptr, GLFW_KEY_H) == GLFW_PRESS)
        camera_ptr->noclip = false;

    if (glfwGetKey(window_ptr, GLFW_KEY_T) == GLFW_PRESS)
        camera_ptr->noclip = true;

    if (glfwGetKey(window_ptr, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera_ptr->SetFastSpeed();

    if (glfwGetKey(window_ptr, GLFW_KEY_M) == GLFW_PRESS)
        this->editorMode = true;

    if (glfwGetKey(window_ptr, GLFW_KEY_N) == GLFW_PRESS)
        this->editorMode = false;
}

void Window::ProcessObjectMovement()
{
    if (timer > 1.0)
    {
        timer = 0;
        clicker = true;
    }
    float przesuniecie = frameTime - lastFrameTime;
    float speed = this->camera_ptr->GetSpeed();

    if (glfwGetKey(window_ptr, GLFW_KEY_MINUS) == GLFW_PRESS)
        if (this->handled > 0 && clicker)
        {
            handled--;
            clicker = false;
        }


    if (glfwGetKey(window_ptr, GLFW_KEY_EQUAL) == GLFW_PRESS)
        if (this->handled + 1 < this->objects.size() && clicker)
        {
            handled++;
            clicker = false;
        }

    if (handled > this->objects.size()) return;

    if (glfwGetKey(window_ptr, GLFW_KEY_I) == GLFW_PRESS)
        objects[handled].ChangePosition(glm::vec3(-speed * przesuniecie, 0.0, 0.0));
    if (glfwGetKey(window_ptr, GLFW_KEY_K) == GLFW_PRESS)
        objects[handled].ChangePosition(glm::vec3(speed * przesuniecie, 0.0, 0.0));
    if (glfwGetKey(window_ptr, GLFW_KEY_J) == GLFW_PRESS)
        objects[handled].ChangePosition(glm::vec3(0.0, 0.0, speed * przesuniecie));
    if (glfwGetKey(window_ptr, GLFW_KEY_L) == GLFW_PRESS)
        objects[handled].ChangePosition(glm::vec3(0.0, 0.0, -speed * przesuniecie));
    if (glfwGetKey(window_ptr, GLFW_KEY_O) == GLFW_PRESS)
        objects[handled].ChangePosition(glm::vec3(0.0, speed * przesuniecie, 0.0));
    if (glfwGetKey(window_ptr, GLFW_KEY_P) == GLFW_PRESS)
        objects[handled].ChangePosition(glm::vec3(0.0, -speed * przesuniecie, 0.0));

    if (this->timer == 0)
    {
        auto pos = objects[handled].GetPosition();
        std::cout << "Nazwa obiektu " << objects[handled].GetParent()->GetName() << std::endl
            << "Nr obiektu " << handled << std::endl
            << "Pozycja obiektu " << pos.x << " " << pos.y << " " << pos.z << std::endl;
    }

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

void InitCastle::CreateSources(glm::vec3 pos, glm::vec3 col)
{
    Light a;
    a.color = col;
    a.pos = pos;
    _lights.push_back(a);
    //sources[n++] = a;

}

void Window::create_Particle()
{
    Particle a;
    a.position = glm::vec3(3, 7, -6);
    a.speed = glm::vec3((double)rand() / RAND_MAX, 5 * abs((double)rand() / RAND_MAX), (double)rand() / RAND_MAX);
    a.ttl = rand() % 100;
    system.push_back(a);
}

void Window::initializeSystem()
{
    for (int i = 0; i < ilosc; i++) create_Particle();
}

void Window::ProcessSystem()
{
    for (int i = 0; i < ilosc; i++)
    {
        system[i].position += system[i].speed * (frameTime - lastFrameTime);
        system[i].speed -= glm::vec3(0.01, 0.01f, 0.0f);
        system[i].ttl -= 0.5;
        if (system[i].ttl <= 0)
        {
            system[i].position = glm::vec3(3, 7, -6);
            system[i].speed = glm::vec3((double)rand() / RAND_MAX, 5 * abs((double)rand() / RAND_MAX), (double)rand() / RAND_MAX);
            system[i].ttl = rand() % 100;
        }
    }
}