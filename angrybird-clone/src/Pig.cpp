#include "Pig.hpp"
#include <iostream>
#include "Game.hpp"

using namespace std;
using namespace sf;

Texture Pig::pigTexture;
SoundBuffer Pig::pigHitSoundBuffer;
bool Pig::texturesLoaded = false;
bool Pig::soundsLoaded = false;

void Pig::loadResources() {
    if (!texturesLoaded) {
        if (!pigTexture.loadFromFile("src/pig.png")) {
            cerr << "CRITICAL ERROR: Could not load static pig.png! All pigs will be green circles.\n";
            texturesLoaded = false;
        } else {
            texturesLoaded = true;
            cout << "DEBUG: Static pig.png loaded successfully.\n";
        }
    }

    if (!soundsLoaded) {
        if (!pigHitSoundBuffer.loadFromFile("src/pigdeath.wav")) {
            cerr << "CRITICAL ERROR: Could not load static pig_hit.wav! No pig hit sounds will play.\n";
            soundsLoaded = false;
        } else {
            soundsLoaded = true;
            cout << "DEBUG: Static .wav loaded successfully.\n";
        }
    }
}

Pig::Pig(float x, float y) : alive(true) {
    shape.setRadius(15.f);
    shape.setFillColor(Color::Green);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(x, y);
    shape.setOutlineThickness(0);

    if (texturesLoaded) {
        sprite.setTexture(pigTexture);
        sprite.setScale(60.f / pigTexture.getSize().x, 60.f / pigTexture.getSize().y);
        sprite.setOrigin(pigTexture.getSize().x / 2.f, pigTexture.getSize().y / 2.f);
        sprite.setPosition(x, y);

        shape.setRadius(sprite.getGlobalBounds().width / 2.f);
        shape.setOrigin(shape.getRadius(), shape.getRadius());
        shape.setPosition(x, y);
        shape.setFillColor(Color::Transparent);
    }

    if (soundsLoaded) {
        hitSound.setBuffer(pigHitSoundBuffer);
        hitSound.setVolume(100.f);
    }
}

void Pig::draw(RenderWindow& window) {
    if (!alive) return;
    if (texturesLoaded) window.draw(sprite);
    else window.draw(shape);
}

FloatRect Pig::getBounds() const {
    return shape.getGlobalBounds();
}

bool Pig::isAlive() const {
    return alive;
}

bool Pig::isSoundPlaying() const {
    return hitSound.getStatus() == Sound::Playing;
}

void Pig::hit(Game* game) {
    if (!alive) return;
    alive = false;
    if (game) game->addScore(10);
    if (soundsLoaded) {
        hitSound.play();
        cout << "DEBUG: Pig hit at (" << shape.getPosition().x << ", " << shape.getPosition().y << ") playing sound.\n";
    } else {
        cout << "DEBUG: Pig hit at (" << shape.getPosition().x << ", " << shape.getPosition().y << ") but no sound loaded.\n";
    }
}
