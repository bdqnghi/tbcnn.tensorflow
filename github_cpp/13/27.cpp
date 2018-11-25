
using std::cout;  using std::cerr;

#ifndef __CPP__INCLUDED__RPerl__Algorithm__Sort__Bubble_cpp
#define __CPP__INCLUDED__RPerl__Algorithm__Sort__Bubble_cpp 0.004_012


#include <RPerl/Algorithm/Sort/Bubble.h>  

# ifdef __PERL__TYPES









void RPerl__Algorithm__Sort__Bubble::integer__sort()

{
	if (TEST_VERBOSE2) { fprintf(stderr, "in integer__sort(), top of subroutine, have pre-DUMPER SV_REFERENCE_COUNT(this->integer__data) = %u\n", SV_REFERENCE_COUNT(this->integer__data));  fprintf(stderr, "in integer__sort(), top of subroutine, have this->integer__data = %s", RPerl_DUMPER__perl_from_c(this->integer__data));  fprintf(stderr, "in integer__sort(), top of subroutine, have post-DUMPER SV_REFERENCE_COUNT(this->integer__data) = %u\n\n", SV_REFERENCE_COUNT(this->integer__data));  }


	this->integer__data = integer__bubblesort(this->integer__data);

	if (TEST_VERBOSE2) { fprintf(stderr, "in integer__sort(), bottom of subroutine, have pre-SvREFCNT_dec pre-DUMPER SV_REFERENCE_COUNT(this->integer__data) = %u\n", SV_REFERENCE_COUNT(this->integer__data));  fprintf(stderr, "in integer__sort(), bottom of subroutine, have pre-SvREFCNT_dec this->integer__data = %s", RPerl_DUMPER__perl_from_c(this->integer__data));  fprintf(stderr, "in integer__sort(), bottom of subroutine, have pre-SvREFCNT_dec post-DUMPER SV_REFERENCE_COUNT(this->integer__data) = %u\n\n", SV_REFERENCE_COUNT(this->integer__data));  }
	SvREFCNT_dec(this->integer__data);
	if (TEST_VERBOSE2) { fprintf(stderr, "in integer__sort(), bottom of subroutine, have post-SvREFCNT_dec pre-DUMPER SV_REFERENCE_COUNT(this->integer__data) = %u\n", SV_REFERENCE_COUNT(this->integer__data));  fprintf(stderr, "in integer__sort(), bottom of subroutine, have post-SvREFCNT_dec this->integer__data = %s", RPerl_DUMPER__perl_from_c(this->integer__data));  fprintf(stderr, "in integer__sort(), bottom of subroutine, have post-SvREFCNT_dec post-DUMPER SV_REFERENCE_COUNT(this->integer__data) = %u\n\n", SV_REFERENCE_COUNT(this->integer__data));  }
	if (TEST_VERBOSE2) { fprintf(stderr, "in integer__sort(), bottom of subroutine, have pre-DUMPER SV_REFERENCE_COUNT(this->integer__data) = %u\n", SV_REFERENCE_COUNT(this->integer__data));  fprintf(stderr, "in integer__sort(), bottom of subroutine, have this->integer__data = %s", RPerl_DUMPER__perl_from_c(this->integer__data));  fprintf(stderr, "in integer__sort(), bottom of subroutine, post-DUMPER SV_REFERENCE_COUNT(this->integer__data) = %u\n\n", SV_REFERENCE_COUNT(this->integer__data));  }

}

void RPerl__Algorithm__Sort__Bubble::number__sort()
{
	this->number__data = number__bubblesort(this->number__data);
	SvREFCNT_dec(this->number__data);
}




void RPerl__Algorithm__Sort__Bubble::inherited__Bubble(SV* person) { cout << "in CPPOPS_PERLTYPES Bubble->inherited__Bubble(), received this = '" << this << "' and person = '" << SvPV_nolen(person) << "', FRIED\n"; }


void RPerl__Algorithm__Sort__Bubble::inherited(SV* person) { cout << "in CPPOPS_PERLTYPES Bubble->inherited(), received this = '" << this << "' and person = '" << SvPV_nolen(person) << "', ILLOGICAL\n"; }






