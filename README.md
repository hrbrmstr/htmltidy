
[![Travis-CI Build Status](https://travis-ci.org/hrbrmstr/htmltidy.svg?branch=master)](https://travis-ci.org/hrbrmstr/htmltidy) [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/hrbrmstr/htmltidy?branch=master&svg=true)](https://ci.appveyor.com/project/hrbrmstr/htmltidy) [![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/htmltidy)](https://cran.r-project.org/package=htmltidy) ![downloads](http://cranlogs.r-pkg.org/badges/grand-total/htmltidy)

<!-- README.md is generated from README.Rmd. Please edit that file -->
`htmltidy` — Tidy Up and Test XPath Queries on HTML and XML Content

Partly inspired by [this SO question](http://stackoverflow.com/questions/37061873/identify-a-weblink-in-bold-in-r) and because there's a great deal of cruddy HTML out there that needs fixing to use properly when scraping data.

It relies on a locally included version of [`libtidy`](http://www.html-tidy.org/) and works on macOS, Linux & Windows.

It also incorporates an `htmlwidget` to view and test XPath queries on HTML/XML content.

The following functions are implemented:

-   `tidy_html`: Tidy or "Pretty Print" HTML/XHTML Documents
-   `html_view`: HTML/XML pretty printer and viewer
-   `xml_view`: HTML/XML pretty printer and viewer
-   `html_tree_view`: HTML/XML tree viewer
-   `xml_tree_view`: HTML/XML tree viewer

### Installation

``` r
devtools::install_github("hrbrmstr/htmltidy")
```

### Usage

``` r
library(htmltidy)

# current verison
packageVersion("htmltidy")
## [1] '0.3.0'

library(XML)
library(xml2)
library(httr)
library(purrr)
```

This is really "un-tidy" content:

``` r
res <- GET("http://rud.is/test/untidy.html")
cat(content(res, as="text"))
## <head>
## <style>
## body { font-family: sans-serif; }
## </style>
## </head>
## <body>
## <b>This is <b>some <i>really </i> poorly formatted HTML</b>
## 
## as is this <span id="sp">portion<div>
```

Let's see what `tidy_html()` does to it.

It can handle the `response` object directly:

``` r
cat(tidy_html(res, list(TidyDocType="html5", TidyWrapLen=200)))
## <!DOCTYPE html>
## <html>
## <head>
## <meta name="generator" content="HTML Tidy for HTML5 for R version 5.0.0">
## <style>
## body { font-family: sans-serif; }
## </style>
## <title></title>
## </head>
## <body>
## <b>This is some <i>really</i> poorly formatted HTML as is this <span id="sp">portion</span></b>
## <div><span id="sp"></span></div>
## </body>
## </html>
```

But, you'll probably mostly use it on HTML you've identified as gnarly and already have that HTML text content handy:

``` r
cat(tidy_html(content(res, as="text"), list(TidyDocType="html5", TidyWrapLen=200)))
## <!DOCTYPE html>
## <html>
## <head>
## <meta name="generator" content="HTML Tidy for HTML5 for R version 5.0.0">
## <style>
## body { font-family: sans-serif; }
## </style>
## <title></title>
## </head>
## <body>
## <b>This is some <i>really</i> poorly formatted HTML as is this <span id="sp">portion</span></b>
## <div><span id="sp"></span></div>
## </body>
## </html>
```

NOTE: you could also just have done:

``` r
cat(tidy_html(url("http://rud.is/test/untidy.html"), 
              list(TidyDocType="html5", TidyWrapLen=200)))
## <!DOCTYPE html>
## <html>
## <head>
## <meta name="generator" content="HTML Tidy for HTML5 for R version 5.0.0">
## <style>
## body { font-family: sans-serif; }
## </style>
## <title></title>
## </head>
## <body>
## <b>This is some <i>really</i> poorly formatted HTMLas is this <span id="sp">portion</span></b>
## <div><span id="sp"></span></div>
## </body>
## </html>
```

You'll see that this differs substantially from the mangling `libxml2` does (via `read_html()`):

``` r
pg <- read_html("http://rud.is/test/untidy.html")
cat(toString(pg))
## <?xml version="1.0" standalone="yes"?>
## <!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" "http://www.w3.org/TR/REC-html40/loose.dtd">
## <html><head><style><![CDATA[
## body { font-family: sans-serif; }
## ]]></style></head><body>
## <b>This is <b>some <i>really </i> poorly formatted HTML</b>
## 
## as is this <span id="sp">portion<div/></span></b></body></html>
```

It can also deal with "raw" and parsed objects:

``` r
tidy_html(content(res, as="raw"))
##   [1] 3c 21 44 4f 43 54 59 50 45 20 68 74 6d 6c 3e 0a 3c 68 74 6d 6c 20 78 6d 6c 6e 73 3d 22 68 74 74 70 3a 2f 2f 77 77
##  [39] 77 2e 77 33 2e 6f 72 67 2f 31 39 39 39 2f 78 68 74 6d 6c 22 3e 0a 3c 68 65 61 64 3e 0a 3c 6d 65 74 61 20 6e 61 6d
##  [77] 65 3d 22 67 65 6e 65 72 61 74 6f 72 22 20 63 6f 6e 74 65 6e 74 3d 0a 22 48 54 4d 4c 20 54 69 64 79 20 66 6f 72 20
## [115] 48 54 4d 4c 35 20 66 6f 72 20 52 20 76 65 72 73 69 6f 6e 20 35 2e 30 2e 30 22 20 2f 3e 0a 3c 74 69 74 6c 65 3e 3c
## [153] 2f 74 69 74 6c 65 3e 0a 3c 2f 68 65 61 64 3e 0a 3c 62 6f 64 79 3e 0a 3c 2f 62 6f 64 79 3e 0a 3c 2f 68 74 6d 6c 3e
## [191] 0a

tidy_html(content(res, as="text", encoding="UTF-8"))
## [1] "<!DOCTYPE html>\n<html xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n<meta name=\"generator\" content=\n\"HTML Tidy for HTML5 for R version 5.0.0\" />\n<style>\n<![CDATA[\nbody { font-family: sans-serif; }\n]]>\n</style>\n<title></title>\n</head>\n<body>\n<b>This is some <i>really</i> poorly formatted HTML as is this\n<span id=\"sp\">portion</span></b>\n<div><span id=\"sp\"></span></div>\n</body>\n</html>\n"

tidy_html(content(res, as="parsed", encoding="UTF-8"))
## {xml_document}
## <html xmlns="http://www.w3.org/1999/xhtml">
## [1] <head>\n  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />\n  <meta name="generator" content ...
## [2] <body>\n<b>This is some <i>really</i> poorly formatted HTML as is this\n<span id="sp">portion</span></b>\n</body>

tidy_html(htmlParse("http://rud.is/test/untidy.html"))
## <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
## <html xmlns="http://www.w3.org/1999/xhtml">
## <head>
## <meta name="generator" content="HTML Tidy for HTML5 for R version 5.0.0">
## <style>
## <![CDATA[
## body { font-family: sans-serif; }
## ]]>
## </style>
## <title></title>
## </head>
## <body>
## <b>This is some <i>really</i> poorly formatted HTML as is this
## <span id="sp">portion</span></b>
## <div><span id="sp"></span></div>
## </body>
## </html>
## 
```

And, show the markup errors:

``` r
invisible(tidy_html(url("http://rud.is/test/untidy.html"), verbose=TRUE))
## line 1 column 1 - Warning: missing <!DOCTYPE> declaration
## line 1 column 68 - Warning: nested emphasis <b>
## line 1 column 138 - Warning: missing </span> before <div>
## line 1 column 68 - Warning: missing </b> before <div>
## line 1 column 164 - Warning: inserting implicit <span>
## line 1 column 164 - Warning: missing </span>
## line 1 column 159 - Warning: missing </div>
## line 1 column 1 - Warning: inserting missing 'title' element
## line 1 column 164 - Warning: <span> anchor "sp" already defined
## Info: Document content looks like XHTML5
## Tidy found 9 warnings and 0 errors!
```

### Testing Options

``` r

opts <- list(TidyDocType="html5",
             TidyMakeClean=TRUE,
             TidyHideComments=TRUE,
             TidyIndentContent=FALSE,
             TidyWrapLen=200)

txt <- "<html>
<head>
      <style>
        p { color: red; }
      </style>
    <body>
          <!-- ===== body ====== -->
         <p>Test</p>

    </body>
        <!--Default Zone
        -->
        <!--Default Zone End-->
</html>"

cat(tidy_html(txt, option=opts))
## <!DOCTYPE html>
## <html>
## <head>
## <meta name="generator" content="HTML Tidy for HTML5 for R version 5.0.0">
## <style>
##         p { color: red; }
## </style>
## <title></title>
## </head>
## <body>
## <p>Test</p>
## </body>
## </html>
```

But, you're probably better off running it on plain HTML source.

Since it's C/C++-backed, it's pretty fast:

``` r
book <- readLines("http://singlepageappbook.com/single-page.html")
sum(map_int(book, nchar))
## [1] 207501
system.time(tidy_book <- tidy_html(book))
##    user  system elapsed 
##   0.021   0.001   0.022
```

(It's usually between 20 & 25 milliseconds to process those 202 kilobytes of HTML.) Not too shabby.

### Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
