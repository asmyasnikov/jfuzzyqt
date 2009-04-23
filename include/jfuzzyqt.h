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
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
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

///<Thisclass is called FIS@jFuzzyLogic

namespace jfuzzyqt{

class FunctBlock;

Q_DECL_EXPORT class JFuzzyQt : public QObject
{
    Q_OBJECT

public:
    JFuzzyQt(QObject *parent=NULL);
    ~JFuzzyQt();
    bool load(const QString& fileUri);
    void setVariable(const QString& varName, const double& value);
    void evaluate();
    double getValue(const QString& varName)const;
    void debug() const;

private:
    QHash<QString, FunctBlock*> functionBlocks;
    QString defaultBlockName;

    bool addFunctionBlock(FunctBlock* functionBlock);

};

}using namespace jfuzzyqt;

#endif // JFUZZYQT_H
