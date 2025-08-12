#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bird.hpp"
#include "Pig.hpp"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
using namespace sf;

enum class GameState {
    MainMenu,
    Playing,
    GameOver
};

class Game {
public:
    Game();
    void run();
    void playSound(const SoundBuffer& buffer, float volume);
    void addScore(int points);

private:
    RenderWindow window;
    Bird bird;
    vector<Pig> pigs;
    Clock clock;
    GameState currentGameState;

    bool mousePressed;
    Vector2f mouseClickPos, mouseReleasePos;

    Font font;
    Text titleText, startText;

    vector<Sound> soundQueue;

    bool pendingLevelReset;
    Clock levelResetTimer;

    int score;
    Text scoreText;
    void updateScoreText();

    void processEvents();
    void update(Time deltaTime);
    void render();
    void checkCollisions();
    void resetLevel();

    void handleMainMenuInput(Event& event);
    void updateMainMenu(Time deltaTime);
    void drawMainMenu();
};

#endif
