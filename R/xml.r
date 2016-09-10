#' Tidy XML Documents
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
#' @return tidied XML content
#' @references \url{https://github.com/htacg/tidy-html5/blob/master/include/tidyenum.h}
#'  (for definitions of the options supported above).
#' @export
tidy_xml <- function(content, options=list(TidyXmlOut=TRUE)) {
  UseMethod("tidy_xml")
}

#' @export
#' @rdname tidy_xml
tidy_xml.default <- function(content, options=list(TidyXmlOut=TRUE)) {
  .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
        source=content, options=options)
}

#' @export
#' @rdname tidy_xml
tidy_xml.character <- function(content, options=list(TidyXmlOut=TRUE)) {
  .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
        source=content, options=options)
}

#' @export
#' @rdname tidy_xml
tidy_xml.raw <- function(content, options=list(TidyXmlOut=TRUE)) {
  content <- iconv(readBin(content, character()), to="UTF-8")
  out <- .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
               source=content, options=options)
  charToRaw(out)
}

#' @export
#' @rdname tidy_xml
tidy_xml.xml_document <- function(content, options=list(TidyXmlOut=TRUE)) {
  content <- toString(content)
  out <- .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
               source=content, options=options)
  xml2::read_xml(out)
}

#' @export
#' @rdname tidy_xml
tidy_xml.XMLInternalDocument <- function(content, options=list(TidyXmlOut=TRUE)) {
  content <- saveXML(content)
  out <- .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
               source=content, options=options)
  XML::xmlParse(out)
}
