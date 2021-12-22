#include "PlotData.hpp"
#include <limits>
#include <cmath>

/**
 * \brief Constructor for PlotData class
 */
PlotData::PlotData(sf::Color color, int type): data_(), color_(color), type_(type){}

/**
 * \brief get the size of the vector data_
 */
size_t PlotData::getDataSize() const
{
    return data_.size();
}

/**
 * \brief get the type of the plotted data
 * @return type_ attribute
*/
int PlotData::getType() const
{
    return type_;
}

/**
 * \brief get the color of the plotted data
 * @return color_ attribute
*/
sf::Color PlotData::getColor() const
{
    return color_;
} 

/**
 * \brief get the X value range of the data
 * @return min, max pair of the X value range
*/
std::pair<double, double> PlotData::getRangeX() const
{
    auto min_x = std::numeric_limits<double>::infinity();
    auto max_x = std::numeric_limits<double>::lowest();

    for(const auto& elem : data_)
    {
        min_x = std::min(min_x, elem.x);
        max_x = std::max(max_x, elem.x);
    }

    return std::pair<double, double>(min_x, max_x);
}

/**
 * \brief get the Y value range of the data
 * @return min, max pair of the Y value range
*/
std::pair<double, double> PlotData::getRangeY() const
{
    auto min_y = std::numeric_limits<double>::infinity();
    auto max_y = std::numeric_limits<double>::lowest();

    for(const auto& elem : data_) 
    {
        min_y = std::min(min_y, elem.y);
        max_y = std::max(max_y, elem.y);
    }

    return std::pair<double, double>(min_y, max_y);
}

/**
 * \brief add a new point to the data_ vector
 * @param data the data to be added
*/
void PlotData::addData(sf::Vector2<double> data)
{
    data_.push_back(data);
}

/**
 * \brief get the point at index i in the data_ vector
 * @param i the index
 * @return the point correcponding to the index i
*/
sf::Vector2<double> PlotData::operator()(size_t i) const
{
    return data_[i];
}