#ifndef MEMBERSHIPFUNCTIONPIECEWISELINEAR_H
#define MEMBERSHIPFUNCTIONPIECEWISELINEAR_H

#include <QList>
#include "membershipfunctionContinuous.h"
#include "value.h"

class MembershipFunctionPieceWiseLinear : public MembershipFunctionContinuous
{
public:
	MembershipFunctionPieceWiseLinear(QObject* parent, QList<Value> x, QList<Value> y);
	~MembershipFunctionPieceWiseLinear();
	void debug(QString tbs)const;
	double membership(double index) const;

private:
	QList<Value> x;///<Piece wise linear function values x
	QList<Value> y;///<Piece wise linear function values y

};

#endif // MEMBERSHIPFUNCTIONPIECEWISELINEAR_H
