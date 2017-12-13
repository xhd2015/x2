/*
 * test_all_precompiled.h
 *
 *  Created on: Dec 4, 2017
 *      Author: 13774
 */

#ifndef TEST_ALL_PRECOMPILED_H_
#define TEST_ALL_PRECOMPILED_H_

#include <typeinfo>
#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <regex>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <new>
#include <memory>
#include <type_traits>


using u64_t = unsigned long long;
using u32_t = unsigned int;
using u16_t = unsigned short;
//#define AS_MACRO __attribute__((always_inline)) inline

#define DEOUT()	cout << __func__ << endl
#define DEFUN(name) name(){DEOUT();}

#endif /* TEST_ALL_PRECOMPILED_H_ */
