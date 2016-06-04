#pragma once


#include <string>
#include <rv_walk.h>
#include "rv_side.h"
#include "rv_etc.h"
#include "rv_unroller.h"
#include "rv_temps.h"


class RVArithConverter:
	public RVWalk
{
public:
	RVArithConverter(Project* _tree);
	~RVArithConverter(void);
	void convert_abstract_arithmetics_to_concrete();
private:
	bool arithmeticAbstraction( Statement* st );
	Project* parsetree;


};

