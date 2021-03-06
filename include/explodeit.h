/**************************************************************
 * ExplodeIt:  A class to encapsulate the creation and use of 
 * a graphics object as an explosion.  
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * March 2021 San Diego, California USA
 ***********************************************************/

#ifndef EXPLODEIT_H
#define EXPLODEIT_H
#include "commonheader.h"
#include <chrono>
#include <random>
#include "../assimpopengl/include/model.h"
#include "../assimpopengl/include/shader.h"
#include "../assimpopengl/include/info.h"
/** \class ExplodeIt A class to encapsulate the display of a 
 *  graphics object and the exploding of that object.
 */
class ExplodeIt
{
public:
    /** \brief Echo the creation of the class and call it's
     *  initialization.
     */
    ExplodeIt();

    /** \brief Echo the destruction of the class and delete 
     *  any pointers.
     */
    ~ExplodeIt();
    
    /** \brief Initialize the object.
     */
    void initObject();
    /** \brief Draw the object and the explosion.
     */
    void drawIt(mat4 model, mat4 view, mat4 projection, vec3 viewPos, bool exploding);
    /** \brief The sound creation function 
     *  that exists on a seperate thread.
     */
    static char *sndMaker();   
    /* Variables */
    //! The object.
    Model *object;
    //! The shaders.
    Shader *shader, *explodeShader, *cloudShader;
    //! Optional lighting.
    vector<PointLight>lights;
    vector<SpotLight>spotLights;
    //! The object definition.
    vector<ModelInfo>objectinfo;
    //! A single object definition.
    ModelInfo item;
    //! The location of the object.
    string objectLoc = "/usr/share/openglresources/objects/ufo5.obj";
    //! The shader program files.
    string objectVertex = "/usr/share/openglresources/shaders/objects.vs";
    string objectFragment = "/usr/share/openglresources/shaders/objects.frag";
    string explodeVertex = "/usr/share/openglresources/shaders/explode.vs";
    string explodeFragment = "/usr/share/openglresources/shaders/explode.frag";
    string cloudVertex = "/usr/share/openglresources/shaders/cloud.vs";
    string cloudFragment = "/usr/share/openglresources/shaders/cloud.frag";
};

#endif // EXPLODEIT_H
