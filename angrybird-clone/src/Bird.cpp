#include "Bird.hpp"
#include <iostream>
using namespace std;
using namespace sf;

Bird::Bird(float startX, float startY) :
    initialPosition(startX, startY), flying(false) 
{
    shape.setRadius(20.f);
    shape.setFillColor(Color::Red);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(initialPosition);
    shape.setOutlineThickness(0);

    if (!texture.loadFromFile("src/bird.png")) {
        cerr << "Error: Could not load bird.png!\n";
        shape.setOutlineThickness(2);
        shape.setOutlineColor(Color::Black);
    } else {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        sprite.setScale(80.f / texture.getSize().x, 80.f / texture.getSize().y);
        sprite.setPosition(initialPosition);
        shape.setRadius(sprite.getGlobalBounds().width / 2.f);
        shape.setOrigin(shape.getRadius(), shape.getRadius());
        shape.setPosition(initialPosition);
        shape.setFillColor(Color::Transparent);
    }
    velocity = {0.f, 0.f};
}

void Bird::launch(float initialVelX, float initialVelY) {
    if (!flying) {
        velocity = {initialVelX, initialVelY};
        flying = true;
    }
}

void Bird::update(Time dt) {
    if (flying) {
        velocity.y += gravity * dt.asSeconds();
        sprite.move(velocity * dt.asSeconds());
        shape.move(velocity * dt.asSeconds());
        if (shape.getPosition().y + shape.getRadius() > 600.f) {
            shape.setPosition(shape.getPosition().x, 600.f - shape.getRadius());
            sprite.setPosition(shape.getPosition());
            velocity.y = 0;
            flying = false;
        }
    }
}

void Bird::draw(RenderWindow& window) {
    if (texture.getSize().x > 0 && texture.getSize().y > 0)
        window.draw(sprite);
    else
        window.draw(shape);
}

void Bird::reset(float startX, float startY) {
    shape.setPosition(startX, startY);
    sprite.setPosition(startX, startY);
    velocity = {0.f, 0.f};
    flying = false;
}

Vector2f Bird::getPosition() const {
    return shape.getPosition();
}

FloatRect Bird::getBounds() const {
    return shape.getGlobalBounds();
}

bool Bird::isFlying() const {
    return flying;
}
