#ifndef CSL_LEVDEA_H
#define CSL_LEVDEA_H CSL_LEVDEA_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>

#include "../Global.h"

namespace csl {

    
    class LevDEA {

    public:
	class Pos {
	private:
	    
	    int position_;
	    
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


	
	inline Pos walk( const Pos& p, wchar_t c ) const;

	
	inline Pos walkStr( const Pos& p, const wchar_t* str ) const;
	

	
	inline bool isFinal( const Pos& p ) const;

	
	inline int getDistance( const Pos& p ) const;

	wchar_t* getPattern() {
	    return pattern_;
	}

	
	void setDistance( int k );

	void loadPattern( const wchar_t* p );

	
	void printTable() const;
	void printCharvec() const;
	void printBits( const bits64& ) const;


    private:
	typedef std::vector< size_t > State;

	
	wchar_t pattern_[Global::lengthOfWord];

	
	size_t patLength_;


	
	table_cell* tab;

	
	inline table_cell& table( const size_t row, const size_t col ) const {

	    assert( row < z2k2 );
	    assert( col < coresets );
	    return tab[coresets*( row )+( col )];
	}
	inline int fin_table( int row, int col ) const {
	    
	    return fin[coresets*( row )+( col )];
	}


	
	int *fin;
	
	size_t k_;
	
	size_t coresets;

	std::vector< unsigned long long > charvecs_;

	void cleanCharvecs();
	void calcCharvec();

	bits32 calc_k_charvec( wchar_t c, size_t i ) const;


	
	uint_t z2k1;
	uint_t z2k2;

	bits32 tabsLoaded_;
	table_cell* tabs[4];
	int* fins[4];
	size_t coresetss[4];

	static const bits64 zff = 0xffffffffffffffffll; 
	static const bits64 z10 = 1ll << 63; 

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
	
	return ( ( patLength_ - p.pattern_pos() < 2 * k_ + 1 ) && ( fin_table( 2*k_ -( patLength_ - p.pattern_pos() ), p.position() ) != -1 ) );
    }

    inline int LevDEA::getDistance( const Pos& p ) const {
	if ( patLength_ - p.pattern_pos() >= 2 * k_ + 1 ) return -1;
	return fin_table( 2 * k_ - ( patLength_ - p.pattern_pos() ), p.position() );
    }

} 

#endif
