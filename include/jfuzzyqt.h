/****************************************************************
Copyright (C) 2009 Marco Estanqueiro, Aleksey Myasnikov
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
 * \file jfuzzyqt.h
 * \class JFuzzyQt
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief Class JFuzzyQt is main class of fuzzy model.
 *
 * Application instructions:
 * 1) Construct JFuzzyQt object:
 *    JFuzzyQt model;
 * 2) Set path of fcl-file:
 *    model.load("./example.fcl");
 * 3) Sets variable values:
 *    model.setVariable("var1", var1);
 * 4) Evalute model:
 *    model.evalute();
 * 5) Getting result:
 *    double result = model.getValue("res")
 */
#ifndef JFUZZYQT_H
#define JFUZZYQT_H

#include <Qt/qglobal.h>
#ifndef Q_DECL_EXPORT
#   define Q_DECL_EXPORT
#endif
#include <QString>
#include <QObject>
#include <QHash>
#include <QStringList>

namespace jfuzzyqt{

class FunctBlock;

Q_DECL_EXPORT class JFuzzyQt : public QObject
{
    Q_OBJECT

public:
    /**
      * \brief Default constructor
      * \param parent - Qt parent object
     **/
    JFuzzyQt(QObject *parent=NULL);
    /**
      * \brief Constructor
      * \param fleUri - path of fcl file
      * \param parent - Qt parent object
     **/
    JFuzzyQt(const QString& fileUri, QObject *parent=NULL);
    /**
      * \brief Destructor
     **/
    ~JFuzzyQt();
    /**
      * \brief Loading fcl-model from file
      * \param fleUri - path of fcl file
      * \return true  - if loading was finished
      * \return false - if loading was not finished
     **/
    bool load(const QString& fileUri);
    /**
      * \brief Setting variable value
      * \param varName - variable name
      * \param value   - variable value
      * \param fb      - variable function block.
      * If (fb == QString::null), than set all variables with varName in all function blocks
     **/
    void setVariable(const QString& varName, const double& value, const QString& fb = QString::null);
    /**
      * \brief Evalution model
      * \param fb      - variable function block.
      * If (fb == QString::null), than evalute all function blocks
     **/
    void evaluate(const QString& fb = QString::null);
    /**
      * \brief Getting variable value
      * \param varName - variable name
      * \param fb      - variable function block.
      * If (fb == QString::null), than using defaultBlockName
      * \return variable value
     **/
    double getValue(const QString& varName, const QString& fb = QString::null)const;
    /**
      * \brief Show in console debugging messages
     **/
    void debug() const;
    /**
      * \brief Getting names of function blocks
      * \return names of function blocks
     **/
    QStringList functBlocks()const;
    /**
      * \brief Getting inputs
      * \param fb      - function block.
      * If (fb == QString::null), than using defaultBlockName
      * \return input variable names of function block fb
     **/
    QStringList inputs(const QString& fb = QString::null)const;
    /**
      * \brief Getting outputs
      * \param fb      - function block.
      * If (fb == QString::null), than using defaultBlockName
      * \return output variable names of function block fb
     **/
    QStringList outputs(const QString& fb = QString::null)const;

private:
    QHash<QString, FunctBlock*> functionBlocks;
    QString defaultBlockName;

    bool addFunctionBlock(FunctBlock* functionBlock);

};

}using namespace jfuzzyqt;

#endif // JFUZZYQT_H
