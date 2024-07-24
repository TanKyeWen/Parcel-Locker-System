#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <typeinfo>

#define OWNER_DETAIL "own_detail.txt"
#define LOCKER_DETAIL "locker.txt"
#define PARCEL_DETAIL "parcel_unit_num.txt"

using namespace std;

int total_line(string text_file);											// determine total line in the text file
void read_file(string f[], int size, string text_file);						// retrieved data from text file
void Continue();															// allow user pressing enter to continue
void parcel_chkin(int num,string f[]);										// parcel check-in function
void append_detail(string f[], int size, string text_file);					// adding text file from the most bottom
void update_detail(string f[], int size, string text_file);					// updating data in text file
void parcel_chkout(string f[], int num);									// parcel check-out function
string get_pin();															// generate PIN
void registration(string f[],int num);										// new owner registration function


int main(void)
{


    bool loop_main = true;
    while(loop_main)
    {
			int num = total_line(OWNER_DETAIL);
		    string f[num];
		    read_file(f, num, OWNER_DETAIL);
    	system("cls");
        string input_main;
        cout  << "\t=================================================================\n";
        cout  << "\t  Welcome to Boulevard Service Apartment community Parcel system\n";
        cout  << "\t=================================================================\n\n";
        cout  << "\t< 1 > Parcel check-in\n";
        cout  << "\t< 2 > Parcel check-out\n";
        cout  << "\t< 3 > Resident registration\n";
        cout  << "\t< 88 > Exit system\n\n";
        cout << "\tPlease enter your option : ";
        cin >> input_main;

        if (input_main == "1")
            parcel_chkin(num, f);

        else if(input_main == "2")
            parcel_chkout(f, num);

        else if (input_main == "3")
            registration(f,num);

        else if(input_main == "88")   										// exit system
        {
            cout  << "\n\n\tExiting system.";
            loop_main = false;
        }

        else																// input validation checking
        {
            cout << "\n\n\tInvalid option entered.\n";
            Continue();
        }
    }
	return 0;
}

int total_line(string text_file)
{
	ifstream in_file(text_file);
	if(!in_file)															// file validation
		cout << "Error opening file\n";
	else
	{
		string data;
		int index = 1;
    	while(getline(in_file, data))
      		index += data.length();											// retrieving total line in text file
		in_file.close();
    	return index;														// return total line in text file
	}
}

void read_file(string f[], int size, string text_file)
{
    ifstream in_file(text_file);
    if(!in_file)															// file validation
        cout << "Error opening file\n";
    else
    {
        string data[size];
        int i = 0;
        in_file >> data[i];
        while(in_file)														// retrieved data in text file
        {
            if (text_file == LOCKER_DETAIL){
              for (char x : data[i]){
                f[i] = x;
              }
            }
            f[i]=data[i];
            i++;
            in_file >> data[i];
        }
        in_file.close();
    }
}

void Continue()
{
	cout << "\n\n\tPress Enter to continue...";
	char a;
	fflush(stdin);
	a = getchar();
}

void parcel_chkin(int num, string f[])
{
	bool loop_parcel_chkin = true;
	while (loop_parcel_chkin)
	{
	    string uni_num, Parcel_locker;
	    int step = 0;
	    while(step == 0)
		{
			system("cls");
			cout  << "\t==============================================================\n";
	        cout  << "\t                     Parcel check-in.\n";
	        cout  << "\t==============================================================\n\n";
	        cout  << "\tEnter 88 to exit.\n";
			cout  << "\tEnter delivery unit number : ";
	        cin >> uni_num;

	        if (uni_num == "88")											// exit checking
			{
	        	loop_parcel_chkin = false;
	        	break;
			}
	        else
			{
		        for(int i = 0; i <= num; i++)								// apartment unit number checking
		        {
		        	if(uni_num == f[i])
		        	{
		        		step = 1;
		        		i = num + 1;
		        	}
					else
						step = 100;
		        }

				if(step == 100)
				{
					cout  << "\n\tInvalid apartment unit number entered";
			    	Continue();
			    	step = 0;
				}
			}
		}

		while(step == 1)
		{
	    	string lock_file[total_line(LOCKER_DETAIL)];
			read_file(lock_file, total_line(LOCKER_DETAIL), LOCKER_DETAIL);	// retrieved data in locker.txt

			int full = 1;
	    	for (int i = 0; i <= 39; i++)
			{
		        if (lock_file[i] == "1")									// locker avaibility checking
				{
		        	cout  << "\n\n\t==============================================================\n";
		    		cout  << "\t             Please place item in locker " << i+1 << endl;
		    		cout  << "\t==============================================================\n";
		    		cout  << "\n\n\tA PIN has been sent to the owner via sms\n";
		    		Continue();

		        	lock_file[i] = "0";
		        	Parcel_locker = to_string(i+1);
		        	append_detail(lock_file, total_line(LOCKER_DETAIL), LOCKER_DETAIL);

		        	full = 0;
		    		i = 40;
		        	step = 2;
	        	}
	    	}
		}

	    while(step == 2)
		{
	    	string auth[3] = {uni_num, Parcel_locker, get_pin()};			// updating data in parcel_unit_num.txt
	    	int size = sizeof(auth)/sizeof(auth[0]);
	    	append_detail(auth, size, PARCEL_DETAIL);
	    	step = 3;
	    	loop_parcel_chkin = false;										// exit parcel check-in function
	    }
	}
}

