#' @export
#' @rdname tidy_html
tidy_html.response <- function(content, options=list(TidyXhtmlOut=TRUE),
                               verbose=FALSE) {

  if (!grepl("html", content$headers[["content-type"]])) {
    stop("htmltidy only parses HTML content from httr::response objects",
         call.=FALSE)
  }

  html_txt <- suppressMessages(httr::content(content, as="text"))

  tidy_html(html_txt)

}
