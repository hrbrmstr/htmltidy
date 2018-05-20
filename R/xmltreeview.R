#' HTML/XML tree viewer
#'
#' This uses the \code{xml-viewer} JavaScript module to provide a simple collapsible
#' tree viewer for HTML/XML documents, nodes, node sets and plain character
#' HTML/XML in an \code{htmlwidget} pane.
#'
#' @md
#' @param doc \code{xml2} document/node/nodeset, an \code{HTMLInternalDocument}/
#'        \code{XMLInternalDocument} or atomic character vector of HTML/XML content
#' @param mode viewer mode. `traditional` uses tag notation; `modern` favors readability
#'        oveer angle brackets.
#' @param scroll should the \code{<div>} holding the HTML/XML content scroll
#'        (\code{TRUE}) or take up the full viewer/browser window (\code{FALSE}).
#'        Default is \code{FALSE} (take up the full viewer/browser window). If
#'        this is set to \code{TRUE}, \code{height} should be set to a value
#'        other than \code{NULL}.
#' @param width widget \code{div} width
#' @param height widget \code{div} height
#' @note Large HTML or XML content may take some time to render properly. It is suggested
#'       that this function be used on as minimal of a subset of HTML/XML as possible
#'       or used in a browser context vs an IDE viewer context.
#' @export
#' @references \href{http://www.lexiconista.com/xonomy/}{xonomy xml viewer}
#' @examples
#' if(interactive()) {
#' txt <- paste0("<note><to>Tove</to><from>Jani</from><heading>Reminder</heading>",
#'               "<body>Don't forget me this weekend!</body></note>")
#' # xml_tree_view(txt)
#' }
xml_tree_view <- function(doc=NULL, mode=c("traditional", "modern"), scroll=FALSE, width="100%", height=NULL) {

  if (inherits(doc, "character")) {
    doc <- paste0(doc, collapse="")
  } else if (inherits(doc, "xml_nodeset")) {
    doc <- paste0(as.character(doc), collapse="")
  } else if (inherits(doc, "xml_document") | inherits(doc, "xml_node")) {
    doc <- as.character(doc)
  } else if (inherits(doc, "HTMLInternalDocument") |
             inherits(doc, "XMLInternalDocument")) {
    doc <- XML::saveXML(doc)
  }

  mode <- match.arg(trimws(tolower(mode)), c("traditional", "modern"))
  mode <- unname(c("traditional"="nerd", "modern"="laic")[mode])

  params <- list(
    xmlDoc = doc,
    mode = mode,
    scroll = scroll
  )

  # create widget
  htmlwidgets::createWidget(
    name = 'xmltreeview',
    x = params,
    width = width,
    height = height,
    package = 'htmltidy'
  )

}

#' @rdname xml_tree_view
#' @export
html_tree_view <- xml_tree_view
