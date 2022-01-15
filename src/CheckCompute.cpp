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
 * \brief open the forecast result in a new window
*/
void CheckCompute::startPlot(double p1, double p2, double p3, double p4, int start, int end)
{
    computeForecast(p1,p2,p3,p4,start,end);
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
 * @param start the year of start
 * @param end the year of end
*/
void CheckCompute::computeForecast(double p1, double p2, double p3, double p4, int start, int end)
{
    my_plot_->resetData();
    int diff;
    end <= start ? diff = 2 : diff = end - start + 1;
    std::vector<int> years(diff);

    if(end <= start)
    {
        std::iota(years.begin(), years.end(), 2022);
    }

    else
    {
        std::iota(years.begin(), years.end(), start); 
    }

    PlotData rightSideEquation(sf::Color::Red,1);
    PlotData LeftSideEquation(sf::Color(255,128,28),1);

    double P = Linear(coeff_[0].first,coeff_[0].second,years[0]);
    double G = Log(coeff_[1].first,coeff_[1].second,years[0]);
    double F = Sqrt(coeff_[2].first,coeff_[2].second,years[0]);
    double E = Sqrt(coeff_[3].first,coeff_[3].second,years[0]);

    double G_P = G/P;
    double E_G = E/G;
    double F_E = F/E;

    for(const auto& x : years)
    {
        F = Sqrt(coeff_[2].first,coeff_[2].second,x);
        P = computePercentage(P,p1);
        G_P = computePercentage(G_P,p2);
        E_G = computePercentage(E_G,p3);
        F_E = computePercentage(F_E,p4);

        double leftSide = P * G_P * E_G * F_E;
        LeftSideEquation.addData(sf::Vector2<double>(x,leftSide));
        rightSideEquation.addData(sf::Vector2<double>(x,F));
    }

    my_plot_->addData(rightSideEquation);
    my_plot_->addData(LeftSideEquation);
}