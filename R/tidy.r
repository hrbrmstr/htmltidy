#' Tidy HTML/XML/XHTML Documents
#'
#' @param content atomic character or raw vector of content to tidy
#' @param options named list of options
#' @return atomic character vector of tidy content
#' @export
tidy_html <- function(content, options=list(TidyXhtmlOut=TRUE)) {
  .Call('htmltidy_tidy_html_int', PACKAGE='htmltidy', source=content, options=options)
}

#
#   TidyXmlDecl,         /**< Add <?xml?> for XML docs */
#   TidyUpperCaseTags,   /**< Output tags in upper not lower case */
#   TidyUpperCaseAttrs,  /**< Output attributes in upper not lower case */
#   TidyMakeBare,        /**< Make bare HTML: remove Microsoft cruft */
#   TidyMakeClean,       /**< Replace presentational clutter by style rules */
#   TidyGDocClean,       /**< Clean up HTML exported from Google Docs */
#   TidyLogicalEmphasis, /**< Replace i by em and b by strong */
#   TidyDropPropAttrs,   /**< Discard proprietary attributes */
#   TidyDropFontTags,    /**< Discard presentation tags */
#   TidyDropEmptyElems,  /**< Discard empty elements */
#   TidyDropEmptyParas,  /**< Discard empty p elements */
#   TidyFixComments,     /**< Fix comments with adjacent hyphens */
#   TidyBreakBeforeBR,   /**< Output newline before <br> or not? */
  # TidyNumEntities,     /**< Use numeric entities */
  # TidyQuoteMarks,      /**< Output " marks as &quot; */
  # TidyQuoteNbsp,       /**< Output non-breaking space as entity */
  # TidyQuoteAmpersand,  /**< Output naked ampersand as &amp; */
  # TidyWrapAttVals,     /**< Wrap within attribute values */
  # TidyWrapScriptlets,  /**< Wrap within JavaScript string literals */
  # TidyWrapSection,     /**< Wrap within <![ ... ]> section tags */
  # TidyWrapAsp,         /**< Wrap within ASP pseudo elements */
  # TidyWrapJste,        /**< Wrap within JSTE pseudo elements */
  # TidyWrapPhp,         /**< Wrap within PHP pseudo elements */
  # TidyFixBackslash,    /**< Fix URLs by replacing \ with / */
  # TidyIndentAttributes,/**< Newline+indent before each attribute */
  # TidyXmlPIs,          /**< If set to yes PIs must end with ?> */
  # TidyXmlSpace,        /**< If set to yes adds xml:space attr as needed */
  # TidyEncloseBodyText, /**< If yes text at body is wrapped in P's */
  # TidyEncloseBlockText,/**< If yes text in blocks is wrapped in P's */
  # TidyKeepFileTimes,   /**< If yes last modied time is preserved */
  # TidyWord2000,        /**< Draconian cleaning for Word2000 */
  # TidyMark,            /**< Add meta element indicating tidied doc */
  # TidyEmacs,           /**< If true format error output for GNU Emacs */
  # TidyEmacsFile,       /**< Name of current Emacs file */
  # TidyLiteralAttribs,  /**< If true attributes may use newlines */
  # TidyBodyOnly,        /**< Output BODY content only */
  # TidyFixUri,          /**< Applies URI encoding if necessary */
  # TidyLowerLiterals,   /**< Folds known attribute values to lower case */
  # TidyHideComments,    /**< Hides all (real) comments in output */
  # TidyIndentCdata,     /**< Indent <!CDATA[ ... ]]> section */
  # TidyForceOutput,     /**< Output document even if errors were found */
  # TidyShowErrors,      /**< Number of errors to put out */
  # TidyAsciiChars,      /**< Convert quotes and dashes to nearest ASCII char */
  # TidyJoinClasses,     /**< Join multiple class attributes */
  # TidyJoinStyles,      /**< Join multiple style attributes */
  # TidyEscapeCdata,     /**< Replace <![CDATA[]]> sections with escaped text */
  # TidyIndentSpaces,    /**< Indentation n spaces/tabs */
  # TidyWrapLen,         /**< Wrap margin */
  # TidyTabSize,         /**< Expand tabs to n spaces */








