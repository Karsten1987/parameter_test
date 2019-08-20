#ifndef PARAMETER_TEST__VISIBILITY_CONTROL_H_
#define PARAMETER_TEST__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define PARAMETER_TEST_EXPORT __attribute__ ((dllexport))
    #define PARAMETER_TEST_IMPORT __attribute__ ((dllimport))
  #else
    #define PARAMETER_TEST_EXPORT __declspec(dllexport)
    #define PARAMETER_TEST_IMPORT __declspec(dllimport)
  #endif
  #ifdef PARAMETER_TEST_BUILDING_LIBRARY
    #define PARAMETER_TEST_PUBLIC PARAMETER_TEST_EXPORT
  #else
    #define PARAMETER_TEST_PUBLIC PARAMETER_TEST_IMPORT
  #endif
  #define PARAMETER_TEST_PUBLIC_TYPE PARAMETER_TEST_PUBLIC
  #define PARAMETER_TEST_LOCAL
#else
  #define PARAMETER_TEST_EXPORT __attribute__ ((visibility("default")))
  #define PARAMETER_TEST_IMPORT
  #if __GNUC__ >= 4
    #define PARAMETER_TEST_PUBLIC __attribute__ ((visibility("default")))
    #define PARAMETER_TEST_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define PARAMETER_TEST_PUBLIC
    #define PARAMETER_TEST_LOCAL
  #endif
  #define PARAMETER_TEST_PUBLIC_TYPE
#endif

#endif  // PARAMETER_TEST__VISIBILITY_CONTROL_H_
