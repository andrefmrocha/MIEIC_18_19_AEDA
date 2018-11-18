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
    cout << "-------------Tenis Company---------------" << endl;
    cout << "                                         " << endl;
    cout << "Choose option:                           " << endl;
    cout << "                                         " << endl;
    cout << "1.New Company                           " << endl;
    cout << "2.Load Company                            " << endl;
    cout << "3.Exit                                   " << endl;
    cout << "------------------------------------------" << endl;

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
    cout << "-------------Company" << cardValue << "---------------" << endl;
    cout << "                                         " << endl;
    cout << "Choose option:                           " << endl;
    cout << "                                         " << endl;
    cout << "1.Add Person                             " << endl;
    cout << "2.Add Reservation                        " << endl;
    cout << "3.Show Person                            " << endl;
    cout << "6.Increment day                          " << endl;
    cout << "7.Exit                                   " << endl;
    cout << "-----------------------------------------" << endl;

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
    //double price;
    //duration -- unsigned int --problem?
    int duration;
    int save;

    int flagMenu = 0;

    while (true) {

        flagMenu = Menu(cardValue);

        switch (flagMenu) {
            case 1: //Add Person
            {
                /////////////////////////////////////////////////////////////
                int flagP;

                cout << "1.Add User" << endl;
                cout << "2.Add Teacher" << endl;
                cout << "3.Go back" << endl;

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

                    cout << "Name: " << endl;
                    cin>> name;
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

                cout << "1.Add Free class" << endl;
                cout << "2.Add Lesson" << endl;
                cout << "3.Go back" << endl;

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
                    cout << "Name of User: " << endl;
                    cin >> name;

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

                        int i = C.getUser(name);
                        //need to choose how to handle price

                        if (!C.makeLesson(m, d, strH, name, C.getUsers().at(i).getTeacher()))
                            cout << "Error adding Lesson. Try again" << endl;

                    }
                }

                break;
            }
            case 3: //show person
            {
                ///////////////////////////////////////////////////////////////
                int flagR;

                cout << "1.Show all Teachers and Users" << endl;
                cout << "2.Show User" << endl;
                cout << "3.Show Teacher" << endl;
                cout << "4.Go back" << endl;

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
                        //show teachers and user information
                        break;
                    }
                    case 2: //show user
                    {
                    	int flagR;

                    	cout << "1.Show Information" << endl;
                    	cout << "2.Show Report" << endl;
                    	cout << "3.Show Invoice" << endl;

                    	cin >> flagR;

                    	 while (flagR != 1 && flagR != 2 && flagR != 3 && flagR != 4) {
                    		 cin.clear();
                    		 cin.ignore(1000, '\n');
                    		 cout << "Error...Try again: " << endl;
                    		 cin >> flagR;
                    	 }

                        cout << "Name of User: " << endl;
                        getline(cin, name);

                        /*
                        if(flagR == 1)
                        //show user
                        else if (flagR == 2)
                        	//show report
                        else if(flagR == 3)
                        	//show invoice
						*/

						break;
                    }
                    case 3: //show teacher
                    {
                        cout << "Name of Teacher: " << endl;
                        getline(cin, name);

                        //show teacher
                        break;
                    }
                    case 4: //go back
                    {
                        break;
                    }
                }

                break;
            }

            case 4: //show report
            {
                cout << "Name of user: " << endl;
                getline(cin, name);
                cout << "Month of report? (1 to 12)" << endl;
                cin >> m;
                //call function to show report
            }
            case 5: // show invoice
            {
                cout << "Name of user: " << endl;
                getline(cin, name);
                cout << "Month of invoice? (1 to 12)" << endl;
                cin >> m;
                //call function to show invoices
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
                    //save function
                }
                return 0;
                break;

            }
        }

    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    int cardValue = 1;

    unsigned int year, day, month;
    ////////////////////////////////////

    int flag = MainIntro();

    switch (flag) {
        case 1: //new Company
        {
        	bool flag = true;
        	Date D;

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
            cardValue++;

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



