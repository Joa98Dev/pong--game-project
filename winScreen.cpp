#include <raylib.h>
#include <iostream>
#include "button.hpp"
#include "main.hpp"


void Winner() {
    
    SetTargetFPS(30);

    Texture2D background = LoadTexture("Graphics/creditsBG.png");

    // Load the button texture
    Button startButton{"Graphics/startButton.png", {300, 300}, {0.5}};
    Button exitButton{"Graphics/exitButton.png", {300, 450}, {0.5}};

    InitAudioDevice();

    Music bgMusic = LoadMusicStream("Audio/playerWinsTheme.ogg");
    Sound buttonPressed = LoadSound("Audio/buttonPressed.ogg");

    SetMusicVolume(bgMusic, 0.3f);

    PlayMusicStream(bgMusic);

    bool exitGame = false;

    while(WindowShouldClose() == false && exitGame == false) {
        
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

}