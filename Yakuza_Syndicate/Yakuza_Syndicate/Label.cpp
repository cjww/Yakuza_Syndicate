#include "Label.h"

Label::Label(const char* str) {
	font.loadFromFile("C:/windows/fonts/arial.ttf");
	text.setFont(font);
	text.setString(str);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw((UIElement)*this);
	target.draw(text);
}
