#define RunDB_cxx
#include "../include/RunDB.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
using std::string;

//This class has three functions: OpenDB, Query, and CloseDB. The OpenDB and CloseDB method check to see if the database exists and loads it, and the Close terminates the database. Query allows the user to query a user defined table for a specific column.
//Possible future updates include specifying the table to map,
//Remove the map and pass a run number arguement to get run parameters.


RunDB::RunDB(){
  returnvalue = "0";
};

RunDB::~RunDB(){

};

void RunDB::OpenDB( void ){
  //returncode = sqlite3_open("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.1/database/eg1databasecopy.sqlite", &database); //- This is old - 
  returncode = sqlite3_open("/u/home/bclary/eg1analysis/SKIMprotocol/analysiscode_v2.2/analysiscode_v2.1/database/eg1databasecopy.sqlite", &database);
  if( returncode )
    {
      std::cerr << "Can't open database: " << sqlite3_errmsg(database) << "." << std::endl;
      sqlite3_close(database);
      exit(1);
    }
  else {
    //std::cout<< " >> Database opened " << std::endl;
  }
}

std::string RunDB::Query( string tempTable, string tempColumn, int tempRunID ){
												     
  sqlite3_stmt *stmt;
  
  std::string select("SELECT ");
  std::string from(" FROM ");
  std::string where(" WHERE RunID = ");
  std::string runid = std::to_string(tempRunID);
  std::string s_query = select + tempColumn + from + tempTable + where + runid;
  char *sql_query = (char*)s_query.c_str();
  
  returncode = sqlite3_prepare_v2(database, sql_query, s_query.size() + 1, &stmt, 0);  // Alter text after "FROM" for desired table 
  int ncols = sqlite3_column_count(stmt);

  //printf("The statement %s has %d parameters(s).\n", s_query.c_str(), sqlite3_bind_parameter_count(stmt));  
  if (returncode == SQLITE_OK) {
    sqlite3_bind_int(stmt, 0, 1);
  }
  else {
    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(database));
  }
  int step = sqlite3_step(stmt);
    
  if (step == SQLITE_ROW) {  
    //printf("Polarization type is : %s \n", sqlite3_column_text(stmt, 0)) ;
    returnvalue = ((const char*)sqlite3_column_text(stmt, 0));
  }
  sqlite3_finalize(stmt);
  return returnvalue;
}

// Overloading the function here to allow the user to Query Cut Parameters.
// Instead of three arguments there are two: table name and Column.
// Return a string to convert to a double. 
// Commented the original function header out on 2-14-2017 in order for function to check is tempfileinput is in the good run list. 
// Commented out pieces below wil help to return a double is need be
// double RunDB::Query( string tempTable, string tempColumn, string tempfileinput ){
std::string RunDB::Query( string tempTable, string tempColumn, string tempfileinput, string fromwhere ){
  sqlite3_stmt *stmt;
  
  std::string select("SELECT ");
  std::string from(" FROM ");
  std::string where(" WHERE " );
  //std::string tabletype GoodFileID = ");   
  //std::string search = std::to_string(tempfileinput);
  //  std::string s_query = select + tempColumn + from + tempTable + where + tempColumn + " = " + tempfileinput ;

  std::string s_query = select + tempColumn + from + tempTable + where + fromwhere + " = " + tempfileinput ;
  char *sql_query = (char*)s_query.c_str();
  
  returncode = sqlite3_prepare_v2(database, sql_query, s_query.size() + 1, &stmt, 0);  // Alter text after "FROM" for desired table 
  int ncols = sqlite3_column_count(stmt);

  //printf("The statement %s has %d parameters(s).\n", s_query.c_str(), sqlite3_bind_parameter_count(stmt));  
  if (returncode == SQLITE_OK) {
    sqlite3_bind_int(stmt, 0, 1);
  }
  else {
    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(database));
  }
  int step = sqlite3_step(stmt);
  
  if (step == SQLITE_ROW) {  
    //printf("Polarization type is : %s \n", sqlite3_column_text(stmt, 0)) ;
    returnvalue = ((const char*)sqlite3_column_text(stmt, 0));
    //Below code helps to return a variable of type double
    //std::string str(returnvalue);
    //returndouble = std::stof(returnvalue);
       
  }
  sqlite3_finalize(stmt);
  //return returndouble;
  return returnvalue;
}

std::string RunDB::Query( string tempTable, string tempColumn, string tempfileinput){
  sqlite3_stmt *stmt;
  
  std::string select("SELECT ");
  std::string from(" FROM ");
  std::string where(" WHERE " );
  //std::string tabletype GoodFileID = ");   
  //std::string search = std::to_string(tempfileinput);
  //  std::string s_query = select + tempColumn + from + tempTable + where + tempColumn + " = " + tempfileinput ;
  std::string s_query = select + tempColumn + from + tempTable + where + " = " + tempfileinput ;
  char *sql_query = (char*)s_query.c_str();
  
  returncode = sqlite3_prepare_v2(database, sql_query, s_query.size() + 1, &stmt, 0);  // Alter text after "FROM" for desired table 
  int ncols = sqlite3_column_count(stmt);

  //printf("The statement %s has %d parameters(s).\n", s_query.c_str(), sqlite3_bind_parameter_count(stmt));  
  if (returncode == SQLITE_OK) {
    sqlite3_bind_int(stmt, 0, 1);
  }
  else {
    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(database));
  }
  int step = sqlite3_step(stmt);
  
  if (step == SQLITE_ROW) {  
    //printf("Polarization type is : %s \n", sqlite3_column_text(stmt, 0)) ;
    returnvalue = ((const char*)sqlite3_column_text(stmt, 0));
    //Below code helps to return a variable of type double
    //std::string str(returnvalue);
    //returndouble = std::stof(returnvalue);
       
  }
  sqlite3_finalize(stmt);
  //return returndouble;
  return returnvalue;
}
  


void RunDB::CloseDB( void ){
  sqlite3_close(database);
  //std::cout<<" >> Database closed." << std::endl;
}
