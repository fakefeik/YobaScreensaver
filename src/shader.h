#include "main.h"

class Shader {
public:
	Shader();
	~Shader();
	void init();
	void bind();
	void unbind();
	unsigned int id();
private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;
	bool inited;
};