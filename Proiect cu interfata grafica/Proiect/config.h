#pragma once
#include "SFML/Graphics.hpp";

// Screen / Viewport configurations
struct ScreenConfig {
	int width = 1280;
	int height = 720;

	// Top-Left relative coordinates of the visualizer area
	const float xVisualizer = 0.0f;
	const float yVisualizer = 0.0f;

	// Top-Left relative coordinates of the GUI area
	const float xGUI = 0.0f;
	const float yGUI = 0.8f;

	sf::RenderWindow window;
	sf::View visualizerView, GUI_View;

	enum views{ visualizer, GUI };
};
extern ScreenConfig screenConfig;

// Projection configurations
struct ProjectionConfig {
	float fov = 45.0f;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 100.0f;
};
extern ProjectionConfig projectionConfig;

// Movement configurations
struct MovementConfig {
	float speed = 1.0f;
	float sensitivity = 0.01f;
};
extern MovementConfig movementConfig;

// Render configurations
struct RenderConfig {
	bool drawAxisEnabled = true;
	bool hasBeenToggled = false;
};
extern RenderConfig renderConfig;

//Keyboard configurations
struct KeyboardConfig{
    bool isToggled[13] = {false};
    enum keys{ point = 10, backspace = 11, Minus = 12 };
};
extern KeyboardConfig keyboardConfig;
