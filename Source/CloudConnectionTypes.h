#ifndef _CLOUDCONNECTIONTYPES_H_
#define _CLOUDCONNECTIONTYPES_H_

/*
- Types definitions required for the Cloud Connection Plugin
- Google Games Services
"all scores are submitted to leaderboards and stored internally as long integers" 
Source: https://developers.google.com/games/services/common/concepts/leaderboards#score_formatting
Google C++ Sample applications use uint64_t as their type to send scores so typedefing it here to use as our format as well
Google Java API submits the score as a java "long"
*/

#if defined(_VISION_ANDROID)
  typedef uint64_t ULONG64;  ///< 64 bit unsigned.
#elif defined(_VISION_IOS)
  typedef uint64_t  ULONG64;  ///< 64 bit unsigned.
#elif defined(_VISION_WIN32)
  typedef unsigned long long ULONG64;   ///< 64 bit unsigned.
#else
#error Cloud Connection Plugin - types not defined for this platform
#endif

#endif