SV* integer__bubblesort(SV* integer__data)  


{





	RPerl_object_property_init(integer__data); 
	SvREFCNT_inc(integer__data);



	integer__array_ref__CHECKTRACE(integer__data, "integer__data", "integer__bubblesort()");



	integer is_sorted = 0;

	integer i;


	AV* integer__data_av = (AV*) SvRV(integer__data);  
	const integer integer__data_length = av_len(integer__data_av) + 1;  
	SV* integer__data_i = newSV(0);  
	SV* integer__data_i_plus_1 = newSV(0);  


	SV* swap = newSV(0);










	while (not(is_sorted))

	{








		is_sorted = 1;

		for (i = 0; i < (integer__data_length - 1); i++)

		{











			integer__data_i = AV_ELEMENT(integer__data_av, i);  
			integer__data_i_plus_1 = AV_ELEMENT(integer__data_av, (i + 1));  

			
			if (SvIV(integer__data_i) > SvIV(integer__data_i_plus_1))  

			{



				is_sorted = 0;


				integer__data_i = AV_ELEMENT(integer__data_av, i);  
				swap = integer__data_i;  


				integer__data_i_plus_1 = AV_ELEMENT(integer__data_av, (i + 1));  
				av_store(integer__data_av, i, SvREFCNT_inc(integer__data_i_plus_1));  


				av_store(integer__data_av, (i + 1), SvREFCNT_inc(swap));  

			}





		}





	}


















	return(integer__data);

}

SV* number__bubblesort(SV* number__data)
{
	RPerl_object_property_init(number__data);
	SvREFCNT_inc(number__data);



	number__array_ref__CHECKTRACE(number__data, "number__data", "number__bubblesort()");

	integer is_sorted = 0;
	integer i;
	AV* number__data_av = (AV*) SvRV(number__data);
	const integer number__data_length = av_len(number__data_av) + 1;
	SV* number__data_i = newSV(0);
	SV* number__data_i_plus_1 = newSV(0);

	SV* swap = newSV(0);
	while (not(is_sorted))
	{
		is_sorted = 1;
		for (i = 0; i < (number__data_length - 1); i++)
		{
			number__data_i = AV_ELEMENT(number__data_av, i);
			number__data_i_plus_1 = AV_ELEMENT(number__data_av, (i + 1));

			if (SvNV(number__data_i) > SvNV(number__data_i_plus_1))
			{
				is_sorted = 0;
				number__data_i = AV_ELEMENT(number__data_av, i);
				swap = number__data_i;
				number__data_i_plus_1 = AV_ELEMENT(number__data_av, (i + 1));
				av_store(number__data_av, i, SvREFCNT_inc(number__data_i_plus_1));
				av_store(number__data_av, (i + 1), SvREFCNT_inc(swap));
			}
		}
	}
	return(number__data);
}




SV* uninherited__Bubble(SV* person) { cout << "in CPPOPS_PERLTYPES Bubble::uninherited__Bubble(), received person = '" << SvPV_nolen(person) << "', MITOCHONDRIAL\n"; return(newSVpv("Bubble::uninherited__Bubble() RULES! CPPOPS_PERLTYPES", 0)); }



SV* uninherited(SV* person) { cout << "in CPPOPS_PERLTYPES Bubble::uninherited(), received person = '" << SvPV_nolen(person) << "', TETRAHEDRON\n"; return(newSVpv("Bubble::uninherited() ROCKS! CPPOPS_PERLTYPES", 0)); }



SV* integer__bubblesort__typetest0(SV* lucky_integers)
{


	integer__array_ref__CHECKTRACE(lucky_integers, "lucky_integers", "integer__bubblesort__typetest0()");
	







	return(newSVpvf("%s%s", SvPV_nolen(integer__array_ref__stringify(integer__bubblesort(lucky_integers))), "CPPOPS_PERLTYPES"));
}

SV* number__bubblesort__typetest0(SV* lucky_numbers)
{

	number__array_ref__CHECKTRACE(lucky_numbers, "lucky_numbers", "number__bubblesort__typetest0()");
	

	return(newSVpvf("%s%s", SvPV_nolen(number__array_ref__stringify(number__bubblesort(lucky_numbers))), "CPPOPS_PERLTYPES"));
}





