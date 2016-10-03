library(htmltidy)

# from ?xml2::read_xml
cd <- xml2::read_xml("http://www.xmlfiles.com/examples/cd_catalog.xml")

xml_tree_view(cd)

htmltools::browsable(
  htmltools::tagList(
    xml_tree_view(cd, width = "100%", height = "300px"),
    xml_view(cd)
  )
)
