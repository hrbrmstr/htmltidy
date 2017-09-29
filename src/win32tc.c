/* win32tc.c -- Interface to Win32 transcoding routines

  (c) 1998-2008 (W3C) MIT, ERCIM, Keio University
  See tidy.h for the copyright notice.

*/

/* keep these here to keep file non-empty */
#include "tidy.h"
#include "forward.h"
#include "streamio.h"
#include "tmbstr.h"
#include "utf8.h"

#ifdef TIDY_WIN32_MLANG_SUPPORT

#define VC_EXTRALEAN
#define CINTERFACE
#define COBJMACROS

#include <windows.h>
#include <mlang.h>

#undef COBJMACROS
#undef CINTERFACE
#undef VC_EXTRALEAN

/* maximum number of bytes for a single character */
#define TC_INBUFSIZE  16

/* maximum number of characters per byte sequence */
#define TC_OUTBUFSIZE 16

#define CreateMLangObject(p) \
  CoCreateInstance( \
        &CLSID_CMLangConvertCharset, \
        NULL, \
        CLSCTX_ALL, \
        &IID_IMLangConvertCharset, \
        (VOID **)&p);


/* Character Set to Microsoft Windows Codepage Identifier map,     */
/* from <rotor/sscli/clr/src/classlibnative/nls/encodingdata.cpp>. */

/* note: the 'safe' field indicates whether this encoding can be   */
/* read/written character-by-character; this does not apply to     */
/* various stateful encodings such as ISO-2022 or UTF-7, these     */
/* must be read/written as a complete stream. It is possible that  */
/* some 'unsafe' encodings are marked as 'save'.                   */

/* todo: cleanup; Tidy should use only a single mapping table to   */
/* circumvent unsupported aliases in other transcoding libraries,  */
/* enable reverse lookup of encoding names and ease maintenance.   */

