/****************************************************************
Copyright (C) 2009 Aleksey Myasnikov
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
in file LICENSE along with this program.  If not, see
<http://www.gnu.org/licenses/>
****************************************************************/
/*!
 * \file errorfunction.cpp
 * \class ErrorFunction
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \date 2009/04
 * \version 1.08
 * \brief Class OptimizationParameters provide access to values
 */
#include "errorfunction.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <math.h>

jfuzzyqt::ErrorFunction::ErrorFunction(QObject*parent)
    : QObject(parent)
{
}
jfuzzyqt::ErrorFunction::ErrorFunction(QObject*parent, const QString& fileUri)
    : QObject(parent)
{
    QFile file(fileUri);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        QString line = in.readLine();
        QStringList names = line.replace("\t"," ").split(" ",QString::SkipEmptyParts);
        do{
            line = in.readLine();
            if(!line.isEmpty())
            {
                QHash<QString, double>sample;
                QStringList values = line.replace("\t"," ").split(" ");
                for(int i = 0; i < values.size(); i++)
                {
                    if(!values.at(i).isEmpty())
                    {
                        if(names.size() >= values.size())
                        {
                            sample[names.at(i)] = values.at(i).toDouble();
                        }else{
                            qDebug() << "Error reading line " << line;
                        }
                    }
                }
                samples.append(sample);
            }
        }while(!line.isNull());
        file.close();
    }
}
double jfuzzyqt::ErrorFunction::evaluate(JFuzzyQt&model)const
{
    double toReturn = 0.;
    QStringList inputs = model.inputs();
    QStringList outputs = model.outputs();
    for(int i = 0; i < samples.size(); i++)
    {
        QHash<QString, double>sample = samples.at(i);
        for(QHash<QString, double>::const_iterator j = sample.begin(); j != sample.end(); j++)
        {
            if(inputs.contains(j.key()))
            {
                model.setVariable(j.key(), j.value());
            }
        }
        model.evaluate();
        for(QHash<QString, double>::const_iterator j = sample.begin(); j != sample.end(); j++)
        {
            if(outputs.contains(j.key()))
            {
                toReturn += pow(qAbs(model.getValue(j.key())-j.value()), 2.);
            }
        }
    }
    return toReturn;
}
void jfuzzyqt::ErrorFunction::append(QHash<QString, double>sample)
{
    samples.append(sample);
}
int jfuzzyqt::ErrorFunction::samplesSize()const
{
    return samples.size();
}
