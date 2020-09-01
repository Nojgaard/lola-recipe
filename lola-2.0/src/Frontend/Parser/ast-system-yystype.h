#ifndef YYSTYPE_HEADER
#define YYSTYPE_HEADER
union KC_YYSTYPE {
    kc::nocasestring yt_nocasestring;
    kc::casestring yt_casestring;
    kc::real yt_real;
    kc::integer yt_integer;
    kc::voidptr yt_voidptr;
    kc::tFormula yt_tFormula;
    kc::tStatePredicate yt_tStatePredicate;
    kc::tConjunction_list yt_tConjunction_list;
    kc::tDisjunction_list yt_tDisjunction_list;
    kc::tAtomicProposition yt_tAtomicProposition;
    kc::tTerm yt_tTerm;
    kc::tProduct_list yt_tProduct_list;
    kc::tBuechiAutomata yt_tBuechiAutomata;
    kc::tBuechiRules yt_tBuechiRules;
    kc::tTransitionRules yt_tTransitionRules;
    kc::tAcceptingSet yt_tAcceptingSet;
};
#define YYSTYPE KC_YYSTYPE
#endif // YYSTYPE_HEADER
