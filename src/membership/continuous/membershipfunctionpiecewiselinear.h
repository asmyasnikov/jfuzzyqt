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
 * \file membershipfunctionpiecewiselinear.h
 * \class FIXME
 * \author Marco Estanqueiro
 * \author Aleksey Myasnikov
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#ifndef MEMBERSHIPFUNCTIONPIECEWISELINEAR_H
#define MEMBERSHIPFUNCTIONPIECEWISELINEAR_H

#include <QList>
#include "membershipfunctioncontinuous.h"
#include "../value.h"

class MembershipFunctionPieceWiseLinear : public MembershipFunctionContinuous
{
    Q_OBJECT

public:
    MembershipFunctionPieceWiseLinear(QObject* parent, const QList<double>& x,const QList<double>& y);
    ~MembershipFunctionPieceWiseLinear();
    void debug(const QString& tbs)const;
    QString getName()const;
    double membership(double index) const;

private:
    QList<Value*> x;///<Piece wise linear function values x
    QList<Value*> y;///<Piece wise linear function values y

};

#endif // MEMBERSHIPFUNCTIONPIECEWISELINEAR_H
