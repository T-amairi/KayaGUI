#pragma once
#include "Window.hpp"
#include "CheckPlot.hpp"
#include "TextField.hpp"

class WindowMain : public Window
{
    public:
        //Constructor for WindowMain class
        WindowMain();

        //prepare all figures and classes to be drawn
        void preparePlot();
        void prepareTextFields();
        void prepareTextsLeftPanel();
        void prepareTextsRightPanel();
        void prepareTextures();
        void prepareSprites();

        //draw function
        void drawAll();
        void drawButtons();
        void drawImages();
        void drawTexts();
        void drawTextFields();

        //text fields
        void checkInput(sf::Event& event);
        void outlineColor(bool ifPressed);
 
        //getter function 
        std::pair<PlotData,PlotData> loadData(std::string path);
        sf::Vector2f getMousePos();

        //Open the main window 
        void run();

    private:
        //font
        sf::Font font_;
        //setting for antialiasing level
        sf::ContextSettings settings_;
        //for handling all the plot window
        CheckPlot checkplot_;
        //vector for all the texture to be used
        std::vector<sf::Texture> textures_;
        //vector for all the sprite to be drawn
        std::vector<sf::Sprite> sprites_;
        //vector for all the text to be drawn
        std::vector<sf::Text> texts_;
        //vector for all the text boxes to be drawn
        std::vector<std::shared_ptr<TextField>> fields_;
};