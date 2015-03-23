#include "main.h"

class Mesh {
public:
	std::string name;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scaling;

	Mesh(void);
	Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned short> indices);
	Mesh(float vertices[], unsigned int indices[], float uvs[], const char *texturepath);
	Mesh::Mesh(std::string name, 
		   float vertices[], int vertCount, 
		   int indices[], int indCount, 
		   float uvs[], int uvCount,
		   glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling);
	void LoadTexture(const char *path);
	void Draw(void);
	void DrawWireframe(void);
protected:
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint linesBuffer;
	GLuint uvBuffer;
	GLuint textureID;
	int verticesCount;
	int indicesCount;
	int uvsCount;
	int lineIndicesCount;
	void SetVertices(float vertices[], int verticesCount);
	void SetIndices(int indices[], int indicesCount);
	void SetTextureCoordinates(float textureCoordinates[], int uvsCount);
	void SetLineIndices(int indcies[]);
};

class Plane: public Mesh {
public:
	Plane(float size);
	Plane(float width, float height);
	Plane(float width, float height, glm::vec3 position, float textureCoords);
};

class Cube: public Mesh {
public:
	Cube();
	Cube(float size);
	Cube(float width, float height, float depth);
};