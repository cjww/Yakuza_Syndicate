#pragma once
#include "UIElement.h"
#include "Label.h"
#include "Pane.h"

class Button : public Pane {
private:
	Label* label;
	float paddingLeft;
	float paddingTop;

public:
	Button(const UIVisualSettings& visuals = {});
	Button(const char* labelString, const UIVisualSettings& visuals = {});
	Button(const char* labelString, sf::Vector2f size, const UIVisualSettings& visuals = {});

	virtual void setPosition(sf::Vector2f position);

	virtual bool contains(sf::Vector2f point);

	virtual void setVisuals(const UIVisualSettings& visuals) override;

	Label* getLabel() const;
};