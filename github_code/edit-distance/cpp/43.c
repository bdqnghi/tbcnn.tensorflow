#ifndef FSDICT_LEVDEA_H
#define FSDICT_LEVDEA_H FSDICT_LEVDEA_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>

#include "../Global.h"
#include "./AutData.h"
namespace fsdict {

    /**
     * LevDEA gives access to deterministic levenshtein automata.
     * It is an implementation of the concepts described in
     * "S. Mihov and K. Schulz. Fast approximate search in large dictionaries. Computational Linguistics, 30, 2004."
     *
     * @caution This class is one huge memory leak!!!
     *
     * @author Ulrich Reffle
     * @date 2006
     */
    class FSDICT_DECLSPEC LevDEA {

    public:
	/**
	 * @brief External representation of a state of the Levenshtein Automaton
	 */
	class Pos {
	private:
	    /// holds the current position in the automaton (may be equal to -1)
	    int position_;
	    /// holds the current position in the pattern
	    size_t patternPos_;

	public:
	    /**
	     * @brief Constructor, optional values for position and patternPos
	     */
	    Pos( int position = 0, size_t patternPos = 0 ) {
		position_ = position;
		patternPos_ = patternPos;
	    }

	    /**
	     * @brief Returns the position in the Lev. automaton.
	     */
	    inline int position() const {
		return position_;
	    }

	    /**
	     * @brief Returns the position in the pattern.
	     */
	    inline size_t patternPos() const {
		return patternPos_;
	    }

	    /**
	     * @brief Set new values for positions in the automaton and the pattern.
	     */
	    inline void set( int position, size_t patternPos ) {
		position_ = position;
		patternPos_ = patternPos;
	    };

	    /**
	     * @brief Returns true iff the current state is a valid one, returns false iff it is a fail state (or: trap state).
	     */
	    inline bool isValid() const {
		return ( position() != -1 );
	    }
	};

	/**
	 * @brief A regular constructor.
	 */
	LevDEA( int init_k = 0 );

	/**
	 * @brief A regular destructor.
	 */
	~LevDEA();

	/**
	 * @brief Returns the root state (at the root of the automaton, and the start of the pattern.)
	 */
	inline Pos getRoot() const {
	    return Pos( 0, 0 );
	}


	/**
	 * Follow a transition in the automaton. Input-char c is translated into
	 * a bit-vector which then is used as "input symbol" for the automaton.
	 *
	 * @param p a start position in the automaton
	 * @param c a character
	 * @return the new position
	 */
	inline Pos walk( const Pos& p, wchar_t c ) const;

	/**
	 * do a walk sequentially for a std::wstring.
	 *
	 * @param p a start position in the automaton
	 * @param str a const reference to a std::wstring
	 * @return the new position
	 */
	inline Pos walkStr( const Pos& p, const std::wstring& str ) const;

	/**
	 * do a walk sequentially for a c-string
	 *
	 * @param p a start position in the automaton
	 * @param str a c-string
	 * @return the new position
	 */
	inline Pos walkStr( const Pos& p, const wchar_t* str ) const;

	/**
	 * Returns true iff state p is a position standing for a final state
	 * @param p a position in the automaton
	 * @return true iff state p is a position standing for a final state
	 */
	inline bool isFinal( const Pos& p ) const;

	/**
	 * @brief Returns the lev. distance for a match at that position.
	 */
	inline int getDistance( const Pos& p ) const;

	inline bool startSuffixMatch( const Pos& p ,std::vector< size_t >* patternStartPositions );

	/**
	 * @brief Returns the current search pattern.
	 */
	const std::wstring& getPattern() {
	    return pattern_;
	}

	/**
	 * @brief Set a max Levenshtein distance for matching.
	 */
	void setThreshold( size_t k );

	size_t getThreshold() const;

	/**
	 * @brief Load a new search pattern.
	 */
	void loadPattern( const wchar_t* p );

	/**
	 * @brief Load a new search pattern, pass a utf8-encoded single-byte string.
	 */
	void loadPattern_utf8( const char* p );

