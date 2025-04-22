// Include the raylib library
#include <raylib.h>
#include <iostream>
#include "main.hpp"
#include "winScreen.hpp"

// Global variables that store the player and cpu score
int playerScore = 0;
int cpuScore = 0;

// Class that store all the attributes of the ball object
class Ball {
    public:
    // Circle coordinates
    float x;
    float y;

    // Circle speed x and  y axis
    int speedX, speedY;

    // Circle radius
    int radius;

    // Draw the circle shape
    void Draw() {
        // Coordinate x, y, radius, color
        DrawCircle(x, y, 20, WHITE);
    }

    // Update circle speed on x and y axis
    void Update() {
        x += speedX;
        y += speedY;

        // Make the ball collide with screen limits
        if(y + radius >= GetScreenHeight() || y - radius <= 0) {
            speedY *= -1;
        }

        // Handle the player and cpuscore
        if(x + radius >= GetScreenWidth()) {
            cpuScore++;
            resetBall();
        } else if(x - radius <= 0) {
            playerScore++;
            resetBall();
        }

        if(cpuScore == 10 || playerScore == 10) {
            Winner();
        }
    }

    // Reset the ball attributes 
    void resetBall() {
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed[2] = {-1, 1};
        speedX *= speed[GetRandomValue(0,1)];
        speedY *= speed[GetRandomValue(0,1)];
    }
};

// Class that store all the attributes of the paddle object
class Paddle {
    protected:
    // Limit the paddle movement to the Y axis
    void LimitMovement() {
        if (y < 0) {
            y = 0;
        }
    
        if (y > GetScreenHeight() - height) {
            y = GetScreenHeight() - height;
        }
    }

    // Store the paddle coordinates, size and speed
    public:
    float x;
    float y;
    float width;
    float height;
    int speed;

    // Function that handles how the rectangle being drew
    void Draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }

    // Funtion that update the paddle position when up and down key are pressed
    void Update() {
        if(IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if(IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        
        LimitMovement();
    }
};

// Class that store all the attributes of the cpu paddle object
class cpuPaddle: public Paddle {
    public:

    // Upadate the cpu paddle position to follow the ball's coordinates
    void Update(int ballY) {
        if (ballY < y + height / 2 - 10) {
            y -= speed;
        } else if (ballY > y + height / 2 + 10) {
            y += speed;
        }
        LimitMovement();
    }
};
// Instance all the objects classes
Ball ball;
Paddle paddle;
cpuPaddle cpu;

// Stores all the game logic
void RunGame() {

    // Handles the frames per second
    SetTargetFPS(60);

    // Initialize the game audio
    InitAudioDevice();

    // Load the music and sfx
    Music bgMusic = LoadMusicStream("Audio/pongTheme.mp3");
    Sound collideSound = LoadSound("Audio/collideSound.ogg");

    // Set up the volume
    SetMusicVolume(bgMusic, 0.3f);

    // Play the music
    PlayMusicStream(bgMusic);

    // Paddle coordinates
    int rectX = 10;
    int rectY = 400;

    // Defining the background color {red, green, blue, alpha channel}
    Color AQUA = {4, 195, 221, 255};

    // Ball instance
    ball.radius = 20;
    ball.x = 400;
    ball.y = 400;
    ball.speedX = 5;
    ball.speedY = 5;

    // Paddle instance
    paddle.width = 25;
    paddle.height = 120;
    paddle.x = GetScreenWidth() - paddle.width - 10;
    paddle.y = (GetScreenHeight() - paddle.height) / 2;
    paddle.speed = 5;

    // CPU paddle instance
    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = (GetScreenHeight() - paddle.height) / 2;
    cpu.speed = 5;

    // Game loop
    while(WindowShouldClose() == false) {

        // Loop the music
        UpdateMusicStream(bgMusic);

        // Start drawing the differente shapes on screen
        BeginDrawing();

        // Updating all the objects
        ball.Update();
        paddle.Update();
        cpu.Update(ball.y);

        // Handle the ball with the paddle and the cpu paddle collision
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{paddle.x, paddle.y, paddle.width, paddle.height})) {
            ball.speedX *= -1;
            PlaySound(collideSound);
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})) {
            ball.speedX *= -1;
            PlaySound(collideSound);
        }

        // Clear the BG with the color added
        ClearBackground(AQUA);

        // Draw a line on the screen
        // Coordinate start -> x, y && end -> x, y, color
        DrawLine(400, 0, 400, 800, WHITE);

        // Call the draw method of all the objects
        ball.Draw();
        paddle.Draw();
        cpu.Draw();

        // Show text on the window(text, positionX, positionY, fontSize, Color)
        DrawText(TextFormat("%i", cpuScore), 200, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore), 600, 20, 80, WHITE);
        
        // End the drawing function
        EndDrawing();
    }
        // Clean up the audio resources
        UnloadMusicStream(bgMusic);
        UnloadSound(collideSound);

        // Stop audio
        CloseAudioDevice();
}