#version 300 es
precision lowp float;

out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture0;

void main()
{
    FragColor = vec4(mix(ourColor, texture(texture0, TexCoord).rgb, 0.2), 1.0f);
}