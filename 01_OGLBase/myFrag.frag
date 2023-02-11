#version 330 core

// pipeline-ból bejövõ per-fragment attribútumok
in vec3 vs_out_pos;
in vec3 vs_out_norm;
in vec2 vs_out_tex;

out vec4 fs_out_col;

// irány fényforrás: fény iránya
uniform vec3 light_dir = vec3(-1,-1,-1);

// fénytulajdonságok: ambiens, diffúz, ...
uniform vec3 La = vec3(0.4, 0.4, 0.4);
uniform vec3 Ld = vec3(0.6, 0.6, 0.6);

uniform sampler2D texImage;
uniform float t;
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

	vec3 ambient = La;

	vec3 normal = normalize(vs_out_norm);
	vec3 to_light = normalize(-light_dir);
	
	float cosa = clamp(dot(normal, to_light), 0, 1);

	vec3 diffuse = cosa*Ld;

	vec4 texColor = texture(texImage, vs_out_tex);
	if (distance(texColor.xyz, vec3(0,1,0)) < 0.001) {
		texColor = mix(vec4(1,0,0,1), vec4(0,0,0,1), t);
	}
	
	fs_out_col = vec4(ambient + diffuse, 1) * texColor;

	}
}