#pragma once
#include <SFML/Graphics.hpp>
#include "PlotAxes.hpp"
#include "PlotData.hpp"
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Plot : virtual public sf::Drawable, virtual public sf::Transformable
{
    public:
        //Constructor for Plot class
        Plot(sf::Color axes_color, sf::Color scale_color, sf::Font font, sf::Color font_color);

        //Drawing functions
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void drawPoint(const PlotData& elem, sf::RenderTarget& target, sf::RenderStates states,
        const pair<double, double>& x_range, const pair<double, double>& y_range) const;
        void drawLine(const PlotData& elem, sf::RenderTarget& target, sf::RenderStates states, 
        const pair<double, double>& x_range, const pair<double, double>& y_range) const;

        //setter functions
        void autoRange();
        void addData(PlotData data);
        void setRangeX(const double& min, const double& max);
        void setRangeY(const double& min, const double& max);

        //getter functions
        pair<double, double> getRangeX() const;
        pair<double, double> getRangeY() const;

        private:
            //the data to plot
            vector<PlotData> data_set_;
            //plot axes
            PlotAxes axes_;
};