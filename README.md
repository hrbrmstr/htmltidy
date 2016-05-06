
<!-- README.md is generated from README.Rmd. Please edit that file -->
`htmltidy` — Clean up gnarly HTML/XML

NOTE: Requires [`libtidy`](http://www.html-tidy.org/) and presently is super-basic (no way to set options and pretty much only does HTML)

The following functions are implemented:

-   `tidy` : Clean up gnarly HTML/XML

### Installation

``` r
devtools::install_github("hrbrmstr/htmltidy")
```

### Usage

``` r
library(htmltidy)

# current verison
packageVersion("htmltidy")
#> [1] '0.0.0.9000'

cat(tidy("<b><p><a href='http://google.com'>google &gt</a></p></b>"))
#> <!DOCTYPE html>
#> <html xmlns="http://www.w3.org/1999/xhtml">
#> <head>
#> <meta name="generator" content=
#> "HTML Tidy for HTML5 for Mac OS X version 5.2.0" />
#> <title></title>
#> </head>
#> <body>
#> <p><b><a href='http://google.com'>google &gt;</a></b></p>
#> </body>
#> </html>
```

### Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
