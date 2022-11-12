/*
Dakota Kunz 
C++
Due: Nov. 11, 2022
Description: Write a C++ program that reads characters representing binary (base 2) 
numbers from a data file called BinaryIn.dat and translates them to decimal (base 10) 
numbers. The binary and decimal numbers should be output in two columns with 
appropriate headings. 
*/
#include<iostream>
#include <fstream>
#include <iomanip>

using namespace std;
string input = "BinaryIn.dat";
//ifstream infile;

//Precondition: Library iostream and iomanip
//Postcondition: Outputs heading with correct spacing 
void heading();

//Precondition: Library iostream, iomanip, and fstream
//Postcondition: Outputs bi and base, while testing along the way to make sure it is still valid
void Output(int count, int base, bool firstDig, bool badDig, char bi);

int main()
{
	char bi=' ';
	int base = 0; int count = 0;
	bool firstDig = false; bool badDig = false;

	ifstream infile;
	
	heading();
	Output(count, base, firstDig, badDig, bi);
	
	return 0;
}

void heading()
{//outputs heading 
	cout << '\t' << "Binary Number" << setw(42) << "Decimal Equivalent" << endl;
}

void Output(int count, int base, bool firstDig, bool badDig, char bi)
{
	ifstream infile; 
	infile.open(input);
	if (!infile)
		cout << "File can not be found!";

	infile.get(bi);//Primary read

	//runs while file is valid
	while (infile)
	{

		//Runs as long as there is a first character and makes sure file is still valid 
		while (bi != '\n' && infile)
		{
			//Tests to see if the first digit is valid 
			if (!firstDig && (bi == '1' || bi == '0') || firstDig && (bi == '1' || bi == '0'))
			{
				if (!firstDig)
					cout << "\t    ";
				count++;
				firstDig = true;
				cout << bi;
				base *= 2;//General Calculation 

				if (bi == '1')//extra calculation is bi is equal to 1
				{
					base++;
				}
			}
	
			//Safe cause for getting a bad digit
			else if (bi != ' '|| (bi == ' ' && firstDig))
			{
				for (int i = 0; i < (count); i++)//deletes number off screen using backspaces
					cout << '\b';
				cout << setw(15 - (count / 2)) << "Bad Digit On Input\n";
				badDig = true;
				infile.ignore(500, '\n');//Once bi is invalid it will ignore till a new end of line is reachd then breaks out of statement
				break;
			}		
			infile.get(bi);//Gets Next number in sequence
		}

		if (!badDig)
		{
			for (int i = 0; i < (40 - count); i++)
				cout << " ";
			cout << base << endl;
		}

		//resets value after reaching a new line to restart calculations
		firstDig = false;
		badDig = false;
		count = 0;
		base = 0;
		infile.get(bi);//Gets every first digit besides the very first one
	}
}