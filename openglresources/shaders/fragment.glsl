/*********************************************************
*   fragment.glsl:  A fragment shader for a fireworks display.
*   Created by:  Edward C. Eberle <eberdeed@eberdeed.net>
*   March 2020 San Diego, California USA
*   Copyright Maureen Ann Quinn March 2020
**********************************************************/
#version 300 es
precision highp float;

uniform vec4 u_color;

in float v_lifetime;

out vec4 fragColor;

void main()
{
    //! Get the color.
    fragColor = u_color;
    //! Allow it to fade over time.
    fragColor.a *= v_lifetime;
}
