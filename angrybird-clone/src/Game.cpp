#include "Game.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace sf;

Game::Game() :
    window(VideoMode({800, 600}), "Angry Birds Clone"),
    bird(100.f, 450.f),
    mousePressed(false),
    currentGameState(GameState::MainMenu),
    pendingLevelReset(false),
    score(0)
{
    window.setFramerateLimit(120);
    Pig::loadResources();

    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
        cerr << "Error loading font.\n";

    titleText.setFont(font);
    titleText.setString("Angry Birds Clone");
    titleText.setCharacterSize(50);
    titleText.setFillColor(Color::White);
    titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
    titleText.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 50);

    startText.setFont(font);
    startText.setString("Press SPACE to Start");
    startText.setCharacterSize(30);
    startText.setFillColor(Color::Yellow);
    startText.setOrigin(startText.getLocalBounds().width / 2, startText.getLocalBounds().height / 2);
    startText.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 50);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10.f, 10.f);
    updateScoreText();
}

void Game::playSound(const SoundBuffer& buffer, float volume) {
    Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(volume);
    sound.play();
    soundQueue.push_back(move(sound));
}

void Game::run() {
    while (window.isOpen()) {
        Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) window.close();

        switch (currentGameState) {
            case GameState::MainMenu:
                handleMainMenuInput(event);
                break;
            case GameState::Playing:
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                    mousePressed = true;
                    mouseClickPos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                }
                if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && mousePressed) {
                    mouseReleasePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    Vector2f launchVector = mouseClickPos - mouseReleasePos;
                    float powerMultiplier = 3.f;
                    bird.launch(launchVector.x * powerMultiplier, launchVector.y * powerMultiplier);
                    mousePressed = false;
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {resetLevel(); score = 0; updateScoreText();}
                break;
            case GameState::GameOver:
                break;
        }
    }
}

void Game::update(Time deltaTime) {
    switch (currentGameState) {
        case GameState::MainMenu:
            updateMainMenu(deltaTime);
            break;
        case GameState::Playing:
            bird.update(deltaTime);
            checkCollisions();

            soundQueue.erase(remove_if(soundQueue.begin(), soundQueue.end(),
                [](const Sound& s){ return s.getStatus() == Sound::Stopped; }),
                soundQueue.end());

            if (bird.isFlying() && bird.getPosition().y >= 500.f) {
                cout << "Bird hit the ground. Resetting level and score.\n";
                resetLevel();
                score = 0;
                updateScoreText();
            }

            if (!pendingLevelReset) {
                bool allPigsDestroyed = all_of(pigs.begin(), pigs.end(),
                    [](const Pig& pig){ return !pig.isAlive(); });
                if (allPigsDestroyed) {
                    pendingLevelReset = true;
                    levelResetTimer.restart();
                    cout << "All pigs destroyed! Waiting to reset level...\n";
                }
            } else if (levelResetTimer.getElapsedTime().asSeconds() > 1.2f) {
                cout << "Level complete! Resetting now.\n";
                resetLevel();
                pendingLevelReset = false;
            }
            break;
        case GameState::GameOver:
            break;
    }
}

void Game::render() {
    window.clear(Color(100, 149, 237));

    switch (currentGameState) {
        case GameState::MainMenu:
            drawMainMenu();
            break;
        case GameState::Playing: {
            RectangleShape slingshotBase({50.f, 150.f});
            slingshotBase.setFillColor(Color(139, 69, 19));
            slingshotBase.setPosition(80.f, 450.f);
            window.draw(slingshotBase);

            RectangleShape ground({800.f, 100.f});
            ground.setFillColor(Color(100, 70, 0));
            ground.setPosition(0.f, 500.f);
            window.draw(ground);

            if (mousePressed && !bird.isFlying()) {
                Vertex line[] = {
                    Vertex(bird.getPosition(), Color::Black),
                    Vertex(mouseClickPos, Color::Black)
                };
                window.draw(line, 2, Lines);
            }

            bird.draw(window);
            for (auto& pig : pigs) pig.draw(window);
            window.draw(scoreText);
            break;
        }
        case GameState::GameOver:
            break;
    }

    window.display();
}

void Game::checkCollisions() {
    if (!bird.isFlying()) return;
    for (auto& pig : pigs) {
        if (pig.isAlive() && bird.getBounds().intersects(pig.getBounds())) {
            pig.hit(this);
            bird.reset(100.f, 450.f);
            cout << "Pig hit!\n";
            break;
        }
    }
}

void Game::resetLevel() {
    bird.reset(100.f, 450.f);
    pigs.clear();
    pigs.emplace_back(600.f, 480.f);
    pigs.emplace_back(650.f, 480.f);
    pigs.emplace_back(700.f, 480.f);
    cout << "Level reset. Destroy the pigs!\n";
}

void Game::handleMainMenuInput(Event& event) {
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
        currentGameState = GameState::Playing;
        resetLevel();
    }
}

void Game::updateMainMenu(Time) {}

void Game::drawMainMenu() {
    window.clear(Color::Black);
    window.draw(titleText);
    window.draw(startText);
}

void Game::addScore(int points) {
    score += points;
    updateScoreText();
}

void Game::updateScoreText() {
    stringstream ss;
    ss << "Score: " << score;
    scoreText.setString(ss.str());
}
