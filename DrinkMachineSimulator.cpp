#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Defining structure
	struct Drink
	{
		string name;
		double cost;
		int qty;
	};

//Function prototype
void greetingsDisplay();
double drinkSale(Drink* , int);
void inventory(Drink*, int);
bool doItAgain(bool );
int getChoice();
double getAmt();

int main() {

	bool goAgain = true; 
	double totalSales =0;

	//Array holding 5 Drink structures
	const int DRINK_SIZE = 5;
	Drink myDrink[DRINK_SIZE] =
	{
		{"Cola      ", 0.75, 20},
		{"Root Beer ", 0.75, 20},
		{"Lemon-Lime", 0.75, 20},
		{"Grape Soda", 0.80, 20},
		{"Cream Soda", 0.80, 20 }
	};

	Drink* ptrD = nullptr;
	ptrD = myDrink;                  //ptr to hold array

	greetingsDisplay();              // Initial greetings

	do
	{	
		
		inventory(ptrD, DRINK_SIZE);                        //Module to keep stock
		totalSales += drinkSale(ptrD, DRINK_SIZE);           //Module to perform sales

		goAgain = doItAgain(goAgain);                       //Module to do another transaction

	} while (goAgain);

	//inventory(ptrD, DRINK_SIZE);           //To display available stock
	cout << "\nThe total sales is $" << totalSales<<endl;
	cout << "Thank you and Enjoy your drink(s)!" << endl;

	return 0;
	system("pause");
}

bool doItAgain(bool oneMore) {
		
		int another;
		cout << "Do you want to buy another drink?\n[0] No \n[1] Yes   ";
		cin >> another;
		if(another != 1)
		{
			oneMore = false;
		}
		return oneMore;
}

void inventory(Drink* drinks, int size) {
	
	cout << "\n\t Drink             Price   Quantity\n"
		<< "\t-----------------------------------\n" << endl;

	for (int i = 0; i < size; i++)
	{
		cout << setprecision(2) << fixed;
		cout << "\t[" << (i + 1) << "] " << drinks[i].name;
		cout << setw(7) << "$ " << drinks[i].cost;
		cout << setw(8) << drinks[i].qty << endl;
	}

}

double drinkSale(Drink* drinkList, int size) {
	
	double amt, sales = 0;
	bool didSell = false;        //To confirm sale
	

	cout << "\nPick a drink number or \nenter [0] to cancel transaction: "<<endl;
	int choice = getChoice();

	//Input Validation
	while (choice < 0 || choice > 5) {
		cout << "Invalid menu choice.\n"
			<<"Enter drink number or [0] to cancel. " << endl;
		choice = getChoice();
	}

	double cost = drinkList[choice -1].cost;    

	//make sale and get payment
	if (choice != 0){
		if (drinkList[choice - 1].qty == 0) {
			cout << "\nSorry! We are sold out on "
				<< drinkList[choice - 1].name << " at the moment.\n" << endl;
		}
		else
		{
			//Proceed to make sale
			double amt = getAmt();
			
			//Calculate and reimburse balance
			if (amt > cost && amt <= 1)
			{
				cout << "\nYou have a balance of $" << setprecision(2)
					<< amt - cost << " cents.\n" << endl;
			}
			else 
			{
				while (amt < cost)
				{
					double bal;
					bal = cost - amt;
					cout << "You still owe $" << bal << " cents.\n" << endl;
					cout << "Please complete payment \n";
					bal = getAmt();
					amt += bal;
					if (amt > cost)
					{
						cout << "\nYou have a balance of $" << setprecision(2)
							<< amt - cost << " cents.\n" << endl;
					}
				}
			}

			didSell = true;
			if (didSell)
			{
				drinkList[choice - 1].qty -= 1;
			}
			
		}
		sales = cost;
	}
	return sales;
}


void greetingsDisplay() {

	cout << "\t              Welcome!\n" << endl;
	cout << "\tGet a fresh drink to cool your taste \n\tand brighten your day." << endl;
	
}

//Module performs input validation
int getChoice()
{
	int choice = 0;

	cout << "Enter choice: "; 
	cin >> setw(1) >> choice;
	//Input Validation
	while (choice < 0) {
		cout << "ERROR: Faulty input! \nTry again..." << endl;
		cout << "Enter choice: ";
		cin >> setw(1) >> choice;
	}

	//Error check
	while (!cin.good())
	{
		//Report problem
		cout << "ERROR: Faulty input! \nTry again..." << endl;

		//Clear stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');       //Clears the max of residue input in cin

		//Get input again.
		cout << "Enter choice: ";
		cin >> setw(1) >> choice;
		//Input Validation
		while (choice < 0 ) {
			cout << "ERROR: Faulty input! \nTry again..." << endl;
			cout << "Enter choice: ";
			cin >> setw(1) >> choice;
		}
	}
	//Clear stream
	cin.clear();	
	cin.ignore(INT_MAX, '\n'); 

	return choice;
}

//Module performs input validation
double getAmt()
{
	double amt = 0;

	cout << "Enter payment: ";
	cin >> setw(1) >> amt;
	//Input Validation
	while (amt < 0 || amt > 1) {
		cout << "ERROR: Faulty input! \nTry again..." << endl;
		cout << "Enter payment: ";
		cin >> setw(1) >> amt;
	}

	//Error check
	while (!cin.good())
	{
		//Report problem
		cout << "ERROR: Faulty input! \nTry again..." << endl;

		//Clear stream
		cin.clear();
		cin.ignore(INT_MAX, '\n');       //Clears the max of residue input in cin

		//Get input again.
		cout << "Enter payment: ";
		cin >> setw(1) >> amt;
		//Input Validation
		while (amt < 0 || amt > 1) {
			cout << "ERROR: Faulty input! \nTry again..." << endl;
			cout << "Enter payment: ";
			cin >> setw(1) >> amt;
		}
	}
	//Clear stream
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	return amt;
}
