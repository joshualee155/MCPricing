#ifndef MCEXOTICENGINE_H
#define MCEXOTICENGINE_H

#include "PricingEngine.h"
#include "PathDependentOption.h"
//#include "shared_ptr.h"
#include <memory>

using std::shared_ptr;

class MCExoticEngine : public PathDependentOption::Engine
{
public:
	MCExoticEngine(const shared_ptr<StochProcess>& process_,
		double DiscountRate_,
		int DatesofYear_ = 250,
		int SizeofTimes_ = 10000);
	virtual void calculate() const;
	virtual MCExoticEngine* clone() const;
private:
	int DatesofYear, SizeofTimes;
    shared_ptr<StochProcess> process;
    double DiscountRate;
};
#endif