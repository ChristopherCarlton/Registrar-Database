#include "StudentRecords.h"
using namespace std;

//Default student record constructor
StudentRecords::StudentRecords(){
  studentID = -1;
  name = "";
  level = "Freshman";
  major = "Computer Science";
  gpa = 4.0;
  advisorID = -1;
}

//Overloaded student record constructor
StudentRecords::StudentRecords(int id, string n, string lvl, string m, float g, int a){
  studentID = id;
  name = n;
  level = lvl;
  major = m;
  gpa = g;
  advisorID = a;
}

//Destructor
StudentRecords::~StudentRecords(){
}

//returns student record id #
int StudentRecords::getStudentID(){
  return studentID;
}

//sets student record id #
void StudentRecords::setStudentID(int id){
  studentID = id;
}

//gets student record name
string StudentRecords::getStudentName(){
  return name;
}

//sets student record name
void StudentRecords::setStudentName(string n){
  name = n;
}

//gets student record level
string StudentRecords::getStudentLevel(){
  return level;
}

//sets student record level
void StudentRecords::setStudentLevel(string l){
  level = l;
}

//gets student record major
string StudentRecords::getStudentMajor(){
  return major;
}

//sets student record major
void StudentRecords::setStudentMajor(string m){
  major = m;
}

//gets student record gpa
float StudentRecords::getStudentGpa(){
  return gpa;
}

//sets student record gpa
void StudentRecords::setStudentGpa(float g){
  gpa = g;
}

//gets student record Advisor ID
int StudentRecords::getStudentAdvisorID(){
  return advisorID;
}

//sets student record Advisor ID
void StudentRecords::setStudentAdvisorID(int i){
  advisorID = i;
}
