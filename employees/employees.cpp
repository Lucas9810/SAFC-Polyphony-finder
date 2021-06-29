#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

ifstream file("file.csv"); // load file to "file"

int getnumsemi() // get the number of semicolons before the polyphony number
{
	string garbage;
	getline(file, garbage);

	int numsemi = 0; //the number used to keep track

	int position = garbage.find("Polyphony"); //look for polyphony's position in the first line
	if (position != -1) //if it finds polyphony in the first line
	{
		//cout << "found polyphony in the first line" << endl;
		for (int semicolonposition = 0; semicolonposition < garbage.find("Polyphony"); semicolonposition++) //loop until 
		{
			if (garbage.find(";", semicolonposition) != -1) //if it finds a semicolon in the first line
			{
				//cout << "found semicolon in the first line" << endl;
				while (semicolonposition < garbage.find("Polyphony")) //:shrug:
				{
					semicolonposition = garbage.find(";", semicolonposition + 2); // advance semicolon position
					numsemi++;
				}
			}
			else //if it finds no semicolon, exit with error
			{
				cout << "File may be broken or improperly written; there were no semicolon dividers found in the first line of the file. Make sure that SAFC is set to export using semicolon dividers." << endl;
				exit(68);
			}
		}

	}
	else //if no polyphony is found in the first line, error
	{
		cout << "Unable to find polyphony information in the input file. Missing information in the first line." << endl;
		exit(69);
	}

	numsemi--; // remove one from numsemi because it counts one too high :flushed:
	//cout << numsemi << " is the returned value, and this worked properly if it is 3." << endl;
	return numsemi;
}

int main()
{
	if (!file)  // if file is missing, exit
	{
		cout << "No file named file.csv was found." << endl << "Please run the program with a SAFC full information export in the same directory as the program, renamed to file.csv.";
		exit(4);
	}

	int semicolonposition = 0; //current position of the semicolon loop
	int semicolonnumber = getnumsemi(); //number that the semicolon is (3 usually)
	int currentsemicolon = 0; //semicolon that the loop is currently on
	double maxpoly = 0;
	double counter = 0;
	//cout << semicolonnumber << " is semicolonnumber, and it should also be 3" << endl;

	string used;
	do
	{
		getline(file, used);
		if (used.empty()) // if there is an empty line, end the process early
		{
			cout << "The Maximum polyphony in the scanned file was " << maxpoly << endl;
			return 0;
		}
		//cout << "string used is currently " << used << endl;

		while (currentsemicolon < semicolonnumber)
		{
			if (used.find(";", semicolonposition) != -1) //if it finds a semicolon in the looped lines
			{
				semicolonposition = used.find(";", semicolonposition + 1);
				//cout << semicolonposition + 1 << endl;
				currentsemicolon++;
			}
			else //if it finds no semicolon, exit with error
			{
				cout << "File may be broken or improperly written; there were no semicolon dividers found after the first line." << endl;
				exit(68);
			}

		}

		double currentpoly = stod(used.substr(semicolonposition + 1, used.find(";", semicolonposition + 1) - semicolonposition - 1)); // convert substring after semicolon before polyphony number and before semicolon after polyphony number

			if (currentpoly > maxpoly)
				maxpoly = currentpoly;

		counter++;

		semicolonposition = 0; //reset the values for the next thing in the loop
		currentsemicolon = 0;
	} while (file); // do all that while there is still lines left

	cout << "The Maximum polyphony in the scanned file was " << maxpoly << endl;

	return 0;
}