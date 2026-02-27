#pragma once
#include "pch.h"
#include "input_controller.h"
#include "render_controller.h"
#include "camera_controller.h"
#include "render_view.h"
#include "state.h"
#include "config.h"
#include "menu.h"

#define _USE_MATH_DEFINES

int main() {
    //Read file path for .obj file
    std::cout<<"Enter .obj file path:\n\n";
    char objFilePath[401]; gets(objFilePath);

    //char objFilePath[] = "cubeOne.obj";

	// Initialize render state and window
	initializeRenderState();

	const float PI = 3.141592f;
	const float DELTA = 0.5f * PI;

	// Create mesh from an .obj file
	Mesh mesh = createMesh(objFilePath);
	if(mesh.failedLoading){ std::cout<<"\nError: File not found!\n"; return 0; }

	sf::Clock clock;

	while (screenConfig.window.isOpen()) {
		timeState.deltaTime = clock.restart().asSeconds();

		// Act upon mouse or keyboard press
		//and window closing or resizing
		handleInputs();

		loadParamsToMesh(mesh, menu);
		
		//TODO: Have multiple meshes and loadParams to all selected ones.
		/*for(int i = 0; i < noOfMeshes; i++){
			if(meshes[i].isSelected){
				loadParamsToMesh(meshes[i], menu);
			}
		}*/
		
		//TODO: Unify two or more meshes into one mesh.

		// Draw frist cube in 3D space and rotate it
		drawMesh(mesh);

		// Draw world axis in the center of the screen
		if (renderConfig.drawAxisEnabled) {
			drawAxis();
		}

		//Draw the menu
		drawMenu(menu);

		screenConfig.window.display();
		screenConfig.window.clear();
	}
	return 0;
}
