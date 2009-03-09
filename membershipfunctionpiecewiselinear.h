#ifndef MEMBERSHIPFUNCTIONPIECEWISELINEAR_H
#define MEMBERSHIPFUNCTIONPIECEWISELINEAR_H

#include "MembershipFunctionContinuous.h"
#include "Value.h"
#include <QList>

class MembershipFunctionPieceWiseLinear : public MembershipFunctionContinuous
{
public:
	MembershipFunctionPieceWiseLinear(QList<Value> x, QList<Value> y);
	~MembershipFunctionPieceWiseLinear();
	void debug(QString tbs)const;

private:
	QList<Value> x;///<Piece wise linear function values x
	QList<Value> y;///<Piece wise linear function values y

};

#endif // MEMBERSHIPFUNCTIONPIECEWISELINEAR_H
