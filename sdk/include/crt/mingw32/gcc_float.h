/* Copyright (C) 2002 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

/* As a special exception, if you include this header file into source
   files compiled by GCC, this header file does not by itself cause
   the resulting executable to be covered by the GNU General Public
   License.  This exception does not however invalidate any other
   reasons why the executable file might be covered by the GNU General
   Public License.  */

/*
 * ISO C Standard:  5.2.4.2.2  Characteristics of floating types <float.h>
 */

#ifndef _FLOAT_H___
#define _FLOAT_H___


/* Maximum representable finite floating-point number,

	(1 - b**-p) * b**emax
*/
#undef LDBL_MAX
#define LDBL_MAX	__LDBL_MAX__

/* The difference between 1 and the least value greater than 1 that is
   representable in the given floating point type, b**1-p.  */
#undef LDBL_EPSILON
#define LDBL_EPSILON	__LDBL_EPSILON__

/* Addition rounds to 0: zero, 1: nearest, 2: +inf, 3: -inf, -1: unknown.  */
/* ??? This is supposed to change with calls to fesetround in <fenv.h>.  */
#undef FLT_ROUNDS
#define FLT_ROUNDS 1

#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* The floating-point expression evaluation method.
        -1  indeterminate
         0  evaluate all operations and constants just to the range and
            precision of the type
         1  evaluate operations and constants of type float and double
            to the range and precision of the double type, evaluate
            long double operations and constants to the range and
            precision of the long double type
         2  evaluate all operations and constants to the range and
            precision of the long double type

   ??? This ought to change with the setting of the fp control word;
   the value provided by the compiler assumes the widest setting.  */
#undef FLT_EVAL_METHOD
#define FLT_EVAL_METHOD	__FLT_EVAL_METHOD__


#endif /* C99 */
#endif /* _FLOAT_H___ */
