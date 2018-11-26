//
//  RodCutting.cpp
//  HW_C1
//
//  Created by JinWoo Lee on 2014. 8. 6..
//  Copyright (c) 2014년 JinWoo Lee. All rights reserved.
//

#include "RodCutting.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

int rod_cutting_combination_recursion( int * price, int length, int * cut_pos, int cur_pos );
int rod_cutting_top_down_recursion( int * price, int length, int * max_price );


int rod_cutting_combination( int * price, int length )
{
	int cut_pos[length];
	
	for( int i = 0; i < length; ++i )
		cut_pos[i] = 0;

	return rod_cutting_combination_recursion( price, length, cut_pos, 0 );
}

int rod_cutting_combination_recursion( int * price, int length, int * cut_pos, int cur_pos )
{
	if ( cur_pos == length )
	{
		int value = 0;
		int last_cut_pos = 0;

		for( int i = 0; i < length; ++i )
		{
			if ( cut_pos[i] )
			{
				value += price[ i - last_cut_pos ];
				last_cut_pos = i;
			}
		}

		value += price[ length - last_cut_pos ];
		
		return value;
	}
	
	cut_pos[cur_pos] = 0;
	int nocut_value = rod_cutting_combination_recursion( price, length, cut_pos, cur_pos + 1 );
	cut_pos[cur_pos] = 1;
	int cut_value = rod_cutting_combination_recursion( price, length, cut_pos, cur_pos + 1 );

	return MAX(nocut_value, cut_value);
}

int rod_cutting_first_cut( int * price, int length )
{
	int max_price = price[length];

	int half = length / 2;
	for( int i = 1; i <= half; ++i )
	{
		int sum = price[i] + rod_cutting_first_cut( price, length - i );
		max_price = MAX( max_price, sum );
	}
	
	return max_price;
}

int rod_cutting_top_down( int * price, int length )
{
	int max_price[length + 1];
	
	for ( int i = 0; i <= length; ++i )
		max_price[i] = -1;

	return rod_cutting_top_down_recursion( price, length, max_price );
}

int rod_cutting_top_down_recursion( int * price, int length, int * max_price )
{
	if ( max_price[length] < 0 )
	{
		max_price[length] = price[length];

		int half = length / 2;
		for ( int i = 1; i <= half; ++i )
		{
			int sum = price[i] + rod_cutting_top_down_recursion( price, length - i, max_price );
			max_price[length] = MAX( max_price[length], sum );
		}
	}

	return max_price[length];
}

int rod_cutting_bottom_up( int * price, int length )
{
	int max_price[length + 1];
	
	for( int i = 0; i <= length; ++i )
	{
		max_price[i] = price[i];
		
		for ( int j = 1; j < i; ++j )
		{
			max_price[i] = MAX( max_price[i], price[j] + max_price[i - j] );
		}
	}
	
	return max_price[length];
}

int rod_cutting_pieces( int * price, int length, int * piece )
{
	int max_price[length + 1];
	
	for( int i = 0; i <= length; ++i )
	{
		max_price[i] = price[i];
		piece[i] = i;
		
		for ( int j = 1; j < i; ++j )
		{
			int new_price = price[j] + max_price[i - j];
			if( new_price > max_price[i] )
			{
				max_price[i] = new_price;
				piece[i] = j;
			}
		}
	}
	
	return max_price[length];
}
