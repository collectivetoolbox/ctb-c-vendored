// Provenance source: llvm/clang/lib/Headers/stdint.h sha256=5e0ab094f39830fafd0ecde083d329c423378ff325142a52700b17773977f6c3
// /*===---- stdint.h - Standard header for sized integer types --------------===*\
//  *
//  * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
//  * See https://llvm.org/LICENSE.txt for license information.
//  * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//  *
// \*===----------------------------------------------------------------------===*/
// 
// #ifndef __CLANG_STDINT_H
// // AIX system headers need stdint.h to be re-enterable while _STD_TYPES_T
// // is defined until an inclusion of it without _STD_TYPES_T occurs, in which
// // case the header guard macro is defined.
// #if !defined(_AIX) || !defined(_STD_TYPES_T) || !defined(__STDC_HOSTED__)
// #define __CLANG_STDINT_H
// #endif
// 
// #if defined(__MVS__) && __has_include_next(<stdint.h>)
// #include_next <stdint.h>
// #else
// 
// /* If we're hosted, fall back to the system's stdint.h, which might have
//  * additional definitions.
//  */
// #if __STDC_HOSTED__ && __has_include_next(<stdint.h>)
// 
// // C99 7.18.3 Limits of other integer types
// //
// //  Footnote 219, 220: C++ implementations should define these macros only when
// //  __STDC_LIMIT_MACROS is defined before <stdint.h> is included.
// //
// //  Footnote 222: C++ implementations should define these macros only when
// //  __STDC_CONSTANT_MACROS is defined before <stdint.h> is included.
// //
// // C++11 [cstdint.syn]p2:
// //
// //  The macros defined by <cstdint> are provided unconditionally. In particular,
// //  the symbols __STDC_LIMIT_MACROS and __STDC_CONSTANT_MACROS (mentioned in
// //  footnotes 219, 220, and 222 in the C standard) play no role in C++.
// //
// // C11 removed the problematic footnotes.
// //
// // Work around this inconsistency by always defining those macros in C++ mode,
// // so that a C library implementation which follows the C99 standard can be
// // used in C++.
// # ifdef __cplusplus
// #  if !defined(__STDC_LIMIT_MACROS)
// #   define __STDC_LIMIT_MACROS
// #   define __STDC_LIMIT_MACROS_DEFINED_BY_CLANG
// #  endif
// #  if !defined(__STDC_CONSTANT_MACROS)
// #   define __STDC_CONSTANT_MACROS
// #   define __STDC_CONSTANT_MACROS_DEFINED_BY_CLANG
// #  endif
// # endif
// 
// # include_next <stdint.h>
// 
// # ifdef __STDC_LIMIT_MACROS_DEFINED_BY_CLANG
// #  undef __STDC_LIMIT_MACROS
// #  undef __STDC_LIMIT_MACROS_DEFINED_BY_CLANG
// # endif
// # ifdef __STDC_CONSTANT_MACROS_DEFINED_BY_CLANG
// #  undef __STDC_CONSTANT_MACROS
// #  undef __STDC_CONSTANT_MACROS_DEFINED_BY_CLANG
// # endif
// 
// #else
// 
// /* C99 7.18.1.1 Exact-width integer types.
//  * C99 7.18.1.2 Minimum-width integer types.
//  * C99 7.18.1.3 Fastest minimum-width integer types.
//  *
//  * The standard requires that exact-width type be defined for 8-, 16-, 32-, and
//  * 64-bit types if they are implemented. Other exact width types are optional.
//  * This implementation defines an exact-width types for every integer width
//  * that is represented in the standard integer types.
//  *
//  * The standard also requires minimum-width types be defined for 8-, 16-, 32-,
//  * and 64-bit widths regardless of whether there are corresponding exact-width
//  * types.
//  *
//  * To accommodate targets that are missing types that are exactly 8, 16, 32, or
//  * 64 bits wide, this implementation takes an approach of cascading
//  * redefinitions, redefining __int_leastN_t to successively smaller exact-width
//  * types. It is therefore important that the types are defined in order of
//  * descending widths.
//  *
//  * We currently assume that the minimum-width types and the fastest
//  * minimum-width types are the same. This is allowed by the standard, but is
//  * suboptimal.
//  *
//  * In violation of the standard, some targets do not implement a type that is
//  * wide enough to represent all of the required widths (8-, 16-, 32-, 64-bit).
//  * To accommodate these targets, a required minimum-width type is only
//  * defined if there exists an exact-width type of equal or greater width.
//  */
// 
// #ifdef __INT64_TYPE__
// # ifndef __int8_t_defined /* glibc sys/types.h also defines int64_t*/
// typedef __INT64_TYPE__ int64_t;
// # endif /* __int8_t_defined */
// typedef __UINT64_TYPE__ uint64_t;
// # undef __int_least64_t
// # define __int_least64_t int64_t
// # undef __uint_least64_t
// # define __uint_least64_t uint64_t
// # undef __int_least32_t
// # define __int_least32_t int64_t
// # undef __uint_least32_t
// # define __uint_least32_t uint64_t
// # undef __int_least16_t
// # define __int_least16_t int64_t
// # undef __uint_least16_t
// # define __uint_least16_t uint64_t
// # undef __int_least8_t
// # define __int_least8_t int64_t
// # undef __uint_least8_t
// # define __uint_least8_t uint64_t
// #endif /* __INT64_TYPE__ */
// 
// #ifdef __int_least64_t
// typedef __int_least64_t int_least64_t;
// typedef __uint_least64_t uint_least64_t;
// typedef __int_least64_t int_fast64_t;
// typedef __uint_least64_t uint_fast64_t;
// #endif /* __int_least64_t */
// 
// #ifdef __INT56_TYPE__
// typedef __INT56_TYPE__ int56_t;
// typedef __UINT56_TYPE__ uint56_t;
// typedef int56_t int_least56_t;
// typedef uint56_t uint_least56_t;
// typedef int56_t int_fast56_t;
// typedef uint56_t uint_fast56_t;
// # undef __int_least32_t
// # define __int_least32_t int56_t
// # undef __uint_least32_t
// # define __uint_least32_t uint56_t
// # undef __int_least16_t
// # define __int_least16_t int56_t
// # undef __uint_least16_t
// # define __uint_least16_t uint56_t
// # undef __int_least8_t
// # define __int_least8_t int56_t
// # undef __uint_least8_t
// # define __uint_least8_t uint56_t
// #endif /* __INT56_TYPE__ */
// 
// 
// #ifdef __INT48_TYPE__
// typedef __INT48_TYPE__ int48_t;
// typedef __UINT48_TYPE__ uint48_t;
// typedef int48_t int_least48_t;
// typedef uint48_t uint_least48_t;
// typedef int48_t int_fast48_t;
// typedef uint48_t uint_fast48_t;
// # undef __int_least32_t
// # define __int_least32_t int48_t
// # undef __uint_least32_t
// # define __uint_least32_t uint48_t
// # undef __int_least16_t
// # define __int_least16_t int48_t
// # undef __uint_least16_t
// # define __uint_least16_t uint48_t
// # undef __int_least8_t
// # define __int_least8_t int48_t
// # undef __uint_least8_t
// # define __uint_least8_t uint48_t
// #endif /* __INT48_TYPE__ */
// 
// 
// #ifdef __INT40_TYPE__
// typedef __INT40_TYPE__ int40_t;
// typedef __UINT40_TYPE__ uint40_t;
// typedef int40_t int_least40_t;
// typedef uint40_t uint_least40_t;
// typedef int40_t int_fast40_t;
// typedef uint40_t uint_fast40_t;
// # undef __int_least32_t
// # define __int_least32_t int40_t
// # undef __uint_least32_t
// # define __uint_least32_t uint40_t
// # undef __int_least16_t
// # define __int_least16_t int40_t
// # undef __uint_least16_t
// # define __uint_least16_t uint40_t
// # undef __int_least8_t
// # define __int_least8_t int40_t
// # undef __uint_least8_t
// # define __uint_least8_t uint40_t
// #endif /* __INT40_TYPE__ */
// 
// 
// #ifdef __INT32_TYPE__
// 
// # ifndef __int8_t_defined /* glibc sys/types.h also defines int32_t*/
// typedef __INT32_TYPE__ int32_t;
// # endif /* __int8_t_defined */
// 
// # ifndef __uint32_t_defined  /* more glibc compatibility */
// # define __uint32_t_defined
// typedef __UINT32_TYPE__ uint32_t;
// # endif /* __uint32_t_defined */
// 
// # undef __int_least32_t
// # define __int_least32_t int32_t
// # undef __uint_least32_t
// # define __uint_least32_t uint32_t
// # undef __int_least16_t
// # define __int_least16_t int32_t
// # undef __uint_least16_t
// # define __uint_least16_t uint32_t
// # undef __int_least8_t
// # define __int_least8_t int32_t
// # undef __uint_least8_t
// # define __uint_least8_t uint32_t
// #endif /* __INT32_TYPE__ */
// 
// #ifdef __int_least32_t
// typedef __int_least32_t int_least32_t;
// typedef __uint_least32_t uint_least32_t;
// typedef __int_least32_t int_fast32_t;
// typedef __uint_least32_t uint_fast32_t;
// #endif /* __int_least32_t */
// 
// #ifdef __INT24_TYPE__
// typedef __INT24_TYPE__ int24_t;
// typedef __UINT24_TYPE__ uint24_t;
// typedef int24_t int_least24_t;
// typedef uint24_t uint_least24_t;
// typedef int24_t int_fast24_t;
// typedef uint24_t uint_fast24_t;
// # undef __int_least16_t
// # define __int_least16_t int24_t
// # undef __uint_least16_t
// # define __uint_least16_t uint24_t
// # undef __int_least8_t
// # define __int_least8_t int24_t
// # undef __uint_least8_t
// # define __uint_least8_t uint24_t
// #endif /* __INT24_TYPE__ */
// 
// #ifdef __INT16_TYPE__
// #ifndef __int8_t_defined /* glibc sys/types.h also defines int16_t*/
// typedef __INT16_TYPE__ int16_t;
// #endif /* __int8_t_defined */
// typedef __UINT16_TYPE__ uint16_t;
// # undef __int_least16_t
// # define __int_least16_t int16_t
// # undef __uint_least16_t
// # define __uint_least16_t uint16_t
// # undef __int_least8_t
// # define __int_least8_t int16_t
// # undef __uint_least8_t
// # define __uint_least8_t uint16_t
// #endif /* __INT16_TYPE__ */
// 
// #ifdef __int_least16_t
// typedef __int_least16_t int_least16_t;
// typedef __uint_least16_t uint_least16_t;
// typedef __int_least16_t int_fast16_t;
// typedef __uint_least16_t uint_fast16_t;
// #endif /* __int_least16_t */
// 
// 
// #ifdef __INT8_TYPE__
// #ifndef __int8_t_defined  /* glibc sys/types.h also defines int8_t*/
// typedef __INT8_TYPE__ int8_t;
// #endif /* __int8_t_defined */
// typedef __UINT8_TYPE__ uint8_t;
// # undef __int_least8_t
// # define __int_least8_t int8_t
// # undef __uint_least8_t
// # define __uint_least8_t uint8_t
// #endif /* __INT8_TYPE__ */
// 
// #ifdef __int_least8_t
// typedef __int_least8_t int_least8_t;
// typedef __uint_least8_t uint_least8_t;
// typedef __int_least8_t int_fast8_t;
// typedef __uint_least8_t uint_fast8_t;
// #endif /* __int_least8_t */
// 
// /* prevent glibc sys/types.h from defining conflicting types */
// #ifndef __int8_t_defined
// # define __int8_t_defined
// #endif /* __int8_t_defined */
// 
// /* C99 7.18.1.4 Integer types capable of holding object pointers.
//  */
// #define __stdint_join3(a,b,c) a ## b ## c
// 
// #ifndef _INTPTR_T
// #ifndef __intptr_t_defined
// typedef __INTPTR_TYPE__ intptr_t;
// #define __intptr_t_defined
// #define _INTPTR_T
// #endif
// #endif
// 
// #ifndef _UINTPTR_T
// typedef __UINTPTR_TYPE__ uintptr_t;
// #define _UINTPTR_T
// #endif
// 
// /* C99 7.18.1.5 Greatest-width integer types.
//  */
// typedef __INTMAX_TYPE__  intmax_t;
// typedef __UINTMAX_TYPE__ uintmax_t;
// 
// /* C99 7.18.4 Macros for minimum-width integer constants.
//  *
//  * The standard requires that integer constant macros be defined for all the
//  * minimum-width types defined above. As 8-, 16-, 32-, and 64-bit minimum-width
//  * types are required, the corresponding integer constant macros are defined
//  * here. This implementation also defines minimum-width types for every other
//  * integer width that the target implements, so corresponding macros are
//  * defined below, too.
//  *
//  * Note that C++ should not check __STDC_CONSTANT_MACROS here, contrary to the
//  * claims of the C standard (see C++ 18.3.1p2, [cstdint.syn]).
//  */
// 
// #ifdef __int_least64_t
// #define INT64_C(v) __INT64_C(v)
// #define UINT64_C(v) __UINT64_C(v)
// #endif /* __int_least64_t */
// 
// 
// #ifdef __INT56_TYPE__
// #define INT56_C(v) __INT56_C(v)
// #define UINT56_C(v) __UINT56_C(v)
// #endif /* __INT56_TYPE__ */
// 
// 
// #ifdef __INT48_TYPE__
// #define INT48_C(v) __INT48_C(v)
// #define UINT48_C(v) __UINT48_C(v)
// #endif /* __INT48_TYPE__ */
// 
// 
// #ifdef __INT40_TYPE__
// #define INT40_C(v) __INT40_C(v)
// #define UINT40_C(v) __UINT40_C(v)
// #endif /* __INT40_TYPE__ */
// 
// 
// #ifdef __int_least32_t
// #define INT32_C(v) __INT32_C(v)
// #define UINT32_C(v) __UINT32_C(v)
// #endif /* __int_least32_t */
// 
// 
// #ifdef __INT24_TYPE__
// #define INT24_C(v) __INT24_C(v)
// #define UINT24_C(v) __UINT24_C(v)
// #endif /* __INT24_TYPE__ */
// 
// 
// #ifdef __int_least16_t
// #define INT16_C(v) __INT16_C(v)
// #define UINT16_C(v) __UINT16_C(v)
// #endif /* __int_least16_t */
// 
// 
// #ifdef __int_least8_t
// #define INT8_C(v) __INT8_C(v)
// #define UINT8_C(v) __UINT8_C(v)
// #endif /* __int_least8_t */
// 
// 
// /* C99 7.18.2.1 Limits of exact-width integer types.
//  * C99 7.18.2.2 Limits of minimum-width integer types.
//  * C99 7.18.2.3 Limits of fastest minimum-width integer types.
//  *
//  * The presence of limit macros are completely optional in C99.  This
//  * implementation defines limits for all of the types (exact- and
//  * minimum-width) that it defines above, using the limits of the minimum-width
//  * type for any types that do not have exact-width representations.
//  *
//  * As in the type definitions, this section takes an approach of
//  * successive-shrinking to determine which limits to use for the standard (8,
//  * 16, 32, 64) bit widths when they don't have exact representations. It is
//  * therefore important that the definitions be kept in order of decending
//  * widths.
//  *
//  * Note that C++ should not check __STDC_LIMIT_MACROS here, contrary to the
//  * claims of the C standard (see C++ 18.3.1p2, [cstdint.syn]).
//  */
// 
// #ifdef __INT64_TYPE__
// # define INT64_MAX           INT64_C( 9223372036854775807)
// # define INT64_MIN         (-INT64_C( 9223372036854775807)-1)
// # define UINT64_MAX         UINT64_C(18446744073709551615)
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT64_WIDTH         64
// # define INT64_WIDTH          UINT64_WIDTH
// 
// # define __UINT_LEAST64_WIDTH UINT64_WIDTH
// # undef __UINT_LEAST32_WIDTH
// # define __UINT_LEAST32_WIDTH UINT64_WIDTH
// # undef __UINT_LEAST16_WIDTH
// # define __UINT_LEAST16_WIDTH UINT64_WIDTH
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX UINT64_MAX
// #endif /* __STDC_VERSION__ */
// 
// # define __INT_LEAST64_MIN   INT64_MIN
// # define __INT_LEAST64_MAX   INT64_MAX
// # define __UINT_LEAST64_MAX UINT64_MAX
// # undef __INT_LEAST32_MIN
// # define __INT_LEAST32_MIN   INT64_MIN
// # undef __INT_LEAST32_MAX
// # define __INT_LEAST32_MAX   INT64_MAX
// # undef __UINT_LEAST32_MAX
// # define __UINT_LEAST32_MAX UINT64_MAX
// # undef __INT_LEAST16_MIN
// # define __INT_LEAST16_MIN   INT64_MIN
// # undef __INT_LEAST16_MAX
// # define __INT_LEAST16_MAX   INT64_MAX
// # undef __UINT_LEAST16_MAX
// # define __UINT_LEAST16_MAX UINT64_MAX
// # undef __INT_LEAST8_MIN
// # define __INT_LEAST8_MIN    INT64_MIN
// # undef __INT_LEAST8_MAX
// # define __INT_LEAST8_MAX    INT64_MAX
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX  UINT64_MAX
// #endif /* __INT64_TYPE__ */
// 
// #ifdef __INT_LEAST64_MIN
// # define INT_LEAST64_MIN   __INT_LEAST64_MIN
// # define INT_LEAST64_MAX   __INT_LEAST64_MAX
// # define UINT_LEAST64_MAX __UINT_LEAST64_MAX
// # define INT_FAST64_MIN    __INT_LEAST64_MIN
// # define INT_FAST64_MAX    __INT_LEAST64_MAX
// # define UINT_FAST64_MAX  __UINT_LEAST64_MAX
// 
// #if defined(__STDC_VERSION__) &&  __STDC_VERSION__ >= 202311L
// # define UINT_LEAST64_WIDTH __UINT_LEAST64_WIDTH
// # define INT_LEAST64_WIDTH  UINT_LEAST64_WIDTH
// # define UINT_FAST64_WIDTH  __UINT_LEAST64_WIDTH
// # define INT_FAST64_WIDTH   UINT_FAST64_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT_LEAST64_MIN */
// 
// 
// #ifdef __INT56_TYPE__
// # define INT56_MAX           INT56_C(36028797018963967)
// # define INT56_MIN         (-INT56_C(36028797018963967)-1)
// # define UINT56_MAX         UINT56_C(72057594037927935)
// # define INT_LEAST56_MIN     INT56_MIN
// # define INT_LEAST56_MAX     INT56_MAX
// # define UINT_LEAST56_MAX   UINT56_MAX
// # define INT_FAST56_MIN      INT56_MIN
// # define INT_FAST56_MAX      INT56_MAX
// # define UINT_FAST56_MAX    UINT56_MAX
// 
// # undef __INT_LEAST32_MIN
// # define __INT_LEAST32_MIN   INT56_MIN
// # undef __INT_LEAST32_MAX
// # define __INT_LEAST32_MAX   INT56_MAX
// # undef __UINT_LEAST32_MAX
// # define __UINT_LEAST32_MAX UINT56_MAX
// # undef __INT_LEAST16_MIN
// # define __INT_LEAST16_MIN   INT56_MIN
// # undef __INT_LEAST16_MAX
// # define __INT_LEAST16_MAX   INT56_MAX
// # undef __UINT_LEAST16_MAX
// # define __UINT_LEAST16_MAX UINT56_MAX
// # undef __INT_LEAST8_MIN
// # define __INT_LEAST8_MIN    INT56_MIN
// # undef __INT_LEAST8_MAX
// # define __INT_LEAST8_MAX    INT56_MAX
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX  UINT56_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT56_WIDTH         56
// # define INT56_WIDTH          UINT56_WIDTH
// # define UINT_LEAST56_WIDTH   UINT56_WIDTH
// # define INT_LEAST56_WIDTH    UINT_LEAST56_WIDTH
// # define UINT_FAST56_WIDTH    UINT56_WIDTH
// # define INT_FAST56_WIDTH     UINT_FAST56_WIDTH
// # undef __UINT_LEAST32_WIDTH
// # define __UINT_LEAST32_WIDTH UINT56_WIDTH
// # undef __UINT_LEAST16_WIDTH
// # define __UINT_LEAST16_WIDTH UINT56_WIDTH
// # undef __UINT_LEAST8_WIDTH
// # define __UINT_LEAST8_WIDTH  UINT56_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT56_TYPE__ */
// 
// 
// #ifdef __INT48_TYPE__
// # define INT48_MAX           INT48_C(140737488355327)
// # define INT48_MIN         (-INT48_C(140737488355327)-1)
// # define UINT48_MAX         UINT48_C(281474976710655)
// # define INT_LEAST48_MIN     INT48_MIN
// # define INT_LEAST48_MAX     INT48_MAX
// # define UINT_LEAST48_MAX   UINT48_MAX
// # define INT_FAST48_MIN      INT48_MIN
// # define INT_FAST48_MAX      INT48_MAX
// # define UINT_FAST48_MAX    UINT48_MAX
// 
// # undef __INT_LEAST32_MIN
// # define __INT_LEAST32_MIN   INT48_MIN
// # undef __INT_LEAST32_MAX
// # define __INT_LEAST32_MAX   INT48_MAX
// # undef __UINT_LEAST32_MAX
// # define __UINT_LEAST32_MAX UINT48_MAX
// # undef __INT_LEAST16_MIN
// # define __INT_LEAST16_MIN   INT48_MIN
// # undef __INT_LEAST16_MAX
// # define __INT_LEAST16_MAX   INT48_MAX
// # undef __UINT_LEAST16_MAX
// # define __UINT_LEAST16_MAX UINT48_MAX
// # undef __INT_LEAST8_MIN
// # define __INT_LEAST8_MIN    INT48_MIN
// # undef __INT_LEAST8_MAX
// # define __INT_LEAST8_MAX    INT48_MAX
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX  UINT48_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// #define UINT48_WIDTH         48
// #define INT48_WIDTH          UINT48_WIDTH
// #define UINT_LEAST48_WIDTH   UINT48_WIDTH
// #define INT_LEAST48_WIDTH    UINT_LEAST48_WIDTH
// #define UINT_FAST48_WIDTH    UINT48_WIDTH
// #define INT_FAST48_WIDTH     UINT_FAST48_WIDTH
// #undef __UINT_LEAST32_WIDTH
// #define __UINT_LEAST32_WIDTH UINT48_WIDTH
// # undef __UINT_LEAST16_WIDTH
// #define __UINT_LEAST16_WIDTH UINT48_WIDTH
// # undef __UINT_LEAST8_WIDTH
// #define __UINT_LEAST8_WIDTH  UINT48_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT48_TYPE__ */
// 
// 
// #ifdef __INT40_TYPE__
// # define INT40_MAX           INT40_C(549755813887)
// # define INT40_MIN         (-INT40_C(549755813887)-1)
// # define UINT40_MAX         UINT40_C(1099511627775)
// # define INT_LEAST40_MIN     INT40_MIN
// # define INT_LEAST40_MAX     INT40_MAX
// # define UINT_LEAST40_MAX   UINT40_MAX
// # define INT_FAST40_MIN      INT40_MIN
// # define INT_FAST40_MAX      INT40_MAX
// # define UINT_FAST40_MAX    UINT40_MAX
// 
// # undef __INT_LEAST32_MIN
// # define __INT_LEAST32_MIN   INT40_MIN
// # undef __INT_LEAST32_MAX
// # define __INT_LEAST32_MAX   INT40_MAX
// # undef __UINT_LEAST32_MAX
// # define __UINT_LEAST32_MAX UINT40_MAX
// # undef __INT_LEAST16_MIN
// # define __INT_LEAST16_MIN   INT40_MIN
// # undef __INT_LEAST16_MAX
// # define __INT_LEAST16_MAX   INT40_MAX
// # undef __UINT_LEAST16_MAX
// # define __UINT_LEAST16_MAX UINT40_MAX
// # undef __INT_LEAST8_MIN
// # define __INT_LEAST8_MIN    INT40_MIN
// # undef __INT_LEAST8_MAX
// # define __INT_LEAST8_MAX    INT40_MAX
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX  UINT40_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT40_WIDTH         40
// # define INT40_WIDTH          UINT40_WIDTH
// # define UINT_LEAST40_WIDTH   UINT40_WIDTH
// # define INT_LEAST40_WIDTH    UINT_LEAST40_WIDTH
// # define UINT_FAST40_WIDTH    UINT40_WIDTH
// # define INT_FAST40_WIDTH     UINT_FAST40_WIDTH
// # undef __UINT_LEAST32_WIDTH
// # define __UINT_LEAST32_WIDTH UINT40_WIDTH
// # undef __UINT_LEAST16_WIDTH
// # define __UINT_LEAST16_WIDTH UINT40_WIDTH
// # undef __UINT_LEAST8_WIDTH
// # define __UINT_LEAST8_WIDTH  UINT40_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT40_TYPE__ */
// 
// 
// #ifdef __INT32_TYPE__
// # define INT32_MAX           INT32_C(2147483647)
// # define INT32_MIN         (-INT32_C(2147483647)-1)
// # define UINT32_MAX         UINT32_C(4294967295)
// 
// # undef __INT_LEAST32_MIN
// # define __INT_LEAST32_MIN   INT32_MIN
// # undef __INT_LEAST32_MAX
// # define __INT_LEAST32_MAX   INT32_MAX
// # undef __UINT_LEAST32_MAX
// # define __UINT_LEAST32_MAX UINT32_MAX
// # undef __INT_LEAST16_MIN
// # define __INT_LEAST16_MIN   INT32_MIN
// # undef __INT_LEAST16_MAX
// # define __INT_LEAST16_MAX   INT32_MAX
// # undef __UINT_LEAST16_MAX
// # define __UINT_LEAST16_MAX UINT32_MAX
// # undef __INT_LEAST8_MIN
// # define __INT_LEAST8_MIN    INT32_MIN
// # undef __INT_LEAST8_MAX
// # define __INT_LEAST8_MAX    INT32_MAX
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX  UINT32_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT32_WIDTH         32
// # define INT32_WIDTH          UINT32_WIDTH
// # undef __UINT_LEAST32_WIDTH
// # define __UINT_LEAST32_WIDTH UINT32_WIDTH
// # undef __UINT_LEAST16_WIDTH
// # define __UINT_LEAST16_WIDTH UINT32_WIDTH
// # undef __UINT_LEAST8_WIDTH
// # define __UINT_LEAST8_WIDTH  UINT32_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT32_TYPE__ */
// 
// #ifdef __INT_LEAST32_MIN
// # define INT_LEAST32_MIN   __INT_LEAST32_MIN
// # define INT_LEAST32_MAX   __INT_LEAST32_MAX
// # define UINT_LEAST32_MAX __UINT_LEAST32_MAX
// # define INT_FAST32_MIN    __INT_LEAST32_MIN
// # define INT_FAST32_MAX    __INT_LEAST32_MAX
// # define UINT_FAST32_MAX  __UINT_LEAST32_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT_LEAST32_WIDTH __UINT_LEAST32_WIDTH
// # define INT_LEAST32_WIDTH  UINT_LEAST32_WIDTH
// # define UINT_FAST32_WIDTH  __UINT_LEAST32_WIDTH
// # define INT_FAST32_WIDTH   UINT_FAST32_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT_LEAST32_MIN */
// 
// 
// #ifdef __INT24_TYPE__
// # define INT24_MAX           INT24_C(8388607)
// # define INT24_MIN         (-INT24_C(8388607)-1)
// # define UINT24_MAX         UINT24_C(16777215)
// # define INT_LEAST24_MIN     INT24_MIN
// # define INT_LEAST24_MAX     INT24_MAX
// # define UINT_LEAST24_MAX   UINT24_MAX
// # define INT_FAST24_MIN      INT24_MIN
// # define INT_FAST24_MAX      INT24_MAX
// # define UINT_FAST24_MAX    UINT24_MAX
// 
// # undef __INT_LEAST16_MIN
// # define __INT_LEAST16_MIN   INT24_MIN
// # undef __INT_LEAST16_MAX
// # define __INT_LEAST16_MAX   INT24_MAX
// # undef __UINT_LEAST16_MAX
// # define __UINT_LEAST16_MAX UINT24_MAX
// # undef __INT_LEAST8_MIN
// # define __INT_LEAST8_MIN    INT24_MIN
// # undef __INT_LEAST8_MAX
// # define __INT_LEAST8_MAX    INT24_MAX
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX  UINT24_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT24_WIDTH         24
// # define INT24_WIDTH          UINT24_WIDTH
// # define UINT_LEAST24_WIDTH   UINT24_WIDTH
// # define INT_LEAST24_WIDTH    UINT_LEAST24_WIDTH
// # define UINT_FAST24_WIDTH    UINT24_WIDTH
// # define INT_FAST24_WIDTH     UINT_FAST24_WIDTH
// # undef __UINT_LEAST16_WIDTH
// # define __UINT_LEAST16_WIDTH UINT24_WIDTH
// # undef __UINT_LEAST8_WIDTH
// # define __UINT_LEAST8_WIDTH  UINT24_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT24_TYPE__ */
// 
// 
// #ifdef __INT16_TYPE__
// #define INT16_MAX            INT16_C(32767)
// #define INT16_MIN          (-INT16_C(32767)-1)
// #define UINT16_MAX          UINT16_C(65535)
// 
// # undef __INT_LEAST16_MIN
// # define __INT_LEAST16_MIN   INT16_MIN
// # undef __INT_LEAST16_MAX
// # define __INT_LEAST16_MAX   INT16_MAX
// # undef __UINT_LEAST16_MAX
// # define __UINT_LEAST16_MAX UINT16_MAX
// # undef __INT_LEAST8_MIN
// # define __INT_LEAST8_MIN    INT16_MIN
// # undef __INT_LEAST8_MAX
// # define __INT_LEAST8_MAX    INT16_MAX
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX  UINT16_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT16_WIDTH         16
// # define INT16_WIDTH          UINT16_WIDTH
// # undef __UINT_LEAST16_WIDTH
// # define __UINT_LEAST16_WIDTH UINT16_WIDTH
// # undef __UINT_LEAST8_WIDTH
// # define __UINT_LEAST8_WIDTH  UINT16_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT16_TYPE__ */
// 
// #ifdef __INT_LEAST16_MIN
// # define INT_LEAST16_MIN   __INT_LEAST16_MIN
// # define INT_LEAST16_MAX   __INT_LEAST16_MAX
// # define UINT_LEAST16_MAX __UINT_LEAST16_MAX
// # define INT_FAST16_MIN    __INT_LEAST16_MIN
// # define INT_FAST16_MAX    __INT_LEAST16_MAX
// # define UINT_FAST16_MAX  __UINT_LEAST16_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT_LEAST16_WIDTH __UINT_LEAST16_WIDTH
// # define INT_LEAST16_WIDTH  UINT_LEAST16_WIDTH
// # define UINT_FAST16_WIDTH  __UINT_LEAST16_WIDTH
// # define INT_FAST16_WIDTH   UINT_FAST16_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT_LEAST16_MIN */
// 
// 
// #ifdef __INT8_TYPE__
// # define INT8_MAX            INT8_C(127)
// # define INT8_MIN          (-INT8_C(127)-1)
// # define UINT8_MAX          UINT8_C(255)
// 
// # undef __INT_LEAST8_MIN
// # define __INT_LEAST8_MIN    INT8_MIN
// # undef __INT_LEAST8_MAX
// # define __INT_LEAST8_MAX    INT8_MAX
// # undef __UINT_LEAST8_MAX
// # define __UINT_LEAST8_MAX  UINT8_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT8_WIDTH         8
// # define INT8_WIDTH          UINT8_WIDTH
// # undef __UINT_LEAST8_WIDTH
// # define __UINT_LEAST8_WIDTH UINT8_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT8_TYPE__ */
// 
// #ifdef __INT_LEAST8_MIN
// # define INT_LEAST8_MIN   __INT_LEAST8_MIN
// # define INT_LEAST8_MAX   __INT_LEAST8_MAX
// # define UINT_LEAST8_MAX __UINT_LEAST8_MAX
// # define INT_FAST8_MIN    __INT_LEAST8_MIN
// # define INT_FAST8_MAX    __INT_LEAST8_MAX
// # define UINT_FAST8_MAX  __UINT_LEAST8_MAX
// 
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// # define UINT_LEAST8_WIDTH __UINT_LEAST8_WIDTH
// # define INT_LEAST8_WIDTH  UINT_LEAST8_WIDTH
// # define UINT_FAST8_WIDTH  __UINT_LEAST8_WIDTH
// # define INT_FAST8_WIDTH   UINT_FAST8_WIDTH
// #endif /* __STDC_VERSION__ */
// #endif /* __INT_LEAST8_MIN */
// 
// /* Some utility macros */
// #define  __INTN_MIN(n)  __stdint_join3( INT, n, _MIN)
// #define  __INTN_MAX(n)  __stdint_join3( INT, n, _MAX)
// #define __UINTN_MAX(n)  __stdint_join3(UINT, n, _MAX)
// #define  __INTN_C(n, v) __stdint_join3( INT, n, _C(v))
// #define __UINTN_C(n, v) __stdint_join3(UINT, n, _C(v))
// 
// /* C99 7.18.2.4 Limits of integer types capable of holding object pointers. */
// /* C99 7.18.3 Limits of other integer types. */
// 
// #define  INTPTR_MIN  (-__INTPTR_MAX__-1)
// #define  INTPTR_MAX    __INTPTR_MAX__
// #define UINTPTR_MAX   __UINTPTR_MAX__
// #define PTRDIFF_MIN (-__PTRDIFF_MAX__-1)
// #define PTRDIFF_MAX   __PTRDIFF_MAX__
// #define    SIZE_MAX      __SIZE_MAX__
// 
// /* C23 7.22.2.4 Width of integer types capable of holding object pointers. */
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// /* NB: The C standard requires that these be the same value, but the compiler
//    exposes separate internal width macros. */
// #define INTPTR_WIDTH  __INTPTR_WIDTH__
// #define UINTPTR_WIDTH __UINTPTR_WIDTH__
// #endif
// 
// /* ISO9899:2011 7.20 (C11 Annex K): Define RSIZE_MAX if __STDC_WANT_LIB_EXT1__
//  * is enabled. */
// #if defined(__STDC_WANT_LIB_EXT1__) && __STDC_WANT_LIB_EXT1__ >= 1
// #define   RSIZE_MAX            (SIZE_MAX >> 1)
// #endif
// 
// /* C99 7.18.2.5 Limits of greatest-width integer types. */
// #define  INTMAX_MIN (-__INTMAX_MAX__-1)
// #define  INTMAX_MAX   __INTMAX_MAX__
// #define UINTMAX_MAX  __UINTMAX_MAX__
// 
// /* C23 7.22.2.5 Width of greatest-width integer types. */
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// /* NB: The C standard requires that these be the same value, but the compiler
//    exposes separate internal width macros. */
// #define INTMAX_WIDTH __INTMAX_WIDTH__
// #define UINTMAX_WIDTH __UINTMAX_WIDTH__
// #endif
// 
// /* C99 7.18.3 Limits of other integer types. */
// #define SIG_ATOMIC_MIN __SIG_ATOMIC_MIN__
// #define SIG_ATOMIC_MAX __SIG_ATOMIC_MAX__
// #define WINT_MIN __WINT_MIN__
// #define WINT_MAX __WINT_MAX__
// 
// #ifndef WCHAR_MAX
// # define WCHAR_MAX __WCHAR_MAX__
// #endif
// #ifndef WCHAR_MIN
// #define WCHAR_MIN __WCHAR_MIN__
// #endif
// 
// /* 7.18.4.2 Macros for greatest-width integer constants. */
// #define  INTMAX_C(v) __INTMAX_C(v)
// #define UINTMAX_C(v) __UINTMAX_C(v)
// 
// /* C23 7.22.3.x Width of other integer types. */
// #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
// #define PTRDIFF_WIDTH    __PTRDIFF_WIDTH__
// #define SIG_ATOMIC_WIDTH __SIG_ATOMIC_WIDTH__
// #define SIZE_WIDTH       __SIZE_WIDTH__
// #define WCHAR_WIDTH      __WCHAR_WIDTH__
// #define WINT_WIDTH       __WINT_WIDTH__
// #endif
// 
// #endif /* __STDC_HOSTED__ */
// #endif /* __MVS__ */
// #endif /* __CLANG_STDINT_H */
// End provenance source

