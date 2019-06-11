#shader vertex
#version 330

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex;

out vec2 v_tex;

void main()
{
	gl_Position = position;
	v_tex = tex;
}

#shader fragment
#version 330

in vec2 v_tex;

out vec4 color;
uniform sampler2D u_texture;

void main()
{
	vec4 textColor = texture(u_texture, v_tex);
	color = textColor;
}