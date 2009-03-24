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
		FunctionDiscrete,FunctionFuncion,FunctionGaussian,
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
	
	virtual bool checkParamters(QString errors);
	virtual void estimateUniverse();	
	virtual double membership(double index) const;
	double getUniverseMax();
	double getUniverseMin();
	const bool isDiscrete()const;
	const QString getName()const;
	virtual void debug(QString tbs)const;

private:
	//-------------------------------------------------------------------------
	// Variables
	//-------------------------------------------------------------------------
	double* universeMax; ///< Universe max (range max)
	double* universeMin; ///< Universe min (range min)

};

#endif // MEMBERSHIPFUNCTION_H
