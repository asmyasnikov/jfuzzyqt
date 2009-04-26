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
 * \file value.h
 * \class Value
 * \author Marco Estanqueiro <estanqueiro.marco@gmail.com>
 * \author Aleksey Myasnikov <AlekseyMyasnikov@yandex.ru>
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.83
 * \brief FIXME
 */
#ifndef VALUE_H
#define VALUE_H

#include "../rule/variable.h"
#include <QObject>
#include <QString>

namespace jfuzzyqt{

class Value : public QObject
{
    Q_OBJECT
public:
    enum Type {
            REAL, VAR_REFERENCE, UNDEFINED
    };

    Value(QObject* parent=NULL);
    Value(QObject* parent, const double& value);
    ~Value();
    void debug(const QString& tbs)const;
    double getValue()const;
private:
    Type type;
    double valReal;
    Variable* varRef;

};

}using namespace jfuzzyqt;

#endif // VALUE_H
