#ifndef UTILITIES_GLOBALDEFINITIONS_HPP
#define UTILITIES_GLOBALDEFINITIONS_HPP

// This file holds all globally used constants & types, class (forward)
// declarations and a few frequently used utility functions.
#include <string>

#ifndef ASSERT
#define ASSERT 1
#endif 

//----------------------------------------------------------------------------------------------------
typedef char label_t;
typedef int vertexid_t;
typedef std::string raw_label_t;
typedef std::string string;






//----------------------------------------------------------------------------------------------------
#ifdef ASSERT
#define assert(p, msg)                                                \
   if (!(p)) {                                                        \
     fprintf(stderr, "assert(" #p ") failed file %s, line %d: %s \n", \
             __FILE__, __LINE__, msg);       \
     exit(1); \
   }
#else 
#define assert(p,msg)
#endif 




//----------------------------------------------------------------------------------------------------
#endif
