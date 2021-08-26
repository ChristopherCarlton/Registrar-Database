#include "RegistrarOffice.h"
using namespace std;


Tables *tb;
RegistrarOffice::RegistrarOffice(){

  //Create memory for the Table
   tb = new Tables();
   //By default read records from Student and Faculty Tables
  readStudentDB("student.db");
  readFacultyDB("faculty.db");
}

RegistrarOffice::~RegistrarOffice(){

}
//Present to User the various options until the User decides to Exit
void RegistrarOffice::menu(){
  int options = -1;
  int sid, fid=0;
  int maxfid = 0;
  int maxsid = 0;
  string fname,lname,name, flevel, fdept;
  FacultyRecords fr;
  string sfname, slname, sname, slevel, smajor;
  float sgpa, sadvisorID;
  StudentRecords sr;
  string cmd;
  char command[100];

  string facfilename;
  int fiid;
  while(options != 14){
    cout << "               Main Menu                " << endl;
    cout << "Enter the number corresponding with the action: " << endl;
    cout << "1. Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3. Find and display student information given the students id" << endl;
    cout << "4. Find and display faculty information given the faculty id" << endl;
    cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6. Given a faculty id, print ALL the names and info of his/her advisees." << endl;
    cout << "7. Add a new student" << endl;
    cout << "8. Delete a student given the id" << endl;
    cout << "9. Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id." << endl;
    cout << "11. Change a student’s advisor given the student id and the new faculty id." << endl;
    cout << "12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "13. Rollback" << endl;
    cout << "14. Exit" << endl;
    cout << "Select an Option: " << endl;
    cin >> options;
    switch(options){
      case 1:
        //Print all students and their information (sorted by ascending id #)
        tb->printStudentsAscending();
        break;
      case 2:
        //Print all faculty and their information (sorted by ascending id #)
        tb->printFacultyAscending();
        break;
      case 3:
        //Find and display student information given the students id
        cout << "Enter a StudentID to display info: " << endl;
        cin >> sid ;
        tb->findAndDisplayStudent(sid);
        break;
      case 4:
        //Find and display faculty information given the faculty id
        cout << "Enter a FacultyID to display info: " << endl;
        cin >> fid ;
        tb->findAndDisplayFaculty(fid);
        break;
      case 5:
        //Given a student’s id, print the name and info of their faculty advisor
        cout << "Enter a student’s id to print the name and info of their faculty advisor... " << endl;
        cin >> sid;
        fiid = tb->findAdvisorID(sid);
        tb->findAndDisplayFaculty(fiid);
        break;
      case 6:
        //Given a faculty id, print ALL the names and info of his/her advisees.
        cout << "Select Faculty ID to print all the names and info of his/her advisees..." << endl;
        cin >> fid;
        tb->printAllFacultyAdvisees(fid);
        break;
      case 7:
        //Add a new student
        cout << "Enter First Name: ";
        cin >> sfname;
        cout << "Enter Last Name: ";
        cin >> slname;
        sname = sfname + " " + slname;
        cout << "Level(Single word only): ";
        cin >> slevel;
        cout << "Major(Single word only): ";
        cin >> smajor;
        cout << "GPA: ";
        cin >> sgpa;
        maxsid = tb->getMaxStudentID() + 1; // increment by 1
        sr.setStudentID(maxsid);
        sr.setStudentName(sname);
        sr.setStudentLevel(slevel);
        sr.setStudentMajor(smajor);
        sr.setStudentGpa(sgpa);
        //Take a Snapshot and command used before updating Student Database
        //so that in future if choose to rollback.
        sprintf(command,"Add a New Student %d. ",maxsid);
        takeSnapShot(options,command);
        cout << "Adding New Faculty...with Faculty ID: " << maxfid;
        tb->addStudent(sr);
        break;

      case 8:
        //Delete a student given the id
        cout << "Select Student ID from the below list..." << endl;
        tb->printStudentsAscending();
        cout << "Enter Student ID to be deleted: ";
        cin >> sid;
        //Take a Snapshot and command used before updating Student Database
        //so that in future if choose to rollback.
        sprintf(command,"Delete a student %d.",sid);
        takeSnapShot(options,command);
        tb->deleteStudent(sid);
        break;
      case 9:
        //Add a new faculty member
        cout << "Enter First Name: ";
        cin >> fname;
        cout << "Enter Last Name: ";
        cin >> lname;
        name = fname + " " + lname;
        cout << "Level(Single word only): ";
        cin >> flevel;
        cout << "Dept (Single word only): ";
        cin >> fdept;
        maxfid = tb->getMaxFacultyID() + 1; // increment by 1
        fr.setFacultyID(maxfid);
        fr.setFacultyName(fname);
        fr.setFacultyDepartment(fdept);
        fr.setFacultyLevel(flevel);
        //Take a Snapshot and command used before updating Student Database
        //so that in future if choose to rollback.
        sprintf(command,"Add a New Faculty %d ",maxfid);
        takeSnapShot(options,command);
        cout << "Adding New Faculty...with Faculty ID: " << maxfid;
        tb->addFaculty(fr);
        break;
      case 10:
        //Delete a faculty member given the id.
        cout << "Select Faculty ID from the below list..." << endl;
        tb->printFacultyAscending();
        cout << "Enter Faculty ID to be deleted: ";
        cin >> fid;
        sprintf(command,"Delete a faculty member %d.", fid);
        takeSnapShot(options,command);
        tb->deleteFaculty(fid);

        break;
      case 11:
        //Change a student’s advisor given the student id and the new faculty id.
        cout << "Enter a Student ID: " << endl;
        cin >> sid;
        cout << "Enter a Faculty ID to add an Advisor to the student: " << endl;
        cin >> fid;
        sprintf(command, "Change Student Advisor for %d to a new faculty member %d",sid,fid );
        takeSnapShot(options,command);
        tb->changeStudentAdvisor(sid,fid);
        break;
      case 12:
        //Remove an advisee from a faculty member given the ids
        cout << "Select a Faculty ID and Advisee ID: ";
        tb->printFacultyAscending();
        cin >> fid;
        cout << "Select Advisee ID: " << endl;
        tb->printAllFacultyAdvisees(fid);
        cin >> sid;
        sprintf(command,"Remove Advisee %d  from a faculty member %d. ", sid, fid);
        takeSnapShot(options,command);
        tb->removeAdviseeFromFaculty(fid,sid);
        break;
      case 13:
        //rollback
        rollBackOption();
        break;
        //Rollback
      case 14:
        //Exit
        //Print all Records to  database Files and Exit
        takeSnapShot(options,"Exit");
        break;
      default:
        cout<< "Not a valid entry, try again" << endl;
    }
  }
}

