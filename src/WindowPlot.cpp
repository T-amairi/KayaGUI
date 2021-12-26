#include "WindowPlot.hpp"

/**
 * \brief Constructor for WindowPlot class
 */
WindowPlot::WindowPlot(variable name, std::string title, sf::Color axes_color, sf::Color scale_color, sf::Font font, sf::Color font_color, 
std::string x_label, std::string y_label):Window(),plot_(axes_color,scale_color,font,font_color,x_label,y_label),
title_(title),name_(name),a_(),b_()
{
    if(name_ != variable::Compute)
    {
        loadData();
        setLinearReg();
    }
}

/**
 * \brief open the window with the corresponding plot
*/
void WindowPlot::run()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    create(sf::VideoMode(875, 700),title_,sf::Style::Default,settings);
    setPosition(50, 50);

    while(isOpen())
    {
        if(sf::Event event; pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                close();
            }
        }

        clear(sf::Color(30, 30, 30));
        draw(plot_);
        display();
    }
}

/**
 * \brief add plotting data to the plot_ class
 * @param data the data to be added
*/
void WindowPlot::addData(PlotData data)
{
    plot_.addData(data);
}

/**
 * \brief set the position of plot_ in the window
 * @param x coord
 * @param y y coord
*/
void WindowPlot::setPosition(double x, double y)
{
    plot_.setPosition(x,y);
}

/**
 * \brief get the path of the data file to load
*/
std::string WindowPlot::getPath() const
{
    std::string path = "./data/";

    switch(name_)
    {
        case variable::Population:
            path = path + "population";
            break;
        case variable::Energy:
            path = path + "energy";
            break;
        case variable::GDP:
            path = path + "gdp";
            break;
        case variable::CO2:
            path = path + "co2";
            break;
        default:
            break;
    }

    return path + "_fitted.csv";
}

/**
 * \brief reset the plot data
*/
void WindowPlot::resetData()
{
    plot_.resetData();
}

/**
 * \brief create a pair of the linear coeff
 * @return a std::pair object with first (a_ attribute) and second (b_ attribute)
*/
std::pair<double,double> WindowPlot::getCoeff() const
{
    return std::make_pair(a_,b_);
}

/**
 * \brief compute the linear regression
*/
void WindowPlot::setLinearReg()
{
    PlotData line(sf::Color::Red,1);
    auto points = plot_.getDataSet()[0];

    for(size_t i = 0; i < points.getDataSize(); i++)
    {
        switch(name_)
        {
            case variable::Population:
                line.addData(sf::Vector2<double>(points(i).x,Linear(a_,b_,points(i).x)));
                break;
            case variable::Energy:
                line.addData(sf::Vector2<double>(points(i).x,Sqrt(a_,b_,points(i).x)));
                break;
            case variable::GDP:
                line.addData(sf::Vector2<double>(points(i).x,Log(a_,b_,points(i).x)));
                break;
            case variable::CO2:
                line.addData(sf::Vector2<double>(points(i).x,Sqrt(a_,b_,points(i).x)));
                break;
            default:
                break;
        }
    }

    addData(line);
}

/**
 * \brief load the data from the data folder
*/
void WindowPlot::loadData()
{
    std::fstream file;
    file.open(getPath());
    std::string line;
    PlotData points(sf::Color::White,0);

    while(getline(file,line))
    {
        auto str = split(line,',');

        if(str[1] == "\"Year\"")
        {
            continue;
        }

        else if(str[0] == "a")
        {
            a_ = stod(str[1]);
        }

        else if(str[0] == "b")
        {
            b_ = stod(str[1]);

        }

        else
        {
            points.addData(sf::Vector2<double>(stod(str[1]),stod(str[2])));
        }
    }

    file.close();
    addData(points);
}