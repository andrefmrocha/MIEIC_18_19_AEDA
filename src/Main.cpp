/*
 * Main.cpp
 *
 *  Created on: 31/10/2018
 *      Author: anamargaridarl
 */

#include "Person.h"
#include "Court.h"
#include "Calendar.h"
#include "Date.h"
#include "Invoice.h"
#include "Report.h"
#include "Reservation.h"
#include "Company.h"

#include <iostream>
#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MainIntro() {
    cout << "-------------Tenis Company-----------------" << endl;
    cout << "                                         " << endl;
    cout << "Choose option:                           " << endl;
    cout << "                                         " << endl;
    cout << "1.New Company                           " << endl;
    cout << "2.Load Company                            " << endl;
    cout << "3.Exit                                   " << endl;
    cout << "--------------------------------------------" << endl;

    int flag;
    cin >> flag;

    while (flag != 1 && flag != 2 && flag != 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error...Try again: " << endl;
        cin >> flag;
    }

    return flag;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int Menu(const int cardValue) {
    cout << "-------------Company" << cardValue << "-----------------------" << endl;
    cout << "                                         " << endl;
    cout << "Choose option:                           " << endl;
    cout << "                                         " << endl;
    cout << "1.Add Person                             " << endl;
    cout << "2.Add Reservation                        " << endl;
    cout << "3.Add Court                              " << endl;
    cout << "4.Show Person                            " << endl;
    cout << "5.Show Courts                            " << endl;
    cout << "6.Increment day                          " << endl;
    cout << "7.Exit                                   " << endl;
	cout << "----------------------------------------------"<< endl;

    int flag;
    cin >> flag;

    while (flag != 1 && flag != 2 && flag != 3 && flag != 4 && flag != 5 && flag != 6 && flag != 7) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error...Try again: " << endl;
        cin >> flag;
    }

    return flag;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DevelopCompany(Company &C, unsigned int cardValue) {

    string name, gender;
    int age;
    bool isGold;
    int m, d, strH;
    double duration;
    int save;

    int flagMenu = 0;

    while (true) {

        flagMenu = Menu(cardValue);

        switch (flagMenu) {
            case 1: //Add Person
            {
                /////////////////////////////////////////////////////////////
                int flagP;

            	cout << "----------------------------------------------"<< endl;
                cout << "1.Add User" << endl;
                cout << "2.Add Teacher" << endl;
                cout << "3.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagP;

                while (flagP != 1 && flagP != 2 && flagP != 3) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagP;
                }
                /////////////////////////////////////////////////////////////
                if (flagP == 1)
                {
                	 if (C.getTeachers().empty()) {
                 cout << "Can't added Users. Company needs teachers first."      << endl;
                 break;
                	 }
                }

                if (flagP != 3) //Add User or Teacher
                {
                    cin.ignore();
                    cout << "Name: " << endl;
                    getline(cin, name);
                    cout << "Age: " << endl;
                    cin >> age;
                    cout << "Gender" << endl;
                    cin >> gender;

                    if (flagP == 1) //Add User
                    {
                        cout << "Gold Card?" << endl;
                        cout << "Option: 1.yes 0.no " << endl;

                        cin >> isGold;


                        if (!(C.registerUser(name, age, isGold, gender)))
                            cout << "Error adding User. Try again" << endl;

                    } else if (flagP == 2) //Add Teacher
                    {
                        if (!(C.registerTeacher(name, age, gender)))
                            cout << "Error adding User. Try again" << endl;
                    }
                }

                break;
            }
            case 2: //add reservation
            {
                ///////////////////////////////////////////////////////////////
                int flagR;

            	cout << "----------------------------------------------"<< endl;
                cout << "1.Add Free class" << endl;
                cout << "2.Add Lesson" << endl;
                cout << "3.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagR;

                while (flagR != 1 && flagR != 2 && flagR != 3) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagR;
                }
                ///////////////////////////////////////////////////////////////

                if (flagR != 3) //Add Lesson or Free Class
                {

                    cout << "Month: " << endl;
                    cin >> m;
                    cout << "Day: " << endl;
                    cin >> d;
                    cout << "Starting Hour: " << endl;
                    cin >> strH;
                    cin.ignore();
                    cout << "Name of User: " << endl;
                    getline(cin,name);

                    if (flagR == 1) //Add Free Class
                    {
                        //need to choose how to handle price
                        cout << "Duration: " << endl;
                        cin >> duration;
                        //necessary to handle value entered in duration
                        if (!C.makeFree(m, d, strH, duration, name))
                            cout << "Error adding Free class. Try again" << endl;

                    } else if (flagR == 2) //Add Lesson
                    {

                        User &user = C.getUser(name);
                        //need to choose how to handle price

                        if (!C.makeLesson(m, d, strH, name, user.getTeacher()))
                            cout << "Error adding Lesson. Try again" << endl;

                    }
                }

                break;
            }
            case 3: //add court
            {
            	C.createCourt();
            	break;
            }
            case 4: //show person
            {
                ///////////////////////////////////////////////////////////////
                int flagR;

            	cout << "----------------------------------------------"<< endl;
                cout << "1.Show all Teachers and Users" << endl;
                cout << "2.Show User (information/report/invoice/schedule)" << endl;
                cout << "3.Show Teacher (information/schedule)" << endl;
                cout << "4.Go back" << endl;
            	cout << "----------------------------------------------"<< endl;

                cin >> flagR;

                while (flagR != 1 && flagR != 2 && flagR != 3 && flagR != 4) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Error...Try again: " << endl;
                    cin >> flagR;
                }
                ///////////////////////////////////////////////////////////////

                switch (flagR) {
                    case 1://all teachers and Users
                    {
                        C.showTeachers();
                        C.showUsers();
                        break;
                    }
                    case 2: //show user
                    {
                    	int flagR;

                    	cout << "----------------------------------------------"<< endl;
                    	cout << "1.Show Information" << endl;
                    	cout << endl;
                    	cout << "----------------------------------------------"<< endl;
                    	cout << "Consult invoice or report of specific month" << endl;
                     	cout << "----------------------------------------------"<< endl;
                    	cout << "2.Show Report" << endl;
                        cout << "3.Show Invoice" << endl;
                        cout << "----------------------------------------------"<< endl;
                        cout << endl;
                    	cout << "4.Show Schedule" << endl;
                    	cout << "----------------------------------------------"<< endl;

                    	cin >> flagR;

                    	 while (flagR != 1 && flagR != 2 && flagR != 3 && flagR != 4) {
                    		 cin.clear();
                    		 cin.ignore(1000, '\n');
                    		 cout << "Error...Try again: " << endl;
                    		 cin >> flagR;
                    	 }
                        cin.ignore();
                        cout << "Name of User: " << endl;
                        getline(cin, name);


                        if(flagR == 1)
                        	C.showUser(name);

                        if (flagR == 2)
                        {
                        	 cout << "Month: " << endl;
                        	 cin>>m;
                        	C.showReport(name,m);
                        }
                        else if(flagR == 3)
                        {
                        	cout << "Month: " << endl;
                        	cin >> m;
                        	C.showInvoice(name, m);
                        }
                        else if(flagR == 4)
                        {
                        	C.showUserReservations(name);
                        }

                        break;
                    }
                    case 3: //show teacher
                    {
                    	int flagR;

                    	cout << "1.Show Information" << endl;
                    	cout << "2.Show Schedule" << endl;

                    	cin >> flagR;

                    	while (flagR != 1 && flagR != 2) {
                    		cin.clear();
                    		cin.ignore(1000, '\n');
                    		cout << "Error...Try again: " << endl;
                    		cin >> flagR;
                    	}
                    	cin.ignore();
                    	cout << "Name of User: " << endl;
                    	getline(cin, name);

                    	if(flagR ==1)
                    	{
                        C.showTeacher(name);
                    	}
                    	else if(flagR == 2)
                    	{
                    		C.showTeacherLessons(name);
                    	}

                        break;
                    }
                    case 4: //go back
                    {
                        break;
                    }
                }

                break;
            }
            case 5: //show courts
            {
            	C.showCourts();
            }
            case 6: {
                ++C;
                break;
            }
            case 7: {
                cout << "Save and exit? " << endl;
                cout << "1.Yes 0.No" << endl;
                cin >> save;

                if (save == 1) {
                	ofstream outfile;
                	outfile.open((to_string(cardValue) + ".json").c_str());
                    C.storeInfo(outfile, 0);
                }
                return 0;
                break;

            }
        }

    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    unsigned int year, day, month;
    ////////////////////////////////////

    int flag = MainIntro();

    switch (flag) {
        case 1: //new Company
        {
        	bool flag = true;
        	Date D;

        	int cardValue = 1;
        	ifstream infile;
        	infile.open((to_string(cardValue) + ".json").c_str());
        	while(infile.is_open())
        	{
        		cardValue++;
        		infile.close();
        		infile.open((to_string(cardValue) + ".json").c_str());

        	}

        	while(flag)
        	{
            cout << "Please enter date (day month year): " << endl;
            cin >> day;
            cin >> month;
            cin >> year;

            try {
                Date F(day, month, year);
                D = F;

            } catch (BadDate &e) {
                cout << e.what() << endl;
                continue;
            }
             flag = false;

          	}

            Company C(cardValue, D);

            DevelopCompany(C, cardValue);

            break;

        }
        case 2: //load company
        {

            int cv;
            cout << "Card Value of the company? " << endl;
            cin >> cv;

            Company C;

            ifstream infile;
            infile.open((to_string(cv) + ".json").c_str());

            while (!infile.is_open()) {
                cerr << "There is no company with Card Value n: " << cv << "! Please try again." << endl;
                cin.clear();
                cin.ignore(1000, '/n');
                cout << "Card Value of the company?" << endl;
                cin >> cv;
                infile.open((to_string(cv) + ".json").c_str());
            }

            C.readInfo(infile);

            DevelopCompany(C, cv);

            break;
        }
        case 3: //exit
        {
            return 0;
            break;
        }
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



