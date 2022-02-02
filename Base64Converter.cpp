/*
coded By mortza
For learning
*/
#include <iostream> 
#include <math.h> 
#include <conio.h> 
#include <windows.h>   
#include <string>

using namespace std;


string decimalToBinary(int, int);
int binaryToDecimal(string);
int getIndexOfBase64Char(char);
string encodeString(string);
string decodeString(string);
const int lengthOfBase64Chars = 64;
const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


int main()
{
	string girilenMetin;

	system("Color 04");
	system("cls");
	cout << "\n\n\t=+=+=+=+=+=+=+=+=";
	cout << "\n\n\tBase64Converter";
	cout << "\n\n\t=+=+=+=+=+=+=+=+=";
	cout << "\n\n\t==============================================";
	cout << "\n\n\tCoded By mortza";
	cout << "\n\n\tBase64Covertor";
	cout << "\n\n\t\033[32m--------------------------------------------------\033[0m";
	cout << "\n\n\t\033[32mEnter the text you want to convert to Base64 type:\033[0m";
	cout << "\n\n\t\033[32m--------------------------------------------------\033[0m" << endl;
	getline(cin, girilenMetin);
	cout << encodeString(girilenMetin) << endl << endl << endl;

	cout << "\n\n\t\033[32m--------------------------------------------------\033[0m";
	cout << "\n\n\t\033[32mEnter the text in the base64 round: \033[0m";
	cout << "\n\n\t\033[32m--------------------------------------------------\033[0m" << endl << endl;
	getline(cin, girilenMetin);
	cout << decodeString(girilenMetin) << endl << endl;
	system("Color 0A");
	system("pause");
	main();

	return 0;
}

string encodeString(string input) {
	string girilenMetin = input;
	string binaryData;
	int requiredExtraByte = 0;
	int* asciiKarsiliklari = (int*)malloc(sizeof(int) * girilenMetin.length());
	for (int i = 0; i < girilenMetin.length(); i++)
	{
		asciiKarsiliklari[i] = girilenMetin[i];
	}


	requiredExtraByte = girilenMetin.length() % 3 == 0 ? 0 : 3 - girilenMetin.length() % 3;


	for (int i = 0; i < girilenMetin.length() + requiredExtraByte; i++)
	{
		if (girilenMetin.length() > i) {
			binaryData += decimalToBinary(asciiKarsiliklari[i], 8);
		}
		else
		{

			binaryData += decimalToBinary(0, 8);
		}
	}

	string encodedData;

	for (int i = 0; i < binaryData.length(); i += 6)
	{
		string get6Digit = binaryData.substr(i, 6);

		int toDecimal = binaryToDecimal(get6Digit);


		if (binaryData.length() - (requiredExtraByte * 8) > i)
		{

			encodedData += base64chars[toDecimal];
		}
		else
		{

			encodedData += "=";
		}

	}

	return encodedData;
}


string decodeString(string input) {


	string decodedData = "";


	string binaryData = "";



	if (input.length() % 4 != 0) return "\t!Error:This not Valid Base64 Format!";


	int lastIndexCharOfInputStr = input.length() - 1;



	if (input[lastIndexCharOfInputStr] == '=') {


		input.erase(lastIndexCharOfInputStr, 1);


		lastIndexCharOfInputStr--;


		if (input[lastIndexCharOfInputStr] == '=')
		{

			input.erase(lastIndexCharOfInputStr, 1);
		}
	}


	for (int i = 0; i < input.length(); i++)
	{

		int index = getIndexOfBase64Char(input[i]);


		binaryData += decimalToBinary(index, 6);
	}





	for (int i = 0; i < binaryData.length(); i += 8)
	{

		char c = binaryToDecimal(binaryData.substr(i, 8));


		decodedData += c;
	}

	return decodedData;
}


int binaryToDecimal(string value) {

	int result = 0;

	for (int i = 0; i < value.length(); i++)
	{
		int digit = value[value.length() - i - 1] - '0';

		result = result + (digit * (pow(2, i)));
	}

	return result;
}


string decimalToBinary(int value, int digitFormat) {


	int divisionResult = value;


	int calculatedDigit = divisionResult % 2;


	divisionResult = (divisionResult - (divisionResult % 2)) / 2;


	string binaryDataStr = to_string(calculatedDigit);


	while (divisionResult > 0) {

		calculatedDigit = divisionResult % 2;
		divisionResult = (divisionResult - (divisionResult % 2)) / 2;


		binaryDataStr = to_string(calculatedDigit) + binaryDataStr;
	}


	if (digitFormat != -1 && binaryDataStr.length() < digitFormat)
	{
		int requiredZeros = digitFormat - binaryDataStr.length();

		for (int i = 0; i < requiredZeros; i++)
		{
			binaryDataStr = "0" + binaryDataStr;
		}
	}

	return binaryDataStr;
}


int getIndexOfBase64Char(char c) {

	for (int i = 0; i < lengthOfBase64Chars; i++)
	{
		if (base64chars[i] == c) {
			return i;
		}
	}

	return -1;
}