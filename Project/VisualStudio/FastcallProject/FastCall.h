#pragma once

#ifdef DYNAMIC_EXPORT
#define _API_ __declspec(dllexport)
#else
#define _API_ __declspec(dllimport)
#endif

#ifdef STATIC_LIBRARY
#define EAPI// int
#else
#define EAPI extern "C" _API_
#endif //STATIC_LIBRARY


EAPI double multi(double a, double b);