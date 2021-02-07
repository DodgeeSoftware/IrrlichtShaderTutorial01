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

// VARYING VARIABLES (Communication from the VertexShader)
// -------------------------------------------------------
varying vec4 Position;
varying vec3 Normal;
varying vec4 Color;
varying mat4 m;

// ATTRIBUTES
// ----------


// PIXEL SHADER MAIN
// -----------------

void main()
{
    // Compute the vector from the vertex to the eye position
    vec3 toEye = normalize(CameraPosition - Position.xyz);

    // Sum of the effect of all lights on the surface
    vec3 totalLighting = vec3(0.0, 0.0, 0.0);
    vec3 totalDiffuseLighting = vec3(0.0, 0.0, 0.0);
    vec3 totalSpecularLighting = vec3(0.0, 0.0, 0.0);

    // DO DIRECTIONAL LIGHTS
    for (int i = 0; i < DirectionalLightCount; i++)
    {
        vec3 lightDirection = vec3(DirectionalLightDirection[3 * i + 0], DirectionalLightDirection[3 * i + 1], DirectionalLightDirection[3 * i + 2]);
        lightDirection = normalize(lightDirection);

        // Calculate diffuse co-efficient
        float s = max(dot(lightDirection, Normal), 0.0);

        // Compute the reflection Vector
        vec3 reflectionVec = normalize(reflect(-lightDirection, Normal));
        // Determine how much (if any) specular light makes it to the eye
        float t = pow(max(dot(reflectionVec, toEye), 0.0), SpecularPower);

        // Calculate Lighting components
        vec3 diffuse = s * (DiffuseMaterialColor * vec4(DirectionalLightColor[3 * i + 0], DirectionalLightColor[3 * i + 1], DirectionalLightColor[3 * i + 2], DirectionalLightColor[3 * i + 3])).rgb;
        vec3 specular = t * (SpecularMaterialColor * vec4(DirectionalLightColor[3 * i + 0], DirectionalLightColor[3 * i + 1], DirectionalLightColor[3 * i + 2], DirectionalLightColor[3 * i + 3])).rgb;

        totalDiffuseLighting = totalDiffuseLighting + diffuse;
        totalDiffuseLighting = clamp(totalDiffuseLighting, 0.0, 1.0);
        totalSpecularLighting = totalSpecularLighting + specular;
        totalSpecularLighting = clamp(totalSpecularLighting, 0.0, 1.0);
    }

    // DO POINT LIGHTS
    for (int i = 0; i < PointLightCount; i++)
    {
        // Grab the light position
        vec3 lightPosition = vec3(PointLightPosition[3 * i + 0], PointLightPosition[3 * i + 1], PointLightPosition[3 * i + 2]);

        // Find the normalised vector between the vetex and the light source
        vec3 lightVec = normalize(lightPosition - Position.xyz);
        lightVec = normalize(lightVec);

        vec3 reflectVec = reflect(-lightVec, Normal);
        reflectVec = normalize(reflectVec);

        // Grab the distance between the light and the surface
        float distanceToLightSource = length(lightPosition - Position.xyz);

        // Compute the diffuse term
        float s = max(dot(Normal, lightVec), 0.0);
        // Compute the specular term
        float t = pow(max(dot(reflectVec, toEye), 0.0), SpecularPower);

        // Calculate Lighting components
        vec3 diffuse = s * (DiffuseMaterialColor * vec4(PointLightDiffuseColor[3 * i + 0], PointLightDiffuseColor[3 * i + 1], PointLightDiffuseColor[3 * i + 2], 1.0)).rgb;
        vec3 specular = t * (SpecularMaterialColor * vec4(PointLightDiffuseColor[3 * i + 0], PointLightDiffuseColor[3 * i + 1], PointLightDiffuseColor[3 * i + 2], 1.0)).rgb;

        //specular = vec3(1.0, 0.0 ,0.0);

        // Calcular Attenuation
        float attenuation = (1.0 / (PointLightAttenuation[i * 3 + 0] + PointLightAttenuation[i * 3 + 1] * distanceToLightSource + PointLightAttenuation[i * 3 + 2] * distanceToLightSource * distanceToLightSource));

        totalDiffuseLighting = totalDiffuseLighting + (diffuse) * attenuation;
        totalDiffuseLighting = clamp(totalDiffuseLighting, 0.0, 1.0);
        totalSpecularLighting = totalSpecularLighting + specular * attenuation;
        totalSpecularLighting = clamp(totalSpecularLighting, 0.0, 1.0);
    }

    // DO SPOT LIGHTS
    for (int i = 0; i < SpotLightCount; i++)
    {
        // Grab the light position
        vec3 lightPosition = vec3(SpotLightPosition[3 * i + 0], SpotLightPosition[3 * i + 1], SpotLightPosition[3 * i + 2]);
        // Find the normalised vector between the vetex and the light source
        vec3 lightVec = normalize(lightPosition - Position.xyz);

        // Grab the light direction
        vec3 lightDirection = normalize(vec3(SpotLightDirection[3 * i + 0], SpotLightDirection[3 * i + 1], SpotLightDirection[3 * i + 2]));

        // Grab the distance between the light and the surface
        float distanceToLightSource = length(lightVec);

        // Is the spot lighting hitting this fragment
        if (dot(lightVec, -lightDirection) >= (cos(SpotLightInnerCone[i])))
        {
            float intensity = 0.0;
            float a = cos(SpotLightInnerCone[i]);
            float d = dot(lightVec, -lightDirection);
            if (a < d)
             intensity = 1.0 - pow(clamp(a / d, 0, 1), 2.0);

            // Grab the distance between the light and the surface
            float distanceToLightSource = length(lightPosition - Position.xyz);

            // Compute the vertex colour
            float s = max(dot(Normal, lightVec), 0.0);

            // Compute the reflection Vector
            vec3 reflectionVec = normalize(reflect(-lightVec, Normal));

            // Determine how much (if any) specular light makes it to the eye
            float t = pow(max(dot(reflectionVec, toEye), 0.0), SpecularPower);

            // Calculate Lighting components
            vec3 diffuse = s * (DiffuseMaterialColor * vec4(SpotLightDiffuseColor[3 * i + 0], SpotLightDiffuseColor[3 * i + 1], SpotLightDiffuseColor[4 * i + 3], 1.0)).rgb;
            vec3 specular = t * (SpecularMaterialColor * vec4(SpotLightDiffuseColor[3 * i + 0], SpotLightDiffuseColor[3 * i + 1], SpotLightDiffuseColor[4 * i + 3], 1.0)).rgb;

            // Calcular Attenuation
            float attenuation = (1.0 / (SpotLightAttenuation[i * 3 + 0] + SpotLightAttenuation[i * 3 + 1] * distanceToLightSource + SpotLightAttenuation[i * 3 + 2] * distanceToLightSource * distanceToLightSource));

            // Add lighting to the surface
            totalDiffuseLighting = totalDiffuseLighting + diffuse * attenuation * intensity;
            totalDiffuseLighting = clamp(totalDiffuseLighting, 0.0, 1.0);
            totalSpecularLighting = totalSpecularLighting + specular * attenuation;
            totalSpecularLighting = clamp(totalSpecularLighting, 0.0, 1.0);
        }
    }
    if (Texture0InUse == 1.0)
    {
        if (texture2D(Texture0, gl_TexCoord[0].st).a == 0.0)
            discard;
        vec4 finalColor = (DiffuseMaterialColor * texture2D(Texture0, gl_TexCoord[0].st)) * vec4(AmbientLight.rgb + totalDiffuseLighting.rgb + totalSpecularLighting.rgb, 1.0);
        finalColor.a = texture2D(Texture0, gl_TexCoord[0].st).a;
        gl_FragColor = finalColor;
    }
    else
    {
        vec4 finalColor = (DiffuseMaterialColor) * vec4(AmbientLight.rgb + totalDiffuseLighting.rgb + totalSpecularLighting.rgb, 1.0);
        finalColor.a = texture2D(Texture0, gl_TexCoord[0].st).a;
        gl_FragColor = finalColor;
    }
}
