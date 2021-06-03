#include "Game.hpp"
#include<iostream>
#include<string>  
using namespace std;

void Game::initVariables(){
    // window variables
    this->windowWidth = 800;
    this->windowHeight = 600;
    this->navBarHeight = 50;
    
    // time beetwen rendering fallingObjects
    this->flyingObjectTimerBegin = 0;
    this->flyingObjectTimerEnd = 260;

    this->maxFlyingObjects = 10;
    this->points = 0;
    this->endGame = true;

    
    if(this->MyFont.loadFromFile("fonts/Mermaid1001.ttf")){
        this->MyText.setFont(this->MyFont);
        this->MyText.setFillColor(sf::Color::Black);

        this->buttonText.setFont(this->MyFont);
        this->buttonText.setString("Start game");
        this->buttonText.setPosition(sf::Vector2f(static_cast<float>(this->windowWidth / 2)-60, static_cast<float>(this->windowHeight / 2u)-25));
        this->buttonText.setFillColor(sf::Color::Black);
        cout << "Fonts loaded succesfully" << endl;
    } else {
        cout << "Error::Game::initVariables ---> font not found" << endl;
        this->endGame=true;
    }
}

void Game::initWindow(){
    
    this->window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), "Time Killing Game");

    this->window->setFramerateLimit(90);
}

void Game::initflyingObject(){
    this->flyingObject.setSize(sf::Vector2f(50.f,50.f));
    this->flyingObject.setFillColor(sf::Color::Black);
}

void Game::initBar(){
    // bar catch flying objects

    this->bar.setSize(sf::Vector2f(30.f,120.f));
    this->bar.setFillColor(sf::Color::Black);
    this->bar.setPosition(10.f, 200.f);
}

void Game::initButton(){
    // init restart button
    this->restartButton.setSize(sf::Vector2f(160.f,50.f));
    this->restartButton.setFillColor(sf::Color(41, 138, 49));
    this->restartButton.setPosition(static_cast<float>(this->windowWidth / 2u)-70, static_cast<float>(this->windowHeight / 2u)-25);
}


Game::Game(){
    // constructor

    this->initVariables();
    this->initWindow();
    this->initflyingObject();
    this->initBar();
    this->initButton();
}

Game::~Game(){
    // destructor

    delete this->window;
}

const bool Game::isRunning() const {
    // return true if window is open

    return this->window->isOpen();
}


void Game::poolEvents() {
    // listen for close window event

    while (this->window->pollEvent(this->event))
        {
            if (this->event.type == sf::Event::Closed)
                this->window->close();
            
        }
}

void Game::update() {
    // update all methods
    
    this->poolEvents();

    this->updateMousePosition();

    if(this->endGame == false){
        this->updateFlyingObject();
        this->updateText();
        this->barColisions();
        this->moveBar();
    } else {
        for(int i=0;i<this->array.size(); i++){
            this->array.erase(this->array.begin()+i);
        }
    }
    
}

void Game::render(){
    // create window and draw new elements witch new positions

    this->window->clear(sf::Color(41, 138, 49));

    if (this->endGame) {
        this->renderRestartButton();
        this->listenRestartButton();
    } else {
        this->renderFlyingObject();
        this->renderBar();
    }
    this->renderText();
    
    
    this->window->display();
};

void Game::updateMousePosition() {
    // read mouse postion reference to game window
    this->mousePosition = sf::Mouse::getPosition(*this->window);
    // convert Vector2i to Vector2f
    this->mouseView = this->window->mapPixelToCoords(this->mousePosition);
}

void Game::displayFlyingObject(){
    // generate flying object outside of screen and push it to the array

    this->flyingObject.setPosition(static_cast<float>(this->windowWidth + this->flyingObject.getSize().x),
                                    static_cast<float>( rand() % static_cast<int>(this->windowHeight - this->flyingObject.getSize().y - this->navBarHeight))+this->navBarHeight);
    
    this->array.push_back(this->flyingObject);
}

void Game::updateFlyingObject(){
    // handle maximum number of flying elements on screen

    if(this->array.size() < this->maxFlyingObjects){   
        
        if(this->flyingObjectTimerBegin >= this->flyingObjectTimerEnd){
            this->displayFlyingObject();
            this->flyingObjectTimerBegin = 0;
            
        } else {
            this->flyingObjectTimerBegin += 5;
        }
    }
    // move all flying elements to the left side of window
    // stop game if flying object touch the left border

    for(int i=0;i<this->array.size(); i++){
        array[i].move(-2.f, 0.f);

        if (this->array[i].getPosition().x < 0) {
            this->array.erase(this->array.begin()+i);
            
            this->endGame = true;
            
        }
        
    }
}

void Game::renderFlyingObject(){
    // draw all flying elements
    for(int i = 0; i<this->array.size();i++){
        this->window->draw(array[i]);
    }
}

void Game::renderBar(){
    // draw restart button

    this->window->draw(this->bar);
}

void Game::renderRestartButton(){
    // draw restart button with text

    this->window->draw(this->restartButton);
    this->window->draw(this->buttonText);
}

void Game::barColisions(){
    // checks if we caught the flying elements

    for(int i=0; i < this->array.size(); i++){
        if(this->bar.getGlobalBounds().intersects(this->array[i].getGlobalBounds())){
            this->array.erase(this->array.begin()+i);
            this->points++;
        }
    }
}

void Game::moveBar(){
    // move bar up and down to catch elements

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        if (this->bar.getPosition().y > this->navBarHeight){
            this->bar.move(0.f, -5.f);
        }
        
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (this->bar.getPosition().y < (this->windowHeight - this->bar.getSize().y)){
            this->bar.move(0.f, 5.f);
        }
        
    }
}

void Game::listenRestartButton(){
    // listen to restart button
    // reset number of points

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(this->restartButton.getGlobalBounds().contains(this->mouseView)){
                // init game again
                this->points = 0;
                this->endGame=false;
            }
            
        } 
}

void Game::renderText(){
    // draw points on screen

    this->window->draw(this->MyText);
}

void Game::updateText(){
    // update number of points

    this->MyText.setString("points: "+to_string(this->points));
}


