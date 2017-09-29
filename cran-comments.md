## Test environments

* local OS X install, R 3.4.1 (clang)
* ubuntu 14.04 (on travis-ci), oldrel, release & devel
* win-builder (devel and release)
* AppVeyor

## R CMD check results

0 errors | 0 warnings | 0 notes

---

Fix per note from CRAN regarding 
checks failing: htmltidy C[++] 
code has been updated and examples
that required internet access to
successfully complete have been
re-worked to use the system.file()
package example files.

Also switched to lettting Rcpp create
the registration code vs the self-
generated one that was in the
(now removed) init.c.
