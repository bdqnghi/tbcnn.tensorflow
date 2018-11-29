#include "merge_actor.cpp"

#ifndef SORT_ACTOR_INCLUDED
	#include "sort_actor.h"
#endif // !SORT_ACTOR_INCLUDED

enum side 
{
	NONE = 0, LEFT = (1 << 0), RIGHT = (1 << 1), ALL = (LEFT | RIGHT)
};

struct merge_sort_chan;
struct merge_sort_proc;

struct merge_sort_chan : sort_chan
{
	side part;

	merge_sort_chan(std::vector<int> * data, int start, int end, sort_proc * source, side part)
		: sort_chan(data, start, end, source)
		, part(part)
	{ }
};

struct merge_sort_proc : sort_proc 
{
	int already_sorted_parts;

	merge_sort_proc(engine * e)
		: sort_proc(e)
		, already_sorted_parts(NONE)
	{ }

	void sort(std::vector<int> * data, int start, int end, sort_chan * sortChan)
	{
		if (sortChan -> source == this)
		{
			if (merge_chan * mergeChan = dynamic_cast<merge_chan*>(sortChan))
			{
				notify_about_sorted();
			}
			else if (merge_sort_chan * mergeSortChan = dynamic_cast<merge_sort_chan*>(sortChan))
			{
				already_sorted_parts |= mergeSortChan -> part;
				if (already_sorted_parts == ALL)
				{
					int mid = (
						mergeSortChan -> part == LEFT 
						? mergeSortChan -> end 
						: mergeSortChan -> start - 1
						);

					merge_chan * mergeChan = new merge_chan(data, source_chan -> start, mid, source_chan -> end, this);
					merge_proc * mergeProc = new merge_proc(e);

					send(e, mergeChan, mergeProc);
				}
			}
		}
		else
		{
			if (start < end) 
			{
				int mid = (start + end) / 2;

				sort_chan * leftSortChan = new merge_sort_chan(data, start, mid, this, LEFT);
				merge_sort_proc * leftSortProc = new merge_sort_proc(e);

				send(e, leftSortChan, leftSortProc);

				sort_chan * rightSortChan = new merge_sort_chan(data, mid + 1, end, this, RIGHT);
				merge_sort_proc * rightSortProc = new merge_sort_proc(e);
				
				send(e, rightSortChan, rightSortProc);
			}
			else 
			{
				notify_about_sorted();
			}
		}
	}
};