// Import the Button library
#include "button.hpp"

// Handles the Button class
// Load the button texture from the its path and adjust its scale
Button::Button(const char * imagePath, Vector2 imagePosition, float scale) {
    Image image = LoadImage(imagePath);

    // Save the original size of the texture
    int originalWidth = image.width;
    int originalHeight = image.height;

    // Handles the new size of the texture
    int newWidth = static_cast<int>(originalWidth * scale);
    int newHeight = static_cast<int>(originalHeight * scale);

    // Rezise the texture
    ImageResize(&image, newWidth, newHeight);

    // Load the resized texture
    texture = LoadTextureFromImage(image);

    // Handles the Button position
    position = imagePosition;
}

// Clean up the resources used by the Button, such as the texture
Button::~Button() {
    UnloadTexture(texture);
}

// Draw the button on the screen
void Button::Draw() {
    DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
}

// Handles if the button has been pressed
bool Button::isPressed(Vector2 mousePos, bool mousePressed) {
    Rectangle rect = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};

    // If the mouse is over the button area and gets pressed, returns true
    if (CheckCollisionPointRec(mousePos, rect) && mousePressed) {
        return true;
    }
    

    // if not, returns false
    return false;
}
