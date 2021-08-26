#ifndef FACULTY_RECORDS
#define FACULTY_RECORDS
#include <string>
#include "BST.h"
#include "DLList.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;


class FacultyRecords{
public:
  FacultyRecords(); //Default constructor
  FacultyRecords(int fid, string n, string lvl, string d); //Overloaded Constructor
  ~FacultyRecords(); // Default Destructor
  int getFacultyID();//get Faculty ID
  void setFacultyID(int f); //set Faculty ID
  string getFacultyName(); //get Faculty name
  void setFacultyName(string n); //set Faculty Name
  string getFacultyLevel(); //get Faculty Level
  void setFacultyLevel(string f); //set Faculty Level
  string getFacultyDepartment(); //get Faculty Department
  void setFacultyDepartment(string f); //set Faculty Department
  string getStudentIDs(); //get ALL StudentIDs in a string
  int getNumberStudentsAssigned();//get number of Student IDs
  void printAllAdvisees(); //print all Advisses 
  int* getAdvisees(); //get all Advisee list
  //overloads less than operator (<) for fauculty records to compare just id#s
  friend bool operator <(const FacultyRecords &f1, const FacultyRecords &f2){
    return (f1.FacultyID < f2.FacultyID);
  }
  //overloads greater than operator (>) for fauculty records to compare just id#s

  friend bool operator >(const FacultyRecords &f1, const FacultyRecords &f2){
    return (f1.FacultyID > f2.FacultyID);
  }
  //overloads equal to than operator (==) for fauculty records to compare just id#s

  friend bool operator ==(const FacultyRecords &f1, const FacultyRecords &f2){
    return (f1.FacultyID == f2.FacultyID);
  }
  //overloads not equal to than operator (!=) for fauculty records to compare just id#s

  friend bool operator !=(const FacultyRecords &f1, const FacultyRecords &f2){
    return !(f1.FacultyID == f2.FacultyID);
  }
  //overloads stream insertion operator (<<) for fauculty records to write output to standard out or to a file

  friend ostream& operator<<(ostream& os, FacultyRecords &f1){
    os << f1.FacultyID << '/' << f1.name << '/' << f1.level << '/' << f1.department;
    if (f1.getNumberStudentsAssigned() > 0) os << f1.getStudentIDs();
    os << endl;
    return os;
  }

  //add Student ID to array
  void addStudentID(int id);
  //delete Student ID from array
  void deleteStudentID(int id);

private:
  int FacultyID;
  string name;
  string level;
  string department;
  int numstudents;
  int* studentIDs;
  int studeSize;
  //BST<int> studentIDs;
};



#endif
