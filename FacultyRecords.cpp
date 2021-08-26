#include "FacultyRecords.h"
using namespace std;

//Default constructor
FacultyRecords::FacultyRecords(){
  //FacultyID = fid;
  numstudents = 0;
  //Creating an array of interger to store advisee Ids
  studentIDs = new int[10];
  studeSize = 0;
  for(int i = 0; i < 10; i++){
    studentIDs[i] = 0;
  }
}
//Overloaded Constructor
FacultyRecords::FacultyRecords(int fid, string n, string lvl, string d){
  FacultyID = fid;
  name = n;
  level = lvl;
  department = d;
  studentIDs = new int[10];
  studeSize = 0;
  for(int i = 0; i < 10; i++){
    studentIDs[i] = 0;
  }
}
//Destructor
FacultyRecords::~FacultyRecords(){
}
//get Faculty ID
int FacultyRecords::getFacultyID(){
  return FacultyID;
}
//set Faculty ID
void FacultyRecords::setFacultyID(int f){
  FacultyID = f;
}
//get Faculty Name
string FacultyRecords::getFacultyName(){
  return name;
}
//set Faculty Name
void FacultyRecords::setFacultyName(string n){
  name = n;
}
//get Faculty Level
string FacultyRecords::getFacultyLevel(){
  return level;
}
//set Faculty Level
void FacultyRecords::setFacultyLevel(string f){
  level = f;
}
// get Faculty Department
string FacultyRecords::getFacultyDepartment(){
  return department;
}
// set Faculty Department
void FacultyRecords::setFacultyDepartment(string f){
  department = f;
}
// Add advisee ID to the Faculty record
void FacultyRecords::addStudentID(int sid){

     for(int i = 0; i < 10 ; i++){
       if(studentIDs[i] == 0){
         studentIDs[i] = sid;
         studeSize++;
         break;
       }
     }
}
// Delete Advisee ID if Student is deleted
void FacultyRecords::deleteStudentID(int sid){
  int ssid = -1;
  for (int i = 0; i < 10; i++){
    if(studentIDs[i] == sid){
      studentIDs[i] = 0;
      studeSize--;
    }
  }
}
// get Student IDs formatted to be written to a file
string FacultyRecords::getStudentIDs(){
  std::string ssid_rec = "";

  for (int i = 0; i < 10; i++){
    if(studentIDs[i] != 0){
      int s = studentIDs[i];
      stringstream ss;
      ss << s;
      string str = ss.str();
      ssid_rec += " / StudentID: " + str;
    }
  }
  //cout << "PRINTING STUDENTID LIST: " << ssid_rec;
  return ssid_rec;
}
//Print all Faculty Advissess
void FacultyRecords::printAllAdvisees(){
  string ssid_rec = "";
  /*if (getNumberStudentsAssigned() == 0) {
    cout << "No Advissess assigned.." << endl;
    return;
  }*/
  for (int i = 0; i < 10; i++){
    if(studentIDs[i] != 0){
      cout << "StudentID: " << studentIDs[i] << endl;
    }
  }
}
//Get Numebr of Students assigned 
int FacultyRecords::getNumberStudentsAssigned() {
   return studeSize;
}
//return Student ID array
int* FacultyRecords::getAdvisees(){
  return studentIDs;
  /*string result = "";
  for(int i = 0; i < 10; i++){
    result += studentIDs[i];
  }*/

}
