// array.h - v1.0 - Dynamic arrays
// Source: https://github.com/nothings/stb/blob/master/stretchy_buffer.h
//
//    Unlike C++ vector<>, the sx_array has the same
//    semantics as an object that you manually malloc and realloc.
//    The pointer may relocate every time you add a new object
//    to it, so you:
//
//         1. can't take long-term pointers to elements of the array
//         2. have to return the pointer from functions which might expand it
//            (either as a return value or by storing it to a ptr-to-ptr)
//
//    Now you can do the following things with this array:
//
//         sx_array_free(sx_alloc* alloc, TYPE *a)           free the array
//         sx_array_count(TYPE *a)                           the number of elements in the array
//         sx_array_push(sx_alloc* alloc, TYPE *a, TYPE v)   adds v on the end of the array, a la push_back
//         sx_array_add(sx_alloc* alloc, TYPE *a, int n)     adds n uninitialized elements at end of array & returns pointer to first added
//         sx_array_last(TYPE *a)                            returns an lvalue of the last item in the array
//         sx_array_pop(TYPE *a, index)                      removes an element from the array and decreases array count
//         sx_array_pop_last(TYPE *a)                        removes last element from the array and decreases array count
//         a[n]                                              access the nth (counting from 0) element of the array
// Usage:
//       SomeStruct *arr = NULL;
//       while (something)
//       {
//          SomeStruct new_one;
//          new_one.whatever = whatever;
//          new_one.whatup   = whatup;
//          new_one.foobar   = barfoo;
//          sx_array_push(arr, new_one);
//       }
//
//     Note that these are all macros and many of them evaluate
//     their arguments more than once (except for 'v' in sx_array_push), so the arguments should
//     be side-effect-free.
//
//     Note that 'TYPE *a' in sb_push and sb_add must be lvalues
//     so that the library can overwrite the existing pointer if
//     the object has to be reallocated.
//

#pragma once

#ifndef SX_ARRAY_H_
#define SX_ARRAY_H_

#include "allocator.h"

#define sx_array_free(_alloc, a)     ((a) ? sx_free(_alloc,_sx_sbraw(a)),0 : 0)
#define sx_array_push(_alloc, a, v)  (_sx_sbmaybegrow(_alloc, a, 1), (a)[_sx_sbn(a)++] = (v))
#define sx_array_count(a)            ((a) ? _sx_sbn(a) : 0)
#define sx_array_add(_alloc, a, n)   (_sx_sbmaybegrow(_alloc, a, n), _sx_sbn(a)+=(n), &(a)[_sx_sbn(a)-(n)])
#define sx_array_last(a)             ((a)[_sx_sbn(a)-1])
#define sx_array_pop(a, idx)         do { (a)[idx] = sx_array_last(a); --_sx_sbn(a); } while(0)
#define sx_array_pop_last(a)         do { --_sx_sbn(a); } while(0)
#define sx_array_clear(a)            ((a) ? (_sx_sbn(a) = 0) : 0)

#include "inline/array.inl"

#endif  // SX_ARRAY_H_
