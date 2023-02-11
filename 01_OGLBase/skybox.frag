#version 330 core

// pipeline-ból bejövõ per-fragment attribútumok
in vec3 vs_out_pos;

out vec4 fs_out_col;

uniform samplerCube skyboxTexture;
uniform samplerCube skybox2Texture;

uniform float t;
uniform bool w = false;
uniform bool l = false;

void main()
{
	//fs_out_col = vec4( normalize(vs_out_pos), 1);
	//fs_out_col = texture( skyboxTexture, (vs_out_pos) );

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
		vec4 sky1 = texture(skyboxTexture, vs_out_pos);
		vec4 sky2 = texture(skybox2Texture, vs_out_pos);

		vec4 mixedSky = mix(sky1, sky2, t);

		fs_out_col = mixedSky;
	}
}