#include <Rcpp.h>
#include <tidy.h>
#include <tidybuffio.h>

// #ifdef __linux__
// #include <tidy/tidy.h>
// #include <tidy/buffio.h>
// #endif
//
// #ifdef __APPLE__
// #include <tidy.h>
// #include <tidybuffio.h>
// #endif

// libtidy docs:
// http://api.html-tidy.org/tidy/tidylib_api_5.2.0/tidyenum_8h.html#a3a1401652599150188a168dade7dc150

// NOTE: cannot do "using namespace Rcpp;" b/c of annoying warnings about the
//       ambiguity of 'yes'.

//[[Rcpp::export]]
std::string tidy_html_int(std::string source, Rcpp::List options) {

  TidyBuffer output = {0};
  TidyBuffer errbuf = {0};
  int rc = -1;
  Bool ok;

  TidyDoc tdoc = tidyCreate();

  if (options.containsElementNamed("TidyXhtmlOut")) {
    ok = tidyOptSetBool(tdoc, TidyXhtmlOut, options["TidyXhtmlOut"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyXmlOut")) {
    ok = tidyOptSetBool(tdoc, TidyXmlOut, options["TidyXmlOut"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyHtmlOut")) {
    ok = tidyOptSetBool(tdoc, TidyHtmlOut, options["TidyHtmlOut"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyXmlTags")) {
    ok = tidyOptSetBool(tdoc, TidyXmlTags, options["TidyXmlTags"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyOmitOptionalTags")) {
    ok = tidyOptSetBool(tdoc, TidyOmitOptionalTags, options["TidyOmitOptionalTags"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyXmlDecl")) {
    ok = tidyOptSetBool(tdoc, TidyXmlDecl, options["TidyXmlDecl"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyBreakBeforeBR")) {
    ok = tidyOptSetBool(tdoc, TidyBreakBeforeBR, options["TidyBreakBeforeBR"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyUpperCaseTags")) {
    ok = tidyOptSetBool(tdoc, TidyUpperCaseTags, options["TidyUpperCaseTags"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyUpperCaseAttrs")) {
    ok = tidyOptSetBool(tdoc, TidyUpperCaseAttrs, options["TidyUpperCaseAttrs"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyDropEmptyElems")) {
    ok = tidyOptSetBool(tdoc, TidyDropEmptyElems, options["TidyDropEmptyElems"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyDropEmptyParas")) {
    ok = tidyOptSetBool(tdoc, TidyDropEmptyParas, options["TidyDropEmptyParas"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyFixComments")) {
    ok = tidyOptSetBool(tdoc, TidyFixComments, options["TidyFixComments"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyLogicalEmphasis")) {
    ok = tidyOptSetBool(tdoc, TidyLogicalEmphasis, options["TidyLogicalEmphasis"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyBodyOnly")) {
    ok = tidyOptSetBool(tdoc, TidyBodyOnly, options["TidyBodyOnly"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyHideComments")) {
    ok = tidyOptSetBool(tdoc, TidyBodyOnly, options["TidyHideComments"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyJoinClasses")) {
    ok = tidyOptSetBool(tdoc, TidyJoinClasses, options["TidyJoinClasses"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyJoinStyles")) {
    ok = tidyOptSetBool(tdoc, TidyJoinStyles, options["TidyJoinStyles"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyFixBackslash")) {
    ok = tidyOptSetBool(tdoc, TidyFixBackslash, options["TidyFixBackslash"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyMark")) {
    ok = tidyOptSetBool(tdoc, TidyMark, options["TidyMark"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyReplaceColor")) {
    ok = tidyOptSetBool(tdoc, TidyReplaceColor, options["TidyReplaceColor"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyIndentContent")) {
    ok = tidyOptSetBool(tdoc, TidyIndentContent, options["TidyIndentContent"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyCoerceEndTags")) {
    ok = tidyOptSetBool(tdoc, TidyCoerceEndTags, options["TidyCoerceEndTags"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyCoerceEndTags")) {
    ok = tidyOptSetBool(tdoc, TidyCoerceEndTags, options["TidyCoerceEndTags"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyMakeBare")) {
    ok = tidyOptSetBool(tdoc, TidyMakeBare, options["TidyMakeBare"] ? yes : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyMakeClean")) {
    ok = tidyOptSetValue(tdoc, TidyMakeClean, Rcpp::as<std::string>(options["TidyMakeClean"]).c_str());
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyDoctype")) {
    ok = tidyOptSetValue(tdoc, TidyDoctype, Rcpp::as<std::string>(options["TidyDoctype"]).c_str());
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyAltText")) {
    ok = tidyOptSetValue(tdoc, TidyAltText, Rcpp::as<std::string>(options["TidyAltText"]).c_str());
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyWord2000")) {
    ok = tidyOptSetValue(tdoc, TidyWord2000, Rcpp::as<std::string>(options["TidyWord2000"]).c_str());
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyIndentSpaces")) {
    ok = tidyOptSetInt(tdoc, TidyIndentSpaces, Rcpp::as<int>(options["TidyIndentSpaces"]));
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyWrapLen")) {
    ok = tidyOptSetInt(tdoc, TidyWrapLen, Rcpp::as<int>(options["TidyWrapLen"]));
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyTabSize")) {
    ok = tidyOptSetInt(tdoc, TidyTabSize, Rcpp::as<int>(options["TidyTabSize"]));
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  rc = tidySetErrorBuffer(tdoc, &errbuf);

  if (rc<0) Rcpp::stop("Error setting TidyHTML error buffer");

  rc = tidyParseString(tdoc, source.c_str());

  if (rc<0) Rcpp::stop("Error parsing source document");

  rc = tidyCleanAndRepair(tdoc);

  if (rc<0) Rcpp::stop("Error tidying source document");

  rc = tidyRunDiagnostics(tdoc);

  if (rc<0) Rcpp::stop("Error generating tidy diagnostics");

  rc = tidySaveBuffer(tdoc, &output);

  if (rc<0) Rcpp::stop("Error converting parsed document to character vector");

  std::string ret = std::string(reinterpret_cast<const char*>(output.bp));

  tidyBufFree(&output);
  tidyBufFree(&errbuf);
  tidyRelease(tdoc);

  return(ret);

}
