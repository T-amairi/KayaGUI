#pragma once
#include "Plot.hpp"
#include "Window.hpp"

class WindowPlot : public Window
{
    public:        
        //Constructor for WindowPlot class
        WindowPlot(variable name, std::string title, sf::Color axes_color, sf::Color scale_color, sf::Font font, 
        sf::Color font_color, std::string x_label, std::string y_label);

        //Open the window with a plot
        void run();

        //getter function
        std::string getPath() const;
        
        //setter function
        void addData(PlotData data);
        void setPosition(double x, double y);
        void setLinearReg();

        //load the data
        void loadData();

    private:
        //the plot to be shown in the window
        Plot plot_;
        //window title;
        std::string title_;
        //enum type
        variable name_;
        //coeff for the linear regression
        double a_;
        double b_;
};
