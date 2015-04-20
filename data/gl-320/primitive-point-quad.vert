#version 150 core

precision highp float;
precision highp int;
layout(std140, column_major) uniform;

uniform mat4 MV;

in vec4 Position;
in vec4 Color;

out block
{
	vec4 Color;
} Out;

void main()
{
	Out.Color = Color;
	gl_Position = Position;
	gl_PointSize = 512 / -(MV * Position).z;
}
