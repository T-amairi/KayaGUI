#include <limits>
#include "Plot.hpp"
#include <iostream>

/**
 * \brief Constructor for Plot class
 */
Plot::Plot(sf::Color axes_color,sf::Color scale_color,sf::Font font, sf::Color font_color,
std::string x_label, std::string y_label):data_set_(), axes_(axes_color,scale_color,font,font_color,x_label,y_label){}

/**
 * \brief Drawing function derived from the sf::Drawable class
 */
void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(axes_, states);
    
    for(const auto& elem : data_set_)
    {
        switch(elem.getType())
        {
            case 0:
                drawPoint(elem, target, states, axes_.getRangeX(), axes_.getRangeY());
                break;
            case 1:
                drawLine(elem, target, states, axes_.getRangeX(), axes_.getRangeY());
                break;
            default:
                break;
        }
    }
}

/**
 * \brief              Draws data points on the plot
 * @param elem         the data to plot
 * @param x_range      X range of the plotting area
 * @param y_range      Y range of the plotting area
 */
void Plot::drawPoint(const PlotData& elem, sf::RenderTarget& target, sf::RenderStates states, const std::pair<double, double>& x_range, const std::pair<double, double>& y_range) const
{
    for(size_t i = 0; i < elem.getDataSize(); i++)
    {
        auto point = elem(i);
        const auto x = (point.x - x_range.first) / (x_range.second - x_range.first) * (axes_.DIMENSION.x - axes_.MARGIN.x) + axes_.MARGIN.x;
        const auto y = (axes_.DIMENSION.y - axes_.MARGIN.y) - (point.y - y_range.first) / (y_range.second - y_range.first) * (axes_.DIMENSION.y - axes_.MARGIN.y);

        double POINT_RADIUS = 2.f;
        sf::CircleShape circle(POINT_RADIUS);
        circle.setFillColor(elem.getColor());
        circle.setPosition(x - POINT_RADIUS, y - POINT_RADIUS);
        target.draw(circle, states);
    }
}

/**
 * \brief              Draws a line on the plot
 * @param elem         the data to plot
 * @param x_range      X range of the plotting area
 * @param y_range      Y range of the plotting area
 */
void Plot::drawLine(const PlotData& elem, sf::RenderTarget& target, sf::RenderStates states, const std::pair<double, double>& x_range, const std::pair<double, double>& y_range) const
{
    for(size_t i = 0; i < elem.getDataSize(); i++)
    {
        if(i != elem.getDataSize() - 1)
        {
            auto line_start = elem(i);
            auto line_end = elem(i + 1);

            line_start.x = (line_start.x - x_range.first) / (x_range.second - x_range.first) * (axes_.DIMENSION.x - axes_.MARGIN.x) + axes_.MARGIN.x;
            line_start.y = (axes_.DIMENSION.y - axes_.MARGIN.y) - (line_start.y - y_range.first) / (y_range.second - y_range.first) * (axes_.DIMENSION.y - axes_.MARGIN.y);

            line_end.x = (line_end.x - x_range.first) / (x_range.second - x_range.first) * (axes_.DIMENSION.x - axes_.MARGIN.x) + axes_.MARGIN.x;
            line_end.y = (axes_.DIMENSION.y - axes_.MARGIN.y) - (line_end.y - y_range.first) / (y_range.second - y_range.first) * (axes_.DIMENSION.y - axes_.MARGIN.y);

            sf::Vertex line[] = {sf::Vertex(static_cast<sf::Vector2f>(line_start), elem.getColor()),sf::Vertex(static_cast<sf::Vector2f>(line_end), elem.getColor())};
            target.draw(line, 2, sf::Lines, states);
        }
    }
}

/**
 * \brief add plotting data to the data_set_ vector
 * @param data the data to be added
*/
void Plot::addData(PlotData data)
{
    data_set_.push_back(data);
    autoRange();
}

/**
 * \brief adjust plotting area according to the data in the data_set_ vector
*/
void Plot::autoRange()
{
    double x_min = std::numeric_limits<double>::max();
    double x_max = std::numeric_limits<double>::lowest();
    double y_min = std::numeric_limits<double>::max();
    double y_max = std::numeric_limits<double>::lowest();

    for(const auto& elem : data_set_) 
    {
        auto x_range = elem.getRangeX();
        x_min = std::min(x_range.first, x_min);
        x_max = std::max(x_range.second, x_max);

        auto y_range = elem.getRangeY();
        y_min = std::min(y_range.first, y_min);
        y_max = std::max(y_range.second, y_max);
    }

    setRangeX(x_min, x_max);
    setRangeY(y_min, y_max);
}

/**
 * \brief set plotting area according to the X value range
 * @param min min value of X value range
 * @param max max value of X value range
*/
void Plot::setRangeX(const double& min, const double& max)
{
    std::pair<double, double> x_range;
    min > max ? x_range = std::pair<double, double>(max, min) : x_range = std::pair<double, double>(min, max);
    axes_.setRangeX(x_range);
}

/**
 * \brief set plotting area according to the Y value range
 * @param min min value of Y value range
 * @param max max value of Y value range
*/
void Plot::setRangeY(const double& min, const double& max)
{
    std::pair<double, double> y_range;
    min > max ? y_range = std::pair<double, double>(max, min) : y_range = std::pair<double, double>(min, max);
    axes_.setRangeY(y_range);
}

/**
 * \brief return the data_set_ attribute
*/
std::vector<PlotData> Plot::getDataSet() const
{
    return data_set_;
}