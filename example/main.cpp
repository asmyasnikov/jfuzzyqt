#include <jfuzzyqt.h>
#include <iostream>

#define OUR_HEALTH	0 // our health is 1st variable
#define ENEMY_HEALTH	1 // enemy health is 2nd variable

int main(int, char**)
{
    char	option;	// var for selection of what user wants to do

    std::cout.setf(std::ios::fixed);
    std::cout.precision(2); // only display 2 decimal places

    // create and load the model
    JFuzzyQt model;
    if(model.load("example.fcl"))
    {
        std::cout << "Error Opening example.fcl";
        // make sure the "working directory" in "Project | Settings..."
        // is set to the executable's directory if running from the MSVC IDE
        return 0;
    }
    while (1)
    {
        std::cout << "SELECT AN OPTION:\n\tS - set values\n\tQ - quit" << std::endl;
        std::cin >> option;
        if (option == 'Q' || option == 'q')
            break;
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
    } // end while(1)
    return 0;
} // end main()
