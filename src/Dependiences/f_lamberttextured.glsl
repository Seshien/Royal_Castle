#version 330

in vec2 input_texcoords;
in vec3 input_normal;
in vec3 input_coords;


out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela


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
  vec4 color = vec4(0.1, 0.1, 0.1, 1.0) * texture(TEX, input_texcoords);
  vec3 normal = normalize(NormalMatrix * input_normal);
  vec3 ViewDir = normalize(CameraPos - input_coords);

  for(int i = 0; i < LightsCount; i++)
  {

    vec3 LightDir = normalize(Lights[i].Pos - input_coords);  
    vec3 ReflectDir = reflect(-LightDir, normal);
    float Dist = distance(input_coords, Lights[i].Pos);
    
    float diff = max(dot(normal, LightDir), 0.0);
    float spec = pow(max(dot(ViewDir, ReflectDir), 0.0), 8);

    vec3 Diffuse = Lights[i].Color * diff * (1 / Dist) * (1 / Dist);
    //vec3 Diffuse = vec3(0,0,0);
    vec3 Specular = 0.5 * spec * Lights[i].Color * (5 / Dist) ;
    //vec3 Specular = vec3(0,0,0);
    color += vec4((Diffuse + Specular), 1.0) * texture(TEX, input_texcoords);
  }
  
  pixelColor = color;
}  