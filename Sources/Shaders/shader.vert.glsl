#version 450

// in
in vec3 pos;
in vec4 col;

// out
out vec4 fCol;

// mvp
uniform mat4 projectionMatrix;

void main() {
	gl_Position = projectionMatrix * vec4(pos, 1.0);
	fCol = col;
}