static struct _nameWinCPMap
{
    tmbstr name;
    uint wincp;
    Bool safe;
} const NameWinCPMap[] = {
  { "cp037",                                            37, aye },
  { "csibm037",                                         37, aye },
  { "ebcdic-cp-ca",                                     37, aye },
  { "ebcdic-cp-nl",                                     37, aye },
  { "ebcdic-cp-us",                                     37, aye },
  { "ebcdic-cp-wt",                                     37, aye },
  { "ibm037",                                           37, aye },
  { "cp437",                                           437, aye },
  { "cspc8codepage437",                                437, aye },
  { "ibm437",                                          437, aye },
  { "cp500",                                           500, aye },
  { "csibm500",                                        500, aye },
  { "ebcdic-cp-be",                                    500, aye },
  { "ebcdic-cp-ch",                                    500, aye },
  { "ibm500",                                          500, aye },
  { "asmo-708",                                        708, aye },
  { "dos-720",                                         720, aye },
  { "ibm737",                                          737, aye },
  { "ibm775",                                          775, aye },
  { "cp850",                                           850, aye },
  { "ibm850",                                          850, aye },
  { "cp852",                                           852, aye },
  { "ibm852",                                          852, aye },
  { "cp855",                                           855, aye },
  { "ibm855",                                          855, aye },
  { "cp857",                                           857, aye },
  { "ibm857",                                          857, aye },
  { "ccsid00858",                                      858, aye },
  { "cp00858",                                         858, aye },
  { "cp858",                                           858, aye },
  { "ibm00858",                                        858, aye },
  { "pc-multilingual-850+euro",                        858, aye },
  { "cp860",                                           860, aye },
  { "ibm860",                                          860, aye },
  { "cp861",                                           861, aye },
  { "ibm861",                                          861, aye },
  { "cp862",                                           862, aye },
  { "dos-862",                                         862, aye },
  { "ibm862",                                          862, aye },
  { "cp863",                                           863, aye },
  { "ibm863",                                          863, aye },
  { "cp864",                                           864, aye },
  { "ibm864",                                          864, aye },
  { "cp865",                                           865, aye },
  { "ibm865",                                          865, aye },
  { "cp866",                                           866, aye },
  { "ibm866",                                          866, aye },
  { "cp869",                                           869, aye },
  { "ibm869",                                          869, aye },
  { "cp870",                                           870, aye },
  { "csibm870",                                        870, aye },
  { "ebcdic-cp-roece",                                 870, aye },
  { "ebcdic-cp-yu",                                    870, aye },
  { "ibm870",                                          870, aye },
  { "dos-874",                                         874, aye },
  { "iso-8859-11",                                     874, aye },
  { "tis-620",                                         874, aye },
  { "windows-874",                                     874, aye },
  { "cp875",                                           875, aye },
  { "csshiftjis",                                      932, aye },
  { "cswindows31j",                                    932, aye },
  { "ms_kanji",                                        932, aye },
  { "shift-jis",                                       932, aye },
  { "shift_jis",                                       932, aye },
  { "sjis",                                            932, aye },
  { "x-ms-cp932",                                      932, aye },
  { "x-sjis",                                          932, aye },
  { "chinese",                                         936, aye },
  { "cn-gb",                                           936, aye },
  { "csgb2312",                                        936, aye },
  { "csgb231280",                                      936, aye },
  { "csiso58gb231280",                                 936, aye },
  { "gb2312",                                          936, aye },
  { "gb2312-80",                                       936, aye },
  { "gb231280",                                        936, aye },
  { "gb_2312-80",                                      936, aye },
  { "gbk",                                             936, aye },
  { "iso-ir-58",                                       936, aye },
  { "csksc56011987",                                   949, aye },
  { "iso-ir-149",                                      949, aye },
  { "korean",                                          949, aye },
  { "ks-c-5601",                                       949, aye },
  { "ks-c5601",                                        949, aye },
  { "ks_c_5601",                                       949, aye },
  { "ks_c_5601-1987",                                  949, aye },
  { "ks_c_5601-1989",                                  949, aye },
  { "ks_c_5601_1987",                                  949, aye },
  { "ksc5601",                                         949, aye },
  { "ksc_5601",                                        949, aye },
  { "big5",                                            950, aye },
  { "big5-hkscs",                                      950, aye },
  { "cn-big5",                                         950, aye },
  { "csbig5",                                          950, aye },
  { "x-x-big5",                                        950, aye },
  { "cp1026",                                         1026, aye },
  { "csibm1026",                                      1026, aye },
  { "ibm1026",                                        1026, aye },
  { "ibm01047",                                       1047, aye },
  { "ccsid01140",                                     1140, aye },
  { "cp01140",                                        1140, aye },
  { "ebcdic-us-37+euro",                              1140, aye },
  { "ibm01140",                                       1140, aye },
  { "ccsid01141",                                     1141, aye },
  { "cp01141",                                        1141, aye },
  { "ebcdic-de-273+euro",                             1141, aye },
  { "ibm01141",                                       1141, aye },
  { "ccsid01142",                                     1142, aye },
  { "cp01142",                                        1142, aye },
  { "ebcdic-dk-277+euro",                             1142, aye },
  { "ebcdic-no-277+euro",                             1142, aye },
  { "ibm01142",                                       1142, aye },
  { "ccsid01143",                                     1143, aye },
  { "cp01143",                                        1143, aye },
  { "ebcdic-fi-278+euro",                             1143, aye },
  { "ebcdic-se-278+euro",                             1143, aye },
  { "ibm01143",                                       1143, aye },
  { "ccsid01144",                                     1144, aye },
  { "cp01144",                                        1144, aye },
  { "ebcdic-it-280+euro",                             1144, aye },
  { "ibm01144",                                       1144, aye },
  { "ccsid01145",                                     1145, aye },
  { "cp01145",                                        1145, aye },
  { "ebcdic-es-284+euro",                             1145, aye },
  { "ibm01145",                                       1145, aye },
  { "ccsid01146",                                     1146, aye },
  { "cp01146",                                        1146, aye },
  { "ebcdic-gb-285+euro",                             1146, aye },
  { "ibm01146",                                       1146, aye },
  { "ccsid01147",                                     1147, aye },
  { "cp01147",                                        1147, aye },
  { "ebcdic-fr-297+euro",                             1147, aye },
  { "ibm01147",                                       1147, aye },
  { "ccsid01148",                                     1148, aye },
  { "cp01148",                                        1148, aye },
  { "ebcdic-international-500+euro",                  1148, aye },
  { "ibm01148",                                       1148, aye },
  { "ccsid01149",                                     1149, aye },
  { "cp01149",                                        1149, aye },
  { "ebcdic-is-871+euro",                             1149, aye },
  { "ibm01149",                                       1149, aye },
  { "iso-10646-ucs-2",                                1200, aye },
  { "ucs-2",                                          1200, aye },
  { "unicode",                                        1200, aye },
  { "utf-16",                                         1200, aye },
  { "utf-16le",                                       1200, aye },
  { "unicodefffe",                                    1201, aye },
  { "utf-16be",                                       1201, aye },
  { "windows-1250",                                   1250, aye },
  { "x-cp1250",                                       1250, aye },
  { "windows-1251",                                   1251, aye },
  { "x-cp1251",                                       1251, aye },
  { "windows-1252",                                   1252, aye },
  { "x-ansi",                                         1252, aye },
  { "windows-1253",                                   1253, aye },
  { "windows-1254",                                   1254, aye },
  { "windows-1255",                                   1255, aye },
  { "cp1256",                                         1256, aye },
  { "windows-1256",                                   1256, aye },
  { "windows-1257",                                   1257, aye },
  { "windows-1258",                                   1258, aye },
  { "johab",                                          1361, aye },
  { "macintosh",                                     10000, aye },
  { "x-mac-japanese",                                10001, aye },
  { "x-mac-chinesetrad",                             10002, aye },
  { "x-mac-korean",                                  10003, aye },
  { "x-mac-arabic",                                  10004, aye },
  { "x-mac-hebrew",                                  10005, aye },
  { "x-mac-greek",                                   10006, aye },
  { "x-mac-cyrillic",                                10007, aye },
  { "x-mac-chinesesimp",                             10008, aye },
  { "x-mac-romanian",                                10010, aye },
  { "x-mac-ukrainian",                               10017, aye },
  { "x-mac-thai",                                    10021, aye },
  { "x-mac-ce",                                      10029, aye },
  { "x-mac-icelandic",                               10079, aye },
  { "x-mac-turkish",                                 10081, aye },
  { "x-mac-croatian",                                10082, aye },
  { "x-chinese-cns",                                 20000, aye },
  { "x-cp20001",                                     20001, aye },
  { "x-chinese-eten",                                20002, aye },
  { "x-cp20003",                                     20003, aye },
  { "x-cp20004",                                     20004, aye },
  { "x-cp20005",                                     20005, aye },
  { "irv",                                           20105, aye },
  { "x-ia5",                                         20105, aye },
  { "din_66003",                                     20106, aye },
  { "german",                                        20106, aye },
  { "x-ia5-german",                                  20106, aye },
  { "sen_850200_b",                                  20107, aye },
  { "swedish",                                       20107, aye },
  { "x-ia5-swedish",                                 20107, aye },
  { "norwegian",                                     20108, aye },
  { "ns_4551-1",                                     20108, aye },
  { "x-ia5-norwegian",                               20108, aye },
  { "ansi_x3.4-1968",                                20127, aye },
  { "ansi_x3.4-1986",                                20127, aye },
  { "ascii",                                         20127, aye },
  { "cp367",                                         20127, aye },
  { "csascii",                                       20127, aye },
  { "ibm367",                                        20127, aye },
  { "iso-ir-6",                                      20127, aye },
  { "iso646-us",                                     20127, aye },
  { "iso_646.irv:1991",                              20127, aye },
  { "us",                                            20127, aye },
  { "us-ascii",                                      20127, aye },
  { "x-cp20261",                                     20261, aye },
  { "x-cp20269",                                     20269, aye },
  { "cp273",                                         20273, aye },
  { "csibm273",                                      20273, aye },
  { "ibm273",                                        20273, aye },
  { "csibm277",                                      20277, aye },
  { "ebcdic-cp-dk",                                  20277, aye },
  { "ebcdic-cp-no",                                  20277, aye },
  { "ibm277",                                        20277, aye },
  { "cp278",                                         20278, aye },
  { "csibm278",                                      20278, aye },
  { "ebcdic-cp-fi",                                  20278, aye },
  { "ebcdic-cp-se",                                  20278, aye },
  { "ibm278",                                        20278, aye },
  { "cp280",                                         20280, aye },
  { "csibm280",                                      20280, aye },
  { "ebcdic-cp-it",                                  20280, aye },
  { "ibm280",                                        20280, aye },
  { "cp284",                                         20284, aye },
  { "csibm284",                                      20284, aye },
  { "ebcdic-cp-es",                                  20284, aye },
  { "ibm284",                                        20284, aye },
  { "cp285",                                         20285, aye },
  { "csibm285",                                      20285, aye },
  { "ebcdic-cp-gb",                                  20285, aye },
  { "ibm285",                                        20285, aye },
  { "cp290",                                         20290, aye },
  { "csibm290",                                      20290, aye },
  { "ebcdic-jp-kana",                                20290, aye },
  { "ibm290",                                        20290, aye },
  { "cp297",                                         20297, aye },
  { "csibm297",                                      20297, aye },
  { "ebcdic-cp-fr",                                  20297, aye },
  { "ibm297",                                        20297, aye },
  { "cp420",                                         20420, aye },
  { "csibm420",                                      20420, aye },
  { "ebcdic-cp-ar1",                                 20420, aye },
  { "ibm420",                                        20420, aye },
  { "cp423",                                         20423, aye },
  { "csibm423",                                      20423, aye },
  { "ebcdic-cp-gr",                                  20423, aye },
  { "ibm423",                                        20423, aye },
  { "cp424",                                         20424, aye },
  { "csibm424",                                      20424, aye },
  { "ebcdic-cp-he",                                  20424, aye },
  { "ibm424",                                        20424, aye },
  { "x-ebcdic-koreanextended",                       20833, aye },
  { "csibmthai",                                     20838, aye },
  { "ibm-thai",                                      20838, aye },
  { "cskoi8r",                                       20866, aye },
  { "koi",                                           20866, aye },
  { "koi8",                                          20866, aye },
  { "koi8-r",                                        20866, aye },
  { "koi8r",                                         20866, aye },
  { "cp871",                                         20871, aye },
  { "csibm871",                                      20871, aye },
  { "ebcdic-cp-is",                                  20871, aye },
  { "ibm871",                                        20871, aye },
  { "cp880",                                         20880, aye },
  { "csibm880",                                      20880, aye },
  { "ebcdic-cyrillic",                               20880, aye },
  { "ibm880",                                        20880, aye },
  { "cp905",                                         20905, aye },
  { "csibm905",                                      20905, aye },
  { "ebcdic-cp-tr",                                  20905, aye },
  { "ibm905",                                        20905, aye },
  { "ccsid00924",                                    20924, aye },
  { "cp00924",                                       20924, aye },
  { "ebcdic-latin9--euro",                           20924, aye },
  { "ibm00924",                                      20924, aye },
  { "x-cp20936",                                     20936, aye },
  { "x-cp20949",                                     20949, aye },
  { "cp1025",                                        21025, aye },
  { "x-cp21027",                                     21027, aye },
  { "koi8-ru",                                       21866, aye },
  { "koi8-u",                                        21866, aye },
  { "cp819",                                         28591, aye },
  { "csisolatin1",                                   28591, aye },
  { "ibm819",                                        28591, aye },
  { "iso-8859-1",                                    28591, aye },
  { "iso-ir-100",                                    28591, aye },
  { "iso8859-1",                                     28591, aye },
  { "iso_8859-1",                                    28591, aye },
  { "iso_8859-1:1987",                               28591, aye },
  { "l1",                                            28591, aye },
  { "latin1",                                        28591, aye },
  { "csisolatin2",                                   28592, aye },
  { "iso-8859-2",                                    28592, aye },
  { "iso-ir-101",                                    28592, aye },
  { "iso8859-2",                                     28592, aye },
  { "iso_8859-2",                                    28592, aye },
  { "iso_8859-2:1987",                               28592, aye },
  { "l2",                                            28592, aye },
  { "latin2",                                        28592, aye },
  { "csisolatin3",                                   28593, aye },
  { "iso-8859-3",                                    28593, aye },
  { "iso-ir-109",                                    28593, aye },
  { "iso_8859-3",                                    28593, aye },
  { "iso_8859-3:1988",                               28593, aye },
  { "l3",                                            28593, aye },
  { "latin3",                                        28593, aye },
  { "csisolatin4",                                   28594, aye },
  { "iso-8859-4",                                    28594, aye },
  { "iso-ir-110",                                    28594, aye },
  { "iso_8859-4",                                    28594, aye },
  { "iso_8859-4:1988",                               28594, aye },
  { "l4",                                            28594, aye },
  { "latin4",                                        28594, aye },
  { "csisolatincyrillic",                            28595, aye },
  { "cyrillic",                                      28595, aye },
  { "iso-8859-5",                                    28595, aye },
  { "iso-ir-144",                                    28595, aye },
  { "iso_8859-5",                                    28595, aye },
  { "iso_8859-5:1988",                               28595, aye },
  { "arabic",                                        28596, aye },
  { "csisolatinarabic",                              28596, aye },
  { "ecma-114",                                      28596, aye },
  { "iso-8859-6",                                    28596, aye },
  { "iso-ir-127",                                    28596, aye },
  { "iso_8859-6",                                    28596, aye },
  { "iso_8859-6:1987",                               28596, aye },
  { "csisolatingreek",                               28597, aye },
  { "ecma-118",                                      28597, aye },
  { "elot_928",                                      28597, aye },
  { "greek",                                         28597, aye },
  { "greek8",                                        28597, aye },
  { "iso-8859-7",                                    28597, aye },
  { "iso-ir-126",                                    28597, aye },
  { "iso_8859-7",                                    28597, aye },
  { "iso_8859-7:1987",                               28597, aye },
  { "csisolatinhebrew",                              28598, aye },
  { "hebrew",                                        28598, aye },
  { "iso-8859-8",                                    28598, aye },
  { "iso-ir-138",                                    28598, aye },
  { "iso_8859-8",                                    28598, aye },
  { "iso_8859-8:1988",                               28598, aye },
  { "logical",                                       28598, aye },
  { "visual",                                        28598, aye },
  { "csisolatin5",                                   28599, aye },
  { "iso-8859-9",                                    28599, aye },
  { "iso-ir-148",                                    28599, aye },
  { "iso_8859-9",                                    28599, aye },
  { "iso_8859-9:1989",                               28599, aye },
  { "l5",                                            28599, aye },
  { "latin5",                                        28599, aye },
  { "iso-8859-13",                                   28603, aye },
  { "csisolatin9",                                   28605, aye },
  { "iso-8859-15",                                   28605, aye },
  { "iso_8859-15",                                   28605, aye },
  { "l9",                                            28605, aye },
  { "latin9",                                        28605, aye },
  { "x-europa",                                      29001, aye },
  { "iso-8859-8-i",                                  38598, aye },
  { "iso-2022-jp",                                   50220,  no },
  { "csiso2022jp",                                   50221,  no },
  { "csiso2022kr",                                   50225,  no },
  { "iso-2022-kr",                                   50225,  no },
  { "iso-2022-kr-7",                                 50225,  no },
  { "iso-2022-kr-7bit",                              50225,  no },
  { "cp50227",                                       50227,  no },
  { "x-cp50227",                                     50227,  no },
  { "cp930",                                         50930, aye },
  { "x-ebcdic-japaneseanduscanada",                  50931, aye },
  { "cp933",                                         50933, aye },
  { "cp935",                                         50935, aye },
  { "cp937",                                         50937, aye },
  { "cp939",                                         50939, aye },
  { "cseucpkdfmtjapanese",                           51932, aye },
  { "euc-jp",                                        51932, aye },
  { "extended_unix_code_packed_format_for_japanese", 51932, aye },
  { "iso-2022-jpeuc",                                51932, aye },
  { "x-euc",                                         51932, aye },
  { "x-euc-jp",                                      51932, aye },
  { "euc-cn",                                        51936, aye },
  { "x-euc-cn",                                      51936, aye },
  { "cseuckr",                                       51949, aye },
  { "euc-kr",                                        51949, aye },
  { "iso-2022-kr-8",                                 51949, aye },
  { "iso-2022-kr-8bit",                              51949, aye },
  { "hz-gb-2312",                                    52936,  no },
  { "gb18030",                                       54936, aye },
  { "x-iscii-de",                                    57002, aye },
  { "x-iscii-be",                                    57003, aye },
  { "x-iscii-ta",                                    57004, aye },
  { "x-iscii-te",                                    57005, aye },
  { "x-iscii-as",                                    57006, aye },
  { "x-iscii-or",                                    57007, aye },
  { "x-iscii-ka",                                    57008, aye },
  { "x-iscii-ma",                                    57009, aye },
  { "x-iscii-gu",                                    57010, aye },
  { "x-iscii-pa",                                    57011, aye },
  { "csunicode11utf7",                               65000,  no },
  { "unicode-1-1-utf-7",                             65000,  no },
  { "unicode-2-0-utf-7",                             65000,  no },
  { "utf-7",                                         65000,  no },
  { "x-unicode-1-1-utf-7",                           65000,  no },
  { "x-unicode-2-0-utf-7",                           65000,  no },
  { "unicode-1-1-utf-8",                             65001, aye },
  { "unicode-2-0-utf-8",                             65001, aye },
  { "utf-8",                                         65001, aye },
  { "x-unicode-1-1-utf-8",                           65001, aye },
  { "x-unicode-2-0-utf-8",                           65001, aye },

  /* final entry */
  { NULL,                                                0,  no }
};

