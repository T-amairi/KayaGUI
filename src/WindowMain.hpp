#pragma once
#include "Window.hpp"
#include "Utility.hpp"

class WindowMain : public Window
{
    public:
        //Constructor for WindowMain class
        WindowMain();

        //draw function
        void drawButtons();

        //getter function 
        void preparePlot();
        std::pair<PlotData, PlotData> loadData(std::string path);
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
};