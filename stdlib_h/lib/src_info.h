#ifndef SOURCE_CODE_INFO
#define SOURCE_CODE_INFO

/* This header for source code info only */
/* All macros here define nothing, merely just serve as labels */

#define DISABLED(date, bool) bool /* Disable a region (use case with #if) */

#define STD_AVAILABLE   /* A better version of corresponding function, method, object, or variable is available in the standard header*/

#define CORE_H      /* Core - the fundamental building block of the system, and base for inner working implementaton */
#define SYSTEM_H    /* Basic system implementations */
#define PRIVATE     /* Private expressions (not to be confused with public) [usage only for inner implementations] */
#define PUBLIC      /* Public expressions [for public use, API, Function calls] */
#define GLOBAL      /* Global expressions, the value may be modified by one or more of the types above */

#define DEPRECATED(date)  0 /* May work or functional but no longer supported or maintained since {date}*/
#define DEPRECATED_W(date, msg)


#define OBSOLETE     /* Just don't use this anymore, will be completely gone the next update iteration */

/* as a wise man said 
 * "Some believe that nobody in their right mind should make use of the internals of this structure" 
 * (refers to FILE "opaque" internal structure)
*/

#define TEMP    /* Temporary (In progress) the object is under construction */
#define NON_STD /* Non-Standard (implementation may vary in different systems, platforms, or compilers) */

#define SRC_COMPILER(c) c
#define SRC_SYSTEM(sys) sys

#define TEMPSOL /* Temporary Solution (usually brute-forcing) */

/* Experimental methods, implementation might be removed, abandoned, or continued in the future
 * "if it works, don't bother it" */
#define EXPERIMENTAL

/* Opaque type and need not to be worried about its internal library implementation
 * The contents may appear to change greatly on other implementations */
#define OPAQUE_TYPE  

/* defcon threat and its family */
#ifndef DEFCON
// Unknown threat, seems safe but who knows what demon lurking inside, until it making its move... don't say I didn't warn you
#define DEFCON

#define DEFCON_OMEGA /* ... just don't */
#define DEFCON_ALPHA /* still needs debugging and Improvement */
#define DEFCON_BETA  /* Educational purpose Only */

// basically suicide, only the bravest and toughest man can take the risk
// whenever you feel useless, remember, there exist DEFCON 0
#define DEFCON_0 

// using this is PROHIBITED, can cause devastating error and tremendous irreparable damage
#define DEFCON_1 

// using this is highly Discouraged, a simple mistake leads to fatal error and most likely produce dangerous bugs
#define DEFCON_2 

// Use only when necessary, as this abandoning rules set by professionals, "brute force is not always the answer"
#define DEFCON_3

// use if you know what you're doing, the corresponding functions, methods, variables are ignoring common sense
#define DEFCON_4

// who cares about standard, use if you regard yourself as a man
#define DEFCON_5
#endif

// I know.., I'm still learning so please allow me..
#define MAGIC_NUMBER

#endif