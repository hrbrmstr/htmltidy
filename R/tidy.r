#' Tidy HTML/XHTML Documents
#'
#' Pass in HTML content as either plain or raw text or parsed objects (either with the
#' \code{XML} or \code{xml2} packages) along with an options list that specifies how
#' the content will be tidied and get back tidied content of the same object type as passed
#' in to the function.
#'
#' The default option \code{TixyXhtmlOut} will convert the input content to XHTML.
#'
#' Currently supported options:
#'
#' \itemize{
#'   \item{Ones taking a logical value: }{\code{TidyAltText}, \code{TidyBodyOnly}, \code{TidyBreakBeforeBR},
#'     \code{TidyCoerceEndTags}, \code{TidyDropEmptyElems}, \code{TidyDropEmptyParas},
#'     \code{TidyFixBackslash}, \code{TidyFixComments}, \code{TidyGDocClean}, \code{TidyHideComments},
#'     \code{TidyHtmlOut}, \code{TidyIndentContent}, \code{TidyJoinClasses}, \code{TidyJoinStyles},
#'     \code{TidyLogicalEmphasis}, \code{TidyMakeBare}, \code{TidyMakeClean}, \code{TidyMark},
#'     \code{TidyOmitOptionalTags}, \code{TidyReplaceColor}, \code{TidyUpperCaseAttrs},
#'     \code{TidyUpperCaseTags}, \code{TidyWord2000}, \code{TidyXhtmlOut}}
#'   \item{Ones taking a character value: }{\code{TidyDoctype}, \code{TidyInlineTags}, \code{TidyBlockTags},
#'     \code{TidyEmptyTags}, \code{TidyPreTags}}
#'   \item{Ones taking an integer value: }{\code{TidyIndentSpaces}, \code{TidyTabSize}, \code{TidyWrapLen}}
#' }
#'
#' File \href{https://github.com/hrbrmstr/htmltidy/issues}{an issue} if there are other \code{libtidy}
#' options you'd like supported.
#'
#' It is likely that the most used options will be:
#'
#' \itemize{
#'   \item{\code{TidyXhtmlOut} (logical)},
#'   \item{\code{TidyHtmlOut} (logical)} and
#'   \item{\code{TidyDocType} which should be one of "\code{omit}",
#'     "\code{html5}", "\code{auto}", "\code{strict}" or "\code{loose}"}.
#' }
#'
#' You can clean up Microsoft Word (2000) and Google Docs HTML via logical settings for
#' \code{TidyWord2000} and \code{TidyGDocClean}, respectively.
#'
#' It may also be advantageous to remove all comments with \code{TidyHideComments}.
#'
#' @param content accepts a character vector, raw vector or parsed content from the \code{xml2}
#'        or \code{XML} packages.
#' @param options named list of options
#' @return Tidied HTML/XHTML content. The object type will be the same as that of the input type.
#' @references \url{http://api.html-tidy.org/tidy/quickref_5.1.25.html} &
#'   \url{https://github.com/htacg/tidy-html5/blob/master/include/tidyenum.h}
#'  for definitions of the options supported above and \url{https://www.w3.org/People/Raggett/tidy/}
#'  for an explanation of what "tidy" HTML is and some canonical examples of what it can do.
#' @export
#' @examples
#' opts <- list(
#'   TidyDocType="html5",
#'   TidyMakeClean=TRUE,
#'   TidyHideComments=TRUE,
#'   TidyIndentContent=TRUE,
#'   TidyWrapLen=200
#' )
#'
#' txt <- paste0(
#'   c("<html><head><style>p { color: red; }</style><body><!-- ===== body ====== -->",
#' "<p>Test</p></body><!--Default Zone --> <!--Default Zone End--></html>"),
#'   collapse="")
#'
#' cat(tidy_html(txt, option=opts))
tidy_html <- function(content, options=list(TidyXhtmlOut=TRUE)) {
  UseMethod("tidy_html")
}

#' @export
#' @rdname tidy_html
tidy_html.default <- function(content, options=list(TidyXhtmlOut=TRUE)) {
  content <- content[1]
  .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
        source=content, options=options)
}

#' @export
#' @rdname tidy_html
tidy_html.character <- function(content, options=list(TidyXhtmlOut=TRUE)) {
  content <- content[1]
  .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
        source=content, options=options)
}

#' @export
#' @rdname tidy_html
tidy_html.raw <- function(content, options=list(TidyXhtmlOut=TRUE)) {
  content <- content[1]
  content <- iconv(readBin(content, character()), to="UTF-8")
  out <- .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
               source=content, options=options)
  charToRaw(out)
}

#' @export
#' @rdname tidy_html
tidy_html.xml_document <- function(content, options=list(TidyXhtmlOut=TRUE)) {
  content <- toString(content)
  out <- .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
               source=content, options=options)
  xml2::read_html(out)
}

#' @export
#' @rdname tidy_html
tidy_html.HTMLInternalDocument <- function(content, options=list(TidyXhtmlOut=TRUE)) {
  content <- XML::saveXML(content)
  out <- .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy',
               source=content, options=options)
  XML::htmlParse(out)
}
