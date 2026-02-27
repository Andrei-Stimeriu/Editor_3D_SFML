#include "input_controller.h";

// Move on keyboard press
void handleKeyboardInput() {
	float units = movementConfig.speed * timeState.deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		cameraShift(worldForward * units);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		cameraShift(worldForward * -units);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		cameraShift(worldRight * -units);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		cameraShift(worldRight * units);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
		cameraShift(worldUp * units);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
		cameraShift(worldUp * -units);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && !renderConfig.hasBeenToggled) {
		renderConfig.drawAxisEnabled = !renderConfig.drawAxisEnabled;
		renderConfig.hasBeenToggled = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
		renderConfig.hasBeenToggled = false;
	}

	///Digits for GUI
	if(menu.selectedBox >= 0){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Period) && !keyboardConfig.isToggled[keyboardConfig.keys::point]){
            append(menu.boxTexts[menu.selectedBox], '.');
            keyboardConfig.isToggled[keyboardConfig.keys::point] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Period)){
            keyboardConfig.isToggled[keyboardConfig.keys::point] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace) && !keyboardConfig.isToggled[keyboardConfig.keys::backspace]){
            backOne(menu.boxTexts[menu.selectedBox]);
            keyboardConfig.isToggled[keyboardConfig.keys::backspace] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)){
            keyboardConfig.isToggled[keyboardConfig.keys::backspace] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract) && !keyboardConfig.isToggled[keyboardConfig.keys::Minus]){
            append(menu.boxTexts[menu.selectedBox], '-');
            keyboardConfig.isToggled[keyboardConfig.keys::Minus] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Subtract)){
            keyboardConfig.isToggled[keyboardConfig.keys::Minus] = false;
        }

        ///DIGIT KEYS

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0) && !keyboardConfig.isToggled[0]){
            append(menu.boxTexts[menu.selectedBox], '0');
            keyboardConfig.isToggled[0] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0)){
            keyboardConfig.isToggled[0] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && !keyboardConfig.isToggled[1]){
            append(menu.boxTexts[menu.selectedBox], '1');
            keyboardConfig.isToggled[1] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)){
            keyboardConfig.isToggled[1] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && !keyboardConfig.isToggled[2]){
            append(menu.boxTexts[menu.selectedBox], '2');
            keyboardConfig.isToggled[2] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)){
            keyboardConfig.isToggled[2] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) && !keyboardConfig.isToggled[3]){
            append(menu.boxTexts[menu.selectedBox], '3');
            keyboardConfig.isToggled[3] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)){
            keyboardConfig.isToggled[3] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) && !keyboardConfig.isToggled[4]){
            append(menu.boxTexts[menu.selectedBox], '4');
            keyboardConfig.isToggled[4] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)){
            keyboardConfig.isToggled[4] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) && !keyboardConfig.isToggled[5]){
            append(menu.boxTexts[menu.selectedBox], '5');
            keyboardConfig.isToggled[5] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)){
            keyboardConfig.isToggled[5] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6) && !keyboardConfig.isToggled[6]){
            append(menu.boxTexts[menu.selectedBox], '6');
            keyboardConfig.isToggled[6] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)){
            keyboardConfig.isToggled[6] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7) && !keyboardConfig.isToggled[7]){
            append(menu.boxTexts[menu.selectedBox], '7');
            keyboardConfig.isToggled[7] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)){
            keyboardConfig.isToggled[7] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8) && !keyboardConfig.isToggled[8]){
            append(menu.boxTexts[menu.selectedBox], '8');
            keyboardConfig.isToggled[8] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)){
            keyboardConfig.isToggled[8] = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9) && !keyboardConfig.isToggled[9]){
            append(menu.boxTexts[menu.selectedBox], '9');
            keyboardConfig.isToggled[9] = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)){
            keyboardConfig.isToggled[9] = false;
        }
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
        screenConfig.window.close();
	}
}

//Check in which view the mouse is
int viewFromCoords(int x, int y){
    if(y > screenConfig.yGUI * screenConfig.height){
        return screenConfig.views::GUI;
    }
    return screenConfig.views::visualizer;
}

void handleCameraMovement(int mx, int my, bool mp){
    if(mp){
        // Calculate offset from last frame
        int offsetX = mouseState.x - mx;
        int offsetY = my - mouseState.y;

        // Apply sensitivity
        cameraState.camAngle.y += offsetX * movementConfig.sensitivity; // yaw
        cameraState.camAngle.x += offsetY * movementConfig.sensitivity; // pitch

        // Clamp pitch (prevent flipping)
        if (cameraState.camAngle.x > 1.5f) cameraState.camAngle.x = 1.5f;
        if (cameraState.camAngle.x < -1.5f) cameraState.camAngle.x = -1.5f;
	}
}

void handleGUIMouse(Menu& menu, float relX, float relY, bool mp){
    if(!mp){
        mouseState.isToggled = false;
        return;
    }
    if(mouseState.isToggled){ return; }

    bool found = false;
    for(int i = 0; i < menu.noOfTextBoxes; i++){
        sf::FloatRect box(menu.boxPositions[i], menu.boxSize);
        if(box.contains({relX, relY})){
            menu.selectedBox = i;
            found = true;
            break;
        }
    }
    if(!found){ menu.selectedBox = -1; }
    mouseState.isToggled = true;
}

// Rotate on mouse move
void handleMouseInput() {
	// Mouse look
	int mx = sf::Mouse::getPosition(screenConfig.window).x;
	int my = sf::Mouse::getPosition(screenConfig.window).y;
	bool mp = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	if(viewFromCoords(mx, my) == screenConfig.views::visualizer){
        handleCameraMovement(mx, my, mp);
	}
	else{//Mouse is in the GUI panel
        int width = screenConfig.width;
        int height = (1.0f - screenConfig.yGUI) * screenConfig.height;

        float relX = (float)mx / width;
        float relY = (float)(my - screenConfig.yGUI * screenConfig.height) / height;

        handleGUIMouse(menu, relX, relY, mp);
	}

	// Save new mouse state
	mouseState.x = mx;
	mouseState.y = my;
	mouseState.isPressed = mp;
}

//Terminate when window is closed and
//Update the render state when resized.
void handleWindowEvents(){
    while (const std::optional event = screenConfig.window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            screenConfig.window.close();
        }
        else if(event->is<sf::Event::Resized>()){
            screenConfig.width = screenConfig.window.getSize().x;
            screenConfig.height = screenConfig.window.getSize().y;
            updateRenderState();
        }
    }
}

// Handle all existing inputs
void handleInputs() {
	handleKeyboardInput();
	handleMouseInput();
	handleWindowEvents();
	updateViewMatrix();
}
