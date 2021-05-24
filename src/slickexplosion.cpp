/**********************************************************
 *   SlickExplosion:  A class to encapsulate creating an 
 *   OpenGL window.
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   12/2019 San Diego, California USA
 * ********************************************************/

#include "../include/slickexplosion.h"


SlickExplosion::SlickExplosion()
{
    cout << "\n\n\tCreating SlickExplosion\n\n";
    quit = false;
    camera = new Camera(SCR_WIDTH, SCR_HEIGHT, vec3(0.0f, 0.0f, 18.0f), vec3(0.0f, 0.0f, 0.0f)); 
    width = SCR_WIDTH;
    height = SCR_HEIGHT;
    execLoop();
}

SlickExplosion::~SlickExplosion()
{
    cout << "\n\n\tDestroying SlickExplosion\n\n";
    delete camera;
}



void SlickExplosion::execLoop()
{
    cout << "\n\n\tIn execLoop.\n\n";
    SDL_Event e;
    
    quit = false;
    try
    {
        // Setup the window
        if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
            logSDLError(cout, "SDL_Init");
            exit(1);
        }
        else
        {
            cout << "\n\n\tInitialized SDL.\n\n";
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        window = SDL_CreateWindow("Slick Explosion", 1000, 900, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
        if (window == nullptr){
            logSDLError(cout, "CreateWindow");
            SDL_Quit();
            exit(1);
        }
        else
        {
            cout << "\n\n\tCreated SDL window.\n\n";
        }
        
        context = SDL_GL_CreateContext(window);
        if (context == nullptr){
            logSDLError(cout, "CreateContext");
            SDL_DestroyWindow(window);
            SDL_GL_DeleteContext(context);
            SDL_Quit();
            exit(1);
        }
        else
        {
            cout << "\n\n\tCreated SDL context.\n\n";
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if (renderer == nullptr){
            logSDLError(cout, "CreateRenderer");
            SDL_DestroyWindow(window);
            SDL_GL_DeleteContext(context);
            SDL_Quit();
            exit(1);
        }
        else
        {
            cout << "\n\n\tCreated renderer.\n";
        }
        SDL_GL_MakeCurrent(window, context);
        glewExperimental=true;
        GLenum err=glewInit();
        if(err!=GLEW_OK)
        {
            //Problem: glewInit failed, something is seriously wrong.
            cout<<"\n\n\tglewInit failed, aborting."<<endl;
            exit(1);
        }
        else
        {
            cout << "\n\n\tInitialized glew.\n";
        }
        glEnable(GL_DEPTH_TEST);  
        glDepthFunc(GL_LESS);
        glDepthRange(0.1f, 1000.0f);
        skybox = new SkyBox();
        skybox->setScale(1000.0f);
        skybox->initSkyBox();
        exploder = new ExplodeIt();
        cout << "\n\n\tShader smokecloud.bin created.\n\n";
    }
    catch(exception exc)
    {
        cout << "\n\n\tProgram Initialization Error:  " << exc.what() << "\n\n";
    }
    interval = EXP_GAP;
    timebegin = chrono::system_clock::now();
    // render loop
    // -----------
    while (!quit)
    {
        if (start)
        {
            timebegin = chrono::system_clock::now();
            start = false;
        }
        if (debug1)
        {
            cout << "\n\n\tProcessing interval:  " << interval << ".\n\n";
        }
        timeend = chrono::system_clock::now();
        interval = (float) chrono::duration_cast<chrono::milliseconds>(timeend -
        timebegin).count();
        // render
        // ------
        intbegin = chrono::system_clock::now();
        model = mat4(1.0f);
        viewPos = camera->getPosition();
        projection = camera->getPerspective();
        view = camera->getViewMatrix();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepthf(1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, width, height);
        skybox->drawSkyBox(model, view, projection);
        exploder->drawIt(model, view, projection, viewPos, running);
        intend = chrono::system_clock::now();
        while (SDL_PollEvent(&e))
        {
            keyDown(e);
            mouseMove(e);
            windowEvent(e);
        };
        if (debug1)
        {
            cout << "\n\tSwapping window.";
        }
        SDL_GL_SwapWindow(window);
    }
    //! ------------------------------------------------------------------
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

//! ---------------------------------------------------------------------------------------------------------
// process all input: query SDL2 whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void SlickExplosion::keyDown(SDL_Event e)
{
    int delta = (int)
    //! Use timing to create a cameraSpeed variable.
    chrono::duration_cast<chrono::nanoseconds>(intend -
    intbegin).count();
    float deltaTime = (float)delta / 1000000.0f;
    float cameraSpeed = 0.5f * deltaTime;
    //! Motion keys.
    //! Forward motion.
    if (e.type == SDL_KEYDOWN) 
    {
        cout << "\n\n\tIn keyDown:  " << SDL_GetKeyName(e.key.keysym.sym) << "\n\n";
        switch (e.key.keysym.sym)
        {
            case SDLK_w:
                camera->processKeyboard(Camera::Camera_Movement::FORWARD, cameraSpeed);
                break;
            //! Backwards motion.
            case SDLK_s:
                camera->processKeyboard(Camera::Camera_Movement::BACKWARD, cameraSpeed);
                break;
            //! Move left.
            case SDLK_a:
                camera->processKeyboard(Camera::Camera_Movement::LEFT, cameraSpeed);
                break;
            //! Move right.
            case SDLK_d:
                camera->processKeyboard(Camera::Camera_Movement::RIGHT, cameraSpeed);
                break;
            //! Move up.
            case SDLK_r:
                camera->processKeyboard(Camera::Camera_Movement::UP, cameraSpeed);
                break;
            //! Move down.
            case SDLK_f:
                camera->processKeyboard(Camera::Camera_Movement::DOWN, cameraSpeed);
                break;
            //! Reset the camera.
            case SDLK_z:
                camera->resetCamera();
                break;
            //! Reverse the camera.
            case SDLK_x:
                camera->reverseDirection();
                break;
            //! Zoom keys.
            //! Zoom in.
            case SDLK_UP:
                camera->processMouseScroll(Camera::Camera_Movement::CLOSER);
                break;
            //! Zoom out.
            case SDLK_DOWN:
                camera->processMouseScroll(Camera::Camera_Movement::AWAY);
                break;
            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_SPACE:
                start = true;
                running = !running;
                break;
           case SDLK_RALT:
                altSet = true;
                break;
            case SDLK_LALT:
                altSet = true;
                break;
            case SDLK_RETURN:
                if (altSet)
                {
                    cout << "\n\n\tSet window fullscreen.\n\n";
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    altSet = false;
                }
                break;
        }
    }
}    

void SlickExplosion::windowEvent(SDL_Event e)
{
    if (e.type == SDL_WINDOWEVENT) {
        switch (e.window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            cout << "\n\n\tWindow " << e.window.windowID << " shown.\n\n";
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            cout << "\n\n\tWindow " << e.window.windowID << " hidden.\n\n";
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            cout << "\n\n\tWindow " << e.window.windowID << " exposed.\n\n";
            break;
        case SDL_WINDOWEVENT_MOVED:
            cout << "\n\n\tWindow " << e.window.windowID << " moved to " 
            << e.window.data1 << ", " << e.window.data2 << "\n\n";
            break;
        case SDL_WINDOWEVENT_RESIZED:
            cout << "\n\n\tWindow " << e.window.windowID << " resized to " 
            << e.window.data1 << ", " << e.window.data2 << "\n\n";
            width = (unsigned  int)e.window.data1;
            height = (unsigned  int)e.window.data2;
            glViewport(0, 0, e.window.data1, e.window.data2);
            camera->resizeView(e.window.data1, e.window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            cout << "\n\n\tWindow " << e.window.windowID << " size changed to " 
            << e.window.data1 << ", " << e.window.data2 << "\n\n";
            width = (unsigned  int)e.window.data1;
            height = (unsigned  int)e.window.data2;
            glViewport(0, 0, e.window.data1, e.window.data2);
            camera->resizeView(e.window.data1, e.window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            cout << "\n\n\tWindow " << e.window.windowID << " minimized.\n\n";
            width = (unsigned  int)0;
            height = (unsigned  int)0;
            glViewport(0, 0, 0, 0);
            camera->resizeView(0, 0);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            cout << "\n\n\tWindow " << e.window.windowID << " maximized.\n\n";
            width = (unsigned int)e.window.data1;
            height = (unsigned int)e.window.data2;
            SDL_SetWindowSize(window, width, height);
            glViewport(0, 0, width, height);
            camera->resizeView(width, height);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            cout << "\n\n\tWindow " << e.window.windowID << " restored.\n\n";
            break;
        case SDL_WINDOWEVENT_ENTER:
            cout << "\n\n\tMouse entered window " << e.window.windowID << ".\n\n";
            break;
        case SDL_WINDOWEVENT_LEAVE:
            cout << "\n\n\tMouse left window " << e.window.windowID << ".\n\n";
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            cout << "\n\n\tWindow " << e.window.windowID << " gained keyboard focus.\n\n";
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            cout << "\n\n\tWindow " << e.window.windowID << " lost keyboard focus.\n\n";
            break;
        case SDL_WINDOWEVENT_CLOSE:
            cout << "\n\n\tWindow " << e.window.windowID << " closed.\n\n";
            quit = true;
            break;
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            cout << "\n\n\tWindow " << e.window.windowID << " is offered focus.\n\n";
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            cout << "\n\n\tWindow " << e.window.windowID << " has a special hit test.\n\n";
            break;
        default:
            cout << "\n\n\tWindow " << e.window.windowID << " received an unknown event.\n\n";
            break;
        }
    }
}

void SlickExplosion::mouseMove(SDL_Event e)
{
    if (e.type == SDL_MOUSEWHEEL)
    {
            if(e.wheel.y > 0)
            {
                camera->processMouseScroll(Camera::Camera_Movement::CLOSER);
            }
            else if (e.wheel.y < 0)
            {
                camera->processMouseScroll(Camera::Camera_Movement::AWAY);
            }
    }
    else if( e.type == SDL_MOUSEMOTION)
    {
        camera->processMouseMovement(e.motion.xrel, e.motion.yrel);
    }
    
}    


void SlickExplosion::logSDLError(ostream &os, const string &msg)
{
    os << "\n\n\t" << msg << " error: " << SDL_GetError() << "\n\n";
}


