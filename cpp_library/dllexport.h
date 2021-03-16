#pragma once

#ifdef WIN32
#ifdef CPP_LIBRARY_EXPORTS
#define CPP_LIBRARY_API __declspec(dllexport)
#else
#define CPP_LIBRARY_API __declspec(dllimport)
#endif
#else
#define CPP_LIBRARY_API
#endif