// THis function will take a snapshot of each Database irrespective which DB is updated.
// This is required man the dependency between Student and Faculty relationship
// There are advisees for a faculty.
// For each Student DB version, there will be a Faculty DB version file created.
// DB files are versioned.
// If the user slects 'option-14' which is EXIT, then the records are updated in the
// original faculty.db and student.db files
void RegistrarOffice::takeSnapShot(int option, string command) {
          int indexno = commandList.size();
          char index[100];
          sprintf(index, "%d", indexno);
          string sindex = index;
          //Store which command initiated a snapshot or backup
          cmds.command = command;
          //Create unique file name(s)
          cmds.facfilename= sindex + "_" + "faculty.db";
          cmds.studfilename= sindex + "_" + "student.db";
          cout << "Writing to faculty file: " << cmds.facfilename << endl;
          cout << "Writing to student file: " << cmds.studfilename << endl;

          if (option == 14){ //EXit
              cmds.facfilename = "faculty.db";
              cmds.studfilename = "student.db";
              cmds.command = "Exit";
          }
          //write to snapshot files
          ofacfile.open(cmds.facfilename);
          tb->printAllFacultyToFile(ofacfile);
          ofacfile.close();
          ostufile.open(cmds.studfilename);
          tb->printAllStudentsToFile(ostufile);
          ostufile.close();
          //store the snapshot details in a LList.
          commandList.insertBack(cmds);
}

