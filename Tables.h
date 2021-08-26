#ifndef TABLES_H
#define TABLES_H
#include "StudentRecords.h"
#include "FacultyRecords.h"
#include <string>
using namespace std;

class Tables{
public:
  Tables(); //Default Constructor
  ~Tables(); //Destructor
  void addStudent(StudentRecords student); //Adds student records to student table
  void addFaculty(FacultyRecords faculty); //Adds faculty records to faculty table
  void printStudentsAscending(); //Prints student records ascending order
  void printFacultyAscending(); //Prints faculty records in ascending order
  void findAndDisplayStudent(int ID); //Finds student record in student table and displays attributes of given student given an int id
  void findAndDisplayFaculty(int ID); //Finds faculty record in faculty table and displays attributes of given faculty given an int id
  void printAllFacultyAdvisees(int ID); //Prints all Faculty advisees given a specific faculty member given an int id
  void printAllFacultyToFile(std::ofstream& ofile); //Prints all faculty members in the file database based off ID's in ascending order
  void printAllStudentsToFile(std::ofstream& ofile); //Prints all student members in the file database based off ID's in ascending order
  void deleteFaculty(int ID); //Deletes a faculty record given int id representing a faculty record id
  void deleteStudent(int ID); //Deletes a student record given int id representing a student record id
  void removeAdviseeFromFaculty(int fID, int sID); //Removes an advisee ID from a faculty record given an int id for the faculty record and int id for the student record to be removed
  void changeStudentAdvisor(int sID, int fID); //Changes student records advisor given int id for the student record and int id for the faculty record that will become the advisor
  int findAdvisorID(int ID); //Finds an advisor id of a student record given an int id for the student record
  int  getMaxFacultyID(); //returns max faculty record id
  int getMaxStudentID(); //returns max student record id
  void deleteAllRecords(); //deletes all student and faculty records

private:
  BST<StudentRecords> StudentTable; //table of student records
  BST<FacultyRecords> FacultyTable; //table of faculty records
};

#endif
