#version 120
varying vec3 position;
varying vec3 normal;
uniform sampler2D diffuseSampler;
varying vec2 v_texCoord;
uniform sampler2D tex0;
varying vec2 texture_coordinate; uniform sampler2D my_color_texture;
 
 
uniform vec3 lightPos;
 
uniform vec3 mambient;  //gl_FrontMaterial
uniform vec3 mdiffuse;
uniform vec3 mspecular;
uniform float shininess;
 
uniform vec3 lambient;  //gl_LightSource[0]
uniform vec3 ldiffuse;
uniform vec3 lspecular;
 
 
void main()
{

        float dist=length(lightPos-position);   //distance from light-source to surface
        float att=1.0;    //attenuation (constant,linear,quadric)
        vec3 ambient=mambient*lambient; //the ambient light
       
        vec3 surf2light=normalize(lightPos-position);
        vec3 norm=normalize(normal);
        float dcont=max(0.0,dot(norm,surf2light));
        vec3 diffuse=dcont*(mdiffuse*ldiffuse);
       
        vec3 surf2view=normalize(-position);
        vec3 reflection=reflect(-surf2light,norm);
       
        float scont=pow(max(0.0,dot(surf2view,reflection)),shininess);
        vec3 specular=scont*lspecular*mspecular;
       
	   

        //gl_FragColor=vec4((ambient+diffuse+specular)*att,1.0);  //<- don't forget the paranthesis (ambient+diffuse+specular)
		//gl_FragColor = texture2D(tex, vec2(0.5,0.5));
		gl_FragColor = texture2D(my_color_texture, texture_coordinate) * vec4((ambient+diffuse+specular)*att,1.0);
		
}
