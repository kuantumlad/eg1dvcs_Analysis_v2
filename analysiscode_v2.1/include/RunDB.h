#ifndef RunDB_hh
#define RunDB_hh
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
using std::string;

class RunDB{

public:
  RunDB();
  ~RunDB();

  void OpenDB( void );
  string Query( string, string, int );
  string Query( string, string, string, string );
  string Query( string, string, string );
  //  double Query( string, string );
  void CloseDB( void );

  sqlite3 *database;       // database connection
  sqlite3_stmt *stmt;
  int returncode;          // return code
  char *zErrMsg = 0;
  string returnvalue;
  double returndouble;


   std::vector<double> runconfig;
   std::map< int,std::vector<double> > returnmap;
};

#endif
