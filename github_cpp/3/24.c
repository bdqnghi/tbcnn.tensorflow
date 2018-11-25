



#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_


#include <util/avl_tree.h>

namespace Local {

	template <typename> class Avl_node;
	template <typename> class Avl_tree;
}



template <typename NT>
struct Local::Avl_node : Genode::Avl_node<NT>
{
	using Base = Genode::Avl_node<NT>;

	template <typename FUNC>
	void for_each(FUNC && functor)
	{
		if (NT * l = Base::child(Avl_node<NT>::LEFT))  l->for_each(functor);
		functor(*static_cast<NT *>(this));
		if (NT * r = Base::child(Avl_node<NT>::RIGHT)) r->for_each(functor);
	}
};



template <typename NT>
struct Local::Avl_tree : Genode::Avl_tree<NT>
{
	using Base = Genode::Avl_tree<NT>;

	template <typename FUNC>
	void for_each(FUNC && functor) {
		if (Base::first()) Base::first()->for_each(functor); }
};


#endif 
