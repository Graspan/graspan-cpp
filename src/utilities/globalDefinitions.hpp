#ifndef UTILITIES_GLOBALDEFINITIONS_HPP
#define UTILITIES_GLOBALDEFINITIONS_HPP

// This file holds all globally used constants & types, class (forward)
// declarations and a few frequently used utility functions.
#include <string>
#include <iostream>
#include <vector>
#include <set>
using std::vector;
using std::pair;
using std::set;
using std::cout;
using std::endl;

#ifndef ASSERT
#define ASSERT
#endif 

//----------------------------------------------------------------------------------------------------
typedef char label_t;
typedef int vertexid_t;
typedef int partitionid_t;
typedef std::string raw_label_t;
typedef std::string string;

static string GRAP = ".graph";
static string PART = ".partition";
static string BINA = ".binary";
static string HUMA = ".human";

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