	// used for debug only
	void printTable() const;
	void printCharvec() const;
	void printBits( const bits64& ) const;


    private:

	inline int getTransition( int state, bits64 charvec ) const;


	/// holds the current pattern
	std::wstring pattern_;

	/// k is the max levenshtein-distance
	size_t k_;


	void cleanCharvecs();
	void calcCharvec();

	inline bits64 charvec2snippet( wchar_t c, size_t patternPos ) const;

	// some bitvectors
	uint_t z2k1;
	uint_t z2k2;

	int const* transitions_;
	int const* finalInfo_;
	bits64 const* suffixMatch_;

	std::vector< bits64 > charvecs_;

	/// The length of the bit-vector used as transition labels.
	size_t bitVectorLength_;

	/// The number of outgoing transitions of each state.
	size_t nrOfTransitions_;

	size_t zeroShift_;

	static const bits64 zff = 0xffffffffffffffffll; // that's 64 '1's
	static const bits64 z10 = 1ll << 63; // that's a '1' followed by 63 '0's

    };



    inline LevDEA::Pos LevDEA::walk( const Pos& p, wchar_t c ) const {
        if( static_cast< size_t >( c ) > Global::maxNrOfChars ) {
	  throw exceptions::badInput( "fsdict::LevDEA::walk: Can't walk with a char > Global::maxNrOfChars." );
	}
	return Pos( getTransition( p.position(), charvec2snippet( c, p.patternPos() ) ), p.patternPos() + 1 );
    }

    inline LevDEA::Pos LevDEA::walkStr( const Pos& position, const std::wstring& str ) const {
	return walkStr( position, str.c_str() );
    }

    inline LevDEA::Pos LevDEA::walkStr( const Pos& position, const wchar_t* str ) const {
	LevDEA::Pos p = position;

	while( *str && p.isValid() ) {
	    p = walk( p, *str );
	    ++str;
	}
	return p;
    }


    inline bool LevDEA::isFinal( const Pos& p ) const {
	return getDistance(p) > -1;
    }

    inline int LevDEA::getDistance( const Pos& p ) const {
	if( ! p.isValid() ) {
	    throw exceptions::fsdictException("Can't call getDistance for fail state.");
	}
	int finalInfoOffset = pattern_.length() - p.patternPos() + zeroShift_;
	if( finalInfoOffset > static_cast< int >( bitVectorLength_ - 1 ) ) {
	    return -1;
	}
	else if( finalInfoOffset >= 0 ) {
	    return finalInfo_[p.position()*bitVectorLength_ + finalInfoOffset];
	}
	else {
	    return -1;
	}
    }


    inline bool LevDEA::startSuffixMatch( const Pos& p ,std::vector< size_t >* patternStartPositions ) {
	// std::wcout << "pos=" << p.position() << std::endl;
	bits64 v = suffixMatch_[p.position()];
	// std::wcout << "v=" << v << std::endl;
	if( suffixMatch_[p.position()] == 0 ) {
	    return false;
	}

	bits64 bit = 1L << ( bitVectorLength_ - 1 );
	size_t startPos;
	for( size_t i = 0; i < bitVectorLength_; ++i ) {
	    if( bit & v ) {
		startPos = p.patternPos() - zeroShift_ + i;
		if( startPos >= 0 && startPos < pattern_.length() ) {
		    patternStartPositions->push_back( startPos );
		}
	    }
	    bit >>= 1;
	}
	return true;
    }

    inline int LevDEA::getTransition( int state, bits64 charvec ) const {
	// the state ids are consecutive numbers, each has exactly nrOfTransitions_ transitions in the table.
	return transitions_[state*nrOfTransitions_ + charvec];
    }

    bits64 LevDEA::charvec2snippet( wchar_t c, size_t patternPos ) const {
	bits64 r = 0;
	int shiftRight = (pattern_.length() - patternPos - 1 - zeroShift_ );
	if( shiftRight > 0 ) r = ( charvecs_[c] >> shiftRight );
	else            r = ( charvecs_[c] << -shiftRight );
	return ( r & z2k1 );
    }

} // eon

#endif
