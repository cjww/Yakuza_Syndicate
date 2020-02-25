#pragma once
#include "UIElement.h"
#include "Label.h"

class Button : public UIElement {
private:

public:
	Button();
	Button(const char* labelString);
};