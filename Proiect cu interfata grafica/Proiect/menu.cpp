#include "menu.h"

Menu menu;

void drawText(sf::Vector2f relPosition, char* theString){
    int width = screenConfig.width;
    int height = (1.0f - screenConfig.yGUI) * screenConfig.height;

    float relX = relPosition.x;
    float relY = relPosition.y;

    sf::Font font("consolai.ttf");
    sf::Text text(font);

    text.setCharacterSize(height / 3.5f);
    text.setFillColor(sf::Color(255, 150, 50));

    text.setString(theString);
    text.setPosition({relX * width, relY * height});

    screenConfig.window.draw(text);
}

void drawTextBox(sf::Vector2f relPosition, sf::Vector2f relSize, char* theString, bool selected){
    int width = screenConfig.width;
    int height = (1.0f - screenConfig.yGUI) * screenConfig.height;

    sf::RectangleShape rectangle;

    rectangle.setFillColor(sf::Color(64, 32, 0));
    if(selected){
        rectangle.setFillColor(sf::Color(100, 64, 0));
    }

    rectangle.setOutlineColor(sf::Color(255, 150, 50));
    rectangle.setOutlineThickness(1.0f);

    rectangle.setPosition({relPosition.x * width, relPosition.y * height});
    rectangle.setSize({relSize.x * width, relSize.y * height});

    screenConfig.window.draw(rectangle);

    sf::Vector2f textRelPos =
    {relPosition.x + menu.xAligns[0], relPosition.y - 3*menu.yAligns[0]};
    drawText(textRelPos, theString);
}

void drawMenu(Menu& menu){
    screenConfig.window.setView(screenConfig.GUI_View);

    for(int i = 0; i < menu.noOfLabels; i++){
        drawText(menu.labelPositions[i], menu.labelTexts[i]);
    }
    for(int i = 0; i < menu.noOfTextBoxes; i++){
        bool selected = false;
        if(i == menu.selectedBox){ selected = true; }
        drawTextBox(menu.boxPositions[i], menu.boxSize, menu.boxTexts[i], selected);
    }

    screenConfig.window.setView(screenConfig.visualizerView);
}

void loadParamsToMesh(Mesh& mesh, Menu& menu){
    Vec3 translation, rotation, scaling;

    translation.x = stringToFloat(menu.boxTexts[0]);
    translation.y = stringToFloat(menu.boxTexts[1]);
    translation.z = stringToFloat(menu.boxTexts[2]);

    rotation.x = stringToFloat(menu.boxTexts[3]);
    rotation.y = stringToFloat(menu.boxTexts[4]);
    rotation.z = stringToFloat(menu.boxTexts[5]);

    scaling.x = stringToFloat(menu.boxTexts[6]);
    scaling.y = stringToFloat(menu.boxTexts[7]);
    scaling.z = stringToFloat(menu.boxTexts[8]);

    setScaling(mesh, scaling);
    setTranslation(mesh, translation);
    setRotation(mesh, rotation);
}

void loadParamsFromMesh(Menu& menu, Mesh& mesh){
    Vec3 translation = mesh.translation;
    Vec3 rotation = mesh.rotation;
    Vec3 scaling = mesh.scaling;

    floatToString(menu.boxTexts[0], translation.x);
    floatToString(menu.boxTexts[1], translation.y);
    floatToString(menu.boxTexts[2], translation.z);

    floatToString(menu.boxTexts[3], rotation.x);
    floatToString(menu.boxTexts[4], rotation.y);
    floatToString(menu.boxTexts[5], rotation.z);

    floatToString(menu.boxTexts[6], scaling.x);
    floatToString(menu.boxTexts[7], scaling.y);
    floatToString(menu.boxTexts[8], scaling.z);
}
