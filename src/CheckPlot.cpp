#include "CheckPlot.hpp"

/**
 * \brief Constructor for CheckPlot class
 */
CheckPlot::CheckPlot():my_buttons_(),my_plots_(){}

/**
 * \brief add plot window to my_plots_ vector
 * @param plot the plot window to be added
*/
void CheckPlot::addPlot(WindowPlot* plot)
{
    my_plots_.push_back(plot);
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
 * \brief stop a plot 
 * @param id the index of the plot to be stopped
*/
void CheckPlot::stopPlot(int id)
{
    my_plots_[id]->close();
}

/**
 * \brief add button to my_buttons_ vector
 * @param button the button to be added
*/
void CheckPlot::addButton(sf::Sprite* button)
{
    my_buttons_.push_back(button);
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
std::vector<sf::Sprite*> CheckPlot::getButtons()
{
    return my_buttons_;
}

/**
 * \brief deletes all the used memory  
*/
void CheckPlot::free()
{
    for(size_t i = 0; i < my_plots_.size(); i++)
    {
        delete my_plots_[i];
    }
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