#include "Engine.h"
#include "stb_image.h"
#include "objects/GameObject.h"
#include "objects/Line.h"


Engine::Engine()
{
}

Engine::~Engine()
{
    delete inputHandler;
    delete debugUI;
    delete camera;
    delete sceneManager;
    delete sky;
    delete physicsManager;
    delete renderer;
    glfwDestroyWindow(window);
    glfwTerminate();
    inputHandler = nullptr;
    debugUI = nullptr;
    camera = nullptr;
    sceneManager = nullptr;
    sky = nullptr;
    physicsManager = nullptr;
    renderer = nullptr;
}

// void test(GLFWwindow * window, int key, int scancode, int action, int mods)
// {
//      if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
//      {
//           std::cout << "KEY PRESS SPACE" << std::endl;
//      }
// }

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int Engine::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Cologne", nullptr, nullptr);
    if (window == nullptr)
    {
        CG_CORE_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        CG_CORE_ERROR("Fail to initialize GLAD");
        return -1;
    }
    stbi_set_flip_vertically_on_load(true);

    renderer = new Renderer();

    inputHandler = new InputHandler(window);
    debugUI = new DebugUI(window);
    camera = new MainCamera(glm::vec3(-12.72f, 3.93f, -9.24f));
    sceneManager = new SceneManager();
    sky = new SkyBox(RESOURCES_PATH "assets/skybox", RESOURCES_PATH "assets/skybox.vs",
                     RESOURCES_PATH "assets/skybox.fs");

    physicsManager = new PhysicsManager();
    return 0;
}

void Engine::run()
{
    // GameObject gameObject("Cube");
    // gameObject.setupShader("assets/shader.vs", "assets/lightShader.fs");
    // gameObject.shader->setVec3("color", glm::vec3(1.0f));
    // gameObject.setupModel("assets/cube/cube.obj");
    const float spacing = 2.5f;
    const int count = 20;
//    for (int i = 0; i < count; i++)
//    {
//        GameObject *cube = sceneManager->getNewGameObject();
//        cube->setupShader(RESOURCES_PATH "assets/shader.vs", RESOURCES_PATH "assets/lightShader.fs");
//        cube->shader->setVec3("color", glm::vec3(1.0f, static_cast<float>(i) / count, 0.0f));
//        cube->setupModel(RESOURCES_PATH "assets/cube/cube.obj");
//        cube->transform->setPosition(glm::vec3((static_cast<float>(i + 1) * spacing), 0.0f, 0.0f));
//        cube = nullptr;
//    }
    glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
    float t = 0.0;
    const float fixedStep = 1.0 / 60.0;
    float currentTime = (float) glfwGetTime();
    float accumulator = 0.0;
//    GameObject *cube = sceneManager->gameObjects[0];
    bool shouldPhysics = false;
    GameObject *bag = new GameObject();
    bag->setupModel(RESOURCES_PATH "assets/backpack/backpack.obj");
    bag->transform->setPosition({0, 0,1});
    Line line(RESOURCES_PATH "assets/shader.vs", RESOURCES_PATH "assets/lightShader.fs");
    glm::vec3 linePt = glm::vec3(10.0);
    glm::vec3 linePt2 = glm::vec3(10.0);
    std::vector<glm::vec3> positions;
    positions.push_back(glm::vec3( 3.0, -0.5, -3.0));
    positions.push_back(glm::vec3(-3.0, -0.5,  0.0));
    positions.push_back(glm::vec3(-3.0, -0.5, -3.0));
    positions.push_back(glm::vec3( 0.0, -0.5, -3.0));
    positions.push_back(glm::vec3( 0.0, -0.5,  0.0));
    positions.push_back(glm::vec3( 3.0, -0.5,  0.0));
    positions.push_back(glm::vec3(-3.0, -0.5,  3.0));
    positions.push_back(glm::vec3( 0.0, -0.5,  3.0));
    positions.push_back(glm::vec3( 3.0, -0.5,  3.0));
    while (!glfwWindowShouldClose(window))
    {
        // dt
        float newTime = (float) glfwGetTime();
        float deltaTime = newTime - currentTime;
        if (deltaTime > 0.25f)
            deltaTime = 0.25f;
        currentTime = newTime;
        accumulator += deltaTime;


        glfwPollEvents();
        debugUI->preRender();
        // process inputs for camera
        camera->handle_input(window, deltaTime);
        camera->debug_UI();
        ImGui::Checkbox("Physics Sim", &shouldPhysics);
        ImGui::InputFloat3("Line point", glm::value_ptr(linePt));
        ImGui::InputFloat3("Line point2", glm::value_ptr(linePt2));
        // imgui display
        // physics update
//        if (shouldPhysics)
//        {
//            physicsManager->update(deltaTime);
//            cube->transform->setPosition(glm::vec3(physicsManager->position.GetX(), physicsManager->position.GetY(),
//                                                   physicsManager->position.GetZ()));
//            cube->transform->setRotation(glm::quat(physicsManager->rotation.GetW(), physicsManager->rotation.GetX(),
//                                                   physicsManager->rotation.GetY(), physicsManager->rotation.GetZ()));
//        }
//        while (accumulator >= fixedStep)
//        {
//            if (shouldPhysics)
//            {
//            }
//            t += deltaTime;
//            accumulator -= fixedStep;
//        }

        // behavior update
        // audio update

        // update transforms
        // gameObject.transform->setPosition(glm::vec3(pos[0], pos[1], pos[2]));

        // render loop

        glm::mat4 projection = camera->getPerspectiveMatrix();
        glm::mat4 view = camera->getViewMatrix();
//        line.draw(linePt2, linePt, glm::vec3(1.0, 1.0, 1.0), projection, view);
//        sceneManager->updateObjects(view, projection);
        renderer->update(projection, view);
        for(int i = 0; i < positions.size(); i++)
        {
            bag->transform->setPosition(positions[i]);
            bag->transform->setScale(glm::vec3(0.25f));
            renderer->draw(bag);
        }
//        renderer->draw(bag);
        renderer->postUpdate(projection, view, camera->getCameraPos());

//        sky->Draw(view, projection); //todo move this somewhere else
//        physicsManager->postUpdate(view, projection);
        debugUI->render();
        debugUI->postRender();
        glfwSwapBuffers(window);
    }
    delete bag;
}
