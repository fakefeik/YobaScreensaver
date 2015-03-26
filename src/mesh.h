#include "main.h"

class Mesh {
public:
	Mesh(void);
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

class Cube: public Mesh {
public:
	Cube();
};