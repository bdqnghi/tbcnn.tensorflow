
using std::cout;  using std::cerr;

#ifndef __CPP__INCLUDED__RPerl__Algorithm__Sort__Bubble_h
#define __CPP__INCLUDED__RPerl__Algorithm__Sort__Bubble_h 0.004_011


#include <rperltypes_mode.h>  
#include <rperltypes.h>  

#include <RPerl/HelperFunctions.cpp>		


#include <RPerl/Algorithm/Sort.cpp>			




# ifdef __PERL__TYPES








class RPerl__Algorithm__Sort__Bubble : public RPerl__Algorithm__Sort  

{
public:
	

	void integer__sort();  
	void number__sort();

	
	void inherited__Bubble(SV* person);
	void inherited(SV* person);

	
	SV* get_integer__data() { return SvREFCNT_inc(this->integer__data); }
	void set_integer__data(SV* integer__data_new) { this->integer__data = integer__data_new; }
	SV* get_number__data() { return SvREFCNT_inc(this->number__data); }
	void set_number__data(SV* number__data_new) { this->number__data = number__data_new; }

	
	RPerl__Algorithm__Sort__Bubble() {}
	~RPerl__Algorithm__Sort__Bubble() {}



private:

	SV* integer__data;
	SV* number__data;
};



SV* integer__bubblesort(SV* integer__data);
SV* number__bubblesort(SV* number__data);



SV* uninherited__Bubble(SV* person);

SV* uninherited(SV* person);


SV* integer__bubblesort__typetest0(SV* lucky_integers);
SV* number__bubblesort__typetest0(SV* lucky_numbers);



SV* RPerl__Algorithm__Sort__Bubble__OPS_TYPES_ID() { return(newSViv(1)); }  
SV* RPerl__Algorithm__Sort__Bubble__ops() { return(newSVpv("CPP", 3)); }
SV* RPerl__Algorithm__Sort__Bubble__types() { return(newSVpv("PERL", 4)); }





# elif defined __CPP__TYPES








class RPerl__Algorithm__Sort__Bubble : public RPerl__Algorithm__Sort  

{
public:
	

	void integer__sort();  
	void number__sort();


	void inherited__Bubble(string person);
	void inherited(string person);

	
	integer__array_ref get_integer__data() { return(this->integer__data); }
	void set_integer__data(integer__array_ref integer__data_new) { this->integer__data = integer__data_new; }  
	number__array_ref get_number__data() { return(this->number__data); }
	void set_number__data(number__array_ref number__data_new) { this->number__data = number__data_new; }

	
	RPerl__Algorithm__Sort__Bubble() {}
	~RPerl__Algorithm__Sort__Bubble() {}

	

private:

	integer__array_ref integer__data;
	number__array_ref number__data;
};



integer__array_ref integer__bubblesort(integer__array_ref integer__data);
number__array_ref number__bubblesort(number__array_ref number__data);


string uninherited__Bubble(string person);

string uninherited(string person);


string integer__bubblesort__typetest0(integer__array_ref lucky_integers);
string number__bubblesort__typetest0(number__array_ref lucky_numbers);



integer RPerl__Algorithm__Sort__Bubble__OPS_TYPES_ID() { integer retval = 1;  return(retval); }  
string RPerl__Algorithm__Sort__Bubble__ops() { string retval = "CPP";  return(retval); }
string RPerl__Algorithm__Sort__Bubble__types() { string retval = "CPP";  return(retval); }





# else

Purposefully_die_from_a_compile-time_error,_due_to_neither___PERL__TYPES_nor___CPP__TYPES_being_defined.__We_need_to_define_exactly_one!

# endif

#endif
