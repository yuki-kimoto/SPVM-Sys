// Copyright (c) 2023 Yuki Kimoto
// MIT License

// This code is originally copied from the File::Glob module of Perl.

#ifndef _COMPAT_GLOB_H_
#define	_COMPAT_GLOB_H_

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

#include "SPVM__Sys__IO__Glob__charclass.h"

#include "spvm_native.h"

# define glob_t _ssh_compat_glob_t
# define glob(env, stack, a, b, c, d)  _ssh__compat_glob(env, stack, a, b, c, d)
# define globfree(a)  _ssh__compat_globfree(a)

struct stat;
typedef struct {
	size_t gl_pathc;	/* Count of total paths so far. */
	size_t gl_matchc;	/* Count of paths matching pattern. */
	size_t gl_offs;		/* Reserved at beginning of gl_pathv. */
	int gl_flags;		/* Copy of flags parameter to glob. */
	char **gl_pathv;	/* List of paths matching pattern. */
	struct stat **gl_statv;	/* Stat entries corresponding to gl_pathv */
				/* Copy of errfunc parameter to glob. */
	int (*gl_errfunc)(SPVM_ENV* env, SPVM_VALUE* stack, const char *, int);

	/*
	 * Alternate filesystem access methods for glob; replacement
	 * versions of closedir(3), readdir(3), opendir(3), stat(2)
	 * and lstat(2).
	 */
	void (*gl_closedir)(SPVM_ENV* env, SPVM_VALUE* stack, void *);
	struct dirent *(*gl_readdir)(SPVM_ENV* env, SPVM_VALUE* stack, void *);	
	void *(*gl_opendir)(SPVM_ENV* env, SPVM_VALUE* stack, const char *);
	int (*gl_lstat)(SPVM_ENV* env, SPVM_VALUE* stack, const char *, struct stat *);
	int (*gl_stat)(SPVM_ENV* env, SPVM_VALUE* stack, const char *, struct stat *);
} glob_t;

#define	GLOB_APPEND	0x0001	/* Append to output from previous call. */
#define	GLOB_DOOFFS	0x0002	/* Use gl_offs. */
#define	GLOB_ERR	0x0004	/* Return on error. */
#define	GLOB_MARK	0x0008	/* Append / to matching directories. */
#define	GLOB_NOCHECK	0x0010	/* Return pattern itself if nothing matches. */
#define	GLOB_NOSORT	0x0020	/* Don't sort. */
#define	GLOB_NOESCAPE	0x1000	/* Disable backslash escaping. */

#define	GLOB_NOSPACE	(-1)	/* Malloc call failed. */
#define	GLOB_ABORTED	(-2)	/* Unignored error. */
#define	GLOB_NOMATCH	(-3)	/* No match and GLOB_NOCHECK not set. */
#define	GLOB_NOSYS	(-4)	/* Function not supported. */

#define	GLOB_ALTDIRFUNC	0x0040	/* Use alternately specified directory funcs. */
#define	GLOB_BRACE	0x0080	/* Expand braces ala csh. */
#define	GLOB_MAGCHAR	0x0100	/* Pattern had globbing characters. */
#define	GLOB_NOMAGIC	0x0200	/* GLOB_NOCHECK without magic chars (csh). */
#define	GLOB_QUOTE	0x0400	/* Quote special chars with \. */
#define	GLOB_TILDE	0x0800	/* Expand tilde names from the passwd file. */
#define GLOB_LIMIT	0x2000	/* Limit pattern match output to ARG_MAX */
#define	GLOB_KEEPSTAT	0x4000	/* Retain stat data for paths in gl_statv. */
#define GLOB_ABEND	GLOB_ABORTED /* backward compatibility */

int	glob(SPVM_ENV* env, SPVM_VALUE* stack, const char *, int, int (*)(SPVM_ENV* env, SPVM_VALUE* stack, const char *, int), glob_t *);
void	globfree(glob_t *);

#endif
