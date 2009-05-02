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
    if(model.load("../fcl/"+fclfiles.at(example-1)))
    {
        std::cout << "Error Opening " << fclfiles.at(example).toLocal8Bit().data() << std::endl;
        // make sure the "working directory" in "Project | Settings..."
        // is set to the executable's directory if running from the MSVC IDE
        return 0;
    }
    int option = 0;
    std::cout << "Select option [1-resave, 2-calc] : ";
    std::cin >> option;
    if(option==1)
    {
        char*filename = new char[256];
        for(int i = 0; i < 255; i++)
        {
            filename[i] = ' ';
        }
        filename[256] = '\0';
        std::cout << "Enter file name for saving : ";
        std::cin >> filename;
        if(!model.save(QString(filename)))
        {
            std::cout << "fault" << std::endl;
        }
    }else if(option==2){
        QStringList funct_blocks = model.functBlocks();
        int funct_block = 0;
        if(funct_blocks.size() > 1)
        {
            std::cout << "Detected function blocks:" << std::endl;
            for(int i = 0; i < funct_blocks.size(); i++)
            {
                std::cout << " " << (i+1) << ". " << funct_blocks.at(i).toLocal8Bit().data() << std::endl;
            }
            while((funct_block < 1) || (funct_block > funct_blocks.size()))
            {
                std::cout << "Select number of funct block [1.." << funct_blocks.size() << "] : ";
                std::cin >> funct_block;
            }
            funct_block--;
        }
        QStringList inputs = model.inputs(funct_blocks.at(funct_block));
        QStringList outputs = model.outputs(funct_blocks.at(funct_block));
        if(inputs.size() == 2 && outputs.size() == 1)
        {
            std::cout << " Declarations : " << std::endl;
            std::cout << " input1 = " << inputs.at(0).toLocal8Bit().data() << std::endl;
            std::cout << " input2 = " << inputs.at(1).toLocal8Bit().data() << std::endl;
            std::cout << " output = " << outputs.at(0).toLocal8Bit().data() << std::endl;
            int input1, input2; // values for input variables
            std::cout << "------------------------------------------------------------------" << std::endl;
            std::cout << "                               output                             " << std::endl;
            std::cout << "------------------------------------------------------------------" << std::endl;
            std::cout << "      |                        input2                             " << std::endl;
            std::cout << "input1|-----------------------------------------------------------" << std::endl;
            std::cout << "      | 0.0 | 1.0 | 2.0 | 3.0 | 4.0 | 5.0 | 6.0 | 7.0 | 8.0 | 9.0 " << std::endl;
            std::cout << "------------------------------------------------------------------" << std::endl;
            for(input1 = 0; input1 < 10; input1++)
            {
                QString line;
                line.append(QString("%1").arg(double(input1),5,'f',2));
                line.append(" |");
                for(input2 = 0; input2 < 10; input2++)
                {
                    model.setVariable(inputs.at(0), input1, funct_blocks.at(funct_block));
                    model.setVariable(inputs.at(1), input2, funct_blocks.at(funct_block));
                    model.evaluate(funct_blocks.at(funct_block));
                    line.append(QString("%1").arg(model.getValue(outputs.at(0), funct_blocks.at(funct_block)),5,'f', 2));
                    if(input2 < 9) line.append("|");
                }
                std::cout << line.toLocal8Bit().data() << std::endl;
            }
        }else{
            std::cout << "Input values: " << std::endl;
            for(int i = 0; i < inputs.size(); i++)
            {
                double value = 0.;
                std::cout << inputs.at(i).toLocal8Bit().data() << " = ";
                std::cin >> value;
                model.setVariable(inputs.at(i), value, funct_blocks.at(funct_block));
            }
            std::cout << "Result: " << std::endl;
            model.evaluate(funct_blocks.at(funct_block));
            if(!outputs.size())
            {
                std::cout << "Output variables was not found" << std::endl;
            }
            for(int i = 0; i < outputs.size(); i++)
            {
                std::cout << outputs.at(i).toLocal8Bit().data() << " = " << model.getValue(outputs.at(i), funct_blocks.at(funct_block)) << std::endl;
            }
        }
    }
    return 0;
}
