#version 330 core
// Do not use any version older than 330!

in vec4 myvertex;
in vec3 mynormal;

out vec4 fragColor;

uniform vec3 light0dirn; 
uniform vec4 light0color; 

uniform vec4 light1posn; 
uniform vec4 light1color; 

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

        // Light 0, directional
        vec3 direction0 = normalize (light0dirn) ; 
        vec3 half0 = normalize (direction0 + eyedirn) ; 
        vec4 col0 = ComputeLight(direction0, light0color, normal, half0, diffuse, specular, shininess);

          // Light 1, point 
        vec3 position = light1posn.xyz / light1posn.w ; 
        vec3 direction1 = normalize (position - mypos) ; // no attenuation 
        vec3 half1 = normalize (direction1 + eyedirn) ;  
        vec4 col1 = ComputeLight(direction1, light1color, normal, half1, diffuse, specular, shininess) ;
        
        fragColor = ambient + col0 + col1;
}
