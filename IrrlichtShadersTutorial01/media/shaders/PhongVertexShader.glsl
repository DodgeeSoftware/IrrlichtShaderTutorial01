// *******************************
// * (c) Shem Taylor 2013 - 2021 *
// * All right reserved          *
// * Company Dodgee Software     *
// *******************************

#version 130

// DATA STRUCTURES
// ---------------



// UNIFORM VARIABLES (From C++)
// ----------------------------

// Screen Width and Height
uniform float ScreenWidth;
uniform float ScreenHeight;

// Global Matrices
uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldMatrix;
uniform mat4 InverseWorldMatrix;
uniform mat4 ViewMatrix;
uniform mat4 InverseViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 InverseProjectionMatrix;
uniform mat4 NormalMatrix;

// Time
uniform float Time;

// Camera
uniform vec3 CameraPosition; // Position of the Camera in WorldSpace
uniform vec3 CameraTarget; // Normalised Vector for Camera Direction

// Irrlicht Material
uniform bool LightingEnabled;
uniform float SpecularPower; // Specular Co-Efficient of the material
uniform vec4 AmbientMaterialColor; // Ambient Color of the material
uniform vec4 DiffuseMaterialColor; // Diffuse Color of the material
uniform vec4 SpecularMaterialColor; // Specular Color of the material
uniform vec4 EmmissiveMaterialColor; // Emmissive Color of the material

// Irrlicht Textures and Texture Matrices
uniform float Texture0InUse;
uniform sampler2D Texture0;
uniform mat4 Texture0Matrix;
uniform float Texture1InUse;
uniform sampler2D Texture1;
uniform mat4 Texture1Matrix;
uniform float Texture2InUse;
uniform sampler2D Texture2;
uniform mat4 Texture2Matrix;
uniform float Texture3InUse;
uniform sampler2D Texture3;
uniform mat4 Texture3Matrix;
//uniform float Texture4InUse;
//uniform sampler2D Texture4;
//uniform mat4 Texture4Matrix;
//uniform float Texture5InUse;
//uniform sampler2D Texture5;
//uniform mat4 Texture5Matrix;
//uniform float Texture6InUse;
//uniform sampler2D Texture6;
//uniform mat4 Texture6Matrix;
//uniform float Texture7InUse;
//uniform sampler2D Texture7;
//uniform mat4 Texture7Matrix;

// Lighting
uniform vec4 AmbientLight;
uniform vec4 ShadowColor;

uniform int DirectionalLightCount;
uniform float DirectionalLightDirection[3 * 1];
uniform float DirectionalLightColor[3 * 1];

uniform int PointLightCount;
uniform float PointLightPosition[25 * 3];
//uniform float PointLightAmbientColor[25 * 3];
uniform float PointLightDiffuseColor[25 * 3];
//uniform float PointLightSpecularColor[25 * 3];
uniform float PointLightAttenuation[25 * 3];

uniform int SpotLightCount;
uniform float SpotLightPosition[25 * 3];
uniform float SpotLightDirection[25 * 3];
//uniform float SpotLightAmbientColor[25 * 3];
uniform float SpotLightDiffuseColor[25 * 3];
//uniform float SpotLightSpecularColor[25 * 3];
uniform float SpotLightAttenuation[25 * 3];
uniform float SpotLightInnerCone[25];
uniform float SpotLightOuterCone[25];
uniform float SpotLightFalloff[25];

// VARYING VARIABLES (Communication from to the Pixel Shader)
// ----------------------------------------------------------
varying vec4 Position;
varying vec3 Normal;
varying vec4 Color;
varying mat4 m;

// ATTRIBUTES
// ----------



// VERTEX SHADER MAIN
// ------------------

void main()
{
    // Apply Texture Matrices to Texture Co-ordinates (TODO: use the irrlicht texture matrices instead)
    gl_TexCoord[0]  = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_TexCoord[1]  = gl_TextureMatrix[1] * gl_MultiTexCoord1;
    gl_TexCoord[2]  = gl_TextureMatrix[2] * gl_MultiTexCoord2;
    gl_TexCoord[3]  = gl_TextureMatrix[3] * gl_MultiTexCoord3;

    /* Transform the vertex
        gl_Position is converted into screen space by
        multiplying it by the WorldViewProjection Matrix */
    gl_Position = WorldViewProjectionMatrix * gl_Vertex;

    /* gl_Vertex is a point in the model which has
        been transformed locally. That is positioned about
        the point (0,0). We want calculate the position in
        world space and pass that into our fragment shader
        through a varying declaration in the vertex and
        fragment shader */
    Position = WorldMatrix * gl_Vertex;

    /* Compute the vertex Normal
        the normal matrix here is special. The matrix should rotate
        but never translate and never scale. */
    Normal = (NormalMatrix * vec4(gl_Normal, 1.0)).xyz;
    Normal = normalize(Normal);
}

