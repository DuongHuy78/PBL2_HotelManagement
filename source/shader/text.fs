#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;
uniform int mode;      
uniform int nrChannels;
// mode = 0: normal render, 
// mode = 1: text render, 
// mode = 2: image render

void main() {    
    if(mode == 0) {
        color = vec4(textColor, 1.0);
    }
    else if(mode == 1) {
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
        color = vec4(textColor, 1.0) * sampled;
    }
    else if(mode == 2) {
        if(nrChannels == 1) {
            vec4 sampled = vec4(vec3(texture(text, TexCoords).r), 1.0);
            color = sampled;
        }
        else if(nrChannels == 3) {
            vec4 sampled = vec4(texture(text, TexCoords).rgb, 1.0);
            color = sampled;
        }
        else if(nrChannels == 4) {
            vec4 sampled = texture(text, TexCoords);
            color = sampled;
        }
    }
}  
