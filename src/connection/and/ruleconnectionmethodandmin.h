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
 * \file ruleconnectionmethodandmin.h
 * \class FIXME
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#ifndef RULECONNECTIONMETHODANDMIN_H
#define RULECONNECTIONMETHODANDMIN_H

#include "../ruleconnectionmethod.h"
#include <QString>

class RuleConnectionMethodAndMin : public RuleConnectionMethod
{
    Q_OBJECT

public:
    RuleConnectionMethodAndMin();
    ~RuleConnectionMethodAndMin();
    double connect(double antecedent1, double antecedent2)const;
    QString toQString() const;
private:

};

#endif // RULECONNECTIONMETHODANDMIN_H
