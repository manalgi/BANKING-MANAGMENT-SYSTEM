#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

//funtion for adding new account: non of the information here bein validate if it like address or birthday date. 
void new_acc(int Cnum) {
	string name, address, Bdate;
	int phone;
	float deposit;
	
	//ignoring the last cin from the function check();
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//

	cout << "Full Name: ";
	getline(cin, name);
	cout << "Address (street, house number, city) : ";
	getline(cin, address);
	cout << "Birthday (dd/mm/yyyy): ";
	getline(cin, Bdate);
	cout << "Phone Number: ";
	cin >> phone;
	cout << "Deposit amount: ";
	cin >> deposit;

	//open or creating file as our DATABASE for this program 
	ofstream myfile("DB.txt",ios::app);
	if (myfile.is_open()) {
		
		myfile << Cnum << endl << name << endl << address << endl << Bdate << endl << phone << endl << deposit << endl;
		cout << "success"<<endl<<endl;
		myfile.close();
	}
	else
		cout << "File Error" << endl;
	
	
}

//in order to keep the customer number (Cnum) in order and icreasing , by defualt it start as =11111 or it checks what was the last account that
//has been created and increase by 1 and then call new_acc to creat the new acc() member 
void check() {
	int Cnum = 11111;
	string line;
	ofstream file("DB.txt");
	file.close();
	
	ifstream myfile("DB.txt");
	if (myfile.is_open())
	{
		int i = 0 ;
		while (getline(myfile, line))
		{
			//the Cnum always saved as first and his idex divided by 6, so we check what was the last Cnum that has been created here and save it;
			if (i == 0 || (i%6==0)) {
				Cnum = stoi(line);
			}
			i++;

		}
		myfile.close();
		//cout << Cnum << endl;
		++Cnum;
		//cout << Cnum<<endl;
		new_acc(Cnum);
	}
	else {
		cout << "Error! Unable to Open File DB.txt" << endl;
	}
}
//reading the dile DB.txt and output it on screen and counting number of customers
void view_list() {
	int i = 1;
	string line;
	ifstream myfile("DB.txt");
	if (myfile.is_open())
	{
		cout << "	CUSTOMER LIST " << endl;
		while (getline(myfile, line))
		{
			cout << i << ")" << endl;
			cout <<"Account number: " +line << '\n';
			getline(myfile, line);
			cout << "Name holder: " + line << '\n';
			getline(myfile, line);
			cout << "Address: " + line << '\n';
			getline(myfile, line);
			cout << "Date of birth: " + line << '\n';
			getline(myfile, line);
			cout << "Phone number: " + line << '\n';
			getline(myfile, line);
			cout << "Account Status: " + line << '\n';
			i++;
		}
		myfile.close();
		cout << endl << "total of customers " << i - 1 << endl;
		cout << "	END OF LIST" << endl << endl;
		
	}
	else {
		cout << "Error! Unable to Open File DB.txt" << endl;
	}

}
//2 option for updating customer profile. 1)phone number or 2) address. 
void edit(){
	int newphone = 0,Cnum;
	string newaddress = "unknown", choise;
	cout << "what is Customer ID number: ";
	cin >> Cnum;
	cout << "What would you like to edit? phone / address ?";
	getline(cin, choise);
	if (choise == "phone") {
		cout << "what is your new phone number?";
		cin >> newphone;
	}
	else if (choise == "address") {
		cout << "what is your new address?";
		getline(cin, newaddress);
	}
	//converting the customer number to string
	string line, foo;
	foo = to_string(Cnum);
	fstream myfile("DB.txt");
	ofstream temp_file("DBtemp.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//finding the customer number and changing accordingly
			if (line == foo) {
				//first line always Customer number
				temp_file << line << endl;
				for (int i = 0; i < 4; i++) {
					getline(myfile, line);
					//check if the user asked for phone update and , and it is always the 4th line (3+1)
					if (choise == "phone" && i == 3)
					{
						temp_file << newphone << endl;
					}
					//or address which is always the second line (1+1)
					else if (choise == "address" && i == 1) {
						myfile << newaddress << endl;
					}
					else {//the rest get copied as it is
						temp_file << line << endl;
					}

				}

			}
			else
				temp_file << line << endl;//copt rest of the customers
		}
		
		myfile.close();
		temp_file.close();
		//removing the old file
		remove("DB.txt");
		//the temp file become the new updated to now we change the name back
		rename("DBtemp.txt", "DB.txt");
		cout << "succss" << endl << endl;
	
	}
	else {
		cout << "Error! Unable to Open File DB.txt" << endl;
	}

}
//transaction by adding money to the account , or removing money or by taking it or by sending to anther account(assuming the account exist);
void transact() {
	int num,Cnum;
	float amount;
	string Cto="0";
	cout << "what is Customer ID number: ";
	cin >> Cnum;
	cout << " would you like?"<<endl<<"1) deposit money "<<endl<<"2) send money	"<<endl<<"3) withdraw  money"<<endl<<"your choice: ";
	cin >> num;
	if (num == 1) {
		cout << "enter the amount of deposit: ";
		cin >> amount;
	}
	else if (num == 3) {
		cout << "enter the amount that you would like to wthdraw: ";
		cin >> amount;
	}
	else if (num == 2) {
		cout << "what is the ID account of the reciver: ";
		cin >> Cto;
		cout << "amount of money: ";
		cin >> amount;
		
	}
	string line, foo;
	foo = to_string(Cnum);
	float oldamount; 
	fstream myfile("DB.txt");
	ofstream temp_file("DBtemp.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			//finding the  owner in the file 
			if (line == foo) {
				temp_file << line << endl;
				
				for (int i = 0; i < 5; i++) {
					getline(myfile, line);
					
					if (num == 1 && i == 4)
					{
						//converting to float and then adding the new amount and coping it to the new file
						oldamount = stof(line);
						oldamount += amount;
						temp_file << oldamount << endl;
					}
					else if ((num == 3 ||num == 2) && i == 4)
					{
						//converting to float and then reducing the new amount and coping it to the new file
						oldamount = stof(line);
						oldamount = oldamount-amount;
						temp_file << oldamount << endl;
					}
					else {
						temp_file << line << endl;
					}

				}

			}
			//finding the reciever in the file.
			else if (line == Cto) {
				temp_file << line << endl;
				for (int i = 0; i < 5; i++) {
					getline(myfile, line);
					if (num == 2 && i == 4)
					{
						oldamount = stof(line);
						cout << oldamount<<"+";
						oldamount += amount;
						cout << amount << endl;
						temp_file << oldamount << endl;
					}
					else {
						temp_file << line << endl;
					}

				}

			}
			//coping the rest of the customers
			else
				temp_file << line << endl;
		}
		myfile.close();
		temp_file.close();
		//removing old file
		remove("DB.txt");
		//the temp file become the main and updated one, changing back the name
		rename("DBtemp.txt", "DB.txt");
		cout << "succss" << endl<<endl;

	}
	else {
		cout << "Error! Unable to Open File DB.txt" << endl;
	}

}
//deleting customer account , by removing all information about him form the file
void erase() {
	string line, foo;
	int Cnum;
	cout << "what is Customer ID number: ";
	cin >> Cnum;
	foo = to_string(Cnum);
	fstream myfile("DB.txt");
	ofstream temp_file("DBtemp.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line == foo) {
				//skiping all lines after finding the customer ID number (foo is the Cnum as a string)
				for (int i = 0; i < 5; i++) {
					getline(myfile, line);
				}

			}
			else//coping the rest of the customers
				temp_file << line << endl;
		}
		myfile.close();
		temp_file.close();
		//removing old file
		remove("DB.txt");
		//renaming the new file and the updated one
		rename("DBtemp.txt", "DB.txt");
		cout << "Account deleted" << endl <<  endl;

	}
	else {
		cout << "Error! Unable to Open File DB.txt" << endl;
	}
}


int main() {
	cout << "CUSTOMER ACCOUNT BANKING MANAGMENT SYSTEM" << endl << "	WELCOME TO THE MAIN MENU		" << endl;
	int choice;

	
	while (1) {
		cout <<endl << "1)Create new account" << endl << "2)Update account information" << endl << "3)Transaction" << endl << "4)View customers list" << endl << "5)Delete account" << endl << "6)EXIT";
		cout << endl << "what is your choice? ";
		//cin >> choice;
		if (!(cin >> choice) && (choice < 1 || choice > 6)) {
			cout << "Invalid selection- choose only between 1-6" << endl;
			// reset error flags
			cin.clear();
			// throw away garbage input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		else {
			switch (choice)
			{
			case 1:check();
				break;
			case 2:edit();
				break;
			case 3:transact();
				break;
			case 4:view_list();
				break;
			case 5:erase();
				break;
			case 6:return 0;
				break;
			
			}
		}
			
		
	}

	system("pause");
	return 0;
}
