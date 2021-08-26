#ifndef REGISTRAR_OFFICE
#define REGISTRAR_OFFICE
#include <string>
#include "Tables.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "DLList.h"
using namespace std;
//Structure to store Snapshot file names and the User actioned commands 
struct Commands
{
    string facfilename;
    string studfilename;
    string command;
};

class RegistrarOffice{
public:
  RegistrarOffice(); //Default Constructor
  ~RegistrarOffice(); //Desctructor
  void menu(); //displays menue of options for the Registrar Office
  void readFacultyDB(string); //Read faculty records from Faculty DB file
  void readStudentDB(string); //REad student records from Staudent DB file
  void takeSnapShot(int,string);// Write Faculty & Student Tables to snapshot files
  void rollBackOption(); // Present to User to rollback from previously modified databases
private:
  DLList<int> facultyIDs;
  DLList<int> studentIDs;
  DLList<Commands> commandList;
  Commands cmds;
  ofstream ofacfile, ostufile;
};

#endif
