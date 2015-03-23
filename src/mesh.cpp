#include "mesh.h"
#include "texture.h"

Mesh::Mesh() {

}

Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned short> indices) {
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	uvBuffer = -1;
}

Mesh::Mesh(float vertices[], unsigned int indices[], float uvs[], const char *texturepath) {

}

Mesh::Mesh(std::string name, 
		   float vertices[], int vertCount, 
		   int indices[], int indCount, 
		   float uvs[], int uvCount,
		   glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling) {
	this->name = name;
	this->position = position;
	this->rotation = rotation;
	this->scaling = scaling;
	SetVertices(vertices, vertCount);
	SetIndices(indices, indCount);
	SetTextureCoordinates(uvs, uvCount);
}

void Mesh::Draw() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	if (textureID != -1 && uvBuffer != -1) {
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, (void*)0);

	glDisableVertexAttribArray(0);
}

void Mesh::DrawWireframe() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, linesBuffer);
	glDrawElements(GL_LINES, indicesCount * 2, GL_UNSIGNED_INT, (void*)0);
	glDisableVertexAttribArray(0);
}

void Mesh::SetVertices(float vertices[], int verticesCount) {
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, verticesCount, &vertices[0], GL_STATIC_DRAW);
	this->verticesCount = verticesCount;
}


void Mesh::SetIndices(int indices[], int indicesCount) {
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indicesCount, &indices[0], GL_STATIC_DRAW);
	this->indicesCount = indicesCount;
	SetLineIndices(indices);
}

void Mesh::SetTextureCoordinates(float textureCoordinates[], int uvsCount) {
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvsCount, &textureCoordinates[0], GL_STATIC_DRAW);
	this->uvsCount = uvsCount;
}

void Mesh::SetLineIndices(int indices[]) {
	std::vector<int> lineIndices;
	int j = 0;
	for (int i = 0; i < indicesCount * 2; i += 6) {
		int a = indices[j];
		int b = indices[j + 1];
		int c = indices[j + 2];
		j += 3;
		lineIndices.push_back(a);
		lineIndices.push_back(b);
		lineIndices.push_back(b);
		lineIndices.push_back(c);
		lineIndices.push_back(c);
		lineIndices.push_back(a);
	}
	glGenBuffers(1, &linesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, linesBuffer);
	glBufferData(GL_ARRAY_BUFFER, lineIndices.size(), &lineIndices[0], GL_STATIC_DRAW);
}

void Mesh::LoadTexture(const char *path) {
	textureID = loadBMP_custom();
}