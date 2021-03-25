/*********************************************************
*   vertex.glsl:  A vertex shader for a fireworks display.
*   Created by:  Edward C. Eberle <eberdeed@eberdeed.net>
*   March 2020 San Diego, California USA
*   Copyright Maureen Ann Quinn March 2020
**********************************************************/
#version 300 es
precision highp float;

//! Everything is a vec4 to ensure data integrity.
layout(location = 0) in float phi1;
layout(location = 1) in float rho1;
layout(location = 2) in float radius1;
layout(location = 3) in float a_lifetime;


/** The only thing passed out is the current
  * position in time travelling from 1 -> 0.
  */
out float v_lifetime;

//! Current time (from zero).
uniform float u_time;
//! Cloud location.
uniform mat4 model;
//! Camera view matrix.
uniform mat4 view;
//! Projection of view.
uniform mat4 projection;
//! Scale of the explosion.
uniform mat4 scaler;


float timeval;
vec4 tmpPos;
const float onePi = acos(-1.0) / 180.0;
float x, y, z, r, phi, rho, theta;

float fmod(float num, float div);
void main()
{
  //! Check to see if the explosion is still happening.
  if (u_time <= a_lifetime)
  {
        //! Create a ratio so the time goes from zero to one.
        timeval = (u_time / a_lifetime);
        
        r = radius1 * timeval;
        r = clamp(r, 0.0, 1.0);
        //!  Create a timeline that goes from one to zero.
        v_lifetime = 1.0 - timeval;
        //! Square that value.
        v_lifetime *= v_lifetime;
        //! Clamp it between 0 and 1.
        v_lifetime = clamp ( v_lifetime, 0.0, 1.0 );
        /** Make the point size vary inversly according to
          * the square of the time.
          */
        gl_PointSize = v_lifetime * 500.0;
        //! Make the particle slide from the start to the end.
        theta  = timeval * acos(-1.0) * 2.0;
        theta = fmod(theta, acos(-1.0) * 2.0);
        phi = cos(theta) * acos(-1.0) + phi1;
        rho = sin(theta) * acos(-1.0) + rho1;
        x = r * sin(phi) * cos(rho);
        y = r * sin(phi) * sin(rho);
        z = r * cos(phi);
        tmpPos = vec4(x, y, z, 1.0);
        //! Apply the projection, view and scale matrices.
        gl_Position = model * projection * view * scaler * tmpPos;
    }
    else
    {
        //! Otherwise dump it in the corner.
        gl_Position = vec4( -1000.0, -1000.0, -1000.0, 0.0 );
    }
}

float fmod(float num, float div)
{
    int result = int(num / div);
    return(num - (float(result) * div));
}