void append_detail(string f[], int size, string text_file)
{
	ofstream out_file;
	if(text_file == LOCKER_DETAIL)
    	out_file.open(text_file, ios::out);
	else
		out_file.open(text_file, ios::app);
	if(!out_file)
    	cout << "Error opening file\n";
	else
	{
		for (int i = 0; i <= size-1; i++)
    		out_file << f[i] << endl;
    }
    out_file.close();
}

void update_detail(string f[], int size, string text_file){
	ofstream out_file(text_file, ios::out);
	if(!out_file)
      cout << "Error opening file\n";
  else{
    for (int i = 0; i <= size - 1; i++){
			if(f[i] == ""){
				break;
			}
			out_file << f[i] << endl;

		}
	}
	out_file.close();
}

void parcel_chkout(string f[], int num)
{
	bool loop_chkout = true;
	while (loop_chkout)
	{
		system("cls");
        cout  << "\t=================================================================\n";
        cout  << "\t                     Parcel check out\n";
		cout  << "\t=================================================================\n";
		cout  << "\n\tEnter 88 to exit.\n";
		cout  << "\tEnter apartment unit number : ";
		string unit_num;													// apartment unit number retrieving
		cin >> unit_num;
		int chkout_step = 0;

		if (unit_num == "88")												// exit checking
			loop_chkout = false;
		else
		{
			int chkout_step = 1, locate_user;
	    	for (int i = 0; i <= num; i++)
			{
	   			if(f[i] == unit_num)										// finding data location
	   			{
	   				chkout_step = 2;
	   				locate_user = i;
	   				break;
	   			}
	   			chkout_step = 101;
	   		}

	   		if (chkout_step == 101)											// apartment unit number validation
	   		{
	   			cout << "\n\tApartment unit number entered doesn't exist\n";
	   			Continue();
			}

			if (chkout_step == 2)
			{
				cout << "\n\tEnter login password : ";
				string password;
				cin >> password;											// login password retrieving

				if(password == f[locate_user + 3])							// loging password validating
					chkout_step++;
				else
				{
					int times = 0;
					for (int i = 3; i >=1; i--)
					{
						cout << "\n\tIncorrect password entered.\n\t"
							 << i << " time(s) attempting remain.\n";
						cout << "\tEnter login password : ";
						cin >> password;

						if(password == f[locate_user + 3])
						{
							chkout_step++;
							break;
						}

						times ++;
					}

					if (times == 3)
					{
						cout << "\n\tReached maximum time of attempting.";
						Continue();
					}
				}
			}

			while (chkout_step == 3)
			{
				system("cls");
       			cout  << "\t=================================================================\n";
        		cout  << "\t                      Parcel check out\n";
				cout  << "\t=================================================================\n";
				cout  << "\n\n\tApartment number : " << unit_num;
				cout  << "\n\tOwner name       : " << f[locate_user + 1];
				cout  << "\n\tContact number   : " << f[locate_user + 2];

				int parcel_num = total_line(PARCEL_DETAIL);					// data retrieving
				string p_detail[parcel_num], lockarr[total_line(LOCKER_DETAIL)];
				read_file(p_detail, parcel_num, PARCEL_DETAIL);
				read_file(lockarr, 40, LOCKER_DETAIL);

				int array_n = 0, exit = 0;
				string locker_no[40], pin[40];

				for(int i = 0; i <=parcel_num; i++)							// check-out parcel determination
				{
					if (p_detail[i] == "")
						break;

					else if (p_detail[i] == unit_num)
					{
						exit = 1;
						locker_no[array_n] = p_detail[i + 1];
						pin[array_n] = p_detail[i + 2];
						array_n += 1;
					}
				}

				if (exit == 0)												// check-out parcel validation
				{
					cout  << "\n\n\tNo parcel is in any locker";
					Continue();
					chkout_step = 0;
				}

				while(exit == 1)
				{
					if (exit == 1 && array_n == 1)
					{
						cout  << "\n\n\tYour parcel is in locker No :\n\t"
						      << locker_no[0];
						exit = 2;
					}

					if (exit == 1 && array_n > 1)
					{
						cout  << "\n\n\tYour parcel is in locker No :\n\t";
						for(int j = 0; j <= array_n ; j++)
						{
							cout << locker_no[j] << " ";
						}
						exit = 2;
					}
				}

				if (exit == 2)												// exit checking
				{
					cout << "\n\n\tEnter 88 to exit.";
					cout << "\n\tEnter No. of locker to unlock : ";

					string opt;
					cin >> opt;												// open locker based on locker number

					if(opt == "88")
					{
						chkout_step = 0;
					}

					else
					{
						for(int n = 0; n <= array_n - 1; n++)				// no. locker validation
						{
							if (opt == locker_no[n])
							{
								exit = 3;
								array_n = n;
								break;
							}
							else
								exit = 101;
						}
					}

					if(exit == 101)
					{
						cout  << "\n\tInvalid locker No. entered.";
						Continue();
					}


					if (exit == 3)
					{
						string pin_num;
						system("cls");
	       				cout  << "\t=================================================================\n";
	        			cout  << "\t                      Parcel check out\n";
						cout  << "\t=================================================================\n";
						cout  << "\n\tLocker No." << opt;
						cout  << "\n\n\tEnter one-time PIN number : ";
						cin  >> pin_num;

						int pin_loop = 0, PIN_exit = 0;

						if (pin_num == pin[array_n])						// PIN number validation
							pin_loop = 1;

						if(pin_loop == 0)
						{
							for (int i = 3; i >=1; i--)
							{
								cout << "\n\tIncorrect one-time PIN number entered.\n\t"
									 << i << " time(s) attempting remain.\n";
								cout << "\tEnter one-time PIN number : ";
								cin >> pin_num;

								if (pin_num == pin[array_n])
								{
									pin_loop = 1;
									PIN_exit++;
									break;
								}
							}
							if (PIN_exit == 0)
							{
								cout << "\n\tReached maximum time of attempting.";
								Continue();
							}
						}

						if(pin_loop == 1)
						{
							int skip = 0;									// data updating
							for(int i = 0; i <=parcel_num; i++)
							{
								if (p_detail[i] == "")
									break;

								if (p_detail[i] == opt)
									skip = 1;

								if (skip == 1)
								{
									if (p_detail[i] == "")
										break;

									else
										p_detail[i-1] =p_detail[i+2];
								}
							}
							update_detail(p_detail, parcel_num, PARCEL_DETAIL);

							read_file(lockarr, 40, LOCKER_DETAIL);
							lockarr[stoi(locker_no[array_n])-1] = "1";
							update_detail(lockarr, 40, LOCKER_DETAIL);

							cout << "\n\tPlease collect your parcel in the locker.";
							cout << "\n\tThank you for choosing Boulevard Service Apartment community \n\tParcel system.";
							cout << "\n\n\tHave a Great Day! :D";
							Continue();
						}
					}
				}
			}
		}
	}
}

