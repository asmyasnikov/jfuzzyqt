#ifndef MEMBERSHIPFUNCTION_H
#define MEMBERSHIPFUNCTION_H

#include <QString>

class Value;

class MembershipFunction
{
public:
	enum MembershipType{FunctionContinuous,FunctionCosine,FunctionDifferenceSigmoidal,FunctionDiscrete,FunctionFuncion,
	FunctionGaussian,FunctionGenBell,FunctionGenericSingleton,FunctionPieceWiseLinear,FunctionSigmoidal,
	FunctionSingleton,FunctionTrapetzoidal,FunctionTriangular};
	
	bool discrete;
	Value* parameters;
	MembershipType type;

	MembershipFunction(MembershipType type);
	MembershipFunction(MembershipType type, MembershipFunction& membership);
	~MembershipFunction();
	
	virtual bool checkParamters(QString errors);
	virtual void estimateUniverse();	
	virtual double membership(double in) const;
	double getUniverseMax();
	double getUniverseMin();
	const bool isDiscrete()const;
	const QString getName()const;
	virtual void debug(QString tbs)const;
private:
	//-------------------------------------------------------------------------
	// Variables
	//-------------------------------------------------------------------------
	/** Function's parameters */
	
	/** Universe max (range max) */
	double* universeMax;
	/** Universe min (range min) */
	double* universeMin;
};

#endif // MEMBERSHIPFUNCTION_H
