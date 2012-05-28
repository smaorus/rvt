// This file is included automatically in any semantic check, if one of the input programs calls rv_getint / rv_getint. The user should include manualy in the source programs "#include "rv_inputs.h".

unsigned long  rv_input_values[RV_MAX_INPUTS];
unsigned rv_input_cnt0 = 0;
unsigned rv_input_cnt1 = 0;

long rv_save_input(unsigned long  mask)
{ return (rv_input_values[rv_input_cnt0++] = mask & nondet_long()); }

long rv_retrive_input(void)
{ 
	if (rv_input_cnt1 >= rv_input_cnt0) return nondet_long(); // in case there are more inputs on side 1
	return rv_input_values[rv_input_cnt1++]; 
}

char rvs0_rv_getchar(void)
{ return rv_save_input(0xFF); }

char rvs1_rv_getchar(void)
{ return rv_retrive_input(); }

int rvs0_rv_getint(void)
{ return rv_save_input( 0xFFFFFFFFL ); }

int rvs1_rv_getint(void)
{ return rv_retrive_input(); }

