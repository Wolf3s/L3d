
// ===============================================================================================================
// -*- C++ -*-
//
// Shaders.hpp - Inline GLSL shaders used by the L3D app.
//
// Copyright (c) 2012 Guilherme R. Lampert
// guilherme.ronaldo.lampert@gmail.com
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// above is included in the resulting source code.
//
// ===============================================================================================================

static const char defaultVertShader[] = "\
uniform mat4 MVPMatrix; \n \
uniform mat4 normalMatrix; \n \
uniform vec4 lightPosition; \n \
\n \
attribute vec4 inPosition; \n \
attribute vec3 inNormal; \n \
attribute vec2 inTextCoord; \n \
\n \
varying vec2 texCoord; \n \
varying vec3 eyespaceNormal; \n \
varying vec3 lightDir; \n \
varying vec3 eyeVec; \n \
 \n \
void main() \n \
{ \n \
	texCoord = inTextCoord; // Pass on unchanged to the next stage. \n \
\n \
	eyespaceNormal = vec3(normalMatrix * vec4(inNormal, 1.0)); \n \
\n \
	vec4 transformedVertexPosition = (MVPMatrix * inPosition); \n \
\n \
	lightDir = (lightPosition.xyz - transformedVertexPosition.xyz); \n \
\n \
	eyeVec = -transformedVertexPosition.xyz; \n \
\n \
	gl_Position = transformedVertexPosition; \n \
}\n";

static const char defaultFragShader[] = "\
uniform sampler2D texture; \n \
uniform vec4 ambientLight; \n \
uniform vec4 diffuseLight; \n \
uniform vec4 specularLight; \n \
uniform vec4 objectColor; \n \
uniform float shininess; \n \
\n \
varying vec2 texCoord; \n \
varying vec3 eyespaceNormal; \n \
varying vec3 lightDir; \n \
varying vec3 eyeVec; \n \
\n \
void main() \n \
{ \n \
	vec3 N = normalize(eyespaceNormal); \n \
	vec3 E = normalize(eyeVec); \n \
	vec3 L = normalize(lightDir); \n \
	vec3 reflectV = reflect(-L, N); \n \
\n \
	// Change this if no texture is applied: \n \
	// vec4 ambientTerm = ambientLight * lightColor; \n \
\n \
	vec4 ambientTerm = texture2D(texture, texCoord); \n \
	vec4 diffuseTerm = diffuseLight * max(dot(N, L), 0.0); \n \
	vec4 specularTerm = specularLight * pow(max(dot(reflectV, E), 0.0), shininess); \n \
\n \
	gl_FragColor = objectColor * (ambientTerm + diffuseTerm + specularTerm); \n \
}\n";

// ===============================================================================================================

static const char colorOnlyVertShader[] = "\
attribute vec4 inPosition; \n \
\n \
varying vec4 color; \n \
\n \
uniform vec4 objectColor; \n \
uniform mat4 modelView; \n \
uniform mat4 projection; \n \
\n \
void main() \n \
{ \n \
	color = objectColor; \n \
	gl_Position = projection * modelView * inPosition; \n \
}\n";

static const char colorOnlyFragShader[] = "\
varying vec4 color; \n \
\n \
void main() \n \
{ \n \
	gl_FragColor = color; \n \
}\n";
