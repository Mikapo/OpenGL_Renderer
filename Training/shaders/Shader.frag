#version 330 core
// Do not use any version older than 330!

#define MAX_LIGHT_AMOUNT 10

in vec4 myvertex;
in vec3 mynormal;

out vec4 fragColor;

uniform int lightamount;
uniform vec4 lightpos [MAX_LIGHT_AMOUNT]; 
uniform vec4 lightcolor [MAX_LIGHT_AMOUNT];  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform float shininess; 

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess) 
{

        float nDotL = dot(normal, direction) ;         
        vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0f);  

        float nDotH = dot(normal, halfvec) ; 
        vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0f), myshininess); 

        vec4 retval = lambert + phong; 
        return retval;            
}       

void main() 
{       
        // They eye is always at (0,0,0) looking down -z axis 
        // Also compute current fragment position and direction to eye 

        const vec3 eyepos = vec3(0,0,0); 
        vec3 mypos = myvertex.xyz / myvertex.w; // Dehomogenize current location 
        vec3 eyedirn = normalize(eyepos - mypos); 

        // Compute normal, needed for shading. 
        vec3 normal = normalize(mynormal); 

   
          // Light 1, point 

        vec4 final_light_color = vec4(0, 0, 0, 1);
        for(int i = 0; i < lightamount; i++)
        {
            vec3 position = lightpos[i].xyz / lightpos[i].w ; 
            vec3 direction1 = normalize (position - mypos) ; // no attenuation 
            vec3 half1 = normalize (direction1 + eyedirn) ;  
            final_light_color =+ ComputeLight(direction1, lightcolor[i], normal, half1, diffuse, specular, shininess) ;
        }
        
        fragColor = ambient + final_light_color;
}
