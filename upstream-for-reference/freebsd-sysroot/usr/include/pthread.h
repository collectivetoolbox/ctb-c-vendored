// Provenance source: llvm/libc/include/llvm-libc-macros/pthread-macros.h sha256=cd111fb70d9bed62c819200a4890a135bcfd304a7123aa985114d08f53d0df7b
// //===-- Definition of pthread macros --------------------------------------===//
// //
// // Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// // See https://llvm.org/LICENSE.txt for license information.
// // SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// //
// //===----------------------------------------------------------------------===//
// 
// #ifndef LLVM_LIBC_MACROS_PTHREAD_MACRO_H
// #define LLVM_LIBC_MACROS_PTHREAD_MACRO_H
// 
// #define PTHREAD_NULL {0}
// 
// #define PTHREAD_CREATE_JOINABLE 0
// #define PTHREAD_CREATE_DETACHED 1
// 
// #define PTHREAD_MUTEX_NORMAL 0
// #define PTHREAD_MUTEX_ERRORCHECK 1
// #define PTHREAD_MUTEX_RECURSIVE 2
// #define PTHREAD_MUTEX_DEFAULT PTHREAD_MUTEX_NORMAL
// 
// #define PTHREAD_MUTEX_STALLED 0
// #define PTHREAD_MUTEX_ROBUST 1
// 
// #define PTHREAD_BARRIER_SERIAL_THREAD -1
// 
// #define PTHREAD_ONCE_INIT {0}
// 
// #define PTHREAD_PROCESS_PRIVATE 0
// #define PTHREAD_PROCESS_SHARED 1
// 
// #define PTHREAD_SCOPE_SYSTEM 0
// #define PTHREAD_SCOPE_PROCESS 1
// 
// #define PTHREAD_INHERIT_SCHED 0
// #define PTHREAD_EXPLICIT_SCHED 1
// 
// #ifdef __linux__
// #define PTHREAD_MUTEX_INITIALIZER                                              \
//   {                                                                            \
//       /* .__ftxw = */ {0},    /* .__priority_inherit = */ 0,                   \
//       /* .__recursive = */ 0, /* .__robust = */ 0,                             \
//       /* .__pshared = */ 0,   /* .__error_checking = */ 0,                     \
//       /* .__owner = */ 0,     /* .__lock_count = */ 0,                         \
//   }
// #else
// #define PTHREAD_MUTEX_INITIALIZER                                              \
//   {                                                                            \
//       /* .__ftxw = */ {0},    /* .__priority_inherit = */ 0,                   \
//       /* .__recursive = */ 0, /* .__robust = */ 0,                             \
//       /* .__pshared = */ 0,   /* .__error_checking = */ 0,                     \
//       /* .__owner = */ 0,     /* .__lock_count = */ 0,                         \
//   }
// #endif
// 
// #define PTHREAD_COND_INITIALIZER                                               \
//   {                                                                            \
//       /* .__waiter_queue = */ {{NULL, NULL}},                                  \
//       /* .__futex = */ {0},                                                    \
//       /* .__is_shared = */ 0,                                                  \
//       /* .__is_realtime = */ 1,                                                \
//       /* .__padding = */ {0},                                                  \
//   }
// 
// #define PTHREAD_RWLOCK_INITIALIZER                                             \
//   {                                                                            \
//       /* .__raw = */ {                                                         \
//           /* .__is_pshared = */ 0,                                             \
//           /* .__preference = */ 0,                                             \
//           /* .__state = */ 0,                                                  \
//           /* .__wait_queue_mutex = */ {0},                                     \
//           /* .__pending_readers = */ {0},                                      \
//           /* .__pending_writers = */ {0},                                      \
//           /* .__reader_serialization = */ {0},                                 \
//           /* .__writer_serialization = */ {0},                                 \
//       },                                                                       \
//       /* .__write_tid = */ 0,                                                  \
//   }
// 
// #define pthread_cleanup_push(routine, arg)                                     \
//   do {                                                                         \
//     struct __pthread_cleanup_frame __cleanup_frame;                            \
//   __pthread_cleanup_push(&__cleanup_frame, (routine), (arg))
// 
// #define pthread_cleanup_pop(execute)                                           \
//   __pthread_cleanup_pop((execute));                                            \
//   }                                                                            \
//   while (0)
// 
// // glibc extensions
// #define PTHREAD_STACK_MIN (1 << 14) // 16KB
// #define PTHREAD_RWLOCK_PREFER_READER_NP 0
// #define PTHREAD_RWLOCK_PREFER_WRITER_NP 1
// #define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP 2
// 
// // llvm libc extensions
// #define PTHREAD_STACK_DYNAMIC_NP 0
// 
// #endif // LLVM_LIBC_MACROS_PTHREAD_MACRO_H
// End provenance source

