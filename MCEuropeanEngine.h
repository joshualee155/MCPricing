#ifndef MCEUROPEANENGINE_H
#define MCEUROPEANENGINE_H

#include "PricingEngine.h"
#include "VanillaOption.h"
#include <memory>

using std::shared_ptr;

class MCEuropeanEngine :public VanillaOption::Engine
{
public:
	MCEuropeanEngine(const shared_ptr<StochProcess>& process_,
		double DiscountRate_,
		bool withControlVariate_ = true,
		int DatesofYear_ = 250,
		int SizeofTimes_ = 10000);
	virtual void calculate() const;
	virtual MCEuropeanEngine* clone() const;
private:
    shared_ptr<StochProcess> process;
    double DiscountRate;
	int DatesofYear, SizeofTimes;
	bool withControlVariate;
};
#endif