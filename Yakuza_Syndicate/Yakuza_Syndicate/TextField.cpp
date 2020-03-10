#include "TextField.h"

TextField::TextField(const char* labelString, sf::Vector2f size, const UIVisualSettings& visuals) : Button(labelString, size, visuals){
	focused = false;
	
}

void TextField::handleInput(const sf::Event& e) {
	if (focused) {
		if (e.text.unicode < 128) {
			char c = e.text.unicode;
			if (c == 8) {
				if (string.size() > 0) {
					string.resize(string.size() - 1);
				}
			}
			else {
				string.push_back(c);
			}
			setText(string);
		}
	}
}

void TextField::setFocused(bool focus) {
	this->focused = focus;
	//getLabel()->setPosition(getPosition() + sf::Vector2f(50, 5));

}

std::string TextField::getText() const {
	return getLabel()->getString();

}

void TextField::setText(const std::string& string) {
	this->string = string;
	getLabel()->setString(string);
	getLabel()->setPosition(
		getPosition()
		+ sf::Vector2f(getBounds().width / 2, 5)
		- sf::Vector2f(getLabel()->getBounds().width / 2, 0));
}
