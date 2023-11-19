#pragma once

#include <glew.h>
#include <gl/GL.h>
#include <SDL.h>
#include <glm/glm.hpp>


#include "GameObject.h"


class BallObject : public GameObject
{
public:
   
    int leftPlayerScore = 0;
    int rightPlayerScore = 0;

    
    
    // constructor(s)
    BallObject();
    BallObject(glm::vec2 pos, const glm::vec2 size, glm::vec2 velocity);

    // moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 Move(float dt, unsigned int window_width, unsigned int window_height);

   
};