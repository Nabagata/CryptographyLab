#include<bits/stdc++.h>
using namespace std;

void disp(vector<int> v)
{
  for(int i=0;i<v.size();i++){
    if(i!=v.size()-1) cout<<v[i]<<"*x^"<<v.size()-i-1<<" + ";
    else cout<<v[i]<<"*x^"<<v.size()-i-1;
  }
  cout<<"\n\n";
}


vector<int> multiply(vector<int> v1, vector<int> v2, int n)
{
   vector<int> res(v1.size()+v2.size()-1,0);

   for (int i=0; i<v1.size(); i++)
   {
     for (int j=0; j<v2.size(); j++)
         if(i+j>n) res[i+j] += v1[i]*v2[j];
   }

   return res;
}

// vector<int> div(vector<int> v1, vector<int> v2)
// {
//   vector<int> res(v1.size());
//   int lpos2;
//   for(int i=0;i<v2.size();i++){
//     if(v2[i]==1){
//       lpos2=i; break;
//     }
//   }
//   for(int lpos2=0;i<v2.size();i++){
//     if(v2[i]){
//       int lpos1;
//       for(int j=0;j<v1.size();j++){
//         if(v1[j]==1){
//           lpos1=j; break;
//         }
//       }
//       vector<int> sub(v1.size()),temp(v2.size(),0);
//       temp[lpos1-lpos2]=1;
//       sub=multiply(v2,temp);
//       v1=sub
//       disp(sub);
//     }
//   }
//   return res;
// }

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

int main()
{
  vector<int> p1,p2,p3;
  int temp,n;
  cout<<"Enter n for 2^n:\n";
  cin>>n;
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
  mod(p3);
  disp(p3);

  cout<<"After subtraction: \n";
  p3 = sub(p1,p2);
  mod(p3);
  disp(p3);

  cout<<"After multiplication: \n";
  p3 = multiply(p1,p2,n);
  disp(p3);
  mod(p3);
  cout<<"After mod: \n";
  disp(p3);

  // cout<<"After division: \n";
  // p3 = div(p1,p2);
  // disp(p3);
}
