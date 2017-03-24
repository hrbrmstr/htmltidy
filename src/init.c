#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME:
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP htmltidy_tidy_html_int(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"htmltidy_tidy_html_int", (DL_FUNC) &htmltidy_tidy_html_int, 3},
    {NULL, NULL, 0}
};

void R_init_htmltidy(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
