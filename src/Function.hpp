#include <cmath>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

//to get which function to use
enum variable {Population,GDP,CO2,Energy};

/**
 * \brief normal linear regression
*/
inline double Linear(double a, double b, double x)
{
    return a*x + b;
}

/**
 * \brief linear regression with log box-cox transformation
*/
inline double Log(double a, double b, double x)
{
    return exp(a*x + b);
}

/**
 * \brief linear regression with square root box-cox transformation
*/
inline double Sqrt(double a, double b, double x)
{
    return pow(a*x + b,2);
}

/**
 * \brief Split a line in a list of string according to the delimeter delim
 */
inline std::vector<std::string> split(const std::string& line, char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(line);

    while(std::getline(tokenStream, token, delim))
    {
        tokens.push_back(token);
    }

    return tokens;
}