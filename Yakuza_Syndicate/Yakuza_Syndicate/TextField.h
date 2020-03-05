#pragma once
#include "Button.h"

class TextField : public Button {
private:
	bool focused;
	std::string string;
public:
	TextField(const char* labelString, sf::Vector2f size, const UIVisualSettings& visuals = {});
	
	void handleInput(const sf::Event& e);

	void setFocused(bool focus);

	std::string getText() const;
	void setText(const std::string& string);

};