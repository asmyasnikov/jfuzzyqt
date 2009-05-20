#include <jfuzzyqt.h>
#include <iostream>
#include <QDir>

using namespace jfuzzyqt;

int main(int argc, char**argv)
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
        std::cout << "Select number of fcl file [1.." << fclfiles.size() << "] : ";
        std::cin >> example;
    }
    if(!model.load("../fcl/"+fclfiles.at(example-1)))
    {
        std::cout << "Error opening " << fclfiles.at(example-1).toLocal8Bit().data() << std::endl;
        return 0;
    }
    char*filename = new char[256];
    for(int i = 0; i < 255; i++)
    {
        filename[i] = ' ';
    }
    filename[255] = '\0';
    std::cout << "Enter file name with samples (for example, \"../fcl/tipper.dat\") : ";
    std::cin >> filename;
    if(!model.optimize(QString(filename)))
    {
        std::cout << "Optimization fault" << std::endl;
    }else{
        std::cout << "Optimization is Ok" << std::endl;
    }
    for(int i = 0; i < 255; i++)
    {
        filename[i] = ' ';
    }
    filename[255] = '\0';
    std::cout << "Enter file name for saving : ";
    std::cin >> filename;
    if(!model.save(QString(filename)))
    {
        std::cout << "Saving fault" << std::endl;
    }else{
        std::cout << "Saving is Ok" << std::endl;
    }
    return 0;
}
