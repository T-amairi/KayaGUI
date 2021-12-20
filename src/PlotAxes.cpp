#include "PlotAxes.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>

//dimension of the chart 
const sf::Vector2f PlotAxes::DIMENSION{800.0, 600.0};
//the margin between the plot and the chart dimension 
const sf::Vector2f PlotAxes::MARGIN{40.0, 20.0}; 

/**
 * \brief Constructor for PlotAxes class
 */
PlotAxes::PlotAxes(sf::Color axes_color,sf::Color scale_color,sf::Font font, sf::Color font_color, 
string x_label, string y_label):axes_color_(axes_color), scale_color_(scale_color), font_(font), 
font_color_(font_color), x_label_(x_label), y_label_(y_label), x_range_(), y_range_(){}

/**
 * \brief Drawing function derived from the sf::Drawable class
 */
void PlotAxes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawAxes(target, states);
    drawLegend(target, states);
}

/**
 * \brief Draws axes
 */
void PlotAxes::drawAxes(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Draw X axis 
    auto x_start = sf::Vector2f(MARGIN.x, DIMENSION.y - MARGIN.y);
    auto x_end = sf::Vector2f(DIMENSION.x,  DIMENSION.y - MARGIN.y);
    sf::Vertex x_axes[] = {sf::Vertex(x_start, axes_color_),sf::Vertex(x_end, axes_color_)};
    target.draw(x_axes, 2, sf::Lines, states);

    //Draw X label
    drawLabelX(target,states);

    //Draw X scale 
    for(int i = 1; i < 10; i++)
    {
        auto x_start = sf::Vector2f(MARGIN.x, DIMENSION.y - MARGIN.y - i * (DIMENSION.y - MARGIN.y) / 9);
        auto x_end = sf::Vector2f(DIMENSION.x, DIMENSION.y - MARGIN.y - i * (DIMENSION.y - MARGIN.y) / 9);
        sf::Vertex x_axes[] = {sf::Vertex(x_start, scale_color_),sf::Vertex(x_end, scale_color_)};
        target.draw(x_axes, 2, sf::Lines, states);
    }

    //Draw Y axis
    auto y_start = sf::Vector2f(MARGIN.x, 0);
    auto y_end = sf::Vector2f(MARGIN.x,  DIMENSION.y - MARGIN.y);
    sf::Vertex y_axes[] = {sf::Vertex(y_start, axes_color_),sf::Vertex(y_end, axes_color_)};
    target.draw(y_axes, 2, sf::Lines, states);

    //Draw Y label
    drawLabelY(target,states);

    // Draw Y scale
    for(int i = 1; i < 10; i++) 
    {
        auto y_start = sf::Vector2f(MARGIN.x + i * (DIMENSION.x - MARGIN.x) / 9, 0);
        auto y_end = sf::Vector2f(MARGIN.x + i * (DIMENSION.x - MARGIN.x) / 9,  DIMENSION.y - MARGIN.y);
        sf::Vertex y_axes[] = {sf::Vertex(y_start, scale_color_),sf::Vertex(y_end, scale_color_)};
        target.draw(y_axes, 2, sf::Lines, states);
    }
}

/**
 * \brief Draws legend
 */
void PlotAxes::drawLegend(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Draw X legend
    const double x_step = (x_range_.second - x_range_.first) / 9;
    const int x_precision = abs(min(0.0,log10(x_step) - 2.0));

    for(int i = 0; i < 10; i++) 
    {
        double val = x_range_.first + i * x_step;
        stringstream ss;
        ss.precision(x_precision);
        ss << fixed;
        ss << val;
        sf::Text legend;
        legend.setString(ss.str());
        legend.setFont(font_);
        legend.setFillColor(font_color_);
        legend.setCharacterSize(15);
        legend.setOrigin(legend.getGlobalBounds().width / 2.0, legend.getGlobalBounds().height / 2.0);
        legend.setPosition(MARGIN.x + i * (DIMENSION.x - MARGIN.x) / 9, DIMENSION.y - MARGIN.y + 10.0);
        target.draw(legend, states);
    }

    //Draw Y legend
    const double y_step = (y_range_.second - y_range_.first) / 9;
    const int y_precision = abs(min(0.0,log10(y_step) - 2.0));

    for(int i = 0; i < 10; i++)
    {
        double val = y_range_.first + i * y_step;
        stringstream ss;
        ss.precision(y_precision);
        ss << fixed;
        ss.width(5);
        ss << val;
        sf::Text legend;
        legend.setString(ss.str());
        legend.setFont(font_);
        legend.setFillColor(font_color_);
        legend.setCharacterSize(15);
        legend.setOrigin(legend.getGlobalBounds().width, legend.getGlobalBounds().height);
        legend.setPosition(MARGIN.x - 10.0, DIMENSION.y - MARGIN.y - i * (DIMENSION.y - MARGIN.y ) / 9.0);
        target.draw(legend, states);
    }
}

/**
 * \brief Draws label of X axis
 */
void PlotAxes::drawLabelX(sf::RenderTarget& target, sf::RenderStates states) const
{   
    sf::Text label_x;
    auto size_x = DIMENSION.x - MARGIN.x;
    label_x.setString(x_label_);
    label_x.setFont(font_);
    label_x.setFillColor(font_color_);
    label_x.setCharacterSize(16);
    label_x.setOrigin(label_x.getGlobalBounds().width / 2.0, label_x.getGlobalBounds().height / 2.0);
    label_x.setPosition(size_x / 2 - x_label_.size() * 5, DIMENSION.y - MARGIN.y + 30.0);
    target.draw(label_x, states);
}

/**
 * \brief Draws label of Y axis
 */
void PlotAxes::drawLabelY(sf::RenderTarget& target, sf::RenderStates states) const
{   
    sf::Text label_y;
    auto size_y = DIMENSION.y - MARGIN.y;
    label_y.setString(y_label_);
    label_y.setFont(font_);
    label_y.setFillColor(font_color_);
    label_y.setCharacterSize(16);
    label_y.setOrigin(label_y.getGlobalBounds().width / 2.0, label_y.getGlobalBounds().height / 2.0);
    label_y.setPosition(MARGIN.x - 45.0, size_y / 2 - y_label_.size() * 5);
    label_y.setRotation(-90);
    target.draw(label_y, states);
}

/**
 * \brief set the X value of the plot range
 * @param x_range the X value range of the plotting area
*/
void PlotAxes::setRangeX(const pair<double, double>& x_range)
{
    x_range_ = x_range;
}

/**
 * \brief set the Y value of the plot range
 * @param y_range the Y value range of the plotting area
*/
void PlotAxes::setRangeY(const pair<double, double>& y_range)
{
    y_range_ = y_range;
}

/**
 * \brief get the X value of the plot range
 * @return the X value range of the plotting area
*/
pair<double, double> PlotAxes::getRangeX() const
{
    return x_range_;
}

/**
 * \brief get the Y value of the plot range
 * @return the Y value range of the plotting area
*/
pair<double, double> PlotAxes::getRangeY() const
{
    return y_range_;
}