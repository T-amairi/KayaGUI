#pragma once
#include "Window.hpp"
#include "CheckPlot.hpp"
#include "TextField.hpp"
#include "CheckCompute.hpp"

class WindowMain : public Window
{
    public:
        //Constructor for WindowMain class
        WindowMain();

        //prepare all figures and classes to be drawn
        void preparePlot();
        void prepareCompute();
        void prepareTextFields();
        void prepareTextsLeftPanel();
        void prepareTextsRightPanel();
        void prepareTextures();
        void prepareSprites();
        void prepareLegend();

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
        sf::Vector2f getMousePos() const;
        std::vector<double> getInput() const;

        //Open the main window 
        void run() override;

    private:
        //font
        sf::Font font_;
        //setting for antialiasing level
        sf::ContextSettings settings_;
        //for handling all the plot window
        CheckPlot checkplot_;
        //for handling all the plot window
        CheckCompute checkcompute_;
        //vector for all the texture to be used
        std::vector<sf::Texture> textures_;
        //vector for all the sprite to be drawn
        std::vector<sf::Sprite> sprites_;
        //vector for all the text to be drawn
        std::vector<sf::Text> texts_;
        //vector for all the text boxes to be drawn
        std::vector<std::shared_ptr<TextField>> fields_;
};