uint TY_(Win32MLangGetCPFromName)(TidyAllocator *allocator, ctmbstr encoding)
{
    uint i;
    tmbstr enc;

    /* ensure name is in lower case */
    enc = TY_(tmbstrdup)(allocator,encoding);
    enc = TY_(tmbstrtolower)(enc);

    for (i = 0; NameWinCPMap[i].name; ++i)
    {
        if (TY_(tmbstrcmp)(NameWinCPMap[i].name, enc) == 0)
        {
            IMLangConvertCharset * p = NULL;
            uint wincp = NameWinCPMap[i].wincp;
            HRESULT hr;

            TidyFree(allocator, enc);

            /* currently no support for unsafe encodings */
            if (!NameWinCPMap[i].safe)
                return 0;

            /* hack for config.c */
            CoInitialize(NULL);
            hr = CreateMLangObject(p);

            if (hr != S_OK || !p)
            {
                wincp = 0;
            }
            else
            {
                hr = IMLangConvertCharset_Initialize(p, wincp, 1200, 0);

                if (hr != S_OK)
                    wincp = 0;

                IMLangConvertCharset_Release(p);
                p = NULL;
            }

            CoUninitialize();

            return wincp;
        }
    }

    TidyFree(allocator, enc);
    return 0;
}

Bool TY_(Win32MLangInitInputTranscoder)(StreamIn * in, uint wincp)
{
    IMLangConvertCharset * p = NULL;
    HRESULT hr;

    assert( in != NULL );

    CoInitialize(NULL);

    if (wincp == 0)
    {
        /* no codepage found for this encoding */
        return no;
    }

    hr = CreateMLangObject(p);

    if (hr != S_OK || !p)
    {
        /* MLang not supported */
        return no;
    }

    hr = IMLangConvertCharset_Initialize(p, wincp, 1200, 0);

    if (hr != S_OK)
    {
        /* encoding not supported, insufficient memory, etc. */
        return no;
    }

    in->mlang = p;

    return aye;
}

