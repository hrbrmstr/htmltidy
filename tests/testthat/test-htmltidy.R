context("basic functionality")
test_that("tidying works", {

  th <- tidy_html("<b><p><a href='http://google.com'>google &gt</a></p></b>")

  expect_gte(nchar(th), 249)
  expect_equivalent(grepl("HTML Tidy for HTML5 for R", th), TRUE)

})
