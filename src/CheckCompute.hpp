#pragma once
#include "WindowPlot.hpp"
#include <memory>

class CheckCompute
{
    public:
        //Constructor for CheckCompute class
        CheckCompute();

        //setter function
        void startPlot(double p1, double p2, double p3, double p4, int year);
        void setButton(std::shared_ptr<sf::Sprite> pTrbutton);
        void setPlot(std::shared_ptr<WindowPlot> pTrplot);
        void setCoeff(std::vector<std::pair<double,double>> coeff);
        void setColor(sf::Color color);

        //compute
        void computeForecast(double p1, double p2, double p3, double p4, int year);
        
        //getter function
        std::shared_ptr<sf::Sprite> getButton() const;
        
        //check if the mouse is on a button
        bool operator[](sf::Vector2f mouse_coord) const;

    private:
        //compute button
        std::shared_ptr<sf::Sprite> my_button_;
        //plot
        std::shared_ptr<WindowPlot> my_plot_;
        //all the linear coeff
        std::vector<std::pair<double,double>> coeff_;
};