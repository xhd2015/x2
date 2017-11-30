/**
 * Nov 30, 2017 by 13774
 *
 */

#include <cstring>
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <regex>
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <algorithm>

using namespace std;


template <typename __String>
bool startsWith(const __String &s,const __String &head);


/**
 * 查找__Vector<__Tuple>中__E对应的位置
 */
template <template <class> class __Vector,typename __Tuple,typename __E>
__Tuple find(__Vector<__Tuple> & vec,const __E &e);



