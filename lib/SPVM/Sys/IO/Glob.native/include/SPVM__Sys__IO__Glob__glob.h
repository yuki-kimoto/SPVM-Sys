// Copyright (c) 2023 Yuki Kimoto
// MIT License

// Originally copied from https://github.com/Perl/perl5/blob/v5.42.2/ext/File-Glob/bsd_glob.h

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
 *
 *	@(#)glob.h	8.1 (Berkeley) 6/2/93
 *	[lots of perl-specific changes since then--see bsd_glob.c]
 */

#ifndef SPVM__SYS__IO__GLOB__GLOB_H
#define SPVM__SYS__IO__GLOB__GLOB_H

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
#if 0
  #include <pwd.h>
#endif
#include <stdlib.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include <string.h>
#include <unistd.h>

// Types defined in perl.h
typedef size_t STRLEN;
typedef struct stat Stat_t;
typedef uint16_t U16;
typedef uint8_t U8;
typedef struct dirent Direntry_t;

// Functions defined in perl.h
#define PerlEnv_getenv(name) getenv(name)
#define PerlDir_close(dh) closedir(dh)
#define Renew(ptr, n, type) ((ptr) = (type*)realloc((ptr), (size_t)((n) * sizeof(type))))
#define Newx(ptr, n, type) ((ptr) = (type*)malloc((size_t)((n) * sizeof(type))))
#define Safefree(ptr) ((ptr) ? (void)free((ptr)), (ptr) = NULL : (void)0)
#define PerlDir_open(dir) opendir(dir)
#define PerlLIO_stat(file, stat_info) stat(file, stat_info)

// Functions defined in perl.h
// [TODO]Must support Unicode folding in the future
#define toFOLD(ch) tolower((unsigned char)(ch))

// Functions defined in perl.h
// [TODO]Must support real symbolic link check in the future
#if defined(_WIN32)
  #undef S_ISLNK
  #define S_ISLNK(mode) (0)
#endif

// Functions defined in perl.h
// [TODO]Must support Unicode folding in the future
#define toFOLD(ch) tolower((unsigned char)(ch))

/* #include <sys/cdefs.h> */

typedef struct {
        int gl_pathc;		/* Count of total paths so far. */
        int gl_matchc;		/* Count of paths matching pattern. */
        int gl_offs;		/* Reserved at beginning of gl_pathv. */
        int gl_flags;		/* Copy of flags parameter to glob. */
        char **gl_pathv;	/* List of paths matching pattern. */
                                /* Copy of errfunc parameter to glob. */
        int (*gl_errfunc)(const char *, int);

        /*
         * Alternate filesystem access methods for glob; replacement
         * versions of closedir(3), readdir(3), opendir(3), stat(2)
         * and lstat(2).
         */
        void (*gl_closedir)(void *);
        Direntry_t *(*gl_readdir)(void *); 
        void *(*gl_opendir)(const char *);
        int (*gl_lstat)(const char *, Stat_t *);
        int (*gl_stat)(const char *, Stat_t *);
} glob_t;

#define GLOB_APPEND     0x0001  /* Append to output from previous call. */
#define GLOB_DOOFFS     0x0002  /* Use gl_offs. */
#define GLOB_ERR        0x0004  /* Return on error. */
#define GLOB_MARK       0x0008  /* Append / to matching directories. */
#define GLOB_NOCHECK    0x0010  /* Return pattern itself if nothing matches. */
#define GLOB_NOSORT     0x0020  /* Don't sort. */

#define GLOB_ALTDIRFUNC 0x0040  /* Use alternately specified directory funcs. */
#define GLOB_BRACE      0x0080  /* Expand braces ala csh. */
#define GLOB_MAGCHAR    0x0100  /* Pattern had globbing characters. */
#define GLOB_NOMAGIC    0x0200  /* GLOB_NOCHECK without magic chars (csh). */
#define GLOB_QUOTE      0x0400  /* Quote special chars with \. */
#define GLOB_TILDE      0x0800  /* Expand tilde names from the passwd file. */
#define GLOB_NOCASE     0x1000  /* Treat filenames without regard for case. */
#define GLOB_ALPHASORT  0x2000  /* Alphabetic, not ASCII sort, like csh. */
#define GLOB_LIMIT      0x4000  /* Limit pattern match output to ARG_MAX
                                   (usually from limits.h). */

#define GLOB_NOSPACE    (-1)    /* Malloc call failed. */
#define GLOB_ABEND      (-2)    /* Unignored error. */

int	bsd_glob(const char *, int, int (*)(const char *, int), glob_t *);
void	bsd_globfree(glob_t *);

#endif // SPVM__SYS__IO__GLOB__GLOB_H
