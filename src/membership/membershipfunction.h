/****************************************************************
Copyright (C) 2009 Marco Estanqueiro
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
 * \file membershipfunction.h
 * \class FIXME
 * \author Marco Estanqueiro
 * \author pcingola@users.sourceforge.net from Java jFuzzyLogic project
 * \date 2009/04
 * \version 0.2
 * \brief FIXME
 */
#ifndef MEMBERSHIPFUNCTION_H
#define MEMBERSHIPFUNCTION_H

#include <QString>
#include <QObject>

class Value;

class MembershipFunction : public QObject
{
    Q_OBJECT

public:
    enum MembershipType
    {
            FunctionContinuous,FunctionCosine,FunctionDifferenceSigmoidal,
            FunctionDiscrete,FunctionFunction,FunctionGaussian,
            FunctionGenBell,FunctionGenericSingleton,FunctionPieceWiseLinear,
            FunctionSigmoidal,FunctionSingleton,FunctionTrapetzoidal,
            FunctionTriangular
    };

    bool discrete;
    Value** parameters;
    MembershipType type;

    MembershipFunction(QObject* parent, MembershipType type);
    MembershipFunction(MembershipType type, MembershipFunction& membership);
    ~MembershipFunction();

    virtual bool checkParamters(const QString& errors);
    virtual void estimateUniverse();
    virtual double membership(double index) const = 0;
    double getUniverseMax();
    double getUniverseMin();
    bool isDiscrete()const;
    virtual QString getName()const = 0;
    virtual void debug(const QString& tbs)const = 0;

protected:
    double* universeMax; ///< Universe max (range max)
    double* universeMin; ///< Universe min (range min)

};

#endif // MEMBERSHIPFUNCTION_H
