#pragma once

#include "pch.h"
#include "state.h"
#include "config.h"
#include "camera_controller.h"
#include "render_controller.h"
#include "menu.h"
#include "stringProcessing.h"

void handleKeyboardInput();
void handleMouseInput();
void handleWindowEvents();
void handleInputs();

int viewFromCoords(int x, int y);
void handleCameraMovement(int mx, int my, bool mp);
void handleGUI(Menu& menu, float relX, float relY, bool mp);