void TY_(Win32MLangUninitInputTranscoder)(StreamIn * in)
{
    IMLangConvertCharset * p;

    assert( in != NULL );

    p = (IMLangConvertCharset *)in->mlang;
    if (p)
    {
        IMLangConvertCharset_Release(p);
        p = NULL;
        in->mlang = NULL;
    }

    CoUninitialize();
}

#if 0
Bool Win32MLangInitOutputTranscoder(TidyAllocator *allocator, StreamOut * out, tmbstr encoding)
{
    IMLangConvertCharset * p = NULL;
    HRESULT hr;
    uint wincp;

    assert( out != NULL );

    CoInitialize(NULL);

    wincp = TY_(Win32MLangGetCPFromName)(allocator, encoding);
    if (wincp == 0)
    {
        /* no codepage found for this encoding */
        return no;
    }

    hr = CreateMLangObject(p);

    if (hr != S_OK || !p)
    {
        /* MLang not supported */
        return no;
    }

    IMLangConvertCharset_Initialize(p, 1200, wincp, MLCONVCHARF_NOBESTFITCHARS);

    if (hr != S_OK)
    {
        /* encoding not supported, insufficient memory, etc. */
        return no;
    }

    out->mlang = p;

    return aye;
}

void Win32MLangUninitOutputTranscoder(StreamOut * out)
{
    IMLangConvertCharset * p;

    assert( out != NULL );

    p = (IMLangConvertCharset *)out->mlang;
    if (p)
    {
        IMLangConvertCharset_Release(p);
        p = NULL;
        out->mlang = NULL;
    }

    CoUninitialize();
}
#endif

