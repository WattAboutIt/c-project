#ifndef BIRD_HPP
#define BIRD_HPP

#include <SFML/Graphics.hpp>
using namespace sf;

class Bird {
public:
    Bird(float startX, float startY);
    void launch(float initialVelX, float initialVelY);
    void update(Time deltaTime);
    void draw(RenderWindow& window);
    void reset(float startX, float startY);
    Vector2f getPosition() const;
    FloatRect getBounds() const;
    bool isFlying() const;

private:
    Texture texture;
    Sprite sprite;
    CircleShape shape;
    Vector2f velocity, initialPosition;
    bool flying;
    const float gravity = 980.f;
};

#endif
