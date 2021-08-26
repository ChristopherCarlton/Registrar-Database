#ifndef STUDENT_RECORDS
#define STUDENT_RECORDS
#include <string>
using namespace std;
#include <iostream>

class StudentRecords{
public:
  StudentRecords(); //Default student record constructor
  StudentRecords(int id, string n, string lvl, string m, float g, int a); //Overloaded student record constructor
  ~StudentRecords(); //Destructor
  int getStudentID(); //returns student record id #
  void setStudentID(int id); //sets student record id #
  string getStudentName(); //gets student record name
  void setStudentName(string n); //sets student record name
  string getStudentLevel(); //gets student record level
  void setStudentLevel(string l); //sets student record level
  string getStudentMajor(); //gets student record major
  void setStudentMajor(string m); //sets student record major
  float getStudentGpa(); //gets student record gpa
  void setStudentGpa(float g); //sets student record gpa
  int getStudentAdvisorID(); //gets student record Advisor ID
  void setStudentAdvisorID(int i); //sets student record Advisor ID

  //overloads less than operator (<) for student records to compare just id#s
  friend bool operator <(const StudentRecords &s1, const StudentRecords &s2){
    return (s1.studentID < s2.studentID);
  }

  //overloads greater than operator (>) for student records to compare just id#s
  friend bool operator >(const StudentRecords &s1, const StudentRecords &s2){
    return (s1.studentID > s2.studentID);
  }

  //overloads equal operator (==) for student records to compare just id#s
  friend bool operator ==(const StudentRecords &s1, const StudentRecords &s2){
    return (s1.studentID == s2.studentID);
  }

  //overloads not equal operator (!=) for student records to compare just id#s
  friend bool operator !=(const StudentRecords &s1, const StudentRecords &s2){
    return !(s1.studentID == s2.studentID);
  }

  //overloads cout operator (<<)  for a student record to display all attributes of the student record
  friend ostream& operator<<(ostream& os, const StudentRecords &s1){
    os << s1.studentID << '/' << s1.name << '/' << s1.level << '/' << s1.major << "/GPA: " << s1.gpa << "/AdvisorID: " << s1.advisorID;
    os << endl;
    return os;
  }

private:
  int studentID;
  string name;
  string level;
  string major;
  float gpa;
  int advisorID;


};



#endif
