#' Tidy HTML/XML/XHTML Documents
#'
#' Currently supported options: \code{TidyAltText}, \code{TidyBodyOnly},
#' \code{TidyBreakBeforeBR}, \code{TidyCoerceEndTags}, \code{TidyCoerceEndTags},
#' \code{TidyDoctype}, \code{TidyDropEmptyElems}, \code{TidyDropEmptyParas},
#' \code{TidyFixBackslash}, \code{TidyFixComments}, \code{TidyHideComments},
#' \code{TidyHtmlOut}, \code{TidyIndentContent}, \code{TidyIndentSpaces},
#' \code{TidyJoinClasses}, \code{TidyJoinStyles}, \code{TidyLogicalEmphasis},
#' \code{TidyMakeBare}, \code{TidyMakeClean}, \code{TidyMark},
#' \code{TidyOmitOptionalTags}, \code{TidyReplaceColor}, \code{TidyTabSize},
#' \code{TidyUpperCaseAttrs}, \code{TidyUpperCaseTags}, \code{TidyWord2000},
#' \code{TidyWrapLen}, \code{TidyXhtmlOut}, \code{TidyXmlDecl}, \code{TidyXmlOut},
#' \code{TidyXmlTags}.
#'
#' @param content atomic character or raw vector of content to tidy
#' @param options named list of options
#' @return Atomic character vector of tidy HTML/XML/XHTML content
#' @export
tidy_html <- function(content, options=list(TidyXhtmlOut=TRUE)) {
  .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy', source=content, options=options)
}
