// Ensure header is only include once
#pragma once

// Import the raylib library
#include <raylib.h>

// Store all the Button attributes
class Button {
    public:
        // Handle the image route, its postion and scale
        Button(const char* imagePath, Vector2 imagePosition, float scale);

        // Clean up the resources used by the Button
        ~Button();

        // Handles the Button render on the screen
        void Draw();

        // Handles if the button is pressed
        bool isPressed(Vector2 mousePos, bool mousePressed);
    private:
        Texture2D texture;
        Vector2 position;
};