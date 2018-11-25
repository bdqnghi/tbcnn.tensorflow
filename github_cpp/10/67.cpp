 

#ifndef SEQAN_HEADER_SCORE_EDIT_H
#define SEQAN_HEADER_SCORE_EDIT_H

namespace SEQAN_NAMESPACE_MAIN
{







template <typename TValue>
class Score<TValue, EditDistance>
{
public:
	Score()
	{
	}

	Score(Score const &)
	{
	}
	~Score()
	{
	}

	Score & operator = (Score const &)
	{
		return *this;
	}


};




typedef Score<int, EditDistance> EditDistanceScore;



template <typename TValue>
inline TValue
scoreMatch(Score<TValue, EditDistance> &)
{
	return 0;
}

template <typename TValue>
inline TValue
scoreMatch(Score<TValue, EditDistance> const &)
{
	return 0;
}

template <typename TValue>
inline TValue
scoreMismatch(Score<TValue, EditDistance> &)
{
	return -1;
}

template <typename TValue>
inline TValue
scoreMismatch(Score<TValue, EditDistance> const &)
{
	return -1;
}

template <typename TValue>
inline TValue
scoreGapExtend(Score<TValue, EditDistance> &)
{
	return -1;
}

template <typename TValue>
inline TValue
scoreGapExtend(Score<TValue, EditDistance> const &)
{
	return -1;
}

template <typename TValue>
inline TValue
scoreGapOpen(Score<TValue, EditDistance> &)
{
	return -1;
}

template <typename TValue>
inline TValue
scoreGapOpen(Score<TValue, EditDistance> const &)
{
	return -1;
}





}

#endif 
