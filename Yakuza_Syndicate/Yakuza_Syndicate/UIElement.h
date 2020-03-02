#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct UIVisualSettings{
	sf::Color rectFillColor = sf::Color::White;
	sf::Color rectOutlineColor = sf::Color::Black;
	int rectOutlineThicknes = 0;

	sf::Color textFillColor = sf::Color::Black;
	sf::Color textOutlineColor = sf::Color::Black;
	int textSize = 30;
	int textOutlineThickness = 0;
	std::string textFont = "C:/Windows/Fonts/Arial.ttf";
};

class UIElement : public sf::Drawable {
private:
	std::vector<UIElement*> children;
	UIElement* parent;
	sf::Vector2f offsetToParrent;

public:
	UIElement(const UIVisualSettings& visuals = {});
	UIElement(const UIElement& other);
	virtual ~UIElement();

	UIElement* addChild(UIElement* elem, sf::Vector2f offset = sf::Vector2f(0, 0));

	virtual sf::Vector2f getPosition() const = 0;
	virtual void setPosition(sf::Vector2f position) = 0;

	virtual sf::FloatRect getBounds() const = 0;
	
	virtual void setVisuals(const UIVisualSettings& visuals);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

protected:
	void setChildrenPosition(sf::Vector2f parentPosition);
	void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
};