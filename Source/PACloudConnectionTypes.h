#ifndef _PACLOUDCONNECTIONTYPES_H_
#define _PACLOUDCONNECTIONTYPES_H_

#if defined(_VISION_ANDROID)
  typedef uint64_t ULONG64;  ///< 64 bit unsigned.
#elif defined(_VISION_IOS)
  typedef uint64_t  ULONG64;  ///< 64 bit unsigned.
#elif defined(_VISION_WIN32)
  typedef unsigned long long int ULONG64;   ///< 64 bit unsigned.
#else
#error PA Cloud Connection Plugin - types not defined for this platform
#endif

#endif