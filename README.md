
[![Travis-CI Build Status](https://travis-ci.org/hrbrmstr/htmltidy.svg?branch=master)](https://travis-ci.org/hrbrmstr/htmltidy)

<!-- README.md is generated from README.Rmd. Please edit that file -->
`htmltidy` — Clean up gnarly HTML/XHTML

Inspired by [this SO question](http://stackoverflow.com/questions/37061873/identify-a-weblink-in-bold-in-r) and because there's a great deal of cruddy HTML out there that needs fixing to use properly when scraping data.

It relies on a locally included version of [`libtidy`](http://www.html-tidy.org/) and works on macOS, Linux & Windows.

The following functions are implemented:

-   `tidy_html` : Clean up gnarly HTML/XHTML

### Installation

``` r
devtools::install_github("hrbrmstr/htmltidy")
```

### Usage

``` r
library(htmltidy)

# current verison
packageVersion("htmltidy")
#> [1] '0.2.0.9000'

library(XML)
library(xml2)
library(httr)

res <- GET("http://rud.is")

head(tidy_html(res$content), 256)
#>   [1] 3c 21 44 4f 43 54 59 50 45 20 68 74 6d 6c 20 50 55 42 4c 49 43 20 22 2d 2f 2f 57 33 43 2f 2f 44 54 44 20 58 48 54
#>  [39] 4d 4c 20 31 2e 30 20 54 72 61 6e 73 69 74 69 6f 6e 61 6c 2f 2f 45 4e 22 0a 20 20 20 20 22 68 74 74 70 3a 2f 2f 77
#>  [77] 77 77 2e 77 33 2e 6f 72 67 2f 54 52 2f 78 68 74 6d 6c 31 2f 44 54 44 2f 78 68 74 6d 6c 31 2d 74 72 61 6e 73 69 74
#> [115] 69 6f 6e 61 6c 2e 64 74 64 22 3e 0a 3c 68 74 6d 6c 20 78 6d 6c 6e 73 3d 22 68 74 74 70 3a 2f 2f 77 77 77 2e 77 33
#> [153] 2e 6f 72 67 2f 31 39 39 39 2f 78 68 74 6d 6c 22 3e 0a 3c 68 65 61 64 3e 0a 3c 6d 65 74 61 20 6e 61 6d 65 3d 22 67
#> [191] 65 6e 65 72 61 74 6f 72 22 20 63 6f 6e 74 65 6e 74 3d 0a 22 48 54 4d 4c 20 54 69 64 79 20 66 6f 72 20 48 54 4d 4c
#> [229] 35 20 66 6f 72 20 52 20 76 65 72 73 69 6f 6e 20 35 2e 30 2e 30 22 20 2f 3e 0a 3c 6d

head(tidy_html(content(res, as="raw")), 256)
#>   [1] 3c 21 44 4f 43 54 59 50 45 20 68 74 6d 6c 20 50 55 42 4c 49 43 20 22 2d 2f 2f 57 33 43 2f 2f 44 54 44 20 58 48 54
#>  [39] 4d 4c 20 31 2e 30 20 54 72 61 6e 73 69 74 69 6f 6e 61 6c 2f 2f 45 4e 22 0a 20 20 20 20 22 68 74 74 70 3a 2f 2f 77
#>  [77] 77 77 2e 77 33 2e 6f 72 67 2f 54 52 2f 78 68 74 6d 6c 31 2f 44 54 44 2f 78 68 74 6d 6c 31 2d 74 72 61 6e 73 69 74
#> [115] 69 6f 6e 61 6c 2e 64 74 64 22 3e 0a 3c 68 74 6d 6c 20 78 6d 6c 6e 73 3d 22 68 74 74 70 3a 2f 2f 77 77 77 2e 77 33
#> [153] 2e 6f 72 67 2f 31 39 39 39 2f 78 68 74 6d 6c 22 3e 0a 3c 68 65 61 64 3e 0a 3c 6d 65 74 61 20 6e 61 6d 65 3d 22 67
#> [191] 65 6e 65 72 61 74 6f 72 22 20 63 6f 6e 74 65 6e 74 3d 0a 22 48 54 4d 4c 20 54 69 64 79 20 66 6f 72 20 48 54 4d 4c
#> [229] 35 20 66 6f 72 20 52 20 76 65 72 73 69 6f 6e 20 35 2e 30 2e 30 22 20 2f 3e 0a 3c 6d

(class(tidy_html(content(res, as="text", encoding="UTF-8")))) # output is too long to show
#> [1] "character"

tidy_html(content(res, as="parsed", encoding="UTF-8")) # same as tidy_html(read_html("http://rud.is"))
#> {xml_document}
#> <html xmlns="http://www.w3.org/1999/xhtml">
#> [1] <head>\n  <meta name="generator" content="HTML Tidy for HTML5 for R version 5.0.0" />\n  <meta http-equiv="Conten ...
#> [2] <body>\n<div id="main"><b>Welcome to rud.is.</b><br /><br />\n&gt; <i>You are in a maze of twisty little passages ...

(class(tidy_html(htmlParse("http://rud.is")))) # output is too long to show
#> [1] "HTMLInternalDocument" "HTMLInternalDocument" "XMLInternalDocument"  "XMLAbstractDocument"
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
#> <!DOCTYPE html>
#> <html>
#> <head>
#> <meta name="generator" content="HTML Tidy for HTML5 for R version 5.0.0">
#> <style>
#>         p { color: red; }
#> </style>
#> <title></title>
#> </head>
#> <body>
#> <p>Test</p>
#> </body>
#> </html>
```

### Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
