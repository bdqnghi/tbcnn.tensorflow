#pragma once

#include "Cpp/Features.h"
#include "Cpp/Warnings.h"

#include "Concepts/Range.h"
#include "Concepts/RangeOf.h"

#include "Funal/Op.h"

INTRA_PUSH_DISABLE_REDUNDANT_WARNINGS

namespace Intra { namespace Range {

namespace D {

template<typename T, typename C> void heap_shift_down(T arr[], size_t i, size_t j, C comparer)
{
	while(i*2+1<j)
	{
		size_t maxNodeId = i*2+2;
		if(i*2+1==j-1 || comparer(arr[i*2+2], arr[i*2+1])) maxNodeId--;

		if(!comparer(arr[i], arr[maxNodeId])) break;

		Cpp::Swap(arr[i], arr[maxNodeId]);
		i = maxNodeId;
	}
}

}

//! Пирамидальная сортировка массива array с предикатом сравнения comparer.
//! Характеристики алгоритма:
//! - Гарантированная сложность: O(n Log n);
//! - Неустойчив;
//! - На почти отсортированных массивах работает так же долго, как и для хаотичных данных;
//! - Для N меньше нескольких тысяч ShellSort быстрее.
template<typename R, typename C=Funal::TLess> Meta::EnableIf<
	Concepts::IsAssignableArrayClass<R>::_
> HeapSort(R&& range, C comparer = Funal::Less)
{
	const size_t count = Concepts::LengthOf(range);

	//Строим дерево поиска
	for(size_t i=count/2; i>0; i--)
		D::heap_shift_down(Concepts::DataOf(range), i-1, count, comparer);

	//Забираем максимальный (0) элемент дерева в i-ю позицию
	//Перемещаем новый 0 элемент на правильную позицию в дереве
	for(size_t i=count-1; i>0; i--)
	{
		Cpp::Swap(range[0], range[i]);
		D::heap_shift_down(Concepts::DataOf(range), 0, i, comparer);
	}
}

}}

INTRA_WARNING_POP
