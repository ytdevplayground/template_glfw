#version 460 core
                              
out vec4 aColor;

uniform sampler2D uTexture;

in vec2 vTexCoord;
                              
void main() {
    aColor = texture(uTexture, vTexCoord);
}