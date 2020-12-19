#include "Mesh.h"

se::Mesh::Mesh(const se::AssetData* data) : se::Asset(data), se::Drawable()
{
	/*m_RenderPattern = [&]() {
		se::Camera m_Camera(glm::vec3(0.0, 0.0, 0.0), 70.0f, float(WINDOW_WIDTH) / float(WINDOW_HEIGHT), 0.01f, 3000.0f);
		m_Shader->Bind();
		m_Shader->SendUniformMatrix4fv(0, GL_FALSE, &m_Transform.GetModel()[0][0]);
		m_Shader->SendUniformMatrix4fv(1, GL_FALSE, &m_Camera.GetView()[0][0]);
		m_Shader->SendUniformMatrix4fv(2, GL_FALSE, &m_Camera.GetPerpective()[0][0]);
	};*/

}

se::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}



void se::Mesh::Load()
{
	m_Transform.SetPostition(glm::vec3(0, 0, 10));

	m_AttribCount = 1;
	m_IndicesCount = 3;
	//Only for test below
	GLfloat vertex[] = { 0.5f,  0.5f, 0.0f,  // top right
						 0.5f, -0.5f, 0.0f,  // bottom right
						-0.5f, -0.5f, 0.0f
	};
	GLuint  indices[] = { 0, 1, 2 };

	glGenVertexArrays(1, &m_VAO);

	glGenBuffers(1, &m_VBO);

	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

}
