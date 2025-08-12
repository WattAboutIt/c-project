#ifndef PIG_HPP
#define PIG_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Game;

class Pig {
public:
    static void loadResources();
    static Texture pigTexture;
    static SoundBuffer pigHitSoundBuffer;
    static bool texturesLoaded;
    static bool soundsLoaded;

    Pig(float x, float y);
    void draw(RenderWindow& window);
    FloatRect getBounds() const;
    bool isAlive() const;
    bool isSoundPlaying() const;
    void hit(Game* game);

private:
    Sprite sprite;
    CircleShape shape;
    bool alive;
    Sound hitSound;
};

#endif
