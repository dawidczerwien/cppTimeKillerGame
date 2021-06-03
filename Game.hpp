#ifndef _Game_HPP

#define _Game_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
    private:
        // window variables
        int windowWidth;
        int windowHeight;
        int navBarHeight;
        sf::RenderWindow* window;
        sf::Event event;
        
        sf::RectangleShape flyingObject;

        // bar catch flying objects
        sf::RectangleShape bar;

        // button if endGame
        sf::RectangleShape restartButton;

        // mouse listening
        sf::Vector2i mousePosition;
        sf::Vector2f mouseView;

        // https://www.tutorialspoint.com/difference-between-std-vector-and-std-array-in-cplusplus
        std::vector<sf::RectangleShape> array;
        
        // timer between displaing flying objects
        int flyingObjectTimerBegin;
        int flyingObjectTimerEnd;

        // maximum number of displayed elements on screen
        int maxFlyingObjects;
        
        bool endGame;

        // points variable
        // font for text
        // text displaying points
        // button text displaing restart game
        int points;
        sf::Font MyFont;
        sf::Text MyText;
        sf::Text buttonText;
        
        // init methods
        void initVariables();
        void initWindow();
        void initflyingObject();
        void initBar();
        void initButton();
    public:
        Game();
        ~Game();
        const bool isRunning() const;

        //Functions declarations
        void poolEvents();

        void update();
        void render();

        void displayFlyingObject();
        void updateFlyingObject();
        void renderFlyingObject();

        void renderText();
        void updateText();

        void renderBar();
        void barColisions();
        void moveBar();

        void updateMousePosition();

        void renderRestartButton();
        void listenRestartButton();
};
#endif