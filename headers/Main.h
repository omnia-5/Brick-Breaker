#include "./GameGrid.h"
#include "./LevelDesignGrid.h"
#include "./ColorPicker.h"
#include "./Button.h"
#include "./TimeManager.h"
#include "./LevelSelector.h"
#include "./AnimatedTitle.h"
#include "./Player.h"
#include "./Ball.h"
#include "./Storage.h"

Storage storage;

sf::Mutex mainMenuMutex, gameMutex, instructionsMutex,
leaderBoardMutex, creditsMutex, playMutex, chooseLevelMutex,
enterYourNameMutex, winMutex, loseMutex, pauseMutex, levelDesignMutux;

const sf::VideoMode VIDEOMODE = sf::VideoMode((unsigned int)APP_SIZE.x, (unsigned int)APP_SIZE.y);
std::string TITLE = "Brick-Detonator";

bool isLoadingCustomLevel = false;
std::string customLevelPath = "";

void switchWindows(sf::Mutex& mutex, sf::RenderWindow& window, sf::Thread& thread) {
    mutex.lock();
    window.close();
    thread.launch();
    mutex.unlock();
};

void mainMenu();
void enterYourName();
void credits();
void leaderBoard();
void chooseLevel();
void levelDesign();
void play();
void pauseScreen();
void gameLoop();
void instructions();
void win();
void lose();

struct PlayerName {
    std::string text;
    int length;

    PlayerName() :text(""), length(0) {};
};

PlayerName playerName;