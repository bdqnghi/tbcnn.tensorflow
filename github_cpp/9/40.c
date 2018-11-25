

































#ifndef SEQAN_HEADER_MODIFIER_SHORTCUTS_H
#define SEQAN_HEADER_MODIFIER_SHORTCUTS_H

namespace seqan
{































typedef ModView<FunctorComplement<Dna> >    ModComplementDna;
typedef ModView<FunctorComplement<Dna5> >    ModComplementDna5;
typedef ModView<FunctorComplement<Rna> >    ModComplementRna;
typedef ModView<FunctorComplement<Rna5> >    ModComplementRna5;

template <typename THost>
struct ReverseString
{
    typedef ModifiedString<THost, ModReverse> Type;
};

template <typename THost>
struct ComplementString
{
    typedef ModifiedString<THost, ModView<FunctorComplement<typename Value<THost>::Type> > > Type;
};

template <typename THost>
struct ReverseComplementString
{
    typedef typename ReverseString<typename ComplementString<THost>::Type>::Type Type;
};



typedef ComplementString<DnaString>::Type           DnaStringComplement;
typedef ComplementString<Dna5String>::Type          Dna5StringComplement;
typedef ComplementString<RnaString>::Type           RnaStringComplement;
typedef ComplementString<Rna5String>::Type          Rna5StringComplement;

typedef ReverseString<DnaString>::Type              DnaStringReverse;
typedef ReverseString<Dna5String>::Type             Dna5StringReverse;
typedef ReverseString<RnaString>::Type              RnaStringReverse;
typedef ReverseString<Rna5String>::Type             Rna5StringReverse;

typedef ReverseComplementString<DnaString>::Type    DnaStringReverseComplement;
typedef ReverseComplementString<Dna5String>::Type    Dna5StringReverseComplement;
typedef ReverseComplementString<RnaString>::Type    RnaStringReverseComplement;
typedef ReverseComplementString<Rna5String>::Type    Rna5StringReverseComplement;







template <typename TSequence >
inline void complement(TSequence & sequence)
{
    convert(sequence, FunctorComplement<typename Value<TSequence>::Type>());
}

template <typename TSequence >
inline void complement(TSequence const & sequence)
{
    convert(sequence, FunctorComplement<typename Value<TSequence>::Type>());
}





template < typename TSequence, typename TSpec >
inline void complement(StringSet<TSequence, TSpec> & stringSet)
{
    unsigned seqCount = length(stringSet);
    for(unsigned seqNo = 0; seqNo < seqCount; ++seqNo)
        complement(stringSet[seqNo]);
}

template < typename TSequence, typename TSpec >
inline void complement(StringSet<TSequence, TSpec> const & stringSet)
{
    unsigned seqCount = length(stringSet);
    for(unsigned seqNo = 0; seqNo < seqCount; ++seqNo)
        complement(stringSet[seqNo]);
}





template <typename THost>
inline ModifiedString<THost, ModView<FunctorComplement<typename Value<THost>::Type> > >
complementString(THost & host)
{
    return ModifiedString<THost, ModView<FunctorComplement<typename Value<THost>::Type> > >(host);
}

template <typename THost>
inline ModifiedString<THost const, ModView<FunctorComplement<typename Value<THost>::Type> > >
complementString(THost const & host)
{
    return ModifiedString<THost const, ModView<FunctorComplement<typename Value<THost>::Type> > >(host);
}








template < typename TSequence, typename TParallelTag >
inline void reverseComplement(TSequence & sequence, Tag<TParallelTag> parallelTag)
{
    complement(sequence);
    reverse(sequence, parallelTag);
}



template < typename TSequence, typename TParallelTag >
inline void reverseComplement(TSequence const & sequence, Tag<TParallelTag> parallelTag)
{
    complement(sequence);
    reverse(sequence, parallelTag);
}

template < typename TSequence, typename TSpec, typename TParallelTag >
inline void reverseComplement(StringSet<TSequence, TSpec> & stringSet, Tag<TParallelTag>)
{
    int seqCount = length(stringSet);
    SEQAN_OMP_PRAGMA(parallel for if(IsSameType<Tag<TParallelTag>, Parallel>::VALUE))
    for(int seqNo = 0; seqNo < seqCount; ++seqNo)
        reverseComplement(stringSet[seqNo], Serial());
}



template < typename TSequence, typename TSpec, typename TParallelTag >
inline void reverseComplement(StringSet<TSequence, TSpec> const & stringSet, Tag<TParallelTag>)
{
    int seqCount = length(stringSet);
    SEQAN_OMP_PRAGMA(parallel for if(IsSameType<Tag<TParallelTag>, Parallel>::VALUE))
    for(int seqNo = 0; seqNo < seqCount; ++seqNo)
        reverseComplement(stringSet[seqNo], Serial());
}

template <typename TText>
inline void reverseComplement(TText & text)
{
    reverseComplement(text, Serial());
}

template <typename TText>
inline void reverseComplement(TText const & text)
{
    reverseComplement(text, Serial());
}





template <typename THost>
inline typename ReverseComplementString<THost>::Type
reverseComplementString(THost & host)
{
    typedef typename ReverseComplementString<THost>::Type TRevComp;
    return TRevComp(host);
}

template <typename THost>
inline typename ReverseComplementString<THost const>::Type
reverseComplementString(THost const & host)
{
    typedef typename ReverseComplementString<THost const>::Type TRevComp;
    return TRevComp(host);
}







template < typename TSequence >
inline void toLower(TSequence & sequence)
{
    convert(sequence, FunctorLowcase<typename Value<TSequence>::Type>());
}



template < typename TSequence >
inline void toLower(TSequence const & sequence)
{
    convert(sequence, FunctorLowcase<typename Value<TSequence>::Type>());
}

template < typename TSequence, typename TSpec >
inline void toLower(StringSet<TSequence, TSpec> & stringSet)
{
    unsigned seqCount = length(stringSet);
    for(unsigned seqNo = 0; seqNo < seqCount; ++seqNo)
        toLower(stringSet[seqNo]);
}



template < typename TSequence, typename TSpec >
inline void toLower(StringSet<TSequence, TSpec> const & stringSet)
{
    unsigned seqCount = length(stringSet);
    for(unsigned seqNo = 0; seqNo < seqCount; ++seqNo)
        toLower(stringSet[seqNo]);
}







template < typename TSequence >
inline void toUpper(TSequence & sequence)
{
    convert(sequence, FunctorUpcase<typename Value<TSequence>::Type>());
}



template < typename TSequence >
inline void toUpper(TSequence const & sequence)
{
    convert(sequence, FunctorUpcase<typename Value<TSequence>::Type>());
}

template < typename TSequence, typename TSpec >
inline void toUpper(StringSet<TSequence, TSpec> & stringSet)
{
    unsigned seqCount = length(stringSet);
    for(unsigned seqNo = 0; seqNo < seqCount; ++seqNo)
        toUpper(stringSet[seqNo]);
}



template < typename TSequence, typename TSpec >
inline void toUpper(StringSet<TSequence, TSpec> const & stringSet)
{

    unsigned seqCount = length(stringSet);
    for(unsigned seqNo = 0; seqNo < seqCount; ++seqNo)
        toUpper(stringSet[seqNo]);
}





template <typename THost>
inline ModifiedString<THost const, ModView<FunctorLowcase<typename Value<THost>::Type> > >
lowerString(THost const & host)
{
    return ModifiedString<THost const, ModView<FunctorLowcase<typename Value<THost>::Type> > >(host);
}





template <typename THost>
inline ModifiedString<THost const, ModView<FunctorUpcase<typename Value<THost>::Type> > >
upperString(THost const & host)
{
    return ModifiedString<THost const, ModView<FunctorUpcase<typename Value<THost>::Type> > >(host);
}

}

#endif
