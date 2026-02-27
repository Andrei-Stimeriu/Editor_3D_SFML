#pragma once
#include <SFML/Graphics.hpp>
#include "config.h"
#include "mesh.h"
#include "stringProcessing.h"

struct Menu{
    int noOfLabels = 12;
    int noOfTextBoxes = 9;

    float xAligns[4] = {0.01f, 0.33f, 0.55f, 0.78f};
    float yAligns[3] = {0.01f, 0.34f, 0.67f};

    float xOffset = 0.03f;

    char labelTexts[12][12] =
    {"Position", "Rotation", "Scale",
     "X", "Y", "Z",
     "X", "Y", "Z",
     "X", "Y", "Z"};

    sf::Vector2f labelPositions[12] =
    {{xAligns[0], yAligns[0]}, {xAligns[0], yAligns[1]}, {xAligns[0], yAligns[2]},
     {xAligns[1], yAligns[0]}, {xAligns[2], yAligns[0]}, {xAligns[3], yAligns[0]},
     {xAligns[1], yAligns[1]}, {xAligns[2], yAligns[1]}, {xAligns[3], yAligns[1]},
     {xAligns[1], yAligns[2]}, {xAligns[2], yAligns[2]}, {xAligns[3], yAligns[2]}};

    int maxTextLength = 6;

    char boxTexts[9][7] =
    {"0", "0", "0",
     "0", "0", "0",
     "1", "1", "1"};

    sf::Vector2f boxPositions[9];

    sf::Vector2f boxSize = {0.15f, 0.3f};

    int selectedBox = -1;

    Menu(){
        for(int i = 0; i < noOfTextBoxes; i++){
            boxPositions[i].x = labelPositions[i+3].x + xOffset;
            boxPositions[i].y = labelPositions[i+3].y;
        }
    }
};
extern Menu menu;

void drawText(sf::Vector2f relPosition, char* theString);
void drawTextBox(sf::Vector2f relPosition, sf::Vector2f relSize, char* theString, bool selected);
void drawMenu(Menu& menu);
void loadParamsToMesh(Mesh& mesh, Menu& menu);
void loadParamsFromMesh(Menu& menu, Mesh& mesh);
