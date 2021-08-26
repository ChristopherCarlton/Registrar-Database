#include "Tables.h"
using namespace std;

//Default Constructor
Tables::Tables(){
    //studentTable = new BST<StudentRecords>;
}

//Destructor
Tables::~Tables(){

}

//Adds student records to student table
void Tables::addStudent(StudentRecords student){
  StudentTable.insert(student);
}

//Adds faculty records to faculty table
void Tables::addFaculty(FacultyRecords faculty){
  FacultyTable.insert(faculty);
}

//Prints student records ascending order
void Tables::printStudentsAscending(){
  StudentTable.printInOrder();
}

//Prints faculty records in ascending order
void Tables::printFacultyAscending(){
  FacultyTable.printInOrder();
}

//Finds faculty record in faculty table and displays attributes of given faculty given an int id
void Tables::findAndDisplayFaculty(int ID) {
  FacultyRecords f1 = FacultyRecords(ID,"","","");
  FacultyRecords retf = FacultyTable.returnRecord(f1);
  if (retf.getFacultyName() == "") cout << " FAULTY RECORD NOT FOUND...." << endl;
  cout << "FacultyID: " << retf.getFacultyID() << " /" << retf.getFacultyName() << " /" << retf.getFacultyLevel() << " /" << retf.getFacultyDepartment() << retf.getStudentIDs() << endl;
}

//Finds student record in student table and displays attributes of given student given an int id
void Tables::findAndDisplayStudent(int ID){
  StudentRecords s1 = StudentRecords(ID,"","","",0,0);
  StudentRecords rets = StudentTable.returnRecord(s1);
    if(rets.getStudentName() == "") cout << " FAULT RECORD NOT FOUND...." << endl;
    cout << "Student ID: " << rets.getStudentID() <<" /" << rets.getStudentName() << " /" << rets.getStudentLevel() << " /" << rets.getStudentMajor() << "/ GPA:" << rets.getStudentGpa() << endl;
}

//Prints all faculty members in the file database based off ID's in ascending order
void Tables::printAllFacultyToFile(std::ofstream& ofile){
  FacultyTable.printInOrderToFile(ofile);
}

//Prints all student members in the file database based off ID's in ascending order
void Tables::printAllStudentsToFile(std::ofstream& ofile){
  StudentTable.printInOrderToFile(ofile);
}

//Prints all Faculty advisees given a specific faculty member given an int id
void Tables::printAllFacultyAdvisees(int ID){
  FacultyRecords f1 = FacultyRecords(ID,"","","");
  FacultyRecords retf = FacultyTable.returnRecord(f1);
  retf.printAllAdvisees();

}

//Deletes a faculty record given int id representing a faculty record id
void Tables::deleteFaculty(int ID){
  FacultyRecords f1 = FacultyRecords(ID,"","","");
  FacultyRecords retf = FacultyTable.returnRecord(f1);
  int* arr = retf.getAdvisees();
  for(int i = 0; i < 10;i++){
    if(arr[i] != 0){
      StudentRecords s1 = StudentRecords(arr[i],"","","",0,0);
      StudentRecords rets = StudentTable.returnRecord(s1);
      rets.setStudentAdvisorID(-1);
      StudentTable.deleteValue(rets);
      StudentTable.insert(rets);
    }
  }
  FacultyTable.deleteValue(f1);
}

//Deletes a student record given int id representing a student record id
void Tables::deleteStudent(int ID){
  StudentRecords s1 = StudentRecords(ID,"","","",0,0);
  StudentRecords rets = StudentTable.returnRecord(s1);
  int fid = rets.getStudentAdvisorID();
  FacultyRecords f1 = FacultyRecords(fid,"","","");
  FacultyRecords retf = FacultyTable.returnRecord(f1);
  retf.deleteStudentID(ID);
  FacultyTable.deleteValue(retf);
  FacultyTable.insert(retf);
  StudentTable.deleteValue(s1);
}

//Removes an advisee ID from a faculty record given an int id for the faculty record and int id for the student record to be removed
void Tables::removeAdviseeFromFaculty(int fID, int sID){
  FacultyRecords f1 = FacultyRecords(fID,"","","");
  FacultyRecords retf = FacultyTable.returnRecord(f1);
  retf.deleteStudentID(sID);
}

//Changes student records advisor given int id for the student record and int id for the faculty record that will become the advisor
void Tables::changeStudentAdvisor(int sID, int fID){
  StudentRecords s1 = StudentRecords(sID,"","","",0,0);
  FacultyRecords f1 = FacultyRecords(fID,"","","");
  FacultyRecords retf = FacultyTable.returnRecord(f1);
  StudentRecords rets = StudentTable.returnRecord(s1);
  rets.setStudentAdvisorID(fID);
  retf.addStudentID(sID);
  FacultyTable.deleteValue(retf);
  StudentTable.deleteValue(rets);
  FacultyTable.insert(retf);
  StudentTable.insert(rets);
}

//Finds an advisor id of a student record given an int id for the student record
int Tables::findAdvisorID(int ID){
  StudentRecords s1 = StudentRecords(ID,"","","",0,0);
  StudentRecords rets = StudentTable.returnRecord(s1);
  if (rets.getStudentName() == "") cout << " FAULTY RECORD NOT FOUND...." << endl;
  return rets.getStudentAdvisorID();
}

//returns max faculty record id
int Tables::getMaxFacultyID() {
  FacultyRecords retf = FacultyTable.getMax();
  return retf.getFacultyID();
}

//returns max student record id
int Tables::getMaxStudentID(){
  StudentRecords rets = StudentTable.getMax();
  return rets.getStudentID();
}

//deletes all student and faculty records
void Tables::deleteAllRecords() {
  FacultyTable.purgeAllNodes();
  StudentTable.purgeAllNodes();
}
