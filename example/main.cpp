#include <jfuzzyqt.h>
#include <iostream>
#include <QDir>

#define OUR_HEALTH	0 // our health is 1st variable
#define ENEMY_HEALTH	1 // enemy health is 2nd variable

int main(int, char**)
{
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
    int service, food; // values for input variables
    std::cout << "                                food                               " << std::endl;
    std::cout << " |     |-----------------------------------------------------------" << std::endl;
    std::cout << " |value| 0.0 | 1.0 | 2.0 | 3.0 | 4.0 | 5.0 | 6.0 | 7.0 | 8.0 | 9.0 " << std::endl;
    std::cout << "-|-----------------------------------------------------------------" << std::endl;
    for(service = 0; service < 10; service++)
    {
        QString line;
        switch(service)
        {
            case 1: line.append("s"); break;
            case 2: line.append("e"); break;
            case 3: line.append("r"); break;
            case 4: line.append("v"); break;
            case 5: line.append("i"); break;
            case 6: line.append("c"); break;
            case 7: line.append("e"); break;
            default: line.append(" "); break;
        }
        line.append("|");
        line.append(QString("%1").arg(double(service),5,'f',2));
        line.append("|");
        for(food = 0; food < 10; food++)
        {
            model.setVariable("service", service);
            model.setVariable("food", food);
            model.evaluate();
            line.append(QString("%1").arg(model.getValue("tip"),5,'f', 2));
            if(food < 9) line.append("|");
        }
        std::cout << line.toLocal8Bit().data() << std::endl;
    }
    return 0;
}
