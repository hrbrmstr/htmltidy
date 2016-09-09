context("basic functionality")
test_that("tidying works", {

  expect_gte(nchar(tidy_html("<b><p><a href='http://google.com'>google &gt</a></p></b>")),
             249)

})
