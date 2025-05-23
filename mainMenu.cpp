// Import all the libraries needed
#include <raylib.h>
#include <iostream>
#include "button.hpp"
#include "main.hpp"

// main function of the game
int main() {

    // Initialize a window
    InitWindow(800, 800, "Pong++");
    
    // Set the frames per seconds
    SetTargetFPS(60);

    // Initialize the game audio
    InitAudioDevice();

    // Load BG and buttons images
    Texture2D background = LoadTexture("Graphics/menuBG.png");
    Button startButton{"Graphics/startButton.png", {300, 300}, {0.5}}; // x = 300, y = 150
    Button exitButton{"Graphics/exitButton.png", {300, 450}, {0.5}};

    // Load the music and sfx
    Music bgMusic = LoadMusicStream("Audio/bgTheme.mp3");
    Sound buttonPressed = LoadSound("Audio/buttonPressed.ogg");
    // Set the volume
    SetMusicVolume(bgMusic, 0.3f);

    // Play the music
    PlayMusicStream(bgMusic);
    

    // Handle if the game is close
    bool exitGame = false;

// Game loop
    while(WindowShouldClose() == false && exitGame == false) {

        // Loop the music
        UpdateMusicStream(bgMusic);


        // Check every time the mouse coordinates
        Vector2 mousePos = GetMousePosition();

        // Check if the left button of the mouse has been pressed
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // Check if the start button has been pressed
        // If the button is pressed loads the game
        if(startButton.isPressed(mousePos, mousePressed)) {
            PlaySound(buttonPressed);
            WaitTime(0.2f);
            RunGame();
        }

        // Check if the start button has been pressed
        // If the button is pressed close the game
        if(exitButton.isPressed(mousePos, mousePressed)) {
            PlaySound(buttonPressed);
            WaitTime(0.2f);
            exitGame = true;
        }

        // Draw the objetcs to show in the main menu
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background, 0, 0, WHITE);
        startButton.Draw();
        exitButton.Draw();
        EndDrawing();
    }

    // Clean up the audio resources
    UnloadMusicStream(bgMusic);

    // Clean up the sound resources
    UnloadSound(buttonPressed);

    // Stop audio
    CloseAudioDevice();

    CloseWindow();
    return 0;
}

// g++ main.cpp mainMenu.cpp button.cpp -o pong -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

// https://youtu.be/L_OYo2RS8iU?list=PLwJjxqYuirCLkq42mGw4XKGQlpZSfxsYd
// https://youtu.be/pXdrz1pB35Q?list=PLwJjxqYuirCLkq42mGw4XKGQlpZSfxsYd