library(xml2)

doc <- read_xml("http://www.npr.org/rss/rss.php?id=1001")

str(doc)

xml_view(doc, add_filter=TRUE)
xml2::xml_find_all(doc, './/dc:creator', ns=xml2::xml_ns(doc))

xml_text(xml2::xml_find_all(doc, './/link[contains(., "soccer")]', ns=xml2::xml_ns(doc)))

