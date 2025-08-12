// src/Pig.hpp
#ifndef PIG_HPP
#define PIG_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game; // Forward declaration of the Game class

class Pig {
public:
    // Load static resources once for all Pig instances
    static void loadResources();
    // Static members to hold shared resources
    static sf::Texture pigTexture;
    static sf::SoundBuffer pigHitSoundBuffer;
    static bool texturesLoaded;
    static bool soundsLoaded;

    Pig(float x, float y);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isAlive() const;
    bool isSoundPlaying() const;
    void hit(Game* game); // Pass a pointer to the game object to allow score updates

private:
    sf::Sprite sprite;
    sf::CircleShape shape; // Collision shape
    bool alive;
    sf::Sound hitSound;
};

#endif // PIG_HPP
