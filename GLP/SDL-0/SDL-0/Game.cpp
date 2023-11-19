#define GLT_IMPLEMENTATION
#define GLT_MANUAL_VIEWPORT

#include "Game.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Time.h"
#include "BallObject.h"
#include "gltext.h"
#include <SDL_timer.h>
#include <iostream>
#include <algorithm>
#include <string>


using namespace std;


SpriteRenderer* Renderer;
GameObject* leftPlayer;
GameObject* rightPlayer;
//GameObject* Ball;

BallObject* Ball;

void CheckCollision(BallObject& ball, GameObject& leftPlayer, GameObject& rightPlayer);

Game::Game()
    : State(GAME_ACTIVE), Keys(), Width(SCREEN_WIDTH), Height(SCREEN_HEIGHT), isRunning(true)
{

}

Game::~Game()
{
    //delete Renderer;
    delete leftPlayer;
    delete rightPlayer;
}

void Game::Init()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        cout << "SDL initialization succeeded!\n";
    }
    ///////////SETTING UP SDL/////////////
    //Create a simple window

    unsigned int center = SDL_WINDOWPOS_CENTERED;
    Window = SDL_CreateWindow("Pong", center, center, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    //SDL_WINDOW_OPENGL is a u32 flag !


    //Create an OpenGL compatible context to let glew draw on it
    Context = SDL_GL_CreateContext(Window);

    /////////SETTING UP OPENGL WITH GLEW///
    //Initialize glew
    glewExperimental = GL_TRUE;
    if (glewInit() == GLEW_OK) {
        cout << "Glew initialized successfully\n";
    }


    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



    ResourceManager::LoadShader("simpleVertex.shader", "simpleFragment.shader", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);

    glm::vec2 left_playerPos = glm::vec2(this->Width / 10.0f - PLAYER_SIZE.x * 3.0f, this->Height / 2.0f - PLAYER_SIZE.y / 2.0f);
    leftPlayer = new GameObject(left_playerPos, PLAYER_SIZE, PLAYER_ROTATION);

    glm::vec2 right_playerPos = glm::vec2(this->Width - PLAYER_SIZE.x * 2.0f, this->Height / 2.0f - PLAYER_SIZE.y / 2.0f);
    rightPlayer = new GameObject(right_playerPos, PLAYER_SIZE, PLAYER_ROTATION);

     glm::vec2 ballPos = glm::vec2(this->Width / 2.0f, this->Height / 2.0f);
    Ball = new BallObject(ballPos, BALL_SIZE, INITIAL_BALL_VELOCITY);

}


void Game::Update(float dt)
{
  




    // update objects
    Ball->Move(dt, this->Width, this->Height);

    CheckCollision(*Ball, *leftPlayer, *rightPlayer);

}

void CheckCollision(BallObject& ball, GameObject& leftPlayer, GameObject& rightPlayer)
{
    

    // collision x-axis?
    bool leftCollisionX = ball.Position.x + ball.Size.x >= leftPlayer.Position.x &&
        leftPlayer.Position.x + leftPlayer.Size.x >= ball.Position.x;
    // collision y-axis?
    bool leftCollisionY = ball.Position.y + ball.Size.y >= leftPlayer.Position.y &&
        leftPlayer.Position.y + leftPlayer.Size.y >= ball.Position.y;
    // collision only if on both axes

     // collision x-axis?
    bool rightCollisionX = ball.Position.x + ball.Size.x >= rightPlayer.Position.x &&
        rightPlayer.Position.x + rightPlayer.Size.x >= ball.Position.x;
    // collision y-axis?
    bool rightCollisionY = ball.Position.y + ball.Size.y >= rightPlayer.Position.y &&
        rightPlayer.Position.y + rightPlayer.Size.y >= ball.Position.y;
    // collision only if on both axes

    if (leftCollisionX && leftCollisionY)
    {
        
        ball.Velocity.x = -ball.Velocity.x;

        float centerBoard = leftPlayer.Position.x + leftPlayer.Size.x / 2.0f;
        float distance = (Ball->Position.x + Ball->Size.x) - centerBoard;
        float percentage = distance / (leftPlayer.Size.x / 2.0f);
        // then move accordingly
        
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * Ball->strength;
        
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        
        Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
      
    }

    if (rightCollisionX && rightCollisionY)
    {
        
        ball.Velocity.x = -ball.Velocity.x;

        float centerBoard = rightPlayer.Position.x + rightPlayer.Size.x / 2.0f;
        float distance = (Ball->Position.x + Ball->Size.x) - centerBoard;
        float percentage = distance / (rightPlayer.Size.x / 2.0f);
        // then move accordingly
        
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * Ball->strength;
        
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        
        Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
       
    }


}

