// src/Game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Required for sf::Sound and sf::SoundBuffer
#include "Bird.hpp"
#include "Pig.hpp"
#include <vector>
#include <algorithm> // Required for std::remove_if
#include <string>

// Define game states
enum class GameState {
    MainMenu,
    Playing,
    GameOver // You can expand this later
};

class Game {
public:
    Game();
    void run();
    void playSound(const sf::SoundBuffer& buffer, float volume); // New: Method to play sounds
    void addScore(int points); // NEW: Function to add points to the score

private:
    sf::RenderWindow window;
    Bird bird;
    std::vector<Pig> pigs;
    sf::Clock clock;
    GameState currentGameState;

    bool mousePressed;
    sf::Vector2f mouseClickPos;
    sf::Vector2f mouseReleasePos;

    // For Main Menu
    sf::Font font;
    sf::Text titleText;
    sf::Text startText;

    // For sound management
    std::vector<sf::Sound> soundQueue;

    // For delayed level reset
    bool pendingLevelReset;
    sf::Clock levelResetTimer;

    // NEW: For score
    int score;
    sf::Text scoreText;
    void updateScoreText(); // NEW: Function to update the score display

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void checkCollisions();
    void resetLevel();

    // Methods for handling main menu
    void handleMainMenuInput(sf::Event& event);
    void updateMainMenu(sf::Time deltaTime);
    void drawMainMenu();
};

#endif // GAME_HPP
