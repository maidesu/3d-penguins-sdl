#version 330 core

in vec3 vs_out_pos;
out vec4 fs_out_col;

uniform bool c;
uniform bool w = false;
uniform bool l = false;

void main()
{
	if (w)
	{
		fs_out_col = vec4(1, 1, 1, 1);
	}
	else if (l)
	{
		fs_out_col = vec4(0, 0, 0, 1);
	}
	else
	{

	fs_out_col = c ? vec4(1,0,0,1) : vec4(0,1,0,1);

	}
}