#include "./headers/Main.h"

void mainMenu() {
    mainMenuMutex.lock();
    sf::RenderWindow mainMenuWindow(VIDEOMODE, TITLE + " - Main Menu");

    sf::Thread gameThread(&gameLoop),
        instructionsThread(&instructions), leaderBoardThread(&leaderBoard),
        creditsThread(&credits), playThread(&play), levelDesignThread(&levelDesign);

    Title title("Brick Detonator", sf::Vector2f(450, 10), 64, "Joystick-5KjV");

    Button playButton(sf::Vector2f(600, 140), sf::Vector2f(96, 48), "Play");
    playButton.setCallBack([&]() {switchWindows(playMutex, mainMenuWindow, playThread); });
    Button desigenLevelButton(sf::Vector2f(550, 220), sf::Vector2f(224, 48), "Level Design");
    desigenLevelButton.setCallBack([&]() {switchWindows(levelDesignMutux, mainMenuWindow, levelDesignThread); });
    Button instructionButton(sf::Vector2f(550, 300), sf::Vector2f(224, 48), "Instruction");
    instructionButton.setCallBack([&]() {switchWindows(instructionsMutex, mainMenuWindow, instructionsThread); });
    Button leaderboardButton(sf::Vector2f(545, 380), sf::Vector2f(240, 48), "Leader Board");
    leaderboardButton.setCallBack([&]() {switchWindows(leaderBoardMutex, mainMenuWindow, leaderBoardThread); });
    Button creditsButton(sf::Vector2f(590, 460), sf::Vector2f(128, 48), "Credit");
    creditsButton.setCallBack([&]() {switchWindows(creditsMutex, mainMenuWindow, creditsThread); });
    Button exitButton(sf::Vector2f(610, 530), sf::Vector2f(80, 48), "Exit");
    exitButton.setCallBack([&]() {mainMenuWindow.close(); });


    // run the program as long as the window is open
    while (mainMenuWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (mainMenuWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                mainMenuWindow.close();

            playButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mainMenuWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            instructionButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mainMenuWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            leaderboardButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mainMenuWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            desigenLevelButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mainMenuWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            creditsButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mainMenuWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            exitButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(mainMenuWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));

        }
        // clear the windowr
        mainMenuWindow.clear();
        // draw everything here...
        title.draw(&mainMenuWindow);
        playButton.draw(&mainMenuWindow);
        instructionButton.draw(&mainMenuWindow);
        leaderboardButton.draw(&mainMenuWindow);
        desigenLevelButton.draw(&mainMenuWindow);
        creditsButton.draw(&mainMenuWindow);
        exitButton.draw(&mainMenuWindow);
        // end the current frame
        mainMenuWindow.display();
    }
    mainMenuMutex.unlock();
}

