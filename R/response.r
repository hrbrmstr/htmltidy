#' @param encoding specify the encoding when tidying an \code{httr} \code{response}
#'   object. Default to "\code{UTF-8}".
#' @export
#' @rdname tidy_html
tidy_html.response <- function(content, options=list(TidyXhtmlOut=TRUE),
                               verbose=FALSE, encoding="UTF-8") {

  if (!grepl("html", content$headers[["content-type"]])) {
    stop("htmltidy only parses HTML content from httr::response objects",
         call.=FALSE)
  }

  html_txt <- httr::content(content, as="text", encoding=encoding)

  tidy_html(html_txt)

}
