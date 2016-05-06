context("basic functionality")
test_that("we can do something", {

  expect_that(nchar(tidy("<b><p><a href='http://google.com'>google &gt</a></p></b>")),
              equals(256))

})