int TY_(Win32MLangGetChar)(byte firstByte, StreamIn * in, uint * bytesRead)
{
    IMLangConvertCharset * p;
    TidyInputSource * source;
    CHAR inbuf[TC_INBUFSIZE] = { 0 };
    WCHAR outbuf[TC_OUTBUFSIZE] = { 0 };
    HRESULT hr = S_OK;
    size_t inbufsize = 0;

    assert( in != NULL );
    assert( &in->source != NULL );
    assert( bytesRead != NULL );
    assert( in->mlang != NULL );

    p = (IMLangConvertCharset *)in->mlang;
    source = &in->source;

    inbuf[inbufsize++] = (CHAR)firstByte;

    while(inbufsize < TC_INBUFSIZE)
    {
        UINT outbufsize = TC_OUTBUFSIZE;
        UINT readNow = inbufsize;
        int nextByte = EndOfStream;

        hr = IMLangConvertCharset_DoConversionToUnicode(p, inbuf, &readNow, outbuf, &outbufsize);

        assert( hr == S_OK );
        assert( outbufsize <= 2 );

        if (outbufsize == 2)
        {
            /* U+10000-U+10FFFF are returned as a pair of surrogates */
            tchar m = (tchar)outbuf[0];
            tchar n = (tchar)outbuf[1];
            assert( TY_(IsHighSurrogate)(n) && TY_(IsLowSurrogate)(m) );
            *bytesRead = readNow;
            return (int)TY_(CombineSurrogatePair)(n, m);
        }

        if (outbufsize == 1)
        {
            /* we found the character   */
            /* set bytesRead and return */
            *bytesRead = readNow;
            return (int)outbuf[0];
        }

        /* we need more bytes */
        nextByte = source->getByte(source->sourceData);

        if (nextByte == EndOfStream)
        {
            /* todo: error message for broken stream? */

            *bytesRead = readNow;
            return EndOfStream;
        }

        inbuf[inbufsize++] = (CHAR)nextByte;
    }

    /* No full character found after reading TC_INBUFSIZE bytes, */
    /* give up to read this stream, it's obviously unreadable.   */

    /* todo: error message for broken stream? */
    return EndOfStream;
}

