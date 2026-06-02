// Copyright (c) 2023 Yuki Kimoto
// MIT License

// Originally copied from https://github.com/Perl/perl5/blob/v5.42.2/ext/File-Glob/bsd_glob.h

#ifndef SPVM_SYS_IO_GLOB_H
#define SPVM_SYS_IO_GLOB_H

#include <stdint.h>

typedef struct {
  int32_t gl_pathc;   /* Count of total paths so far. */
  int32_t gl_matchc;    /* Count of paths matching pattern. */
  int32_t gl_offs;    /* Reserved at beginning of gl_pathv. */
  int32_t gl_flags;   /* Copy of flags parameter to glob. */
  char **gl_pathv;  /* List of paths matching pattern. */
                          /* Copy of errfunc parameter to glob. */
} SPVM_SYS_IO_GLOB;

enum {
  SPVM_SYS_IO_GLOB_C_APPEND    = 0x0001,  /* Append to output from previous call. */
  SPVM_SYS_IO_GLOB_C_DOOFFS    = 0x0002,  /* Use gl_offs. */
  SPVM_SYS_IO_GLOB_C_ERR       = 0x0004,  /* Return on error. */
  SPVM_SYS_IO_GLOB_C_MARK      = 0x0008,  /* Append / to matching directories. */
  SPVM_SYS_IO_GLOB_C_NOCHECK   = 0x0010,  /* Return pattern itself if nothing matches. */
  SPVM_SYS_IO_GLOB_C_NOSORT    = 0x0020,  /* Don't sort. */
  SPVM_SYS_IO_GLOB_C_ALTDIRFUNC= 0x0040,  /* Use alternately specified directory funcs. */
  SPVM_SYS_IO_GLOB_C_BRACE     = 0x0080,  /* Expand braces ala csh. */
  SPVM_SYS_IO_GLOB_C_MAGCHAR   = 0x0100,  /* Pattern had globbing characters. */
  SPVM_SYS_IO_GLOB_C_NOMAGIC   = 0x0200,  /* GLOB_NOCHECK without magic chars (csh). */
  SPVM_SYS_IO_GLOB_C_QUOTE     = 0x0400,  /* Quote special chars with \. */
  SPVM_SYS_IO_GLOB_C_TILDE     = 0x0800,  /* Expand tilde names from the passwd file. */
  SPVM_SYS_IO_GLOB_C_NOCASE    = 0x1000,  /* Treat filenames without regard for case. */
  SPVM_SYS_IO_GLOB_C_ALPHASORT = 0x2000,  /* Alphabetic, not ASCII sort, like csh. */
  SPVM_SYS_IO_GLOB_C_LIMIT     = 0x4000,  /* Limit pattern match output to ARG_MAX. */
  SPVM_SYS_IO_GLOB_C_NOSPACE   = -1,      /* Malloc call failed. */
  SPVM_SYS_IO_GLOB_C_ABEND     = -2       /* Unignored error. */
};

int32_t spvm_sys_io_glob_bsd_glob(const char* pattern, int32_t flags, SPVM_SYS_IO_GLOB* pglob);
void spvm_sys_io_glob_bsd_globfree(SPVM_SYS_IO_GLOB* pglob);

#endif // SPVM_SYS_IO_GLOB_H
