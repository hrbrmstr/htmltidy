#' @title HTML, XHTML & XML Options for tidy_html
#' @description This dataset contains the options (and their default settings) for
#' tidy_html. They are passed in a named-list to tidy_html
#'
#' \itemize{
#'   \item \code{Option}: Option name
#'   \item \code{Type}: Option value type
#'   \item \code{Default}: Is it the default for tidy_html?
#' }
#'
#' @docType data
#' @keywords datasets
#' @name tidy_options
#'
#' @references The \href{http://api.html-tidy.org/tidy/quickref_5.1.25.html}{
#'   HTML Tidy Options Quick Reference}
#'
#' @export
#' @usage tidy_options
#' @note Last updated 2016-09-09.
#' @format A data frame with 55 rows and 3 variables
NULL

tidy_options <- structure(list(Option = c("add-xml-decl", "add-xml-space", "alt-text",
"anchor-as-name", "assume-xml-procins", "bare", "clean", "coerce-endtags",
"css-prefix", "decorate-inferred-ul", "doctype", "drop-empty-elements",
"drop-empty-paras", "drop-font-tags", "drop-proprietary-attributes",
"enclose-block-text", "enclose-text", "escape-cdata", "fix-backslash",
"fix-bad-comments", "fix-uri", "gdoc", "hide-comments", "hide-endtags",
"indent-cdata", "input-xml", "join-classes", "join-styles", "literal-attributes",
"logical-emphasis", "lower-literals", "merge-divs", "merge-emphasis",
"merge-spans", "ncr", "new-blocklevel-tags", "new-empty-tags",
"new-inline-tags", "new-pre-tags", "numeric-entities", "omit-optional-tags",
"output-html", "output-xhtml", "output-xml", "preserve-entities",
"quote-ampersand", "quote-marks", "quote-nbsp", "repeated-attributes",
"replace-color", "show-body-only", "skip-nested", "uppercase-attributes",
"uppercase-tags", "word-2000"), Type = c("Boolean", "Boolean",
"String", "Boolean", "Boolean", "Boolean", "Boolean", "Boolean",
"String", "Boolean", "DocType", "Boolean", "Boolean", "Boolean",
"Boolean", "Boolean", "Boolean", "Boolean", "Boolean", "Boolean",
"Boolean", "Boolean", "Boolean", "Boolean", "Boolean", "Boolean",
"Boolean", "Boolean", "Boolean", "Boolean", "Boolean", "AutoBool",
"Boolean", "AutoBool", "Boolean", "Tag names", "Tag names", "Tag names",
"Tag names", "Boolean", "Boolean", "Boolean", "Boolean", "Boolean",
"Boolean", "Boolean", "Boolean", "Boolean", "enum", "Boolean",
"AutoBool", "Boolean", "Boolean", "Boolean", "Boolean"), Default = c("no",
"no", "-", "yes", "no", "no", "no", "yes", "-", "no", "auto",
"yes", "yes", "no", "no", "no", "no", "no", "yes", "yes", "yes",
"no", "no", "no", "no", "no", "no", "yes", "no", "no", "yes",
"auto", "yes", "auto", "yes", "-", "-", "-", "-", "no", "no",
"no", "no", "no", "no", "yes", "no", "yes", "keep-last", "no",
"no", "yes", "no", "no", "no")), .Names = c("Option", "Type",
"Default"), row.names = 3:57, class = "data.frame")
