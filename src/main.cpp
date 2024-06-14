#include "main.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Socket& s);

// settings
int SCR_WIDTH = 600;//1600;
int SCR_HEIGHT = 300;//900;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
std::string receiveData(std::shared_ptr<Socket> socket){
    return socket->Receive();
}
void processReceivedData(std::string str){
    
}
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
    std::shared_ptr<Socket> s(new Socket(66671));
    s->Connect("127.0.0.1");
    // while(true){
    //     std::cout << s->Receive() << std::endl;
    // }
    // auto networkLambda = [](){
        // Socket::Initialize();
        // Socket s(66670);
        // s.Connect("127.0.0.1");
        // clock_t this_time = clock();
        // clock_t last_time = this_time;
        // double time_counter = 0;
        // while(true)
        // {
        //     this_time = clock();

        //     time_counter += (double)(this_time - last_time);

        //     last_time = this_time;

        //     if(time_counter > (double)(5 * CLOCKS_PER_SEC))
        //     {
        //         time_counter -= (double)(5 * CLOCKS_PER_SEC);
        //         s.Send("No siema!");
        //     }
        // }

    // };

    //std::thread networkThread(networkLambda);
   


    Sprite::Initialize();
    Collider::Initialize();
    

    // Sprite::get(idplayer1).setScale(0.5,2.5);
    // int idplayer2 = Sprite::Add("box",-0.8f,0,0);
    // Sprite::get(idplayer2).setScale(0.5,2.5);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        glfwGetWindowSize(window, &SCR_WIDTH, &SCR_HEIGHT);
        processInput(window,*s);

        // render
        // ------
       
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
    glfwTerminate();
    return 0;
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, Socket &s)
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
        //Sprite::get(0).addPos(0,1.0f*deltaTime);
        neutralInput = false;
        s.Send("8");
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        //Sprite::get(0).addPos(0,-1.0f*deltaTime);
        neutralInput = false;
        s.Send("2");
    }
    if(neutralInput){
        s.Send("5");
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