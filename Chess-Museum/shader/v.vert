# version 460

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec2 TexCoord;

uniform vec4 lightPos;
uniform mat4 gl_ModelViewProjectionMatrix;
uniform mat4 gl_ModelViewMatrix;
uniform mat3 gl_NormalMatrix;

out vec3 normal;
out vec3 lightVec;
out vec3 viewVec;
out vec2 tex;

void main(){ 
	gl_Position = gl_ModelViewProjectionMatrix * Position;
	vec4 vert = gl_ModelViewMatrix * Position;

	normal   = gl_NormalMatrix * vec3(Normal);
	lightVec = vec3(lightPos - vert);
	viewVec  = -vec3(vert);
	tex = TexCoord;
}