#' Tidy or "Pretty Print" HTML/XHTML Documents
#'
#' Pass in HTML content as either plain or raw text or parsed objects (either with the
#' \code{XML} or \code{xml2} packages) or as an \code{httr} \code{response} object
#' along with an options list that specifies how the content will be tidied and get back
#' tidied content of the same object type as passed in to the function.
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
#' @param verbose output document errors? (default: \code{FALSE})
#' @note If document parsing errors are severe enough, \code{tidy_html()} will not be able
#'   to clean the document and will display the errors (this output can be captured with
#'   \code{sink()} or \code{capture.output()}) along with a warning and return a "best effort"
#'   cleaned version of the document.
#' @return Tidied HTML/XHTML content. The object type will be the same as that of the input type
#'         except when it is a \code{connection}, then a character vector will be returned.
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
#'
#' \dontrun{
#' library(httr)
#' res <- GET("https://rud.is/test/untidy.html")
#'
#' # look at the original, un-tidy source
#' cat(content(res, as="text", encoding="UTF-8"))
#'
#' # see the tidied version
#' cat(tidy_html(content(res, as="text", encoding="UTF-8"),
#'               list(TidyDocType="html5", TidyWrapLen=200)))
#'
#' # but, you could also just do:
#' cat(tidy_html(url("https://rud.is/test/untidy.html")))
#' }
tidy_html <- function(content, options=list(TidyXhtmlOut=TRUE), verbose=FALSE) {
  UseMethod("tidy_html")
}

#' @export
#' @rdname tidy_html
tidy_html.default <- function(content, options=list(TidyXhtmlOut=TRUE),
                              verbose=FALSE) {
  content <- paste0(content, collapse="")
  .Call('_htmltidy_do_the_tidy', PACKAGE='htmltidy',
        source=content, options=options, show_errors=verbose)
}

#' @export
#' @rdname tidy_html
tidy_html.character <- function(content, options=list(TidyXhtmlOut=TRUE),
                              verbose=FALSE) {
  content <- paste0(content, collapse="")
  .Call('_htmltidy_do_the_tidy', PACKAGE='htmltidy',
        source=content, options=options, show_errors=verbose)
}

#' @export
#' @rdname tidy_html
tidy_html.raw <- function(content, options=list(TidyXhtmlOut=TRUE),
                              verbose=FALSE) {
  content <- content[1]
  content <- iconv(readBin(content, character()), to="UTF-8")
  out <- .Call('_htmltidy_do_the_tidy', PACKAGE='htmltidy',
               source=content, options=options, show_errors=verbose)
  charToRaw(out)
}

#' @export
#' @rdname tidy_html
tidy_html.xml_document <- function(content, options=list(TidyXhtmlOut=TRUE),
                              verbose=FALSE) {
  content <- toString(content)
  out <- .Call('_htmltidy_do_the_tidy', PACKAGE='htmltidy',
               source=content, options=options, show_errors=verbose)
  xml2::read_html(out)
}

#' @export
#' @rdname tidy_html
tidy_html.HTMLInternalDocument <- function(content, options=list(TidyXhtmlOut=TRUE),
                              verbose=FALSE) {
  content <- XML::saveXML(content)
  out <- .Call('_htmltidy_do_the_tidy', PACKAGE='htmltidy',
               source=content, options=options, show_errors=verbose)
  XML::htmlParse(out)
}

#' @export
#' @rdname tidy_html
tidy_html.connection <- function(content, options=list(TidyXhtmlOut=TRUE),
                              verbose=FALSE) {

  html <- paste0(readLines(content, warn=FALSE), collapse="")
  close(content)

  .Call('_htmltidy_do_the_tidy', PACKAGE='htmltidy',
        source=html, options=options, show_errors=verbose)

}

