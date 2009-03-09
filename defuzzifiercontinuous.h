#ifndef DEFUZZIFIERCONTINUOUS_H
#define DEFUZZIFIERCONTINUOUS_H

#include "defuzzifier.h"

class DefuzzifierContinuous : public Defuzzifier
{
public:
	const static int DEFAULT_NUMBER_OF_POINTS = 1000;

	DefuzzifierContinuous();
	~DefuzzifierContinuous();

	double getMin();
	double getStepSize();
	int getLength();
	void setValue(double valueX, double valueY);
	int getIndex(double d);
	double DefuzzifierContinuous::getValue(double x);
private:
	//-------------------------------------------------------------------------
	// Variables
	//-------------------------------------------------------------------------

	/** Where function ends */
	double max;
	/** Where function begins */
	double min;
	/** 
	 * Step size between each element in 'values[]'
	 * 			stepSize = (max - min) / values.length 
	 */
	double stepSize;
	/** 
	 * Funcion values: A generic continuous function
	 * 			y = f(x)
	 * where x : [min, max] 
	 * Values are stored in 'values[]' array.
	 * Array's index is calculated as: 
	 * 			index = (x - min) / (max - min) * (values.length)
	 */
	double values[DEFAULT_NUMBER_OF_POINTS];
};

#endif // DEFUZZIFIERCONTINUOUS_H