string get_pin()
{
    string pin = "";

	srand(time(NULL));
	for (int i = 0; i <= 2; i++)
		pin += to_string(rand()% 99 + 10);

    return pin;
}

void registration(string f[],int num)
{
	bool loop_registration = true;

	while(loop_registration)
	{
		system("cls");
		cout  << "\n\n\t=================================================================\n";
		cout  << "\tBoulevard Service Apartment community Parcel system registration\n";
		cout  << "\t=================================================================\n\n\n";
		cout  << "\tEnter 88 to exit.\n";
		cout  << "\tEnter apartment unit number : ";
		string new_own[4] = {"","","",""};
		int reg_step = 0;
		cin >> new_own[0];

		if (new_own[0] == "88")												// exit checking
			loop_registration = false;
		else
		{
			for (int i = 0; i <= num ; i++)
			{
				if((i+1)%4==1)												// repeated apartment number checking
				{
					if(new_own[0] == f[i])
					{
						reg_step = 101;
						break;
					}
				}
			}

			if (reg_step == 101)
			{
				cout << "\n\n\tApartment unit already exist.\n\tPress Enter to continue...";
				char a;
				fflush(stdin);
				a = getchar();
			}

			else if (reg_step == 0)
			{
	    		cout << "\n\tExample : TanKyeWen\n";
				cout << "\tEnter Owner name : ";
				cin >> new_own[1];

	    		cout << "\n\tExample : 012-3456789\n";
				cout << "\tEnter contact number : ";
				cin >> new_own[2];

	    		cout << "\n\tInclude both numbers and alphabet.\n";
				cout << "\tEnter login password : ";
				cin >> new_own[3];

	    		append_detail(new_own, 4, OWNER_DETAIL);
				cout << "\n\n\t=================================================================\n";
				cout << "\t                New account registed successfully\n";
				cout << "\t=================================================================\n";
				Continue();
				loop_registration = false;									// exiting regitration
			}
		}
	}
}
