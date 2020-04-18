#include "hashtable.h"
#include <iostream>
using namespace std;
using namespace cop4530;

void replace(string word, HashTable<string> Ti,vector<string>&MyList);
void menu()
{
	cout << "\n\n";
	cout << "l - Load Dictionary From File" << endl;
	cout << "a - Add Word" << endl;
	cout << "r - Remove Word" << endl;
	cout << "c - Clear HashTable" << endl;
	cout << "f - Find Word" << endl;
	cout << "d - Dump HashTable" << endl;
	cout << "s - HashTable Size" << endl;
	cout << "w - Write to File" << endl;
	cout << "x - Exit program" << endl;
	cout << "\nEnter choice : ";
}
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		size_t cap;
		cout << "Enter preferred Hash Table Capacity: ";
		cin >> cap;
		cout << '\n' << cap;
		if (cap < 0)
		{
			cout << "** input too Small " << '\n' << "set to default capacity " << "11" << endl;
			cap = 11;
		}
		HashTable<string>Foo(cap);
		char choice;
		do 
		{
			menu();
			cin >> choice;
			cout << endl;
			switch (choice)
			{
			case 'l': 
			{
				string fname;
				cout << "Enter dictionary name to load from: ";
				cin >> fname;
				cout << endl;
				const char * filez = (fname.c_str());
				if (Foo.load(filez) == true)
					cout << "Dictionary loaded successfully." << endl;
				else
					cout << "Cannot open file " << fname;

				break;
			}
			case 'a':
			{
				string word;
				cout << "Enter Word: ";
					cin >> word; 
					std::transform(word.begin(), word.end(), word.begin(), ::tolower);
					if (Foo.contains(word))
						cout << '\n' << "****: Word already exists, could not add";
					else
					{
						Foo.insert(word);
						cout << "Word " << word << " added";
					}
					break;
			}
			case 'r':
			{
				string toerase;
				cout << "Enter Word: "; 
				cin >> toerase;
				if (!Foo.contains(toerase))
					cout << '\n' << "Word does not exist, could not delete";
				else
				{
					Foo.remove(toerase);
					cout << "Word " << toerase << " removed";
				}
				break;
			}
			case 'c':
			{
				Foo.clear();
				break;
			}
			case 'f':
			{
				string findword;
				cout << "Enter word:  ";
				cin >> findword;
				cout << endl;
				if (Foo.contains(findword))
					cout << "Word " << findword << " " << "found";
				else
					cout << "Word " << findword << " " << "not found";
				break;
			}
			case 'd': 
			{
				Foo.dump();
			}
			case 's':
			{
				cout << "Size of hashtable: ";
				cout << Foo.mySize(); //calls getter function
				break;
			}
			case 'w':
			{
				string w;
				cout << "Enter dictionary file name to write to: ";
				cin >> w;
				const char* writefile = (w.c_str());
				if (Foo.write_to_file(writefile) == true)
					cout << "Written Successfully ";
				else
					cout << "Written unsuccessfully";
				break;
				
			}
			}

		} while (choice != 'x');




	}

	HashTable<string>Ti;//You should load the words in the dictionary into a hash table
	//Ti.load(argv[1]);// You should load the words in the dictionary into a hash table
	Ti.load("words.txt");
	//ifstream input(argv[2]); //input file
	ifstream input("test1.txt");
	//ofstream output_file(argv[3]); //output file
	ofstream output_file("Newfile.txt");
	
	vector<string>Lines;
	string str;
	while (getline(input, str))
	{
		Lines.push_back(str); //gets an entire line from the File
	}

	for (size_t i = 0; i < Lines.size(); i++)
	{
		output_file << endl;
		//getline(cin, Lines[i]);
		istringstream iss(Lines[i]);
		string word;
		while (iss >> word)
		{
			string temp = word; //check for punctuation
			temp.erase(std::remove_if(temp.begin(), temp.end(), ispunct), temp.end()); //check for punctuation
			std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			if (Ti.contains(temp)) //checks to see if the word is in the table
				output_file << word << " ";  //if so output it to file //account for punct
			else
			{
				cout << Lines[i] << endl; //print out the whole line, 
				string change;
				vector<string>MyList;
				replace(word, Ti, MyList);
				vector<int>options;
				//print out the list and ask for option!
				cout << "=================" << endl;
				for (int i = 0; i < MyList.size(); i++)
				{
					options.push_back(i);
					cout << i << "): " << MyList[i] << endl;
				}
				cout << "n (no change): " << endl;
				cout << "=================" << endl;
				cout << "Your choice: ";
				cin >> change;
				cout << change << endl;
				if (change == "n")
					output_file << word << " ";
				else 
				{
					int x = stoi(change); //string to int
					//check to see if change is valid 
					vector<int>::iterator it = find(options.begin(), options.end(), x);

						if (it == options.end()) //if choice is not an option
							std::cout << "invalid choice " << std::endl;
						else
						{
							int index = std::distance(options.begin(), it); //gets the index
							//if choice is valid
							word = MyList[index];
							output_file << word << " "; 
							cout << endl;
						}
				}

				
			}
		}
	}
	output_file.close();
	input.close();
}
void replace(string word, HashTable<string> Ti, vector<string>&MyList)
{
	
	string temp = word;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower); //lowercase the word
	//check to see if the word is in the hashtable in all base cases
	int count = 0;
	int size = static_cast<int>(temp.length());
	for (auto i = 0; i < size; i++)
	{
		string temporary = temp;
		for (char c = 'a'; c <= 'z'; ++c)
		{
			temporary[i] = c;
			if (Ti.contains(temporary) && count < 10) //if the hashtable contains the word; pushback!
			{
				MyList.push_back(temporary); //gets ten words then breaks;
				count++;
			}
		}
	}
}