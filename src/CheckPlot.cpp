#include "CheckPlot.hpp"

/**
 * \brief Constructor for CheckPlot class
 */
CheckPlot::CheckPlot():my_buttons_(),my_plots_(){}

/**
 * \brief add plot window to my_plots_ vector
 * @param plot the plot window to be added
*/
void CheckPlot::addPlot(std::shared_ptr<WindowPlot> pTrplot)
{
    my_plots_.push_back(pTrplot);
}

/**
 * \brief start a new plot in a new window
 * @param id the index of the plot in my_plots_ vector
*/
void CheckPlot::startPlot(int id)
{
    my_plots_[id]->run();
}

/**
 * \brief add button to my_buttons_ vector
 * @param button the button to be added
*/
void CheckPlot::addButton(std::shared_ptr<sf::Sprite> pTrbutton)
{
    my_buttons_.push_back(pTrbutton);
}

/**
 * \brief set a new color to a button in my_buttons_ vector
 * @param id the index of the button in my_buttons_ vector
 * @param color the new color to be set
*/
void CheckPlot::setColor(int id, sf::Color color)
{
    my_buttons_[id]->setColor(color);
}

/**
 * \brief set a new color to all buttons in my_buttons_ vector
 * @param color the new color to be set
*/
void CheckPlot::setAllColor(sf::Color color)
{
    for(auto& button : my_buttons_)
    {
        button->setColor(color);
    }
}

/**
 * \brief return my_buttons_ vector
*/
std::vector<std::shared_ptr<sf::Sprite>> CheckPlot::getButtons() const
{
    return my_buttons_;
}

/**
 * \brief checks if the mouse cursor is on one of the buttons
 * @param mouse_coord x,y coord of the mouse
 * @return the index in my_buttons_ corresponding to the button on which the mouse is or -1 if none
*/
int CheckPlot::operator[](sf::Vector2f mouse_coord) const
{
    for(size_t i = 0; i < my_buttons_.size(); i++)
    {
        if(my_buttons_[i]->getGlobalBounds().contains(mouse_coord))
        {
            return i;
        }
    }

    return -1;
}

/**
 * \brief create a vector containing all coeffs
 * @return a vector of pair containing all coeffs for each parameters of the kaya equation
*/
std::vector<std::pair<double,double>> CheckPlot::getCoeff() const
{
    std::vector<std::pair<double,double>> vec;
    
    for(const auto& ptr : my_plots_)
    {
        vec.push_back(ptr->getCoeff());
    }

    return vec;
}