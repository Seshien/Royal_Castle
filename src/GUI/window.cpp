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
    TexturedShader = std::make_shared<ShaderProgram>("src/Dependiences/v_lamberttextured.glsl", "no", "src/Dependiences/f_lamberttextured.glsl");

	SkyBoxShader = std::make_shared<ShaderProgram>("src/Dependiences/v_skybox.glsl", "no", "src/Dependiences/f_skybox.glsl");

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

	this->skybox_ptr = initcastle->LoadSkybox(this->SkyBoxShader);

    InitializeParticles();
	InitializeFlags();

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

		ProcessInternal();

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
	//Czyszczenie okna
    ClearWindow();


    glm::mat4 V = glm::lookAt(camera_ptr->cameraCoords, camera_ptr->cameraViewCoords + camera_ptr->cameraCoords, camera_ptr->cameraDefUpCoords); //Wylicz macierz widoku
    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 300.0f); //Wylicz macierz rzutowania

    TexturedShader->use();
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

    for (auto model : objects)
    {
        model.Draw();
    }

	SkyBoxShader->use();

	//usuwamy translacje z macierzy widoku, by skybox sie nie poruszal
	V = glm::mat4(glm::mat3(V));


	glUniformMatrix4fv(SkyBoxShader->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(SkyBoxShader->u("V"), 1, false, glm::value_ptr(V));

	skybox_ptr->Draw();


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

	ProcessInputMovement();

	ProcessInputOther();

    //poruszanie obiektow
    if (this->editorMode)
        ProcessInputObjectMovement();


}

void Window::ProcessInputMovement()
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

void Window::ProcessInputOther()
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

void Window::ProcessInputObjectMovement()
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



void Window::CreateParticle(Model *model)
{
    Particle particle;
    particle.position = model->GetPosition();
    particle.source = model->GetPosition();
    particle.speed = glm::vec3((double)rand() / RAND_MAX, 5 * abs((double)rand() / RAND_MAX), (double)rand() / RAND_MAX);
    particle.ttl = (rand() % 25) / 10.0f;
	particle.model = model;
    particles.push_back(particle);
}
void Window::CreateFlag(Model *model)
{
	Flag a;
	a.flag_angle = 0.0f;
	a.flag_speed = 0.0005f;
	a.model = model;
	flags.push_back(a);
}
void Window::InitializeParticles()
{
	for (auto & model : objects)
		if (model.GetParent()->GetName() == "dym") CreateParticle(&model);
}

void Window::InitializeFlags()
{
	for (auto & model : objects)
		if (model.GetParent()->GetName() == "flaga") CreateFlag(&model);
}
void Window::ProcessInternal()
{

	for (auto & flag : flags)
	{
		flag.flag_angle += flag.flag_speed;
		if (flag.flag_angle > PI / 100)
			flag.flag_speed *= -1;
		else if (flag.flag_angle < -PI / 100)
			flag.flag_speed *= -1;

		flag.model->ChangeRotation(glm::vec3(0, 1, 0), flag.flag_angle);
	}

	for (auto & particle : particles)
	{
		particle.position += particle.speed * (frameTime - lastFrameTime);
		if (particle.speed.x > 0.01f && particle.speed.y > 0.01f && particle.speed.z > 0.01f) particle.speed -= glm::vec3(0.01f, 0.01f, 0.01f);
		particle.ttl -= (frameTime - lastFrameTime);
		if (particle.ttl <= 0)
		{
			particle.position = glm::vec3(particle.source.x + (rand() % 200 - 100) / 1000.0f, particle.source.y + (rand() % 200 - 100) / 1000.0f, particle.source.z + (rand() % 200 - 100) / 1000.0f);
			particle.speed = glm::vec3((double)rand() / (3.0 * RAND_MAX), abs((double)rand() / RAND_MAX) + 0.1f, (double)rand() / (3.0 * RAND_MAX));
            particle.ttl = (rand() % 25) / 10.0f;
		}
		particle.model->SetPosition(particle.position);
	}
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
