#pragma once
#include "Window.hpp"
#include "Utility.hpp"

class WindowMain : public Window
{
    public:
        //Constructor for WindowMain class
        WindowMain();

        //draw function
        void drawAll();
        void drawButtons();
        void drawMiddleLine();
        void drawEquation();
        void drawTextsLeftPanel();

        //getter function 
        void preparePlot();
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
        //button texture to plot 
        sf::Texture button_texture_plot_;
        //kaya equation image 
        sf::Texture equation_texture_;
        //background image 
        sf::Texture background_texture_;
};