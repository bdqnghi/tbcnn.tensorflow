

#include <unotools/unotoolsdllapi.h>

#ifndef INCLUDED_UNOTOOLS_TEXTSEARCH_HXX
#define INCLUDED_UNOTOOLS_TEXTSEARCH_HXX
#include <i18nlangtag/lang.h>
#include <rtl/ustring.hxx>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/util/XTextSearch.hpp>
#include <com/sun/star/util/SearchOptions.hpp>

class CharClass;

namespace com {
    namespace sun {
        namespace star {
            namespace util {
                struct SearchResult;
            }
        }
    }
}

namespace utl
{


class UNOTOOLS_DLLPUBLIC SearchParam
{
public:
    enum SearchType{ SRCH_NORMAL, SRCH_REGEXP, SRCH_LEVDIST };

private:
    OUString sSrchStr;            
    OUString sReplaceStr;         

    SearchType m_eSrchType;       

    bool m_bWordOnly   : 1;        
    bool m_bSrchInSel  : 1;        
    bool m_bCaseSense  : 1;

    
    bool bLEV_Relaxed : 1;
    int nLEV_OtherX;
    int nLEV_ShorterY;
    int nLEV_LongerZ;

    
    long nTransliterationFlags;

public:
    SearchParam( const OUString &rText,
                    SearchType eSrchType = SearchParam::SRCH_NORMAL,
                    bool bCaseSensitive = true,
                    bool bWordOnly = false,
                    bool bSearchInSelection = false );

    SearchParam( const SearchParam& );

    ~SearchParam();

    const OUString& GetSrchStr() const          { return sSrchStr; }
    const OUString& GetReplaceStr() const       { return sReplaceStr; }
    SearchType      GetSrchType() const         { return m_eSrchType; }

    bool            IsCaseSensitive() const     { return m_bCaseSense; }
    bool            IsSrchInSelection() const   { return m_bSrchInSel; }
    bool            IsSrchWordOnly() const      { return m_bWordOnly; }

    void SetSrchStr( const OUString& rStr )     { sSrchStr = rStr; }
    void SetReplaceStr( const OUString& rStr )  { sReplaceStr = rStr; }
    void SetSrchType( SearchType eType )        { m_eSrchType = eType; }

    void SetCaseSensitive( int bFlag )          { m_bCaseSense = bFlag; }
    void SetSrchInSelection( int bFlag )        { m_bSrchInSel = bFlag; }
    void SetSrchWordOnly( int bFlag )           { m_bWordOnly = bFlag; }

    bool            IsSrchRelaxed() const       { return bLEV_Relaxed; }
    int             GetLEVOther() const         { return nLEV_OtherX; }
    int             GetLEVShorter() const       { return nLEV_ShorterY; }
    int             GetLEVLonger() const        { return nLEV_LongerZ; }

    void SetSrchRelaxed( int bFlag )            { bLEV_Relaxed = bFlag; }
    void SetLEVOther( int nValue )              { nLEV_OtherX = nValue; }
    void SetLEVShorter( int nValue )            { nLEV_ShorterY = nValue; }
    void SetLEVLonger( int nValue )             { nLEV_LongerZ = nValue; }

    long GetTransliterationFlags() const        { return nTransliterationFlags; }
    void SetTransliterationFlags( long nValue ) { nTransliterationFlags = nValue; }
};









class UNOTOOLS_DLLPUBLIC TextSearch
{
    static ::com::sun::star::uno::Reference< ::com::sun::star::util::XTextSearch >
        getXTextSearch( const ::com::sun::star::util::SearchOptions& rPara );

    com::sun::star::uno::Reference < com::sun::star::util::XTextSearch >
            xTextSearch;

    void Init( const SearchParam & rParam,
               const ::com::sun::star::lang::Locale& rLocale );

public:
    
    
    TextSearch( const SearchParam & rPara, LanguageType nLanguage );
    TextSearch( const SearchParam & rPara, const CharClass& rCClass );

    TextSearch( const ::com::sun::star::util::SearchOptions& rPara );
    ~TextSearch();

    
    bool SearchForward( const OUString &rStr,
                        sal_Int32* pStart, sal_Int32* pEnd,
                        ::com::sun::star::util::SearchResult* pRes = 0 );
    bool SearchBackward( const OUString &rStr,
                        sal_Int32* pStart, sal_Int32* pEnd,
                        ::com::sun::star::util::SearchResult* pRes = 0 );

    void SetLocale( const ::com::sun::star::util::SearchOptions& rOpt,
                    const ::com::sun::star::lang::Locale& rLocale );

    
    void ReplaceBackReferences( OUString& rReplaceStr, const OUString &rStr, const ::com::sun::star::util::SearchResult& rResult );

};

}   

#endif


