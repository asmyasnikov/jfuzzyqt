#include <jfuzzyqt.h>
#include <iostream>
#include <QDir>

#define OUR_HEALTH	0 // our health is 1st variable
#define ENEMY_HEALTH	1 // enemy health is 2nd variable

int main(int, char**)
{
    char	option;	// var for selection of what user wants to do

    std::cout.setf(std::ios::fixed);
    std::cout.precision(2); // only display 2 decimal places
    // create and load the model
    JFuzzyQt model;
    QDir dir("../fcl");
    QStringList filter;
    filter.append("*.fcl");
    dir.setNameFilters(filter);
    QStringList fclfiles = dir.entryList();
    std::cout << "Existing fcl-files:" << std::endl;
    for(int i = 0; i < fclfiles.size(); i++)
    {
        std::cout << " " << (i+1) << ". " << fclfiles.at(i).toLocal8Bit().data() << std::endl;
    }
    int example = -1;
    while((example < 1) || (example > fclfiles.size()))
    {
        std::cout << "Select number of fcl file [0.." << fclfiles.size()-1 << "] : ";
        std::cin >> example;
    }
    if(model.load("../fcl/"+fclfiles.at(example-1)))
    {
        std::cout << "Error Opening " << fclfiles.at(example).toLocal8Bit().data() << std::endl;
        // make sure the "working directory" in "Project | Settings..."
        // is set to the executable's directory if running from the MSVC IDE
        return 0;
    }
    std::cout << "SELECT AN OPTION (S - set values, Q - quit) : ";
    std::cin >> option;
    if (option == 'S' || option == 's')
    {
        float service, food; // values for input variables
        for(service = 0; service < 10; service++)
        {
            for(food = 0; food < 10; food++)
            {
                model.setVariable("service", service);
                model.setVariable("food", food);
                model.evaluate();
                std::cout << "f(" << service << ";" << food << ")=" << model.getValue("tip") << std::endl;
            }
        }
    } // end if option = 's'
    return 0;
} // end main()
