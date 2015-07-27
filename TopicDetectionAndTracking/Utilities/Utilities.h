/* All external dependencies should be put here.
If other .h in this system is already included, no need to include this
file again, since all other .h files would include this file. */

#ifndef UTILITIES_H
#define UTILITIES_H

/* Without this statement, while developing in VS, you have to use functions like
strtok_s instead functions like strtok. We avoid doing it. Because functions like
strtok_s won't work in other platform, e.g., linux. */
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <assert.h>
#include <sstream>
#include <cmath>
#include <cstring>

// please avoid using namespaces
using std::string;
using std::vector;
using std::map;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::stringstream;

#endif
