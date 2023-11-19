#pragma once


#include <glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


class SpriteRenderer
{

public:
	SpriteRenderer(Shader& shader);

	void DrawSprite(glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(0.5f));

private:
	
	Shader shader;
	unsigned int quadVAO;
	void initRenderData();
	
};

