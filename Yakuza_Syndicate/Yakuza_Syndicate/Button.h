#pragma once
#include "UIElement.h"
#include "Label.h"
#include "Pane.h"
#include "Image.h"

class Button : public Pane {
private:
	Label* label;
	float paddingLeft;
	float paddingTop;

	Image* image;
public:
	Button(const UIVisualSettings& visuals = {});
	Button(const char* labelString, const UIVisualSettings& visuals = {});
	Button(const char* labelString, sf::Vector2f size, const UIVisualSettings& visuals = {});
	Button(Image* image, const UIVisualSettings& visuals = {});

	virtual void setPosition(sf::Vector2f position);

};