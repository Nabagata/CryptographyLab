#include<bits/stdc++.h>
using namespace std;

vector<int> div(vector<int> v1, vector<int> v2)
{
  vector<int> res(v1.size());
  for(int i=0;i<v2.size();i++){
    for(int j=0;j<v1.size();j++){
      res[i-j]=v1[i]/v2[j];
    }
  }
  return res;
}

vector<int> multiply(vector<int> v1, vector<int> v2)
{
   vector<int> res(v1.size()+v2.size()-1,0);

   for (int i=0; i<v1.size(); i++)
   {
     for (int j=0; j<v2.size(); j++)
         res[i+j] += v1[i]*v2[j];
   }

   return res;
}

vector<int> add(vector<int> v1, vector<int> v2)
{
  vector<int> res(v1.size());
  for(int i=0;i<v1.size();i++){
    res[i]=v1[i]+v2[i];
  }
  return res;
}

vector<int> sub(vector<int> v1, vector<int> v2)
{
  vector<int> res(v1.size());
  for(int i=0;i<v1.size();i++){
    res[i]=v1[i]-v2[i];
  }
  return res;
}

void mod(vector<int> &v)
{
  for(int i=0;i<v.size();i++){
    v[i]=v[i]%2;
  }
}

void disp(vector<int> v)
{
  for(int i=0;i<v.size();i++){
    if(i!=v.size()-1) cout<<v[i]<<"*x^"<<v.size()-i-1<<" + ";
    else cout<<v[i]<<"*x^"<<v.size()-i-1;
  }
  cout<<"\n\n";
}

int main()
{
  vector<int> p1,p2,p3;
  int temp;
  cout<<"Enter coefficients of 1st polynomial:\n";
  for(int i=0;i<5;i++){
    cout<<"x^"<<5-i-1<<" ";
    cin>>temp;
    p1.push_back(temp);
  }
  cout<<"Enter coefficients of 2nd polynomial:\n";
  for(int i=0;i<5;i++){
    cout<<"x^"<<5-i-1<<" ";
    cin>>temp;
    p2.push_back(temp);
  }

  cout<<"After addition: \n";
  p3 = add(p1,p2);
  disp(p3);

  cout<<"After subtraction: \n";
  p3 = sub(p1,p2);
  disp(p3);

  cout<<"After multiplication: \n";
  p3 = multiply(p1,p2);
  disp(p3);
  mod(p3);
  cout<<"After mod: \n";
  disp(p3);

  cout<<"After division: \n";
  p3 = div(p1,p2);
  disp(p3);
}
