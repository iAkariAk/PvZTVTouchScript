/*
 * Copyright 2015, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef LIBFFI_TARGET_H
/* Copyright (c) 2009, 2010, 2011, 2012 ARM Ltd.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
``Software''), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED ``AS IS'', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#ifndef LIBFFI_TARGET_H
#define LIBFFI_TARGET_H

#ifndef LIBFFI_H
#error "Please do not include ffitarget.h directly into your source.  Use ffi.h instead."
#endif

#ifndef LIBFFI_ASM
#ifdef __ILP32__
#define FFI_SIZEOF_ARG 8
#define FFI_SIZEOF_JAVA_RAW  4
typedef unsigned long long ffi_arg;
typedef signed long long ffi_sarg;
#elif defined(_M_ARM64)
#define FFI_SIZEOF_ARG 8
typedef unsigned long long ffi_arg;
typedef signed long long ffi_sarg;
#else
typedef unsigned long ffi_arg;
typedef signed long ffi_sarg;
#endif

typedef enum ffi_abi
{
    FFI_FIRST_ABI = 0,
    FFI_SYSV,
    FFI_LAST_ABI,
    FFI_DEFAULT_ABI = FFI_SYSV
} ffi_abi;
#endif

/* ---- Definitions for closures ----------------------------------------- */

#define FFI_CLOSURES 1
#define FFI_NATIVE_RAW_API 0

#if defined (FFI_EXEC_TRAMPOLINE_TABLE) && FFI_EXEC_TRAMPOLINE_TABLE

#ifdef __MACH__
#define FFI_TRAMPOLINE_SIZE 16
#define FFI_TRAMPOLINE_CLOSURE_OFFSET 16
#else
#error "No trampoline table implementation"
#endif

#else
#define FFI_TRAMPOLINE_SIZE 24
#define FFI_TRAMPOLINE_CLOSURE_OFFSET FFI_TRAMPOLINE_SIZE
#endif

#ifdef _M_ARM64
#define FFI_EXTRA_CIF_FIELDS unsigned is_variadic
#endif

/* ---- Internal ---- */

#if defined (__APPLE__)
#define FFI_TARGET_SPECIFIC_VARIADIC
#define FFI_EXTRA_CIF_FIELDS unsigned aarch64_nfixedargs
#elif !defined(_M_ARM64)
/* iOS and Windows reserve x18 for the system.  Disable Go closures until
   a new static chain is chosen.  */
#define FFI_GO_CLOSURES 1
#endif

#ifndef _M_ARM64
/* No complex type on Windows */
#define FFI_TARGET_HAS_COMPLEX_TYPE
#endif

#endif

#endif
