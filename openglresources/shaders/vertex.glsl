/*********************************************************
*   vertex.glsl:  A vertex shader for a fireworks display.
*   Created by:  Edward C. Eberle <eberdeed@eberdeed.net>
*   March 2020 San Diego, California USA
*   Copyright Maureen Ann Quinn March 2020
**********************************************************/
#version 300 es
precision highp float;

//! Everything is a vec4 to ensure data integrity.
layout(location = 0) in vec4 a_startPosition;
layout(location = 1) in vec4 a_endPosition;
layout(location = 2) in vec4 a_lifetime;

/** The only thing passed out is the current
  * position in time travelling from 1 -> 0.
  */
out float v_lifetime;

//! Current time (from zero).
uniform float u_time;
//! Center of the current explosion.
uniform vec4 u_centerPosition;
//! Camera view matrix.
uniform mat4 view;
//! Projection of view.
uniform mat4 projection;
//! Scale of the explosion.
uniform mat4 scaler;

float timeval;
vec4 tmpPos;

void main()
{
  //! Check to see if the explosion is still happening.
  if (u_time <= a_lifetime.x)
  {
        //! Create a ratio so the time goes from zero to one.
        timeval = (u_time / a_lifetime.x);
        //!  Create a timeline that goes from one to zero.
        v_lifetime = 1.0 - timeval;
        //! Square that value.
        v_lifetime *= v_lifetime;
        //! Clamp it between 0 and 1.
        v_lifetime = clamp ( v_lifetime, 0.0, 1.0 );
        /** Make the point size vary inversly according to
          * the square of the time.
          */
        gl_PointSize = ( v_lifetime * v_lifetime ) * 40.0;
        //! Make the particle slide from the start to the end.
        tmpPos = ((1.0 - timeval) * a_startPosition) + (timeval * a_endPosition);
        //! Move it to the center of the explosion.
        tmpPos += u_centerPosition;
        //! Set the size adjustment to 1.
        tmpPos.w = 1.0;
        //! Apply the projection, view and scale matrices.
        gl_Position = projection * view * scaler * tmpPos;
    }
    else
    {
        //! Otherwise dump it in the corner.
        gl_Position = vec4( -1000.0, -1000.0, -1000.0, 0.0 );
    }
}
