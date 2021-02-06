// *******************************
// * (c) Shem Taylor 2013 - 2021 *
// * All right reserved          *
// * Company Dodgee Software     *
// *******************************

#version 130

// Global Matrices
uniform mat4 WorldViewProjection;
uniform mat4 WorldViewInverseTranspose;
uniform mat4 WorldViewInverse;
uniform mat4 WorldView;
uniform vec4 CameraPosition;

void main()
{
    gl_FragColor = vec4(1.0,1.0,0.0,1.0);
}
