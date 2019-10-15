#include<bits/stdc++.h>
using namespace std;

int main()
{
  string str;
  cin>>str;
  string odd,even,res;
  for(int i=0;i<str.length();i++){
    if(i%2==0) odd+=str[i];
    else even+=str[i];
  }
  res=odd+even;
  cout<<res;
}
