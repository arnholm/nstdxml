#ifndef NSTDXML_CONFIG_H_INCLUDED
#define NSTDXML_CONFIG_H_INCLUDED

#ifdef _MSC_VER

   /// MSVC compiler
   // disabling warning 4251 is the only practical way to deal with dll-export issues according to M$
   #pragma warning (disable:4251) // class "XX" needs to have dll-interface to be used by clients of class "YY"

   #ifdef NSTDXML_IMPLEMENTATION
      #define NSTDXML_PUBLIC __declspec(dllexport)
      #define NSTDXML_EXTERN
   #else
      #define NSTDXML_PUBLIC __declspec(dllimport)
      #define NSTDXML_EXTERN extern
   #endif
   #define NSTDXML_PRIVATE

#elif __GNUC__

   /// gnu gcc

   #define NSTDXML_PUBLIC  __attribute__ ((visibility("default")))
   #define NSTDXML_PRIVATE __attribute__ ((visibility("hidden")))
   #define NSTDXML_EXTERN

#else

  #error "Unknown compiler"

#endif


#endif // NSTDXML_CONFIG_H_INCLUDED

