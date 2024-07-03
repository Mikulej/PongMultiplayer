#include "main.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Client& c);

// settings
int SCR_WIDTH = 600;//1600;
int SCR_HEIGHT = 300;//900;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
std::string receiveData(std::shared_ptr<Socket> socket){
    return socket->Receive();
}
void processReceivedData(std::string str);
int main()
{
    //networking: connect to server
    
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    srand((unsigned)time(NULL));

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pong Multiplayer", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("shader/vs.glsl", "shader/fs.glsl");

    glfwSwapInterval(1);
   
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:

    Socket::Initialize();
    Client client;
    //client.startReceivingData();
    std::thread thread(&Client::receiveData, client);

    Sprite::Initialize();
    Collider::Initialize();
   
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
        processInput(window, client);
       
        // render
        // ------
        Collider::UpdateAllPos();
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Sprite::RenderAll(ourShader);
        // render container


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    Sprite::DeleteTextures();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    thread.join();
    glfwTerminate();
    return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, Client &c)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    bool neutralInput = true;
    // if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        
    // }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        neutralInput = false;
        c.sendData("8");
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        neutralInput = false;
        c.sendData("2");
    }
    if(neutralInput){
        c.sendData("5");
    }
}
void processReceivedData(std::string str){
    
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}