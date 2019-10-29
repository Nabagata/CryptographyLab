#include <iostream>
using namespace std;

string encrypt(string text, string key)
{
	string result = "";
  int j=key.length();
	for (int i=0;i<text.length();i++)
	{
		// if (isupper(text[i]))
		// 	result += char(int(text[i]+(int(key[i%j])-64)-65)%26 +65);
    //
  	// else
      // cout<<(int(text[i]-97))<<" "<<(int(key[i%j])-97)<<" ";
  		result += char((int(text[i]-97)+(int(key[i%j])-97))%26 +97);
	}

	return result;
}

string decrypt(string text, string key)
{
	string result = "";
  int j=key.length();
	for (int i=0;i<text.length();i++)
	{
		// if (isupper(text[i]))
		// 	result += char(int(text[i]-(int(key[i%j])-64)-65)%26 +65);
    //
  	// else
  		result += char((int(text[i]-97)-(int(key[i%j])-97)+26)%26 +97);
	}

	return result;
}

int main()
{
	string text="hello";
  string key="xmckl";

	cout << "Text : " << text;
	cout << "\nKey: " << key;
	cout << "\nCipher: " << encrypt(text, key);
  cout << "\nText : " << decrypt(encrypt(text, key), key);
  cout<<endl;
	return 0;
}
