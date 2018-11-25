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

    
    class FSDICT_DECLSPEC LevDEA {

    public:
	
	class Pos {
	private:
	    
	    int position_;
	    
	    size_t patternPos_;

	public:
	    
	    Pos( int position = 0, size_t patternPos = 0 ) {
		position_ = position;
		patternPos_ = patternPos;
	    }

	    
	    inline int position() const {
		return position_;
	    }

	    
	    inline size_t patternPos() const {
		return patternPos_;
	    }

	    
	    inline void set( int position, size_t patternPos ) {
		position_ = position;
		patternPos_ = patternPos;
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

	
	inline Pos walkStr( const Pos& p, const std::wstring& str ) const;

	
	inline Pos walkStr( const Pos& p, const wchar_t* str ) const;

	
	inline bool isFinal( const Pos& p ) const;

	
	inline int getDistance( const Pos& p ) const;

	inline bool startSuffixMatch( const Pos& p ,std::vector< size_t >* patternStartPositions );

	
	const std::wstring& getPattern() {
	    return pattern_;
	}

	
	void setThreshold( size_t k );

	size_t getThreshold() const;

	
	void loadPattern( const wchar_t* p );

	
	void loadPattern_utf8( const char* p );

	
	void printTable() const;
	void printCharvec() const;
	void printBits( const bits64& ) const;


    private:

	inline int getTransition( int state, bits64 charvec ) const;


	
	std::wstring pattern_;

	
	size_t k_;


	void cleanCharvecs();
	void calcCharvec();

	inline bits64 charvec2snippet( wchar_t c, size_t patternPos ) const;

	
	uint_t z2k1;
	uint_t z2k2;

	int const* transitions_;
	int const* finalInfo_;
	bits64 const* suffixMatch_;

	std::vector< bits64 > charvecs_;

	
	size_t bitVectorLength_;

	
	size_t nrOfTransitions_;

	size_t zeroShift_;

	static const bits64 zff = 0xffffffffffffffffll; 
	static const bits64 z10 = 1ll << 63; 

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
	
	bits64 v = suffixMatch_[p.position()];
	
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
	
	return transitions_[state*nrOfTransitions_ + charvec];
    }

    bits64 LevDEA::charvec2snippet( wchar_t c, size_t patternPos ) const {
	bits64 r = 0;
	int shiftRight = (pattern_.length() - patternPos - 1 - zeroShift_ );
	if( shiftRight > 0 ) r = ( charvecs_[c] >> shiftRight );
	else            r = ( charvecs_[c] << -shiftRight );
	return ( r & z2k1 );
    }

} 

#endif
