#version 330

in vec3 i_nl;
in vec2 i_tc;
in vec3 i_coord;


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light
{
    vec3 Pos;
    vec3 Color;
};


uniform sampler2D TEX;
uniform mat3 NormalMatrix;
uniform Light Lights[256];
uniform int LightsCount;
uniform vec3 CameraPos;


void main()
{
  vec4 color = vec4(0.025, 0.025, 0.025, 1.0) * texture(TEX, i_tc);
  vec3 normal = NormalMatrix * i_nl;
  vec3 ViewDir = normalize(CameraPos - i_coord);

  for(int i = 0; i < LightsCount; i++)
  {
    vec3 LightDir = normalize(Lights[i].Pos - i_coord);  
    vec3 ReflectDir = reflect(-LightDir, normal);
    float Dist = distance(i_coord, Lights[i].Pos);
    
    float diff = max(dot(normal, LightDir), 0.0);
    float spec = pow(max(dot(ViewDir, ReflectDir), 0.0), 32);

    vec3 Diffuse = Lights[i].Color * diff * (1 / Dist) * (1 / Dist);
    vec3 Specular = 0.5 * spec * Lights[i].Color * (1 / Dist) * (1 / Dist);

    color += vec4((Diffuse + Specular), 1.0) * texture(TEX, i_tc);
  }
  
  pixelColor = color;
}  