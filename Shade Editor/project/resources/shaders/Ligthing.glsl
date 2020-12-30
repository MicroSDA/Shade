/*vec4 Light(vec3 Normals, vec4 Texture)
{
    return vec4(Texture.rgb * clamp(dot(-vec3(0,0,1), Normals),0.0, 1.0), Texture.a);
}*/
struct GeneralLight {
   vec3  direction;
   vec3  colorAmbient;
   vec3  colorDiffuse;
   vec3  colorSpecular;
   float shininesStrength;
};
struct Material {
   vec3  colorAmbient;
   vec3  colorDiffuse;
   vec3  colorSpecular;
   float shinines;
   float transparency;
};

uniform GeneralLight   generalL;
uniform Material       material;

vec4 ProcessGeneralLight(GeneralLight generalLight, Material material, vec3 NormalTBN, vec4 Texture, vec3 ToCameraDirection)
{
    vec4  m_AmbientColor   = vec4(vec3(0,0,0) * generalLight.colorAmbient, 1.0)  * Texture;
    vec4  m_DiffuesColor   = vec4(0.0, 0.0, 0.0, 1.0);
    vec4  m_SpecularColor  = vec4(0.0, 0.0, 0.0, 1.0);

    float m_DiffuesShading = dot(NormalTBN, -generalLight.direction);

    if(m_DiffuesShading > 0.0)
    {
       m_DiffuesColor   = vec4(vec3(1,1,1) * generalLight.colorDiffuse * m_DiffuesShading, 1.0) * Texture;
      // vec3  m_Reflect  = normalize(reflect(-generalLight.direction, NormalTBN));
       //float m_SpecularShading = dot(ToCameraDirection, m_Reflect);
       float m_SpecularShading = dot(NormalTBN, normalize(-generalLight.direction + ToCameraDirection));
       if(m_SpecularShading > 0.0)
       {
          m_SpecularShading = pow(m_SpecularShading, 2);
          m_SpecularColor  = vec4(vec3(1,1,1) * vec3(1,1,1), 1.0) * generalLight.shininesStrength * m_SpecularShading * 
          Texture ; 
      }
    }

    return vec4(m_AmbientColor + m_DiffuesColor + m_SpecularColor);// Alpha is hardcoded now
}