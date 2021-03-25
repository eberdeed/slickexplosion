/**********************************************************
 *   SmokeCloud:  A class to encapsulate a spinning gaseous
 *   cloud.
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   03/2021 San Diego, California USA
 * ********************************************************/

#ifndef SMOKECLOUD_H
#define SMOKECLOUD_H

//! The defines.
#define NUM_PARTICLES 10000
#define SCALE 10

#include "commonheader.h"
#include "shader.h"

/** \class SmokeCloud Display a swirling gaseous cloud of particles.
 */
class SmokeCloud
{
public:
    //! Define a Partilcle.
    struct ParticleData {
        float phi1;
        float rho1;
        float radius1;
        float lifetime;
    };
    
    /** \brief Echo the creation of the class and initialize
     *  and define the particles.
     */
    SmokeCloud(Shader *shader);

    /** \brief Echo the destruction of the class and delete
     *  the OpenGL buffers.
     * 
     */
    ~SmokeCloud();

    /** \brief initFire defines the particles and their paths
     *  while also providing the lifespan of each particle.
     */
    void initFire();
    /** \brief Draw a cloud of smoke.
     */
    void drawCloud(mat4 model, mat4 view, mat4 projection, 
    float timeVal, bool start);
    /** \brief defineObjects defines the OpenGL 
     *  buffer used to draw the fireworks.
     */
    void defineObjects();
    /** \brief debug provides the particle information.
     *  When debug1 is set to true oodles of debug 
     *  information are provided.
     */
    void debug();
    
    /* Variables */
    //! 180 degrees in radians.
    const float pi180 = acos(-1.0f);
    //! The size of the cloud.
    mat4 scaler;
    //! Cloud color.
    vec4 color;
    //! The shader program.
    Shader *shader;
    //! The time point to seed the random number generator.
    chrono::system_clock::time_point tdata;
    //! Define a random float generator. 
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 generator; //Standard mersenne_twister_engine seeded with rd()    
    uniform_real_distribution<float>randomFloats; // generates random floats between 0.0 and 1.0    
    //! The array containing the particle data.
    ParticleData particles[NUM_PARTICLES];
    //! The OpenGL buffer and vertex array handles.
    GLuint VAO = 0, VBO = 0;
    //! The debug flag.
    bool debug1 = false;

};

#endif // SMOKECLOUD_H