# elif defined __CPP__TYPES









void RPerl__Algorithm__Sort__Bubble::integer__sort()

{
	if (TEST_VERBOSE2) { fprintf(stderr, "in integer__sort(), top of subroutine, have this->integer__data = %s\n", integer__array_ref__stringify(this->integer__data).c_str()); }


	this->integer__data = integer__bubblesort(this->integer__data);

	if (TEST_VERBOSE2) { fprintf(stderr, "in integer__sort(), bottom of subroutine, have this->integer__data = %s\n", integer__array_ref__stringify(this->integer__data).c_str()); }

}

void RPerl__Algorithm__Sort__Bubble::number__sort()
{
	this->number__data = number__bubblesort(this->number__data);
}




void RPerl__Algorithm__Sort__Bubble::inherited__Bubble(string person) { cout << "in CPPOPS_CPPTYPES Bubble->inherited__Bubble(), received this = '" << this << "' and person = '" << person << "', FRIED\n"; }


void RPerl__Algorithm__Sort__Bubble::inherited(string person) { cout << "in CPPOPS_CPPTYPES Bubble->inherited(), received this = '" << this << "' and person = '" << person << "', ILLOGICAL\n"; }






integer__array_ref integer__bubblesort(integer__array_ref integer__data)  

{



	integer is_sorted = 0;

	integer i;

	const integer integer__data_length = integer__data.size();
	integer integer__data_i = -9999;  
	integer integer__data_i_plus_1 = -9999;  


	integer swap = -9999;










	while (not(is_sorted))

	{








		is_sorted = 1;

		for (i = 0; i < (integer__data_length - 1); i++)

		{











			integer__data_i = integer__data[i];  
			integer__data_i_plus_1 = integer__data[(i + 1)];  

			
			if (integer__data_i > integer__data_i_plus_1)  

			{



				is_sorted = 0;


				swap = integer__data_i;  


				integer__data[i] = integer__data_i_plus_1;  

				integer__data[(i + 1)] = swap;

			}





		}





	}








	return(integer__data);

}

number__array_ref number__bubblesort(number__array_ref number__data)
{

	integer is_sorted = 0;
	integer i;
	const integer number__data_length = number__data.size();
	number number__data_i = -9999;
	number number__data_i_plus_1 = -9999;
	number swap = -9999;
	while (not(is_sorted))
	{
		is_sorted = 1;
		for (i = 0; i < (number__data_length - 1); i++)
		{
			number__data_i = number__data[i];
			number__data_i_plus_1 = number__data[(i + 1)];
			if (number__data_i > number__data_i_plus_1)
			{
				is_sorted = 0;
				swap = number__data_i;
				number__data[i] = number__data_i_plus_1;
				number__data[(i + 1)] = swap;
			}
		}
	}
	return(number__data);
}




string uninherited__Bubble(string person) { cout << "in CPPOPS_CPPTYPES Bubble::uninherited__Bubble(), received person = '" << person << "', MITOCHONDRIAL\n"; return((string)"Bubble::uninherited__Bubble() RULES! CPPOPS_CPPTYPES"); }



string uninherited(string person) { cout << "in CPPOPS_CPPTYPES Bubble::uninherited(), received person = '" << person << "', TETRAHEDRON\n"; return((string)"Bubble::uninherited() ROCKS! CPPOPS_CPPTYPES"); }



string integer__bubblesort__typetest0(integer__array_ref lucky_integers)
{
    
    return(integer__array_ref__stringify(integer__bubblesort(lucky_integers)) + "CPPOPS_CPPTYPES");
}

string number__bubblesort__typetest0(number__array_ref lucky_numbers)
{
    
    return(number__array_ref__stringify(number__bubblesort(lucky_numbers)) + "CPPOPS_CPPTYPES");
}





# else

Purposefully_die_from_a_compile-time_error,_due_to_neither___PERL__TYPES_nor___CPP__TYPES_being_defined.__We_need_to_define_exactly_one!

# endif

#endif