//Present to ENd User the LAST 5 Snapshot versions and the commands
// used so that the rollback can be done.
//Present to User which DB version to rollback to?
//Re-initialize FacultyTable and StudentTable by reading from the correspondong snaphost
//DB files
void RegistrarOffice::rollBackOption() {

  string menustring;
  std::stringstream ss;
  int rollbackoption = -1;
  if (commandList.size() == 0) {
    cout << "No snapshots available to rollback to..." << endl;
    return;
  }
  cout << "Select one of the snapshots to rollback to.." << endl;
  char count[100];
  string tmp;
  // Present to the User last FIVE snapshots to roll back to.
  for (int i =0; i < commandList.size(); i++) {
    sprintf(count,"%d",i);
    tmp = count;
    cmds = commandList.peek(i);
    if (i < 5) menustring.append(tmp+ "# " + cmds.command + "\n" );
  }
  // Provide to the User to quit Rollback option in case if decides not to rollback.
    menustring.append("6# Quit.");

  if (rollbackoption == 6) return;
  cout << menustring << endl;
  //cout << "Enter: ";
  cin >> rollbackoption;
  if ((rollbackoption <= 5)) {
    //Select the DB filenames from the linked list.
      cmds= commandList.peek(rollbackoption);
      cout << "reading following DBs.." << endl;
      cout << cmds.facfilename << endl;
      cout << cmds.studfilename << endl;
      //Delete all current records in BOTH the tables, student and faculty
      tb->deleteAllRecords();
      cout << "Reading From Backup files.." << endl;
      free(tb);
      //create a New table
      tb = new Tables();
      //Read from snapshot files
      readFacultyDB(cmds.facfilename);
      readStudentDB(cmds.studfilename);
      //Delete the previous rollback command used.
      commandList.removeFrom(rollbackoption);
  }

}
//Read Faculty DB file all records
void RegistrarOffice::readFacultyDB(string file){
  string goldFile = file;
  string line;
  ifstream facfile (goldFile);
  while ( getline (facfile,line) ) {
    stringstream check1(line);
    string intermediate = "";
    DLList<string> tokens;

    // Tokenizing each line with  '/' seperator
    // e.g: 501/Prof. Stacy/Assistance Prof/Zoology  / StudentID: 100 / StudentID: 102
    while(getline(check1, intermediate, '/'))
    {
        tokens.insertBack(intermediate);
    }
    string s = tokens.peek(0);
    stringstream degree(s);
    int x = 0;
    degree >> x;
    //Creating Faculty records
    FacultyRecords fac(x,tokens.peek(1), tokens.peek(2), tokens.peek(3));
    //Adding Student IDs, Advissee IDs to the Integer array
    if(tokens.size() > 4){
      for(int i = 4; i < tokens.size(); i++){
        string temp = tokens.peek(i);
        string act = "";
        for(int j = 0; j < temp.size(); j++){
          if(isdigit(temp[j])){
            act += temp[j];
          }
        }
        fac.addStudentID(stoi(act));
      }
    }

    tb->addFaculty(fac);

  }
  facfile.close();
}
//Read Students records from database file
void RegistrarOffice::readStudentDB(string file) {
  string goldFile = file;
  string line;
  ifstream studfile (goldFile);
  while ( getline (studfile,line) ) {
    stringstream check1(line);
    string intermediate = "";
    DLList<string> tokens;

    // Tokenizing each field  '/' seperator
    // e.g:100/Nicholas Sniff/Freshman/Biology/GPA: 3.5/AdvisorID: 501
    while(getline(check1, intermediate, '/'))
    {
        //cout << "STUDENT TOKEN: " << intermediate << endl;
        tokens.insertBack(intermediate);
    }

    int studentid = 0;
    int facultyid = 0;
    double gpa = 0.0;

    string studentid_str = tokens.peek(0);
    string advisor_str = tokens.peek(5);//Advisor e.g: Advisor ID: 300
    string gpa_str = tokens.peek(4);//GPA e.g: GPA: 4.0

    stringstream studentId(studentid_str);
    stringstream advisorId(advisor_str);
    stringstream gpaNum(gpa_str);

    //Again tokenizing Gpa and Advisor IDs
    string temp;
    while(getline(advisorId, temp, ' '))
    {
        //cout << "advisorId: " << temp;
        facultyid = atoi(temp.c_str());
    }
    while(getline(gpaNum, temp, ' '))
    {
        //cout << "gpaNumumber: " << temp;
        gpa = atof(temp.c_str());
    }

    studentId >> studentid;
    StudentRecords stu(studentid,tokens.peek(1),tokens.peek(2),tokens.peek(3),gpa,facultyid);
    tb->addStudent(stu);
  }
  studfile.close();
}