// Provenance source: freebsd/sys/sys/types.h sha256=e1dfee28c1a7ec6d7428e775e83ae3b44f0f9260b76812fb1372cdc63a834b01
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1982, 1986, 1991, 1993, 1994
//  *	The Regents of the University of California.  All rights reserved.
//  * (c) UNIX System Laboratories, Inc.
//  * All or some portions of this file are derived from material licensed
//  * to the University of California by American Telephone and Telegraph
//  * Co. or Unix System Laboratories, Inc. and are reproduced herein with
//  * the permission of UNIX System Laboratories, Inc.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the University nor the names of its contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  *
//  *	@(#)types.h	8.6 (Berkeley) 2/19/95
//  */
// 
// #ifndef _SYS_TYPES_H_
// #define	_SYS_TYPES_H_
// 
// #include <sys/cdefs.h>
// 
// /* Machine type dependent parameters. */
// #include <machine/endian.h>
// #include <sys/_types.h>
// 
// #include <sys/_pthreadtypes.h>
// 
// #if __BSD_VISIBLE
// typedef	unsigned char	u_char;
// typedef	unsigned short	u_short;
// typedef	unsigned int	u_int;
// typedef	unsigned long	u_long;
// #ifndef _KERNEL
// typedef	unsigned short	ushort;		/* Sys V compatibility */
// typedef	unsigned int	uint;		/* Sys V compatibility */
// #endif
// #endif
// 
// /*
//  * XXX POSIX sized integrals that should appear only in <sys/stdint.h>.
//  */
// #include <sys/_stdint.h>
// 
// typedef __uint8_t	u_int8_t;	/* unsigned integrals (deprecated) */
// typedef __uint16_t	u_int16_t;
// typedef __uint32_t	u_int32_t;
// typedef __uint64_t	u_int64_t;
// 
// typedef	__uint64_t	u_quad_t;	/* quads (deprecated) */
// typedef	__int64_t	quad_t;
// typedef	quad_t *	qaddr_t;
// 
// typedef	char *		caddr_t;	/* core address */
// typedef	const char *	c_caddr_t;	/* core address, pointer to const */
// 
// #ifndef _BLKSIZE_T_DECLARED
// typedef	__blksize_t	blksize_t;
// #define	_BLKSIZE_T_DECLARED
// #endif
// 
// typedef	__cpuwhich_t	cpuwhich_t;
// typedef	__cpulevel_t	cpulevel_t;
// typedef	__cpusetid_t	cpusetid_t;
// 
// #ifndef _BLKCNT_T_DECLARED
// typedef	__blkcnt_t	blkcnt_t;
// #define	_BLKCNT_T_DECLARED
// #endif
// 
// #ifndef _CLOCK_T_DECLARED
// typedef	__clock_t	clock_t;
// #define	_CLOCK_T_DECLARED
// #endif
// 
// #ifndef _CLOCKID_T_DECLARED
// typedef	__clockid_t	clockid_t;
// #define	_CLOCKID_T_DECLARED
// #endif
// 
// typedef	__critical_t	critical_t;	/* Critical section value */
// typedef	__daddr_t	daddr_t;	/* disk address */
// 
// #ifndef _DEV_T_DECLARED
// typedef	__dev_t		dev_t;		/* device number or struct cdev */
// #define	_DEV_T_DECLARED
// #endif
// 
// #ifndef _FFLAGS_T_DECLARED
// typedef	__fflags_t	fflags_t;	/* file flags */
// #define	_FFLAGS_T_DECLARED
// #endif
// 
// typedef	__fixpt_t	fixpt_t;	/* fixed point number */
// 
// #ifndef _FSBLKCNT_T_DECLARED		/* for statvfs() */
// typedef	__fsblkcnt_t	fsblkcnt_t;
// typedef	__fsfilcnt_t	fsfilcnt_t;
// #define	_FSBLKCNT_T_DECLARED
// #endif
// 
// #ifndef _GID_T_DECLARED
// typedef	__gid_t		gid_t;		/* group id */
// #define	_GID_T_DECLARED
// #endif
// 
// #ifndef _IN_ADDR_T_DECLARED
// typedef	__uint32_t	in_addr_t;	/* base type for internet address */
// #define	_IN_ADDR_T_DECLARED
// #endif
// 
// #ifndef _IN_PORT_T_DECLARED
// typedef	__uint16_t	in_port_t;
// #define	_IN_PORT_T_DECLARED
// #endif
// 
// #ifndef _ID_T_DECLARED
// typedef	__id_t		id_t;		/* can hold a uid_t or pid_t */
// #define	_ID_T_DECLARED
// #endif
// 
// #ifndef _INO_T_DECLARED
// typedef	__ino_t		ino_t;		/* inode number */
// #define	_INO_T_DECLARED
// #endif
// 
// #ifndef _KEY_T_DECLARED
// typedef	__key_t		key_t;		/* IPC key (for Sys V IPC) */
// #define	_KEY_T_DECLARED
// #endif
// 
// #ifndef _LWPID_T_DECLARED
// typedef	__lwpid_t	lwpid_t;	/* Thread ID (a.k.a. LWP) */
// #define	_LWPID_T_DECLARED
// #endif
// 
// #ifndef _MODE_T_DECLARED
// typedef	__mode_t	mode_t;		/* permissions */
// #define	_MODE_T_DECLARED
// #endif
// 
// #ifndef _ACCMODE_T_DECLARED
// typedef	__accmode_t	accmode_t;	/* access permissions */
// #define	_ACCMODE_T_DECLARED
// #endif
// 
// #ifndef _NLINK_T_DECLARED
// typedef	__nlink_t	nlink_t;	/* link count */
// #define	_NLINK_T_DECLARED
// #endif
// 
// #ifndef _OFF_T_DECLARED
// typedef	__off_t		off_t;		/* file offset */
// #define	_OFF_T_DECLARED
// #endif
// 
// #ifndef _OFF64_T_DECLARED
// typedef	__off64_t	off64_t;	/* file offset (alias) */
// #define	_OFF64_T_DECLARED
// #endif
// 
// #ifndef _PID_T_DECLARED
// typedef	__pid_t		pid_t;		/* process id */
// #define	_PID_T_DECLARED
// #endif
// 
// typedef	__register_t	register_t;
// 
// #ifndef _RLIM_T_DECLARED
// typedef	__rlim_t	rlim_t;		/* resource limit */
// #define	_RLIM_T_DECLARED
// #endif
// 
// typedef	__int64_t	sbintime_t;
// 
// typedef	__segsz_t	segsz_t;	/* segment size (in pages) */
// 
// #ifndef _SIZE_T_DECLARED
// typedef	__size_t	size_t;
// #define	_SIZE_T_DECLARED
// #endif
// 
// #ifndef _SSIZE_T_DECLARED
// typedef	__ssize_t	ssize_t;
// #define	_SSIZE_T_DECLARED
// #endif
// 
// #ifndef _SUSECONDS_T_DECLARED
// typedef	__suseconds_t	suseconds_t;	/* microseconds (signed) */
// #define	_SUSECONDS_T_DECLARED
// #endif
// 
// #ifndef _TIME_T_DECLARED
// typedef	__time_t	time_t;
// #define	_TIME_T_DECLARED
// #endif
// 
// #ifndef _TIMER_T_DECLARED
// typedef	__timer_t	timer_t;
// #define	_TIMER_T_DECLARED
// #endif
// 
// #ifndef _MQD_T_DECLARED
// typedef	__mqd_t	mqd_t;
// #define	_MQD_T_DECLARED
// #endif
// 
// typedef	__u_register_t	u_register_t;
// 
// #ifndef _UID_T_DECLARED
// typedef	__uid_t		uid_t;		/* user id */
// #define	_UID_T_DECLARED
// #endif
// 
// #ifndef _USECONDS_T_DECLARED
// typedef	__useconds_t	useconds_t;	/* microseconds (unsigned) */
// #define	_USECONDS_T_DECLARED
// #endif
// 
// #ifndef _CAP_IOCTL_T_DECLARED
// #define	_CAP_IOCTL_T_DECLARED
// typedef	unsigned long	cap_ioctl_t;
// #endif
// 
// #ifndef _CAP_RIGHTS_T_DECLARED
// #define	_CAP_RIGHTS_T_DECLARED
// struct cap_rights;
// 
// typedef	struct cap_rights	cap_rights_t;
// #endif
// 
// /*
//  * Types suitable for exporting physical addresses, virtual addresses
//  * (pointers), and memory object sizes from the kernel independent of native
//  * word size.  These should be used in place of vm_paddr_t, (u)intptr_t, and
//  * size_t in structs which contain such types that are shared with userspace.
//  */
// typedef	__uint64_t	kpaddr_t;
// typedef	__uint64_t	kvaddr_t;
// typedef	__uint64_t	ksize_t;
// typedef	__int64_t	kssize_t;
// 
// typedef	__vm_offset_t	vm_offset_t;
// typedef	__uint64_t	vm_ooffset_t;
// typedef	__vm_paddr_t	vm_paddr_t;
// typedef	__uint64_t	vm_pindex_t;
// typedef	__vm_size_t	vm_size_t;
// 
// typedef __rman_res_t    rman_res_t;
// 
// #ifdef _KERNEL
// typedef	unsigned int	boolean_t;
// typedef	struct _device	*device_t;
// typedef	__intfptr_t	intfptr_t;
// 
// /*
//  * XXX this is fixed width for historical reasons.  It should have had type
//  * __int_fast32_t.  Fixed-width types should not be used unless binary
//  * compatibility is essential.  Least-width types should be used even less
//  * since they provide smaller benefits.
//  *
//  * XXX should be MD.
//  *
//  * XXX this is bogus in -current, but still used for spl*().
//  */
// typedef	__uint32_t	intrmask_t;	/* Interrupt mask (spl, xxx_imask...) */
// 
// typedef	__uintfptr_t	uintfptr_t;
// typedef	__uint64_t	uoff_t;
// typedef	char		vm_memattr_t;	/* memory attribute codes */
// typedef	struct vm_page	*vm_page_t;
// 
// #define offsetof(type, field) __offsetof(type, field)
// #endif /* _KERNEL */
// 
// #if	defined(_KERNEL) || defined(_STANDALONE)
// #if !defined(__bool_true_false_are_defined) && !defined(__cplusplus)
// #define	__bool_true_false_are_defined	1
// #define	false	0
// #define	true	1
// typedef	_Bool	bool;
// #endif /* !__bool_true_false_are_defined && !__cplusplus */
// #endif /* KERNEL || _STANDALONE */
// 
// /*
//  * The following are all things that really shouldn't exist in this header,
//  * since its purpose is to provide typedefs, not miscellaneous doodads.
//  */
// 
// #ifdef __POPCNT__
// #define	__bitcount64(x)	__builtin_popcountll((__uint64_t)(x))
// #define	__bitcount32(x)	__builtin_popcount((__uint32_t)(x))
// #define	__bitcount16(x)	__builtin_popcount((__uint16_t)(x))
// #define	__bitcountl(x)	__builtin_popcountl((unsigned long)(x))
// #define	__bitcount(x)	__builtin_popcount((unsigned int)(x))
// #else
// /*
//  * Population count algorithm using SWAR approach
//  * - "SIMD Within A Register".
//  */
// static __inline __uint16_t
// __bitcount16(__uint16_t _x)
// {
// 
// 	_x = (_x & 0x5555) + ((_x & 0xaaaa) >> 1);
// 	_x = (_x & 0x3333) + ((_x & 0xcccc) >> 2);
// 	_x = (_x + (_x >> 4)) & 0x0f0f;
// 	_x = (_x + (_x >> 8)) & 0x00ff;
// 	return (_x);
// }
// 
// static __inline __uint32_t
// __bitcount32(__uint32_t _x)
// {
// 
// 	_x = (_x & 0x55555555) + ((_x & 0xaaaaaaaa) >> 1);
// 	_x = (_x & 0x33333333) + ((_x & 0xcccccccc) >> 2);
// 	_x = (_x + (_x >> 4)) & 0x0f0f0f0f;
// 	_x = (_x + (_x >> 8));
// 	_x = (_x + (_x >> 16)) & 0x000000ff;
// 	return (_x);
// }
// 
// #ifdef __LP64__
// static __inline __uint64_t
// __bitcount64(__uint64_t _x)
// {
// 
// 	_x = (_x & 0x5555555555555555) + ((_x & 0xaaaaaaaaaaaaaaaa) >> 1);
// 	_x = (_x & 0x3333333333333333) + ((_x & 0xcccccccccccccccc) >> 2);
// 	_x = (_x + (_x >> 4)) & 0x0f0f0f0f0f0f0f0f;
// 	_x = (_x + (_x >> 8));
// 	_x = (_x + (_x >> 16));
// 	_x = (_x + (_x >> 32)) & 0x000000ff;
// 	return (_x);
// }
// 
// #define	__bitcountl(x)	__bitcount64((unsigned long)(x))
// #else
// static __inline __uint64_t
// __bitcount64(__uint64_t _x)
// {
// 
// 	return (__bitcount32(_x >> 32) + __bitcount32(_x));
// }
// 
// #define	__bitcountl(x)	__bitcount32((unsigned long)(x))
// #endif
// #define	__bitcount(x)	__bitcount32((unsigned int)(x))
// #endif
// 
// #if __BSD_VISIBLE
// 
// #include <sys/select.h>
// 
// /*
//  * The major and minor numbers are encoded in dev_t as MMMmmmMm (where
//  * letters correspond to bytes).  The encoding of the lower 4 bytes is
//  * constrained by compatibility with 16-bit and 32-bit dev_t's.  The
//  * encoding of the upper 4 bytes is the least unnatural one consistent
//  * with this and other constraints.  Also, the decoding of the m bytes by
//  * minor() is unnatural to maximize compatibility subject to not discarding
//  * bits.  The upper m byte is shifted into the position of the lower M byte
//  * instead of shifting 3 upper m bytes to close the gap.  Compatibility for
//  * minor() is achieved iff the upper m byte is 0.
//  */
// #define	major(d)	__major(d)
// static __inline int
// __major(dev_t _d)
// {
// 	return (((_d >> 32) & 0xffffff00) | ((_d >> 8) & 0xff));
// }
// #define	minor(d)	__minor(d)
// static __inline int
// __minor(dev_t _d)
// {
// 	return (((_d >> 24) & 0xff00) | (_d & 0xffff00ff));
// }
// #define	makedev(M, m)	__makedev((M), (m))
// static __inline dev_t
// __makedev(int _Major, int _Minor)
// {
// 	return (((dev_t)(_Major & 0xffffff00) << 32) | ((_Major & 0xff) << 8) |
// 	    ((dev_t)(_Minor & 0xff00) << 24) | (_Minor & 0xffff00ff));
// }
// 
// /*
//  * These declarations belong elsewhere, but are repeated here and in
//  * <stdio.h> to give broken programs a better chance of working with
//  * 64-bit off_t's.
//  */
// #ifndef _KERNEL
// __BEGIN_DECLS
// #ifndef _FTRUNCATE_DECLARED
// #define	_FTRUNCATE_DECLARED
// int	 ftruncate(int, off_t);
// #endif
// #ifndef _LSEEK_DECLARED
// #define	_LSEEK_DECLARED
// off_t	 lseek(int, off_t, int);
// #endif
// #ifndef _MMAP_DECLARED
// #define	_MMAP_DECLARED
// void *	 mmap(void *, size_t, int, int, int, off_t);
// #endif
// #ifndef _TRUNCATE_DECLARED
// #define	_TRUNCATE_DECLARED
// int	 truncate(const char *, off_t);
// #endif
// __END_DECLS
// #endif /* !_KERNEL */
// 
// #endif /* __BSD_VISIBLE */
// 
// #endif /* !_SYS_TYPES_H_ */
// End provenance source

#pragma once
#include <x86/_types.h>
