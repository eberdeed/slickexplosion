/*******************************************************************
 * CommonHeader:  A header file to reduce repetition of #define
 * and #include statements.
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * April 2020 San Diego, California USA
****************************************************************/
#ifndef COMMONHEADER_H
#define COMMONHEADER_H
/** \class CommonHeader A header file to hold all the includes, defines and
 *  structs the program uses.
 */
#define EXP_GAP 2000
//! GLEW The OpenGL library manager
#define GLEW_STATIC
#include <glew.h>
//! GLM The OpenGL math library
#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/quaternion.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/matrix_interpolation.hpp>
#include <gtc/matrix_access.hpp> 
#include <gtx/euler_angles.hpp>
//! SDL2
#include <SDL.h>
//! CPP Library
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <sstream>
#include <chrono>
#include <vector>
#include <thread>
#include <cmath>
//! Boost
#include <filesystem.hpp>
//! System
#include <pthread.h>
// Free Image Plus
#include <FreeImagePlus.h>

using namespace std;
using namespace glm;
using namespace boost::filesystem;

//! The structures.
//! Define a Partilcle.
struct ParticleData {
    float phi1;
    float rho1;
    float radius1;
    float lifetime;
};

#endif // COMMONHEADER_H
