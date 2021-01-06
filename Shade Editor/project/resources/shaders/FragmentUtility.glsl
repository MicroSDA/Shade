vec3 CalculateTBNNormal(vec3 NormalMap, mat3 TBNMatrix)
{
   vec3 m_TBNNormal = NormalMap;
   m_TBNNormal = 2.0 * m_TBNNormal  - vec3(1.0, 1.0, 1.0);   
   m_TBNNormal = normalize(TBNMatrix * m_TBNNormal);
   return m_TBNNormal;
}