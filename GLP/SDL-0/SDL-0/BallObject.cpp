#include "BallObject.h"

#include <iostream>
#include <string>

using namespace std;

BallObject::BallObject()
    : GameObject() { }

BallObject::BallObject(glm::vec2 pos, const glm::vec2 size, glm::vec2 velocity)
    : GameObject(pos, size, glm::vec3(1.0f), velocity) { }

glm::vec2 BallObject::Move(float dt, unsigned int window_width, unsigned int window_height)
{


    // move the ball
    this->Position += this->Velocity * dt;
    this->Color = glm::vec3(this->Position.x / window_width, 0.0f, this->Position.x / window_width);

    
    // then check if outside window bounds and if so, reverse velocity and restore at correct position
    if (this->Position.x <= 0.0f)
    {
        //Reset Position
        this->Position = glm::vec2(window_width / 2.0f, window_height / 2.0f);
        leftPlayerScore += 1;

        

    }
    else if (this->Position.x + this->Size.x >= window_width)
    {
        
        this->Position = glm::vec2(window_width / 2.0f, window_height / 2.0f);
        rightPlayerScore += 1;

       
       
    }
    if (this->Position.y <= 0.0f)
        {
            
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    else if (this->Position.y + this->Size.y >= window_height)
    {

        this->Velocity.y = -this->Velocity.y;
        this->Position.y = window_height - this->Size.y;
    }
    
    return this->Position;
}


