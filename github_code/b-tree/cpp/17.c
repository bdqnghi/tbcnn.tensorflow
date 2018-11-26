////////////////////////////////////////////////////////////////////////////
//	Created		: 26.03.2010
//	Author		: Dmitriy Iassenev
//	Copyright (C) GSC Game World - 2010
////////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "mixing_n_ary_tree_node_comparer.h"
#include "mixing_n_ary_tree_animation_node.h"
#include "mixing_n_ary_tree_weight_node.h"
#include "mixing_n_ary_tree_addition_node.h"
#include "mixing_n_ary_tree_subtraction_node.h"
#include "mixing_n_ary_tree_multiplication_node.h"
#include "mixing_n_ary_tree_transition_node.h"

using xray::animation::mixing::n_ary_tree_node_comparer;
using xray::animation::mixing::n_ary_tree_animation_node;
using xray::animation::mixing::n_ary_tree_weight_node;
using xray::animation::mixing::n_ary_tree_addition_node;
using xray::animation::mixing::n_ary_tree_subtraction_node;
using xray::animation::mixing::n_ary_tree_multiplication_node;
using xray::animation::mixing::n_ary_tree_transition_node;
using xray::animation::mixing::n_ary_tree_base_node;

n_ary_tree_node_comparer::enum_result n_ary_tree_node_comparer::compare	(
		n_ary_tree_base_node& left,
		n_ary_tree_base_node& right
	)
{
	result				= equal;
	left.accept			( *this, right );
	return				result;
}

////////////////////////////////////////////////////////////////////////////
// n_ary_tree_animation_node
////////////////////////////////////////////////////////////////////////////
void n_ary_tree_node_comparer::dispatch	( n_ary_tree_animation_node& left,		n_ary_tree_animation_node& right )
{
	result				= left < right ? less : right < left ? more : equal;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_animation_node& left,		n_ary_tree_weight_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_animation_node& left,		n_ary_tree_addition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_animation_node& left,		n_ary_tree_subtraction_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_animation_node& left,		n_ary_tree_multiplication_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_animation_node& left,		n_ary_tree_transition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

////////////////////////////////////////////////////////////////////////////
// n_ary_tree_transition_node
////////////////////////////////////////////////////////////////////////////
void n_ary_tree_node_comparer::dispatch	( n_ary_tree_transition_node& left,		n_ary_tree_animation_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_transition_node& left,		n_ary_tree_transition_node& right )
{
	left.from().accept	( *this, right.from() );
	if ( result != equal )
		return;

	left.to().accept	( *this, right.to() );
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_transition_node& left,		n_ary_tree_weight_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_transition_node& left,		n_ary_tree_addition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_transition_node& left,		n_ary_tree_subtraction_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_transition_node& left,		n_ary_tree_multiplication_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

////////////////////////////////////////////////////////////////////////////
// n_ary_tree_weight_node
////////////////////////////////////////////////////////////////////////////
void n_ary_tree_node_comparer::dispatch	( n_ary_tree_weight_node& left,			n_ary_tree_animation_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_weight_node& left,			n_ary_tree_transition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_weight_node& left,			n_ary_tree_weight_node& right )
{
	result				= left < right ? less : right < left ? more : equal;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_weight_node& left,			n_ary_tree_addition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_weight_node& left,			n_ary_tree_subtraction_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_weight_node& left,			n_ary_tree_multiplication_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

////////////////////////////////////////////////////////////////////////////
// n_ary_tree_addition_node
////////////////////////////////////////////////////////////////////////////
void n_ary_tree_node_comparer::dispatch	( n_ary_tree_addition_node& left,		n_ary_tree_animation_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_addition_node& left,		n_ary_tree_transition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_addition_node& left,		n_ary_tree_weight_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_addition_node& left,		n_ary_tree_addition_node& right )
{
	propagate			( left, right );
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_addition_node& left,		n_ary_tree_subtraction_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_addition_node& left,		n_ary_tree_multiplication_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

////////////////////////////////////////////////////////////////////////////
// n_ary_tree_subtraction_node
////////////////////////////////////////////////////////////////////////////
void n_ary_tree_node_comparer::dispatch	( n_ary_tree_subtraction_node& left,		n_ary_tree_animation_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_subtraction_node& left,		n_ary_tree_transition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_subtraction_node& left,		n_ary_tree_weight_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_subtraction_node& left,		n_ary_tree_addition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_subtraction_node& left,		n_ary_tree_subtraction_node& right )
{
	propagate			( left, right );
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_subtraction_node& left,		n_ary_tree_multiplication_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= less;
}

////////////////////////////////////////////////////////////////////////////
// n_ary_tree_multiplication_node
////////////////////////////////////////////////////////////////////////////
void n_ary_tree_node_comparer::dispatch	( n_ary_tree_multiplication_node& left,	n_ary_tree_animation_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_multiplication_node& left,	n_ary_tree_transition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_multiplication_node& left,	n_ary_tree_weight_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_multiplication_node& left,	n_ary_tree_addition_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_multiplication_node& left,	n_ary_tree_subtraction_node& right )
{
	XRAY_UNREFERENCED_PARAMETER	( left );
	XRAY_UNREFERENCED_PARAMETER	( right );
	result				= more;
}

void n_ary_tree_node_comparer::dispatch	( n_ary_tree_multiplication_node& left,	n_ary_tree_multiplication_node& right )
{
	propagate			( left, right );
}

template <typename T>
inline void n_ary_tree_node_comparer::propagate	( T& left, T& right )
{
	ASSERT				( result == equal );

	u32 const left_operands_count	= left.operands_count();
	u32 const right_operands_count	= right.operands_count();
	n_ary_tree_base_node* const* i			= left.operands( sizeof(T) );
	n_ary_tree_base_node* const* const i_e	= i + left_operands_count;
	n_ary_tree_base_node* const* j			= right.operands( sizeof(T) );
	n_ary_tree_base_node* const* const j_e	= j + right_operands_count;
	for ( ; (i != i_e) && (j != j_e); ++i, ++j ) {
		(*i)->accept	( *this, **j );
		
		if ( result != equal )
			return;
	}

	ASSERT				( result == equal );
	ASSERT				( (i == i_e) || (j == j_e) );
	if ( i != i_e )
		result			= more;
	else
		if ( j != j_e )
			result		= less;
}