void Game::Render()
{
    if (this->State == GAME_ACTIVE)
    {
        
        leftPlayer->Draw(*Renderer);

        rightPlayer->Draw(*Renderer);

        Ball->Draw(*Renderer);

    }
}

void Game::Loop()
{

    Timer timer;
    float dt = 0;


    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

  

    gltViewport(this->Width, this->Height);

     


    while (isRunning) {

        float dt = timer.computeDeltaTime() / 1000.0f;

        ProcessInput(dt);

        timer.delayTime();

        Update(dt);

        gltInit();
        
        glClear(GL_COLOR_BUFFER_BIT);

        

        string leftScoreString = to_string(Ball->leftPlayerScore);
        char const * leftScoreChar = leftScoreString.c_str();


        string rightScoreString = to_string(Ball->rightPlayerScore);
        char const* rightScoreChar = rightScoreString.c_str();
     
        // Creating text
        GLTtext* leftScoreText = gltCreateText();
        gltSetText(leftScoreText, leftScoreChar);

        GLTtext* rightScoreText = gltCreateText();
        gltSetText(rightScoreText, rightScoreChar);

     
        GLfloat fontScale = 1.5f;

        GLfloat x = 0.0f;
        GLfloat y = 0.0f;



        // Begin text drawing (this for instance calls glUseProgram)
        gltBeginDraw();

        // Draw any amount of text between begin and end
        gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        //gltDrawText2D(text, 0.0f, 0.0f, fontScale);
        gltDrawText2DAligned(leftScoreText, (GLfloat)this->Width / 4, (GLfloat)this->Height / 8, fontScale, GLT_TOP, GLT_TOP);
        gltDrawText2DAligned(rightScoreText, (GLfloat)this->Width / 1.5, (GLfloat)this->Height / 8, fontScale, GLT_TOP, GLT_TOP);


        // Finish drawing text
        gltEndDraw();

        // Deleting text
        gltDeleteText(leftScoreText);
        gltDeleteText(rightScoreText);

        // Destroy glText
        gltTerminate();

        Render();

        SDL_GL_SwapWindow(Window); // Swapbuffer   

    }

    SDL_DestroyWindow(Window);

    SDL_GL_DeleteContext(Context);

}


void Game::ProcessInput(float dt)
{


    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            switch (event.type) {

            case SDL_QUIT:
                isRunning = false;
                break;

            

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {

                case SDLK_UP:
                    if (rightPlayer->Position.y > 0)
                    {
                        rightPlayer->Position.y -= velocity;
                        
                    }
                    break;

                case SDLK_DOWN:
                    if (rightPlayer->Position.y < this->Height - rightPlayer->Size.y)
                    {
                        rightPlayer->Position.y += velocity;
                     
                    }
                    break;

                case SDLK_w:
                    if (leftPlayer->Position.y > 0)
                    {
                        leftPlayer->Position.y -= velocity;
                       
                    }
                    break;

                case SDLK_s:
                    if (leftPlayer->Position.y < this->Height - rightPlayer->Size.y)
                    {
                        leftPlayer->Position.y += velocity;
                        
                    }
                    break;

                case SDLK_ESCAPE:
                    isRunning = false;
                    break;


                }

            }
        }

    }
}
