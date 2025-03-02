#include<iostream>
#include<vector>
#include<string>
using namespace std;

//American Standard Code for Information Interchange
void A2Z()
{
	for (int i = 65; i < 91; i++)
	{
		cout << (char)i << " ";
	}
	cout << endl << endl;
}

void a2z()
{
	for (int i = 97; i < 123; i++)
	{
		cout << (char)i << " ";
	}
	cout << endl << endl;
}

string restoreOriginalCase(const string& original, const string& processed)
{
	string result = processed;
	for (size_t i = 0; i < original.length(); i++)
	{
		if (islower(original[i]))
		{
			result[i] = tolower(result[i]);
		}
	}
	return result;
}

string CaesarCipher(string word, int shift, bool endec) 
{
	for (int i = 0; i < word.length(); i++)
	{
		if (isupper(word[i]))
		{
			if (endec)
				word[i] = 'A' + (word[i] - 'A' + shift) % 26;
			else
				word[i] = 'A' + (word[i] - 'A' - shift + 26) % 26;
		}
		else if (islower(word[i]))
		{
			if (endec)
				word[i] = 'a' + (word[i] - 'a' + shift) % 26;
			else
				word[i] = 'a' + (word[i] - 'a' - shift + 26) % 26;
		}
	}
	
	return word;
}


string Vigenere(string word, string key, bool endec)
{
	string originalWord = word;

	vector<int> spacePositions;
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] == ' ') spacePositions.push_back(i);
	}

	word.erase(remove(word.begin(), word.end(), ' '), word.end());

	for (char& c : word) c = toupper(c);
	for (char& c : key) c = toupper(c);

	string newKey = key;
	string cipherText;

	while (newKey.length() < word.length())
	{
		newKey += key;
	}
	if (endec)
	{
		for (int i = 0; i < word.length(); i++)
		{
			cipherText += ((word[i] + newKey[i]) % 26) + 65;
		}
	}
	else if (!endec)
	{
		for (int i = 0; i < word.length(); i++)
		{
			cipherText += ((word[i] - newKey[i] + 26) % 26) + 65;
		}
	}


	for (int pos : spacePositions)
	{
		cipherText.insert(pos, " ");
	}

	string text = restoreOriginalCase(originalWord, cipherText);

	return text;
}

string VigenereEnDec(bool endec)
{
	string type;
	string word;
	string key;
	string cipherText;
	bool validKey;

	if (endec)
		type = "plain";
	else
		type = "cipher";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter a " << type << " text : ";
	getline(cin, word);

	validKey = false;

	while (!validKey)
	{
		cout << "Enter the key: ";
		cin >> key;
		validKey = true;
		for (char& c : key) {
			if (!isalpha(c)) 
			{
				cout << "Invalid key. Please enter alphabetic characters only." << endl;
				validKey = false;
				break;
			}
			}
			if (!validKey) {
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		cout << endl;
		cipherText = Vigenere(word, key, endec);
		
		return cipherText;
}

string CaesarEnDec(bool endec)
{
	string type;
	string word;
	string cipherText;
	int shift;

	if (endec)
		type = "plain";
	else
		type = "cipher";

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter a " << type << " text : ";
	getline(cin, word);

	cout << "Enter the shifting position: ";

	while (!(cin >> shift) || shift < 0)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a positive integer: ";
	}
	cout << endl;

	cipherText = CaesarCipher(word, shift, endec);
	
	return cipherText;
}



void MAIN()
{
	string x = "Y";
	string plaintext;
	string ciphertext;
	int option;
	int type;
	int shift;


	do {
		cout << "Welcome to the encryption and decryption station" << endl;
		cout << "Press 1: caesar cipher 2: vigenere cipher 3: Exit" << endl;
		cin >> type;
		cout << endl;

		while (type < 1 || type > 3)
		{
			cout << "Please enter within 1 and 3: ";
			cin >> type;
			cout << endl;
		}

		switch (type)
		{
			case 1:
				cout << "Enter 1: Encryption 2: Decryption 3: Exit" << endl;
				cin >> option;

				while (option < 1 || option > 3)
				{
					cout << "Please enter within 1 and 3: ";
					cin >> option;
					cout << endl;
				}

				switch (option)
				{
				case 1:
					
					ciphertext = CaesarEnDec(true);
					cout << "Cipher text: " << ciphertext << endl << endl;
					cout << "Press Y/y to continue or any key to exit: ";
					cin >> x;
					cout << endl;

					break;
				case 2:
					
					plaintext = CaesarEnDec(false);
					cout << "Plain text: " << plaintext << endl << endl;
					cout << "Press Y/y to continue or any key to exit: ";
					cin >> x;
					cout << endl;

					break;
				case 3:
					x = "n";
					break;
				}

				break;

			case 2:
				cout << "Enter 1: Encryption 2: Decryption 3: Exit" << endl;
				cin >> option;

				while (option < 1 || option > 3)
				{
					cout << "Please enter within 1 and 3: ";
					cin >> option;
					cout << endl;
				}

				switch (option)
				{
				case 1:
					
					ciphertext = VigenereEnDec(true);
					cout << "Cipher text: " << ciphertext << endl << endl;
					cout << "Press Y/y to continue or any key to exit: ";
					cin >> x;
					cout << endl;

					break;
				case 2:
					
					plaintext = VigenereEnDec(false);
					cout << "Plain text: " << plaintext << endl << endl;
					cout << "Press Y/y to continue or any key to exit: ";
					cin >> x;
					cout << endl;
					break;
				case 3:
					x = "n";
					break;
				}

				break;

			case 3:
				x = "n";
				break;
		}

	} while (x == "Y" || x == "y");

	cout << "Program exited successfully" << endl << endl;
}


int main()
{
	MAIN();

	cout << "Press Enter to continue...";
	cin.ignore();
	cin.get();

	return 0;
}