// Provenance source: llvm/libc/include/pthread.yaml sha256=756af6583fd92577d068a34baecae807584275dc56d2d8c649c56be7bb9cc987
// header: pthread.h
// standards:
//   - posix
// macros:
//   - macro_name: "PTHREAD_NULL"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_CREATE_JOINABLE"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_CREATE_DETACHED"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_MUTEX_NORMAL"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_MUTEX_ERRORCHECK"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_MUTEX_RECURSIVE"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_MUTEX_DEFAULT"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_MUTEX_STALLED"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_MUTEX_ROBUST"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_BARRIER_SERIAL_THREAD"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_ONCE_INIT"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_PROCESS_PRIVATE"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_PROCESS_SHARED"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_SCOPE_SYSTEM"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_SCOPE_PROCESS"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_INHERIT_SCHED"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_EXPLICIT_SCHED"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_MUTEX_INITIALIZER"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_COND_INITIALIZER"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_RWLOCK_INITIALIZER"
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_STACK_MIN"
//     standards:
//       - gnu
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_RWLOCK_PREFER_READER_NP"
//     standards:
//       - gnu
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_RWLOCK_PREFER_WRITER_NP"
//     standards:
//       - gnu
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP"
//     standards:
//       - gnu
//     macro_header: pthread-macros.h
//   - macro_name: "PTHREAD_STACK_DYNAMIC_NP"
//     standards:
//       - llvm_libc_ext
//     macro_header: pthread-macros.h
//   - macro_name: "pthread_cleanup_pop"
//     macro_header: pthread-macros.h
//   - macro_name: "pthread_cleanup_push"
//     macro_header: pthread-macros.h
// types:
//   - type_name: pthread_t
//   - type_name: pthread_once_t
//   - type_name: pthread_mutex_t
//   - type_name: pthread_mutexattr_t
//   - type_name: pthread_barrier_t
//   - type_name: pthread_barrierattr_t
//   - type_name: pthread_key_t
//   - type_name: pthread_cond_t
//   - type_name: pthread_condattr_t
//   - type_name: pthread_rwlock_t
//   - type_name: pthread_rwlockattr_t
//   - type_name: pthread_attr_t
//   - type_name: pthread_spinlock_t
//   - type_name: pthread_id_np_t
//     standards:
//       - llvm_libc_ext
//   - type_name: struct___pthread_cleanup_frame
//     standards:
//       - llvm_libc_ext
// functions:
//   - name: __pthread_cleanup_pop
//     standards:
//       - llvm_libc_ext
//     return_type: void
//     arguments:
//       - type: int
//   - name: __pthread_cleanup_push
//     standards:
//       - llvm_libc_ext
//     return_type: void
//     arguments:
//       - type: struct __pthread_cleanup_frame *
//       - type: void (*)(void *)
//       - type: void *
//   - name: pthread_atfork
//     return_type: int
//     arguments:
//       - type: __atfork_callback_t
//       - type: __atfork_callback_t
//       - type: __atfork_callback_t
//   - name: pthread_attr_destroy
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//   - name: pthread_attr_getdetachstate
//     return_type: int
//     arguments:
//       - type: const pthread_attr_t *
//       - type: int *
//   - name: pthread_attr_getguardsize
//     return_type: int
//     arguments:
//       - type: const pthread_attr_t *__restrict
//       - type: size_t *__restrict
//   - name: pthread_attr_getinheritsched
//     standards:
//       - posix
//     return_type: int
//     arguments:
//       - type: const pthread_attr_t *__restrict
//       - type: int *__restrict
//   - name: pthread_attr_getschedparam
//     return_type: int
//     arguments:
//       - type: const pthread_attr_t *__restrict
//       - type: struct sched_param *__restrict
//   - name: pthread_attr_getschedpolicy
//     return_type: int
//     arguments:
//       - type: const pthread_attr_t *__restrict
//       - type: int *__restrict
//   - name: pthread_attr_getscope
//     standards:
//       - posix
//     return_type: int
//     arguments:
//       - type: const pthread_attr_t *__restrict
//       - type: int *__restrict
//   - name: pthread_attr_getstack
//     return_type: int
//     arguments:
//       - type: const pthread_attr_t *__restrict
//       - type: void **__restrict
//       - type: size_t *__restrict
//   - name: pthread_attr_getstacksize
//     return_type: int
//     arguments:
//       - type: const pthread_attr_t *__restrict
//       - type: size_t *__restrict
//   - name: pthread_attr_init
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//   - name: pthread_attr_setdetachstate
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//       - type: int
//   - name: pthread_attr_setguardsize
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//       - type: size_t
//   - name: pthread_attr_setinheritsched
//     standards:
//       - posix
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//       - type: int
//   - name: pthread_attr_setschedparam
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *__restrict
//       - type: const struct sched_param *__restrict
//   - name: pthread_attr_setschedpolicy
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//       - type: int
//   - name: pthread_attr_setscope
//     standards:
//       - posix
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//       - type: int
//   - name: pthread_attr_setstack
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//       - type: void *
//       - type: size_t
//   - name: pthread_attr_setstacksize
//     return_type: int
//     arguments:
//       - type: pthread_attr_t *
//       - type: size_t
//   - name: pthread_condattr_destroy
//     return_type: int
//     arguments:
//       - type: pthread_condattr_t *
//   - name: pthread_condattr_getclock
//     return_type: int
//     arguments:
//       - type: const pthread_condattr_t *__restrict
//       - type: clockid_t *__restrict
//   - name: pthread_condattr_getpshared
//     return_type: int
//     arguments:
//       - type: const pthread_condattr_t *__restrict
//       - type: int *__restrict
//   - name: pthread_condattr_init
//     return_type: int
//     arguments:
//       - type: pthread_condattr_t *
//   - name: pthread_condattr_setclock
//     return_type: int
//     arguments:
//       - type: pthread_condattr_t *
//       - type: clockid_t
//   - name: pthread_condattr_setpshared
//     return_type: int
//     arguments:
//       - type: pthread_condattr_t *
//       - type: int
//   - name: pthread_cond_broadcast
//     return_type: int
//     arguments:
//       - type: pthread_cond_t *
//   - name: pthread_cond_clockwait
//     return_type: int
//     arguments:
//       - type: pthread_cond_t *__restrict
//       - type: pthread_mutex_t *__restrict
//       - type: clockid_t
//       - type: const struct timespec *__restrict
//   - name: pthread_cond_destroy
//     return_type: int
//     arguments:
//       - type: pthread_cond_t *
//   - name: pthread_cond_init
//     return_type: int
//     arguments:
//       - type: pthread_cond_t *__restrict
//       - type: const pthread_condattr_t *__restrict
//   - name: pthread_cond_signal
//     return_type: int
//     arguments:
//       - type: pthread_cond_t *
//   - name: pthread_cond_timedwait
//     return_type: int
//     arguments:
//       - type: pthread_cond_t *__restrict
//       - type: pthread_mutex_t *__restrict
//       - type: const struct timespec *__restrict
//   - name: pthread_cond_wait
//     return_type: int
//     arguments:
//       - type: pthread_cond_t *__restrict
//       - type: pthread_mutex_t *__restrict
//   - name: pthread_create
//     return_type: int
//     arguments:
//       - type: pthread_t *__restrict
//       - type: const pthread_attr_t *__restrict
//       - type: __pthread_start_t
//       - type: void *
//   - name: pthread_detach
//     return_type: int
//     arguments:
//       - type: pthread_t
//   - name: pthread_equal
//     return_type: int
//     arguments:
//       - type: pthread_t
//       - type: pthread_t
//   - name: pthread_exit
//     return_type: _Noreturn void
//     arguments:
//       - type: void *
//   - name: pthread_getattr_np
//     standards:
//       - gnu
//     return_type: int
//     arguments:
//       - type: pthread_t
//       - type: pthread_attr_t *
//   - name: pthread_getname_np
//     standards:
//       - gnu
//     return_type: int
//     arguments:
//       - type: pthread_t
//       - type: char *
//       - type: size_t
//   - name: pthread_getschedparam
//     return_type: int
//     arguments:
//       - type: pthread_t
//       - type: int *__restrict
//       - type: struct sched_param *__restrict
//   - name: pthread_getspecific
//     return_type: void *
//     arguments:
//       - type: pthread_key_t
//   - name: pthread_getstack_np
//     standards:
//       - llvm_libc_ext
//     return_type: int
//     arguments:
//       - type: pthread_t
//       - type: void **__restrict
//       - type: size_t *__restrict
//   - name: pthread_join
//     return_type: int
//     arguments:
//       - type: pthread_t
//       - type: void **
//   - name: pthread_key_create
//     return_type: int
//     arguments:
//       - type: pthread_key_t *
//       - type: __pthread_tss_dtor_t
//   - name: pthread_key_delete
//     return_type: int
//     arguments:
//       - type: pthread_key_t
//   - name: pthread_mutex_destroy
//     return_type: int
//     arguments:
//       - type: pthread_mutex_t *
//   - name: pthread_mutex_init
//     return_type: int
//     arguments:
//       - type: pthread_mutex_t *__restrict
//       - type: const pthread_mutexattr_t *__restrict
//   - name: pthread_mutex_lock
//     return_type: int
//     arguments:
//       - type: pthread_mutex_t *
//   - name: pthread_mutex_trylock
//     return_type: int
//     arguments:
//       - type: pthread_mutex_t *
//   - name: pthread_mutex_unlock
//     return_type: int
//     arguments:
//       - type: pthread_mutex_t *
//   - name: pthread_mutexattr_destroy
//     return_type: int
//     arguments:
//       - type: pthread_mutexattr_t *
//   - name: pthread_mutexattr_getpshared
//     return_type: int
//     arguments:
//       - type: const pthread_mutexattr_t *__restrict
//       - type: int *__restrict
//   - name: pthread_mutexattr_getrobust
//     return_type: int
//     arguments:
//       - type: const pthread_mutexattr_t *__restrict
//       - type: int *__restrict
//   - name: pthread_mutexattr_gettype
//     return_type: int
//     arguments:
//       - type: const pthread_mutexattr_t *__restrict
//       - type: int *__restrict
//   - name: pthread_mutexattr_init
//     return_type: int
//     arguments:
//       - type: pthread_mutexattr_t *
//   - name: pthread_mutexattr_setpshared
//     return_type: int
//     arguments:
//       - type: pthread_mutexattr_t *__restrict
//       - type: int
//   - name: pthread_mutexattr_setrobust
//     return_type: int
//     arguments:
//       - type: pthread_mutexattr_t *__restrict
//       - type: int
//   - name: pthread_mutexattr_settype
//     return_type: int
//     arguments:
//       - type: pthread_mutexattr_t *__restrict
//       - type: int
//   - name: pthread_barrier_init
//     return_type: int
//     arguments:
//       - type: pthread_barrier_t *__restrict
//       - type: const pthread_barrierattr_t *__restrict
//       - type: int
//   - name: pthread_barrier_wait
//     return_type: int
//     arguments:
//       - type: pthread_barrier_t *
//   - name: pthread_barrier_destroy
//     return_type: int
//     arguments:
//       - type: pthread_barrier_t *
//   - name: pthread_once
//     return_type: int
//     arguments:
//       - type: pthread_once_t *
//       - type: __pthread_once_func_t
//   - name: pthread_rwlock_clockrdlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *__restrict
//       - type: clockid_t
//       - type: const struct timespec *__restrict
//   - name: pthread_rwlock_clockwrlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *__restrict
//       - type: clockid_t
//       - type: const struct timespec *__restrict
//   - name: pthread_rwlock_destroy
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *
//   - name: pthread_rwlock_init
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *
//       - type: const pthread_rwlockattr_t *__restrict
//   - name: pthread_rwlock_rdlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *
//   - name: pthread_rwlock_timedrdlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *__restrict
//       - type: const struct timespec *__restrict
//   - name: pthread_rwlock_timedwrlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *__restrict
//       - type: const struct timespec *__restrict
//   - name: pthread_rwlock_tryrdlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *
//   - name: pthread_rwlock_trywrlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *
//   - name: pthread_rwlock_unlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *
//   - name: pthread_rwlock_wrlock
//     return_type: int
//     arguments:
//       - type: pthread_rwlock_t *
//   - name: pthread_rwlockattr_destroy
//     return_type: int
//     arguments:
//       - type: pthread_rwlockattr_t *
//   - name: pthread_rwlockattr_getkind_np
//     standards:
//       - gnu
//     return_type: int
//     arguments:
//       - type: pthread_rwlockattr_t *
//       - type: int *
//   - name: pthread_rwlockattr_getpshared
//     return_type: int
//     arguments:
//       - type: const pthread_rwlockattr_t *
//       - type: int *
//   - name: pthread_rwlockattr_init
//     return_type: int
//     arguments:
//       - type: pthread_rwlockattr_t *
//   - name: pthread_rwlockattr_setkind_np
//     standards:
//       - gnu
//     return_type: int
//     arguments:
//       - type: pthread_rwlockattr_t *
//       - type: int
//   - name: pthread_rwlockattr_setpshared
//     return_type: int
//     arguments:
//       - type: pthread_rwlockattr_t *
//       - type: int
//   - name: pthread_self
//     return_type: pthread_t
//     arguments:
//       - type: void
//   - name: pthread_setname_np
//     standards:
//       - gnu
//     return_type: int
//     arguments:
//       - type: pthread_t
//       - type: const char *
//   - name: pthread_setschedparam
//     return_type: int
//     arguments:
//       - type: pthread_t
//       - type: int
//       - type: const struct sched_param *
//   - name: pthread_setspecific
//     return_type: int
//     arguments:
//       - type: pthread_key_t
//       - type: const void *
//   - name: pthread_spin_destroy
//     return_type: int
//     arguments:
//       - type: pthread_spinlock_t *
//   - name: pthread_spin_init
//     return_type: int
//     arguments:
//       - type: pthread_spinlock_t *
//       - type: int
//   - name: pthread_spin_lock
//     return_type: int
//     arguments:
//       - type: pthread_spinlock_t *
//   - name: pthread_spin_trylock
//     return_type: int
//     arguments:
//       - type: pthread_spinlock_t *
//   - name: pthread_spin_unlock
//     return_type: int
//     arguments:
//       - type: pthread_spinlock_t *
//   - name: pthread_getthreadid_np
//     standards:
//       - llvm_libc_ext
//     return_type: pthread_id_np_t
//     arguments:
//       - type: void
//   - name: pthread_getunique_np
//     standards:
//       - llvm_libc_ext
//     return_type: int
//     arguments:
//       - type: const pthread_t *__restrict
//       - type: pthread_id_np_t *__restrict
// End provenance source
// Provenance source: llvm/libc/LICENSE.TXT sha256=ebcd9bbf783a73d05c53ba4d586b8d5813dcdf3bbec50265860ccc885e606f47
// ==============================================================================
// The LLVM Project is under the Apache License v2.0 with LLVM Exceptions:
// ==============================================================================
// 
//                                  Apache License
//                            Version 2.0, January 2004
//                         http://www.apache.org/licenses/
// 
//     TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION
// 
//     1. Definitions.
// 
//       "License" shall mean the terms and conditions for use, reproduction,
//       and distribution as defined by Sections 1 through 9 of this document.
// 
//       "Licensor" shall mean the copyright owner or entity authorized by
//       the copyright owner that is granting the License.
// 
//       "Legal Entity" shall mean the union of the acting entity and all
//       other entities that control, are controlled by, or are under common
//       control with that entity. For the purposes of this definition,
//       "control" means (i) the power, direct or indirect, to cause the
//       direction or management of such entity, whether by contract or
//       otherwise, or (ii) ownership of fifty percent (50%) or more of the
//       outstanding shares, or (iii) beneficial ownership of such entity.
// 
//       "You" (or "Your") shall mean an individual or Legal Entity
//       exercising permissions granted by this License.
// 
//       "Source" form shall mean the preferred form for making modifications,
//       including but not limited to software source code, documentation
//       source, and configuration files.
// 
//       "Object" form shall mean any form resulting from mechanical
//       transformation or translation of a Source form, including but
//       not limited to compiled object code, generated documentation,
//       and conversions to other media types.
// 
//       "Work" shall mean the work of authorship, whether in Source or
//       Object form, made available under the License, as indicated by a
//       copyright notice that is included in or attached to the work
//       (an example is provided in the Appendix below).
// 
//       "Derivative Works" shall mean any work, whether in Source or Object
//       form, that is based on (or derived from) the Work and for which the
//       editorial revisions, annotations, elaborations, or other modifications
//       represent, as a whole, an original work of authorship. For the purposes
//       of this License, Derivative Works shall not include works that remain
//       separable from, or merely link (or bind by name) to the interfaces of,
//       the Work and Derivative Works thereof.
// 
//       "Contribution" shall mean any work of authorship, including
//       the original version of the Work and any modifications or additions
//       to that Work or Derivative Works thereof, that is intentionally
//       submitted to Licensor for inclusion in the Work by the copyright owner
//       or by an individual or Legal Entity authorized to submit on behalf of
//       the copyright owner. For the purposes of this definition, "submitted"
//       means any form of electronic, verbal, or written communication sent
//       to the Licensor or its representatives, including but not limited to
//       communication on electronic mailing lists, source code control systems,
//       and issue tracking systems that are managed by, or on behalf of, the
//       Licensor for the purpose of discussing and improving the Work, but
//       excluding communication that is conspicuously marked or otherwise
//       designated in writing by the copyright owner as "Not a Contribution."
// 
//       "Contributor" shall mean Licensor and any individual or Legal Entity
//       on behalf of whom a Contribution has been received by Licensor and
//       subsequently incorporated within the Work.
// 
//     2. Grant of Copyright License. Subject to the terms and conditions of
//       this License, each Contributor hereby grants to You a perpetual,
//       worldwide, non-exclusive, no-charge, royalty-free, irrevocable
//       copyright license to reproduce, prepare Derivative Works of,
//       publicly display, publicly perform, sublicense, and distribute the
//       Work and such Derivative Works in Source or Object form.
// 
//     3. Grant of Patent License. Subject to the terms and conditions of
//       this License, each Contributor hereby grants to You a perpetual,
//       worldwide, non-exclusive, no-charge, royalty-free, irrevocable
//       (except as stated in this section) patent license to make, have made,
//       use, offer to sell, sell, import, and otherwise transfer the Work,
//       where such license applies only to those patent claims licensable
//       by such Contributor that are necessarily infringed by their
//       Contribution(s) alone or by combination of their Contribution(s)
//       with the Work to which such Contribution(s) was submitted. If You
//       institute patent litigation against any entity (including a
//       cross-claim or counterclaim in a lawsuit) alleging that the Work
//       or a Contribution incorporated within the Work constitutes direct
//       or contributory patent infringement, then any patent licenses
//       granted to You under this License for that Work shall terminate
//       as of the date such litigation is filed.
// 
//     4. Redistribution. You may reproduce and distribute copies of the
//       Work or Derivative Works thereof in any medium, with or without
//       modifications, and in Source or Object form, provided that You
//       meet the following conditions:
// 
//       (a) You must give any other recipients of the Work or
//           Derivative Works a copy of this License; and
// 
//       (b) You must cause any modified files to carry prominent notices
//           stating that You changed the files; and
// 
//       (c) You must retain, in the Source form of any Derivative Works
//           that You distribute, all copyright, patent, trademark, and
//           attribution notices from the Source form of the Work,
//           excluding those notices that do not pertain to any part of
//           the Derivative Works; and
// 
//       (d) If the Work includes a "NOTICE" text file as part of its
//           distribution, then any Derivative Works that You distribute must
//           include a readable copy of the attribution notices contained
//           within such NOTICE file, excluding those notices that do not
//           pertain to any part of the Derivative Works, in at least one
//           of the following places: within a NOTICE text file distributed
//           as part of the Derivative Works; within the Source form or
//           documentation, if provided along with the Derivative Works; or,
//           within a display generated by the Derivative Works, if and
//           wherever such third-party notices normally appear. The contents
//           of the NOTICE file are for informational purposes only and
//           do not modify the License. You may add Your own attribution
//           notices within Derivative Works that You distribute, alongside
//           or as an addendum to the NOTICE text from the Work, provided
//           that such additional attribution notices cannot be construed
//           as modifying the License.
// 
//       You may add Your own copyright statement to Your modifications and
//       may provide additional or different license terms and conditions
//       for use, reproduction, or distribution of Your modifications, or
//       for any such Derivative Works as a whole, provided Your use,
//       reproduction, and distribution of the Work otherwise complies with
//       the conditions stated in this License.
// 
//     5. Submission of Contributions. Unless You explicitly state otherwise,
//       any Contribution intentionally submitted for inclusion in the Work
//       by You to the Licensor shall be under the terms and conditions of
//       this License, without any additional terms or conditions.
//       Notwithstanding the above, nothing herein shall supersede or modify
//       the terms of any separate license agreement you may have executed
//       with Licensor regarding such Contributions.
// 
//     6. Trademarks. This License does not grant permission to use the trade
//       names, trademarks, service marks, or product names of the Licensor,
//       except as required for reasonable and customary use in describing the
//       origin of the Work and reproducing the content of the NOTICE file.
// 
//     7. Disclaimer of Warranty. Unless required by applicable law or
//       agreed to in writing, Licensor provides the Work (and each
//       Contributor provides its Contributions) on an "AS IS" BASIS,
//       WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
//       implied, including, without limitation, any warranties or conditions
//       of TITLE, NON-INFRINGEMENT, MERCHANTABILITY, or FITNESS FOR A
//       PARTICULAR PURPOSE. You are solely responsible for determining the
//       appropriateness of using or redistributing the Work and assume any
//       risks associated with Your exercise of permissions under this License.
// 
//     8. Limitation of Liability. In no event and under no legal theory,
//       whether in tort (including negligence), contract, or otherwise,
//       unless required by applicable law (such as deliberate and grossly
//       negligent acts) or agreed to in writing, shall any Contributor be
//       liable to You for damages, including any direct, indirect, special,
//       incidental, or consequential damages of any character arising as a
//       result of this License or out of the use or inability to use the
//       Work (including but not limited to damages for loss of goodwill,
//       work stoppage, computer failure or malfunction, or any and all
//       other commercial damages or losses), even if such Contributor
//       has been advised of the possibility of such damages.
// 
//     9. Accepting Warranty or Additional Liability. While redistributing
//       the Work or Derivative Works thereof, You may choose to offer,
//       and charge a fee for, acceptance of support, warranty, indemnity,
//       or other liability obligations and/or rights consistent with this
//       License. However, in accepting such obligations, You may act only
//       on Your own behalf and on Your sole responsibility, not on behalf
//       of any other Contributor, and only if You agree to indemnify,
//       defend, and hold each Contributor harmless for any liability
//       incurred by, or claims asserted against, such Contributor by reason
//       of your accepting any such warranty or additional liability.
// 
//     END OF TERMS AND CONDITIONS
// 
//     APPENDIX: How to apply the Apache License to your work.
// 
//       To apply the Apache License to your work, attach the following
//       boilerplate notice, with the fields enclosed by brackets "[]"
//       replaced with your own identifying information. (Don't include
//       the brackets!)  The text should be enclosed in the appropriate
//       comment syntax for the file format. We also recommend that a
//       file or class name and description of purpose be included on the
//       same "printed page" as the copyright notice for easier
//       identification within third-party archives.
// 
//     Copyright [yyyy] [name of copyright owner]
// 
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
// 
// 
// ---- LLVM Exceptions to the Apache 2.0 License ----
// 
// As an exception, if, as a result of your compiling your source code, portions
// of this Software are embedded into an Object form of such source code, you
// may redistribute such embedded portions in such Object form without complying
// with the conditions of Sections 4(a), 4(b) and 4(d) of the License.
// 
// In addition, if you combine or link compiled forms of this Software with
// software that is licensed under the GPLv2 ("Combined Software") and if a
// court of competent jurisdiction determines that the patent provision (Section
// 3), the indemnity provision (Section 9) or other Section of the License
// conflicts with the conditions of the GPLv2, you may retroactively and
// prospectively choose to deem waived or otherwise exclude such Section(s) of
// the License, but only in their entirety and only with respect to the Combined
// Software.
// 
// ==============================================================================
// Software from third parties included in the LLVM Project:
// ==============================================================================
// The LLVM Project contains third party software which is under different license
// terms. All such code will be identified clearly using at least one of two
// mechanisms:
// 1) It will be in a separate directory tree with its own `LICENSE.txt` or
//    `LICENSE` file at the top containing the specific license and restrictions
//    which apply to that software, or
// 2) It will contain specific license and restriction terms at the top of every
//    file.
// 
// ==============================================================================
// Legacy LLVM License (https://llvm.org/docs/DeveloperPolicy.html#legacy):
// ==============================================================================
// University of Illinois/NCSA
// Open Source License
// 
// Copyright (c) 2007-2019 University of Illinois at Urbana-Champaign.
// All rights reserved.
// 
// Developed by:
// 
//     LLVM Team
// 
//     University of Illinois at Urbana-Champaign
// 
//     http://llvm.org
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal with
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
// 
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimers.
// 
//     * Redistributions in binary form must reproduce the above copyright notice,
//       this list of conditions and the following disclaimers in the
//       documentation and/or other materials provided with the distribution.
// 
//     * Neither the names of the LLVM Team, University of Illinois at
//       Urbana-Champaign, nor the names of its contributors may be used to
//       endorse or promote products derived from this Software without specific
//       prior written permission.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
// CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE
// SOFTWARE.
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_affinity.c sha256=1c1d2e7ba5d0eec411665c4b930548bf8065f06e39b12fc1fe6d2cc19a1f6e12
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2008, David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread_np.h>
// #include <sys/param.h>
// #include <sys/cpuset.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_pthread_getaffinity_np, pthread_getaffinity_np);
// __weak_reference(_pthread_setaffinity_np, pthread_setaffinity_np);
// 
// int
// _pthread_setaffinity_np(pthread_t td, size_t cpusetsize, const cpuset_t *cpusetp)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	lwpid_t		tid;
// 	int		error;
// 
// 	if (td == curthread) {
// 		error = cpuset_setaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID,
// 			-1, cpusetsize, cpusetp);
// 		if (error == -1)
// 			error = errno;
// 	} else if ((error = _thr_find_thread(curthread, td, 0)) == 0) {
// 		tid = TID(td);
// 		error = cpuset_setaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID, tid,
// 			cpusetsize, cpusetp);
// 		if (error == -1)
// 			error = errno;
// 		THR_THREAD_UNLOCK(curthread, td);
// 	}
// 	return (error);
// }
// 
// int
// _pthread_getaffinity_np(pthread_t td, size_t cpusetsize, cpuset_t *cpusetp)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	lwpid_t tid;
// 	int error;
// 
// 	if (td == curthread) {
// 		error = cpuset_getaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID,
// 			-1, cpusetsize, cpusetp);
// 		if (error == -1)
// 			error = errno;
// 	} else if ((error = _thr_find_thread(curthread, td, 0)) == 0) {
// 		tid = TID(td);
// 		error = cpuset_getaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID, tid,
// 			    cpusetsize, cpusetp);
// 		if (error == -1)
// 			error = errno;
// 		THR_THREAD_UNLOCK(curthread, td);
// 	}
// 	return (error);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_barrier.c sha256=569313f01538c7286216e68f76dea0aa14db46ef37e9782ad756da9f36bd59c2
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2003 David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// _Static_assert(sizeof(struct pthread_barrier) <= THR_PAGE_SIZE_MIN,
//     "pthread_barrier is too large for off-page");
// 
// __weak_reference(_pthread_barrier_init,		pthread_barrier_init);
// __weak_reference(_pthread_barrier_wait,		pthread_barrier_wait);
// __weak_reference(_pthread_barrier_destroy,	pthread_barrier_destroy);
// 
// int
// _pthread_barrier_destroy(pthread_barrier_t *barrier)
// {
// 	pthread_barrier_t bar;
// 	struct pthread *curthread;
// 	int pshared;
// 
// 	if (barrier == NULL || *barrier == NULL)
// 		return (EINVAL);
// 
// 	if (*barrier == THR_PSHARED_PTR) {
// 		bar = __thr_pshared_offpage(barrier, 0);
// 		if (bar == NULL) {
// 			*barrier = NULL;
// 			return (0);
// 		}
// 		pshared = 1;
// 	} else {
// 		bar = *barrier;
// 		pshared = 0;
// 	}
// 	curthread = _get_curthread();
// 	THR_UMUTEX_LOCK(curthread, &bar->b_lock);
// 	if (bar->b_destroying) {
// 		THR_UMUTEX_UNLOCK(curthread, &bar->b_lock);
// 		return (EBUSY);
// 	}
// 	bar->b_destroying = 1;
// 	do {
// 		if (bar->b_waiters > 0) {
// 			bar->b_destroying = 0;
// 			THR_UMUTEX_UNLOCK(curthread, &bar->b_lock);
// 			return (EBUSY);
// 		}
// 		if (bar->b_refcount != 0) {
// 			_thr_ucond_wait(&bar->b_cv, &bar->b_lock, NULL, 0);
// 			THR_UMUTEX_LOCK(curthread, &bar->b_lock);
// 		} else
// 			break;
// 	} while (1);
// 	bar->b_destroying = 0;
// 	THR_UMUTEX_UNLOCK(curthread, &bar->b_lock);
// 
// 	*barrier = NULL;
// 	if (pshared)
// 		__thr_pshared_destroy(barrier);
// 	else
// 		free(bar);
// 	return (0);
// }
// 
// int
// _pthread_barrier_init(pthread_barrier_t * __restrict barrier,
//     const pthread_barrierattr_t * __restrict attr, unsigned count)
// {
// 	pthread_barrier_t bar;
// 	int pshared;
// 
// 	if (barrier == NULL || count == 0 || count > INT_MAX)
// 		return (EINVAL);
// 
// 	if (attr == NULL || *attr == NULL ||
// 	    (*attr)->pshared == PTHREAD_PROCESS_PRIVATE) {
// 		bar = calloc(1, sizeof(struct pthread_barrier));
// 		if (bar == NULL)
// 			return (ENOMEM);
// 		*barrier = bar;
// 		pshared = 0;
// 	} else {
// 		bar = __thr_pshared_offpage(barrier, 1);
// 		if (bar == NULL)
// 			return (EFAULT);
// 		*barrier = THR_PSHARED_PTR;
// 		pshared = 1;
// 	}
// 
// 	_thr_umutex_init(&bar->b_lock);
// 	_thr_ucond_init(&bar->b_cv);
// 	if (pshared) {
// 		bar->b_lock.m_flags |= USYNC_PROCESS_SHARED;
// 		bar->b_cv.c_flags |= USYNC_PROCESS_SHARED;
// 	}
// 	bar->b_count = count;
// 	return (0);
// }
// 
// int
// _pthread_barrier_wait(pthread_barrier_t *barrier)
// {
// 	struct pthread *curthread;
// 	pthread_barrier_t bar;
// 	int64_t cycle;
// 	int ret;
// 
// 	if (barrier == NULL || *barrier == NULL)
// 		return (EINVAL);
// 
// 	if (*barrier == THR_PSHARED_PTR) {
// 		bar = __thr_pshared_offpage(barrier, 0);
// 		if (bar == NULL)
// 			return (EINVAL);
// 	} else {
// 		bar = *barrier;
// 	}
// 	curthread = _get_curthread();
// 	THR_UMUTEX_LOCK(curthread, &bar->b_lock);
// 	if (++bar->b_waiters == bar->b_count) {
// 		/* Current thread is lastest thread */
// 		bar->b_waiters = 0;
// 		bar->b_cycle++;
// 		_thr_ucond_broadcast(&bar->b_cv);
// 		THR_UMUTEX_UNLOCK(curthread, &bar->b_lock);
// 		ret = PTHREAD_BARRIER_SERIAL_THREAD;
// 	} else {
// 		cycle = bar->b_cycle;
// 		bar->b_refcount++;
// 		do {
// 			_thr_ucond_wait(&bar->b_cv, &bar->b_lock, NULL, 0);
// 			THR_UMUTEX_LOCK(curthread, &bar->b_lock);
// 			/* test cycle to avoid bogus wakeup */
// 		} while (cycle == bar->b_cycle);
// 		if (--bar->b_refcount == 0 && bar->b_destroying)
// 			_thr_ucond_broadcast(&bar->b_cv);
// 		THR_UMUTEX_UNLOCK(curthread, &bar->b_lock);
// 		ret = 0;
// 	}
// 	return (ret);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_barrierattr.c sha256=aef6bd109f581bd5e2bf3d61844c2745d394155e0b7f38c69d260c086014fab3
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2003 David Xu <davidxu@freebsd.org>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice(s), this list of conditions and the following disclaimer as
//  *    the first lines of this file unmodified other than the possible 
//  *    addition of one or more copyright notices.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice(s), this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY
//  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  * DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) BE LIABLE FOR ANY
//  * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  * DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_pthread_barrierattr_destroy, pthread_barrierattr_destroy);
// __weak_reference(_pthread_barrierattr_init, pthread_barrierattr_init);
// __weak_reference(_pthread_barrierattr_setpshared,
// 	pthread_barrierattr_setpshared);
// __weak_reference(_pthread_barrierattr_getpshared,
// 	pthread_barrierattr_getpshared);
// 
// int
// _pthread_barrierattr_destroy(pthread_barrierattr_t *attr)
// {
// 
// 	if (attr == NULL || *attr == NULL)
// 		return (EINVAL);
// 
// 	free(*attr);
// 	return (0);
// }
// 
// int
// _pthread_barrierattr_getpshared(const pthread_barrierattr_t * __restrict attr,
//     int * __restrict pshared)
// {
// 
// 	if (attr == NULL || *attr == NULL)
// 		return (EINVAL);
// 
// 	*pshared = (*attr)->pshared;
// 	return (0);
// }
// 
// int
// _pthread_barrierattr_init(pthread_barrierattr_t *attr)
// {
// 
// 	if (attr == NULL)
// 		return (EINVAL);
// 
// 	if ((*attr = malloc(sizeof(struct pthread_barrierattr))) == NULL)
// 		return (ENOMEM);
// 
// 	(*attr)->pshared = PTHREAD_PROCESS_PRIVATE;
// 	return (0);
// }
// 
// int
// _pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared)
// {
// 
// 	if (attr == NULL || *attr == NULL ||
// 	    (pshared != PTHREAD_PROCESS_PRIVATE &&
// 	    pshared != PTHREAD_PROCESS_SHARED))
// 		return (EINVAL);
// 
// 	(*attr)->pshared = pshared;
// 	return (0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_cancel.c sha256=abc01588d48b97efe5c6790c94b2833d9985ca867a246682befa2fd01989db82
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005, David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_thr_cancel, pthread_cancel);
// __weak_reference(_thr_cancel, _pthread_cancel);
// __weak_reference(_thr_setcancelstate, pthread_setcancelstate);
// __weak_reference(_thr_setcancelstate, _pthread_setcancelstate);
// __weak_reference(_thr_setcanceltype, pthread_setcanceltype);
// __weak_reference(_thr_setcanceltype, _pthread_setcanceltype);
// __weak_reference(_Tthr_testcancel, pthread_testcancel);
// __weak_reference(_Tthr_testcancel, _pthread_testcancel);
// __weak_reference(_Tthr_cancel_enter, _pthread_cancel_enter);
// __weak_reference(_Tthr_cancel_leave, _pthread_cancel_leave);
// 
// static inline void
// testcancel(struct pthread *curthread)
// {
// 	if (__predict_false(SHOULD_CANCEL(curthread) &&
// 	    !THR_IN_CRITICAL(curthread)))
// 		_pthread_exit(PTHREAD_CANCELED);
// }
// 
// void
// _thr_testcancel(struct pthread *curthread)
// {
// 	testcancel(curthread);
// }
// 
// int
// _thr_cancel(pthread_t pthread)
// {
// 	struct pthread *curthread = _get_curthread();
// 	int ret;
// 
// 	/*
// 	 * POSIX says _pthread_cancel should be async cancellation safe.
// 	 * _thr_find_thread and THR_THREAD_UNLOCK will enter and leave critical
// 	 * region automatically.
// 	 */
// 	if ((ret = _thr_find_thread(curthread, pthread, 1)) == 0) {
// 		if (!pthread->cancel_pending) {
// 			pthread->cancel_pending = 1;
// 			if (pthread->state != PS_DEAD)
// 				_thr_send_sig(pthread, SIGCANCEL);
// 		}
// 		THR_THREAD_UNLOCK(curthread, pthread);
// 	}
// 	return (ret);
// }
// 
// int
// _thr_setcancelstate(int state, int *oldstate)
// {
// 	struct pthread *curthread = _get_curthread();
// 	int oldval;
// 
// 	oldval = curthread->cancel_enable;
// 	switch (state) {
// 	case PTHREAD_CANCEL_DISABLE:
// 		curthread->cancel_enable = 0;
// 		break;
// 	case PTHREAD_CANCEL_ENABLE:
// 		curthread->cancel_enable = 1;
// 		if (curthread->cancel_async)
// 			testcancel(curthread);
// 		break;
// 	default:
// 		return (EINVAL);
// 	}
// 
// 	if (oldstate) {
// 		*oldstate = oldval ? PTHREAD_CANCEL_ENABLE :
// 			PTHREAD_CANCEL_DISABLE;
// 	}
// 	return (0);
// }
// 
// int
// _thr_setcanceltype(int type, int *oldtype)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	int oldval;
// 
// 	oldval = curthread->cancel_async;
// 	switch (type) {
// 	case PTHREAD_CANCEL_ASYNCHRONOUS:
// 		curthread->cancel_async = 1;
// 		testcancel(curthread);
// 		break;
// 	case PTHREAD_CANCEL_DEFERRED:
// 		curthread->cancel_async = 0;
// 		break;
// 	default:
// 		return (EINVAL);
// 	}
// 
// 	if (oldtype) {
// 		*oldtype = oldval ? PTHREAD_CANCEL_ASYNCHRONOUS :
// 		 	PTHREAD_CANCEL_DEFERRED;
// 	}
// 	return (0);
// }
// 
// void
// _Tthr_testcancel(void)
// {
// 	struct pthread *curthread;
// 
// 	_thr_check_init();
// 	curthread = _get_curthread();
// 	testcancel(curthread);
// }
// 
// void
// _thr_cancel_enter(struct pthread *curthread)
// {
// 	curthread->cancel_point = 1;
// 	testcancel(curthread);
// }
// 
// void
// _thr_cancel_enter2(struct pthread *curthread, int maycancel)
// {
// 	curthread->cancel_point = 1;
// 	if (__predict_false(SHOULD_CANCEL(curthread) &&
// 	    !THR_IN_CRITICAL(curthread))) {
// 		if (!maycancel)
// 			thr_wake(curthread->tid);
// 		else
// 			_pthread_exit(PTHREAD_CANCELED);
// 	}
// }
// 
// void
// _thr_cancel_leave(struct pthread *curthread, int maycancel)
// {
// 	curthread->cancel_point = 0;
// 	if (__predict_false(SHOULD_CANCEL(curthread) &&
// 	    !THR_IN_CRITICAL(curthread) && maycancel))
// 		_pthread_exit(PTHREAD_CANCELED);
// }
// 
// void
// _Tthr_cancel_enter(int maycancel)
// {
// 	_thr_cancel_enter2(_get_curthread(), maycancel);
// }
// 
// void
// _Tthr_cancel_leave(int maycancel)
// {
// 	_thr_cancel_leave(_get_curthread(), maycancel);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_clean.c sha256=24c640b373e8981bf0afdb29556e5fd89624bf3e01c317293bffa6d8114dab8e
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
// 
//  * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <signal.h>
// #include <errno.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// #undef pthread_cleanup_push
// #undef pthread_cleanup_pop
// 
// /* old binary compatible interfaces */
// __weak_reference(_thr_cleanup_pop, pthread_cleanup_pop);
// __weak_reference(_thr_cleanup_pop, _pthread_cleanup_pop);
// __weak_reference(_thr_cleanup_push, pthread_cleanup_push);
// __weak_reference(_thr_cleanup_push, _pthread_cleanup_push);
// 
// /* help static linking when libc symbols have preference */
// __weak_reference(__thr_cleanup_push_imp, __pthread_cleanup_push_imp);
// __weak_reference(__thr_cleanup_pop_imp, __pthread_cleanup_pop_imp);
// 
// void
// __thr_cleanup_push_imp(void (*routine)(void *), void *arg,
//     struct _pthread_cleanup_info *info)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	struct pthread_cleanup *newbuf;
// 
// 	newbuf = (void *)info;
// 	newbuf->routine = routine;
// 	newbuf->routine_arg = arg;
// 	newbuf->onheap = 0;
// 	newbuf->prev = curthread->cleanup;
// 	curthread->cleanup = newbuf;
// }
// 
// void
// __thr_cleanup_pop_imp(int execute)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	struct pthread_cleanup *old;
// 
// 	if ((old = curthread->cleanup) != NULL) {
// 		curthread->cleanup = old->prev;
// 		if (execute)
// 			old->routine(old->routine_arg);
// 		if (old->onheap)
// 			free(old);
// 	}
// }
// 
// void
// _thr_cleanup_push(void (*routine)(void *), void *arg)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	struct pthread_cleanup *newbuf;
// #ifdef _PTHREAD_FORCED_UNWIND
// 	curthread->unwind_disabled = 1;
// #endif
// 	if ((newbuf = (struct pthread_cleanup *)
// 	    malloc(sizeof(struct pthread_cleanup))) != NULL) {
// 		newbuf->routine = routine;
// 		newbuf->routine_arg = arg;
// 		newbuf->onheap = 1;
// 		newbuf->prev = curthread->cleanup;
// 		curthread->cleanup = newbuf;
// 	}
// }
// 
// void
// _thr_cleanup_pop(int execute)
// {
// 	__pthread_cleanup_pop_imp(execute);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_cond.c sha256=977ab4f8e7c118902238a56cb3e652938602cfb55658724528b477909887df97
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005 David Xu <davidxu@freebsd.org>
//  * Copyright (c) 2015 The FreeBSD Foundation
//  * All rights reserved.
//  *
//  * Portions of this software were developed by Konstantin Belousov
//  * under sponsorship from the FreeBSD Foundation.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <stdlib.h>
// #include <errno.h>
// #include <string.h>
// #include <pthread.h>
// #include <limits.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// _Static_assert(sizeof(struct pthread_cond) <= THR_PAGE_SIZE_MIN,
//     "pthread_cond too large");
// 
// /*
//  * Prototypes
//  */
// int	__pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
// 		       const struct timespec * abstime);
// static int cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
// static int cond_wait_common(pthread_cond_t *cond, pthread_mutex_t *mutex,
// 		    const struct timespec *abstime, int cancel);
// static int cond_signal_common(pthread_cond_t *cond);
// static int cond_broadcast_common(pthread_cond_t *cond);
// 
// /*
//  * Double underscore versions are cancellation points.  Single underscore
//  * versions are not and are provided for libc internal usage (which
//  * shouldn't introduce cancellation points).
//  */
// __weak_reference(__thr_cond_wait, pthread_cond_wait);
// __weak_reference(__thr_cond_wait, __pthread_cond_wait);
// __weak_reference(_thr_cond_wait, _pthread_cond_wait);
// __weak_reference(__pthread_cond_timedwait, pthread_cond_timedwait);
// __weak_reference(_thr_cond_init, pthread_cond_init);
// __weak_reference(_thr_cond_init, _pthread_cond_init);
// __weak_reference(_thr_cond_destroy, pthread_cond_destroy);
// __weak_reference(_thr_cond_destroy, _pthread_cond_destroy);
// __weak_reference(_thr_cond_signal, pthread_cond_signal);
// __weak_reference(_thr_cond_signal, _pthread_cond_signal);
// __weak_reference(_thr_cond_broadcast, pthread_cond_broadcast);
// __weak_reference(_thr_cond_broadcast, _pthread_cond_broadcast);
// 
// #define CV_PSHARED(cvp)	(((cvp)->kcond.c_flags & USYNC_PROCESS_SHARED) != 0)
// 
// static void
// cond_init_body(struct pthread_cond *cvp, const struct pthread_cond_attr *cattr)
// {
// 
// 	if (cattr == NULL) {
// 		cvp->kcond.c_clockid = CLOCK_REALTIME;
// 	} else {
// 		if (cattr->c_pshared)
// 			cvp->kcond.c_flags |= USYNC_PROCESS_SHARED;
// 		cvp->kcond.c_clockid = cattr->c_clockid;
// 	}
// }
// 
// static int
// cond_init(pthread_cond_t *cond, const pthread_condattr_t *cond_attr)
// {
// 	struct pthread_cond *cvp;
// 	const struct pthread_cond_attr *cattr;
// 	int pshared;
// 
// 	cattr = cond_attr != NULL ? *cond_attr : NULL;
// 	if (cattr == NULL || cattr->c_pshared == PTHREAD_PROCESS_PRIVATE) {
// 		pshared = 0;
// 		cvp = calloc(1, sizeof(struct pthread_cond));
// 		if (cvp == NULL)
// 			return (ENOMEM);
// 	} else {
// 		pshared = 1;
// 		cvp = __thr_pshared_offpage(cond, 1);
// 		if (cvp == NULL)
// 			return (EFAULT);
// 	}
// 
// 	/*
// 	 * Initialise the condition variable structure:
// 	 */
// 	cond_init_body(cvp, cattr);
// 	*cond = pshared ? THR_PSHARED_PTR : cvp;
// 	return (0);
// }
// 
// static int
// init_static(struct pthread *thread, pthread_cond_t *cond)
// {
// 	int ret;
// 
// 	THR_LOCK_ACQUIRE(thread, &_cond_static_lock);
// 
// 	if (*cond == NULL)
// 		ret = cond_init(cond, NULL);
// 	else
// 		ret = 0;
// 
// 	THR_LOCK_RELEASE(thread, &_cond_static_lock);
// 
// 	return (ret);
// }
// 
// #define CHECK_AND_INIT_COND							\
// 	if (*cond == THR_PSHARED_PTR) {						\
// 		cvp = __thr_pshared_offpage(cond, 0);				\
// 		if (cvp == NULL)						\
// 			return (EINVAL);					\
// 	} else if (__predict_false((cvp = (*cond)) <= THR_COND_DESTROYED)) {	\
// 		if (cvp == THR_COND_INITIALIZER) {				\
// 			int ret;						\
// 			ret = init_static(_get_curthread(), cond);		\
// 			if (ret)						\
// 				return (ret);					\
// 		} else if (cvp == THR_COND_DESTROYED) {				\
// 			return (EINVAL);					\
// 		}								\
// 		cvp = *cond;							\
// 	}
// 
// int
// _thr_cond_init(pthread_cond_t * __restrict cond,
//     const pthread_condattr_t * __restrict cond_attr)
// {
// 
// 	*cond = NULL;
// 	return (cond_init(cond, cond_attr));
// }
// 
// int
// _thr_cond_destroy(pthread_cond_t *cond)
// {
// 	struct pthread_cond *cvp;
// 	int error;
// 
// 	error = 0;
// 	if (*cond == THR_PSHARED_PTR) {
// 		cvp = __thr_pshared_offpage(cond, 0);
// 		if (cvp != NULL) {
// 			if (cvp->kcond.c_has_waiters)
// 				error = EBUSY;
// 			else
// 				__thr_pshared_destroy(cond);
// 		}
// 		if (error == 0)
// 			*cond = THR_COND_DESTROYED;
// 	} else if ((cvp = *cond) == THR_COND_INITIALIZER) {
// 		/* nothing */
// 	} else if (cvp == THR_COND_DESTROYED) {
// 		error = EINVAL;
// 	} else {
// 		cvp = *cond;
// 		if (cvp->__has_user_waiters || cvp->kcond.c_has_waiters)
// 			error = EBUSY;
// 		else {
// 			*cond = THR_COND_DESTROYED;
// 			free(cvp);
// 		}
// 	}
// 	return (error);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, if thread is canceled, it means it
//  *   did not get a wakeup from pthread_cond_signal(), otherwise, it is
//  *   not canceled.
//  *   Thread cancellation never cause wakeup from pthread_cond_signal()
//  *   to be lost.
//  */
// static int
// cond_wait_kernel(struct pthread_cond *cvp, struct pthread_mutex *mp,
//     const struct timespec *abstime, int cancel)
// {
// 	struct pthread *curthread;
// 	int error, error2, recurse, robust;
// 
// 	curthread = _get_curthread();
// 	robust = _mutex_enter_robust(curthread, mp);
// 
// 	error = _mutex_cv_detach(mp, &recurse);
// 	if (error != 0) {
// 		if (robust)
// 			_mutex_leave_robust(curthread, mp);
// 		return (error);
// 	}
// 
// 	if (cancel)
// 		_thr_cancel_enter2(curthread, 0);
// 	error = _thr_ucond_wait(&cvp->kcond, &mp->m_lock, abstime,
// 	    CVWAIT_ABSTIME | CVWAIT_CLOCKID);
// 	if (cancel)
// 		_thr_cancel_leave(curthread, 0);
// 
// 	/*
// 	 * Note that PP mutex and ROBUST mutex may return
// 	 * interesting error codes.
// 	 */
// 	if (error == 0) {
// 		error2 = _mutex_cv_lock(mp, recurse, true);
// 	} else if (error == EINTR || error == ETIMEDOUT) {
// 		error2 = _mutex_cv_lock(mp, recurse, true);
// 		/*
// 		 * Do not do cancellation on EOWNERDEAD there.  The
// 		 * cancellation cleanup handler will use the protected
// 		 * state and unlock the mutex without making the state
// 		 * consistent and the state will be unrecoverable.
// 		 */
// 		if (error2 == 0 && cancel) {
// 			if (robust) {
// 				_mutex_leave_robust(curthread, mp);
// 				robust = false;
// 			}
// 			_thr_testcancel(curthread);
// 		}
// 
// 		if (error == EINTR)
// 			error = 0;
// 	} else {
// 		/* We know that it didn't unlock the mutex. */
// 		_mutex_cv_attach(mp, recurse);
// 		if (cancel) {
// 			if (robust) {
// 				_mutex_leave_robust(curthread, mp);
// 				robust = false;
// 			}
// 			_thr_testcancel(curthread);
// 		}
// 		error2 = 0;
// 	}
// 	if (robust)
// 		_mutex_leave_robust(curthread, mp);
// 	return (error2 != 0 ? error2 : error);
// }
// 
// /*
//  * Thread waits in userland queue whenever possible, when thread
//  * is signaled or broadcasted, it is removed from the queue, and
//  * is saved in curthread's defer_waiters[] buffer, but won't be
//  * woken up until mutex is unlocked.
//  */
// 
// static int
// cond_wait_user(struct pthread_cond *cvp, struct pthread_mutex *mp,
//     const struct timespec *abstime, int cancel)
// {
// 	struct pthread *curthread;
// 	struct sleepqueue *sq;
// 	int deferred, error, error2, recurse;
// 
// 	curthread = _get_curthread();
// 	if (curthread->wchan != NULL)
// 		PANIC("thread %p was already on queue.", curthread);
// 
// 	if (cancel)
// 		_thr_testcancel(curthread);
// 
// 	_sleepq_lock(cvp);
// 	/*
// 	 * set __has_user_waiters before unlocking mutex, this allows
// 	 * us to check it without locking in pthread_cond_signal().
// 	 */
// 	cvp->__has_user_waiters = 1; 
// 	deferred = 0;
// 	(void)_mutex_cv_unlock(mp, &recurse, &deferred);
// 	curthread->mutex_obj = mp;
// 	_sleepq_add(cvp, curthread);
// 	for(;;) {
// 		_thr_clear_wake(curthread);
// 		_sleepq_unlock(cvp);
// 		if (deferred) {
// 			deferred = 0;
// 			if ((mp->m_lock.m_owner & UMUTEX_CONTESTED) == 0)
// 				(void)_umtx_op_err(&mp->m_lock,
// 				    UMTX_OP_MUTEX_WAKE2, mp->m_lock.m_flags,
// 				    0, 0);
// 		}
// 		if (curthread->nwaiter_defer > 0) {
// 			_thr_wake_all(curthread->defer_waiters,
// 			    curthread->nwaiter_defer);
// 			curthread->nwaiter_defer = 0;
// 		}
// 
// 		if (cancel)
// 			_thr_cancel_enter2(curthread, 0);
// 		error = _thr_sleep(curthread, cvp->kcond.c_clockid, abstime);
// 		if (cancel)
// 			_thr_cancel_leave(curthread, 0);
// 
// 		_sleepq_lock(cvp);
// 		if (curthread->wchan == NULL) {
// 			error = 0;
// 			break;
// 		} else if (cancel && SHOULD_CANCEL(curthread)) {
// 			sq = _sleepq_lookup(cvp);
// 			cvp->__has_user_waiters = _sleepq_remove(sq, curthread);
// 			_sleepq_unlock(cvp);
// 			curthread->mutex_obj = NULL;
// 			error2 = _mutex_cv_lock(mp, recurse, false);
// 			if (!THR_IN_CRITICAL(curthread))
// 				_pthread_exit(PTHREAD_CANCELED);
// 			else /* this should not happen */
// 				return (error2);
// 		} else if (error == ETIMEDOUT) {
// 			sq = _sleepq_lookup(cvp);
// 			cvp->__has_user_waiters =
// 			    _sleepq_remove(sq, curthread);
// 			break;
// 		}
// 	}
// 	_sleepq_unlock(cvp);
// 	curthread->mutex_obj = NULL;
// 	error2 = _mutex_cv_lock(mp, recurse, false);
// 	if (error == 0)
// 		error = error2;
// 	return (error);
// }
// 
// static int
// cond_wait_common(pthread_cond_t *cond, pthread_mutex_t *mutex,
// 	const struct timespec *abstime, int cancel)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	struct pthread_cond *cvp;
// 	struct pthread_mutex *mp;
// 	int	error;
// 
// 	CHECK_AND_INIT_COND
// 
// 	if (*mutex == THR_PSHARED_PTR) {
// 		mp = __thr_pshared_offpage(mutex, 0);
// 		if (mp == NULL)
// 			return (EINVAL);
// 	} else {
// 		mp = *mutex;
// 	}
// 
// 	if ((error = _mutex_owned(curthread, mp)) != 0)
// 		return (error);
// 
// 	if (curthread->attr.sched_policy != SCHED_OTHER ||
// 	    (mp->m_lock.m_flags & (UMUTEX_PRIO_PROTECT | UMUTEX_PRIO_INHERIT |
// 	    USYNC_PROCESS_SHARED)) != 0 || CV_PSHARED(cvp))
// 		return (cond_wait_kernel(cvp, mp, abstime, cancel));
// 	else
// 		return (cond_wait_user(cvp, mp, abstime, cancel));
// }
// 
// int
// _thr_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex)
// {
// 
// 	return (cond_wait_common(cond, mutex, NULL, 0));
// }
// 
// int
// __thr_cond_wait(pthread_cond_t * __restrict cond,
//     pthread_mutex_t * __restrict mutex)
// {
// 
// 	return (cond_wait_common(cond, mutex, NULL, 1));
// }
// 
// int
// _thr_cond_timedwait(pthread_cond_t * __restrict cond,
//     pthread_mutex_t * __restrict mutex,
//     const struct timespec * __restrict abstime)
// {
// 
// 	if (abstime == NULL || abstime->tv_sec < 0 || abstime->tv_nsec < 0 ||
// 	    abstime->tv_nsec >= 1000000000)
// 		return (EINVAL);
// 
// 	return (cond_wait_common(cond, mutex, abstime, 0));
// }
// 
// int
// __pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
// 		       const struct timespec *abstime)
// {
// 
// 	if (abstime == NULL || abstime->tv_sec < 0 || abstime->tv_nsec < 0 ||
// 	    abstime->tv_nsec >= 1000000000)
// 		return (EINVAL);
// 
// 	return (cond_wait_common(cond, mutex, abstime, 1));
// }
// 
// static int
// cond_signal_common(pthread_cond_t *cond)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	struct pthread *td;
// 	struct pthread_cond *cvp;
// 	struct pthread_mutex *mp;
// 	struct sleepqueue *sq;
// 	int	*waddr;
// 	int	pshared;
// 
// 	/*
// 	 * If the condition variable is statically initialized, perform dynamic
// 	 * initialization.
// 	 */
// 	CHECK_AND_INIT_COND
// 
// 	pshared = CV_PSHARED(cvp);
// 
// 	_thr_ucond_signal(&cvp->kcond);
// 
// 	if (pshared || cvp->__has_user_waiters == 0)
// 		return (0);
// 
// 	curthread = _get_curthread();
// 	waddr = NULL;
// 	_sleepq_lock(cvp);
// 	sq = _sleepq_lookup(cvp);
// 	if (sq == NULL) {
// 		_sleepq_unlock(cvp);
// 		return (0);
// 	}
// 
// 	td = _sleepq_first(sq);
// 	mp = td->mutex_obj;
// 	cvp->__has_user_waiters = _sleepq_remove(sq, td);
// 	if (PMUTEX_OWNER_ID(mp) == TID(curthread)) {
// 		if (curthread->nwaiter_defer >= MAX_DEFER_WAITERS) {
// 			_thr_wake_all(curthread->defer_waiters,
// 			    curthread->nwaiter_defer);
// 			curthread->nwaiter_defer = 0;
// 		}
// 		curthread->defer_waiters[curthread->nwaiter_defer++] =
// 		    &td->wake_addr->value;
// 		mp->m_flags |= PMUTEX_FLAG_DEFERRED;
// 	} else {
// 		waddr = &td->wake_addr->value;
// 	}
// 	_sleepq_unlock(cvp);
// 	if (waddr != NULL)
// 		_thr_set_wake(waddr);
// 	return (0);
// }
// 
// struct broadcast_arg {
// 	struct pthread *curthread;
// 	unsigned int *waddrs[MAX_DEFER_WAITERS];
// 	int count;
// };
// 
// static void
// drop_cb(struct pthread *td, void *arg)
// {
// 	struct broadcast_arg *ba = arg;
// 	struct pthread_mutex *mp;
// 	struct pthread *curthread = ba->curthread;
// 
// 	mp = td->mutex_obj;
// 	if (PMUTEX_OWNER_ID(mp) == TID(curthread)) {
// 		if (curthread->nwaiter_defer >= MAX_DEFER_WAITERS) {
// 			_thr_wake_all(curthread->defer_waiters,
// 			    curthread->nwaiter_defer);
// 			curthread->nwaiter_defer = 0;
// 		}
// 		curthread->defer_waiters[curthread->nwaiter_defer++] =
// 		    &td->wake_addr->value;
// 		mp->m_flags |= PMUTEX_FLAG_DEFERRED;
// 	} else {
// 		if (ba->count >= MAX_DEFER_WAITERS) {
// 			_thr_wake_all(ba->waddrs, ba->count);
// 			ba->count = 0;
// 		}
// 		ba->waddrs[ba->count++] = &td->wake_addr->value;
// 	}
// }
// 
// static int
// cond_broadcast_common(pthread_cond_t *cond)
// {
// 	int    pshared;
// 	struct pthread_cond *cvp;
// 	struct sleepqueue *sq;
// 	struct broadcast_arg ba;
// 
// 	/*
// 	 * If the condition variable is statically initialized, perform dynamic
// 	 * initialization.
// 	 */
// 	CHECK_AND_INIT_COND
// 
// 	pshared = CV_PSHARED(cvp);
// 
// 	_thr_ucond_broadcast(&cvp->kcond);
// 
// 	if (pshared || cvp->__has_user_waiters == 0)
// 		return (0);
// 
// 	ba.curthread = _get_curthread();
// 	ba.count = 0;
// 	
// 	_sleepq_lock(cvp);
// 	sq = _sleepq_lookup(cvp);
// 	if (sq == NULL) {
// 		_sleepq_unlock(cvp);
// 		return (0);
// 	}
// 	_sleepq_drop(sq, drop_cb, &ba);
// 	cvp->__has_user_waiters = 0;
// 	_sleepq_unlock(cvp);
// 	if (ba.count > 0)
// 		_thr_wake_all(ba.waddrs, ba.count);
// 	return (0);
// }
// 
// int
// _thr_cond_signal(pthread_cond_t * cond)
// {
// 
// 	return (cond_signal_common(cond));
// }
// 
// int
// _thr_cond_broadcast(pthread_cond_t * cond)
// {
// 
// 	return (cond_broadcast_common(cond));
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_condattr.c sha256=b83779bfc3a621f9646e2696c9d7eb456fef0f15dfca42e7dd3aaea6efd553a8
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1997 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <stdlib.h>
// #include <string.h>
// #include <errno.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_pthread_condattr_init, pthread_condattr_init);
// __weak_reference(_pthread_condattr_destroy, pthread_condattr_destroy);
// __weak_reference(_pthread_condattr_getclock, pthread_condattr_getclock);
// __weak_reference(_pthread_condattr_setclock, pthread_condattr_setclock);
// __weak_reference(_pthread_condattr_getpshared, pthread_condattr_getpshared);
// __weak_reference(_pthread_condattr_setpshared, pthread_condattr_setpshared);
// 
// int
// _pthread_condattr_init(pthread_condattr_t *attr)
// {
// 	pthread_condattr_t pattr;
// 	int ret;
// 
// 	if ((pattr = (pthread_condattr_t)
// 	    malloc(sizeof(struct pthread_cond_attr))) == NULL) {
// 		ret = ENOMEM;
// 	} else {
// 		memcpy(pattr, &_pthread_condattr_default,
// 		    sizeof(struct pthread_cond_attr));
// 		*attr = pattr;
// 		ret = 0;
// 	}
// 	return (ret);
// }
// 
// int
// _pthread_condattr_destroy(pthread_condattr_t *attr)
// {
// 	int	ret;
// 
// 	if (attr == NULL || *attr == NULL) {
// 		ret = EINVAL;
// 	} else {
// 		free(*attr);
// 		*attr = NULL;
// 		ret = 0;
// 	}
// 	return(ret);
// }
// 
// int
// _pthread_condattr_getclock(const pthread_condattr_t * __restrict attr,
//     clockid_t * __restrict clock_id)
// {
// 	if (attr == NULL || *attr == NULL)
// 		return (EINVAL);
// 	*clock_id = (*attr)->c_clockid;
// 	return (0);
// }
// 
// int
// _pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id)
// {
// 	if (attr == NULL || *attr == NULL)
// 		return (EINVAL);
// 	if (clock_id != CLOCK_REALTIME &&
// 	    clock_id != CLOCK_VIRTUAL &&
// 	    clock_id != CLOCK_PROF &&
// 	    clock_id != CLOCK_MONOTONIC) {
// 		return  (EINVAL);
// 	}
// 	(*attr)->c_clockid = clock_id;
// 	return (0);
// }
// 
// int
// _pthread_condattr_getpshared(const pthread_condattr_t * __restrict attr,
//     int * __restrict pshared)
// {
// 
// 	if (attr == NULL || *attr == NULL)
// 		return (EINVAL);
// 	*pshared = (*attr)->c_pshared;
// 	return (0);
// }
// 
// int
// _pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared)
// {
// 
// 	if (attr == NULL || *attr == NULL ||
// 	    (pshared != PTHREAD_PROCESS_PRIVATE &&
// 	    pshared != PTHREAD_PROCESS_SHARED))
// 		return (EINVAL);
// 	(*attr)->c_pshared = pshared;
// 	return (0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_create.c sha256=61f7cc80f0f767ded622437a8aa40bebff56df8fb0c5e80fa520991fd301cf4e
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2003 Daniel M. Eischen <deischen@gdeb.com>
//  * Copyright (c) 2005, David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <sys/types.h>
// #include <sys/rtprio.h>
// #include <sys/signalvar.h>
// #include <errno.h>
// #include <link.h>
// #include <stdlib.h>
// #include <string.h>
// #include <stddef.h>
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// #include "libc_private.h"
// #include "thr_private.h"
// 
// static int  create_stack(struct pthread_attr *pattr);
// static void thread_start(struct pthread *curthread);
// 
// __weak_reference(_pthread_create, pthread_create);
// 
// int
// _pthread_create(pthread_t * __restrict thread,
//     const pthread_attr_t * __restrict attr, void *(*start_routine) (void *),
//     void * __restrict arg)
// {
// 	struct pthread *curthread, *new_thread;
// 	struct thr_param param;
// 	struct sched_param sched_param;
// 	struct rtprio rtp;
// 	sigset_t set, oset;
// 	cpuset_t *cpusetp;
// 	int i, cpusetsize, create_suspended, locked, old_stack_prot, ret;
// 
// 	cpusetp = NULL;
// 	ret = cpusetsize = 0;
// 	_thr_check_init();
// 
// 	/*
// 	 * Tell libc and others now they need lock to protect their data.
// 	 */
// 	if (_thr_isthreaded() == 0) {
// 		_malloc_first_thread();
// 		_thr_setthreaded(1);
// 	}
// 
// 	curthread = _get_curthread();
// 	if ((new_thread = _thr_alloc(curthread)) == NULL)
// 		return (EAGAIN);
// 
// 	memset(&param, 0, sizeof(param));
// 
// 	if (attr == NULL || *attr == NULL)
// 		/* Use the default thread attributes: */
// 		new_thread->attr = _pthread_attr_default;
// 	else {
// 		new_thread->attr = *(*attr);
// 		cpusetp = new_thread->attr.cpuset;
// 		cpusetsize = new_thread->attr.cpusetsize;
// 		new_thread->attr.cpuset = NULL;
// 		new_thread->attr.cpusetsize = 0;
// 	}
// 	if (new_thread->attr.sched_inherit == PTHREAD_INHERIT_SCHED) {
// 		/* inherit scheduling contention scope */
// 		if (curthread->attr.flags & PTHREAD_SCOPE_SYSTEM)
// 			new_thread->attr.flags |= PTHREAD_SCOPE_SYSTEM;
// 		else
// 			new_thread->attr.flags &= ~PTHREAD_SCOPE_SYSTEM;
// 
// 		new_thread->attr.prio = curthread->attr.prio;
// 		new_thread->attr.sched_policy = curthread->attr.sched_policy;
// 	}
// 
// 	new_thread->tid = TID_TERMINATED;
// 
// 	old_stack_prot = _rtld_get_stack_prot();
// 	if (create_stack(&new_thread->attr) != 0) {
// 		/* Insufficient memory to create a stack: */
// 		_thr_free(curthread, new_thread);
// 		return (EAGAIN);
// 	}
// 	/*
// 	 * Write a magic value to the thread structure
// 	 * to help identify valid ones:
// 	 */
// 	new_thread->magic = THR_MAGIC;
// 	new_thread->start_routine = start_routine;
// 	new_thread->arg = arg;
// 	new_thread->cancel_enable = 1;
// 	new_thread->cancel_async = 0;
// 	/* Initialize the mutex queue: */
// 	for (i = 0; i < TMQ_NITEMS; i++)
// 		TAILQ_INIT(&new_thread->mq[i]);
// 
// 	/* Initialise hooks in the thread structure: */
// 	if (new_thread->attr.suspend == THR_CREATE_SUSPENDED) {
// 		new_thread->flags = THR_FLAGS_NEED_SUSPEND;
// 		create_suspended = 1;
// 	} else {
// 		create_suspended = 0;
// 	}
// 
// 	new_thread->state = PS_RUNNING;
// 
// 	if (new_thread->attr.flags & PTHREAD_CREATE_DETACHED)
// 		new_thread->flags |= THR_FLAGS_DETACHED;
// 
// 	/* Add the new thread. */
// 	new_thread->refcount = 1;
// 	_thr_link(curthread, new_thread);
// 
// 	/*
// 	 * Handle the race between __pthread_map_stacks_exec and
// 	 * thread linkage.
// 	 */
// 	if (old_stack_prot != _rtld_get_stack_prot())
// 		_thr_stack_fix_protection(new_thread);
// 
// 	/* Return thread pointer eariler so that new thread can use it. */
// 	(*thread) = new_thread;
// 	if (SHOULD_REPORT_EVENT(curthread, TD_CREATE) || cpusetp != NULL) {
// 		THR_THREAD_LOCK(curthread, new_thread);
// 		locked = 1;
// 	} else
// 		locked = 0;
// 	param.start_func = (void (*)(void *)) thread_start;
// 	param.arg = new_thread;
// 	param.stack_base = new_thread->attr.stackaddr_attr;
// 	param.stack_size = new_thread->attr.stacksize_attr;
// 	param.tls_base = (char *)new_thread->tcb;
// 	param.tls_size = sizeof(struct tcb);
// 	param.child_tid = &new_thread->tid;
// 	param.parent_tid = &new_thread->tid;
// 	param.flags = 0;
// 	if (new_thread->attr.flags & PTHREAD_SCOPE_SYSTEM)
// 		param.flags |= THR_SYSTEM_SCOPE;
// 	if (new_thread->attr.sched_inherit == PTHREAD_INHERIT_SCHED)
// 		param.rtp = NULL;
// 	else {
// 		sched_param.sched_priority = new_thread->attr.prio;
// 		_schedparam_to_rtp(new_thread->attr.sched_policy,
// 			&sched_param, &rtp);
// 		param.rtp = &rtp;
// 	}
// 
// 	/* Schedule the new thread. */
// 	if (create_suspended) {
// 		SIGFILLSET(set);
// 		SIGDELSET(set, SIGTRAP);
// 		__sys_sigprocmask(SIG_SETMASK, &set, &oset);
// 		new_thread->sigmask = oset;
// 		SIGDELSET(new_thread->sigmask, SIGCANCEL);
// 	}
// 
// 	ret = thr_new(&param, sizeof(param));
// 
// 	if (ret != 0) {
// 		ret = errno;
// 		/*
// 		 * Translate EPROCLIM into well-known POSIX code EAGAIN.
// 		 */
// 		if (ret == EPROCLIM)
// 			ret = EAGAIN;
// 	}
// 
// 	if (create_suspended)
// 		__sys_sigprocmask(SIG_SETMASK, &oset, NULL);
// 
// 	if (ret != 0) {
// 		if (!locked)
// 			THR_THREAD_LOCK(curthread, new_thread);
// 		new_thread->state = PS_DEAD;
// 		new_thread->tid = TID_TERMINATED;
// 		new_thread->flags |= THR_FLAGS_DETACHED;
// 		new_thread->refcount--;
// 		if (new_thread->flags & THR_FLAGS_NEED_SUSPEND) {
// 			new_thread->cycle++;
// 			_thr_umtx_wake(&new_thread->cycle, INT_MAX, 0);
// 		}
// 		_thr_try_gc(curthread, new_thread); /* thread lock released */
// 		atomic_add_int(&_thread_active_threads, -1);
// 	} else if (locked) {
// 		if (cpusetp != NULL) {
// 			if (cpuset_setaffinity(CPU_LEVEL_WHICH, CPU_WHICH_TID,
// 				TID(new_thread), cpusetsize, cpusetp)) {
// 				ret = errno;
// 				/* kill the new thread */
// 				new_thread->force_exit = 1;
// 				new_thread->flags |= THR_FLAGS_DETACHED;
// 				_thr_try_gc(curthread, new_thread);
// 				 /* thread lock released */
// 				goto out;
// 			}
// 		}
// 
// 		_thr_report_creation(curthread, new_thread);
// 		THR_THREAD_UNLOCK(curthread, new_thread);
// 	}
// out:
// 	if (ret)
// 		(*thread) = 0;
// 	return (ret);
// }
// 
// static int
// create_stack(struct pthread_attr *pattr)
// {
// 	int ret;
// 
// 	/* Check if a stack was specified in the thread attributes: */
// 	if ((pattr->stackaddr_attr) != NULL) {
// 		pattr->guardsize_attr = 0;
// 		pattr->flags |= THR_STACK_USER;
// 		ret = 0;
// 	}
// 	else
// 		ret = _thr_stack_alloc(pattr);
// 	return (ret);
// }
// 
// static void
// thread_start(struct pthread *curthread)
// {
// 	sigset_t set;
// 
// 	if (curthread->attr.suspend == THR_CREATE_SUSPENDED)
// 		set = curthread->sigmask;
// 	_thr_signal_block_setup(curthread);
// 
// 	/*
// 	 * This is used as a serialization point to allow parent
// 	 * to report 'new thread' event to debugger or tweak new thread's
// 	 * attributes before the new thread does real-world work.
// 	 */
// 	THR_LOCK(curthread);
// 	THR_UNLOCK(curthread);
// 
// 	if (curthread->force_exit)
// 		_pthread_exit(PTHREAD_CANCELED);
// 
// 	if (curthread->attr.suspend == THR_CREATE_SUSPENDED) {
// #if 0
// 		/* Done in THR_UNLOCK() */
// 		_thr_ast(curthread);
// #endif
// 
// 		/*
// 		 * Parent thread have stored signal mask for us,
// 		 * we should restore it now.
// 		 */
// 		__sys_sigprocmask(SIG_SETMASK, &set, NULL);
// 	}
// 
// #ifdef _PTHREAD_FORCED_UNWIND
// 	curthread->unwind_stackend = (char *)curthread->attr.stackaddr_attr +
// 		curthread->attr.stacksize_attr;
// #endif
// 
// 	/* Run the current thread's start routine with argument: */
// 	_pthread_exit(curthread->start_routine(curthread->arg));
// 
// 	/* This point should never be reached. */
// 	PANIC("Thread has resumed after exit");
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_ctrdtr.c sha256=f01b2b9ac08efbdd935bc2efbc1b93d602075161905ddd548799fa51af69b833
// /*-
//  * Copyright (C) 2003 Jake Burkholder <jake@freebsd.org>
//  * Copyright (C) 2003 David Xu <davidxu@freebsd.org>
//  * Copyright (c) 2001,2003 Daniel Eischen <deischen@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Neither the name of the author nor the names of its contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include <sys/cdefs.h>
// #include <sys/types.h>
// #include <rtld_tls.h>
// 
// #include "thr_private.h"
// 
// struct tcb *
// _tcb_ctor(struct pthread *thread, int initial)
// {
// 	struct tcb *tcb;
// 
// 	if (initial)
// 		tcb = _tcb_get();
// 	else
// 		tcb = _rtld_allocate_tls(NULL, TLS_TCB_SIZE, TLS_TCB_ALIGN);
// 	if (tcb)
// 		tcb->tcb_thread = thread;
// 	return (tcb);
// }
// 
// void
// _tcb_dtor(struct tcb *tcb)
// {
// 
// 	_rtld_free_tls(tcb, TLS_TCB_SIZE, TLS_TCB_ALIGN);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_detach.c sha256=66f0fb5d1b171889abecfff07dac971d45f5cef2344ad9105c4aec45e81b7f91
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005 David Xu <davidxu@freebsd.org>
//  * Copyright (C) 2003 Daniel M. Eischen <deischen@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <sys/types.h>
// #include <errno.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_thr_detach, pthread_detach);
// __weak_reference(_thr_detach, _pthread_detach);
// 
// int
// _thr_detach(pthread_t pthread)
// {
// 	struct pthread *curthread = _get_curthread();
// 	int rval;
// 
// 	if (pthread == NULL)
// 		return (EINVAL);
// 
// 	if ((rval = _thr_find_thread(curthread, pthread,
// 			/*include dead*/1)) != 0) {
// 		return (rval);
// 	}
// 
// 	/* Check if the thread is already detached or has a joiner. */
// 	if ((pthread->flags & THR_FLAGS_DETACHED) != 0 ||
// 	    (pthread->joiner != NULL)) {
// 		THR_THREAD_UNLOCK(curthread, pthread);
// 		return (EINVAL);
// 	}
// 
// 	/* Flag the thread as detached. */
// 	pthread->flags |= THR_FLAGS_DETACHED;
// 	_thr_try_gc(curthread, pthread); /* thread lock released */
// 
// 	return (0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_equal.c sha256=23f37a51d86761efd93fe7db59c29889e3359c38caa46c9756ee03dc588606c6
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include "un-namespace.h"
// #include "thr_private.h"
// 
// __weak_reference(_thr_equal, pthread_equal);
// __weak_reference(_thr_equal, _pthread_equal);
// 
// int
// _thr_equal(pthread_t t1, pthread_t t2)
// {
// 	/* Compare the two thread pointers: */
// 	return (t1 == t2);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_event.c sha256=45e3fd566b58aaba6af41b65599e52188519e6dc130995745d5d16ef95932b4e
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005 David Xu
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "thr_private.h"
// 
// void
// _thread_bp_create(void)
// {
// }
// 
// void
// _thread_bp_death(void)
// {
// }
// 
// void
// _thr_report_creation(struct pthread *curthread, struct pthread *newthread)
// {
// 	curthread->event_buf.event = TD_CREATE;
// 	curthread->event_buf.th_p = (uintptr_t)newthread;
// 	curthread->event_buf.data = 0;
// 	THR_UMUTEX_LOCK(curthread, &_thr_event_lock);
// 	_thread_last_event = curthread;
// 	_thread_bp_create();
// 	_thread_last_event = NULL;
// 	THR_UMUTEX_UNLOCK(curthread, &_thr_event_lock);
// }
// 
// void
// _thr_report_death(struct pthread *curthread)
// {
// 	curthread->event_buf.event = TD_DEATH;
// 	curthread->event_buf.th_p = (uintptr_t)curthread;
// 	curthread->event_buf.data = 0;
// 	THR_UMUTEX_LOCK(curthread, &_thr_event_lock);
// 	_thread_last_event = curthread;
// 	_thread_bp_death();
// 	_thread_last_event = NULL;
// 	THR_UMUTEX_UNLOCK(curthread, &_thr_event_lock);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_exit.c sha256=b7938c75a973b698985141da538ec13af5f35d1f20551f46e9f4e57aae10b1c0
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995-1998 John Birrell <jb@cimlogic.com.au>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #ifdef _PTHREAD_FORCED_UNWIND
// #include <dlfcn.h>
// #endif
// #include <stdarg.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <sys/types.h>
// #include <sys/signalvar.h>
// #include "un-namespace.h"
// 
// #include "libc_private.h"
// #include "thr_private.h"
// 
// static void	exit_thread(void) __dead2;
// 
// __weak_reference(_Tthr_exit, pthread_exit);
// __weak_reference(_Tthr_exit, _pthread_exit);
// 
// #ifdef _PTHREAD_FORCED_UNWIND
// static int message_printed;
// 
// static void thread_unwind(void) __dead2;
// #ifdef PIC
// static void thread_uw_init(void);
// static _Unwind_Reason_Code thread_unwind_stop(int version,
// 	_Unwind_Action actions,
// 	uint64_t exc_class,
// 	struct _Unwind_Exception *exc_obj,
// 	struct _Unwind_Context *context, void *stop_parameter);
// /* unwind library pointers */
// static _Unwind_Reason_Code (*uwl_forcedunwind)(struct _Unwind_Exception *,
// 	_Unwind_Stop_Fn, void *);
// static uintptr_t (*uwl_getcfa)(struct _Unwind_Context *);
// 
// static void
// thread_uw_init(void)
// {
// 	static int inited = 0;
// 	Dl_info dli;
// 	void *handle;
// 	void *forcedunwind, *getcfa;
// 
// 	if (inited)
// 	    return;
// 	handle = RTLD_DEFAULT;
// 	if ((forcedunwind = dlsym(handle, "_Unwind_ForcedUnwind")) != NULL) {
// 	    if (dladdr(forcedunwind, &dli)) {
// 		/*
// 		 * Make sure the address is always valid by holding the library,
// 		 * also assume functions are in same library.
// 		 */
// 		if ((handle = dlopen(dli.dli_fname, RTLD_LAZY)) != NULL) {
// 		    forcedunwind = dlsym(handle, "_Unwind_ForcedUnwind");
// 		    getcfa = dlsym(handle, "_Unwind_GetCFA");
// 		    if (forcedunwind != NULL && getcfa != NULL) {
// 			uwl_getcfa = getcfa;
// 			atomic_store_rel_ptr((volatile void *)&uwl_forcedunwind,
// 				(uintptr_t)forcedunwind);
// 		    } else {
// 			dlclose(handle);
// 		    }
// 		}
// 	    }
// 	}
// 	inited = 1;
// }
// 
// _Unwind_Reason_Code
// _Unwind_ForcedUnwind(struct _Unwind_Exception *ex, _Unwind_Stop_Fn stop_func,
// 	void *stop_arg)
// {
// 	return (*uwl_forcedunwind)(ex, stop_func, stop_arg);
// }
// 
// uintptr_t
// _Unwind_GetCFA(struct _Unwind_Context *context)
// {
// 	return (*uwl_getcfa)(context);
// }
// #else
// #pragma weak _Unwind_GetCFA
// #pragma weak _Unwind_ForcedUnwind
// #endif /* PIC */
// 
// static void
// thread_unwind_cleanup(_Unwind_Reason_Code code __unused,
//     struct _Unwind_Exception *e __unused)
// {
// 	/*
// 	 * Specification said that _Unwind_Resume should not be used here,
// 	 * instead, user should rethrow the exception. For C++ user, they
// 	 * should put "throw" sentence in catch(...) block.
// 	 */
// 	PANIC("exception should be rethrown");
// }
// 
// static _Unwind_Reason_Code
// thread_unwind_stop(int version __unused, _Unwind_Action actions,
// 	uint64_t exc_class __unused,
// 	struct _Unwind_Exception *exc_obj __unused,
// 	struct _Unwind_Context *context, void *stop_parameter __unused)
// {
// 	struct pthread *curthread = _get_curthread();
// 	struct pthread_cleanup *cur;
// 	uintptr_t cfa;
// 	int done = 0;
// 
// 	/* XXX assume stack grows down to lower address */
// 
// 	cfa = _Unwind_GetCFA(context);
// 	if (actions & _UA_END_OF_STACK ||
// 	    cfa >= (uintptr_t)curthread->unwind_stackend) {
// 		done = 1;
// 	}
// 
// 	while ((cur = curthread->cleanup) != NULL &&
// 	       (done || (uintptr_t)cur <= cfa)) {
// 		__pthread_cleanup_pop_imp(1);
// 	}
// 
// 	if (done) {
// 		/* Tell libc that it should call non-trivial TLS dtors. */
// 		__cxa_thread_call_dtors();
// 
// 		exit_thread(); /* Never return! */
// 	}
// 
// 	return (_URC_NO_REASON);
// }
// 
// static void
// thread_unwind(void)
// {
// 	struct pthread  *curthread = _get_curthread();
// 
// 	curthread->ex.exception_class = 0;
// 	curthread->ex.exception_cleanup = thread_unwind_cleanup;
// 	_Unwind_ForcedUnwind(&curthread->ex, thread_unwind_stop, NULL);
// 	PANIC("_Unwind_ForcedUnwind returned");
// }
// 
// #endif
// 
// void
// _thread_exitf(const char *fname, int lineno, const char *fmt, ...)
// {
// 	va_list ap;
// 
// 	/* Write an error message to the standard error file descriptor: */
// 	_thread_printf(STDERR_FILENO, "Fatal error '");
// 
// 	va_start(ap, fmt);
// 	_thread_vprintf(STDERR_FILENO, fmt, ap);
// 	va_end(ap);
// 
// 	_thread_printf(STDERR_FILENO, "' at line %d in file %s (errno = %d)\n",
// 	    lineno, fname, errno);
// 
// 	abort();
// }
// 
// void
// _thread_exit(const char *fname, int lineno, const char *msg)
// {
// 
// 	_thread_exitf(fname, lineno, "%s", msg);
// }
// 
// void
// _Tthr_exit(void *status)
// {
// 	_pthread_exit_mask(status, NULL);
// }
// 
// void
// _pthread_exit_mask(void *status, sigset_t *mask)
// {
// 	struct pthread *curthread = _get_curthread();
// 
// 	/* Check if this thread is already in the process of exiting: */
// 	if (curthread->cancelling)
// 		PANIC("Thread %p has called "
// 		    "pthread_exit() from a destructor. POSIX 1003.1 "
// 		    "1996 s16.2.5.2 does not allow this!", curthread);
// 
// 	/* Flag this thread as exiting. */
// 	curthread->cancelling = 1;
// 	curthread->no_cancel = 1;
// 	curthread->cancel_async = 0;
// 	curthread->cancel_point = 0;
// 	if (mask != NULL)
// 		__sys_sigprocmask(SIG_SETMASK, mask, NULL);
// 	if (curthread->unblock_sigcancel) {
// 		sigset_t set;
// 
// 		curthread->unblock_sigcancel = 0;
// 		SIGEMPTYSET(set);
// 		SIGADDSET(set, SIGCANCEL);
// 		__sys_sigprocmask(SIG_UNBLOCK, mask, NULL);
// 	}
// 	
// 	/* Save the return value: */
// 	curthread->ret = status;
// #ifdef _PTHREAD_FORCED_UNWIND
// 
// #ifdef PIC
// 	thread_uw_init();
// 	if (uwl_forcedunwind != NULL) {
// #else
// 	if (_Unwind_ForcedUnwind != NULL) {
// #endif
// 		if (curthread->unwind_disabled) {
// 			if (message_printed == 0) {
// 				message_printed = 1;
// 				_thread_printf(2, "Warning: old _pthread_cleanup_push was called, "
// 				  	"stack unwinding is disabled.\n");
// 			}
// 			goto cleanup;
// 		}
// 		thread_unwind();
// 
// 	} else {
// cleanup:
// 		while (curthread->cleanup != NULL) {
// 			__pthread_cleanup_pop_imp(1);
// 		}
// 		__cxa_thread_call_dtors();
// 
// 		exit_thread();
// 	}
// 
// #else
// 	while (curthread->cleanup != NULL) {
// 		__pthread_cleanup_pop_imp(1);
// 	}
// 	__cxa_thread_call_dtors();
// 
// 	exit_thread();
// #endif /* _PTHREAD_FORCED_UNWIND */
// }
// 
// static void
// exit_thread(void)
// {
// 	struct pthread *curthread = _get_curthread();
// 
// 	free(curthread->name);
// 	curthread->name = NULL;
// 
// 	/* Check if there is thread specific data: */
// 	if (curthread->specific != NULL) {
// 		/* Run the thread-specific data destructors: */
// 		_thread_cleanupspecific();
// 	}
// 
// 	if (!_thr_isthreaded())
// 		exit(0);
// 
// 	if (atomic_fetchadd_int(&_thread_active_threads, -1) == 1) {
// 		exit(0);
// 		/* Never reach! */
// 	}
// 
// 	/* Tell malloc that the thread is exiting. */
// 	_malloc_thread_cleanup();
// 
// 	THR_LOCK(curthread);
// 	curthread->state = PS_DEAD;
// 	if (curthread->flags & THR_FLAGS_NEED_SUSPEND) {
// 		curthread->cycle++;
// 		_thr_umtx_wake(&curthread->cycle, INT_MAX, 0);
// 	}
// 	if (!curthread->force_exit && SHOULD_REPORT_EVENT(curthread, TD_DEATH))
// 		_thr_report_death(curthread);
// 	/*
// 	 * Thread was created with initial refcount 1, we drop the
// 	 * reference count to allow it to be garbage collected.
// 	 */
// 	curthread->refcount--;
// 	_thr_try_gc(curthread, curthread); /* thread lock released */
// 
// #if defined(_PTHREADS_INVARIANTS)
// 	if (THR_IN_CRITICAL(curthread))
// 		PANIC("thread %p exits with resources held!", curthread);
// #endif
// 	/*
// 	 * Kernel will do wakeup at the address, so joiner thread
// 	 * will be resumed if it is sleeping at the address.
// 	 */
// 	thr_exit(&curthread->tid);
// 	PANIC("thr_exit() returned");
// 	/* Never reach! */
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_fork.c sha256=eafefd324c16e6d6657a59224f7d055ca8aaa0cebd74fa18dcde570a5becaa8b
// /*
//  * Copyright (c) 2005 David Xu <davidxu@freebsd.org>
//  * Copyright (c) 2003 Daniel Eischen <deischen@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995-1998 John Birrell <jb@cimlogic.com.au>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  *
//  */
// 
// #include <sys/syscall.h>
// #include "namespace.h"
// #include <errno.h>
// #include <link.h>
// #include <string.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <spinlock.h>
// #include "un-namespace.h"
// 
// #include "libc_private.h"
// #include "rtld_lock.h"
// #include "thr_private.h"
// 
// __weak_reference(_thr_atfork, _pthread_atfork);
// __weak_reference(_thr_atfork, pthread_atfork);
// 
// bool _thr_after_fork = false;
// 
// int
// _thr_atfork(void (*prepare)(void), void (*parent)(void),
//     void (*child)(void))
// {
// 	struct pthread *curthread;
// 	struct pthread_atfork *af;
// 
// 	_thr_check_init();
// 
// 	if ((af = malloc(sizeof(struct pthread_atfork))) == NULL)
// 		return (ENOMEM);
// 
// 	curthread = _get_curthread();
// 	af->prepare = prepare;
// 	af->parent = parent;
// 	af->child = child;
// 	THR_CRITICAL_ENTER(curthread);
// 	_thr_rwl_wrlock(&_thr_atfork_lock);
// 	TAILQ_INSERT_TAIL(&_thr_atfork_list, af, qe);
// 	_thr_rwl_unlock(&_thr_atfork_lock);
// 	THR_CRITICAL_LEAVE(curthread);
// 	return (0);
// }
// 
// void
// __pthread_cxa_finalize(struct dl_phdr_info *phdr_info)
// {
// 	atfork_head    temp_list = TAILQ_HEAD_INITIALIZER(temp_list);
// 	struct pthread *curthread;
// 	struct pthread_atfork *af, *af1;
// 
// 	_thr_check_init();
// 
// 	curthread = _get_curthread();
// 	THR_CRITICAL_ENTER(curthread);
// 	_thr_rwl_wrlock(&_thr_atfork_lock);
// 	TAILQ_FOREACH_SAFE(af, &_thr_atfork_list, qe, af1) {
// 		if (__elf_phdr_match_addr(phdr_info, af->prepare) ||
// 		    __elf_phdr_match_addr(phdr_info, af->parent) ||
// 		    __elf_phdr_match_addr(phdr_info, af->child)) {
// 			TAILQ_REMOVE(&_thr_atfork_list, af, qe);
// 			TAILQ_INSERT_TAIL(&temp_list, af, qe);
// 		}
// 	}
// 	_thr_rwl_unlock(&_thr_atfork_lock);
// 	THR_CRITICAL_LEAVE(curthread);
// 	while ((af = TAILQ_FIRST(&temp_list)) != NULL) {
// 		TAILQ_REMOVE(&temp_list, af, qe);
// 		free(af);
// 	}
// 	_thr_tsd_unload(phdr_info);
// 	_thr_sigact_unload(phdr_info);
// }
// 
// enum thr_fork_mode {
// 	MODE_FORK,
// 	MODE_PDFORK,
// };
// 
// struct thr_fork_args {
// 	enum thr_fork_mode mode;
// 	void *fdp;
// 	int flags;
// };
// 
// static pid_t
// thr_fork_impl(const struct thr_fork_args *a)
// {
// 	struct pthread *curthread;
// 	struct pthread_atfork *af;
// 	pid_t ret;
// 	int errsave, cancelsave;
// 	int was_threaded;
// 	int rtld_locks[MAX_RTLD_LOCKS];
// 
// 	if (!_thr_is_inited()) {
// 		switch (a->mode) {
// 		case MODE_FORK:
// 			return (__sys_fork());
// 		case MODE_PDFORK:
// 			return (__sys_pdfork(a->fdp, a->flags));
// 		default:
// 			errno = EDOOFUS;
// 			return (-1);
// 		}
// 	}
// 
// 	curthread = _get_curthread();
// 	cancelsave = curthread->no_cancel;
// 	curthread->no_cancel = 1;
// 	_thr_rwl_rdlock(&_thr_atfork_lock);
// 
// 	/* Run down atfork prepare handlers. */
// 	TAILQ_FOREACH_REVERSE(af, &_thr_atfork_list, atfork_head, qe) {
// 		if (af->prepare != NULL)
// 			af->prepare();
// 	}
// 
// 	/*
// 	 * Block all signals until we reach a safe point.
// 	 */
// 	_thr_signal_block(curthread);
// 	_thr_signal_prefork();
// 
// 	/*
// 	 * All bets are off as to what should happen soon if the parent
// 	 * process was not so kindly as to set up pthread fork hooks to
// 	 * relinquish all running threads.
// 	 */
// 	if (_thr_isthreaded() != 0) {
// 		was_threaded = 1;
// 		__thr_malloc_prefork(curthread);
// 		_malloc_prefork();
// 		__thr_pshared_atfork_pre();
// 		_rtld_atfork_pre(rtld_locks);
// 	} else {
// 		was_threaded = 0;
// 	}
// 
// 	/*
// 	 * Fork a new process.
// 	 * There is no easy way to pre-resolve the __sys_fork symbol
// 	 * without performing the fork.  Use the syscall(2)
// 	 * indirection, the syscall symbol is resolved in
// 	 * _thr_rtld_init() with side-effect free call.
// 	 */
// 	switch (a->mode) {
// 	case MODE_FORK:
// 		ret = syscall(SYS_fork);
// 		break;
// 	case MODE_PDFORK:
// 		ret = syscall(SYS_pdfork, a->fdp, a->flags);
// 		break;
// 	default:
// 		ret = -1;
// 		errno = EDOOFUS;
// 		break;
// 	}
// 
// 	if (ret == 0) {
// 		/* Child process */
// 		errsave = errno;
// 		curthread->cancel_pending = 0;
// 		curthread->flags &= ~(THR_FLAGS_NEED_SUSPEND|THR_FLAGS_DETACHED);
// 
// 		/*
// 		 * Thread list will be reinitialized, and later we call
// 		 * _libpthread_init(), it will add us back to list.
// 		 */
// 		curthread->tlflags &= ~TLFLAGS_IN_TDLIST;
// 
// 		/* before thr_self() */
// 		if (was_threaded)
// 			__thr_malloc_postfork(curthread);
// 
// 		/* child is a new kernel thread. */
// 		thr_self(&curthread->tid);
// 
// 		/* clear other threads locked us. */
// 		_thr_umutex_init(&curthread->lock);
// 		_mutex_fork(curthread);
// 
// 		_thr_signal_postfork_child();
// 
// 		if (was_threaded) {
// 			_thr_after_fork = true;
// 			_rtld_atfork_post(rtld_locks);
// 			_thr_after_fork = false;
// 			__thr_pshared_atfork_post();
// 		}
// 		_thr_setthreaded(0);
// 
// 		/* reinitalize library. */
// 		_libpthread_init(curthread);
// 
// 		/* atfork is reinitialized by _libpthread_init()! */
// 		_thr_rwl_rdlock(&_thr_atfork_lock);
// 
// 		if (was_threaded) {
// 			_thr_setthreaded(1);
// 			_malloc_postfork();
// 			_thr_setthreaded(0);
// 		}
// 
// 		/* Ready to continue, unblock signals. */ 
// 		_thr_signal_unblock(curthread);
// 
// 		/* Run down atfork child handlers. */
// 		TAILQ_FOREACH(af, &_thr_atfork_list, qe) {
// 			if (af->child != NULL)
// 				af->child();
// 		}
// 		_thr_rwlock_unlock(&_thr_atfork_lock);
// 		curthread->no_cancel = cancelsave;
// 	} else {
// 		/* Parent process */
// 		errsave = errno;
// 
// 		_thr_signal_postfork();
// 
// 		if (was_threaded) {
// 			__thr_malloc_postfork(curthread);
// 			_rtld_atfork_post(rtld_locks);
// 			__thr_pshared_atfork_post();
// 			_malloc_postfork();
// 		}
// 
// 		/* Ready to continue, unblock signals. */ 
// 		_thr_signal_unblock(curthread);
// 
// 		/* Run down atfork parent handlers. */
// 		TAILQ_FOREACH(af, &_thr_atfork_list, qe) {
// 			if (af->parent != NULL)
// 				af->parent();
// 		}
// 
// 		_thr_rwlock_unlock(&_thr_atfork_lock);
// 		curthread->no_cancel = cancelsave;
// 		/* test async cancel */
// 		if (curthread->cancel_async)
// 			_thr_testcancel(curthread);
// 	}
// 	errno = errsave;
// 
// 	return (ret);
// }
// 
// __weak_reference(__thr_fork, _fork);
// 
// pid_t
// __thr_fork(void)
// {
// 	struct thr_fork_args a;
// 
// 	a.mode = MODE_FORK;
// 	return (thr_fork_impl(&a));
// }
// 
// pid_t
// __thr_pdfork(int *fdp, int flags)
// {
// 	struct thr_fork_args a;
// 
// 	a.mode = MODE_PDFORK;
// 	a.fdp = fdp;
// 	a.flags = flags;
// 	return (thr_fork_impl(&a));
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_getcpuclockid.c sha256=ba6698d416a8c4254e95c2b7266b361899272f97598121ef3c87fee13b6f47f0
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2008 David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <pthread.h>
// #include <sys/time.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_pthread_getcpuclockid, pthread_getcpuclockid);
// 
// int
// _pthread_getcpuclockid(pthread_t pthread, clockid_t *clock_id)
// {
// 
// 	if (pthread == NULL)
// 		return (EINVAL);
// 
// 	if (clock_getcpuclockid2(TID(pthread), CPUCLOCK_WHICH_TID, clock_id))
// 		return (errno);
// 	return (0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_getprio.c sha256=aba01debfd1559d6ef0964b04de07b1f7cd6821670019c9aa0943b03cc091b5f
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <pthread.h>
// #include "un-namespace.h"
// #include "thr_private.h"
// 
// __weak_reference(_pthread_getprio, pthread_getprio);
// 
// int
// _pthread_getprio(pthread_t pthread)
// {
// 	int policy, ret;
// 	struct sched_param param;
// 
// 	if ((ret = _pthread_getschedparam(pthread, &policy, &param)) == 0)
// 		ret = param.sched_priority;
// 	else {
// 		/* Invalid thread: */
// 		errno = ret;
// 		ret = -1;
// 	}
// 
// 	/* Return the thread priority or an error status: */
// 	return (ret);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_getthreadid_np.c sha256=df233529e8f3b61b2139d4fa21ceb9fc7fb3704288e126caedbc23075f4e3a5a
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2011 Jung-uk Kim <jkim@FreeBSD.org>
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_thr_getthreadid_np, _pthread_getthreadid_np);
// __weak_reference(_thr_getthreadid_np, pthread_getthreadid_np);
// 
// /*
//  * Provide the equivelant to AIX pthread_getthreadid_np() function.
//  */
// int
// _thr_getthreadid_np(void)
// {
// 	struct pthread *curthread;
// 
// 	_thr_check_init();
// 	curthread = _get_curthread();
// 	return (TID(curthread));
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_info.c sha256=83b14d644fb0cc60d7b620cacbf509496d9d028c2777c5bb0b8b01210957efba
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995-1998 John Birrell <jb@cimlogic.com.au>
//  * Copyright (c) 2018 The FreeBSD Foundation
//  * All rights reserved.
//  *
//  * Portions of this software were developed by Konstantin Belousov
//  * under sponsorship from the FreeBSD Foundation.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <sys/errno.h>
// #include <stdlib.h>
// #include <string.h>
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// static void
// thr_set_name_np(struct pthread *thread, char **tmp_name)
// {
// 
// 	free(thread->name);
// 	thread->name = *tmp_name;
// 	*tmp_name = NULL;
// }
// 
// /* Set the thread name. */
// __weak_reference(_pthread_setname_np, pthread_setname_np);
// int
// _pthread_setname_np(pthread_t thread, const char *name)
// {
// 	struct pthread *curthread;
// 	char *tmp_name;
// 	int res;
// 
// 	if (name != NULL) {
// 		tmp_name = strdup(name);
// 		if (tmp_name == NULL)
// 			return (ENOMEM);
// 	} else {
// 		tmp_name = NULL;
// 	}
// 	curthread = _get_curthread();
// 	if (curthread == thread) {
// 		res = 0;
// 		THR_THREAD_LOCK(curthread, thread);
// 		if (thr_set_name(thread->tid, name) == -1)
// 			res = errno;
// 		else
// 			thr_set_name_np(thread, &tmp_name);
// 		THR_THREAD_UNLOCK(curthread, thread);
// 	} else {
// 		res = ESRCH;
// 		if (_thr_find_thread(curthread, thread, 0) == 0) {
// 			if (thread->state != PS_DEAD) {
// 				if (thr_set_name(thread->tid, name) == -1) {
// 					res = errno;
// 				} else {
// 					thr_set_name_np(thread, &tmp_name);
// 					res = 0;
// 				}
// 			}
// 			THR_THREAD_UNLOCK(curthread, thread);
// 		}
// 	}
// 	free(tmp_name);
// 	return (res);
// }
// 
// /* Set the thread name for debug. */
// __weak_reference(_pthread_set_name_np, pthread_set_name_np);
// void
// _pthread_set_name_np(pthread_t thread, const char *name)
// {
// 	(void)_pthread_setname_np(thread, name);
// }
// 
// static void
// thr_get_name_np(struct pthread *thread, char *buf, size_t len)
// {
// 
// 	if (thread->name != NULL)
// 		strlcpy(buf, thread->name, len);
// 	else if (len > 0)
// 		buf[0] = '\0';
// }
// 
// __weak_reference(_thr_getname_np, pthread_getname_np);
// __weak_reference(_thr_getname_np, _pthread_getname_np);
// int
// _thr_getname_np(pthread_t thread, char *buf, size_t len)
// {
// 	struct pthread *curthread;
// 	int res;
// 
// 	res = 0;
// 	curthread = _get_curthread();
// 	if (curthread == thread) {
// 		THR_THREAD_LOCK(curthread, thread);
// 		thr_get_name_np(thread, buf, len);
// 		THR_THREAD_UNLOCK(curthread, thread);
// 	} else {
// 		if (_thr_find_thread(curthread, thread, 0) == 0) {
// 			if (thread->state != PS_DEAD)
// 				thr_get_name_np(thread, buf, len);
// 			else
// 				res = ESRCH;
// 			THR_THREAD_UNLOCK(curthread, thread);
// 		} else {
// 			res = ESRCH;
// 			if (len > 0)
// 				buf[0] = '\0';
// 		}
// 	}
// 	return (res);
// }
// 
// __weak_reference(_pthread_get_name_np, pthread_get_name_np);
// void
// _pthread_get_name_np(pthread_t thread, char *buf, size_t len)
// {
// 	(void)_thr_getname_np(thread, buf, len);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_join.c sha256=1d982a308b2d3b3ffefbf7b88dd25e9fbccdb5f4220c1a4d78666432b305c1ba
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005, David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// int	_pthread_peekjoin_np(pthread_t pthread, void **thread_return);
// int	_pthread_timedjoin_np(pthread_t pthread, void **thread_return,
// 	    const struct timespec *abstime);
// static int join_common(pthread_t, void **, const struct timespec *, bool peek);
// 
// __weak_reference(_thr_join, pthread_join);
// __weak_reference(_thr_join, _pthread_join);
// __weak_reference(_pthread_timedjoin_np, pthread_timedjoin_np);
// __weak_reference(_pthread_peekjoin_np, pthread_peekjoin_np);
// 
// static void backout_join(void *arg)
// {
// 	struct pthread *pthread = (struct pthread *)arg;
// 	struct pthread *curthread = _get_curthread();
// 
// 	THR_THREAD_LOCK(curthread, pthread);
// 	pthread->joiner = NULL;
// 	THR_THREAD_UNLOCK(curthread, pthread);
// }
// 
// int
// _thr_join(pthread_t pthread, void **thread_return)
// {
// 	return (join_common(pthread, thread_return, NULL, false));
// }
// 
// int
// _pthread_timedjoin_np(pthread_t pthread, void **thread_return,
// 	const struct timespec *abstime)
// {
// 	if (abstime == NULL || abstime->tv_sec < 0 || abstime->tv_nsec < 0 ||
// 	    abstime->tv_nsec >= 1000000000)
// 		return (EINVAL);
// 
// 	return (join_common(pthread, thread_return, abstime, false));
// }
// 
// int
// _pthread_peekjoin_np(pthread_t pthread, void **thread_return)
// {
// 	return (join_common(pthread, thread_return, NULL, true));
// }
// 
// /*
//  * Cancellation behavior:
//  *   if the thread is canceled, joinee is not recycled.
//  */
// static int
// join_common(pthread_t pthread, void **thread_return,
//     const struct timespec *abstime, bool peek)
// {
// 	struct pthread *curthread = _get_curthread();
// 	struct timespec ts, ts2, *tsp;
// 	void *tmp;
// 	long tid;
// 	int ret;
// 
// 	if (pthread == NULL)
// 		return (EINVAL);
// 
// 	if (pthread == curthread)
// 		return (EDEADLK);
// 
// 	if ((ret = _thr_find_thread(curthread, pthread, 1)) != 0)
// 		return (ESRCH);
// 
// 	if ((pthread->flags & THR_FLAGS_DETACHED) != 0) {
// 		ret = EINVAL;
// 	} else if (pthread->joiner != NULL) {
// 		/* Multiple joiners are not supported. */
// 		ret = ENOTSUP;
// 	}
// 	if (ret != 0) {
// 		THR_THREAD_UNLOCK(curthread, pthread);
// 		return (ret);
// 	}
// 
// 	/* Only peek into status, do not gc the thread. */
// 	if (peek) {
// 		if (pthread->tid != TID_TERMINATED)
// 			ret = EBUSY;
// 		else if (thread_return != NULL)
// 			*thread_return = pthread->ret;
// 		THR_THREAD_UNLOCK(curthread, pthread);
// 		return (ret);
// 	}
// 
// 	/* Set the running thread to be the joiner: */
// 	pthread->joiner = curthread;
// 
// 	THR_THREAD_UNLOCK(curthread, pthread);
// 
// 	THR_CLEANUP_PUSH(curthread, backout_join, pthread);
// 	_thr_cancel_enter(curthread);
// 
// 	tid = pthread->tid;
// 	while (pthread->tid != TID_TERMINATED) {
// 		_thr_testcancel(curthread);
// 		if (abstime != NULL) {
// 			clock_gettime(CLOCK_REALTIME, &ts);
// 			TIMESPEC_SUB(&ts2, abstime, &ts);
// 			if (ts2.tv_sec < 0) {
// 				ret = ETIMEDOUT;
// 				break;
// 			}
// 			tsp = &ts2;
// 		} else
// 			tsp = NULL;
// 		ret = _thr_umtx_wait(&pthread->tid, tid, tsp);
// 		if (ret == ETIMEDOUT)
// 			break;
// 	}
// 
// 	_thr_cancel_leave(curthread, 0);
// 	THR_CLEANUP_POP(curthread, 0);
// 
// 	if (ret == ETIMEDOUT) {
// 		THR_THREAD_LOCK(curthread, pthread);
// 		pthread->joiner = NULL;
// 		THR_THREAD_UNLOCK(curthread, pthread);
// 	} else {
// 		ret = 0;
// 		tmp = pthread->ret;
// 		THR_THREAD_LOCK(curthread, pthread);
// 		pthread->flags |= THR_FLAGS_DETACHED;
// 		pthread->joiner = NULL;
// 		_thr_try_gc(curthread, pthread); /* thread lock released */
// 
// 		if (thread_return != NULL)
// 			*thread_return = tmp;
// 	}
// 	return (ret);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_kern.c sha256=e341404f2ee171cb9287ae397aaab32899b299edf53f0feadfafc377446b71fb
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005 David Xu <davidxu@freebsd.org>
//  * Copyright (C) 2003 Daniel M. Eischen <deischen@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include <sys/cdefs.h>
// #include <sys/types.h>
// #include <sys/signalvar.h>
// #include <sys/rtprio.h>
// #include <sys/mman.h>
// #include <pthread.h>
// 
// #include "thr_private.h"
// 
// /*#define DEBUG_THREAD_KERN */
// #ifdef DEBUG_THREAD_KERN
// #define DBG_MSG		stdout_debug
// #else
// #define DBG_MSG(x...)
// #endif
// 
// static struct umutex	addr_lock;
// static struct wake_addr *wake_addr_head;
// static struct wake_addr default_wake_addr;
// 
// /*
//  * This is called when the first thread (other than the initial
//  * thread) is created.
//  */
// void
// _thr_setthreaded(int threaded)
// {
// 	__isthreaded = threaded;
// }
// 
// void
// _thr_assert_lock_level(void)
// {
// 	PANIC("locklevel <= 0");
// }
// 
// int
// _rtp_to_schedparam(const struct rtprio *rtp, int *policy,
// 	struct sched_param *param)
// {
// 	switch(rtp->type) {
// 	case RTP_PRIO_REALTIME:
// 		*policy = SCHED_RR;
// 		param->sched_priority = RTP_PRIO_MAX - rtp->prio;
// 		break;
// 	case RTP_PRIO_FIFO:
// 		*policy = SCHED_FIFO;
// 		param->sched_priority = RTP_PRIO_MAX - rtp->prio;
// 		break;
// 	default:
// 		*policy = SCHED_OTHER;
// 		param->sched_priority = 0;
// 		break;
// 	}
// 	return (0);
// }
// 
// int
// _schedparam_to_rtp(int policy, const struct sched_param *param,
// 	struct rtprio *rtp)
// {
// 	switch(policy) {
// 	case SCHED_RR:
// 		rtp->type = RTP_PRIO_REALTIME;
// 		rtp->prio = RTP_PRIO_MAX - param->sched_priority;
// 		break;
// 	case SCHED_FIFO:
// 		rtp->type = RTP_PRIO_FIFO;
// 		rtp->prio = RTP_PRIO_MAX - param->sched_priority;
// 		break;
// 	case SCHED_OTHER:
// 	default:
// 		rtp->type = RTP_PRIO_NORMAL;
// 		rtp->prio = 0;
// 		break;
// 	}
// 	return (0);
// }
// 
// int
// _thr_getscheduler(lwpid_t lwpid, int *policy, struct sched_param *param)
// {
// 	struct rtprio rtp;
// 	int ret;
// 
// 	ret = rtprio_thread(RTP_LOOKUP, lwpid, &rtp);
// 	if (ret == -1)
// 		return (ret);
// 	_rtp_to_schedparam(&rtp, policy, param);
// 	return (0);
// }
// 
// int
// _thr_setscheduler(lwpid_t lwpid, int policy, const struct sched_param *param)
// {
// 	struct rtprio rtp;
// 
// 	_schedparam_to_rtp(policy, param, &rtp);
// 	return (rtprio_thread(RTP_SET, lwpid, &rtp));
// }
// 
// void
// _thr_wake_addr_init(void)
// {
// 	_thr_umutex_init(&addr_lock);
// 	wake_addr_head = NULL;
// }
// 
// /*
//  * Allocate wake-address, the memory area is never freed after
//  * allocated, this becauses threads may be referencing it.
//  */
// struct wake_addr *
// _thr_alloc_wake_addr(void)
// {
// 	struct pthread *curthread;
// 	struct wake_addr *p;
// 
// 	if (_thr_initial == NULL) {
// 		return &default_wake_addr;
// 	}
// 
// 	curthread = _get_curthread();
// 
// 	THR_LOCK_ACQUIRE(curthread, &addr_lock);
// 	if (wake_addr_head == NULL) {
// 		unsigned i;
// 		unsigned pagesize = getpagesize();
// 		struct wake_addr *pp = (struct wake_addr *)
// 			mmap(NULL, pagesize, PROT_READ|PROT_WRITE,
// 			MAP_ANON|MAP_PRIVATE, -1, 0);
// 		for (i = 1; i < pagesize/sizeof(struct wake_addr); ++i)
// 			pp[i].link = &pp[i+1];
// 		pp[i-1].link = NULL;	
// 		wake_addr_head = &pp[1];
// 		p = &pp[0];
// 	} else {
// 		p = wake_addr_head;
// 		wake_addr_head = p->link;
// 	}
// 	THR_LOCK_RELEASE(curthread, &addr_lock);
// 	p->value = 0;
// 	return (p);
// }
// 
// void
// _thr_release_wake_addr(struct wake_addr *wa)
// {
// 	struct pthread *curthread = _get_curthread();
// 
// 	if (wa == &default_wake_addr)
// 		return;
// 	THR_LOCK_ACQUIRE(curthread, &addr_lock);
// 	wa->link = wake_addr_head;
// 	wake_addr_head = wa;
// 	THR_LOCK_RELEASE(curthread, &addr_lock);
// }
// 
// /* Sleep on thread wakeup address */
// int
// _thr_sleep(struct pthread *curthread, int clockid,
// 	const struct timespec *abstime)
// {
// 
// 	if (curthread->wake_addr->value != 0)
// 		return (0);
// 
// 	return _thr_umtx_timedwait_uint(&curthread->wake_addr->value, 0,
//                  clockid, abstime, 0);
// }
// 
// void
// _thr_wake_all(unsigned int *waddrs[], int count)
// {
// 	int i;
// 
// 	for (i = 0; i < count; ++i)
// 		*waddrs[i] = 1;
// 	_umtx_op(waddrs, UMTX_OP_NWAKE_PRIVATE, count, NULL, NULL);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_kill.c sha256=b5b6675b18f945d84a7e0b75436a017d1a43fa5769b588aeb6f08b534af2d182
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1997 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <signal.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_Tthr_kill, _pthread_kill);
// __weak_reference(_Tthr_kill, pthread_kill);
// 
// int
// _Tthr_kill(pthread_t pthread, int sig)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	/* Check for invalid signal numbers: */
// 	if (sig < 0 || sig > _SIG_MAXSIG)
// 		/* Invalid signal: */
// 		return (EINVAL);
// 
// 	curthread = _get_curthread();
// 
// 	/*
// 	 * Ensure the thread is in the list of active threads, and the
// 	 * signal is valid (signal 0 specifies error checking only) and
// 	 * not being ignored:
// 	 */
// 	if (curthread == pthread) {
// 		if (sig > 0)
// 			_thr_send_sig(pthread, sig);
// 		ret = 0;
// 	} else if ((ret = _thr_find_thread(curthread, pthread,
// 	    /*include dead*/0)) == 0) {
// 		if (sig > 0)
// 			_thr_send_sig(pthread, sig);
// 		THR_THREAD_UNLOCK(curthread, pthread);
// 	}
// 
// 	/* Return the completion status: */
// 	return (ret);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_list.c sha256=3c14406c8e848c326edfba5b13343fc0a339fe1dc55bca7a9442f6d98d82c94c
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005 David Xu <davidxu@freebsd.org>
//  * Copyright (C) 2003 Daniel M. Eischen <deischen@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include <sys/cdefs.h>
// #include <sys/types.h>
// #include <sys/queue.h>
// 
// #include <stdlib.h>
// #include <string.h>
// #include <pthread.h>
// 
// #include "libc_private.h"
// #include "thr_private.h"
// #include "static_tls.h"
// 
// /*#define DEBUG_THREAD_LIST */
// #ifdef DEBUG_THREAD_LIST
// #define DBG_MSG		stdout_debug
// #else
// #define DBG_MSG(x...)
// #endif
// 
// #define MAX_THREADS		100000
// 
// /*
//  * Define a high water mark for the maximum number of threads that
//  * will be cached.  Once this level is reached, any extra threads
//  * will be free()'d.
//  */
// #define	MAX_CACHED_THREADS	100
// 
// /*
//  * We've got to keep track of everything that is allocated, not only
//  * to have a speedy free list, but also so they can be deallocated
//  * after a fork().
//  */
// static TAILQ_HEAD(, pthread)	free_threadq;
// static struct umutex		free_thread_lock = DEFAULT_UMUTEX;
// static struct umutex		tcb_lock = DEFAULT_UMUTEX;
// static int			free_thread_count = 0;
// static int			inited = 0;
// static int			total_threads;
// 
// LIST_HEAD(thread_hash_head, pthread);
// #define HASH_QUEUES	128
// static struct thread_hash_head	thr_hashtable[HASH_QUEUES];
// #define	THREAD_HASH(thrd)	(((unsigned long)thrd >> 8) % HASH_QUEUES)
// 
// static void thr_destroy(struct pthread *curthread, struct pthread *thread);
// 
// void
// _thr_list_init(void)
// {
// 	int i;
// 
// 	_gc_count = 0;
// 	total_threads = 1;
// 	_thr_urwlock_init(&_thr_list_lock);
// 	TAILQ_INIT(&_thread_list);
// 	TAILQ_INIT(&free_threadq);
// 	_thr_umutex_init(&free_thread_lock);
// 	_thr_umutex_init(&tcb_lock);
// 	if (inited) {
// 		for (i = 0; i < HASH_QUEUES; ++i)
// 			LIST_INIT(&thr_hashtable[i]);
// 	}
// 	inited = 1;
// }
// 
// void
// _thr_gc(struct pthread *curthread)
// {
// 	struct pthread *td, *td_next;
// 	TAILQ_HEAD(, pthread) worklist;
// 
// 	TAILQ_INIT(&worklist);
// 	THREAD_LIST_WRLOCK(curthread);
// 
// 	/* Check the threads waiting for GC. */
// 	TAILQ_FOREACH_SAFE(td, &_thread_gc_list, gcle, td_next) {
// 		if (td->tid != TID_TERMINATED) {
// 			/* make sure we are not still in userland */
// 			continue;
// 		}
// 		_thr_stack_free(&td->attr);
// 		THR_GCLIST_REMOVE(td);
// 		TAILQ_INSERT_HEAD(&worklist, td, gcle);
// 	}
// 	THREAD_LIST_UNLOCK(curthread);
// 
// 	while ((td = TAILQ_FIRST(&worklist)) != NULL) {
// 		TAILQ_REMOVE(&worklist, td, gcle);
// 		/*
// 		 * XXX we don't free initial thread, because there might
// 		 * have some code referencing initial thread.
// 		 */
// 		if (td == _thr_initial) {
// 			DBG_MSG("Initial thread won't be freed\n");
// 			continue;
// 		}
// 
// 		_thr_free(curthread, td);
// 	}
// }
// 
// struct pthread *
// _thr_alloc(struct pthread *curthread)
// {
// 	struct pthread	*thread = NULL;
// 	struct tcb	*tcb;
// 
// 	if (curthread != NULL) {
// 		if (GC_NEEDED())
// 			_thr_gc(curthread);
// 		if (free_thread_count > 0) {
// 			THR_LOCK_ACQUIRE(curthread, &free_thread_lock);
// 			if ((thread = TAILQ_FIRST(&free_threadq)) != NULL) {
// 				TAILQ_REMOVE(&free_threadq, thread, tle);
// 				free_thread_count--;
// 			}
// 			THR_LOCK_RELEASE(curthread, &free_thread_lock);
// 		}
// 	}
// 	if (thread == NULL) {
// 		if (total_threads > MAX_THREADS)
// 			return (NULL);
// 		atomic_fetchadd_int(&total_threads, 1);
// 		thread = calloc(1, sizeof(struct pthread));
// 		if (thread == NULL) {
// 			atomic_fetchadd_int(&total_threads, -1);
// 			return (NULL);
// 		}
// 		if ((thread->sleepqueue = _sleepq_alloc()) == NULL ||
// 		    (thread->wake_addr = _thr_alloc_wake_addr()) == NULL) {
// 			thr_destroy(curthread, thread);
// 			atomic_fetchadd_int(&total_threads, -1);
// 			return (NULL);
// 		}
// 	} else {
// 		bzero(&thread->_pthread_startzero, 
// 			__rangeof(struct pthread, _pthread_startzero, _pthread_endzero));
// 	}
// 	if (curthread != NULL) {
// 		THR_LOCK_ACQUIRE(curthread, &tcb_lock);
// 		tcb = _tcb_ctor(thread, 0 /* not initial tls */);
// 		THR_LOCK_RELEASE(curthread, &tcb_lock);
// 	} else {
// 		tcb = _tcb_ctor(thread, 1 /* initial tls */);
// 	}
// 	if (tcb != NULL) {
// 		thread->tcb = tcb;
// 	} else {
// 		thr_destroy(curthread, thread);
// 		atomic_fetchadd_int(&total_threads, -1);
// 		thread = NULL;
// 	}
// 	return (thread);
// }
// 
// void
// _thr_free(struct pthread *curthread, struct pthread *thread)
// {
// 	DBG_MSG("Freeing thread %p\n", thread);
// 
// 	/*
// 	 * Always free tcb, as we only know it is part of RTLD TLS
// 	 * block, but don't know its detail and can not assume how
// 	 * it works, so better to avoid caching it here.
// 	 */
// 	if (curthread != NULL) {
// 		THR_LOCK_ACQUIRE(curthread, &tcb_lock);
// 		_tcb_dtor(thread->tcb);
// 		THR_LOCK_RELEASE(curthread, &tcb_lock);
// 	} else {
// 		_tcb_dtor(thread->tcb);
// 	}
// 	thread->tcb = NULL;
// 	if ((curthread == NULL) || (free_thread_count >= MAX_CACHED_THREADS)) {
// 		thr_destroy(curthread, thread);
// 		atomic_fetchadd_int(&total_threads, -1);
// 	} else {
// 		/*
// 		 * Add the thread to the free thread list, this also avoids
// 		 * pthread id is reused too quickly, may help some buggy apps.
// 		 */
// 		THR_LOCK_ACQUIRE(curthread, &free_thread_lock);
// 		TAILQ_INSERT_TAIL(&free_threadq, thread, tle);
// 		free_thread_count++;
// 		THR_LOCK_RELEASE(curthread, &free_thread_lock);
// 	}
// }
// 
// static void
// thr_destroy(struct pthread *curthread __unused, struct pthread *thread)
// {
// 	if (thread->sleepqueue != NULL)
// 		_sleepq_free(thread->sleepqueue);
// 	if (thread->wake_addr != NULL)
// 		_thr_release_wake_addr(thread->wake_addr);
// 	free(thread);
// }
// 
// /*
//  * Add the thread to the list of all threads and increment
//  * number of active threads.
//  */
// void
// _thr_link(struct pthread *curthread, struct pthread *thread)
// {
// 	THREAD_LIST_WRLOCK(curthread);
// 	THR_LIST_ADD(thread);
// 	THREAD_LIST_UNLOCK(curthread);
// 	atomic_add_int(&_thread_active_threads, 1);
// }
// 
// /*
//  * Remove an active thread.
//  */
// void
// _thr_unlink(struct pthread *curthread, struct pthread *thread)
// {
// 	THREAD_LIST_WRLOCK(curthread);
// 	THR_LIST_REMOVE(thread);
// 	THREAD_LIST_UNLOCK(curthread);
// 	atomic_add_int(&_thread_active_threads, -1);
// }
// 
// void
// _thr_hash_add(struct pthread *thread)
// {
// 	struct thread_hash_head *head;
// 
// 	head = &thr_hashtable[THREAD_HASH(thread)];
// 	LIST_INSERT_HEAD(head, thread, hle);
// }
// 
// void
// _thr_hash_remove(struct pthread *thread)
// {
// 	LIST_REMOVE(thread, hle);
// }
// 
// struct pthread *
// _thr_hash_find(struct pthread *thread)
// {
// 	struct pthread *td;
// 	struct thread_hash_head *head;
// 
// 	head = &thr_hashtable[THREAD_HASH(thread)];
// 	LIST_FOREACH(td, head, hle) {
// 		if (td == thread)
// 			return (thread);
// 	}
// 	return (NULL);
// }
// 
// /*
//  * Find a thread in the linked list of active threads and add a reference
//  * to it.  Threads with positive reference counts will not be deallocated
//  * until all references are released.
//  */
// int
// _thr_ref_add(struct pthread *curthread, struct pthread *thread,
//     int include_dead)
// {
// 	int ret;
// 
// 	if (thread == NULL)
// 		/* Invalid thread: */
// 		return (EINVAL);
// 
// 	if ((ret = _thr_find_thread(curthread, thread, include_dead)) == 0) {
// 		thread->refcount++;
// 		THR_CRITICAL_ENTER(curthread);
// 		THR_THREAD_UNLOCK(curthread, thread);
// 	}
// 
// 	/* Return zero if the thread exists: */
// 	return (ret);
// }
// 
// void
// _thr_ref_delete(struct pthread *curthread, struct pthread *thread)
// {
// 	THR_THREAD_LOCK(curthread, thread);
// 	thread->refcount--;
// 	_thr_try_gc(curthread, thread);
// 	THR_CRITICAL_LEAVE(curthread);
// }
// 
// /* entered with thread lock held, exit with thread lock released */
// void
// _thr_try_gc(struct pthread *curthread, struct pthread *thread)
// {
// 	if (THR_SHOULD_GC(thread)) {
// 		THR_REF_ADD(curthread, thread);
// 		THR_THREAD_UNLOCK(curthread, thread);
// 		THREAD_LIST_WRLOCK(curthread);
// 		THR_THREAD_LOCK(curthread, thread);
// 		THR_REF_DEL(curthread, thread);
// 		if (THR_SHOULD_GC(thread)) {
// 			THR_LIST_REMOVE(thread);
// 			THR_GCLIST_ADD(thread);
// 		}
// 		THR_THREAD_UNLOCK(curthread, thread);
// 		THREAD_LIST_UNLOCK(curthread);
// 	} else {
// 		THR_THREAD_UNLOCK(curthread, thread);
// 	}
// }
// 
// /* return with thread lock held if thread is found */
// int
// _thr_find_thread(struct pthread *curthread, struct pthread *thread,
//     int include_dead)
// {
// 	struct pthread *pthread;
// 	int ret;
// 
// 	if (thread == NULL)
// 		return (EINVAL);
// 
// 	ret = 0;
// 	THREAD_LIST_RDLOCK(curthread);
// 	pthread = _thr_hash_find(thread);
// 	if (pthread) {
// 		THR_THREAD_LOCK(curthread, pthread);
// 		if (include_dead == 0 && pthread->state == PS_DEAD) {
// 			THR_THREAD_UNLOCK(curthread, pthread);
// 			ret = ESRCH;
// 		}
// 	} else {
// 		ret = ESRCH;
// 	}
// 	THREAD_LIST_UNLOCK(curthread);
// 	return (ret);
// }
// 
// #include "pthread_tls.h"
// 
// static void
// thr_distribute_static_tls(uintptr_t tlsbase, void *src, size_t len,
//     size_t total_len)
// {
// 
// 	memcpy((void *)tlsbase, src, len);
// 	memset((char *)tlsbase + len, 0, total_len - len);
// }
// 
// void
// __pthread_distribute_static_tls(size_t offset, void *src, size_t len,
//     size_t total_len)
// {
// 	struct pthread *curthread, *thrd;
// 	uintptr_t tlsbase;
// 
// 	if (!_thr_is_inited()) {
// 		tlsbase = _libc_get_static_tls_base(offset);
// 		thr_distribute_static_tls(tlsbase, src, len, total_len);
// 		return;
// 	}
// 	curthread = _get_curthread();
// 	THREAD_LIST_RDLOCK(curthread);
// 	TAILQ_FOREACH(thrd, &_thread_list, tle) {
// 		tlsbase = _get_static_tls_base(thrd, offset);
// 		thr_distribute_static_tls(tlsbase, src, len, total_len);
// 	}
// 	THREAD_LIST_UNLOCK(curthread);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_main_np.c sha256=12da4915d0fb0d5b0c99470cf44fb8f78a7b60b5c5cdef437a0eb32e960ad156
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2001 Alfred Perlstein
//  * Author: Alfred Perlstein <alfred@FreeBSD.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_thr_main_np, pthread_main_np);
// __weak_reference(_thr_main_np, _pthread_main_np);
// 
// /*
//  * Provide the equivalent to Solaris thr_main() function.
//  */
// int
// _thr_main_np(void)
// {
// 
// 	if (!_thr_initial)
// 		return (-1);
// 	else
// 		return (_pthread_equal(_pthread_self(), _thr_initial) ? 1 : 0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_malloc.c sha256=454196c7de5de610b9c511db576f9b6e9c9e8a7aa02a8a132113da2f32102563
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2019 The FreeBSD Foundation
//  * All rights reserved.
//  *
//  * This software was developed by Konstantin Belousov <kib@FreeBSD.org>
//  * under sponsorship from the FreeBSD Foundation.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include <sys/cdefs.h>
// #include <sys/types.h>
// #include <sys/mman.h>
// #include <rtld_malloc.h>
// #include "thr_private.h"
// 
// int npagesizes;
// size_t *pagesizes;
// static size_t pagesizes_d[2];
// static struct umutex thr_malloc_umtx;
// static u_int thr_malloc_umtx_level;
// 
// void
// __thr_malloc_init(void)
// {
// 
// 	if (npagesizes != 0)
// 		return;
// 	npagesizes = getpagesizes(pagesizes_d, nitems(pagesizes_d));
// 	if (npagesizes == -1) {
// 		PANIC("Unable to read page sizes");
// 	}
// 	pagesizes = pagesizes_d;
// 	_thr_umutex_init(&thr_malloc_umtx);
// }
// 
// static void
// thr_malloc_lock(struct pthread *curthread)
// {
// 	uint32_t curtid;
// 
// 	if (curthread == NULL)
// 		return;
// 	curthread->locklevel++;
// 	curtid = TID(curthread);
// 	if ((uint32_t)thr_malloc_umtx.m_owner == curtid)
// 		thr_malloc_umtx_level++;
// 	else
// 		_thr_umutex_lock(&thr_malloc_umtx, curtid);
// }
// 
// static void
// thr_malloc_unlock(struct pthread *curthread)
// {
// 
// 	if (curthread == NULL)
// 		return;
// 	if (thr_malloc_umtx_level > 0)
// 		thr_malloc_umtx_level--;
// 	else
// 		_thr_umutex_unlock(&thr_malloc_umtx, TID(curthread));
// 	curthread->locklevel--;
// 	_thr_ast(curthread);
// }
// 
// void *
// __thr_calloc(size_t num, size_t size)
// {
// 	struct pthread *curthread;
// 	void *res;
// 
// 	curthread = _get_curthread();
// 	thr_malloc_lock(curthread);
// 	res = __crt_calloc(num, size);
// 	thr_malloc_unlock(curthread);
// 	return (res);
// }
// 
// void
// __thr_free(void *cp)
// {
// 	struct pthread *curthread;
// 
// 	curthread = _get_curthread();
// 	thr_malloc_lock(curthread);
// 	__crt_free(cp);
// 	thr_malloc_unlock(curthread);
// }
// 
// void *
// __thr_malloc(size_t nbytes)
// {
// 	struct pthread *curthread;
// 	void *res;
// 
// 	curthread = _get_curthread();
// 	thr_malloc_lock(curthread);
// 	res = __crt_malloc(nbytes);
// 	thr_malloc_unlock(curthread);
// 	return (res);
// }
// 
// void *
// __thr_realloc(void *cp, size_t nbytes)
// {
// 	struct pthread *curthread;
// 	void *res;
// 
// 	curthread = _get_curthread();
// 	thr_malloc_lock(curthread);
// 	res = __crt_realloc(cp, nbytes);
// 	thr_malloc_unlock(curthread);
// 	return (res);
// }
// 
// void
// __thr_malloc_prefork(struct pthread *curthread)
// {
// 
// 	_thr_umutex_lock(&thr_malloc_umtx, TID(curthread));
// }
// 
// void
// __thr_malloc_postfork(struct pthread *curthread)
// {
// 
// 	_thr_umutex_unlock(&thr_malloc_umtx, TID(curthread));
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_multi_np.c sha256=bb46ba2a8cba7dadabbef77af9e083fddf80cc418abd364222912b6c5325b665
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1996 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// __weak_reference(_pthread_multi_np, pthread_multi_np);
// 
// int
// _pthread_multi_np(void)
// {
// 
// 	/* Return to multi-threaded scheduling mode: */
// 	/*
// 	 * XXX - Do we want to do this?
// 	 * __is_threaded = 1;
// 	 */
// 	_pthread_resume_all_np();
// 	return (0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_mutexattr.c sha256=f0f028b8d0eb58cc6be74fd8c00e3e650638ac5247854dfe3cd50d7187a2913c
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1996 Jeffrey Hsu <hsu@freebsd.org>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// /*
//  * Copyright (c) 1997 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  *
//  */
// 
// #include "namespace.h"
// #include <string.h>
// #include <stdlib.h>
// #include <errno.h>
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_thr_mutexattr_init, pthread_mutexattr_init);
// __weak_reference(_thr_mutexattr_init, _pthread_mutexattr_init);
// __weak_reference(_pthread_mutexattr_setkind_np, pthread_mutexattr_setkind_np);
// __weak_reference(_pthread_mutexattr_getkind_np, pthread_mutexattr_getkind_np);
// __weak_reference(_pthread_mutexattr_gettype, pthread_mutexattr_gettype);
// __weak_reference(_thr_mutexattr_settype, pthread_mutexattr_settype);
// __weak_reference(_thr_mutexattr_settype, _pthread_mutexattr_settype);
// __weak_reference(_thr_mutexattr_destroy, pthread_mutexattr_destroy);
// __weak_reference(_thr_mutexattr_destroy, _pthread_mutexattr_destroy);
// __weak_reference(_pthread_mutexattr_getpshared, pthread_mutexattr_getpshared);
// __weak_reference(_pthread_mutexattr_setpshared, pthread_mutexattr_setpshared);
// __weak_reference(_pthread_mutexattr_getprotocol, pthread_mutexattr_getprotocol);
// __weak_reference(_pthread_mutexattr_setprotocol, pthread_mutexattr_setprotocol);
// __weak_reference(_pthread_mutexattr_getprioceiling,
//     pthread_mutexattr_getprioceiling);
// __weak_reference(_pthread_mutexattr_setprioceiling,
//     pthread_mutexattr_setprioceiling);
// __weak_reference(_thr_mutexattr_getrobust, pthread_mutexattr_getrobust);
// __weak_reference(_thr_mutexattr_getrobust, _pthread_mutexattr_getrobust);
// __weak_reference(_thr_mutexattr_setrobust, pthread_mutexattr_setrobust);
// __weak_reference(_thr_mutexattr_setrobust, _pthread_mutexattr_setrobust);
// 
// int
// _thr_mutexattr_init(pthread_mutexattr_t *attr)
// {
// 	int ret;
// 	pthread_mutexattr_t pattr;
// 
// 	if ((pattr = (pthread_mutexattr_t)
// 	    malloc(sizeof(struct pthread_mutex_attr))) == NULL) {
// 		ret = ENOMEM;
// 	} else {
// 		memcpy(pattr, &_pthread_mutexattr_default,
// 		    sizeof(struct pthread_mutex_attr));
// 		*attr = pattr;
// 		ret = 0;
// 	}
// 	return (ret);
// }
// 
// int
// _pthread_mutexattr_setkind_np(pthread_mutexattr_t *attr, int kind)
// {
// 	int	ret;
// 	if (attr == NULL || *attr == NULL) {
// 		errno = EINVAL;
// 		ret = -1;
// 	} else {
// 		(*attr)->m_type = kind;
// 		ret = 0;
// 	}
// 	return(ret);
// }
// 
// int
// _pthread_mutexattr_getkind_np(pthread_mutexattr_t attr)
// {
// 	int	ret;
// 
// 	if (attr == NULL) {
// 		errno = EINVAL;
// 		ret = -1;
// 	} else {
// 		ret = attr->m_type;
// 	}
// 	return (ret);
// }
// 
// int
// _thr_mutexattr_settype(pthread_mutexattr_t *attr, int type)
// {
// 	int	ret;
// 
// 	if (attr == NULL || *attr == NULL || type >= PTHREAD_MUTEX_TYPE_MAX) {
// 		ret = EINVAL;
// 	} else {
// 		(*attr)->m_type = type;
// 		ret = 0;
// 	}
// 	return (ret);
// }
// 
// int
// _pthread_mutexattr_gettype(const pthread_mutexattr_t * __restrict attr,
//     int * __restrict type)
// {
// 	int	ret;
// 
// 	if (attr == NULL || *attr == NULL || (*attr)->m_type >=
// 	    PTHREAD_MUTEX_TYPE_MAX) {
// 		ret = EINVAL;
// 	} else {
// 		*type = (*attr)->m_type;
// 		ret = 0;
// 	}
// 	return (ret);
// }
// 
// int
// _thr_mutexattr_destroy(pthread_mutexattr_t *attr)
// {
// 	int	ret;
// 	if (attr == NULL || *attr == NULL) {
// 		ret = EINVAL;
// 	} else {
// 		free(*attr);
// 		*attr = NULL;
// 		ret = 0;
// 	}
// 	return (ret);
// }
// 
// int
// _pthread_mutexattr_getpshared(const pthread_mutexattr_t *attr,
// 	int *pshared)
// {
// 
// 	if (attr == NULL || *attr == NULL)
// 		return (EINVAL);
// 	*pshared = (*attr)->m_pshared;
// 	return (0);
// }
// 
// int
// _pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared)
// {
// 
// 	if (attr == NULL || *attr == NULL ||
// 	    (pshared != PTHREAD_PROCESS_PRIVATE &&
// 	    pshared != PTHREAD_PROCESS_SHARED))
// 		return (EINVAL);
// 	(*attr)->m_pshared = pshared;
// 	return (0);
// }
// 
// int
// _pthread_mutexattr_getprotocol(const pthread_mutexattr_t * __restrict mattr,
//     int * __restrict protocol)
// {
// 	int ret = 0;
// 
// 	if (mattr == NULL || *mattr == NULL)
// 		ret = EINVAL;
// 	else
// 		*protocol = (*mattr)->m_protocol;
// 
// 	return (ret);
// }
// 
// int
// _pthread_mutexattr_setprotocol(pthread_mutexattr_t *mattr, int protocol)
// {
// 	int ret = 0;
// 
// 	if (mattr == NULL || *mattr == NULL ||
// 	    protocol < PTHREAD_PRIO_NONE || protocol > PTHREAD_PRIO_PROTECT)
// 		ret = EINVAL;
// 	else {
// 		(*mattr)->m_protocol = protocol;
// 		(*mattr)->m_ceiling = THR_MAX_RR_PRIORITY;
// 	}
// 	return (ret);
// }
// 
// int
// _pthread_mutexattr_getprioceiling(const pthread_mutexattr_t * __restrict mattr,
//     int * __restrict prioceiling)
// {
// 	int ret = 0;
// 
// 	if (mattr == NULL || *mattr == NULL)
// 		ret = EINVAL;
// 	else if ((*mattr)->m_protocol != PTHREAD_PRIO_PROTECT)
// 		ret = EINVAL;
// 	else
// 		*prioceiling = (*mattr)->m_ceiling;
// 
// 	return (ret);
// }
// 
// int
// _pthread_mutexattr_setprioceiling(pthread_mutexattr_t *mattr, int prioceiling)
// {
// 	int ret = 0;
// 
// 	if (mattr == NULL || *mattr == NULL)
// 		ret = EINVAL;
// 	else if ((*mattr)->m_protocol != PTHREAD_PRIO_PROTECT)
// 		ret = EINVAL;
// 	else
// 		(*mattr)->m_ceiling = prioceiling;
// 
// 	return (ret);
// }
// 
// int
// _thr_mutexattr_getrobust(pthread_mutexattr_t *mattr, int *robust)
// {
// 	int ret;
// 
// 	if (mattr == NULL || *mattr == NULL) {
// 		ret = EINVAL;
// 	} else {
// 		ret = 0;
// 		*robust = (*mattr)->m_robust;
// 	}
// 	return (ret);
// }
// 
// int
// _thr_mutexattr_setrobust(pthread_mutexattr_t *mattr, int robust)
// {
// 	int ret;
// 
// 	if (mattr == NULL || *mattr == NULL) {
// 		ret = EINVAL;
// 	} else if (robust != PTHREAD_MUTEX_STALLED &&
// 	    robust != PTHREAD_MUTEX_ROBUST) {
// 		ret = EINVAL;
// 	} else {
// 		ret = 0;
// 		(*mattr)->m_robust = robust;
// 	}
// 	return (ret);
// }
// 
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_once.c sha256=9cea1f4b233ad71d556207642486952578d8013ae5f841f223c771f6ab0cd4b1
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005, David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_thr_once, pthread_once);
// __weak_reference(_thr_once, _pthread_once);
// 
// #define ONCE_NEVER_DONE		PTHREAD_NEEDS_INIT
// #define ONCE_DONE		PTHREAD_DONE_INIT
// #define	ONCE_IN_PROGRESS	0x02
// #define ONCE_WAIT		0x03
// 
// /*
//  * POSIX:
//  * The pthread_once() function is not a cancellation point. However,
//  * if init_routine is a cancellation point and is canceled, the effect
//  * on once_control shall be as if pthread_once() was never called.
//  */
//  
// static void
// once_cancel_handler(void *arg)
// {
// 	pthread_once_t *once_control;
// 
// 	once_control = arg;
// 	if (atomic_cmpset_rel_int(&once_control->state, ONCE_IN_PROGRESS,
// 	    ONCE_NEVER_DONE))
// 		return;
// 	atomic_store_rel_int(&once_control->state, ONCE_NEVER_DONE);
// 	_thr_umtx_wake(&once_control->state, INT_MAX, 0);
// }
// 
// int
// _thr_once(pthread_once_t *once_control, void (*init_routine)(void))
// {
// 	struct pthread *curthread;
// 	int state;
// 
// 	_thr_check_init();
// 
// 	for (;;) {
// 		state = once_control->state;
// 		if (state == ONCE_DONE) {
// 			atomic_thread_fence_acq();
// 			return (0);
// 		}
// 		if (state == ONCE_NEVER_DONE) {
// 			if (atomic_cmpset_int(&once_control->state, state,
// 			    ONCE_IN_PROGRESS))
// 				break;
// 		} else if (state == ONCE_IN_PROGRESS) {
// 			if (atomic_cmpset_int(&once_control->state, state,
// 			    ONCE_WAIT))
// 				_thr_umtx_wait_uint(&once_control->state,
// 				    ONCE_WAIT, NULL, 0);
// 		} else if (state == ONCE_WAIT) {
// 			_thr_umtx_wait_uint(&once_control->state, state,
// 			    NULL, 0);
// 		} else
// 			return (EINVAL);
//         }
// 
// 	curthread = _get_curthread();
// 	THR_CLEANUP_PUSH(curthread, once_cancel_handler, once_control);
// 	init_routine();
// 	THR_CLEANUP_POP(curthread, 0);
// 	if (atomic_cmpset_rel_int(&once_control->state, ONCE_IN_PROGRESS,
// 	    ONCE_DONE))
// 		return (0);
// 	atomic_store_rel_int(&once_control->state, ONCE_DONE);
// 	_thr_umtx_wake(&once_control->state, INT_MAX, 0);
// 	return (0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_printf.c sha256=59151ca8ad14dffee701652dbe34b783eac8ef6661ec709f39797b9408b4ae99
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2002 Jonathan Mini <mini@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include <stdarg.h>
// #include <string.h>
// #include <unistd.h>
// #include <pthread.h>
// 
// #include "libc_private.h"
// #include "thr_private.h"
// 
// static void	pchar(int fd, char c);
// static void	pstr(int fd, const char *s);
// 
// /*
//  * Write formatted output to stdout, in a thread-safe manner.
//  *
//  * Recognises the following conversions:
//  *	%c	-> char
//  *	%d	-> signed int (base 10)
//  *	%s	-> string
//  *	%u	-> unsigned int (base 10)
//  *	%x	-> unsigned int (base 16)
//  *	%p	-> unsigned int (base 16)
//  */
// void
// _thread_printf(int fd, const char *fmt, ...)
// {
// 	va_list	ap;
// 
// 	va_start(ap, fmt);
// 	_thread_vprintf(fd, fmt, ap);
// 	va_end(ap);
// }
// 
// void
// _thread_vprintf(int fd, const char *fmt, va_list ap)
// {
// 	static const char digits[16] = "0123456789abcdef";
// 	char buf[20];
// 	char *s;
// 	unsigned long r, u;
// 	int c;
// 	long d;
// 	int islong, isalt;
// 
// 	while ((c = *fmt++)) {
// 		isalt = 0;
// 		islong = 0;
// 		if (c == '%') {
// next:			c = *fmt++;
// 			if (c == '\0')
// 				return;
// 			switch (c) {
// 			case '#':
// 				isalt = 1;
// 				goto next;
// 			case 'c':
// 				pchar(fd, va_arg(ap, int));
// 				continue;
// 			case 's':
// 				pstr(fd, va_arg(ap, char *));
// 				continue;
// 			case 'l':
// 				islong = 1;
// 				goto next;
// 			case 'p':
// 				pstr(fd, "0x");
// 				islong = 1;
// 				/* FALLTHROUGH */
// 			case 'd':
// 			case 'u':
// 			case 'x':
// 				if (c == 'x' && isalt)
// 					pstr(fd, "0x");
// 				r = ((c == 'u') || (c == 'd')) ? 10 : 16;
// 				if (c == 'd') {
// 					if (islong)
// 						d = va_arg(ap, unsigned long);
// 					else
// 						d = va_arg(ap, unsigned);
// 					if (d < 0) {
// 						pchar(fd, '-');
// 						u = (unsigned long)(d * -1);
// 					} else
// 						u = (unsigned long)d;
// 				} else {
// 					if (islong)
// 						u = va_arg(ap, unsigned long);
// 					else
// 						u = va_arg(ap, unsigned);
// 				}
// 				s = buf;
// 				do {
// 					*s++ = digits[u % r];
// 				} while (u /= r);
// 				while (--s >= buf)
// 					pchar(fd, *s);
// 				continue;
// 			}
// 		}
// 		pchar(fd, c);
// 	}
// }
// 
// /*
//  * Write a single character to stdout, in a thread-safe manner.
//  */
// static void
// pchar(int fd, char c)
// {
// 
// 	__sys_write(fd, &c, 1);
// }
// 
// /*
//  * Write a string to stdout, in a thread-safe manner.
//  */
// static void
// pstr(int fd, const char *s)
// {
// 
// 	__sys_write(fd, s, strlen(s));
// }
// 
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_pshared.c sha256=e63d3ef84f6ffad0e9867418db788032a32c724394f4c545110c245b45d49f74
// /*-
//  * Copyright (c) 2015 The FreeBSD Foundation
//  *
//  * This software was developed by Konstantin Belousov
//  * under sponsorship from the FreeBSD Foundation.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include <sys/cdefs.h>
// #include <sys/types.h>
// #include <sys/mman.h>
// #include <sys/queue.h>
// #include "namespace.h"
// #include <stdlib.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// struct psh {
// 	LIST_ENTRY(psh) link;
// 	void *key;
// 	void *val;
// };
// 
// LIST_HEAD(pshared_hash_head, psh);
// #define	HASH_SIZE	128
// static struct pshared_hash_head pshared_hash[HASH_SIZE];
// #define	PSHARED_KEY_HASH(key)	(((unsigned long)(key) >> 8) % HASH_SIZE)
// /* XXXKIB: lock could be split to per-hash chain, if appears contested */
// static struct urwlock pshared_lock = DEFAULT_URWLOCK;
// static int page_size;
// 
// void
// __thr_pshared_init(void)
// {
// 	int i;
// 
// 	page_size = getpagesize();
// 	THR_ASSERT(page_size >= THR_PAGE_SIZE_MIN,
// 	    "THR_PAGE_SIZE_MIN is too large");
// 
// 	_thr_urwlock_init(&pshared_lock);
// 	for (i = 0; i < HASH_SIZE; i++)
// 		LIST_INIT(&pshared_hash[i]);
// }
// 
// static void
// pshared_rlock(struct pthread *curthread)
// {
// 
// 	curthread->locklevel++;
// 	_thr_rwl_rdlock(&pshared_lock);
// }
// 
// static void
// pshared_wlock(struct pthread *curthread)
// {
// 
// 	curthread->locklevel++;
// 	_thr_rwl_wrlock(&pshared_lock);
// }
// 
// static void
// pshared_unlock(struct pthread *curthread)
// {
// 
// 	_thr_rwl_unlock(&pshared_lock);
// 	curthread->locklevel--;
// 	_thr_ast(curthread);
// }
// 
// /*
//  * Among all processes sharing a lock only one executes
//  * pthread_lock_destroy().  Other processes still have the hash and
//  * mapped off-page.
//  *
//  * Mitigate the problem by checking the liveness of all hashed keys
//  * periodically.  Right now this is executed on each
//  * pthread_lock_destroy(), but may be done less often if found to be
//  * too time-consuming.
//  */
// static void
// pshared_gc(struct pthread *curthread)
// {
// 	struct pshared_hash_head *hd;
// 	struct psh *h, *h1;
// 	int error, i;
// 
// 	pshared_wlock(curthread);
// 	for (i = 0; i < HASH_SIZE; i++) {
// 		hd = &pshared_hash[i];
// 		LIST_FOREACH_SAFE(h, hd, link, h1) {
// 			error = _umtx_op(NULL, UMTX_OP_SHM, UMTX_SHM_ALIVE,
// 			    h->val, NULL);
// 			if (error == 0)
// 				continue;
// 			LIST_REMOVE(h, link);
// 			munmap(h->val, page_size);
// 			free(h);
// 		}
// 	}
// 	pshared_unlock(curthread);
// }
// 
// static void *
// pshared_lookup(void *key)
// {
// 	struct pshared_hash_head *hd;
// 	struct psh *h;
// 
// 	hd = &pshared_hash[PSHARED_KEY_HASH(key)];
// 	LIST_FOREACH(h, hd, link) {
// 		if (h->key == key)
// 			return (h->val);
// 	}
// 	return (NULL);
// }
// 
// static int
// pshared_insert(void *key, void **val)
// {
// 	struct pshared_hash_head *hd;
// 	struct psh *h;
// 
// 	hd = &pshared_hash[PSHARED_KEY_HASH(key)];
// 	LIST_FOREACH(h, hd, link) {
// 		/*
// 		 * When the key already exists in the hash, we should
// 		 * return either the new (just mapped) or old (hashed)
// 		 * val, and the other val should be unmapped to avoid
// 		 * address space leak.
// 		 *
// 		 * If two threads perform lock of the same object
// 		 * which is not yet stored in the pshared_hash, then
// 		 * the val already inserted by the first thread should
// 		 * be returned, and the second val freed (order is by
// 		 * the pshared_lock()).  Otherwise, if we unmap the
// 		 * value obtained from the hash, the first thread
// 		 * might operate on an unmapped off-page object.
// 		 *
// 		 * There is still an issue: if hashed key was unmapped
// 		 * and then other page is mapped at the same key
// 		 * address, the hash would return the old val.  I
// 		 * decided to handle the race of simultaneous hash
// 		 * insertion, leaving the unlikely remap problem
// 		 * unaddressed.
// 		 */
// 		if (h->key == key) {
// 			if (h->val != *val) {
// 				munmap(*val, page_size);
// 				*val = h->val;
// 			}
// 			return (1);
// 		}
// 	}
// 
// 	h = malloc(sizeof(*h));
// 	if (h == NULL)
// 		return (0);
// 	h->key = key;
// 	h->val = *val;
// 	LIST_INSERT_HEAD(hd, h, link);
// 	return (1);
// }
// 
// static void *
// pshared_remove(void *key)
// {
// 	struct pshared_hash_head *hd;
// 	struct psh *h;
// 	void *val;
// 
// 	hd = &pshared_hash[PSHARED_KEY_HASH(key)];
// 	LIST_FOREACH(h, hd, link) {
// 		if (h->key == key) {
// 			LIST_REMOVE(h, link);
// 			val = h->val;
// 			free(h);
// 			return (val);
// 		}
// 	}
// 	return (NULL);
// }
// 
// static void
// pshared_clean(void *key, void *val)
// {
// 
// 	if (val != NULL)
// 		munmap(val, page_size);
// 	_umtx_op(NULL, UMTX_OP_SHM, UMTX_SHM_DESTROY, key, NULL);
// }
// 
// static void
// pshared_destroy(struct pthread *curthread, void *key)
// {
// 	void *val;
// 
// 	pshared_wlock(curthread);
// 	val = pshared_remove(key);
// 	pshared_unlock(curthread);
// 	pshared_clean(key, val);
// }
// 
// void *
// __thr_pshared_offpage(void *key, int doalloc)
// {
// 	struct pthread *curthread;
// 	void *res;
// 	int fd, ins_done;
// 
// 	curthread = _get_curthread();
// 	if (doalloc) {
// 		pshared_destroy(curthread, key);
// 		res = NULL;
// 	} else {
// 		pshared_rlock(curthread);
// 		res = pshared_lookup(key);
// 		pshared_unlock(curthread);
// 		if (res != NULL)
// 			return (res);
// 	}
// 	fd = _umtx_op(NULL, UMTX_OP_SHM, doalloc ? UMTX_SHM_CREAT :
// 	    UMTX_SHM_LOOKUP, key, NULL);
// 	if (fd == -1)
// 		return (NULL);
// 	res = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
// 	close(fd);
// 	if (res == MAP_FAILED)
// 		return (NULL);
// 	pshared_wlock(curthread);
// 	ins_done = pshared_insert(key, &res);
// 	pshared_unlock(curthread);
// 	if (!ins_done) {
// 		pshared_clean(key, res);
// 		res = NULL;
// 	}
// 	return (res);
// }
// 
// void
// __thr_pshared_destroy(void *key)
// {
// 	struct pthread *curthread;
// 
// 	curthread = _get_curthread();
// 	pshared_destroy(curthread, key);
// 	pshared_gc(curthread);
// }
// 
// void
// __thr_pshared_atfork_pre(void)
// {
// 
// 	_thr_rwl_rdlock(&pshared_lock);
// }
// 
// void
// __thr_pshared_atfork_post(void)
// {
// 
// 	_thr_rwl_unlock(&pshared_lock);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_pspinlock.c sha256=ac5e0aabc129b68224c3faf749ad8d27cf1415cfe401c994fef1da42f238f953
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2003 David Xu <davidxu@freebsd.org>
//  * Copyright (c) 2016 The FreeBSD Foundation
//  * All rights reserved.
//  *
//  * Portions of this software were developed by Konstantin Belousov
//  * under sponsorship from the FreeBSD Foundation.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// _Static_assert(sizeof(struct pthread_spinlock) <= THR_PAGE_SIZE_MIN,
//     "pthread_spinlock is too large for off-page");
// 
// #define SPIN_COUNT 100000
// 
// __weak_reference(_pthread_spin_init, pthread_spin_init);
// __weak_reference(_pthread_spin_destroy, pthread_spin_destroy);
// __weak_reference(_pthread_spin_trylock, pthread_spin_trylock);
// __weak_reference(_pthread_spin_lock, pthread_spin_lock);
// __weak_reference(_pthread_spin_unlock, pthread_spin_unlock);
// 
// int
// _pthread_spin_init(pthread_spinlock_t *lock, int pshared)
// {
// 	struct pthread_spinlock	*lck;
// 
// 	if (lock == NULL)
// 		return (EINVAL);
// 	if (pshared == PTHREAD_PROCESS_PRIVATE) {
// 		lck = aligned_alloc(CACHE_LINE_SIZE,
// 		    roundup(sizeof(struct pthread_spinlock), CACHE_LINE_SIZE));
// 		if (lck == NULL)
// 			return (ENOMEM);
// 		*lock = lck;
// 	} else if (pshared == PTHREAD_PROCESS_SHARED) {
// 		lck = __thr_pshared_offpage(lock, 1);
// 		if (lck == NULL)
// 			return (EFAULT);
// 		*lock = THR_PSHARED_PTR;
// 	} else {
// 		return (EINVAL);
// 	}
// 	_thr_umutex_init(&lck->s_lock);
// 	return (0);
// }
// 
// int
// _pthread_spin_destroy(pthread_spinlock_t *lock)
// {
// 	void *l;
// 	int ret;
// 
// 	if (lock == NULL || *lock == NULL) {
// 		ret = EINVAL;
// 	} else if (*lock == THR_PSHARED_PTR) {
// 		l = __thr_pshared_offpage(lock, 0);
// 		if (l != NULL)
// 			__thr_pshared_destroy(l);
// 		ret = 0;
// 	} else {
// 		free(*lock);
// 		*lock = NULL;
// 		ret = 0;
// 	}
// 	return (ret);
// }
// 
// int
// _pthread_spin_trylock(pthread_spinlock_t *lock)
// {
// 	struct pthread_spinlock	*lck;
// 
// 	if (lock == NULL || *lock == NULL)
// 		return (EINVAL);
// 	lck = *lock == THR_PSHARED_PTR ? __thr_pshared_offpage(lock, 0) : *lock;
// 	if (lck == NULL)
// 		return (EINVAL);
// 	return (THR_UMUTEX_TRYLOCK(_get_curthread(), &lck->s_lock));
// }
// 
// int
// _pthread_spin_lock(pthread_spinlock_t *lock)
// {
// 	struct pthread *curthread;
// 	struct pthread_spinlock	*lck;
// 	int count;
// 
// 	if (lock == NULL)
// 		return (EINVAL);
// 	lck = *lock == THR_PSHARED_PTR ? __thr_pshared_offpage(lock, 0) : *lock;
// 	if (lck == NULL)
// 		return (EINVAL);
// 
// 	curthread = _get_curthread();
// 	count = SPIN_COUNT;
// 	while (THR_UMUTEX_TRYLOCK(curthread, &lck->s_lock) != 0) {
// 		while (lck->s_lock.m_owner) {
// 			if (!_thr_is_smp) {
// 				_pthread_yield();
// 			} else {
// 				CPU_SPINWAIT;
// 				if (--count <= 0) {
// 					count = SPIN_COUNT;
// 					_pthread_yield();
// 				}
// 			}
// 		}
// 	}
// 	return (0);
// }
// 
// int
// _pthread_spin_unlock(pthread_spinlock_t *lock)
// {
// 	struct pthread_spinlock	*lck;
// 
// 	if (lock == NULL)
// 		return (EINVAL);
// 	lck = *lock == THR_PSHARED_PTR ? __thr_pshared_offpage(lock, 0) : *lock;
// 	if (lck == NULL)
// 		return (EINVAL);
// 	return (THR_UMUTEX_UNLOCK(_get_curthread(), &lck->s_lock));
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_resume_np.c sha256=10d7e089a48e7c8375e12d0f0b1fe2bb28fc09c5de822852678dec8bd5d513d3
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_pthread_resume_np, pthread_resume_np);
// __weak_reference(_pthread_resume_all_np, pthread_resume_all_np);
// 
// static void resume_common(struct pthread *thread);
// 
// /* Resume a thread: */
// int
// _pthread_resume_np(pthread_t thread)
// {
// 	struct pthread *curthread = _get_curthread();
// 	int ret;
// 
// 	/* Add a reference to the thread: */
// 	if ((ret = _thr_find_thread(curthread, thread, /*include dead*/0)) == 0) {
// 		/* Lock the threads scheduling queue: */
// 		resume_common(thread);
// 		THR_THREAD_UNLOCK(curthread, thread);
// 	}
// 	return (ret);
// }
// 
// void
// _pthread_resume_all_np(void)
// {
// 	struct pthread *curthread = _get_curthread();
// 	struct pthread *thread;
// 	int old_nocancel;
// 
// 	old_nocancel = curthread->no_cancel;
// 	curthread->no_cancel = 1;
// 	_thr_suspend_all_lock(curthread);
// 	/* Take the thread list lock: */
// 	THREAD_LIST_RDLOCK(curthread);
// 
// 	TAILQ_FOREACH(thread, &_thread_list, tle) {
// 		if (thread != curthread) {
// 			THR_THREAD_LOCK(curthread, thread);
// 			resume_common(thread);
// 			THR_THREAD_UNLOCK(curthread, thread);
// 		}
// 	}
// 
// 	/* Release the thread list lock: */
// 	THREAD_LIST_UNLOCK(curthread);
// 	_thr_suspend_all_unlock(curthread);
// 	curthread->no_cancel = old_nocancel;
// 	_thr_testcancel(curthread);
// }
// 
// static void
// resume_common(struct pthread *thread)
// {
// 	/* Clear the suspend flag: */
// 	thread->flags &= ~(THR_FLAGS_NEED_SUSPEND | THR_FLAGS_SUSPENDED);
// 	thread->cycle++;
// 	_thr_umtx_wake(&thread->cycle, 1, 0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_rtld.c sha256=441da2f4799795e3cba5982045d6a3cd0f5294962e636123e686840ce3cdf700
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2006, David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
//  /*
//   * A lockless rwlock for rtld.
//   */
// #include <sys/mman.h>
// #include <sys/syscall.h>
// #include <link.h>
// #include <stdlib.h>
// #include <string.h>
// 
// #include "libc_private.h"
// #include "rtld_lock.h"
// #include "thr_private.h"
// 
// #undef errno
// extern int errno;
// 
// static int	_thr_rtld_clr_flag(int);
// static void	*_thr_rtld_lock_create(void);
// static void	_thr_rtld_lock_destroy(void *);
// static void	_thr_rtld_lock_release(void *);
// static void	_thr_rtld_rlock_acquire(void *);
// static int	_thr_rtld_set_flag(int);
// static void	_thr_rtld_wlock_acquire(void *);
// 
// struct rtld_lock {
// 	struct	urwlock	lock;
// 	char		_pad[CACHE_LINE_SIZE - sizeof(struct urwlock)];
// };
// 
// static struct rtld_lock lock_place[MAX_RTLD_LOCKS] __aligned(CACHE_LINE_SIZE);
// static int busy_places;
// 
// static void *
// _thr_rtld_lock_create(void)
// {
// 	int locki;
// 	struct rtld_lock *l;
// 	static const char fail[] = "_thr_rtld_lock_create failed\n";
// 
// 	for (locki = 0; locki < MAX_RTLD_LOCKS; locki++) {
// 		if ((busy_places & (1 << locki)) == 0)
// 			break;
// 	}
// 	if (locki == MAX_RTLD_LOCKS) {
// 		write(2, fail, sizeof(fail) - 1);
// 		return (NULL);
// 	}
// 	busy_places |= (1 << locki);
// 
// 	l = &lock_place[locki];
// 	l->lock.rw_flags = URWLOCK_PREFER_READER;
// 	return (l);
// }
// 
// static void
// _thr_rtld_lock_destroy(void *lock)
// {
// 	int locki;
// 	size_t i;
// 
// 	locki = (struct rtld_lock *)lock - &lock_place[0];
// 	for (i = 0; i < sizeof(struct rtld_lock); ++i)
// 		((char *)lock)[i] = 0;
// 	busy_places &= ~(1 << locki);
// }
// 
// #define SAVE_ERRNO()	{			\
// 	if (curthread != _thr_initial)		\
// 		errsave = curthread->error;	\
// 	else					\
// 		errsave = errno;		\
// }
// 
// #define RESTORE_ERRNO()	{ 			\
// 	if (curthread != _thr_initial)  	\
// 		curthread->error = errsave;	\
// 	else					\
// 		errno = errsave;		\
// }
// 
// static void
// _thr_rtld_rlock_acquire(void *lock)
// {
// 	struct pthread		*curthread;
// 	struct rtld_lock	*l;
// 	int			errsave;
// 
// 	curthread = _get_curthread();
// 	SAVE_ERRNO();
// 	l = (struct rtld_lock *)lock;
// 
// 	THR_CRITICAL_ENTER(curthread);
// 	while (_thr_rwlock_rdlock(&l->lock, 0, NULL) != 0)
// 		;
// 	curthread->rdlock_count++;
// 	RESTORE_ERRNO();
// }
// 
// static void
// _thr_rtld_wlock_acquire(void *lock)
// {
// 	struct pthread		*curthread;
// 	struct rtld_lock	*l;
// 	int			errsave;
// 
// 	curthread = _get_curthread();
// 	SAVE_ERRNO();
// 	l = (struct rtld_lock *)lock;
// 
// 	THR_CRITICAL_ENTER(curthread);
// 	while (_thr_rwlock_wrlock(&l->lock, NULL) != 0)
// 		;
// 	RESTORE_ERRNO();
// }
// 
// static void
// _thr_rtld_lock_release(void *lock)
// {
// 	struct pthread		*curthread;
// 	struct rtld_lock	*l;
// 	int32_t			state;
// 	int			errsave;
// 
// 	curthread = _get_curthread();
// 	SAVE_ERRNO();
// 	l = (struct rtld_lock *)lock;
// 	
// 	state = l->lock.rw_state;
// 	if (__predict_false(_thr_after_fork)) {
// 		/*
// 		 * After fork, only this thread is running, there is no
// 		 * waiters.  Keeping waiters recorded in rwlock breaks
// 		 * wake logic.
// 		 */
// 		atomic_clear_int(&l->lock.rw_state,
// 		    URWLOCK_WRITE_WAITERS | URWLOCK_READ_WAITERS);
// 		l->lock.rw_blocked_readers = 0;
// 		l->lock.rw_blocked_writers = 0;
// 	}
// 	if (_thr_rwlock_unlock(&l->lock) == 0) {
// 		if ((state & URWLOCK_WRITE_OWNER) == 0)
// 			curthread->rdlock_count--;
// 		THR_CRITICAL_LEAVE(curthread);
// 	}
// 	RESTORE_ERRNO();
// }
// 
// static int
// _thr_rtld_set_flag(int mask __unused)
// {
// 	/*
// 	 * The caller's code in rtld-elf is broken, it is not signal safe,
// 	 * just return zero to fool it.
// 	 */
// 	return (0);
// }
// 
// static int
// _thr_rtld_clr_flag(int mask __unused)
// {
// 	return (0);
// }
// 
// /*
//  * ABI bug workaround: This symbol must be present for rtld to accept
//  * RTLI_VERSION from RtldLockInfo
//  */
// extern char _pli_rtli_version;
// char _pli_rtli_version;
// 
// static char *
// _thr_dlerror_loc(void)
// {
// 	struct pthread *curthread;
// 
// 	curthread = _get_curthread();
// 	return (curthread->dlerror_msg);
// }
// 
// static int *
// _thr_dlerror_seen(void)
// {
// 	struct pthread *curthread;
// 
// 	curthread = _get_curthread();
// 	return (&curthread->dlerror_seen);
// }
// 
// void
// _thr_rtld_init(void)
// {
// 	struct RtldLockInfo	li;
// 	struct pthread		*curthread;
// 	ucontext_t *uc;
// 	long dummy = -1;
// 	int uc_len;
// 
// 	curthread = _get_curthread();
// 
// 	/* force to resolve _umtx_op PLT */
// 	_umtx_op_err((struct umtx *)&dummy, UMTX_OP_WAKE, 1, 0, 0);
// 	
// 	/* force to resolve errno() PLT */
// 	__error();
// 
// 	/* force to resolve memcpy PLT */
// 	memcpy(&dummy, &dummy, sizeof(dummy));
// 
// 	mprotect(NULL, 0, 0);
// 	_rtld_get_stack_prot();
// 
// 	li.rtli_version = RTLI_VERSION;
// 	li.lock_create  = _thr_rtld_lock_create;
// 	li.lock_destroy = _thr_rtld_lock_destroy;
// 	li.rlock_acquire = _thr_rtld_rlock_acquire;
// 	li.wlock_acquire = _thr_rtld_wlock_acquire;
// 	li.lock_release  = _thr_rtld_lock_release;
// 	li.thread_set_flag = _thr_rtld_set_flag;
// 	li.thread_clr_flag = _thr_rtld_clr_flag;
// 	li.at_fork = NULL;
// 	li.dlerror_loc = _thr_dlerror_loc;
// 	li.dlerror_loc_sz = sizeof(curthread->dlerror_msg);
// 	li.dlerror_seen = _thr_dlerror_seen;
// 
// 	/*
// 	 * Preresolve the symbols needed for the fork interposer.  We
// 	 * call _rtld_atfork_pre() and _rtld_atfork_post() with NULL
// 	 * argument to indicate that no actual locking inside the
// 	 * functions should happen.  Neither rtld compat locks nor
// 	 * libthr rtld locks cannot work there:
// 	 * - compat locks do not handle the case of two locks taken
// 	 *   in write mode (the signal mask for the thread is corrupted);
// 	 * - libthr locks would work, but locked rtld_bind_lock prevents
// 	 *   symbol resolution for _rtld_atfork_post.
// 	 */
// 	_rtld_atfork_pre(NULL);
// 	_rtld_atfork_post(NULL);
// 	_malloc_prefork();
// 	_malloc_postfork();
// 	getpid();
// 	syscall(SYS_getpid);
// 
// 	/* mask signals, also force to resolve __sys_sigprocmask PLT */
// 	_thr_signal_block(curthread);
// 	_rtld_thread_init(&li);
// 	_thr_signal_unblock(curthread);
// 	_thr_signal_block_check_fast();
// 	_thr_signal_block_setup(curthread);
// 
// 	/* resolve machine depended functions, if any */
// 	_thr_resolve_machdep();
// 
// 	uc_len = __getcontextx_size();
// 	uc = alloca(uc_len);
// 	getcontext(uc);
// 	__fillcontextx2((char *)uc);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_rwlock.c sha256=c29ea5fed9ebeb99ed55df5a58cd633f0994c44cd53b069ee2e7ba7fefc44045
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 1998 Alex Nash
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include <errno.h>
// #include <limits.h>
// #include <stdlib.h>
// #include <string.h>
// 
// #include "namespace.h"
// #include <pthread.h>
// #include "un-namespace.h"
// #include "thr_private.h"
// 
// _Static_assert(sizeof(struct pthread_rwlock) <= THR_PAGE_SIZE_MIN,
//     "pthread_rwlock is too large for off-page");
// 
// __weak_reference(_thr_rwlock_destroy, pthread_rwlock_destroy);
// __weak_reference(_thr_rwlock_destroy, _pthread_rwlock_destroy);
// __weak_reference(_thr_rwlock_init, pthread_rwlock_init);
// __weak_reference(_thr_rwlock_init, _pthread_rwlock_init);
// __weak_reference(_Tthr_rwlock_rdlock, pthread_rwlock_rdlock);
// __weak_reference(_Tthr_rwlock_rdlock, _pthread_rwlock_rdlock);
// __weak_reference(_pthread_rwlock_timedrdlock, pthread_rwlock_timedrdlock);
// __weak_reference(_Tthr_rwlock_tryrdlock, pthread_rwlock_tryrdlock);
// __weak_reference(_Tthr_rwlock_tryrdlock, _pthread_rwlock_tryrdlock);
// __weak_reference(_Tthr_rwlock_trywrlock, pthread_rwlock_trywrlock);
// __weak_reference(_Tthr_rwlock_trywrlock, _pthread_rwlock_trywrlock);
// __weak_reference(_Tthr_rwlock_unlock, pthread_rwlock_unlock);
// __weak_reference(_Tthr_rwlock_unlock, _pthread_rwlock_unlock);
// __weak_reference(_Tthr_rwlock_wrlock, pthread_rwlock_wrlock);
// __weak_reference(_Tthr_rwlock_wrlock, _pthread_rwlock_wrlock);
// __weak_reference(_pthread_rwlock_timedwrlock, pthread_rwlock_timedwrlock);
// 
// static int init_static(struct pthread *thread, pthread_rwlock_t *rwlock);
// static int init_rwlock(pthread_rwlock_t *rwlock, pthread_rwlock_t *rwlock_out);
// 
// static int __always_inline
// check_and_init_rwlock(pthread_rwlock_t *rwlock, pthread_rwlock_t *rwlock_out)
// {
// 	if (__predict_false(*rwlock == THR_PSHARED_PTR ||
// 	    *rwlock <= THR_RWLOCK_DESTROYED))
// 		return (init_rwlock(rwlock, rwlock_out));
// 	*rwlock_out = *rwlock;
// 	return (0);
// }
// 
// static int __noinline
// init_rwlock(pthread_rwlock_t *rwlock, pthread_rwlock_t *rwlock_out)
// {
// 	pthread_rwlock_t prwlock;
// 	int ret;
// 
// 	if (*rwlock == THR_PSHARED_PTR) {
// 		prwlock = __thr_pshared_offpage(rwlock, 0);
// 		if (prwlock == NULL)
// 			return (EINVAL);
// 	} else if ((prwlock = *rwlock) <= THR_RWLOCK_DESTROYED) {
// 		if (prwlock == THR_RWLOCK_INITIALIZER) {
// 			ret = init_static(_get_curthread(), rwlock);
// 			if (ret != 0)
// 				return (ret);
// 		} else if (prwlock == THR_RWLOCK_DESTROYED) {
// 			return (EINVAL);
// 		}
// 		prwlock = *rwlock;
// 	}
// 	*rwlock_out = prwlock;
// 	return (0);
// }
// 
// static int
// rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr)
// {
// 	pthread_rwlock_t prwlock;
// 
// 	if (attr == NULL || *attr == NULL ||
// 	    (*attr)->pshared == PTHREAD_PROCESS_PRIVATE) {
// 		prwlock = aligned_alloc(CACHE_LINE_SIZE,
// 		    roundup(sizeof(struct pthread_rwlock), CACHE_LINE_SIZE));
// 		if (prwlock == NULL)
// 			return (ENOMEM);
// 		memset(prwlock, 0, sizeof(struct pthread_rwlock));
// 		*rwlock = prwlock;
// 	} else {
// 		prwlock = __thr_pshared_offpage(rwlock, 1);
// 		if (prwlock == NULL)
// 			return (EFAULT);
// 		prwlock->lock.rw_flags |= USYNC_PROCESS_SHARED;
// 		*rwlock = THR_PSHARED_PTR;
// 	}
// 	return (0);
// }
// 
// int
// _thr_rwlock_destroy(pthread_rwlock_t *rwlock)
// {
// 	pthread_rwlock_t prwlock;
// 	int ret;
// 
// 	prwlock = *rwlock;
// 	if (prwlock == THR_RWLOCK_INITIALIZER)
// 		ret = 0;
// 	else if (prwlock == THR_RWLOCK_DESTROYED)
// 		ret = EINVAL;
// 	else if (prwlock == THR_PSHARED_PTR) {
// 		*rwlock = THR_RWLOCK_DESTROYED;
// 		__thr_pshared_destroy(rwlock);
// 		ret = 0;
// 	} else {
// 		*rwlock = THR_RWLOCK_DESTROYED;
// 		free(prwlock);
// 		ret = 0;
// 	}
// 	return (ret);
// }
// 
// static int
// init_static(struct pthread *thread, pthread_rwlock_t *rwlock)
// {
// 	int ret;
// 
// 	THR_LOCK_ACQUIRE(thread, &_rwlock_static_lock);
// 
// 	if (*rwlock == THR_RWLOCK_INITIALIZER)
// 		ret = rwlock_init(rwlock, NULL);
// 	else
// 		ret = 0;
// 
// 	THR_LOCK_RELEASE(thread, &_rwlock_static_lock);
// 
// 	return (ret);
// }
// 
// int
// _thr_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr)
// {
// 
// 	_thr_check_init();
// 	*rwlock = NULL;
// 	return (rwlock_init(rwlock, attr));
// }
// 
// static int
// rwlock_rdlock_common(pthread_rwlock_t *rwlock, const struct timespec *abstime)
// {
// 	struct pthread *curthread = _get_curthread();
// 	pthread_rwlock_t prwlock;
// 	int flags;
// 	int ret;
// 
// 	ret = check_and_init_rwlock(rwlock, &prwlock);
// 	if (ret != 0)
// 		return (ret);
// 
// 	if (curthread->rdlock_count) {
// 		/*
// 		 * To avoid having to track all the rdlocks held by
// 		 * a thread or all of the threads that hold a rdlock,
// 		 * we keep a simple count of all the rdlocks held by
// 		 * a thread.  If a thread holds any rdlocks it is
// 		 * possible that it is attempting to take a recursive
// 		 * rdlock.  If there are blocked writers and precedence
// 		 * is given to them, then that would result in the thread
// 		 * deadlocking.  So allowing a thread to take the rdlock
// 		 * when it already has one or more rdlocks avoids the
// 		 * deadlock.  I hope the reader can follow that logic ;-)
// 		 */
// 		flags = URWLOCK_PREFER_READER;
// 	} else {
// 		flags = 0;
// 	}
// 
// 	/*
// 	 * POSIX said the validity of the abstimeout parameter need
// 	 * not be checked if the lock can be immediately acquired.
// 	 */
// 	ret = _thr_rwlock_tryrdlock(&prwlock->lock, flags);
// 	if (ret == 0) {
// 		curthread->rdlock_count++;
// 		return (ret);
// 	}
// 
// 	if (__predict_false(abstime && 
// 		(abstime->tv_nsec >= 1000000000 || abstime->tv_nsec < 0)))
// 		return (EINVAL);
// 
// 	for (;;) {
// 		/* goto kernel and lock it */
// 		ret = __thr_rwlock_rdlock(&prwlock->lock, flags, abstime);
// 		if (ret != EINTR)
// 			break;
// 
// 		/* if interrupted, try to lock it in userland again. */
// 		if (_thr_rwlock_tryrdlock(&prwlock->lock, flags) == 0) {
// 			ret = 0;
// 			break;
// 		}
// 	}
// 	if (ret == 0)
// 		curthread->rdlock_count++;
// 	return (ret);
// }
// 
// int
// _Tthr_rwlock_rdlock(pthread_rwlock_t *rwlock)
// {
// 	_thr_check_init();
// 	return (rwlock_rdlock_common(rwlock, NULL));
// }
// 
// int
// _pthread_rwlock_timedrdlock(pthread_rwlock_t * __restrict rwlock,
//     const struct timespec * __restrict abstime)
// {
// 	_thr_check_init();
// 	return (rwlock_rdlock_common(rwlock, abstime));
// }
// 
// int
// _Tthr_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
// {
// 	struct pthread *curthread;
// 	pthread_rwlock_t prwlock;
// 	int flags;
// 	int ret;
// 
// 	_thr_check_init();
// 	ret = check_and_init_rwlock(rwlock, &prwlock);
// 	if (ret != 0)
// 		return (ret);
// 
// 	curthread = _get_curthread();
// 	if (curthread->rdlock_count) {
// 		/*
// 		 * To avoid having to track all the rdlocks held by
// 		 * a thread or all of the threads that hold a rdlock,
// 		 * we keep a simple count of all the rdlocks held by
// 		 * a thread.  If a thread holds any rdlocks it is
// 		 * possible that it is attempting to take a recursive
// 		 * rdlock.  If there are blocked writers and precedence
// 		 * is given to them, then that would result in the thread
// 		 * deadlocking.  So allowing a thread to take the rdlock
// 		 * when it already has one or more rdlocks avoids the
// 		 * deadlock.  I hope the reader can follow that logic ;-)
// 		 */
// 		flags = URWLOCK_PREFER_READER;
// 	} else {
// 		flags = 0;
// 	}
// 
// 	ret = _thr_rwlock_tryrdlock(&prwlock->lock, flags);
// 	if (ret == 0)
// 		curthread->rdlock_count++;
// 	return (ret);
// }
// 
// int
// _Tthr_rwlock_trywrlock(pthread_rwlock_t *rwlock)
// {
// 	struct pthread *curthread;
// 	pthread_rwlock_t prwlock;
// 	int ret;
// 
// 	_thr_check_init();
// 	ret = check_and_init_rwlock(rwlock, &prwlock);
// 	if (ret != 0)
// 		return (ret);
// 
// 	curthread = _get_curthread();
// 	ret = _thr_rwlock_trywrlock(&prwlock->lock);
// 	if (ret == 0)
// 		prwlock->owner = TID(curthread);
// 	return (ret);
// }
// 
// static int
// rwlock_wrlock_common(pthread_rwlock_t *rwlock, const struct timespec *abstime)
// {
// 	struct pthread *curthread = _get_curthread();
// 	pthread_rwlock_t prwlock;
// 	int ret;
// 
// 	ret = check_and_init_rwlock(rwlock, &prwlock);
// 	if (ret != 0)
// 		return (ret);
// 
// 	/*
// 	 * POSIX said the validity of the abstimeout parameter need
// 	 * not be checked if the lock can be immediately acquired.
// 	 */
// 	ret = _thr_rwlock_trywrlock(&prwlock->lock);
// 	if (ret == 0) {
// 		prwlock->owner = TID(curthread);
// 		return (ret);
// 	}
// 
// 	if (__predict_false(abstime && 
// 	    (abstime->tv_nsec >= 1000000000 || abstime->tv_nsec < 0)))
// 		return (EINVAL);
// 
// 	for (;;) {
// 		/* goto kernel and lock it */
// 		ret = __thr_rwlock_wrlock(&prwlock->lock, abstime);
// 		if (ret == 0) {
// 			prwlock->owner = TID(curthread);
// 			break;
// 		}
// 
// 		if (ret != EINTR)
// 			break;
// 
// 		/* if interrupted, try to lock it in userland again. */
// 		if (_thr_rwlock_trywrlock(&prwlock->lock) == 0) {
// 			ret = 0;
// 			prwlock->owner = TID(curthread);
// 			break;
// 		}
// 	}
// 	return (ret);
// }
// 
// int
// _Tthr_rwlock_wrlock(pthread_rwlock_t *rwlock)
// {
// 	_thr_check_init();
// 	return (rwlock_wrlock_common(rwlock, NULL));
// }
// 
// int
// _pthread_rwlock_timedwrlock(pthread_rwlock_t * __restrict rwlock,
//     const struct timespec * __restrict abstime)
// {
// 	_thr_check_init();
// 	return (rwlock_wrlock_common(rwlock, abstime));
// }
// 
// int
// _Tthr_rwlock_unlock(pthread_rwlock_t *rwlock)
// {
// 	struct pthread *curthread = _get_curthread();
// 	pthread_rwlock_t prwlock;
// 	int ret;
// 	int32_t state;
// 
// 	if (*rwlock == THR_PSHARED_PTR) {
// 		prwlock = __thr_pshared_offpage(rwlock, 0);
// 		if (prwlock == NULL)
// 			return (EINVAL);
// 	} else {
// 		prwlock = *rwlock;
// 	}
// 
// 	if (__predict_false(prwlock <= THR_RWLOCK_DESTROYED))
// 		return (EINVAL);
// 
// 	state = prwlock->lock.rw_state;
// 	if (state & URWLOCK_WRITE_OWNER) {
// 		if (__predict_false(prwlock->owner != TID(curthread)))
// 			return (EPERM);
// 		prwlock->owner = 0;
// 	}
// 
// 	ret = _thr_rwlock_unlock(&prwlock->lock);
// 	if (ret == 0 && (state & URWLOCK_WRITE_OWNER) == 0)
// 		curthread->rdlock_count--;
// 
// 	return (ret);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_rwlockattr.c sha256=dc0f3c502f7b8571f39f35fc4c70606792c2cda834d6bc6282e9125e973dc7b8
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 1998 Alex Nash
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_pthread_rwlockattr_destroy, pthread_rwlockattr_destroy);
// __weak_reference(_pthread_rwlockattr_getpshared, pthread_rwlockattr_getpshared);
// __weak_reference(_pthread_rwlockattr_init, pthread_rwlockattr_init);
// __weak_reference(_pthread_rwlockattr_setpshared, pthread_rwlockattr_setpshared);
// 
// int
// _pthread_rwlockattr_destroy(pthread_rwlockattr_t *rwlockattr)
// {
// 	pthread_rwlockattr_t prwlockattr;
// 
// 	if (rwlockattr == NULL)
// 		return (EINVAL);
// 	prwlockattr = *rwlockattr;
// 	if (prwlockattr == NULL)
// 		return (EINVAL);
// 	free(prwlockattr);
// 	return (0);
// }
// 
// int
// _pthread_rwlockattr_getpshared(
//     const pthread_rwlockattr_t * __restrict rwlockattr,
//     int * __restrict pshared)
// {
// 
// 	*pshared = (*rwlockattr)->pshared;
// 	return (0);
// }
// 
// int
// _pthread_rwlockattr_init(pthread_rwlockattr_t *rwlockattr)
// {
// 	pthread_rwlockattr_t prwlockattr;
// 
// 	if (rwlockattr == NULL)
// 		return (EINVAL);
// 
// 	prwlockattr = malloc(sizeof(struct pthread_rwlockattr));
// 	if (prwlockattr == NULL)
// 		return (ENOMEM);
// 
// 	prwlockattr->pshared = PTHREAD_PROCESS_PRIVATE;
// 	*rwlockattr = prwlockattr;
// 	return (0);
// }
// 
// int
// _pthread_rwlockattr_setpshared(pthread_rwlockattr_t *rwlockattr, int pshared)
// {
// 
// 	if (pshared != PTHREAD_PROCESS_PRIVATE &&
// 	    pshared != PTHREAD_PROCESS_SHARED)
// 		return (EINVAL);
// 	(*rwlockattr)->pshared = pshared;
// 	return (0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_self.c sha256=e091cc03896ad2bfcdb8e2c99a0f63a9ea426228594634c595288cc3d4316708
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_Tthr_self, pthread_self);
// __weak_reference(_Tthr_self, _pthread_self);
// 
// pthread_t
// _Tthr_self(void)
// {
// 	_thr_check_init();
// 
// 	/* Return the running thread pointer: */
// 	return (_get_curthread());
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_sem.c sha256=d59ca4513438fcf1bce32155e4dd4dd9305085223c9c65932aa60148c8275289
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (C) 2005 David Xu <davidxu@freebsd.org>.
//  * Copyright (C) 2000 Jason Evans <jasone@freebsd.org>.
//  * All rights reserved.
//  * 
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice(s), this list of conditions and the following disclaimer as
//  *    the first lines of this file unmodified other than the possible
//  *    addition of one or more copyright notices.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice(s), this list of conditions and the following disclaimer in
//  *    the documentation and/or other materials provided with the
//  *    distribution.
//  * 
//  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY
//  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) BE
//  * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//  * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
//  * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <sys/types.h>
// #include <sys/queue.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <time.h>
// #include <_semaphore.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// FB10_COMPAT(_sem_init_compat, sem_init);
// FB10_COMPAT(_sem_destroy_compat, sem_destroy);
// FB10_COMPAT(_sem_getvalue_compat, sem_getvalue);
// FB10_COMPAT(_sem_trywait_compat, sem_trywait);
// FB10_COMPAT(_sem_wait_compat, sem_wait);
// FB10_COMPAT(_sem_timedwait_compat, sem_timedwait);
// FB10_COMPAT(_sem_post_compat, sem_post);
// 
// typedef struct sem *sem_t;
// 
// extern int _libc_sem_init_compat(sem_t *sem, int pshared, unsigned int value);
// extern int _libc_sem_destroy_compat(sem_t *sem);
// extern int _libc_sem_getvalue_compat(sem_t * __restrict sem, int * __restrict sval);
// extern int _libc_sem_trywait_compat(sem_t *sem);
// extern int _libc_sem_wait_compat(sem_t *sem);
// extern int _libc_sem_timedwait_compat(sem_t * __restrict sem,
//     const struct timespec * __restrict abstime);
// extern int _libc_sem_post_compat(sem_t *sem);
// 
// int _sem_init_compat(sem_t *sem, int pshared, unsigned int value);
// int _sem_destroy_compat(sem_t *sem);
// int _sem_getvalue_compat(sem_t * __restrict sem, int * __restrict sval);
// int _sem_trywait_compat(sem_t *sem);
// int _sem_wait_compat(sem_t *sem);
// int _sem_timedwait_compat(sem_t * __restrict sem,
//     const struct timespec * __restrict abstime);
// int _sem_post_compat(sem_t *sem);
// 
// int
// _sem_init_compat(sem_t *sem, int pshared, unsigned int value)
// {
// 	return _libc_sem_init_compat(sem, pshared, value);
// }
// 
// int
// _sem_destroy_compat(sem_t *sem)
// {
// 	return _libc_sem_destroy_compat(sem);
// }
// 
// int
// _sem_getvalue_compat(sem_t * __restrict sem, int * __restrict sval)
// {
// 	return _libc_sem_getvalue_compat(sem, sval);
// }
// 
// int
// _sem_trywait_compat(sem_t *sem)
// {
// 	return _libc_sem_trywait_compat(sem);
// }
// 
// int
// _sem_wait_compat(sem_t *sem)
// {
// 	return _libc_sem_wait_compat(sem);
// }
// 
// int
// _sem_timedwait_compat(sem_t * __restrict sem,
//     const struct timespec * __restrict abstime)
// {
// 	return _libc_sem_timedwait_compat(sem, abstime);
// }
// 
// int
// _sem_post_compat(sem_t *sem)
// {
// 	return _libc_sem_post_compat(sem);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_setprio.c sha256=aa61470d9b1a75520c11eb19e39ae3fce739ebffd144f897f7bde8d441c843fd
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// __weak_reference(_pthread_setprio, pthread_setprio);
// 
// int
// _pthread_setprio(pthread_t pthread, int prio)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	struct sched_param	param;
// 	int	ret;
// 
// 	param.sched_priority = prio;
// 	if (pthread == curthread)
// 		THR_LOCK(curthread);
// 	else if ((ret = _thr_find_thread(curthread, pthread, /*include dead*/0)))
// 		return (ret);
// 	if (pthread->attr.sched_policy == SCHED_OTHER ||
// 	    pthread->attr.prio == prio) {
// 		pthread->attr.prio = prio;
// 		ret = 0;
// 	} else {
// 		ret = _thr_setscheduler(pthread->tid,
// 			pthread->attr.sched_policy, &param);
// 		if (ret == -1)
// 			ret = errno;
// 		else
// 			pthread->attr.prio = prio;
// 	}
// 	THR_THREAD_UNLOCK(curthread, pthread);
// 	return (ret);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_sig.c sha256=72d97ad6aa114fef5371ae77ff9c8855d204f00b32a37b105e0ad0294e0d6fdb
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005, David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <sys/param.h>
// #include <sys/auxv.h>
// #include <sys/elf.h>
// #include <sys/signalvar.h>
// #include <sys/syscall.h>
// #include <signal.h>
// #include <errno.h>
// #include <stdlib.h>
// #include <string.h>
// #include <pthread.h>
// #include "un-namespace.h"
// #include "libc_private.h"
// 
// #include "libc_private.h"
// #include "thr_private.h"
// 
// /* #define DEBUG_SIGNAL */
// #ifdef DEBUG_SIGNAL
// #define DBG_MSG		stdout_debug
// #else
// #define DBG_MSG(x...)
// #endif
// 
// struct usigaction {
// 	struct sigaction sigact;
// 	struct urwlock   lock;
// };
// 
// static struct usigaction _thr_sigact[_SIG_MAXSIG];
// 
// static inline struct usigaction *
// __libc_sigaction_slot(int signo)
// {
// 
// 	return (&_thr_sigact[signo - 1]);
// }
// 
// static void thr_sighandler(int, siginfo_t *, void *);
// static void handle_signal(struct sigaction *, int, siginfo_t *, ucontext_t *);
// static void check_deferred_signal(struct pthread *);
// static void check_suspend(struct pthread *);
// static void check_cancel(struct pthread *curthread, ucontext_t *ucp);
// 
// int	_sigtimedwait(const sigset_t *set, siginfo_t *info,
// 	const struct timespec * timeout);
// int	_sigwaitinfo(const sigset_t *set, siginfo_t *info);
// int	_sigwait(const sigset_t *set, int *sig);
// int	_setcontext(const ucontext_t *);
// int	_swapcontext(ucontext_t *, const ucontext_t *);
// 
// static const sigset_t _thr_deferset={{
// 	0xffffffff & ~(_SIG_BIT(SIGBUS)|_SIG_BIT(SIGILL)|_SIG_BIT(SIGFPE)|
// 	_SIG_BIT(SIGSEGV)|_SIG_BIT(SIGTRAP)|_SIG_BIT(SIGSYS)),
// 	0xffffffff,
// 	0xffffffff,
// 	0xffffffff}};
// 
// static const sigset_t _thr_maskset={{
// 	0xffffffff,
// 	0xffffffff,
// 	0xffffffff,
// 	0xffffffff}};
// 
// static void
// thr_signal_block_slow(struct pthread *curthread)
// {
// 	if (curthread->sigblock > 0) {
// 		curthread->sigblock++;
// 		return;
// 	}
// 	__sys_sigprocmask(SIG_BLOCK, &_thr_maskset, &curthread->sigmask);
// 	curthread->sigblock++;
// }
// 
// static void
// thr_signal_unblock_slow(struct pthread *curthread)
// {
// 	if (--curthread->sigblock == 0)
// 		__sys_sigprocmask(SIG_SETMASK, &curthread->sigmask, NULL);
// }
// 
// static void
// thr_signal_block_fast(struct pthread *curthread)
// {
// 	atomic_add_32(&curthread->fsigblock, SIGFASTBLOCK_INC);
// }
// 
// static void
// thr_signal_unblock_fast(struct pthread *curthread)
// {
// 	uint32_t oldval;
// 
// 	oldval = atomic_fetchadd_32(&curthread->fsigblock, -SIGFASTBLOCK_INC);
// 	if (oldval == (SIGFASTBLOCK_PEND | SIGFASTBLOCK_INC))
// 		__sys_sigfastblock(SIGFASTBLOCK_UNBLOCK, NULL);
// }
// 
// static bool fast_sigblock;
// 
// void
// _thr_signal_block(struct pthread *curthread)
// {
// 	if (fast_sigblock)
// 		thr_signal_block_fast(curthread);
// 	else
// 		thr_signal_block_slow(curthread);
// }
// 
// void
// _thr_signal_unblock(struct pthread *curthread)
// {
// 	if (fast_sigblock)
// 		thr_signal_unblock_fast(curthread);
// 	else
// 		thr_signal_unblock_slow(curthread);
// }
// 
// void
// _thr_signal_block_check_fast(void)
// {
// 	int bsdflags, error;
// 
// 	error = elf_aux_info(AT_BSDFLAGS, &bsdflags, sizeof(bsdflags));
// 	if (error != 0)
// 		return;
// 	fast_sigblock = (bsdflags & ELF_BSDF_SIGFASTBLK) != 0;
// }
// 
// void
// _thr_signal_block_setup(struct pthread *curthread)
// {
// 	if (!fast_sigblock)
// 		return;
// 	__sys_sigfastblock(SIGFASTBLOCK_SETPTR, &curthread->fsigblock);
// }
// 
// int
// _thr_send_sig(struct pthread *thread, int sig)
// {
// 	return thr_kill(thread->tid, sig);
// }
// 
// static inline void
// remove_thr_signals(sigset_t *set)
// {
// 	if (SIGISMEMBER(*set, SIGCANCEL))
// 		SIGDELSET(*set, SIGCANCEL);
// }
// 
// static const sigset_t *
// thr_remove_thr_signals(const sigset_t *set, sigset_t *newset)
// {
// 	*newset = *set;
// 	remove_thr_signals(newset);
// 	return (newset);
// }
// 
// static void
// sigcancel_handler(int sig __unused,
// 	siginfo_t *info __unused, ucontext_t *ucp)
// {
// 	struct pthread *curthread = _get_curthread();
// 	int err;
// 
// 	if (THR_IN_CRITICAL(curthread))
// 		return;
// 	err = errno;
// 	check_suspend(curthread);
// 	check_cancel(curthread, ucp);
// 	errno = err;
// }
// 
// typedef void (*ohandler)(int sig, int code, struct sigcontext *scp,
//     char *addr, __sighandler_t *catcher);
// 
// /*
//  * The signal handler wrapper is entered with all signal masked.
//  */
// static void
// thr_sighandler(int sig, siginfo_t *info, void *_ucp)
// {
// 	struct pthread *curthread;
// 	ucontext_t *ucp;
// 	struct sigaction act;
// 	struct usigaction *usa;
// 	int err;
// 
// 	err = errno;
// 	curthread = _get_curthread();
// 	ucp = _ucp;
// 	usa = __libc_sigaction_slot(sig);
// 	_thr_rwl_rdlock(&usa->lock);
// 	act = usa->sigact;
// 	_thr_rwl_unlock(&usa->lock);
// 	errno = err;
// 	curthread->deferred_run = 0;
// 
// 	/*
// 	 * if a thread is in critical region, for example it holds low level locks,
// 	 * try to defer the signal processing, however if the signal is synchronous
// 	 * signal, it means a bad thing has happened, this is a programming error,
// 	 * resuming fault point can not help anything (normally causes deadloop),
// 	 * so here we let user code handle it immediately.
// 	 */
// 	if (THR_IN_CRITICAL(curthread) && SIGISMEMBER(_thr_deferset, sig)) {
// 		memcpy(&curthread->deferred_sigact, &act, sizeof(struct sigaction));
// 		memcpy(&curthread->deferred_siginfo, info, sizeof(siginfo_t));
// 		curthread->deferred_sigmask = ucp->uc_sigmask;
// 		/* mask all signals, we will restore it later. */
// 		ucp->uc_sigmask = _thr_deferset;
// 		return;
// 	}
// 
// 	handle_signal(&act, sig, info, ucp);
// }
// 
// static void
// handle_signal(struct sigaction *actp, int sig, siginfo_t *info, ucontext_t *ucp)
// {
// 	struct pthread *curthread = _get_curthread();
// 	ucontext_t uc2;
// 	__siginfohandler_t *sigfunc;
// 	int cancel_point;
// 	int cancel_async;
// 	int cancel_enable;
// 	int in_sigsuspend;
// 	int err;
// 
// 	/* add previous level mask */
// 	SIGSETOR(actp->sa_mask, ucp->uc_sigmask);
// 
// 	/* add this signal's mask */
// 	if (!(actp->sa_flags & SA_NODEFER))
// 		SIGADDSET(actp->sa_mask, sig);
// 
// 	in_sigsuspend = curthread->in_sigsuspend;
// 	curthread->in_sigsuspend = 0;
// 
// 	/*
// 	 * If thread is in deferred cancellation mode, disable cancellation
// 	 * in signal handler.
// 	 * If user signal handler calls a cancellation point function, e.g,
// 	 * it calls write() to write data to file, because write() is a
// 	 * cancellation point, the thread is immediately cancelled if 
// 	 * cancellation is pending, to avoid this problem while thread is in
// 	 * deferring mode, cancellation is temporarily disabled.
// 	 */
// 	cancel_point = curthread->cancel_point;
// 	cancel_async = curthread->cancel_async;
// 	cancel_enable = curthread->cancel_enable;
// 	curthread->cancel_point = 0;
// 	if (!cancel_async)
// 		curthread->cancel_enable = 0;
// 
// 	/* restore correct mask before calling user handler */
// 	__sys_sigprocmask(SIG_SETMASK, &actp->sa_mask, NULL);
// 
// 	sigfunc = actp->sa_sigaction;
// 
// 	/*
// 	 * We have already reset cancellation point flags, so if user's code
// 	 * longjmp()s out of its signal handler, wish its jmpbuf was set
// 	 * outside of a cancellation point, in most cases, this would be
// 	 * true.  However, there is no way to save cancel_enable in jmpbuf,
// 	 * so after setjmps() returns once more, the user code may need to
// 	 * re-set cancel_enable flag by calling pthread_setcancelstate().
// 	 */
// 	if ((actp->sa_flags & SA_SIGINFO) != 0) {
// 		sigfunc(sig, info, ucp);
// 	} else {
// 		((ohandler)sigfunc)(sig, info->si_code,
// 		    (struct sigcontext *)ucp, info->si_addr,
// 		    (__sighandler_t *)sigfunc);
// 	}
// 	err = errno;
// 
// 	curthread->in_sigsuspend = in_sigsuspend;
// 	curthread->cancel_point = cancel_point;
// 	curthread->cancel_enable = cancel_enable;
// 
// 	memcpy(&uc2, ucp, sizeof(uc2));
// 	SIGDELSET(uc2.uc_sigmask, SIGCANCEL);
// 
// 	/* reschedule cancellation */
// 	check_cancel(curthread, &uc2);
// 	errno = err;
// 	syscall(SYS_sigreturn, &uc2);
// }
// 
// void
// _thr_ast(struct pthread *curthread)
// {
// 
// 	if (!THR_IN_CRITICAL(curthread)) {
// 		check_deferred_signal(curthread);
// 		check_suspend(curthread);
// 		check_cancel(curthread, NULL);
// 	}
// }
// 
// /* reschedule cancellation */
// static void
// check_cancel(struct pthread *curthread, ucontext_t *ucp)
// {
// 
// 	if (__predict_true(!curthread->cancel_pending ||
// 	    !curthread->cancel_enable || curthread->no_cancel))
// 		return;
// 
// 	/*
//  	 * Otherwise, we are in defer mode, and we are at
// 	 * cancel point, tell kernel to not block the current
// 	 * thread on next cancelable system call.
// 	 * 
// 	 * There are three cases we should call thr_wake() to
// 	 * turn on TDP_WAKEUP or send SIGCANCEL in kernel:
// 	 * 1) we are going to call a cancelable system call,
// 	 *    non-zero cancel_point means we are already in
// 	 *    cancelable state, next system call is cancelable.
// 	 * 2) because _thr_ast() may be called by
// 	 *    THR_CRITICAL_LEAVE() which is used by rtld rwlock
// 	 *    and any libthr internal locks, when rtld rwlock
// 	 *    is used, it is mostly caused by an unresolved PLT.
// 	 *    Those routines may clear the TDP_WAKEUP flag by
// 	 *    invoking some system calls, in those cases, we
// 	 *    also should reenable the flag.
// 	 * 3) thread is in sigsuspend(), and the syscall insists
// 	 *    on getting a signal before it agrees to return.
//  	 */
// 	if (curthread->cancel_point) {
// 		if (curthread->in_sigsuspend && ucp) {
// 			SIGADDSET(ucp->uc_sigmask, SIGCANCEL);
// 			curthread->unblock_sigcancel = 1;
// 			_thr_send_sig(curthread, SIGCANCEL);
// 		} else
// 			thr_wake(curthread->tid);
// 	} else if (curthread->cancel_async) {
// 		/*
// 		 * asynchronous cancellation mode, act upon
// 		 * immediately.
// 		 */
// 		_pthread_exit_mask(PTHREAD_CANCELED,
// 		    ucp? &ucp->uc_sigmask : NULL);
// 	}
// }
// 
// static void
// check_deferred_signal(struct pthread *curthread)
// {
// 	ucontext_t *uc;
// 	struct sigaction act;
// 	siginfo_t info;
// 	int uc_len;
// 
// 	if (__predict_true(curthread->deferred_siginfo.si_signo == 0 ||
// 	    curthread->deferred_run))
// 		return;
// 
// 	curthread->deferred_run = 1;
// 	uc_len = __getcontextx_size();
// 	uc = alloca(uc_len);
// 	getcontext(uc);
// 	if (curthread->deferred_siginfo.si_signo == 0) {
// 		curthread->deferred_run = 0;
// 		return;
// 	}
// 	__fillcontextx2((char *)uc);
// 	act = curthread->deferred_sigact;
// 	uc->uc_sigmask = curthread->deferred_sigmask;
// 	memcpy(&info, &curthread->deferred_siginfo, sizeof(siginfo_t));
// 	/* remove signal */
// 	curthread->deferred_siginfo.si_signo = 0;
// 	handle_signal(&act, info.si_signo, &info, uc);
// }
// 
// static void
// check_suspend(struct pthread *curthread)
// {
// 	uint32_t cycle;
// 
// 	if (__predict_true((curthread->flags &
// 		(THR_FLAGS_NEED_SUSPEND | THR_FLAGS_SUSPENDED))
// 		!= THR_FLAGS_NEED_SUSPEND))
// 		return;
// 	if (curthread == _single_thread)
// 		return;
// 	if (curthread->force_exit)
// 		return;
// 
// 	/* 
// 	 * Blocks SIGCANCEL which other threads must send.
// 	 */
// 	_thr_signal_block(curthread);
// 
// 	/*
// 	 * Increase critical_count, here we don't use THR_LOCK/UNLOCK
// 	 * because we are leaf code, we don't want to recursively call
// 	 * ourself.
// 	 */
// 	curthread->critical_count++;
// 	THR_UMUTEX_LOCK(curthread, &(curthread)->lock);
// 	while ((curthread->flags & THR_FLAGS_NEED_SUSPEND) != 0) {
// 		curthread->cycle++;
// 		cycle = curthread->cycle;
// 
// 		/* Wake the thread suspending us. */
// 		_thr_umtx_wake(&curthread->cycle, INT_MAX, 0);
// 
// 		/*
// 		 * if we are from pthread_exit, we don't want to
// 		 * suspend, just go and die.
// 		 */
// 		if (curthread->state == PS_DEAD)
// 			break;
// 		curthread->flags |= THR_FLAGS_SUSPENDED;
// 		THR_UMUTEX_UNLOCK(curthread, &(curthread)->lock);
// 		_thr_umtx_wait_uint(&curthread->cycle, cycle, NULL, 0);
// 		THR_UMUTEX_LOCK(curthread, &(curthread)->lock);
// 	}
// 	THR_UMUTEX_UNLOCK(curthread, &(curthread)->lock);
// 	curthread->critical_count--;
// 
// 	_thr_signal_unblock(curthread);
// }
// 
// void
// _thr_signal_init(int dlopened)
// {
// 	struct sigaction act, nact, oact;
// 	struct usigaction *usa;
// 	sigset_t oldset;
// 	int sig, error;
// 
// 	if (dlopened) {
// 		__sys_sigprocmask(SIG_SETMASK, &_thr_maskset, &oldset);
// 		for (sig = 1; sig <= _SIG_MAXSIG; sig++) {
// 			if (sig == SIGCANCEL)
// 				continue;
// 			error = __sys_sigaction(sig, NULL, &oact);
// 			if (error == -1 || oact.sa_handler == SIG_DFL ||
// 			    oact.sa_handler == SIG_IGN)
// 				continue;
// 			usa = __libc_sigaction_slot(sig);
// 			usa->sigact = oact;
// 			nact = oact;
// 			remove_thr_signals(&usa->sigact.sa_mask);
// 			nact.sa_flags &= ~SA_NODEFER;
// 			nact.sa_flags |= SA_SIGINFO;
// 			nact.sa_sigaction = thr_sighandler;
// 			nact.sa_mask = _thr_maskset;
// 			(void)__sys_sigaction(sig, &nact, NULL);
// 		}
// 		__sys_sigprocmask(SIG_SETMASK, &oldset, NULL);
// 	}
// 
// 	/* Install SIGCANCEL handler. */
// 	SIGFILLSET(act.sa_mask);
// 	act.sa_flags = SA_SIGINFO;
// 	act.sa_sigaction = (__siginfohandler_t *)&sigcancel_handler;
// 	__sys_sigaction(SIGCANCEL, &act, NULL);
// 
// 	/* Unblock SIGCANCEL */
// 	SIGEMPTYSET(act.sa_mask);
// 	SIGADDSET(act.sa_mask, SIGCANCEL);
// 	__sys_sigprocmask(SIG_UNBLOCK, &act.sa_mask, NULL);
// }
// 
// void
// _thr_sigact_unload(struct dl_phdr_info *phdr_info __unused)
// {
// #if 0
// 	struct pthread *curthread = _get_curthread();
// 	struct urwlock *rwlp;
// 	struct sigaction *actp;
// 	struct usigaction *usa;
// 	struct sigaction kact;
// 	void (*handler)(int);
// 	int sig;
//  
// 	_thr_signal_block(curthread);
// 	for (sig = 1; sig <= _SIG_MAXSIG; sig++) {
// 		usa = __libc_sigaction_slot(sig);
// 		actp = &usa->sigact;
// retry:
// 		handler = actp->sa_handler;
// 		if (handler != SIG_DFL && handler != SIG_IGN &&
// 		    __elf_phdr_match_addr(phdr_info, handler)) {
// 			rwlp = &usa->lock;
// 			_thr_rwl_wrlock(rwlp);
// 			if (handler != actp->sa_handler) {
// 				_thr_rwl_unlock(rwlp);
// 				goto retry;
// 			}
// 			actp->sa_handler = SIG_DFL;
// 			actp->sa_flags = SA_SIGINFO;
// 			SIGEMPTYSET(actp->sa_mask);
// 			if (__sys_sigaction(sig, NULL, &kact) == 0 &&
// 				kact.sa_handler != SIG_DFL &&
// 				kact.sa_handler != SIG_IGN)
// 				__sys_sigaction(sig, actp, NULL);
// 			_thr_rwl_unlock(rwlp);
// 		}
// 	}
// 	_thr_signal_unblock(curthread);
// #endif
// }
// 
// void
// _thr_signal_prefork(void)
// {
// 	int i;
// 
// 	for (i = 1; i <= _SIG_MAXSIG; ++i)
// 		_thr_rwl_rdlock(&__libc_sigaction_slot(i)->lock);
// }
// 
// void
// _thr_signal_postfork(void)
// {
// 	int i;
// 
// 	for (i = 1; i <= _SIG_MAXSIG; ++i)
// 		_thr_rwl_unlock(&__libc_sigaction_slot(i)->lock);
// }
// 
// void
// _thr_signal_postfork_child(void)
// {
// 	int i;
// 
// 	for (i = 1; i <= _SIG_MAXSIG; ++i) {
// 		bzero(&__libc_sigaction_slot(i) -> lock,
// 		    sizeof(struct urwlock));
// 	}
// }
// 
// void
// _thr_signal_deinit(void)
// {
// }
// 
// int
// __thr_sigaction(int sig, const struct sigaction *act, struct sigaction *oact)
// {
// 	struct sigaction newact, oldact, oldact2;
// 	sigset_t oldset;
// 	struct usigaction *usa;
// 	int ret, err;
// 
// 	if (!_SIG_VALID(sig) || sig == SIGCANCEL) {
// 		errno = EINVAL;
// 		return (-1);
// 	}
// 
// 	ret = 0;
// 	err = 0;
// 	usa = __libc_sigaction_slot(sig);
// 
// 	__sys_sigprocmask(SIG_SETMASK, &_thr_maskset, &oldset);
// 	_thr_rwl_wrlock(&usa->lock);
//  
// 	if (act != NULL) {
// 		oldact2 = usa->sigact;
// 		newact = *act;
// 
//  		/*
// 		 * if a new sig handler is SIG_DFL or SIG_IGN,
// 		 * don't remove old handler from __libc_sigact[],
// 		 * so deferred signals still can use the handlers,
// 		 * multiple threads invoking sigaction itself is
// 		 * a race condition, so it is not a problem.
// 		 */
// 		if (newact.sa_handler != SIG_DFL &&
// 		    newact.sa_handler != SIG_IGN) {
// 			usa->sigact = newact;
// 			remove_thr_signals(&usa->sigact.sa_mask);
// 			newact.sa_flags &= ~SA_NODEFER;
// 			newact.sa_flags |= SA_SIGINFO;
// 			newact.sa_sigaction = thr_sighandler;
// 			newact.sa_mask = _thr_maskset; /* mask all signals */
// 		}
// 		ret = __sys_sigaction(sig, &newact, &oldact);
// 		if (ret == -1) {
// 			err = errno;
// 			usa->sigact = oldact2;
// 		}
// 	} else if (oact != NULL) {
// 		ret = __sys_sigaction(sig, NULL, &oldact);
// 		err = errno;
// 	}
// 
// 	if (oldact.sa_handler != SIG_DFL && oldact.sa_handler != SIG_IGN) {
// 		if (act != NULL)
// 			oldact = oldact2;
// 		else if (oact != NULL)
// 			oldact = usa->sigact;
// 	}
// 
// 	_thr_rwl_unlock(&usa->lock);
// 	__sys_sigprocmask(SIG_SETMASK, &oldset, NULL);
// 
// 	if (ret == 0) {
// 		if (oact != NULL)
// 			*oact = oldact;
// 	} else {
// 		errno = err;
// 	}
// 	return (ret);
// }
// 
// int
// __thr_sigprocmask(int how, const sigset_t *set, sigset_t *oset)
// {
// 	const sigset_t *p = set;
// 	sigset_t newset;
// 
// 	if (how != SIG_UNBLOCK) {
// 		if (set != NULL) {
// 			newset = *set;
// 			SIGDELSET(newset, SIGCANCEL);
// 			p = &newset;
// 		}
// 	}
// 	return (__sys_sigprocmask(how, p, oset));
// }
// 
// __weak_reference(_thr_sigmask, pthread_sigmask);
// __weak_reference(_thr_sigmask, _pthread_sigmask);
// 
// int
// _thr_sigmask(int how, const sigset_t *set, sigset_t *oset)
// {
// 
// 	if (__thr_sigprocmask(how, set, oset))
// 		return (errno);
// 	return (0);
// }
// 
// int
// _sigsuspend(const sigset_t * set)
// {
// 	sigset_t newset;
// 
// 	return (__sys_sigsuspend(thr_remove_thr_signals(set, &newset)));
// }
// 
// int
// __thr_sigsuspend(const sigset_t * set)
// {
// 	struct pthread *curthread;
// 	sigset_t newset;
// 	int ret, old;
// 
// 	curthread = _get_curthread();
// 
// 	old = curthread->in_sigsuspend;
// 	curthread->in_sigsuspend = 1;
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_sigsuspend(thr_remove_thr_signals(set, &newset));
// 	_thr_cancel_leave(curthread, 1);
// 	curthread->in_sigsuspend = old;
// 	if (curthread->unblock_sigcancel) {
// 		curthread->unblock_sigcancel = 0;
// 		SIGEMPTYSET(newset);
// 		SIGADDSET(newset, SIGCANCEL);
// 		__sys_sigprocmask(SIG_UNBLOCK, &newset, NULL);
// 	}
// 
// 	return (ret);
// }
// 
// int
// _sigtimedwait(const sigset_t *set, siginfo_t *info,
// 	const struct timespec * timeout)
// {
// 	sigset_t newset;
// 
// 	return (__sys_sigtimedwait(thr_remove_thr_signals(set, &newset), info,
// 	    timeout));
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, if thread got signal,
//  *   it is not canceled.
//  */
// int
// __thr_sigtimedwait(const sigset_t *set, siginfo_t *info,
//     const struct timespec * timeout)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	sigset_t newset;
// 	int ret;
// 
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_sigtimedwait(thr_remove_thr_signals(set, &newset), info,
// 	    timeout);
// 	_thr_cancel_leave(curthread, (ret == -1));
// 	return (ret);
// }
// 
// int
// _sigwaitinfo(const sigset_t *set, siginfo_t *info)
// {
// 	sigset_t newset;
// 
// 	return (__sys_sigwaitinfo(thr_remove_thr_signals(set, &newset), info));
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, if thread got signal,
//  *   it is not canceled.
//  */ 
// int
// __thr_sigwaitinfo(const sigset_t *set, siginfo_t *info)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	sigset_t newset;
// 	int ret;
// 
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_sigwaitinfo(thr_remove_thr_signals(set, &newset), info);
// 	_thr_cancel_leave(curthread, ret == -1);
// 	return (ret);
// }
// 
// int
// _sigwait(const sigset_t *set, int *sig)
// {
// 	sigset_t newset;
// 
// 	return (__sys_sigwait(thr_remove_thr_signals(set, &newset), sig));
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, if thread got signal,
//  *   it is not canceled.
//  */ 
// int
// __thr_sigwait(const sigset_t *set, int *sig)
// {
// 	struct pthread	*curthread = _get_curthread();
// 	sigset_t newset;
// 	int ret;
// 
// 	do {
// 		_thr_cancel_enter(curthread);
// 		ret = __sys_sigwait(thr_remove_thr_signals(set, &newset), sig);
// 		_thr_cancel_leave(curthread, (ret != 0));
// 	} while (ret == EINTR);
// 	return (ret);
// }
// 
// int
// __thr_setcontext(const ucontext_t *ucp)
// {
// 	ucontext_t uc;
// 
// 	if (ucp == NULL) {
// 		errno = EINVAL;
// 		return (-1);
// 	}
// 	if (!SIGISMEMBER(ucp->uc_sigmask, SIGCANCEL))
// 		return (__sys_setcontext(ucp));
// 	(void) memcpy(&uc, ucp, sizeof(uc));
// 	SIGDELSET(uc.uc_sigmask, SIGCANCEL);
// 	return (__sys_setcontext(&uc));
// }
// 
// int
// __thr_swapcontext(ucontext_t *oucp, const ucontext_t *ucp)
// {
// 	ucontext_t uc;
// 
// 	if (oucp == NULL || ucp == NULL) {
// 		errno = EINVAL;
// 		return (-1);
// 	}
// 	if (SIGISMEMBER(ucp->uc_sigmask, SIGCANCEL)) {
// 		(void) memcpy(&uc, ucp, sizeof(uc));
// 		SIGDELSET(uc.uc_sigmask, SIGCANCEL);
// 		ucp = &uc;
// 	}
// 	return (__sys_swapcontext(oucp, ucp));
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_single_np.c sha256=5faca89c58f402f2807cb64465d1b5e61c10be2fedfe6f5b949d3422726df6e8
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1996 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// __weak_reference(_pthread_single_np, pthread_single_np);
// 
// int
// _pthread_single_np(void)
// {
// 
// 	/* Enter single-threaded (non-POSIX) scheduling mode: */
// 	_pthread_suspend_all_np();
// 	/*
// 	 * XXX - Do we want to do this?
// 	 * __is_threaded = 0;
// 	 */
// 	return (0);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_sleepq.c sha256=dda6afee8ad478fc1bf54ff3e1055830abced1cf22ee0e678ca8ceb6413430a1
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2010 David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include <stdlib.h>
// #include "thr_private.h"
// 
// #define HASHSHIFT	9
// #define HASHSIZE	(1 << HASHSHIFT)
// #define SC_HASH(wchan) ((unsigned)				\
// 	((((uintptr_t)(wchan) >> 3)				\
// 	^ ((uintptr_t)(wchan) >> (HASHSHIFT + 3)))		\
// 	& (HASHSIZE - 1)))
// #define SC_LOOKUP(wc)	&sc_table[SC_HASH(wc)]
// 
// struct sleepqueue_chain {
// 	struct umutex		sc_lock;
// 	int			sc_enqcnt;
// 	LIST_HEAD(, sleepqueue) sc_queues;
// 	int			sc_type;
// };
// 
// static struct sleepqueue_chain  sc_table[HASHSIZE];
// 
// void
// _sleepq_init(void)
// {
// 	int	i;
// 
// 	for (i = 0; i < HASHSIZE; ++i) {
// 		LIST_INIT(&sc_table[i].sc_queues);
// 		_thr_umutex_init(&sc_table[i].sc_lock);
// 	}
// }
// 
// struct sleepqueue *
// _sleepq_alloc(void)
// {
// 	struct sleepqueue *sq;
// 
// 	sq = calloc(1, sizeof(struct sleepqueue));
// 	TAILQ_INIT(&sq->sq_blocked);
// 	SLIST_INIT(&sq->sq_freeq);
// 	return (sq);
// }
// 
// void
// _sleepq_free(struct sleepqueue *sq)
// {
// 	free(sq);
// }
// 
// void
// _sleepq_lock(void *wchan)
// {
// 	struct pthread *curthread = _get_curthread();
// 	struct sleepqueue_chain *sc;
// 
// 	sc = SC_LOOKUP(wchan);
// 	THR_LOCK_ACQUIRE_SPIN(curthread, &sc->sc_lock);
// }
// 
// void
// _sleepq_unlock(void *wchan)
// {
// 	struct sleepqueue_chain *sc;
// 	struct pthread *curthread = _get_curthread();
//                     
// 	sc = SC_LOOKUP(wchan);
// 	THR_LOCK_RELEASE(curthread, &sc->sc_lock);
// }
// 
// static inline struct sleepqueue *
// lookup(struct sleepqueue_chain *sc, void *wchan)
// {
// 	struct sleepqueue *sq;
// 
// 	LIST_FOREACH(sq, &sc->sc_queues, sq_hash)
// 		if (sq->sq_wchan == wchan)
// 			return (sq);
// 	return (NULL);
// }
// 
// struct sleepqueue *
// _sleepq_lookup(void *wchan)
// {
// 	return (lookup(SC_LOOKUP(wchan), wchan));
// }
// 
// void
// _sleepq_add(void *wchan, struct pthread *td)
// {
// 	struct sleepqueue_chain *sc;
// 	struct sleepqueue *sq;
// 
// 	sc = SC_LOOKUP(wchan);
// 	sq = lookup(sc, wchan);
// 	if (sq != NULL) {
// 		SLIST_INSERT_HEAD(&sq->sq_freeq, td->sleepqueue, sq_flink);
// 	} else {
// 		sq = td->sleepqueue;
// 		LIST_INSERT_HEAD(&sc->sc_queues, sq, sq_hash);
// 		sq->sq_wchan = wchan;
// 		/* sq->sq_type = type; */
// 	}
// 	td->sleepqueue = NULL;
// 	td->wchan = wchan;
// 	if (((++sc->sc_enqcnt << _thr_queuefifo) & 0xff) != 0)
// 		TAILQ_INSERT_HEAD(&sq->sq_blocked, td, wle);
// 	else
// 		TAILQ_INSERT_TAIL(&sq->sq_blocked, td, wle);
// }
// 
// int
// _sleepq_remove(struct sleepqueue *sq, struct pthread *td)
// {
// 	int rc;
// 
// 	TAILQ_REMOVE(&sq->sq_blocked, td, wle);
// 	if (TAILQ_EMPTY(&sq->sq_blocked)) {
// 		LIST_REMOVE(sq, sq_hash);
// 		td->sleepqueue = sq;
// 		rc = 0;
// 	} else {
// 		td->sleepqueue = SLIST_FIRST(&sq->sq_freeq);
// 		SLIST_REMOVE_HEAD(&sq->sq_freeq, sq_flink);
// 		rc = 1;
// 	}
// 	td->wchan = NULL;
// 	return (rc);
// }
// 
// void
// _sleepq_drop(struct sleepqueue *sq,
// 	void (*cb)(struct pthread *, void *arg), void *arg)
// {
// 	struct pthread *td;
// 	struct sleepqueue *sq2;
// 
// 	td = TAILQ_FIRST(&sq->sq_blocked);
// 	if (td == NULL)
// 		return;
// 	LIST_REMOVE(sq, sq_hash);
// 	TAILQ_REMOVE(&sq->sq_blocked, td, wle);
// 	if (cb != NULL)
// 		cb(td, arg);
// 	td->sleepqueue = sq;
// 	td->wchan = NULL;
// 	sq2 = SLIST_FIRST(&sq->sq_freeq);
// 	TAILQ_FOREACH(td, &sq->sq_blocked, wle) {
// 		if (cb != NULL)
// 			cb(td, arg);
// 		td->sleepqueue = sq2;
// 		td->wchan = NULL;
// 		sq2 = SLIST_NEXT(sq2, sq_flink);
// 	}
// 	TAILQ_INIT(&sq->sq_blocked);
// 	SLIST_INIT(&sq->sq_freeq);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_spec.c sha256=9241c4755cfa830c479fd5b057e24691ce08c6a1073243b6f370ae2b9cc6109b
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <sys/mman.h>
// #include <signal.h>
// #include <stdlib.h>
// #include <string.h>
// #include <errno.h>
// #include <pthread.h>
// #include "un-namespace.h"
// #include "libc_private.h"
// 
// #include "thr_private.h"
// 
// /* Used in symbol lookup of libthread_db */
// struct pthread_key _thread_keytable[PTHREAD_KEYS_MAX];
// 
// __weak_reference(_thr_key_create, pthread_key_create);
// __weak_reference(_thr_key_create, _pthread_key_create);
// __weak_reference(_thr_key_delete, pthread_key_delete);
// __weak_reference(_thr_key_delete, _pthread_key_delete);
// __weak_reference(_thr_getspecific, pthread_getspecific);
// __weak_reference(_thr_getspecific, _pthread_getspecific);
// __weak_reference(_thr_setspecific, pthread_setspecific);
// __weak_reference(_thr_setspecific, _pthread_setspecific);
// 
// int
// _thr_key_create(pthread_key_t *key, void (*destructor)(void *))
// {
// 	struct pthread *curthread;
// 	int i;
// 
// 	_thr_check_init();
// 
// 	curthread = _get_curthread();
// 
// 	THR_LOCK_ACQUIRE(curthread, &_keytable_lock);
// 	for (i = 0; i < PTHREAD_KEYS_MAX; i++) {
// 
// 		if (_thread_keytable[i].allocated == 0) {
// 			_thread_keytable[i].allocated = 1;
// 			_thread_keytable[i].destructor = destructor;
// 			_thread_keytable[i].seqno++;
// 
// 			THR_LOCK_RELEASE(curthread, &_keytable_lock);
// 			*key = i + 1;
// 			return (0);
// 		}
// 
// 	}
// 	THR_LOCK_RELEASE(curthread, &_keytable_lock);
// 	return (EAGAIN);
// }
// 
// int
// _thr_key_delete(pthread_key_t userkey)
// {
// 	struct pthread *curthread;
// 	int key, ret;
// 
// 	key = userkey - 1;
// 	if ((unsigned int)key >= PTHREAD_KEYS_MAX)
// 		return (EINVAL);
// 	curthread = _get_curthread();
// 	THR_LOCK_ACQUIRE(curthread, &_keytable_lock);
// 	if (_thread_keytable[key].allocated) {
// 		_thread_keytable[key].allocated = 0;
// 		ret = 0;
// 	} else {
// 		ret = EINVAL;
// 	}
// 	THR_LOCK_RELEASE(curthread, &_keytable_lock);
// 	return (ret);
// }
// 
// void 
// _thread_cleanupspecific(void)
// {
// 	struct pthread *curthread;
// 	void (*destructor)(void *);
// 	const void *data;
// 	int i, key;
// 
// 	curthread = _get_curthread();
// 	if (curthread->specific == NULL)
// 		return;
// 	THR_LOCK_ACQUIRE(curthread, &_keytable_lock);
// 	for (i = 0; i < PTHREAD_DESTRUCTOR_ITERATIONS &&
// 	    curthread->specific_data_count > 0; i++) {
// 		for (key = 0; key < PTHREAD_KEYS_MAX &&
// 		    curthread->specific_data_count > 0; key++) {
// 			destructor = NULL;
// 
// 			if (_thread_keytable[key].allocated &&
// 			    (curthread->specific[key].data != NULL)) {
// 				if (curthread->specific[key].seqno ==
// 				    _thread_keytable[key].seqno) {
// 					data = curthread->specific[key].data;
// 					destructor = _thread_keytable[key].
// 					    destructor;
// 				}
// 				curthread->specific[key].data = NULL;
// 				curthread->specific_data_count--;
// 			} else if (curthread->specific[key].data != NULL) {
// 				/* 
// 				 * This can happen if the key is
// 				 * deleted via pthread_key_delete
// 				 * without first setting the value to
// 				 * NULL in all threads.  POSIX says
// 				 * that the destructor is not invoked
// 				 * in this case.
// 				 */
// 				curthread->specific[key].data = NULL;
// 				curthread->specific_data_count--;
// 			}
// 
// 			/*
// 			 * If there is a destructor, call it with the
// 			 * key table entry unlocked.
// 			 */
// 			if (destructor != NULL) {
// 				THR_LOCK_RELEASE(curthread, &_keytable_lock);
// 				destructor(__DECONST(void *, data));
// 				THR_LOCK_ACQUIRE(curthread, &_keytable_lock);
// 			}
// 		}
// 	}
// 	THR_LOCK_RELEASE(curthread, &_keytable_lock);
// 	__thr_free(curthread->specific);
// 	curthread->specific = NULL;
// 	if (curthread->specific_data_count > 0) {
// 		stderr_debug("Thread %p has exited with leftover "
// 		    "thread-specific data after %d destructor iterations\n",
// 		    curthread, PTHREAD_DESTRUCTOR_ITERATIONS);
// 	}
// }
// 
// int 
// _thr_setspecific(pthread_key_t userkey, const void *value)
// {
// 	struct pthread *pthread;
// 	void *tmp;
// 	pthread_key_t key;
// 
// 	key = userkey - 1;
// 	if ((unsigned int)key >= PTHREAD_KEYS_MAX ||
// 	    !_thread_keytable[key].allocated)
// 		return (EINVAL);
// 
// 	pthread = _get_curthread();
// 	if (pthread->specific == NULL) {
// 		tmp = __thr_calloc(PTHREAD_KEYS_MAX,
// 		    sizeof(struct pthread_specific_elem));
// 		if (tmp == NULL)
// 			return (ENOMEM);
// 		pthread->specific = tmp;
// 	}
// 	if (pthread->specific[key].data == NULL) {
// 		if (value != NULL)
// 			pthread->specific_data_count++;
// 	} else if (value == NULL)
// 		pthread->specific_data_count--;
// 	pthread->specific[key].data = value;
// 	pthread->specific[key].seqno = _thread_keytable[key].seqno;
// 	return (0);
// }
// 
// void *
// _thr_getspecific(pthread_key_t userkey)
// {
// 	struct pthread *pthread;
// 	const void *data;
// 	pthread_key_t key;
// 
// 	/* Check if there is specific data. */
// 	key = userkey - 1;
// 	if ((unsigned int)key >= PTHREAD_KEYS_MAX)
// 		return (NULL);
// 
// 	pthread = _get_curthread();
// 	/* Check if this key has been used before. */
// 	if (_thread_keytable[key].allocated && pthread->specific != NULL &&
// 	    pthread->specific[key].seqno == _thread_keytable[key].seqno) {
// 		/* Return the value: */
// 		data = pthread->specific[key].data;
// 	} else {
// 		/*
// 		 * This key has not been used before, so return NULL
// 		 * instead.
// 		 */
// 		data = NULL;
// 	}
// 	return (__DECONST(void *, data));
// }
// 
// void
// _thr_tsd_unload(struct dl_phdr_info *phdr_info)
// {
// 	struct pthread *curthread;
// 	void (*destructor)(void *);
// 	int key;
// 
// 	curthread = _get_curthread();
// 	THR_LOCK_ACQUIRE(curthread, &_keytable_lock);
// 	for (key = 0; key < PTHREAD_KEYS_MAX; key++) {
// 		if (!_thread_keytable[key].allocated)
// 			continue;
// 		destructor = _thread_keytable[key].destructor;
// 		if (destructor == NULL)
// 			continue;
// 		if (__elf_phdr_match_addr(phdr_info, destructor))
// 			_thread_keytable[key].destructor = NULL;
// 	}
// 	THR_LOCK_RELEASE(curthread, &_keytable_lock);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_spinlock.c sha256=1f69fd23ef16cbba16f70ed0633657826efc030a06453b37f2a4004772cd5caf
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1997 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include <sys/cdefs.h>
// #include <sys/types.h>
// #include <pthread.h>
// #include <libc_private.h>
// #include <spinlock.h>
// 
// #include "thr_private.h"
// 
// #define	MAX_SPINLOCKS	72
// 
// /*
//  * These data structures are used to trace all spinlocks
//  * in libc.
//  */
// struct spinlock_extra {
// 	spinlock_t	*owner;
// 	struct umutex	lock;
// };
// 
// static struct umutex		spinlock_static_lock = DEFAULT_UMUTEX;
// static struct spinlock_extra	extra[MAX_SPINLOCKS];
// static int			spinlock_count;
// static int			initialized;
// 
// static void	init_spinlock(spinlock_t *lck);
// 
// /*
//  * These are for compatibility only.  Spinlocks of this type
//  * are deprecated.
//  */
// 
// void
// __thr_spinunlock(spinlock_t *lck)
// {
// 	struct spinlock_extra	*_extra;
// 
// 	_extra = lck->thr_extra;
// 	THR_UMUTEX_UNLOCK(_get_curthread(), &_extra->lock);
// }
// 
// void
// __thr_spinlock(spinlock_t *lck)
// {
// 	struct spinlock_extra *_extra;
// 
// 	if (!_thr_isthreaded())
// 		PANIC("Spinlock called when not threaded.");
// 	if (!initialized)
// 		PANIC("Spinlocks not initialized.");
// 	if (lck->thr_extra == NULL)
// 		init_spinlock(lck);
// 	_extra = lck->thr_extra;
// 	THR_UMUTEX_LOCK(_get_curthread(), &_extra->lock);
// }
// 
// static void
// init_spinlock(spinlock_t *lck)
// {
// 	struct pthread *curthread = _get_curthread();
// 
// 	THR_UMUTEX_LOCK(curthread, &spinlock_static_lock);
// 	if ((lck->thr_extra == NULL) && (spinlock_count < MAX_SPINLOCKS)) {
// 		lck->thr_extra = &extra[spinlock_count];
// 		_thr_umutex_init(&extra[spinlock_count].lock);
// 		extra[spinlock_count].owner = lck;
// 		spinlock_count++;
// 	}
// 	THR_UMUTEX_UNLOCK(curthread, &spinlock_static_lock);
// 	if (lck->thr_extra == NULL)
// 		PANIC("Warning: exceeded max spinlocks");
// }
// 
// void
// _thr_spinlock_init(void)
// {
// 	int i;
// 
// 	_thr_umutex_init(&spinlock_static_lock);
// 	if (initialized != 0) {
// 		/*
// 		 * called after fork() to reset state of libc spin locks,
// 		 * it is not quite right since libc may be in inconsistent
// 		 * state, resetting the locks to allow current thread to be
// 		 * able to hold them may not help things too much, but
// 		 * anyway, we do our best.
// 		 * it is better to do pthread_atfork in libc.
// 		 */
// 		for (i = 0; i < spinlock_count; i++)
// 			_thr_umutex_init(&extra[i].lock);
// 	} else {
// 		initialized = 1;
// 	}
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_stack.c sha256=35e067c8b47becac48824b5cae27e65ba5a11cdaa138dd84d130352dc63b4968
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2001 Daniel Eischen <deischen@freebsd.org>
//  * Copyright (c) 2000-2001 Jason Evans <jasone@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include <sys/cdefs.h>
// #include <sys/param.h>
// #include <sys/auxv.h>
// #include <sys/mman.h>
// #include <sys/queue.h>
// #include <sys/resource.h>
// #include <sys/sysctl.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <link.h>
// 
// #include "thr_private.h"
// 
// /* Spare thread stack. */
// struct stack {
// 	LIST_ENTRY(stack)	qe;		/* Stack queue linkage. */
// 	size_t			stacksize;	/* Stack size (rounded up). */
// 	size_t			guardsize;	/* Guard size. */
// 	void			*stackaddr;	/* Stack address. */
// };
// 
// /*
//  * Default sized (stack and guard) spare stack queue.  Stacks are cached
//  * to avoid additional complexity managing mmap()ed stack regions.  Spare
//  * stacks are used in LIFO order to increase cache locality.
//  */
// static LIST_HEAD(, stack)	dstackq = LIST_HEAD_INITIALIZER(dstackq);
// 
// /*
//  * Miscellaneous sized (non-default stack and/or guard) spare stack queue.
//  * Stacks are cached to avoid additional complexity managing mmap()ed
//  * stack regions.  This list is unordered, since ordering on both stack
//  * size and guard size would be more trouble than it's worth.  Stacks are
//  * allocated from this cache on a first size match basis.
//  */
// static LIST_HEAD(, stack)	mstackq = LIST_HEAD_INITIALIZER(mstackq);
// 
// /**
//  * Base address of the last stack allocated (including its red zone, if
//  * there is one).  Stacks are allocated contiguously, starting beyond the
//  * top of the main stack.  When a new stack is created, a red zone is
//  * typically created (actually, the red zone is mapped with PROT_NONE) above
//  * the top of the stack, such that the stack will not be able to grow all
//  * the way to the bottom of the next stack.  This isn't fool-proof.  It is
//  * possible for a stack to grow by a large amount, such that it grows into
//  * the next stack, and as long as the memory within the red zone is never
//  * accessed, nothing will prevent one thread stack from trouncing all over
//  * the next.
//  *
//  * low memory
//  *     . . . . . . . . . . . . . . . . . . 
//  *    |                                   |
//  *    |             stack 3               | start of 3rd thread stack
//  *    +-----------------------------------+
//  *    |                                   |
//  *    |       Red Zone (guard page)       | red zone for 2nd thread
//  *    |                                   |
//  *    +-----------------------------------+
//  *    |  stack 2 - _thr_stack_default     | top of 2nd thread stack
//  *    |                                   |
//  *    |                                   |
//  *    |                                   |
//  *    |                                   |
//  *    |             stack 2               |
//  *    +-----------------------------------+ <-- start of 2nd thread stack
//  *    |                                   |
//  *    |       Red Zone                    | red zone for 1st thread
//  *    |                                   |
//  *    +-----------------------------------+
//  *    |  stack 1 - _thr_stack_default     | top of 1st thread stack
//  *    |                                   |
//  *    |                                   |
//  *    |                                   |
//  *    |                                   |
//  *    |             stack 1               |
//  *    +-----------------------------------+ <-- start of 1st thread stack
//  *    |                                   |   (initial value of last_stack)
//  *    |       Red Zone                    |
//  *    |                                   | red zone for main thread
//  *    +-----------------------------------+
//  *    | USRSTACK - _thr_stack_initial     | top of main thread stack
//  *    |                                   | ^
//  *    |                                   | |
//  *    |                                   | |
//  *    |                                   | | stack growth
//  *    |                                   |
//  *    +-----------------------------------+ <-- start of main thread stack
//  *                                              (USRSTACK)
//  * high memory
//  *
//  */
// static char *last_stack = NULL;
// 
// /*
//  * Round size up to the nearest multiple of
//  * _thr_page_size.
//  */
// static inline size_t
// round_up(size_t size)
// {
// 	if (size % _thr_page_size != 0)
// 		size = ((size / _thr_page_size) + 1) *
// 		    _thr_page_size;
// 	return size;
// }
// 
// void
// _thr_stack_fix_protection(struct pthread *thrd)
// {
// 
// 	mprotect((char *)thrd->attr.stackaddr_attr +
// 	    round_up(thrd->attr.guardsize_attr),
// 	    round_up(thrd->attr.stacksize_attr),
// 	    _rtld_get_stack_prot());
// }
// 
// static void
// singlethread_map_stacks_exec(void)
// {
// 	char *usrstack;
// 	size_t stacksz;
// 
// 	if (!__thr_get_main_stack_base(&usrstack) ||
// 	    !__thr_get_main_stack_lim(&stacksz))
// 		return;
// 	mprotect(usrstack - stacksz, stacksz, _rtld_get_stack_prot());
// }
// 
// void
// __thr_map_stacks_exec(void)
// {
// 	struct pthread *curthread, *thrd;
// 	struct stack *st;
// 
// 	if (!_thr_is_inited()) {
// 		singlethread_map_stacks_exec();
// 		return;
// 	}
// 	curthread = _get_curthread();
// 	THREAD_LIST_RDLOCK(curthread);
// 	LIST_FOREACH(st, &mstackq, qe)
// 		mprotect((char *)st->stackaddr + st->guardsize, st->stacksize,
// 		    _rtld_get_stack_prot());
// 	LIST_FOREACH(st, &dstackq, qe)
// 		mprotect((char *)st->stackaddr + st->guardsize, st->stacksize,
// 		    _rtld_get_stack_prot());
// 	TAILQ_FOREACH(thrd, &_thread_gc_list, gcle)
// 		_thr_stack_fix_protection(thrd);
// 	TAILQ_FOREACH(thrd, &_thread_list, tle)
// 		_thr_stack_fix_protection(thrd);
// 	THREAD_LIST_UNLOCK(curthread);
// }
// 
// int
// _thr_stack_alloc(struct pthread_attr *attr)
// {
// 	struct pthread *curthread = _get_curthread();
// 	struct stack *spare_stack;
// 	size_t stacksize;
// 	size_t guardsize;
// 	char *stackaddr;
// 
// 	/*
// 	 * Round up stack size to nearest multiple of _thr_page_size so
// 	 * that mmap() * will work.  If the stack size is not an even
// 	 * multiple, we end up initializing things such that there is
// 	 * unused space above the beginning of the stack, so the stack
// 	 * sits snugly against its guard.
// 	 */
// 	stacksize = round_up(attr->stacksize_attr);
// 	guardsize = round_up(attr->guardsize_attr);
// 
// 	attr->stackaddr_attr = NULL;
// 	attr->flags &= ~THR_STACK_USER;
// 
// 	/*
// 	 * Use the garbage collector lock for synchronization of the
// 	 * spare stack lists and allocations from usrstack.
// 	 */
// 	THREAD_LIST_WRLOCK(curthread);
// 	/*
// 	 * If the stack and guard sizes are default, try to allocate a stack
// 	 * from the default-size stack cache:
// 	 */
// 	if ((stacksize == THR_STACK_DEFAULT) &&
// 	    (guardsize == _thr_guard_default)) {
// 		if ((spare_stack = LIST_FIRST(&dstackq)) != NULL) {
// 			/* Use the spare stack. */
// 			LIST_REMOVE(spare_stack, qe);
// 			attr->stackaddr_attr = spare_stack->stackaddr;
// 		}
// 	}
// 	/*
// 	 * The user specified a non-default stack and/or guard size, so try to
// 	 * allocate a stack from the non-default size stack cache, using the
// 	 * rounded up stack size (stack_size) in the search:
// 	 */
// 	else {
// 		LIST_FOREACH(spare_stack, &mstackq, qe) {
// 			if (spare_stack->stacksize == stacksize &&
// 			    spare_stack->guardsize == guardsize) {
// 				LIST_REMOVE(spare_stack, qe);
// 				attr->stackaddr_attr = spare_stack->stackaddr;
// 				break;
// 			}
// 		}
// 	}
// 	if (attr->stackaddr_attr != NULL) {
// 		/* A cached stack was found.  Release the lock. */
// 		THREAD_LIST_UNLOCK(curthread);
// 	}
// 	else {
// 		/*
// 		 * Allocate a stack from or below usrstack, depending
// 		 * on the LIBPTHREAD_BIGSTACK_MAIN env variable.
// 		 */
// 		if (last_stack == NULL)
// 			last_stack = _usrstack - _thr_stack_initial -
// 			    _thr_guard_default;
// 
// 		/* Allocate a new stack. */
// 		stackaddr = last_stack - stacksize - guardsize;
// 
// 		/*
// 		 * Even if stack allocation fails, we don't want to try to
// 		 * use this location again, so unconditionally decrement
// 		 * last_stack.  Under normal operating conditions, the most
// 		 * likely reason for an mmap() error is a stack overflow of
// 		 * the adjacent thread stack.
// 		 */
// 		last_stack -= (stacksize + guardsize);
// 
// 		/* Release the lock before mmap'ing it. */
// 		THREAD_LIST_UNLOCK(curthread);
// 
// 		/* Map the stack and guard page together, and split guard
// 		   page from allocated space: */
// 		if ((stackaddr = mmap(stackaddr, stacksize + guardsize,
// 		     _rtld_get_stack_prot(), MAP_STACK,
// 		     -1, 0)) != MAP_FAILED &&
// 		    (guardsize == 0 ||
// 		     mprotect(stackaddr, guardsize, PROT_NONE) == 0)) {
// 			stackaddr += guardsize;
// 		} else {
// 			if (stackaddr != MAP_FAILED)
// 				munmap(stackaddr, stacksize + guardsize);
// 			stackaddr = NULL;
// 		}
// 		attr->stackaddr_attr = stackaddr;
// 	}
// 	if (attr->stackaddr_attr != NULL)
// 		return (0);
// 	else
// 		return (-1);
// }
// 
// /* This function must be called with _thread_list_lock held. */
// void
// _thr_stack_free(struct pthread_attr *attr)
// {
// 	struct stack *spare_stack;
// 
// 	if ((attr != NULL) && ((attr->flags & THR_STACK_USER) == 0)
// 	    && (attr->stackaddr_attr != NULL)) {
// 		spare_stack = (struct stack *)
// 			((char *)attr->stackaddr_attr +
// 			attr->stacksize_attr - sizeof(struct stack));
// 		spare_stack->stacksize = round_up(attr->stacksize_attr);
// 		spare_stack->guardsize = round_up(attr->guardsize_attr);
// 		spare_stack->stackaddr = attr->stackaddr_attr;
// 
// 		if (spare_stack->stacksize == THR_STACK_DEFAULT &&
// 		    spare_stack->guardsize == _thr_guard_default) {
// 			/* Default stack/guard size. */
// 			LIST_INSERT_HEAD(&dstackq, spare_stack, qe);
// 		} else {
// 			/* Non-default stack/guard size. */
// 			LIST_INSERT_HEAD(&mstackq, spare_stack, qe);
// 		}
// 		attr->stackaddr_attr = NULL;
// 	}
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_suspend_np.c sha256=3e1648ff5ac4697ec253631bc1f2d82d4381631749e28ca167243d0aab67e726
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995-1998 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <errno.h>
// #include <pthread.h>
// #include <pthread_np.h>
// #include "un-namespace.h"
// 
// #include "thr_private.h"
// 
// static int suspend_common(struct pthread *, struct pthread *,
// 		int);
// 
// __weak_reference(_pthread_suspend_np, pthread_suspend_np);
// __weak_reference(_pthread_suspend_all_np, pthread_suspend_all_np);
// 
// /* Suspend a thread: */
// int
// _pthread_suspend_np(pthread_t thread)
// {
// 	struct pthread *curthread = _get_curthread();
// 	int ret;
// 
// 	/* Suspending the current thread doesn't make sense. */
// 	if (thread == _get_curthread())
// 		ret = EDEADLK;
// 
// 	/* Add a reference to the thread: */
// 	else if ((ret = _thr_ref_add(curthread, thread, /*include dead*/0))
// 	    == 0) {
// 		/* Lock the threads scheduling queue: */
// 		THR_THREAD_LOCK(curthread, thread);
// 		suspend_common(curthread, thread, 1);
// 		/* Unlock the threads scheduling queue: */
// 		THR_THREAD_UNLOCK(curthread, thread);
// 
// 		/* Don't forget to remove the reference: */
// 		_thr_ref_delete(curthread, thread);
// 	}
// 	return (ret);
// }
// 
// void
// _thr_suspend_all_lock(struct pthread *curthread)
// {
// 	int old;
// 
// 	THR_LOCK_ACQUIRE(curthread, &_suspend_all_lock);
// 	while (_single_thread != NULL) {
// 		old = _suspend_all_cycle;
// 		_suspend_all_waiters++;
// 		THR_LOCK_RELEASE(curthread, &_suspend_all_lock);
// 		_thr_umtx_wait_uint(&_suspend_all_cycle, old, NULL, 0);
// 		THR_LOCK_ACQUIRE(curthread, &_suspend_all_lock);
// 		_suspend_all_waiters--;
// 	}
// 	_single_thread = curthread;
// 	THR_LOCK_RELEASE(curthread, &_suspend_all_lock);
// }
// 
// void
// _thr_suspend_all_unlock(struct pthread *curthread)
// {
// 
// 	THR_LOCK_ACQUIRE(curthread, &_suspend_all_lock);
// 	_single_thread = NULL;
// 	if (_suspend_all_waiters != 0) {
// 		_suspend_all_cycle++;
// 		_thr_umtx_wake(&_suspend_all_cycle, INT_MAX, 0);
// 	}
// 	THR_LOCK_RELEASE(curthread, &_suspend_all_lock);
// }
// 
// void
// _pthread_suspend_all_np(void)
// {
// 	struct pthread *curthread = _get_curthread();
// 	struct pthread *thread;
// 	int old_nocancel;
// 	int ret;
// 
// 	old_nocancel = curthread->no_cancel;
// 	curthread->no_cancel = 1;
// 	_thr_suspend_all_lock(curthread);
// 	THREAD_LIST_RDLOCK(curthread);
// 	TAILQ_FOREACH(thread, &_thread_list, tle) {
// 		if (thread != curthread) {
// 			THR_THREAD_LOCK(curthread, thread);
// 			if (thread->state != PS_DEAD &&
// 	      		   !(thread->flags & THR_FLAGS_SUSPENDED))
// 			    thread->flags |= THR_FLAGS_NEED_SUSPEND;
// 			THR_THREAD_UNLOCK(curthread, thread);
// 		}
// 	}
// 	thr_kill(-1, SIGCANCEL);
// 
// restart:
// 	TAILQ_FOREACH(thread, &_thread_list, tle) {
// 		if (thread != curthread) {
// 			/* First try to suspend the thread without waiting */
// 			THR_THREAD_LOCK(curthread, thread);
// 			ret = suspend_common(curthread, thread, 0);
// 			if (ret == 0) {
// 				THREAD_LIST_UNLOCK(curthread);
// 				/* Can not suspend, try to wait */
// 				THR_REF_ADD(curthread, thread);
// 				suspend_common(curthread, thread, 1);
// 				THR_REF_DEL(curthread, thread);
// 				_thr_try_gc(curthread, thread);
// 				/* thread lock released */
// 
// 				THREAD_LIST_RDLOCK(curthread);
// 				/*
// 				 * Because we were blocked, things may have
// 				 * been changed, we have to restart the
// 				 * process.
// 				 */
// 				goto restart;
// 			}
// 			THR_THREAD_UNLOCK(curthread, thread);
// 		}
// 	}
// 	THREAD_LIST_UNLOCK(curthread);
// 	_thr_suspend_all_unlock(curthread);
// 	curthread->no_cancel = old_nocancel;
// 	_thr_testcancel(curthread);
// }
// 
// static int
// suspend_common(struct pthread *curthread, struct pthread *thread,
// 	int waitok)
// {
// 	uint32_t tmp;
// 
// 	while (thread->state != PS_DEAD &&
// 	      !(thread->flags & THR_FLAGS_SUSPENDED)) {
// 		thread->flags |= THR_FLAGS_NEED_SUSPEND;
// 		/* Thread is in creation. */
// 		if (thread->tid == TID_TERMINATED)
// 			return (1);
// 		tmp = thread->cycle;
// 		_thr_send_sig(thread, SIGCANCEL);
// 		THR_THREAD_UNLOCK(curthread, thread);
// 		if (waitok) {
// 			_thr_umtx_wait_uint(&thread->cycle, tmp, NULL, 0);
// 			THR_THREAD_LOCK(curthread, thread);
// 		} else {
// 			THR_THREAD_LOCK(curthread, thread);
// 			return (0);
// 		}
// 	}
// 
// 	return (1);
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_symbols.c sha256=9f9f6036006d03a7b0fe5a819432106397e1adb13c78b84864f3698c3ec26cef
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 2004 David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include <sys/cdefs.h>
// #include <sys/types.h>
// #include <stddef.h>
// #include <pthread.h>
// #include <rtld.h>
// 
// #include "thr_private.h"
// 
// /* A collection of symbols needed by debugger */
// 
// /* int _libthr_debug */
// int _thread_off_tcb = offsetof(struct pthread, tcb);
// int _thread_off_tid = offsetof(struct pthread, tid);
// int _thread_off_next = offsetof(struct pthread, tle.tqe_next);
// int _thread_off_attr_flags = offsetof(struct pthread, attr.flags);
// int _thread_off_linkmap = offsetof(Obj_Entry, linkmap);
// int _thread_off_tlsindex = offsetof(Obj_Entry, tlsindex);
// int _thread_off_report_events = offsetof(struct pthread, report_events);
// int _thread_off_event_mask = offsetof(struct pthread, event_mask);
// int _thread_off_event_buf = offsetof(struct pthread, event_buf);
// int _thread_size_key = sizeof(struct pthread_key);
// int _thread_off_key_allocated = offsetof(struct pthread_key, allocated);
// int _thread_off_key_destructor = offsetof(struct pthread_key, destructor);
// int _thread_max_keys = PTHREAD_KEYS_MAX;
// int _thread_off_dtv = offsetof(struct tcb, tcb_dtv);
// int _thread_off_state = offsetof(struct pthread, state);
// int _thread_state_running = PS_RUNNING;
// int _thread_state_zoombie = PS_DEAD;
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_syscalls.c sha256=d95b76b4a543c130ddea7fb53ce2239df9fde9d21760a00f2dd0e792f4a653e1
// /*
//  * Copyright (c) 2014 The FreeBSD Foundation.
//  * Copyright (C) 2005 David Xu <davidxu@freebsd.org>.
//  * Copyright (c) 2003 Daniel Eischen <deischen@freebsd.org>.
//  * Copyright (C) 2000 Jason Evans <jasone@freebsd.org>.
//  * All rights reserved.
//  * 
//  * Portions of this software were developed by Konstantin Belousov
//  * under sponsorship from the FreeBSD Foundation.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice(s), this list of conditions and the following disclaimer as
//  *    the first lines of this file unmodified other than the possible
//  *    addition of one or more copyright notices.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice(s), this list of conditions and the following disclaimer in
//  *    the documentation and/or other materials provided with the
//  *    distribution.
//  * 
//  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) ``AS IS'' AND ANY
//  * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) BE
//  * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//  * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
//  * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995-1998 John Birrell <jb@cimlogic.com.au>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  *
//  */
// 
// #include "namespace.h"
// #include <sys/types.h>
// #include <sys/mman.h>
// #include <sys/param.h>
// #include <sys/select.h>
// #include <sys/signalvar.h>
// #include <sys/socket.h>
// #include <sys/stat.h>
// #include <sys/time.h>
// #include <sys/uio.h>
// #include <sys/wait.h>
// #include <aio.h>
// #include <dirent.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <poll.h>
// #include <signal.h>
// #include <stdarg.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <termios.h>
// #include <unistd.h>
// #include <pthread.h>
// #include "un-namespace.h"
// 
// #include "libc_private.h"
// #include "thr_private.h"
// 
// static int
// __thr_accept(int s, struct sockaddr *addr, socklen_t *addrlen)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_accept(s, addr, addrlen);
// 	_thr_cancel_leave(curthread, ret == -1);
// 
//  	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   If thread is canceled, no socket is created.
//  */
// static int
// __thr_accept4(int s, struct sockaddr *addr, socklen_t *addrlen, int flags)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_accept4(s, addr, addrlen, flags);
// 	_thr_cancel_leave(curthread, ret == -1);
// 
//  	return (ret);
// }
// 
// static int
// __thr_aio_suspend(const struct aiocb * const iocbs[], int niocb, const struct
//     timespec *timeout)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_aio_suspend(iocbs, niocb, timeout);
// 	_thr_cancel_leave(curthread, 1);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   According to manual of close(), the file descriptor is always deleted.
//  *   Here, thread is only canceled after the system call, so the file
//  *   descriptor is always deleted despite whether the thread is canceled
//  *   or not.
//  */
// static int
// __thr_close(int fd)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter2(curthread, 0);
// 	ret = __sys_close(fd);
// 	_thr_cancel_leave(curthread, 1);
// 	
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   If the thread is canceled, connection is not made.
//  */
// static int
// __thr_connect(int fd, const struct sockaddr *name, socklen_t namelen)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_connect(fd, name, namelen);
// 	_thr_cancel_leave(curthread, ret == -1);
// 
//  	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   According to specification, only F_SETLKW is a cancellation point.
//  *   Thread is only canceled at start, or canceled if the system call
//  *   is failure, this means the function does not generate side effect
//  *   if it is canceled.
//  */
// static int
// __thr_fcntl(int fd, int cmd, ...)
// {
// 	struct pthread *curthread;
// 	int ret;
// 	va_list	ap;
// 
// 	curthread = _get_curthread();
// 	va_start(ap, cmd);
// 	if (cmd == F_OSETLKW || cmd == F_SETLKW) {
// 		_thr_cancel_enter(curthread);
// 		ret = __sys_fcntl(fd, cmd, va_arg(ap, void *));
// 		_thr_cancel_leave(curthread, ret == -1);
// 	} else {
// 		ret = __sys_fcntl(fd, cmd, va_arg(ap, void *));
// 	}
// 	va_end(ap);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled after system call.
//  */
// static int
// __thr_fsync(int fd)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter2(curthread, 0);
// 	ret = __sys_fsync(fd);
// 	_thr_cancel_leave(curthread, 1);
// 
// 	return (ret);
// }
// 
// static int
// __thr_fdatasync(int fd)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter2(curthread, 0);
// 	ret = __sys_fdatasync(fd);
// 	_thr_cancel_leave(curthread, 1);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled after system call.
//  */
// static int
// __thr_msync(void *addr, size_t len, int flags)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter2(curthread, 0);
// 	ret = __sys_msync(addr, len, flags);
// 	_thr_cancel_leave(curthread, 1);
// 
// 	return (ret);
// }
// 
// static int
// __thr_clock_nanosleep(clockid_t clock_id, int flags,
//     const struct timespec *time_to_sleep, struct timespec *time_remaining)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_clock_nanosleep(clock_id, flags, time_to_sleep,
// 	    time_remaining);
// 	_thr_cancel_leave(curthread, 1);
// 
// 	return (ret);
// }
// 
// static int
// __thr_nanosleep(const struct timespec *time_to_sleep,
//     struct timespec *time_remaining)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_nanosleep(time_to_sleep, time_remaining);
// 	_thr_cancel_leave(curthread, 1);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   If the thread is canceled, file is not opened.
//  */
// static int
// __thr_openat(int fd, const char *path, int flags, ...)
// {
// 	struct pthread *curthread;
// 	int mode, ret;
// 	va_list	ap;
// 
// 	
// 	/* Check if the file is being created: */
// 	if ((flags & O_CREAT) != 0) {
// 		/* Get the creation mode: */
// 		va_start(ap, flags);
// 		mode = va_arg(ap, int);
// 		va_end(ap);
// 	} else {
// 		mode = 0;
// 	}
// 	
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_openat(fd, path, flags, mode);
// 	_thr_cancel_leave(curthread, ret == -1);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call returns something,
//  *   the thread is not canceled.
//  */
// static int
// __thr_poll(struct pollfd *fds, unsigned int nfds, int timeout)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_poll(fds, nfds, timeout);
// 	_thr_cancel_leave(curthread, ret == -1);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call returns something,
//  *   the thread is not canceled.
//  */
// static int
// __thr_ppoll(struct pollfd pfd[], nfds_t nfds, const struct timespec *
//     timeout, const sigset_t *newsigmask)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_ppoll(pfd, nfds, timeout, newsigmask);
// 	_thr_cancel_leave(curthread, ret == -1);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call returns something,
//  *   the thread is not canceled.
//  */
// static int
// __thr_pselect(int count, fd_set *rfds, fd_set *wfds, fd_set *efds, 
// 	const struct timespec *timo, const sigset_t *mask)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_pselect(count, rfds, wfds, efds, timo, mask);
// 	_thr_cancel_leave(curthread, ret == -1);
// 
// 	return (ret);
// }
// 
// static int
// __thr_kevent(int kq, const struct kevent *changelist, int nchanges,
//     struct kevent *eventlist, int nevents, const struct timespec *timeout)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	if (nevents == 0) {
// 		/*
// 		 * No blocking, do not make the call cancellable.
// 		 */
// 		return (__sys_kevent(kq, changelist, nchanges, eventlist,
// 		    nevents, timeout));
// 	}
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_kevent(kq, changelist, nchanges, eventlist, nevents,
// 	    timeout);
// 	_thr_cancel_leave(curthread, ret == -1 && nchanges == 0);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call got some data, 
//  *   the thread is not canceled.
//  */
// static ssize_t
// __thr_read(int fd, void *buf, size_t nbytes)
// {
// 	struct pthread *curthread;
// 	ssize_t	ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_read(fd, buf, nbytes);
// 	_thr_cancel_leave(curthread, ret == -1);
// 
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call got some data, 
//  *   the thread is not canceled.
//  */
// static ssize_t
// __thr_readv(int fd, const struct iovec *iov, int iovcnt)
// {
// 	struct pthread *curthread;
// 	ssize_t ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_readv(fd, iov, iovcnt);
// 	_thr_cancel_leave(curthread, ret == -1);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call got some data, 
//  *   the thread is not canceled.
//  */
// static ssize_t
// __thr_recvfrom(int s, void *b, size_t l, int f, struct sockaddr *from,
//     socklen_t *fl)
// {
// 	struct pthread *curthread;
// 	ssize_t ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_recvfrom(s, b, l, f, from, fl);
// 	_thr_cancel_leave(curthread, ret == -1);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call got some data, 
//  *   the thread is not canceled.
//  */
// static ssize_t
// __thr_recvmsg(int s, struct msghdr *m, int f)
// {
// 	struct pthread *curthread;
// 	ssize_t ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_recvmsg(s, m, f);
// 	_thr_cancel_leave(curthread, ret == -1);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call returns something,
//  *   the thread is not canceled.
//  */
// static int 
// __thr_select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
// 	struct timeval *timeout)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_select(numfds, readfds, writefds, exceptfds, timeout);
// 	_thr_cancel_leave(curthread, ret == -1);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call sent
//  *   data, the thread is not canceled.
//  */
// static ssize_t
// __thr_sendmsg(int s, const struct msghdr *m, int f)
// {
// 	struct pthread *curthread;
// 	ssize_t ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_sendmsg(s, m, f);
// 	_thr_cancel_leave(curthread, ret <= 0);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call sent some
//  *   data, the thread is not canceled.
//  */
// static ssize_t
// __thr_sendto(int s, const void *m, size_t l, int f, const struct sockaddr *t,
//     socklen_t tl)
// {
// 	struct pthread *curthread;
// 	ssize_t ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_sendto(s, m, l, f, t, tl);
// 	_thr_cancel_leave(curthread, ret <= 0);
// 	return (ret);
// }
// 
// static int
// __thr_system(const char *string)
// {
// 	struct pthread *curthread;
// 	int ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __libc_system(string);
// 	_thr_cancel_leave(curthread, 1);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   If thread is canceled, the system call is not completed,
//  *   this means not all bytes were drained.
//  */
// static int
// __thr_tcdrain(int fd)
// {
// 	struct pthread *curthread;
// 	int ret;
// 	
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __libc_tcdrain(fd);
// 	_thr_cancel_leave(curthread, ret == -1);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call returns
//  *   a child pid, the thread is not canceled.
//  */
// static pid_t
// __thr_wait4(pid_t pid, int *status, int options, struct rusage *rusage)
// {
// 	struct pthread *curthread;
// 	pid_t ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_wait4(pid, status, options, rusage);
// 	_thr_cancel_leave(curthread, ret <= 0);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the system call returns
//  *   a child pid, the thread is not canceled.
//  */
// static pid_t
// __thr_wait6(idtype_t idtype, id_t id, int *status, int options,
//     struct __wrusage *ru, siginfo_t *infop)
// {
// 	struct pthread *curthread;
// 	pid_t ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_wait6(idtype, id, status, options, ru, infop);
// 	_thr_cancel_leave(curthread, ret <= 0);
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the thread wrote some data,
//  *   it is not canceled.
//  */
// static ssize_t
// __thr_write(int fd, const void *buf, size_t nbytes)
// {
// 	struct pthread *curthread;
// 	ssize_t	ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_write(fd, buf, nbytes);
// 	_thr_cancel_leave(curthread, (ret <= 0));
// 	return (ret);
// }
// 
// /*
//  * Cancellation behavior:
//  *   Thread may be canceled at start, but if the thread wrote some data,
//  *   it is not canceled.
//  */
// static ssize_t
// __thr_writev(int fd, const struct iovec *iov, int iovcnt)
// {
// 	struct pthread *curthread;
// 	ssize_t ret;
// 
// 	curthread = _get_curthread();
// 	_thr_cancel_enter(curthread);
// 	ret = __sys_writev(fd, iov, iovcnt);
// 	_thr_cancel_leave(curthread, (ret <= 0));
// 	return (ret);
// }
// 
// void
// __thr_interpose_libc(void)
// {
// 
// 	__set_error_selector(__error_threaded);
// #define	SLOT(name)					\
// 	*(__libc_interposing_slot(INTERPOS_##name)) =	\
// 	    (interpos_func_t)__thr_##name;
// 	SLOT(accept);
// 	SLOT(accept4);
// 	SLOT(aio_suspend);
// 	SLOT(close);
// 	SLOT(connect);
// 	SLOT(fcntl);
// 	SLOT(fsync);
// 	SLOT(fork);
// 	SLOT(msync);
// 	SLOT(nanosleep);
// 	SLOT(openat);
// 	SLOT(poll);
// 	SLOT(pselect);
// 	SLOT(read);
// 	SLOT(readv);
// 	SLOT(recvfrom);
// 	SLOT(recvmsg);
// 	SLOT(select);
// 	SLOT(sendmsg);
// 	SLOT(sendto);
// 	SLOT(setcontext);
// 	SLOT(sigaction);
// 	SLOT(sigprocmask);
// 	SLOT(sigsuspend);
// 	SLOT(sigwait);
// 	SLOT(sigtimedwait);
// 	SLOT(sigwaitinfo);
// 	SLOT(swapcontext);
// 	SLOT(system);
// 	SLOT(tcdrain);
// 	SLOT(wait4);
// 	SLOT(write);
// 	SLOT(writev);
// 	SLOT(spinlock);
// 	SLOT(spinunlock);
// 	SLOT(kevent);
// 	SLOT(wait6);
// 	SLOT(ppoll);
// 	SLOT(map_stacks_exec);
// 	SLOT(fdatasync);
// 	SLOT(clock_nanosleep);
// 	SLOT(pdfork);
// #undef SLOT
// 	*(__libc_interposing_slot(
// 	    INTERPOS__pthread_mutex_init_calloc_cb)) =
// 	    (interpos_func_t)_pthread_mutex_init_calloc_cb;
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_umtx.c sha256=1914a730ddec2d41133dbd4d8471faf1ba41b6999f0f8de1c11377a36d7a7b06
// /*-
//  * SPDX-License-Identifier: BSD-2-Clause
//  *
//  * Copyright (c) 2005 David Xu <davidxu@freebsd.org>
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice unmodified, this list of conditions, and the following
//  *    disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
//  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
//  * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//  * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
//  * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  */
// 
// #include "thr_private.h"
// #include "thr_umtx.h"
// 
// #ifndef HAS__UMTX_OP_ERR
// int _umtx_op_err(void *obj, int op, u_long val, void *uaddr, void *uaddr2)
// {
// 
// 	if (_umtx_op(obj, op, val, uaddr, uaddr2) == -1)
// 		return (errno);
// 	return (0);
// }
// #endif
// 
// void
// _thr_umutex_init(struct umutex *mtx)
// {
// 	static const struct umutex default_mtx = DEFAULT_UMUTEX;
// 
// 	*mtx = default_mtx;
// }
// 
// void
// _thr_urwlock_init(struct urwlock *rwl)
// {
// 	static const struct urwlock default_rwl = DEFAULT_URWLOCK;
// 
// 	*rwl = default_rwl;
// }
// 
// int
// __thr_umutex_lock(struct umutex *mtx, uint32_t id)
// {
// 	uint32_t owner;
// 
// 	if ((mtx->m_flags & (UMUTEX_PRIO_PROTECT | UMUTEX_PRIO_INHERIT)) != 0)
// 		return	(_umtx_op_err(mtx, UMTX_OP_MUTEX_LOCK, 0, 0, 0));
// 
// 	for (;;) {
// 		owner = mtx->m_owner;
// 		if ((owner & ~UMUTEX_CONTESTED) == 0 &&
// 		     atomic_cmpset_acq_32(&mtx->m_owner, owner, id | owner))
// 			return (0);
// 		if (owner == UMUTEX_RB_OWNERDEAD &&
// 		     atomic_cmpset_acq_32(&mtx->m_owner, owner,
// 		     id | UMUTEX_CONTESTED))
// 			return (EOWNERDEAD);
// 		if (owner == UMUTEX_RB_NOTRECOV)
// 			return (ENOTRECOVERABLE);
// 
// 		/* wait in kernel */
// 		_umtx_op_err(mtx, UMTX_OP_MUTEX_WAIT, 0, 0, 0);
// 	}
// }
// 
// #define SPINLOOPS 1000
// 
// int
// __thr_umutex_lock_spin(struct umutex *mtx, uint32_t id)
// {
// 	uint32_t owner;
// 	int count;
// 
// 	if (!_thr_is_smp)
// 		return (__thr_umutex_lock(mtx, id));
// 	if ((mtx->m_flags & (UMUTEX_PRIO_PROTECT | UMUTEX_PRIO_INHERIT)) != 0)
// 		return	(_umtx_op_err(mtx, UMTX_OP_MUTEX_LOCK, 0, 0, 0));
// 
// 	for (;;) {
// 		count = SPINLOOPS;
// 		while (count--) {
// 			owner = mtx->m_owner;
// 			if ((owner & ~UMUTEX_CONTESTED) == 0 &&
// 			    atomic_cmpset_acq_32(&mtx->m_owner, owner,
// 			    id | owner))
// 				return (0);
// 			if (__predict_false(owner == UMUTEX_RB_OWNERDEAD) &&
// 			    atomic_cmpset_acq_32(&mtx->m_owner, owner,
// 			    id | UMUTEX_CONTESTED))
// 				return (EOWNERDEAD);
// 			if (__predict_false(owner == UMUTEX_RB_NOTRECOV))
// 				return (ENOTRECOVERABLE);
// 			CPU_SPINWAIT;
// 		}
// 
// 		/* wait in kernel */
// 		_umtx_op_err(mtx, UMTX_OP_MUTEX_WAIT, 0, 0, 0);
// 	}
// }
// 
// int
// __thr_umutex_timedlock(struct umutex *mtx, uint32_t id,
// 	const struct timespec *abstime)
// {
// 	struct _umtx_time *tm_p, timeout;
// 	size_t tm_size;
// 	uint32_t owner;
// 	int ret;
// 
// 	if (abstime == NULL) {
// 		tm_p = NULL;
// 		tm_size = 0;
// 	} else {
// 		timeout._clockid = CLOCK_REALTIME;
// 		timeout._flags = UMTX_ABSTIME;
// 		timeout._timeout = *abstime;
// 		tm_p = &timeout;
// 		tm_size = sizeof(timeout);
// 	}
// 
// 	for (;;) {
// 		if ((mtx->m_flags & (UMUTEX_PRIO_PROTECT |
// 		    UMUTEX_PRIO_INHERIT)) == 0) {
// 			/* try to lock it */
// 			owner = mtx->m_owner;
// 			if ((owner & ~UMUTEX_CONTESTED) == 0 &&
// 			     atomic_cmpset_acq_32(&mtx->m_owner, owner,
// 			     id | owner))
// 				return (0);
// 			if (__predict_false(owner == UMUTEX_RB_OWNERDEAD) &&
// 			     atomic_cmpset_acq_32(&mtx->m_owner, owner,
// 			     id | UMUTEX_CONTESTED))
// 				return (EOWNERDEAD);
// 			if (__predict_false(owner == UMUTEX_RB_NOTRECOV))
// 				return (ENOTRECOVERABLE);
// 			/* wait in kernel */
// 			ret = _umtx_op_err(mtx, UMTX_OP_MUTEX_WAIT, 0,
// 			    (void *)tm_size, __DECONST(void *, tm_p));
// 		} else {
// 			ret = _umtx_op_err(mtx, UMTX_OP_MUTEX_LOCK, 0, 
// 			    (void *)tm_size, __DECONST(void *, tm_p));
// 			if (ret == 0 || ret == EOWNERDEAD ||
// 			    ret == ENOTRECOVERABLE)
// 				break;
// 		}
// 		if (ret == ETIMEDOUT)
// 			break;
// 	}
// 	return (ret);
// }
// 
// int
// __thr_umutex_unlock(struct umutex *mtx)
// {
// 
// 	return (_umtx_op_err(mtx, UMTX_OP_MUTEX_UNLOCK, 0, 0, 0));
// }
// 
// int
// __thr_umutex_trylock(struct umutex *mtx)
// {
// 
// 	return (_umtx_op_err(mtx, UMTX_OP_MUTEX_TRYLOCK, 0, 0, 0));
// }
// 
// int
// __thr_umutex_set_ceiling(struct umutex *mtx, uint32_t ceiling,
//     uint32_t *oldceiling)
// {
// 
// 	return (_umtx_op_err(mtx, UMTX_OP_SET_CEILING, ceiling, oldceiling, 0));
// }
// 
// int
// _thr_umtx_wait(volatile long *mtx, long id, const struct timespec *timeout)
// {
// 
// 	if (timeout && (timeout->tv_sec < 0 || (timeout->tv_sec == 0 &&
// 	    timeout->tv_nsec <= 0)))
// 		return (ETIMEDOUT);
// 	return (_umtx_op_err(__DEVOLATILE(void *, mtx), UMTX_OP_WAIT, id, 0,
// 	    __DECONST(void*, timeout)));
// }
// 
// int
// _thr_umtx_wait_uint(volatile u_int *mtx, u_int id,
//     const struct timespec *timeout, int shared)
// {
// 
// 	if (timeout && (timeout->tv_sec < 0 || (timeout->tv_sec == 0 &&
// 	    timeout->tv_nsec <= 0)))
// 		return (ETIMEDOUT);
// 	return (_umtx_op_err(__DEVOLATILE(void *, mtx), shared ?
// 	    UMTX_OP_WAIT_UINT : UMTX_OP_WAIT_UINT_PRIVATE, id, 0,
// 	    __DECONST(void*, timeout)));
// }
// 
// int
// _thr_umtx_timedwait_uint(volatile u_int *mtx, u_int id, int clockid,
//     const struct timespec *abstime, int shared)
// {
// 	struct _umtx_time *tm_p, timeout;
// 	size_t tm_size;
// 
// 	if (abstime == NULL) {
// 		tm_p = NULL;
// 		tm_size = 0;
// 	} else {
// 		timeout._clockid = clockid;
// 		timeout._flags = UMTX_ABSTIME;
// 		timeout._timeout = *abstime;
// 		tm_p = &timeout;
// 		tm_size = sizeof(timeout);
// 	}
// 
// 	return (_umtx_op_err(__DEVOLATILE(void *, mtx), shared ?
// 	    UMTX_OP_WAIT_UINT : UMTX_OP_WAIT_UINT_PRIVATE, id,
// 	    (void *)tm_size, __DECONST(void *, tm_p)));
// }
// 
// int
// _thr_umtx_wake(volatile void *mtx, int nr_wakeup, int shared)
// {
// 
// 	return (_umtx_op_err(__DEVOLATILE(void *, mtx), shared ?
// 	    UMTX_OP_WAKE : UMTX_OP_WAKE_PRIVATE, nr_wakeup, 0, 0));
// }
// 
// void
// _thr_ucond_init(struct ucond *cv)
// {
// 
// 	bzero(cv, sizeof(struct ucond));
// }
// 
// int
// _thr_ucond_wait(struct ucond *cv, struct umutex *m,
// 	const struct timespec *timeout, int flags)
// {
// 	struct pthread *curthread;
// 
// 	if (timeout && (timeout->tv_sec < 0 || (timeout->tv_sec == 0 &&
// 	    timeout->tv_nsec <= 0))) {
// 		curthread = _get_curthread();
// 		_thr_umutex_unlock(m, TID(curthread));
//                 return (ETIMEDOUT);
// 	}
// 	return (_umtx_op_err(cv, UMTX_OP_CV_WAIT, flags, m,
// 	    __DECONST(void*, timeout)));
// }
//  
// int
// _thr_ucond_signal(struct ucond *cv)
// {
// 
// 	if (!cv->c_has_waiters)
// 		return (0);
// 	return (_umtx_op_err(cv, UMTX_OP_CV_SIGNAL, 0, NULL, NULL));
// }
// 
// int
// _thr_ucond_broadcast(struct ucond *cv)
// {
// 
// 	if (!cv->c_has_waiters)
// 		return (0);
// 	return (_umtx_op_err(cv, UMTX_OP_CV_BROADCAST, 0, NULL, NULL));
// }
// 
// int
// __thr_rwlock_rdlock(struct urwlock *rwlock, int flags,
// 	const struct timespec *tsp)
// {
// 	struct _umtx_time timeout, *tm_p;
// 	size_t tm_size;
// 
// 	if (tsp == NULL) {
// 		tm_p = NULL;
// 		tm_size = 0;
// 	} else {
// 		timeout._timeout = *tsp;
// 		timeout._flags = UMTX_ABSTIME;
// 		timeout._clockid = CLOCK_REALTIME;
// 		tm_p = &timeout;
// 		tm_size = sizeof(timeout);
// 	}
// 	return (_umtx_op_err(rwlock, UMTX_OP_RW_RDLOCK, flags,
// 	    (void *)tm_size, tm_p));
// }
// 
// int
// __thr_rwlock_wrlock(struct urwlock *rwlock, const struct timespec *tsp)
// {
// 	struct _umtx_time timeout, *tm_p;
// 	size_t tm_size;
// 
// 	if (tsp == NULL) {
// 		tm_p = NULL;
// 		tm_size = 0;
// 	} else {
// 		timeout._timeout = *tsp;
// 		timeout._flags = UMTX_ABSTIME;
// 		timeout._clockid = CLOCK_REALTIME;
// 		tm_p = &timeout;
// 		tm_size = sizeof(timeout);
// 	}
// 	return (_umtx_op_err(rwlock, UMTX_OP_RW_WRLOCK, 0, (void *)tm_size,
// 	    tm_p));
// }
// 
// int
// __thr_rwlock_unlock(struct urwlock *rwlock)
// {
// 
// 	return (_umtx_op_err(rwlock, UMTX_OP_RW_UNLOCK, 0, NULL, NULL));
// }
// 
// void
// _thr_rwl_rdlock(struct urwlock *rwlock)
// {
// 	int ret;
// 
// 	for (;;) {
// 		if (_thr_rwlock_tryrdlock(rwlock, URWLOCK_PREFER_READER) == 0)
// 			return;
// 		ret = __thr_rwlock_rdlock(rwlock, URWLOCK_PREFER_READER, NULL);
// 		if (ret == 0)
// 			return;
// 		if (ret != EINTR)
// 			PANIC("rdlock error");
// 	}
// }
// 
// void
// _thr_rwl_wrlock(struct urwlock *rwlock)
// {
// 	int ret;
// 
// 	for (;;) {
// 		if (_thr_rwlock_trywrlock(rwlock) == 0)
// 			return;
// 		ret = __thr_rwlock_wrlock(rwlock, NULL);
// 		if (ret == 0)
// 			return;
// 		if (ret != EINTR)
// 			PANIC("wrlock error");
// 	}
// }
// 
// void
// _thr_rwl_unlock(struct urwlock *rwlock)
// {
// 
// 	if (_thr_rwlock_unlock(rwlock))
// 		PANIC("unlock error");
// }
// End provenance source

// Provenance source: freebsd/lib/libthr/thread/thr_yield.c sha256=a603b54dbc2fe8624352119358a7129d0d1fcd54ee12d66e8eac04e43f6487d3
// /*-
//  * SPDX-License-Identifier: BSD-3-Clause
//  *
//  * Copyright (c) 1995 John Birrell <jb@cimlogic.com.au>.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the author nor the names of any co-contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY JOHN BIRRELL AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */
// 
// #include "namespace.h"
// #include <pthread.h>
// #include <sched.h>
// #include "un-namespace.h"
// 
// __weak_reference(_pthread_yield, pthread_yield);
// 
// /* Draft 4 yield */
// void
// _pthread_yield(void)
// {
// 
// 	sched_yield();
// }
// End provenance source

#pragma once

#include <sys/cdefs.h>
#include <time.h>
#include <sched.h>
#include <sys/_pthreadtypes.h>
#include <sys/_cpuset.h>
#include <sys/_sigset.h>
#ifndef _SIGSET_T_DECLARED
#define _SIGSET_T_DECLARED
typedef __sigset_t sigset_t;
#endif
#include <llvm-libc-types/pthread_id_np_t.h>
#include <llvm-libc-types/__pthread_once_func_t.h>
#include <llvm-libc-types/__pthread_tss_dtor_t.h>

#define PTHREAD_NULL {0}
#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1
#define PTHREAD_MUTEX_NORMAL 0
#define PTHREAD_MUTEX_ERRORCHECK 1
#define PTHREAD_MUTEX_RECURSIVE 2
#define PTHREAD_MUTEX_DEFAULT PTHREAD_MUTEX_NORMAL
#define PTHREAD_MUTEX_STALLED 0
#define PTHREAD_MUTEX_ROBUST 1
#define PTHREAD_BARRIER_SERIAL_THREAD -1
#define PTHREAD_ONCE_INIT {0}
#define PTHREAD_PROCESS_PRIVATE 0
#define PTHREAD_PROCESS_SHARED 1
#define PTHREAD_SCOPE_SYSTEM 0
#define PTHREAD_SCOPE_PROCESS 1
#define PTHREAD_INHERIT_SCHED 0
#define PTHREAD_EXPLICIT_SCHED 1
#define PTHREAD_MUTEX_INITIALIZER NULL
#define PTHREAD_COND_INITIALIZER NULL
#define PTHREAD_RWLOCK_INITIALIZER NULL
#define PTHREAD_STACK_MIN (1 << 14) // 16KB
#define PTHREAD_RWLOCK_PREFER_READER_NP 0
#define PTHREAD_RWLOCK_PREFER_WRITER_NP 1
#define PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP 2
#define PTHREAD_STACK_DYNAMIC_NP 0

__BEGIN_DECLS
_Noreturn void	pthread_exit(void *);
int	pthread_atfork(void (*)(void), void (*)(void), void (*)(void));
int	pthread_attr_destroy(pthread_attr_t *);
int	pthread_attr_getdetachstate(const pthread_attr_t *, int *);
int	pthread_attr_getguardsize(const pthread_attr_t *__restrict, size_t *__restrict);
int	pthread_attr_getinheritsched(const pthread_attr_t *__restrict, int *__restrict);
int	pthread_attr_getschedparam(const pthread_attr_t *__restrict, struct sched_param *__restrict);
int	pthread_attr_getschedpolicy(const pthread_attr_t *__restrict, int *__restrict);
int	pthread_attr_getscope(const pthread_attr_t *__restrict, int *__restrict);
int	pthread_attr_getstack(const pthread_attr_t *__restrict, void **__restrict, size_t *__restrict);
int	pthread_attr_getstacksize(const pthread_attr_t *__restrict, size_t *__restrict);
int	pthread_attr_init(pthread_attr_t *);
int	pthread_attr_setdetachstate(pthread_attr_t *, int);
int	pthread_attr_setguardsize(pthread_attr_t *, size_t);
int	pthread_attr_setinheritsched(pthread_attr_t *, int);
int	pthread_attr_setschedparam(pthread_attr_t *__restrict, const struct sched_param *__restrict);
int	pthread_attr_setschedpolicy(pthread_attr_t *, int);
int	pthread_attr_setscope(pthread_attr_t *, int);
int	pthread_attr_setstack(pthread_attr_t *, void *, size_t);
int	pthread_attr_setstacksize(pthread_attr_t *, size_t);
int	pthread_barrier_destroy(pthread_barrier_t *);
int	pthread_barrier_destroy(pthread_barrier_t *barrier);
int	pthread_barrier_init(pthread_barrier_t * __restrict barrier, const pthread_barrierattr_t * __restrict attr, unsigned count);
int	pthread_barrier_wait(pthread_barrier_t *);
int	pthread_barrier_wait(pthread_barrier_t *barrier);
int	pthread_barrierattr_destroy(pthread_barrierattr_t *attr);
int	pthread_barrierattr_getpshared(const pthread_barrierattr_t * __restrict attr, int * __restrict pshared);
int	pthread_barrierattr_init(pthread_barrierattr_t *attr);
int	pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared);
int	pthread_cond_broadcast(pthread_cond_t *);
int	pthread_cond_clockwait(pthread_cond_t *__restrict, pthread_mutex_t *__restrict, clockid_t, const struct timespec *__restrict);
int	pthread_cond_destroy(pthread_cond_t *);
int	pthread_cond_init(pthread_cond_t *__restrict, const pthread_condattr_t *__restrict);
int	pthread_cond_signal(pthread_cond_t *);
int	pthread_cond_timedwait(pthread_cond_t *__restrict, pthread_mutex_t *__restrict, const struct timespec *__restrict);
int	pthread_cond_wait(pthread_cond_t *__restrict, pthread_mutex_t *__restrict);
int	pthread_condattr_destroy(pthread_condattr_t *);
int	pthread_condattr_destroy(pthread_condattr_t *attr);
int	pthread_condattr_getclock(const pthread_condattr_t * __restrict attr, clockid_t * __restrict clock_id);
int	pthread_condattr_getclock(const pthread_condattr_t *__restrict, clockid_t *__restrict);
int	pthread_condattr_getpshared(const pthread_condattr_t * __restrict attr, int * __restrict pshared);
int	pthread_condattr_getpshared(const pthread_condattr_t *__restrict, int *__restrict);
int	pthread_condattr_init(pthread_condattr_t *);
int	pthread_condattr_init(pthread_condattr_t *attr);
int	pthread_condattr_setclock(pthread_condattr_t *, clockid_t);
int	pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id);
int	pthread_condattr_setpshared(pthread_condattr_t *, int);
int	pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared);
int	pthread_create(pthread_t * __restrict thread, const pthread_attr_t * __restrict attr, void *(*start_routine) (void *), void * __restrict arg);
int	pthread_detach(pthread_t);
int	pthread_equal(pthread_t, pthread_t);
int	pthread_getaffinity_np(pthread_t td, size_t cpusetsize, cpuset_t *cpusetp);
int	pthread_getattr_np(pthread_t, pthread_attr_t *);
int	pthread_getcpuclockid(pthread_t pthread, clockid_t *clock_id);
int	pthread_getname_np(pthread_t, char *, size_t);
int	pthread_getprio(pthread_t pthread);
int	pthread_getschedparam(pthread_t, int *__restrict, struct sched_param *__restrict);
int	pthread_getstack_np(pthread_t, void **__restrict, size_t *__restrict);
int	pthread_getunique_np(const pthread_t *__restrict, pthread_id_np_t *__restrict);
int	pthread_join(pthread_t, void **);
int	pthread_key_create(pthread_key_t *, __pthread_tss_dtor_t);
int	pthread_key_delete(pthread_key_t);
int	pthread_multi_np(void);
int	pthread_mutex_destroy(pthread_mutex_t *);
int	pthread_mutex_init(pthread_mutex_t *__restrict, const pthread_mutexattr_t *__restrict);
int	pthread_mutex_lock(pthread_mutex_t *);
int	pthread_mutex_trylock(pthread_mutex_t *);
int	pthread_mutex_unlock(pthread_mutex_t *);
int	pthread_mutexattr_destroy(pthread_mutexattr_t *);
int	pthread_mutexattr_getkind_np(pthread_mutexattr_t attr);
int	pthread_mutexattr_getprioceiling(const pthread_mutexattr_t * __restrict mattr, int * __restrict prioceiling);
int	pthread_mutexattr_getprotocol(const pthread_mutexattr_t * __restrict mattr, int * __restrict protocol);
int	pthread_mutexattr_getpshared(const pthread_mutexattr_t *__restrict, int *__restrict);
int	pthread_mutexattr_getpshared(const pthread_mutexattr_t *attr, int *pshared);
int	pthread_mutexattr_getrobust(const pthread_mutexattr_t *__restrict, int *__restrict);
int	pthread_mutexattr_gettype(const pthread_mutexattr_t * __restrict attr, int * __restrict type);
int	pthread_mutexattr_gettype(const pthread_mutexattr_t *__restrict, int *__restrict);
int	pthread_mutexattr_init(pthread_mutexattr_t *);
int	pthread_mutexattr_setkind_np(pthread_mutexattr_t *attr, int kind);
int	pthread_mutexattr_setprioceiling(pthread_mutexattr_t *mattr, int prioceiling);
int	pthread_mutexattr_setprotocol(pthread_mutexattr_t *mattr, int protocol);
int	pthread_mutexattr_setpshared(pthread_mutexattr_t *__restrict, int);
int	pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
int	pthread_mutexattr_setrobust(pthread_mutexattr_t *__restrict, int);
int	pthread_mutexattr_settype(pthread_mutexattr_t *__restrict, int);
int	pthread_once(pthread_once_t *, __pthread_once_func_t);
int	pthread_peekjoin_np(pthread_t pthread, void **thread_return);
int	pthread_resume_np(pthread_t thread);
int	pthread_rwlock_clockrdlock(pthread_rwlock_t *__restrict, clockid_t, const struct timespec *__restrict);
int	pthread_rwlock_clockwrlock(pthread_rwlock_t *__restrict, clockid_t, const struct timespec *__restrict);
int	pthread_rwlock_destroy(pthread_rwlock_t *);
int	pthread_rwlock_init(pthread_rwlock_t *, const pthread_rwlockattr_t *__restrict);
int	pthread_rwlock_rdlock(pthread_rwlock_t *);
int	pthread_rwlock_timedrdlock(pthread_rwlock_t * __restrict rwlock, const struct timespec * __restrict abstime);
int	pthread_rwlock_timedrdlock(pthread_rwlock_t *__restrict, const struct timespec *__restrict);
int	pthread_rwlock_timedwrlock(pthread_rwlock_t * __restrict rwlock, const struct timespec * __restrict abstime);
int	pthread_rwlock_timedwrlock(pthread_rwlock_t *__restrict, const struct timespec *__restrict);
int	pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int	pthread_rwlock_trywrlock(pthread_rwlock_t *);
int	pthread_rwlock_unlock(pthread_rwlock_t *);
int	pthread_rwlock_wrlock(pthread_rwlock_t *);
int	pthread_rwlockattr_destroy(pthread_rwlockattr_t *);
int	pthread_rwlockattr_destroy(pthread_rwlockattr_t *rwlockattr);
int	pthread_rwlockattr_getkind_np(pthread_rwlockattr_t *, int *);
int	pthread_rwlockattr_getpshared(const pthread_rwlockattr_t * __restrict rwlockattr, int * __restrict pshared);
int	pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *, int *);
int	pthread_rwlockattr_init(pthread_rwlockattr_t *);
int	pthread_rwlockattr_init(pthread_rwlockattr_t *rwlockattr);
int	pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *, int);
int	pthread_rwlockattr_setpshared(pthread_rwlockattr_t *, int);
int	pthread_rwlockattr_setpshared(pthread_rwlockattr_t *rwlockattr, int pshared);
int	pthread_setaffinity_np(pthread_t td, size_t cpusetsize, const cpuset_t *cpusetp);
int	pthread_setname_np(pthread_t thread, const char *name);
int	pthread_setname_np(pthread_t, const char *);
int	pthread_setprio(pthread_t pthread, int prio);
int	pthread_setschedparam(pthread_t, int, const struct sched_param *);
int	pthread_setspecific(pthread_key_t, const void *);
int	pthread_single_np(void);
int	pthread_spin_destroy(pthread_spinlock_t *);
int	pthread_spin_destroy(pthread_spinlock_t *lock);
int	pthread_spin_init(pthread_spinlock_t *, int);
int	pthread_spin_init(pthread_spinlock_t *lock, int pshared);
int	pthread_spin_lock(pthread_spinlock_t *);
int	pthread_spin_lock(pthread_spinlock_t *lock);
int	pthread_spin_trylock(pthread_spinlock_t *);
int	pthread_spin_trylock(pthread_spinlock_t *lock);
int	pthread_spin_unlock(pthread_spinlock_t *);
int	pthread_spin_unlock(pthread_spinlock_t *lock);
int	pthread_suspend_np(pthread_t thread);
int	pthread_timedjoin_np(pthread_t pthread, void **thread_return, const struct timespec *abstime);
pthread_id_np_t	pthread_getthreadid_np(void);
pthread_t	pthread_self(void);
void	__pthread_cleanup_pop(int);
void	__pthread_cleanup_push(struct __pthread_cleanup_frame *, void (*)(void *), void *);
void	pthread_exit_mask(void *status, sigset_t *mask);
void	pthread_get_name_np(pthread_t thread, char *buf, size_t len);
void	pthread_resume_all_np(void);
void	pthread_set_name_np(pthread_t thread, const char *name);
void	pthread_suspend_all_np(void);
void	pthread_yield(void);
void *	pthread_getspecific(pthread_key_t);
__END_DECLS
