// Copyright (c) 2023 Yuki Kimoto
// MIT License

// Originally copied from https://github.com/Perl/perl5/blob/v5.42.2/ext/File-Glob/bsd_glob.c

/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Guido van Rossum.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * glob(3) -- a superset of the one defined in POSIX 1003.2.
 *
 * The [!...] convention to negate a range is supported (SysV, Posix, ksh).
 *
 * Optional extra services, controlled by flags not defined by POSIX:
 *
 * SPVM_SYS_IO_GLOB_C_QUOTE:
 *	Escaping convention: \ inhibits any special meaning the following
 *	character might have (except \ at end of string is retained).
 * SPVM_SYS_IO_GLOB_C_MAGCHAR:
 *	Set in gl_flags if pattern contained a globbing character.
 * SPVM_SYS_IO_GLOB_C_NOMAGIC:
 *	Same as SPVM_SYS_IO_GLOB_C_NOCHECK, but it will only append pattern if it did
 *	not contain any magic characters.  [Used in csh style globbing]
 * SPVM_SYS_IO_GLOB_C_TILDE:
 *	expand ~user/foo to the /home/dir/of/user/foo
 * SPVM_SYS_IO_GLOB_C_BRACE:
 *	expand {1,2}{a,b} to 1a 1b 2a 2b
 * gl_matchc:
 *	Number of matches in the current invocation of glob.
 * SPVM_SYS_IO_GLOB_C_ALPHASORT:
 *	sort alphabetically like csh (case doesn't matter) instead of in ASCII
 *	order
 */

#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "spvm_sys_io_glob.h"

#ifndef MAXPATHLEN
#  ifdef PATH_MAX
#    define MAXPATHLEN  PATH_MAX
#  else
#    define MAXPATHLEN  1024
#  endif
#endif

#ifndef ARG_MAX
#  ifdef _SC_ARG_MAX
#    define     ARG_MAX         (sysconf(_SC_ARG_MAX))
#  else
#    ifdef _POSIX_ARG_MAX
#      define   ARG_MAX         _POSIX_ARG_MAX
#    else
#      ifdef WIN32
#        define ARG_MAX         14500   /* from VC's limits.h */
#      else
#        define ARG_MAX         4096    /* from POSIX, be conservative */
#      endif
#    endif
#  endif
#endif

#define BG_DOLLAR       '$'
#define BG_DOT          '.'
#define BG_EOS          '\0'
#define BG_LBRACKET     '['
#define BG_NOT          '!'
#define BG_QUESTION     '?'
#define BG_QUOTE        '\\'
#define BG_RANGE        '-'
#define BG_RBRACKET     ']'
#define BG_SEP  '/'
#ifdef _WIN32
#define BG_SEP2		'\\'
#endif
#define BG_STAR         '*'
#define BG_TILDE        '~'
#define BG_UNDERSCORE   '_'
#define BG_LBRACE       '{'
#define BG_RBRACE       '}'
#define BG_SLASH        '/'
#define BG_COMMA        ','

#define M_QUOTE         0x80
#define M_PROTECT       0x40
#define M_MASK          0xff
#define M_ASCII         0x7f

#define CHAR(c)         ((uint8_t)((c)&M_ASCII))
#define META(c)         ((uint8_t)((c)|M_QUOTE))
#define M_ALL           META('*')
#define M_END           META(']')
#define M_NOT           META('!')
#define M_ONE           META('?')
#define M_RNG           META('-')
#define M_SET           META('[')
#define ismeta(c)       (((c)&M_QUOTE) != 0)

#ifndef S_IFLNK
#  define S_IFLNK 0120000
#endif

#ifndef S_ISLNK
#  define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif

typedef struct stat MY_STAT;
typedef struct dirent MY_DIR;

static void* Renew_v2(void* ptr, size_t n, size_t size);

static void* Newx_v2(size_t n, size_t size);

static void Safefree_v2(void* ptr);

static MY_DIR* PerlDir_open_v2(const char* dir);

static int32_t PerlDir_close_v2(MY_DIR* dir_stream);

static int32_t PerlLIO_stat_v2(const char* file, MY_STAT* stat_info);

static int32_t PerlLIO_lstat_v2(const char* file, MY_STAT* stat_info);

MY_DIR* PerlDir_read(MY_DIR* dirp);

static void* Renew_v2(void* ptr, size_t n, size_t size) {
  return realloc(ptr, n * size);
}

static void* Newx_v2(size_t n, size_t size) {
  return malloc(n * size);
}

static void Safefree_v2(void* ptr) {
  if (ptr) {
    free(ptr);
  }
}

static MY_DIR* PerlDir_open_v2(const char* dir) {
  
  return (MY_DIR*)opendir(dir);
}

static int32_t PerlDir_close_v2(MY_DIR* dir_stream) {
  
  return closedir((DIR*)dir_stream);
}

static int32_t PerlLIO_stat_v2(const char* file, MY_STAT* stat_info) {
  
  return stat(file, stat_info);
}

static int32_t PerlLIO_lstat_v2(const char* file, MY_STAT* stat_info) {
  
#ifdef _WIN32
  return stat(file, stat_info);
#else 
  return lstat(file, stat_info);
#endif
}

static char toFOLD_v2(char ch) {
  return tolower((unsigned char)(ch));
}

static int	 compare(const void *, const void *);
static int	 ci_compare(const void *, const void *);
static int	 g_Ctoc(const char *, char *, size_t);
static int	 g_lstat(char *, MY_STAT *, SPVM_SYS_IO_GLOB *);
static MY_DIR	*g_opendir(char *, SPVM_SYS_IO_GLOB *);
static char	*g_strchr(char *, int);
static int	 g_stat(char *, MY_STAT *, SPVM_SYS_IO_GLOB *);
static int	 glob0(const char *, SPVM_SYS_IO_GLOB *);
static int	 glob1(char *, char *, SPVM_SYS_IO_GLOB *, size_t *);
static int	 glob2(char *, char *, char *, char *, char *, char *,
                       SPVM_SYS_IO_GLOB *, size_t *);
static int	 glob3(char *, char *, char *, char *, char *,
                       char *, char *, SPVM_SYS_IO_GLOB *, size_t *);
static int	 globextend(const char *, SPVM_SYS_IO_GLOB *, size_t *);
static int	 globexp1(const char *, SPVM_SYS_IO_GLOB *);
static int	 globexp2(const char *, const char *, SPVM_SYS_IO_GLOB *, int32_t *);
static int	 match(char *, char *, char *, int);

int32_t spvm_sys_io_glob_bsd_glob(const char* pattern, int32_t flags, SPVM_SYS_IO_GLOB* pglob) {
        const uint8_t *patnext;
        int32_t c;
        char *bufnext, *bufend, patbuf[MAXPATHLEN];
        patnext = (uint8_t *) pattern;
        /* TODO: SPVM_SYS_IO_GLOB_C_APPEND / SPVM_SYS_IO_GLOB_C_DOOFFS aren't supported yet */
#if 0
        if (!(flags & SPVM_SYS_IO_GLOB_C_APPEND)) {
                pglob->gl_pathc = 0;
                pglob->gl_pathv = NULL;
                if (!(flags & SPVM_SYS_IO_GLOB_C_DOOFFS))
                        pglob->gl_offs = 0;
        }
#else
        pglob->gl_pathc = 0;
        pglob->gl_pathv = NULL;
        pglob->gl_offs = 0;
#endif
        pglob->gl_flags = flags & ~SPVM_SYS_IO_GLOB_C_MAGCHAR;
        pglob->gl_matchc = 0;

        bufnext = patbuf;
        bufend = bufnext + MAXPATHLEN - 1;
#ifdef _WIN32
        /* Nasty hack to treat patterns like "C:*" correctly. In this
         * case, the * should match any file in the current directory
         * on the C: drive. However, the glob code does not treat the
         * colon specially, so it looks for files beginning "C:" in
         * the current directory. To fix this, change the pattern to
         * add an explicit "./" at the start (just after the drive
         * letter and colon - ie change to "C:./").
         */
        if (isalpha(pattern[0]) && pattern[1] == ':' &&
            pattern[2] != BG_SEP && pattern[2] != BG_SEP2 &&
            bufend - bufnext > 4) {
                *bufnext++ = pattern[0];
                *bufnext++ = ':';
                *bufnext++ = '.';
                *bufnext++ = BG_SEP;
                patnext += 2;
        }
#endif

        if (flags & SPVM_SYS_IO_GLOB_C_QUOTE) {
                /* Protect the quoted characters. */
                while (bufnext < bufend && (c = *patnext++) != BG_EOS)
                        if (c == BG_QUOTE) {
#ifdef _WIN32
                                    /* To avoid backslashitis on Win32,
                                     * we only treat \ as a quoting character
                                     * if it precedes one of the
                                     * metacharacters []-{}~\
                                     */
                                if ((c = *patnext++) != '[' && c != ']' &&
                                    c != '-' && c != '{' && c != '}' &&
                                    c != '~' && c != '\\') {
#else
                                if ((c = *patnext++) == BG_EOS) {
#endif
                                        c = BG_QUOTE;
                                        --patnext;
                                }
                                *bufnext++ = c | M_PROTECT;
                        } else
                                *bufnext++ = c;
        } else
                while (bufnext < bufend && (c = *patnext++) != BG_EOS)
                        *bufnext++ = c;
        *bufnext = BG_EOS;

        if (flags & SPVM_SYS_IO_GLOB_C_BRACE)
            return globexp1(patbuf, pglob);
        else
            return glob0(patbuf, pglob);
}

/* Free allocated data belonging to a SPVM_SYS_IO_GLOB structure. */
void spvm_sys_io_glob_bsd_globfree(SPVM_SYS_IO_GLOB* pglob) {
        int32_t i;
        char **pp;

        if (pglob->gl_pathv != NULL) {
                pp = pglob->gl_pathv + pglob->gl_offs;
                for (i = pglob->gl_pathc; i--; ++pp)
                        if (*pp)
                                Safefree_v2(*pp);
                Safefree_v2(pglob->gl_pathv);
                pglob->gl_pathv = NULL;
        }
}

MY_DIR* PerlDir_read(MY_DIR* dirp) {
  return readdir((DIR*)dirp);
}

/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
static size_t
my_strlcpy(char *dst, const char *src, size_t siz)
{
  char *d = dst;
  const char *s = src;
  size_t n = siz;

  /* Copy as many bytes as will fit */
  if (n != 0) {
    while (--n != 0) {
      if ((*d++ = *s++) == '\0')
        break;
    }
  }

  /* Not enough room in dst, add NUL and traverse rest of src */
  if (n == 0) {
    if (siz != 0)
      *d = '\0';    /* NUL-terminate dst */
    while (*s++)
      ;
  }

  return(s - src - 1);  /* count does not include NUL */
}

/*
 * Expand recursively a glob {} pattern. When there is no more expansion
 * invoke the standard globbing routine to glob the rest of the magic
 * characters
 */
static int
globexp1(const char *pattern, SPVM_SYS_IO_GLOB *pglob)
{
        const char* ptr = pattern;
        int32_t rv;

        /* Protect a single {}, for find(1), like csh */
        if (pattern[0] == BG_LBRACE && pattern[1] == BG_RBRACE && pattern[2] == BG_EOS)
                return glob0(pattern, pglob);

        while ((ptr = (const char *) g_strchr((char *) ptr, BG_LBRACE)) != NULL)
                if (!globexp2(ptr, pattern, pglob, &rv))
                        return rv;

        return glob0(pattern, pglob);
}


/*
 * Recursive brace globbing helper. Tries to expand a single brace.
 * If it succeeds then it invokes globexp1 with the new pattern.
 * If it fails then it tries to glob the rest of the pattern and returns.
 */
static int
globexp2(const char *ptr, const char *pattern,
         SPVM_SYS_IO_GLOB *pglob, int32_t *rv)
{
        int32_t     i;
        char   *lm, *ls;
        const char *pe, *pm, *pm1, *pl;
        char    patbuf[MAXPATHLEN];

        /* copy part up to the brace */
        for (lm = patbuf, pm = pattern; pm != ptr; *lm++ = *pm++)
                ;
        *lm = BG_EOS;
        ls = lm;

        /* Find the balanced brace */
        for (i = 0, pe = ++ptr; *pe; pe++)
                if (*pe == BG_LBRACKET) {
                        /* Ignore everything between [] */
                        for (pm = pe++; *pe != BG_RBRACKET && *pe != BG_EOS; pe++)
                                ;
                        if (*pe == BG_EOS) {
                                /*
                                 * We could not find a matching BG_RBRACKET.
                                 * Ignore and just look for BG_RBRACE
                                 */
                                pe = pm;
                        }
                } else if (*pe == BG_LBRACE)
                        i++;
                else if (*pe == BG_RBRACE) {
                        if (i == 0)
                                break;
                        i--;
                }

        /* Non matching braces; just glob the pattern */
        if (i != 0 || *pe == BG_EOS) {
                *rv = glob0(patbuf, pglob);
                return 0;
        }

        for (i = 0, pl = pm = ptr; pm <= pe; pm++) {
                switch (*pm) {
                case BG_LBRACKET:
                        /* Ignore everything between [] */
                        for (pm1 = pm++; *pm != BG_RBRACKET && *pm != BG_EOS; pm++)
                                ;
                        if (*pm == BG_EOS) {
                                /*
                                 * We could not find a matching BG_RBRACKET.
                                 * Ignore and just look for BG_RBRACE
                                 */
                                pm = pm1;
                        }
                        break;

                case BG_LBRACE:
                        i++;
                        break;

                case BG_RBRACE:
                        if (i) {
                                i--;
                                break;
                        }
                        /* FALLTHROUGH */
                case BG_COMMA:
                        if (i && *pm == BG_COMMA)
                                break;
                        else {
                                /* Append the current string */
                                for (lm = ls; (pl < pm); *lm++ = *pl++)
                                        ;

                                /*
                                 * Append the rest of the pattern after the
                                 * closing brace
                                 */
                                for (pl = pe + 1; (*lm++ = *pl++) != BG_EOS; )
                                        ;

                                /* Expand the current pattern */
                                *rv = globexp1(patbuf, pglob);

                                /* move after the comma, to the next string */
                                pl = pm + 1;
                        }
                        break;

                default:
                        break;
                }
        }
        *rv = 0;
        return 0;
}

/*
 * The main glob() routine: compiles the pattern (optionally processing
 * quotes), calls glob1() to do the real pattern matching, and finally
 * sorts the list (unless unsorted operation is requested).  Returns 0
 * if things went well, nonzero if errors occurred.  It is not an error
 * to find no matches.
 */
static int
glob0(const char *pattern, SPVM_SYS_IO_GLOB *pglob)
{
        const char *qpat, *qpatnext;
        int32_t c, err, oldflags, oldpathc;
        char *bufnext, patbuf[MAXPATHLEN];
        size_t limit = 0;

        qpat = pattern;
        qpatnext = qpat;
        oldflags = pglob->gl_flags;
        oldpathc = pglob->gl_pathc;
        bufnext = patbuf;

        /* We don't need to check for buffer overflow any more. */
        while ((c = *qpatnext++) != BG_EOS) {
                switch (c) {
                case BG_LBRACKET:
                        c = *qpatnext;
                        if (c == BG_NOT)
                                ++qpatnext;
                        if (*qpatnext == BG_EOS ||
                            g_strchr((char *) qpatnext+1, BG_RBRACKET) == NULL) {
                                *bufnext++ = BG_LBRACKET;
                                if (c == BG_NOT)
                                        --qpatnext;
                                break;
                        }
                        *bufnext++ = M_SET;
                        if (c == BG_NOT)
                                *bufnext++ = M_NOT;
                        c = *qpatnext++;
                        do {
                                *bufnext++ = CHAR(c);
                                if (*qpatnext == BG_RANGE &&
                                    (c = qpatnext[1]) != BG_RBRACKET) {
                                        *bufnext++ = M_RNG;
                                        *bufnext++ = CHAR(c);
                                        qpatnext += 2;
                                }
                        } while ((c = *qpatnext++) != BG_RBRACKET);
                        pglob->gl_flags |= SPVM_SYS_IO_GLOB_C_MAGCHAR;
                        *bufnext++ = M_END;
                        break;
                case BG_QUESTION:
                        pglob->gl_flags |= SPVM_SYS_IO_GLOB_C_MAGCHAR;
                        *bufnext++ = M_ONE;
                        break;
                case BG_STAR:
                        pglob->gl_flags |= SPVM_SYS_IO_GLOB_C_MAGCHAR;
                        /* Collapse adjacent stars to one.
                         * This is required to ensure that a pattern like
                         * "a**" matches a name like "a", as without this
                         * check when the first star matched everything it would
                         * cause the second star to return a match fail.
                         * As long ** is folded here this does not happen.
                         */
                        if (bufnext == patbuf || bufnext[-1] != M_ALL)
                                *bufnext++ = M_ALL;
                        break;
                default:
                        *bufnext++ = CHAR(c);
                        break;
                }
        }
        *bufnext = BG_EOS;

        if ((err = glob1(patbuf, patbuf+MAXPATHLEN-1, pglob, &limit)) != 0) {
                pglob->gl_flags = oldflags;
                return(err);
        }

        /*
         * If there was no match we are going to append the pattern
         * if SPVM_SYS_IO_GLOB_C_NOCHECK was specified or if SPVM_SYS_IO_GLOB_C_NOMAGIC was specified
         * and the pattern did not contain any magic characters
         * SPVM_SYS_IO_GLOB_C_NOMAGIC is there just for compatibility with csh.
         */
        if (pglob->gl_pathc == oldpathc &&
            ((pglob->gl_flags & SPVM_SYS_IO_GLOB_C_NOCHECK) ||
              ((pglob->gl_flags & SPVM_SYS_IO_GLOB_C_NOMAGIC) &&
               !(pglob->gl_flags & SPVM_SYS_IO_GLOB_C_MAGCHAR))))
        {
                pglob->gl_flags = oldflags;
                return(globextend(qpat, pglob, &limit));
        }
        else if (!(pglob->gl_flags & SPVM_SYS_IO_GLOB_C_NOSORT))
            if (pglob->gl_pathv)
                qsort(pglob->gl_pathv + pglob->gl_offs + oldpathc,
                    pglob->gl_pathc - oldpathc, sizeof(char *),
                    (pglob->gl_flags & (SPVM_SYS_IO_GLOB_C_ALPHASORT|SPVM_SYS_IO_GLOB_C_NOCASE))
                        ? ci_compare : compare);
        pglob->gl_flags = oldflags;
        return(0);
}

static int
ci_compare(const void *p, const void *q)
{
        const char *pp = *(const char **)p;
        const char *qq = *(const char **)q;
        int32_t ci;
        while (*pp && *qq) {
                if (toFOLD_v2(*pp) != toFOLD_v2(*qq))
                        break;
                ++pp;
                ++qq;
        }
        ci = toFOLD_v2(*pp) - toFOLD_v2(*qq);
        if (ci == 0)
                return compare(p, q);
        return ci;
}

static int
compare(const void *p, const void *q)
{
        return(strcmp(*(char **)p, *(char **)q));
}

static int
glob1(char *pattern, char *pattern_last, SPVM_SYS_IO_GLOB *pglob, size_t *limitp)
{
        char pathbuf[MAXPATHLEN];

        assert(pattern < pattern_last);

        /* A null pathname is invalid -- POSIX 1003.1 sect. 2.4. */
        if (*pattern == BG_EOS)
                return(0);
        return(glob2(pathbuf, pathbuf+MAXPATHLEN-1,
                     pathbuf, pathbuf+MAXPATHLEN-1,
                     pattern, pattern_last, pglob, limitp));
}

/*
 * The functions glob2 and glob3 are mutually recursive; there is one level
 * of recursion for each segment in the pattern that contains one or more
 * meta characters.
 */
static int
glob2(char *pathbuf, char *pathbuf_last, char *pathend, char *pathend_last,
      char *pattern, char *pattern_last, SPVM_SYS_IO_GLOB *pglob, size_t *limitp)
{
        MY_STAT sb;
        char *p, *q;
        int32_t anymeta;

        assert(pattern < pattern_last);

        /*
         * Loop over pattern segments until end of pattern or until
         * segment with meta character found.
         */
        for (anymeta = 0;;) {
                if (*pattern == BG_EOS) {		/* End of pattern? */
                        *pathend = BG_EOS;
                        if (g_lstat(pathbuf, &sb, pglob))
                                return(0);

                        if (((pglob->gl_flags & SPVM_SYS_IO_GLOB_C_MARK) &&
                            pathend[-1] != BG_SEP
#ifdef _WIN32
                            && pathend[-1] != BG_SEP2
#endif
                            ) && (S_ISDIR(sb.st_mode) ||
                                  (S_ISLNK(sb.st_mode) &&
                            (g_stat(pathbuf, &sb, pglob) == 0) &&
                            S_ISDIR(sb.st_mode)))) {
                                if (pathend+1 > pathend_last)
                                        return (1);
                                *pathend++ = BG_SEP;
                                *pathend = BG_EOS;
                        }
                        ++pglob->gl_matchc;
                        return(globextend(pathbuf, pglob, limitp));
                }

                /* Find end of next segment, copy tentatively to pathend. */
                q = pathend;
                p = pattern;
                while (*p != BG_EOS && *p != BG_SEP
#ifdef _WIN32
                       && *p != BG_SEP2
#endif
                       ) {
                        assert(p < pattern_last);
                        if (ismeta(*p))
                                anymeta = 1;
                        if (q+1 > pathend_last)
                                return (1);
                        *q++ = *p++;
                }

                if (!anymeta) {		/* No expansion, do next segment. */
                        pathend = q;
                        pattern = p;
                        while (*pattern == BG_SEP
#ifdef _WIN32
                               || *pattern == BG_SEP2
#endif
                               ) {
                                assert(p < pattern_last);
                                if (pathend+1 > pathend_last)
                                        return (1);
                                *pathend++ = *pattern++;
                        }
                } else
                        /* Need expansion, recurse. */
                        return(glob3(pathbuf, pathbuf_last, pathend,
                                     pathend_last, pattern,
                                     p, pattern_last, pglob, limitp));
        }
        /* NOTREACHED */
}

static int
glob3(char *pathbuf, char *pathbuf_last, char *pathend, char *pathend_last,
      char *pattern,
      char *restpattern, char *restpattern_last, SPVM_SYS_IO_GLOB *pglob, size_t *limitp)
{
        MY_DIR *dp;
        DIR *dirp;
        int32_t err;
        int32_t nocase;
        char buf[MAXPATHLEN];

        /*
         * The readdirfunc declaration can't be prototyped, because it is
         * assigned, below, to two functions which are prototyped in glob.h
         * and dirent.h as taking pointers to differently typed opaque
         * structures.
         */
        MY_DIR *(*readdirfunc)(DIR*);

        assert(pattern < restpattern_last);
        assert(restpattern < restpattern_last);

        if (pathend > pathend_last)
                return (1);
        *pathend = BG_EOS;
        errno = 0;

        if ((dirp = (DIR*)g_opendir(pathbuf, pglob)) == NULL) {
                return(0);
        }

        err = 0;
        nocase = ((pglob->gl_flags & SPVM_SYS_IO_GLOB_C_NOCASE) != 0);

        /* Search directory for matching names. */
        readdirfunc = (MY_DIR *(*)(DIR *))PerlDir_read;
        while ((dp = (*readdirfunc)(dirp))) {
                uint8_t *sc;
                char *dc;

                /* Initial BG_DOT must be matched literally. */
                if (dp->d_name[0] == BG_DOT && *pattern != BG_DOT)
                        continue;
                dc = pathend;
                sc = (uint8_t *) dp->d_name;
                while (dc < pathend_last && (*dc++ = *sc++) != BG_EOS)
                        ;
                if (dc >= pathend_last) {
                        *dc = BG_EOS;
                        err = 1;
                        break;
                }

                if (!match(pathend, pattern, restpattern, nocase)) {
                        *pathend = BG_EOS;
                        continue;
                }
                err = glob2(pathbuf, pathbuf_last, --dc, pathend_last,
                            restpattern, restpattern_last, pglob, limitp);
                if (err)
                        break;
        }

        PerlDir_close_v2((MY_DIR*)dirp);
        
        return(err);
}


/*
 * Extend the gl_pathv member of a SPVM_SYS_IO_GLOB structure to accommodate a new item,
 * add the new item, and update gl_pathc.
 *
 * This assumes the BSD realloc, which only copies the block when its size
 * crosses a power-of-two boundary; for v7 realloc, this would cause quadratic
 * behavior.
 *
 * Return 0 if new item added, error code if memory couldn't be allocated.
 *
 * Invariant of the SPVM_SYS_IO_GLOB structure:
 *	Either gl_pathc is zero and gl_pathv is NULL; or gl_pathc > 0 and
 *	gl_pathv points to (gl_offs + gl_pathc + 1) items.
 */
static int
globextend(const char *path, SPVM_SYS_IO_GLOB *pglob, size_t *limitp)
{
        char **pathv;
        int32_t i;
        size_t newsize, len;
        char *copy;
        const char *p;

        newsize = sizeof(*pathv) * (2 + pglob->gl_pathc + pglob->gl_offs);
        if (pglob->gl_pathv)
                pathv = Renew_v2(pglob->gl_pathv,newsize,sizeof(char*));
        else
                pathv = Newx_v2(newsize,sizeof(char*));
        if (pathv == NULL) {
                if (pglob->gl_pathv) {
                        Safefree_v2(pglob->gl_pathv);
                        pglob->gl_pathv = NULL;
                }
                return(SPVM_SYS_IO_GLOB_C_NOSPACE);
        }

        if (pglob->gl_pathv == NULL && pglob->gl_offs > 0) {
                /* first time around -- clear initial gl_offs items */
                pathv += pglob->gl_offs;
                for (i = pglob->gl_offs; --i >= 0; )
                        *--pathv = NULL;
        }
        pglob->gl_pathv = pathv;

        for (p = path; *p++;)
                ;
        len = (size_t)(p - path);
        *limitp += len;
        copy = Newx_v2(p-path, sizeof(char));
        if (copy != NULL) {
                if (g_Ctoc(path, copy, len)) {
                        Safefree_v2(copy);
                        return(SPVM_SYS_IO_GLOB_C_NOSPACE);
                }
                pathv[pglob->gl_offs + pglob->gl_pathc++] = copy;
        }
        pathv[pglob->gl_offs + pglob->gl_pathc] = NULL;

        if ((pglob->gl_flags & SPVM_SYS_IO_GLOB_C_LIMIT) &&
            newsize + *limitp >= (unsigned long)ARG_MAX) {
                errno = 0;
                return(SPVM_SYS_IO_GLOB_C_NOSPACE);
        }

        return(copy == NULL ? SPVM_SYS_IO_GLOB_C_NOSPACE : 0);
}


/*
 * pattern matching function for filenames using state machine to avoid
 * recursion. We maintain a "nextp" and "nextn" to allow us to backtrack
 * without additional callframes, and to do cleanly prune the backtracking
 * state when multiple '*' (start) matches are included in the pattern.
 *
 * Thanks to Russ Cox for the improved state machine logic to avoid quadratic
 * matching on failure.
 *
 * https://research.swtch.com/glob
 *
 * An example would be a pattern
 *  ("a*" x 100) . "y"
 * against a file name like
 *  ("a" x 100) . "x"
 *
 */
static int
match(char *name, char *pat, char *patend, int32_t nocase)
{
        int32_t ok, negate_range;
        char c, k;
        char *nextp = NULL;
        char *nextn = NULL;

    redo:
        while (pat < patend) {
                c = *pat++;
                switch (c & M_MASK) {
                case M_ALL:
                        if (pat == patend)
                                return(1);
                        if (*name == BG_EOS)
                                return 0;
                        nextn = name + 1;
                        nextp = pat - 1;
                        break;
                case M_ONE:
                        /* since * matches leftmost-shortest first   *
                         * if we encounter the EOS then backtracking *
                         * will not help, so we can exit early here. */
                        if (*name++ == BG_EOS)
                                return 0;
                        break;
                case M_SET:
                        ok = 0;
                        /* since * matches leftmost-shortest first   *
                         * if we encounter the EOS then backtracking *
                         * will not help, so we can exit early here. */
                        if ((k = *name++) == BG_EOS)
                                return 0;
                        if ((negate_range = ((*pat & M_MASK) == M_NOT)) != BG_EOS)
                                ++pat;
                        while (((c = *pat++) & M_MASK) != M_END)
                                if ((*pat & M_MASK) == M_RNG) {
                                        if (nocase) {
                                                if (tolower(c) <= tolower(k) && tolower(k) <= tolower(pat[1]))
                                                        ok = 1;
                                        } else {
                                                if (c <= k && k <= pat[1])
                                                        ok = 1;
                                        }
                                        pat += 2;
                                } else if (nocase ? (tolower(c) == tolower(k)) : (c == k))
                                        ok = 1;
                        if (ok == negate_range)
                                goto fail;
                        break;
                default:
                        k = *name++;
                        if (nocase ? (tolower(k) != tolower(c)) : (k != c))
                                goto fail;
                        break;
                }
        }
        if (*name == BG_EOS)
                return 1;

    fail:
        if (nextn) {
                pat = nextp;
                name = nextn;
                goto redo;
        }
        return 0;
}

static MY_DIR*
g_opendir(char *str, SPVM_SYS_IO_GLOB *pglob)
{
        char buf[MAXPATHLEN];

        if (!*str) {
                my_strlcpy(buf, ".", sizeof(buf));
        } else {
                if (g_Ctoc(str, buf, sizeof(buf)))
                        return(NULL);
        }

        return(PerlDir_open_v2(buf));
}

static int
g_lstat(char *fn, MY_STAT *sb, SPVM_SYS_IO_GLOB *pglob)
{
        char buf[MAXPATHLEN];

        if (g_Ctoc(fn, buf, sizeof(buf)))
                return(-1);
        return(PerlLIO_lstat_v2(buf, sb));
}

static int
g_stat(char *fn, MY_STAT *sb, SPVM_SYS_IO_GLOB *pglob)
{
        char buf[MAXPATHLEN];

        if (g_Ctoc(fn, buf, sizeof(buf)))
                return(-1);
        return(PerlLIO_stat_v2(buf, sb));
}

static char *
g_strchr(char *str, int32_t ch)
{
        do {
                if (*str == ch)
                        return (str);
        } while (*str++);
        return (NULL);
}

static int
g_Ctoc(const char *str, char *buf, size_t len)
{
        while (len--) {
                if ((*buf++ = (char)*str++) == BG_EOS)
                        return (0);
        }
        return (1);
}