Bool Win32MLangIsConvertible(tchar c, StreamOut * out)
{
    IMLangConvertCharset * p;
    UINT i = 1;
    HRESULT hr;
    WCHAR inbuf[2] = { 0 };
    UINT inbufsize = 0;

    assert( c != 0 );
    assert( c <= 0x10FFFF );
    assert( out != NULL );
    assert( out->mlang != NULL );

    if (c > 0xFFFF)
    {
        tchar high = 0;
        tchar low = 0;

        TY_(SplitSurrogatePair)(c, &low, &high);

        inbuf[inbufsize++] = (WCHAR)low;
        inbuf[inbufsize++] = (WCHAR)high;
    }
    else
        inbuf[inbufsize++] = (WCHAR)c;

    p = (IMLangConvertCharset *)out->mlang;
    hr = IMLangConvertCharset_DoConversionFromUnicode(p, inbuf, &inbufsize, NULL, NULL);

    return hr == S_OK ? aye : no;
}

void Win32MLangPutChar(tchar c, StreamOut * out, uint * bytesWritten)
{
    IMLangConvertCharset * p;
    TidyOutputSink * sink;
    CHAR outbuf[TC_OUTBUFSIZE] = { 0 };
    UINT outbufsize = TC_OUTBUFSIZE;
    HRESULT hr = S_OK;
    WCHAR inbuf[2] = { 0 };
    UINT inbufsize = 0;
    uint i;

    assert( c != 0 );
    assert( c <= 0x10FFFF );
    assert( bytesWritten != NULL );
    assert( out != NULL );
    assert( &out->sink != NULL );
    assert( out->mlang != NULL );

    p = (IMLangConvertCharset *)out->mlang;
    sink = &out->sink;

    if (c > 0xFFFF)
    {
        tchar high = 0;
        tchar low = 0;

        TY_(SplitSurrogatePair)(c, &low, &high);

        inbuf[inbufsize++] = (WCHAR)low;
        inbuf[inbufsize++] = (WCHAR)high;
    }
    else
        inbuf[inbufsize++] = (WCHAR)c;

    hr = IMLangConvertCharset_DoConversionFromUnicode(p, inbuf, &inbufsize, outbuf, &outbufsize);

    assert( hr == S_OK );
    assert( outbufsize > 0 );
    assert( inbufsize == 1 || inbufsize == 2 );

    for (i = 0; i < outbufsize; ++i)
        sink->putByte(sink->sinkData, (byte)(outbuf[i]));

    *bytesWritten = outbufsize;

    return;
}

#endif /* TIDY_WIN32_MLANG_SUPPORT */

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
