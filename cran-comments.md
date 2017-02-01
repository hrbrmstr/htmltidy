## Test environments

* local OS X install, R 3.3.1 (clang)
* ubuntu 12.04 (on travis-ci), oldrel, release & devel
* win-builder (devel and release)
* local 32-bit Windows 10 R 3.3.1
* local ubuntu 14.04 R 3.3.1 & R-devel

## R CMD check results

0 errors | 0 warnings | 2 notes

---

This fixes a fairly nasty bug that was 
user-identfied fairly early after release 
but I didn't want to bug the CRAN team 
so quickly after the CRAN acceptance. This
also addes new functionality (widgets for
viewing & querying XML/HTML) and (optionally)
provides more informaiton on the tidying 
process. 
