#version 120
varying vec3 position;
varying vec3 normal;
uniform sampler2D diffuseSampler;
varying vec2 v_texCoord;
uniform sampler2D tex0;
varying vec2 texture_coordinate; uniform sampler2D my_color_texture;
 

uniform vec4 val;
 
void main()
{
		gl_FragColor = texture2D(my_color_texture, texture_coordinate) * val;
		
}
