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
// Pig.cpp
#include "Pig.hpp"

Pig::Pig(float x, float y) :
    alive(true)
{
    shape.setRadius(15.0f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(x, y);

    // Load sound file
    if (!hitBuffer.loadFromFile("pig_hit.wav")) {
        // You can log or print an error, depending on your setup
        // For now, we’ll just leave it silent if loading fails
    } else {
        hitSound.setBuffer(hitBuffer);
    }
}

void Pig::draw(sf::RenderWindow& window) {
    if (alive) {
        window.draw(shape);
    }
}

sf::FloatRect Pig::getBounds() const {
    return shape.getGlobalBounds();
}

bool Pig::isAlive() const {
    return alive;
}

void Pig::hit() {
    alive = false;
    hitSound.play(); // Play sound when pig is hit
}
