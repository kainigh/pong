#pragma once


#include <glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>

#include "SpriteRenderer.h"

class GameObject
{

public:
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	float       Rotation;
	float strength = 2.0f;
	
	

	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec3 color, glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	GameObject(glm::vec2 pos, glm::vec2 size, float rotation, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	virtual void Draw(SpriteRenderer& renderer);


};

