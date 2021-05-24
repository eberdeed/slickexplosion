/**********************************************************
 *   SlickExplosion:  A class to encapsulate creating an 
 *   OpenGL explosion with sound using SDL2.
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   03/2020 San Diego, California USA
 * ********************************************************/

#ifndef SLICKEXPLOSION_H
#define SLICKEXPLOSION_H

#include "commonheader.h"
#include "../assimpopengl/include/shader.h"
#include "../assimpopengl/include/camera.h"
#include "skybox.h"
#include "explodeit.h"

/** \class SlickExplosion Displays an OpenGL explosion with 
 *  sound using SDL2.  The amount of particles per display and the 
 *  timing of the explosion can be adjusted from the 
 *  commonheader.h file's defines.  The viewport size of the 
 *  screen in pixels can be adjusted in this file.  
 */
class SlickExplosion
{
public:
    /** \brief The constructor is where the initialization occurs
     *  and the execution loop is called, making the class 
     *  self-contained.
     */
    SlickExplosion();
    /** \brief The destructor is where the pointers for
     *  the camera class is deleted.
     */
    ~SlickExplosion();
    /** \brief The execution loop where the ongoing drawing
     *  of the display occurs.
     */
    void execLoop();
    /** \brief framebufferSize uses glViewport 
     *  to adjust the size of the window.
     */
    void framebufferSize(int width, int height);
    /** \brief keyDown handles key events.
     */
    void keyDown(SDL_Event e);
    /** \brief windowEvent handles window resizing,
     *  closing, minimization and maximization.
     */
	void windowEvent(SDL_Event e);
    /** \brief mouseMove handles changes in the
     *  mouse pointer coordinates.
     */
	void mouseMove(SDL_Event e);
    /** \brief logSDLError takes an output stream and
     *  a message and passes the message through the
     *  provided output stream.
     */
    void logSDLError(ostream &os, const string &msg);
    /* Varianbles */
    //! Screen dimensions.
    const unsigned int SCR_WIDTH = 1000;
    const unsigned int SCR_HEIGHT = 900;
    unsigned int width, height;
    //! 180 degrees in radians.
    const float pi180 = acos(-1.0f);
    /** \brief SDL2 variables for window display.
     */
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext context;
    //! The object and debris.
    ExplodeIt *exploder;
    //! The sky box.
    SkyBox *skybox;
    /** \brief Camera permits the user to view the scene
     *  by providing location and orientation values
     *  that are keyboard and mouse driven.
     */
    Camera *camera;
    //! Transform matrices.
    mat4 model, view, projection;
    //! Camera location.
    vec3 viewPos;
    //! Mouse movement variables.
    float lastX, lastY, xpos, ypos;
    bool firstMouse = true;
    //! The time points used for display and mouse timing.
    chrono::system_clock::time_point timebegin, timeend, intend, intbegin;
    //! Time counter.
    float interval;
    //! Shader locations (after "make install").
    string vertexShader = "/usr/share/openglresources/shaders/vertex1.glsl";
    string fragmentShader = "/usr/share/openglresources/shaders/fragment.glsl";
    //! Various boolean flags.
    bool debug1 = false, quit = false, altSet = false, 
    start = false, running = false;
};
    
#endif // SLICKEXPLOSION_H
/** \breif The main.  
 *  I keep the main as simple as possible.
 */
int main(int argc, char **argv)
{
    SlickExplosion squeaky;
    return 0;
}
