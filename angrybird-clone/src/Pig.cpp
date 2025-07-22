// // Pig.cpp
// #include "Pig.hpp"

// Pig::Pig(float x, float y) :
//     alive(true)
// {
//     shape.setRadius(15.0f);
//     shape.setFillColor(sf::Color::Green);
//     shape.setOrigin(shape.getRadius(), shape.getRadius());
//     shape.setPosition(x, y);
// }

// void Pig::draw(sf::RenderWindow& window) {
//     if (alive) {
//         window.draw(shape);
//     }
// }

// sf::FloatRect Pig::getBounds() const {
//     return shape.getGlobalBounds();
// }

// bool Pig::isAlive() const {
//     return alive;
// }

// void Pig::hit() {
//     alive = false;
//     // Optionally change color or add explosion effect here
// }

//Sound effect added 
// Pig.hpp
#ifndef PIG_HPP
#define PIG_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Pig {
public:
    Pig(float x, float y);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isAlive() const;
    void hit(); // Mark pig as hit/destroyed and play sound

private:
    sf::CircleShape shape;
    bool alive;

    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;
};

#endif // PIG_HPP
