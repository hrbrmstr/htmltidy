#include <Rcpp.h>
using namespace Rcpp;

#include <tidy.h>
#include <tidybuffio.h>

// [[Rcpp::export]]
Rcpp::CharacterVector do_the_tidy(std::string source,
                                    Rcpp::List options,
                                    bool show_errors) {

  TidyBuffer output = {0};
  TidyBuffer errbuf = {0};
  int rc = -1, max_rc = -1;
  Bool ok;

  TidyDoc tdoc = tidyCreate();

  if (options.containsElementNamed("TidyXhtmlOut")) {
    ok = tidyOptSetBool(tdoc, TidyXhtmlOut, options["TidyXhtmlOut"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyHtmlOut")) {
    ok = tidyOptSetBool(tdoc, TidyHtmlOut, options["TidyHtmlOut"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyOmitOptionalTags")) {
    ok = tidyOptSetBool(tdoc, TidyOmitOptionalTags, options["TidyOmitOptionalTags"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyBreakBeforeBR")) {
    ok = tidyOptSetBool(tdoc, TidyBreakBeforeBR, options["TidyBreakBeforeBR"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyUpperCaseTags")) {
    ok = tidyOptSetBool(tdoc, TidyUpperCaseTags, options["TidyUpperCaseTags"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyUpperCaseAttrs")) {
    ok = tidyOptSetBool(tdoc, TidyUpperCaseAttrs, options["TidyUpperCaseAttrs"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyDropEmptyElems")) {
    ok = tidyOptSetBool(tdoc, TidyDropEmptyElems, options["TidyDropEmptyElems"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyDropEmptyParas")) {
    ok = tidyOptSetBool(tdoc, TidyDropEmptyParas, options["TidyDropEmptyParas"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyFixComments")) {
    ok = tidyOptSetBool(tdoc, TidyFixComments, options["TidyFixComments"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyLogicalEmphasis")) {
    ok = tidyOptSetBool(tdoc, TidyLogicalEmphasis, options["TidyLogicalEmphasis"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyBodyOnly")) {
    ok = tidyOptSetBool(tdoc, TidyBodyOnly, options["TidyBodyOnly"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyHideComments")) {
    ok = tidyOptSetBool(tdoc, TidyHideComments, options["TidyHideComments"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyJoinClasses")) {
    ok = tidyOptSetBool(tdoc, TidyJoinClasses, options["TidyJoinClasses"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyJoinStyles")) {
    ok = tidyOptSetBool(tdoc, TidyJoinStyles, options["TidyJoinStyles"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyFixBackslash")) {
    ok = tidyOptSetBool(tdoc, TidyFixBackslash, options["TidyFixBackslash"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyMark")) {
    ok = tidyOptSetBool(tdoc, TidyMark, options["TidyMark"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyReplaceColor")) {
    ok = tidyOptSetBool(tdoc, TidyReplaceColor, options["TidyReplaceColor"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyIndentContent")) {
    ok = tidyOptSetBool(tdoc, TidyIndentContent, options["TidyIndentContent"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyCoerceEndTags")) {
    ok = tidyOptSetBool(tdoc, TidyCoerceEndTags, options["TidyCoerceEndTags"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyMakeBare")) {
    ok = tidyOptSetBool(tdoc, TidyMakeBare, options["TidyMakeBare"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyMakeClean")) {
    ok = tidyOptSetBool(tdoc, TidyMakeClean, options["TidyMakeClean"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyGDocClean")) {
    ok = tidyOptSetBool(tdoc, TidyGDocClean, options["TidyGDocClean"] ? aye : no);
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyWord2000")) {
    ok = tidyOptSetBool(tdoc, TidyWord2000, options["TidyWord2000"] ? aye : no);
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

  if (options.containsElementNamed("TidyInlineTags")) {
    ok = tidyOptSetValue(tdoc, TidyInlineTags, Rcpp::as<std::string>(options["TidyInlineTags"]).c_str());
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyBlockTags")) {
    ok = tidyOptSetValue(tdoc, TidyBlockTags, Rcpp::as<std::string>(options["TidyBlockTags"]).c_str());
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyPreTags")) {
    ok = tidyOptSetValue(tdoc, TidyPreTags, Rcpp::as<std::string>(options["TidyPreTags"]).c_str());
    if (ok == no) Rcpp::stop("Error setting TidyHTML options");
  }

  if (options.containsElementNamed("TidyEmptyTags")) {
    ok = tidyOptSetValue(tdoc, TidyEmptyTags, Rcpp::as<std::string>(options["TidyEmptyTags"]).c_str());
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

  ok = tidyOptSetBool(tdoc, TidyForceOutput, aye);
  if (ok == no) Rcpp::stop("Error setting TidyHTML options");

  rc = tidySetErrorBuffer(tdoc, &errbuf);
  max_rc = (rc > max_rc) ? rc : max_rc;

  if (rc<0) Rcpp::stop("Error setting TidyHTML error buffer");

  rc = tidyParseString(tdoc, source.c_str());
  max_rc = (rc > max_rc) ? rc : max_rc;

  if (rc<0) Rcpp::stop("Error parsing source document");

  rc = tidyCleanAndRepair(tdoc);
  max_rc = (rc > max_rc) ? rc : max_rc;

  if (rc<0) Rcpp::stop("Error tidying source document");

  rc = tidyRunDiagnostics(tdoc);
  max_rc = (rc > max_rc) ? rc : max_rc;

  if (rc<0) Rcpp::stop("Error generating tidy diagnostics");

  rc = tidySaveBuffer(tdoc, &output);
  max_rc = (rc > max_rc) ? rc : max_rc;

  if (rc<0) Rcpp::stop("Error converting parsed document to character vector");

  std::string ret;

  if (output.bp) {
    ret = std::string(reinterpret_cast<const char*>(output.bp));
  } else {
    ret = source;
    show_errors = true;
  }

  if (max_rc > 1) show_errors = true;

  if (show_errors) {
    if (errbuf.allocated > 0) {
      Rcpp::Rcout << std::string(reinterpret_cast<const char*>(errbuf.bp)) << std::endl;
    }
    if (max_rc > 1) {
      Rcpp::warning("\nSevere errors were generated during document evaluation.\n");
    }
  }

  if (output.allocated > 0) tidyBufFree(&output);
  if (errbuf.allocated > 0) tidyBufFree(&errbuf);

  tidyRelease(tdoc);

  return(Rcpp::wrap(ret));

}
