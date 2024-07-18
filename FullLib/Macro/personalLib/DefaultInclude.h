#ifndef DEFAULTINCLUDE_H
  #define DEFAULTINCLUDE_H

    #include <iostream>
    #include <vector>
    #include <fstream>
    #include <typeinfo>
    #include <algorithm>
    #include <sstream>
    #include <TString.h>
    #include <TSystem.h>

    #ifndef FATAL
      #define FATAL(msg) do { fprintf(stderr, "FATAL: %s\n", msg); gSystem->Exit(1); } while (0)
    #endif
  
    #ifndef GET_BIT
      #define	GET_BIT(x, bit)	((x & (1 << bit)) >> bit)
    #endif

    using namespace std;

#endif

