#ifndef CSL_LEVDEA_H
#define CSL_LEVDEA_H CSL_LEVDEA_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>

#include "../Global.h"

namespace csl {

    /**
     * LevDEA gives access to deterministic levenshtein automata.
     * It is an implementation of the concepts described in
     * "S. Mihov and K. Schulz. Fast approximate search in large dictionaries. Computational Linguistics, 30, 2004."
     * *** Honestly, a somewhat older approach is used, not exactly the one described in the paper ***
     * Basically the implementation is derived from a C-implementation of Stoyan Mihov.
     * 
     * @caution This class is one huge memory leak!!!
     *
     * @author Ulrich Reffle, <uli@reffle.de>
     * @date 2006
     */
    class LevDEA {

    public:
	class Pos {
	private:
	    /// holds the current position in the automaton
	    int position_;
	    /// holds the current position in the pattern
	    size_t pattern_pos_;

	public:
	    Pos( size_t position = 0, size_t pattern_pos = 0 ) {
		position_ = position;
		pattern_pos_ = pattern_pos;
	    }

	    inline int position() const {
		return position_;
	    }
	    inline size_t pattern_pos() const {
		return pattern_pos_;
	    }
	    inline void set( size_t position, size_t pattern_pos ) {
		position_ = position;
		pattern_pos_ = pattern_pos;
	    };

	    inline bool isValid() const {
		return ( position() != -1 );
	    }
	};

	LevDEA( int init_k = 0 );


	~LevDEA();

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
	 * do a walk sequentially for a string
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
	 * 
	 */
	inline int getDistance( const Pos& p ) const;

	wchar_t* getPattern() {
	    return pattern_;
	}

	/**
	 *
	 * @todo do sth about the paths to the levenshtein tables
	 */
	void setDistance( int k );

	void loadPattern( const wchar_t* p );

	// used for debug only
	void printTable() const;
	void printCharvec() const;
	void printBits( const bits64& ) const;


    private:
	typedef std::vector< size_t > State;

	/// holds the current pattern
	wchar_t pattern_[Global::lengthOfWord];

	/// holds the pattern length
	size_t patLength_;


	/// tab holds the transition table of the automaton
	table_cell* tab;

	// easy access to the table
	inline table_cell& table( const size_t row, const size_t col ) const {
//	    printf("access at row=%d, col=%d\n", row, col );
	    assert( row < z2k2 );
	    assert( col < coresets );
	    return tab[coresets*( row )+( col )];
	}
	inline int fin_table( int row, int col ) const {
	    //      std::cerr<<row<<","<<col<<std::endl;
	    return fin[coresets*( row )+( col )];
	}


	/// fin holds the information about final states
	int *fin;
	/// k is the max levenshtein-distance
	size_t k_;
	/// coresets is the number of distinct configurations of a triangular region (depends on k)
	size_t coresets;

	std::vector< unsigned long long > charvecs_;

	void cleanCharvecs();
	void calcCharvec();

	bits32 calc_k_charvec( wchar_t c, size_t i ) const;


	// some bitvectors
	uint_t z2k1;
	uint_t z2k2;

	bits32 tabsLoaded_;
	table_cell* tabs[4];
	int* fins[4];
	size_t coresetss[4];

	static const bits64 zff = 0xffffffffffffffffll; // that's 64 '1's
	static const bits64 z10 = 1ll << 63; // that's a '1' followed by 63 '0's

	static const int lev0data[];
        static const int lev1data[];
        static const int lev2data[];
        static const int lev3data[];

    };



    inline LevDEA::Pos LevDEA::walk( const Pos& p, wchar_t c ) const {
	table_cell & cell = table( calc_k_charvec( c, p.pattern_pos() ), p.position() );
	return Pos( cell.target, p.pattern_pos() + cell.move_pattern );
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
	//         |  triangle has reached right bound |            |       fin_table gives dist >-1                                       |
	return ( ( patLength_ - p.pattern_pos() < 2 * k_ + 1 ) && ( fin_table( 2*k_ -( patLength_ - p.pattern_pos() ), p.position() ) != -1 ) );
    }

    inline int LevDEA::getDistance( const Pos& p ) const {
	if ( patLength_ - p.pattern_pos() >= 2 * k_ + 1 ) return -1;
	return fin_table( 2 * k_ - ( patLength_ - p.pattern_pos() ), p.position() );
    }

} // eon

#endif
