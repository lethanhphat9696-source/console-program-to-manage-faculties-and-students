#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Student {
    float avg;
    string id;
    string studentName;
    float math;
    float english;
};

struct Faculty {
    string id;
    string studentName;
    int stunum;
    Student* students;
};

bool isnumber(const Faculty* fac, int facnum, const string& id) {
    for (int i = 0; i < facnum; ++i) {
        if (fac[i].id == id) {
            return true;
        }
    }
        return false;
    } 
bool isDuplicateids(const Faculty* fac, int facnum, const string& id){
        for (int i = 0; i < facnum; ++i){
        for (int j = 0; j < fac[i].stunum; ++j) {
            if (fac[i].students[j].id == id) {
                return true;
            }
        }
        }
    
    return false;
}    
bool stop(const Student* students, int index, const string& id) {
    for (int i = 0; i < index; ++i) {
        if (students[i].id == id) {
            return true;
        }
    }
    return false;
}
void inputfaculty(Faculty& faculty, const Faculty* fac, int facnum) {
    while (true) {
     cout << "input faculty info" << endl;
    cout << endl;
        cout << "Enter faculty id: ";
        cin >> faculty.id;
        if (!isnumber(fac, facnum, faculty.id)) {
            break;
        }
        cout << "faculty id already exists. Please enter a unique id.\n";
    }
    
    cout << "enter the name of student: ";
    cin.ignore(); 
    getline(cin, faculty.studentName);
    cout << "input number of student: ";
    cin >> faculty.stunum;
    faculty.students = new Student[faculty.stunum];
    for (int i = 0; i < faculty.stunum; ++i) {
        while (true) {
            cout << "Enter student " << i+1 << " id: ";
            cin >> faculty.students[i].id;
            if (!isDuplicateids(fac, facnum, faculty.students[i].id) && !stop(faculty.students, i, faculty.students[i].id)) {
                break;
            }
            else {
                cout << "Student id already exists. Please enter a unique id.\n";
            }
        }
        
        cout << "Enter student " << i+1 << " studentName: ";
         cin.ignore(); 
        getline(cin, faculty.students[i].studentName);
        cout << "Enter student " << i+1 << " Student math grade: ";
        cin >> faculty.students[i].math;
        cout << "Enter student " << i+1 << " Student english grade: ";
        cin >> faculty.students[i].english;
    }
}
void displayfaculty(const Faculty& faculty) {
    cout << "faculty id: " << faculty.id << endl;
    cout << "faculty studentName: " << faculty.studentName << endl;
    cout << "Number of students: " << faculty.stunum << endl;
    for (int i = 0; i < faculty.stunum; ++i) {
        cout << "         Student " << i+1 <<": "<<endl;
        cout<<  "           id: " << faculty.students[i].id << endl;
        cout << "           studentName: " << faculty.students[i].studentName << endl;
        cout << "           math grade: " << faculty.students[i].math << endl;
        cout << "           english grade: " << faculty.students[i].english << endl;
    }
    cout<<endl;
}
void insertfaculty(Faculty*& fac, int& facnum, int index) {
    Faculty anotherfac;
    inputfaculty(anotherfac, fac, facnum);
    
    if (index >= 0 && index <= facnum) {
        Faculty* temp = new Faculty[facnum + 1];
        for (int i = 0; i < index; ++i) {
            temp[i] = fac[i];
        }
        temp[index] = anotherfac;
        for (int i = index; i < facnum; ++i) {
            temp[i + 1] = fac[i];
        }
        delete[] fac;
        fac = temp;
        facnum++;
        cout << "faculty inserted at index " << index << "." << endl;
    } else {
        cout << "Invalid index. faculty not inserted." << endl;
    }
}
void insertStudents(Faculty* fac, int facnum, const string& facultyid) {
    int facultyIndex = -1;
    for (int i = 0; i < facnum; ++i) {
        if (fac[i].id == facultyid) {
            facultyIndex = i;
            break;
        }
    }
    if (facultyIndex != -1) {
        Faculty& faculty = fac[facultyIndex];
        int studentIndex;
        cout << "input the position you want to add the student: ";
        cin >> studentIndex;
        if (studentIndex >= 0 && studentIndex <= faculty.stunum) {
            Student newStudent;
            while (true) {
                cout << "enter the ID of student: ";
                cin >> newStudent.id;
                if (!isDuplicateids(fac, facnum, newStudent.id)) {
                    break;
                } else {
                    cout << "Student id already exists. Please enter a unique id.\n";
                }
            }
            cout << "Enter student studentName: ";
            cin.ignore(); 
            getline(cin, newStudent.studentName);
            cout << "enter the math grade of student: ";
            cin >> newStudent.math;
            cout << "enter the english grade of student: ";
            cin >> newStudent.english;

            Student* temp = new Student[faculty.stunum + 1];
            for (int i = 0; i < studentIndex; ++i) {
                temp[i] = faculty.students[i];
            }
            temp[studentIndex] = newStudent;
            for (int i = studentIndex; i < faculty.stunum; ++i) {
                temp[i + 1] = faculty.students[i];
            }

            delete[] faculty.students;
            faculty.students = temp;
            faculty.stunum++;
            cout << "Student inserted successfully into the faculty's student list." << endl;
        } else {
            cout << "this is not a valid id, please input again: " << endl;
        }
    } else {
        cout << "faculty with id " << facultyid << " not found." << endl;
    }
}
void deletefaculty(Faculty*& fac, int& facnum, int index) {
    if (index >= 0 && index < facnum) {
        delete[] fac[index].students;
        for (int i = index; i < facnum - 1; ++i) {
            fac[i] = fac[i + 1];
        }
        facnum--;
        cout << "faculty at position " << index << " deleted." << endl;
    } else {
        cout << "Invalid index. faculty not found." << endl;
    }
}
void deleteStudent(Faculty* fac, int facnum, int facultyIndex, int studentIndex) {
    if (facultyIndex >= 0 && facultyIndex < facnum) {
        Faculty& faculty = fac[facultyIndex];
        if (studentIndex >= 0 && studentIndex < faculty.stunum) {
            for (int j = studentIndex; j < faculty.stunum - 1; ++j) {
                faculty.students[j] = faculty.students[j + 1];
            }
            faculty.stunum--;
            cout << "Delete completed!" << endl;
        } else {
            cout << "that not a valid id." << endl;
        }
    } else {
        cout << "Invalid faculty index." << endl;
    }
}
bool swapping(const Student& s1, const Student& s2) {
    return s1.avg < s2.avg; 
}
void showall(const Student* all,int totalStudents){
        cout << left << setw(8) << "id" << " | "
              << setw(20) << "studentName" << " | "
              << setw(13) << "Math Point" << " | "
              << setw(17) << "English Point" << " | "
              << setw(9) << "avgrage" << " |" << endl;
    cout << setfill('-') << setw(75) << "" <<setfill(' ') << endl;
    
    for (int i = 0; i < totalStudents; ++i) {
       cout << left <<setw(8) << all[i].id << " | "
                  << setw(20) << all[i].studentName << " | "
                  << setw(13) << all[i].math << " | "
                  << setw(17) << all[i].english << " | "
                  << setw(9) << all[i].avg << " |" <<endl;
    }
    
}
void averageGrade(Faculty* fac, int facnum){
    int totalStudents = 0;
    for (int i = 0; i < facnum; ++i) {
        totalStudents += fac[i].stunum;
    }
    int currentIndex = 0;
    Student* all = new Student[totalStudents];
    for (int i =0; i<facnum; i++){
        for (int j=0;j<fac[i].stunum; j++){
            fac[i].students[j].avg = (float)(fac[i].students[j].math + fac[i].students[j].english)/2.0f;
            all[currentIndex] = fac[i].students[j];
            currentIndex++;
        }
    }
    sort(all, all + totalStudents, swapping);
    showall(all,totalStudents);
}
void maxAve(Faculty* faculties, int facnum){
    
    int totalStudents = 0;
    for (int i = 0; i < facnum; ++i) {
        totalStudents += faculties[i].stunum;
    }
    float maxAverage = 0;
    int count = 0;
    Student *maxAverageStudent = new Student[totalStudents];
    for (int i =0; i<facnum; i++){
        for (int j=0;j<faculties[i].stunum; j++){
            float avg = (float)(faculties[i].students[j].math + faculties[i].students[j].english)/2.0f;
            if (avg > maxAverage) {
                maxAverage = avg;
                maxAverageStudent[count] = faculties[i].students[j];
            }else if (avg == maxAverage){
                count++;
                maxAverageStudent[count] = faculties[i].students[j];
            }
        }
    }
    cout << "Student with maximum average grade:" << endl;
    for (int i =0; i<count+1; i++){
        cout << "ID: " << maxAverageStudent[i].id << "\nName: " << maxAverageStudent[i].studentName << "\nAverage Grade: " << maxAverage << endl;
        cout<<"-----------\n";
    }
    delete[] maxAverageStudent;
}
void searchid(const Faculty* fac, int facnum) {
    string search;
    cout << "Search by id: ";
    cin >> search;
    bool found = false;
    for (int i = 0; i < facnum; ++i) {
        if (search == fac[i].id) {
            displayfaculty(fac[i]);
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "faculty with id " << search << " not found." << endl;
    }
}


int main() {
    int facnum;
    cout << "input faculty info" << endl;
    cout << endl;
    cout << "input number of fac: ";
    cin >> facnum;

    Faculty* fac = new Faculty[facnum];

    for (int i = 0; i < facnum; ++i) {
        cout << "faculty " << i + 1 << ":" << endl;
        inputfaculty(fac[i], fac, i);
    }

    int choice;
    string facultyid, studentid;
     int facultyIndex4 = -1;

    do {
        cout << "\nplease choose an option\n";
        cout << "1. Insert a faculty (input id)\n";
        cout << "2. Delete a faculty (input id)\n";
        cout << "3. Insert a faculty (input id)\n";
        cout << "4. Delete a student (input id)\n";
        cout << "5. Output faculty Information\n";
        cout << "6. Calculate the average grade\n";
        cout << "7. showall the student with highest average (id, name, grade) \n";
        cout << "8. Search faculty by ID\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
          
               case 1:
    int facultyIndex;
    cout << "Enter the position to insert faculty: ";
    cin >> facultyIndex;
    if (facultyIndex >= 0 && facultyIndex <= facnum) {
        insertfaculty(fac, facnum, facultyIndex);
    } else {
        cout << "Invalid position. Please enter a valid one." << endl;
    }
    break;

            case 2:
    cout << "Enter the position to delete faculty: ";
    cin >> facultyIndex;        
                deletefaculty(fac, facnum, facultyIndex);
                break;
                
            case 3:
                cout << "Enter faculty id to insert student: ";
                cin >> facultyid;
                insertStudents(fac, facnum, facultyid);
                break;
          case 4:
    cout << "Enter faculty id: ";
    cin >> facultyid;
   
    for (int i = 0; i < facnum; ++i) {
        if (fac[i].id == facultyid) {
            facultyIndex4 = i;
            break;
        }
    }
    if (facultyIndex4 != -1) {
        cout << "Enter student position to delete: ";
        int studentIndex;
        cin >> studentIndex;
        deleteStudent(fac, facnum, facultyIndex4, studentIndex);
    } else {
        cout << "faculty with id " << facultyid << " not found." << endl;
    }
    break;

            case 5:
                cout <<"faculty information:"<< endl;
                for (int i = 0; i < facnum; ++i) {
                    displayfaculty(fac[i]);
                }
                break;
            case 6:
                cout<<"Calculating the average grade"<<endl;
                averageGrade(fac,facnum);
                break;
            case 7:
                cout<<"Calculating the max average"<<endl;
                maxAve(fac,facnum);
                break;    
            case 8:
                cout << endl;
                searchid(fac, facnum);
                break; 
            case 9:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Please choose the valid choice between 1-9.\n";
        }
        
    } while (choice != 9);

    for (int i = 0; i < facnum; ++i) {
        delete[] fac[i].students;
    }
    delete[] fac;
    return 0;
}
