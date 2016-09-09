
[![Travis-CI Build Status](https://travis-ci.org/hrbrmstr/htmltidy.svg?branch=master)](https://travis-ci.org/hrbrmstr/htmltidy)

<!-- README.md is generated from README.Rmd. Please edit that file -->
`htmltidy` — Clean up gnarly HTML/XML

Inspired by [this SO question](http://stackoverflow.com/questions/37061873/identify-a-weblink-in-bold-in-r) and because there's a great deal of cruddy HTML out there that needs fixing to use properly when scraping data.

It relies on a locally included version of [`libtidy`](http://www.html-tidy.org/) and presently is super-basic (no way to set options and pretty much only does HTML)

This works enough for me to use in a pinch. It should be straightforward (but tedious) to:

-   enable passing options in a `list`
-   Getting it to work on Windows.

The following functions are implemented:

-   `tidy_html` : Clean up gnarly HTML/XML

### TODO

Fix:

``` text
* checking compiled code ... WARNING
File ‘htmltidy/libs/htmltidy.so’:
  Found ‘___stderrp’, possibly from ‘stderr’ (C)
    Objects: ‘alloc.o’, ‘streamio.o’, ‘tidylib.o’
  Found ‘___stdoutp’, possibly from ‘stdout’ (C)
    Objects: ‘sprtf.o’, ‘tidylib.o’
  Found ‘_exit’, possibly from ‘exit’ (C)
    Objects: ‘alloc.o’, ‘sprtf.o’
```

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

cat(tidy_html("<b><p><a href='http://google.com'>google &gt</a></p></b>"))
#> <!DOCTYPE html>
#> <html xmlns="http://www.w3.org/1999/xhtml">
#> <head>
#> <meta name="generator" content=
#> "HTML Tidy for HTML5 for R version 5.0.0" />
#> <title></title>
#> </head>
#> <body>
#> <p><b><a href='http://google.com'>google &gt;</a></b></p>
#> </body>
#> </html>
```

### Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
