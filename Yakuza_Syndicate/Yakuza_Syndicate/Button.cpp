#include "Button.h"

Button::Button() : UIElement(*ResourceManager::getTexture("Button")) {

}

Button::Button(const char* labelString) : Button() {
	addChild(new Label(labelString));
}
