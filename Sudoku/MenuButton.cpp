#include "MenuButton.h"

#include <SFML/Graphics/RenderTarget.hpp>

//constructorul clasei MenuButton
MenuButton::MenuButton(float x, float y, float width, float height, const sf::Font& font, const std::string& text, ButtonFunction function){
	setSize(sf::Vector2f(width, height));
	setPosition(sf::Vector2f(x, y));
	setOutlineThickness(1);
	setOutlineColor(sf::Color::Black);

	m_idleColor = sf::Color(135, 206, 250);
	m_hoverColor = sf::Color(0, 191, 255);
	m_activeColor = m_idleColor;
	setFillColor(m_activeColor);
	
	m_font = font;
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setFillColor(sf::Color::Black);
	m_text.setCharacterSize(18);

	m_text.setPosition(
		getPosition().x + getGlobalBounds().width / 3.f  - m_text.getGlobalBounds().width / 4,
		getPosition().y + getGlobalBounds().height / 3.f - m_text.getGlobalBounds().height / 4
	);

	m_buttonFunction = function;
}
//functia care returneaza functia asociata butonului
MenuButton::ButtonFunction MenuButton::getFunction(){
	return m_buttonFunction;
}
//functia de desenare
void MenuButton::draw(sf::RenderTarget* target, sf::RenderStates states) const{
	target->draw(*this, states);
	target->draw(m_text);
}
//functia de actualizare a starii butonului
void MenuButton::update(bool isHovered) {
	if (isHovered)
		m_activeColor = m_hoverColor;
	else
		m_activeColor = m_idleColor;
	setFillColor(m_activeColor);
}