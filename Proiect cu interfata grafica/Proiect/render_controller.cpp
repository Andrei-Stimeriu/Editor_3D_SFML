// This is the controller component of the software rasterizer.
//
// If an input is called (either by the user or the computer)
// the model get updated, followed by the view.
//
// NOTE:
// We are not referring to the matrices in the MVP!!
// This is an attempt to follow the MVC architecture.

#include "render_controller.h"

void updateProjectionMatrix() {
	float W = screenConfig.width;
	float H = screenConfig.yGUI * screenConfig.height;
	float front = projectionConfig.FAR_PLANE;
	float back = projectionConfig.NEAR_PLANE;

	renderState.projMatrix = projectionMatrix(projectionConfig.fov, W / H, front, back);
}

// TODO: Find a way to resize the software rasterizer window
//Done
void initializeWindow() {
	int screenWidth = screenConfig.width;
	int screenHeight = screenConfig.height;

	float yGUI = screenConfig.yGUI;

	renderState.viewportMatrix = viewportMatrix(0, 0, screenWidth, yGUI * screenHeight, 0, 1);

    screenConfig.visualizerView = sf::View(sf::FloatRect({0.0f, 0.0f}, {screenWidth, yGUI * screenHeight}));
    screenConfig.GUI_View = sf::View(sf::FloatRect({0.0f, 0.0f}, {screenWidth, (1.0f - yGUI) * screenHeight}));

    screenConfig.visualizerView.setViewport(sf::FloatRect({0.0f, 0.0f}, {1.0f, yGUI}));
    screenConfig.GUI_View.setViewport(sf::FloatRect({0.0f, yGUI}, {1.0f, 1.0f - yGUI}));

	screenConfig.window.create(sf::VideoMode(sf::Vector2u(screenWidth, screenHeight)), "Editor 3D");
	screenConfig.window.setView(screenConfig.visualizerView);
}
void updateWindow() {
	int screenWidth = screenConfig.width;
	int screenHeight = screenConfig.height;

	float yGUI = screenConfig.yGUI;

	renderState.viewportMatrix = viewportMatrix(0, 0, screenWidth, yGUI * screenHeight, 0, 1);

	screenConfig.visualizerView = sf::View(sf::FloatRect({0.0f, 0.0f}, {screenWidth, yGUI * screenHeight}));
    screenConfig.GUI_View = sf::View(sf::FloatRect({0.0f, 0.0f}, {screenWidth, (1.0f - yGUI) * screenHeight}));

    screenConfig.visualizerView.setViewport(sf::FloatRect({0.0f, 0.0f}, {1.0f, yGUI}));
    screenConfig.GUI_View.setViewport(sf::FloatRect({0.0f, yGUI}, {1.0f, 1.0f - yGUI}));
}

// Updates view matrix based on current camera state
void updateViewMatrix() {
	Vec3& camPos = cameraState.camPosition;
	Vec3& camAngle = cameraState.camAngle;

	renderState.viewMatrix = viewMatrix(camPos, camAngle);
}

// Calculates MVP given the model matrix
Mat4 calculateMVP(const Mat4& modelMatrix) {
	return prodMatrix(renderState.projMatrix, prodMatrix(renderState.viewMatrix, modelMatrix));
}

void initializeRenderState() {
	updateProjectionMatrix();
	initializeWindow();
	updateViewMatrix();
}

void updateRenderState() {
	updateProjectionMatrix();
	updateWindow();
	updateViewMatrix();
}
