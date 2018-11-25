


#ifndef INCLUDED_I18NPOOL_SOURCE_SEARCH_TEXTSEARCH_HXX
#define INCLUDED_I18NPOOL_SOURCE_SEARCH_TEXTSEARCH_HXX

#include <cppuhelper/implbase.hxx>
#include <com/sun/star/util/XTextSearch2.hpp>
#include <com/sun/star/i18n/XBreakIterator.hpp>
#include <com/sun/star/i18n/XExtendedTransliteration.hpp>
#include <com/sun/star/i18n/XCharacterClassification.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>

#include <map>
#include <memory>

#include <unicode/regex.h>
using namespace U_ICU_NAMESPACE;
typedef U_ICU_NAMESPACE::UnicodeString IcuUniString;

class WLevDistance;
typedef ::std::map< sal_Unicode, sal_Int32 > TextSearchJumpTable;

class TextSearch: public cppu::WeakImplHelper
<
    css::util::XTextSearch2,
    css::lang::XServiceInfo
>
{
    osl::Mutex m_aMutex;
    css::uno::Reference < css::uno::XComponentContext > m_xContext;

    css::util::SearchOptions2 aSrchPara;
    OUString sSrchStr;
    OUString sSrchStr2;

    mutable css::uno::Reference< css::i18n::XCharacterClassification > xCharClass;

    css::uno::Reference< css::i18n::XExtendedTransliteration > xTranslit;
    css::uno::Reference< css::i18n::XExtendedTransliteration > xTranslit2;

    
    typedef css::util::SearchResult
        (SAL_CALL TextSearch:: *FnSrch)( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );

    FnSrch fnForward;
    FnSrch fnBackward;

    
    std::unique_ptr<TextSearchJumpTable> pJumpTable;
    std::unique_ptr<TextSearchJumpTable> pJumpTable2;
    bool bIsForwardTab;
    bool bUsePrimarySrchStr;
    void MakeForwardTab();
    void MakeForwardTab2();
    void MakeBackwardTab();
    void MakeBackwardTab2();
    sal_Int32 GetDiff( const sal_Unicode ) const;
    
    css::util::SearchResult SAL_CALL
        NSrchFrwrd( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );
    
    css::util::SearchResult SAL_CALL
        NSrchBkwrd( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );

    
    std::unique_ptr<RegexMatcher> pRegexMatcher;
    
    css::util::SearchResult SAL_CALL
        RESrchFrwrd( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );
    
    css::util::SearchResult SAL_CALL
        RESrchBkwrd( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );
    void RESrchPrepare( const css::util::SearchOptions2&);

    
    int nLimit;
    std::unique_ptr<WLevDistance> pWLD;
    css::uno::Reference < css::i18n::XBreakIterator > xBreak;
    
    css::util::SearchResult SAL_CALL
        ApproxSrchFrwrd( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );
    
    css::util::SearchResult SAL_CALL
        ApproxSrchBkwrd( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );

    
    OUString    maWildcardReversePattern;
    OUString    maWildcardReversePattern2;
    sal_uInt32  mcWildcardEscapeChar;
    bool        mbWildcardAllowSubstring;
    
    css::util::SearchResult SAL_CALL
        WildcardSrchFrwrd( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );
    
    css::util::SearchResult SAL_CALL
        WildcardSrchBkwrd( const OUString& searchStr,
                                sal_Int32 startPos, sal_Int32 endPos );

    bool IsDelimiter( const OUString& rStr, sal_Int32 nPos ) const;

    bool checkCTLStart, checkCTLEnd;
    
    bool isCellStart(const OUString& searchStr, sal_Int32 nPos);

public:
    explicit TextSearch(
        const css::uno::Reference < css::uno::XComponentContext >& rxContext );

    virtual ~TextSearch() override;

    
    virtual void SAL_CALL
        setOptions( const css::util::SearchOptions& options ) override;
    virtual css::util::SearchResult SAL_CALL
        searchForward( const OUString& searchStr,
                        sal_Int32 startPos, sal_Int32 endPos ) override;
    virtual css::util::SearchResult SAL_CALL
        searchBackward( const OUString& searchStr,
                        sal_Int32 startPos, sal_Int32 endPos ) override;

    
    virtual void SAL_CALL
        setOptions2( const css::util::SearchOptions2& options ) override;

    
    virtual OUString SAL_CALL getImplementationName() override;
    virtual sal_Bool SAL_CALL supportsService(const OUString& ServiceName) override;
    virtual css::uno::Sequence< OUString > SAL_CALL getSupportedServiceNames() override;
};

#endif