void play() {
    playMutex.lock();
    sf::RenderWindow playWindow(VIDEOMODE, TITLE + " - Play");

    sf::Thread mainMenuThread(&mainMenu), enterYourNameThread(&enterYourName),
        chooseLevelThread(&chooseLevel);

    Title title("Play Method", sf::Vector2f(500, 50), 64, "Joystick-5KjV");

    Button playStandered(sf::Vector2f(550, 240), sf::Vector2f(224, 48), "Standerd");
    playStandered.setCallBack([&]() {switchWindows(enterYourNameMutex, playWindow, enterYourNameThread); });
    Button playCustom(sf::Vector2f(530, 320), sf::Vector2f(264, 48), "Custom Levles");
    playCustom.setCallBack([&]() {switchWindows(chooseLevelMutex, playWindow, chooseLevelThread); });
    Button backButton(sf::Vector2f(610, 400), sf::Vector2f(80, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, playWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (playWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (playWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                playWindow.close();

            playStandered.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(playWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            playCustom.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(playWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(playWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));

        }
        // clear the windowr
        playWindow.clear();
        // draw everything here...
        title.draw(&playWindow);
        playStandered.draw(&playWindow);
        playCustom.draw(&playWindow);
        backButton.draw(&playWindow);
        // end the current frame
        playWindow.display();
    }
    playMutex.unlock();
};

void enterYourName() {
    enterYourNameMutex.lock();
    sf::RenderWindow enterYourNameWindow(VIDEOMODE, TITLE + " - Enter Your Name");

    sf::Thread mainMenuThread(&mainMenu), gameLoopThread(&gameLoop);

    Title title("Enter Your Name", sf::Vector2f(500, 30), 64, "Joystick-5KjV");
    Title subTitle("* 10 characters max", sf::Vector2f(540, 100), 24, "Joystick-5KjV");
    Title userInput(playerName.text, sf::Vector2f(320, 200), 48, "Joystick-5KjV");

    sf::Clock clock;
    sf::Time textEffectTime;
    bool showCursor = true;

    Button playButton(sf::Vector2f(1100, 150), sf::Vector2f(96, 48), "Play");
    playButton.setCallBack([&]() {switchWindows(gameMutex, enterYourNameWindow, gameLoopThread); });
    Button backButton(sf::Vector2f(1100, 250), sf::Vector2f(96, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, enterYourNameWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (enterYourNameWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (enterYourNameWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                // "close requested" event: we close the window
                enterYourNameWindow.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!playerName.text.empty()) {
                        playerName.text.pop_back();
                        playerName.length--;
                    }
                }
                if (std::isprint(event.text.unicode)) std::cout << "menu SFX\n";
                break;
            case sf::Event::TextEntered:
                if (playerName.length < 10 && std::isprint(event.text.unicode)) {
                    playerName.text += event.text.unicode;
                    playerName.length++;
                }
                break;
            };
            playButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(enterYourNameWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(enterYourNameWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
        }

        textEffectTime += clock.restart();

        if (textEffectTime >= sf::seconds(0.5f)) {
            showCursor = !showCursor;
            textEffectTime = sf::Time::Zero;
        }
        userInput.updateContent(playerName.text + (showCursor ? "|" : " "));

        // clear the windowr
        enterYourNameWindow.clear();
        // draw everything here...
        title.draw(&enterYourNameWindow);
        subTitle.draw(&enterYourNameWindow);
        userInput.draw(&enterYourNameWindow);
        playButton.draw(&enterYourNameWindow);
        backButton.draw(&enterYourNameWindow);
        // end the current frame
        enterYourNameWindow.display();
    }
    enterYourNameMutex.unlock();
}

void instructions() {
    instructionsMutex.lock();
    sf::RenderWindow instructionsWindow(VIDEOMODE, TITLE + " - Instructions");
    TimeManager timeManager;

    sf::Thread mainMenuThread(&mainMenu);

    AnimatedTitle title("instructions");

    Button backButton(sf::Vector2f(1100, 150), sf::Vector2f(96, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, instructionsWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (instructionsWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (instructionsWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                // "close requested" event: we close the window
                instructionsWindow.close();
                break;
            };

            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(instructionsWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));

        }

        title.update(timeManager.getDeltaTime());

        // clear the windowr
        instructionsWindow.clear();
        // draw everything here...
        title.draw(&instructionsWindow);
        backButton.draw(&instructionsWindow);
        // end the current frame
        timeManager.update(); // Call fps to be updated every frame otherwise it will always be 0
        instructionsWindow.display();
    }
    instructionsMutex.unlock();
};

void leaderBoard() {
    leaderBoardMutex.lock();
    sf::RenderWindow leaderBoardWindow(VIDEOMODE, TITLE + " - Leader Board");

    sf::Thread mainMenuThread(&mainMenu);
    //storage.getStringLeaderBoard();
    Title title(storage.getStringLeaderBoard(), sf::Vector2f(APP_SIZE.x / 3, 50), 56, "Joystick-5KjV");

    Button backButton(sf::Vector2f(1100, 150), sf::Vector2f(96, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, leaderBoardWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (leaderBoardWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (leaderBoardWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                // "close requested" event: we close the window
                leaderBoardWindow.close();
                break;
            };

            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(leaderBoardWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));

        }

        // clear the windowr
        leaderBoardWindow.clear();
        // draw everything here...
        title.draw(&leaderBoardWindow);
        backButton.draw(&leaderBoardWindow);
        // end the current frame
        leaderBoardWindow.display();
    }
    leaderBoardMutex.unlock();
};

void credits() {
    creditsMutex.lock();
    sf::RenderWindow creditsWindow(VIDEOMODE, TITLE + " - Credits");
    TimeManager timeManager;

    sf::Thread mainMenuThread(&mainMenu);

    AnimatedTitle title("credits");

    Button backButton(sf::Vector2f(1100, 150), sf::Vector2f(96, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, creditsWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (creditsWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (creditsWindow.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                // "close requested" event: we close the window
                creditsWindow.close();
                break;
            };

            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(creditsWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));

        }

        title.update(timeManager.getDeltaTime());

        // clear the windowr
        creditsWindow.clear();
        // draw everything here...
        title.draw(&creditsWindow);
        backButton.draw(&creditsWindow);
        // end the current frame
        timeManager.update(); // Call fps to be updated every frame otherwise it will always be 0
        creditsWindow.display();
    }
    creditsMutex.unlock();
}

void chooseLevel() {
    chooseLevelMutex.lock();
    sf::RenderWindow chooseLevelWindow(VIDEOMODE, TITLE + " - Choose Level");
    TimeManager timeManager;

    sf::Thread mainMenuThread(&mainMenu), enterYourNameThread(&enterYourName);

    Title title("Choose Level", sf::Vector2f(32, 10), 32, "Joystick-5KjV");

    LevelSelector levelSelector("./levels/custom/");

    Button nextButton(sf::Vector2f(1100, 150), sf::Vector2f(96, 48), "Next");
    nextButton.setCallBack([&]() {
        isLoadingCustomLevel = true;
        customLevelPath = levelSelector.getSelectedLevel().path;
        timeManager.sleepFor(100);
        switchWindows(enterYourNameMutex, chooseLevelWindow, enterYourNameThread);
    });
    Button backButton(sf::Vector2f(1100, 250), sf::Vector2f(96, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, chooseLevelWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (chooseLevelWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (chooseLevelWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                chooseLevelWindow.close();
            levelSelector.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(chooseLevelWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            nextButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(chooseLevelWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(chooseLevelWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
        }
        // clear the windowr
        chooseLevelWindow.clear();
        // draw everything here...
        title.draw(&chooseLevelWindow);
        levelSelector.draw(&chooseLevelWindow);
        nextButton.draw(&chooseLevelWindow);
        backButton.draw(&chooseLevelWindow);
        // end the current frame
        timeManager.update(); // Call fps to be updated every frame otherwise it will always be 0
        chooseLevelWindow.display();
    }
    chooseLevelMutex.unlock();
}

void levelDesign() {
    levelDesignMutux.lock();
    sf::RenderWindow levelDesignWindow(VIDEOMODE, TITLE + " - Level Desigen");
    Title title("Level Maker", sf::Vector2f(32, 10), 32, "Joystick-5KjV");

    sf::Thread mainMenuThread(&mainMenu);

    LevelDesignGrid grid;
    ColorPicker colorPicker(540, 1);
    Button saveButton(sf::Vector2f(1100, 550), sf::Vector2f(96, 48), "Save");
    saveButton.setCallBack([&]() {
        grid.saveSerializedGrid();
        grid.reset();
        switchWindows(mainMenuMutex, levelDesignWindow, mainMenuThread);
    });
    Button backButton(sf::Vector2f(1100, 620), sf::Vector2f(96, 48), "Back");
    backButton.setCallBack([&]() {
        grid.reset();
        switchWindows(mainMenuMutex, levelDesignWindow, mainMenuThread);
    });

    // run the program as long as the window is open
    while (levelDesignWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (levelDesignWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                levelDesignWindow.close();
            grid.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(levelDesignWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left), colorPicker.getSelectedColor());
            colorPicker.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(levelDesignWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            saveButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(levelDesignWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(levelDesignWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
        }
        // clear the windowr
        levelDesignWindow.clear();
        // draw everything here...
        grid.draw(&levelDesignWindow);
        colorPicker.draw(&levelDesignWindow);
        saveButton.draw(&levelDesignWindow);
        backButton.draw(&levelDesignWindow);
        title.draw(&levelDesignWindow);
        // end the current frame
        levelDesignWindow.display();
    }
    levelDesignMutux.unlock();
}

void pauseScreen() {
    pauseMutex.lock();
    sf::RenderWindow pauseScreenWindow(VIDEOMODE, TITLE + " - Game Paused");

    sf::Thread mainMenuThread(&mainMenu), gameLoopThread(&gameLoop);

    Title title("Game Paused", sf::Vector2f(500, 50), 64, "Joystick-5KjV");

    Button playStandered(sf::Vector2f(550, 240), sf::Vector2f(224, 48), "Resume");
    playStandered.setCallBack([&]() {switchWindows(gameMutex, pauseScreenWindow, gameLoopThread); });
    Button backButton(sf::Vector2f(610, 400), sf::Vector2f(80, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, pauseScreenWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (pauseScreenWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (pauseScreenWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                pauseScreenWindow.close();

            playStandered.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(pauseScreenWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(pauseScreenWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));

        }
        // clear the windowr
        pauseScreenWindow.clear();
        // draw everything here...
        title.draw(&pauseScreenWindow);

        playStandered.draw(&pauseScreenWindow);
        backButton.draw(&pauseScreenWindow);
        // end the current frame
        pauseScreenWindow.display();
    }
    pauseMutex.unlock();
};

void win() {
    winMutex.lock();
    sf::RenderWindow winScreenWindow(VIDEOMODE, TITLE + " - You Won!");

    sf::Thread mainMenuThread(&mainMenu);

    Title title("You Won!", sf::Vector2f(500, 50), 64, "Joystick-5KjV");

    Button backButton(sf::Vector2f(610, 400), sf::Vector2f(80, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, winScreenWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (winScreenWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (winScreenWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                winScreenWindow.close();

            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(winScreenWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));

        }
        // clear the windowr
        winScreenWindow.clear();
        // draw everything here...
        title.draw(&winScreenWindow);

        backButton.draw(&winScreenWindow);
        // end the current frame
        winScreenWindow.display();
    }
    winMutex.unlock();
};

void lose() {
    loseMutex.lock();
    sf::RenderWindow loseScreenWindow(VIDEOMODE, TITLE + " - You've Lost!");

    sf::Thread mainMenuThread(&mainMenu), gameLoopThread(&gameLoop);

    Title title("You've Lost!", sf::Vector2f(500, 50), 64, "Joystick-5KjV");

    Button playAgain(sf::Vector2f(550, 240), sf::Vector2f(224, 48), "Again");
    playAgain.setCallBack([&]() {switchWindows(gameMutex, loseScreenWindow, gameLoopThread); });

    Button backButton(sf::Vector2f(610, 400), sf::Vector2f(80, 48), "Back");
    backButton.setCallBack([&]() {switchWindows(mainMenuMutex, loseScreenWindow, mainMenuThread); });

    // run the program as long as the window is open
    while (loseScreenWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (loseScreenWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                loseScreenWindow.close();

            playAgain.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(loseScreenWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
            backButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(loseScreenWindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));

        }
        // clear the windowr
        loseScreenWindow.clear();
        // draw everything here...
        title.draw(&loseScreenWindow);

        playAgain.draw(&loseScreenWindow);
        backButton.draw(&loseScreenWindow);
        // end the current frame
        loseScreenWindow.display();
    }
    loseMutex.unlock();
};

void gameLoop() {
    gameMutex.lock();
    // create the window
    sf::RenderWindow gameLoopwindow(VIDEOMODE, TITLE + " - Game Loop");
    TimeManager timeManager;

    sf::Thread pauseScreenThread(&pauseScreen), winThread(&win), loseThread(&lose);

    GameGrid grid(9, 9);

    if (isLoadingCustomLevel) grid.loadFromFile(customLevelPath);

    Player player;
    Ball ball;

    bool gamePaused = false, whiteSpacesOnly = std::all_of(playerName.text.begin(), playerName.text.end(), isspace);
    playerName.text = (playerName.text == "" || whiteSpacesOnly) ? "Unknow" : playerName.text;

    Title scoreString("Score: ", sf::Vector2f(20, 20), 24, "Joystick-5KjV");
    Title livesString("Lives: ", sf::Vector2f(APP_SIZE.x -200, 20), 24, "Joystick-5KjV");
    Title playerNameString("Player Name: " + playerName.text, sf::Vector2f(APP_SIZE.x / 4, 20), 24, "Joystick-5KjV");
    Title FPSTitle("FPS: " + timeManager.getFPS(), sf::Vector2f(APP_SIZE.x - 500, 20), 24, "Joystick-5KjV");

    Button pauseButton(sf::Vector2f(1170, 10), sf::Vector2f(96, 48), "Pause");
    pauseButton.setCallBack([&]() {
        switchWindows(pauseMutex, gameLoopwindow, pauseScreenThread); 
        ball.reset();
        player.resetPosition();
    });

    // run the program as long as the window is open
    while (gameLoopwindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (gameLoopwindow.pollEvent(event)) {
            // "close requested" event: we close the window
            switch(event.type) {
            case sf::Event::Closed:
                // "close requested" event: we close the window
                gameLoopwindow.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space)
                    ball.start();
                break;
            }; 
            pauseButton.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(gameLoopwindow)), sf::Mouse::isButtonPressed(sf::Mouse::Left));
        }

        grid.update(timeManager.getDeltaTime(), &ball, &player);
        player.update(timeManager.getDeltaTime());
        ball.update(timeManager.getDeltaTime());

        if (grid.isFinished()) {
            switchWindows(winMutex, gameLoopwindow, winThread);
            storage.addData(playerName.text + std::to_string(player.getScore()));
        }

        if (player.isDead()) {
            switchWindows(loseMutex, gameLoopwindow, loseThread);
            storage.addData(playerName.text + std::to_string(player.getScore()));
            player.reset();
        }

        scoreString.updateContent("Score: " + std::to_string(player.getScore()));
        livesString.updateContent("Lives: X" + std::to_string(player.getLives()));
        FPSTitle.updateContent("FPS: " + std::to_string(timeManager.getFPS()));

        // clear the windowr
        gameLoopwindow.clear();
        // draw everything here...
        grid.draw(&gameLoopwindow);
        player.draw(&gameLoopwindow);
        ball.draw(&gameLoopwindow);

        scoreString.draw(&gameLoopwindow);
        livesString.draw(&gameLoopwindow);
        playerNameString.draw(&gameLoopwindow);
        FPSTitle.draw(&gameLoopwindow);

        pauseButton.draw(&gameLoopwindow);
        // end the current frame
        gameLoopwindow.display();
        timeManager.update(); // Call fps to be updated every frame otherwise it will always be 0
    }
    gameMutex.unlock();
};

int main() {
    mainMenu();
    return EXIT_SUCCESS;
}
