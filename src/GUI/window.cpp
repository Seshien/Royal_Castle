#include "window.h"

std::vector<Model*> objects;

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
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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
    //myShader = new ShaderProgram("src\\Dependiences\\v_lambert.glsl", NULL, "src\\Dependiences\\f_lambert.glsl");
    myShader = std::make_unique<ShaderProgram>("src\\Dependiences\\v_lambert.glsl", "no", "src\\Dependiences\\f_lambert.glsl");
    glEnable(GL_DEPTH_TEST);

    return 0;
}

bool Window::ObjectsInit()
{
    static_object* obj = new static_object("src\\cube.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.0f, 0.0f, 0.0f));
    obj->create_object();
    static_object* obj2 = new static_object("src\\cube.obj", glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.4f, 0.2f, 0.3f), glm::vec3(0.0f, 0.0f, 0.0f));
    obj2->create_object();
    objects.push_back(obj);
    objects.push_back(obj2);
    return 0;
}

void Window::ChangeViewSize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//PETLA
bool Window::StartWindow()
{

    ChangeClearColor(0,0,0,1);


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
    glm::mat4 P = glm::perspective(glm::radians(50.0f), 1.0f, 1.0f, 50.0f); //Wylicz macierz rzutowania

    myShader->use(); //Aktywuj program cieniuj¹cy
    glUniform4f(myShader->u("color"), 0, 1, 0, 1); //Ustaw kolor rysowania obiektu
    glUniformMatrix4fv(myShader->u("P"), 1, false, glm::value_ptr(P)); //Za³aduj do programu cieniuj¹cego macierz rzutowania
    glUniformMatrix4fv(myShader->u("V"), 1, false, glm::value_ptr(V)); //Za³aduj do programu cieniuj¹cego macierz widoku



    //MODELE


    glm::mat4 I = glm::mat4(1.0f);

   /* glm::mat4 Mt1 = glm::translate(I, glm::vec3(-1.0f, 0.0f, 0.0f)); //Macierz torusa to najpierw przesuniêcie do odpowiedniej pozycji...
    Mt1 = glm::rotate(Mt1, 0.1f * time, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót ¿eby nasz "tryb" by³ odpowiednio obrócony
    glUniformMatrix4fv(myShader->u("M"), 1, false, glm::value_ptr(Mt1));
    glUniform4f(myShader->u("color"), 0, 1, 0, 1);
   // Models::teapot.drawSolid();

    glm::mat4 Mt2 = glm::translate(I, glm::vec3(1.0f, 0.0f, 0.0f)); //Macierz torusa to najpierw przesuniêcie do odpowiedniej pozycji...
    Mt2 = glm::rotate(Mt2, -0.1f * time, glm::vec3(0.0f, 0.0f, 1.0f)); //... potem obrót ¿eby nasz "tryb" by³ odpowiednio obrócony
    glUniformMatrix4fv(myShader->u("M"), 1, false, glm::value_ptr(Mt2));
    glUniform4f(myShader->u("color"), 0, 1, 0, 1);
    //Model::teapot.drawSolid();*/
    glUniformMatrix4fv(myShader->u("M"), 1, false, glm::value_ptr(objects[0]->Mat));
    objects[0]->drawSolid();
    glUniformMatrix4fv(myShader->u("M"), 1, false, glm::value_ptr(objects[1]->Mat));
    objects[1]->drawSolid();

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

    if (timer > 5.0)
    {
        timer = 0;
        std::cout << "Pozycja" << std::endl;
        camera_ptr->printCoords();
    }

    if (glfwGetKey(window_ptr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window_ptr, true);

    if (glfwGetKey(window_ptr, GLFW_KEY_W) == GLFW_PRESS)
        camera_ptr->ChangePosition(FORWARD, frameTime - lastFrameTime);
    if (glfwGetKey(window_ptr, GLFW_KEY_S) == GLFW_PRESS)
        camera_ptr->ChangePosition(BACKWARD, frameTime - lastFrameTime);
    if (glfwGetKey(window_ptr, GLFW_KEY_A) == GLFW_PRESS)
        camera_ptr->ChangePosition(LEFT, frameTime - lastFrameTime);
    if (glfwGetKey(window_ptr, GLFW_KEY_D) == GLFW_PRESS)
        camera_ptr->ChangePosition(RIGHT, frameTime - lastFrameTime);
}

void Window::ChangeClearColor(float x = 0.0f, float y = 0.0f, float z = 0.0f, float a = 1.0f)
{
    glClearColor(x, y, z, a);
}

void Window::RandomClearColor()
{
    ChangeClearColor(rand() % 100 / 100.0, rand() % 100 / 100.0, rand() % 100 / 100.0, rand() % 100 / 100.0);
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