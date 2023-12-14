#include "DifficultyLevelButton.h"

#include <SFML/Graphics/RenderTarget.hpp>

// constructorul clasei DifficultyLevelButton
DifficultyLevelButton::DifficultyLevelButton(float x, float y, float radius, const sf::Font& font, sf::Texture* texture, int difficultyLevel) {
    // initializare variabile membru
    m_isChecked = false;
    m_texture = texture;
    m_font = font;
    m_difficultyLevel = static_cast<DifficultyLevel>(difficultyLevel);

    // setare text in functie de nivelul de dificultate
    switch (difficultyLevel) {
    case 0: m_text.setString("Easy"); break;
    case 1: m_text.setString("Medium"); break;
    case 2: m_text.setString("Hard"); break;
    default: break;
    }

    // configurare aspect text
    m_text.setCharacterSize(14);
    m_text.setFont(m_font);
    m_text.setPosition(
        x, y + radius * 2
    );

    m_text.setFillColor(sf::Color::Black);

    // configurare aspect buton
    setPosition(x, y);
    setRadius(radius);
    setFillColor(sf::Color(211, 211, 211, 125));
    setTexture(m_texture);
}

// destructorul clasei DifficultyLevelButton
DifficultyLevelButton::~DifficultyLevelButton() {
    delete m_texture;
}

// functia de desenare
void DifficultyLevelButton::draw(sf::RenderTarget* target, sf::RenderStates states) const {
    target->draw(*this, states);
    target->draw(m_text);
}

// functia de actualizare
void DifficultyLevelButton::update(bool isChecked) {
    if (isChecked) {
        setFillColor(sf::Color(211, 211, 211));
    }
    else {
        setFillColor(sf::Color(211, 211, 211, 125));
    }
}

// functia de verificare a starii de bifare
bool DifficultyLevelButton::isChecked() {
    return m_isChecked;
}
