#include "CheckCompute.hpp"
#include <numeric>

/**
 * \brief Constructor for CheckPlot class
 */
CheckCompute::CheckCompute(){}

/**
 * \brief set my_plot_ attribute
 * @param pTrplot the plot window to be copied
*/
void CheckCompute::setPlot(std::shared_ptr<WindowPlot> pTrplot)
{
    my_plot_ = pTrplot;
}

/**
 * \brief set my_button_ attribute
 * @param pTrbutton the button to be copied
*/
void CheckCompute::setButton(std::shared_ptr<sf::Sprite> pTrbutton)
{
    my_button_ = pTrbutton;
}

/**
 * \brief set coeff_ attribute
 * @param coeff the vector to be copied
*/
void CheckCompute::setCoeff(std::vector<std::pair<double,double>> coeff)
{
    coeff_ = coeff;
}

/**
 * \brief start a new plot in a new window
*/
void CheckCompute::startPlot(double p1, double p2, double p3, double p4, int year)
{
    computeForecast(p1,p2,p3,p4,year);
    my_plot_->run();
}

/**
 * \brief set a new color to the button_ attribute
 * @param color the new color to be set
*/
void CheckCompute::setColor(sf::Color color)
{
    my_button_->setColor(color);
}

/**
 * \brief return my_button_ attribute
*/
std::shared_ptr<sf::Sprite> CheckCompute::getButton() const
{
    return my_button_;
}

/**
 * \brief checks if the mouse cursor is on the compute button
 * @param mouse_coord x,y coord of the mouse
 * @return true if it is the case, false otherwise
*/
bool CheckCompute::operator[](sf::Vector2f mouse_coord) const
{
    return my_button_->getGlobalBounds().contains(mouse_coord);
}

/**
 * \brief compute kaya forecast
 * @param p1 percentage for the population
 * @param p2 percentage for the G/P ratio
 * @param p3 percentage for the E/G ratio
 * @param p4 percentage for the F/E ratio
 * @param year the year of end
*/
void CheckCompute::computeForecast(double p1, double p2, double p3, double p4, int year)
{
    my_plot_->resetData();
    int diff;
    year < 2022 ? diff = 2 : diff = year - 2021;
    std::vector<int> years(diff);
    std::iota(years.begin(), years.end(), 2022);

    PlotData rightSideEquation(sf::Color::Red,1);
    PlotData LeftSideEquation(sf::Color(255,128,28),1);

    for(const auto& x : years)
    {
        double P = Linear(coeff_[0].first,coeff_[0].second,x);
        double G = Log(coeff_[1].first,coeff_[1].second,x);
        double F = Sqrt(coeff_[2].first,coeff_[2].second,x);
        double E = Sqrt(coeff_[3].first,coeff_[3].second,x);
        double leftSide = computePercentage(P,p1) * computePercentage(G/P,p2) * computePercentage(E/G,p3) * computePercentage(F/E,p4);
        
        rightSideEquation.addData(sf::Vector2<double>(x,F));
        LeftSideEquation.addData(sf::Vector2<double>(x,leftSide));
    }

    my_plot_->addData(rightSideEquation);
    my_plot_->addData(LeftSideEquation);
}