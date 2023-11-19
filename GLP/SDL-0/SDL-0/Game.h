#pragma once
#include <SDL.h>
#include <glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>


// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(20.0f, 200.0f);
const float PLAYER_ROTATION(0.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(3000.0f);

const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
//const float BALL_RADIUS = 12.5f;
const glm::vec2 BALL_SIZE(20.0f, 20.0f);

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;


class Game
{

public:
    GameState               State;
    bool                    Keys[1024];
    unsigned int Width, Height;
    bool isRunning;
   

    //unsigned int frameStart = 0;
    // Last frame start time in milliseconds
    //unsigned int lastFrame;

    Game();
    ~Game();
    SDL_Window* Window;
    SDL_GLContext Context;
    void ProcessInput(float dt);
    // initialize game state (load all shaders/textures/levels)
    void Init();
    void Render();
   
    void Loop();
    void Update(float dt);


};

