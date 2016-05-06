context("basic functionality")
test_that("we can do something", {

  expect_gte(nchar(tidy("<b><p><a href='http://google.com'>google &gt</a></p></b>")),
             256)

})
