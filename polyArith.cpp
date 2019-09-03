#include<bits/stdc++.h>
using namespace std;
void makeBinary(string s,int a[]){
	for(int i=0;i<s.size();i++){
		if(s[i]>='0' && s[i]<='9'){
			a[s[i]-'0']=1;
		}
	}
}
void displayBinary(int a[]){
	for(int i=14;i>=0;i--){
		if(a[i]==1){
			cout<<"x^"<<i<<" + ";
		}		
	}
	cout<<endl;
}
void add(int p1[],int p2[],int res[]){
	for(int i=0;i<14;i++){
		res[i]=p1[i]+p2[i];
		res[i]%=2;
	}
}
void sub(int p1[],int p2[],int res[]){
	for(int i=0;i<14;i++){
		res[i]=p1[i]+p2[i];
		res[i]%=2;
	}
}
void mul(int p1[],int p2[],int res[]){
	for(int i=0;i<14;i++){
		for(int j=0;j<14;j++){
			res[i+j]+=p1[i]*p2[j];
		}
	}
	for(int i=0;i<=14;i++){
		res[i]%=2;
	}
}
void div(int p[],int div[],int quo[]){
	int maxDegOfDiv=0;
	for(int i=14;i>=0;i--){
		if(div[i]==1){
			maxDegOfDiv=i;
			break;
		}
	}
	while(1){
		int maxDegOfP=0;
		for(int i=14;i>=0;i--){
			if(p[i]==1){
				maxDegOfP=i;
				break;
			}
		}
		if(maxDegOfP<maxDegOfDiv){
			break;
		}else{
			int dif=maxDegOfP-maxDegOfDiv;
			quo[dif]=1;
			int tempQuo[14]={0};
			int toBeXored[14]={0};
			int temp[14]={0};
			tempQuo[dif]=1;
			mul(tempQuo,div,toBeXored);
			sub(p,toBeXored,temp);
			for(int i=0;i<14;i++){
				p[i]=temp[i];
			}
		}
	}
	
}
void mod(int p[],int div[],int rem[]){
	int maxDegOfDiv=0;
	for(int i=14;i>=0;i--){
		if(div[i]==1){
			maxDegOfDiv=i;
			break;
		}
	}
	while(1){
		int maxDegOfP=0;
		for(int i=14;i>=0;i--){
			if(p[i]==1){
				maxDegOfP=i;
				break;
			}
		}
		if(maxDegOfP<maxDegOfDiv){
			for(int i=0;i<14;i++){
				rem[i]=p[i];
			}
			break;
		}else{
			int dif=maxDegOfP-maxDegOfDiv;
			int tempQuo[14]={0};
			int toBeXored[14]={0};
			int temp[14]={0};
			tempQuo[dif]=1;
			mul(tempQuo,div,toBeXored);
			sub(p,toBeXored,temp);
			for(int i=0;i<14;i++){
				p[i]=temp[i];
			}
		}
	}
}
int main(){
	cout<<"Enter P1: ";
	string poly1;
	cin>>poly1;
	cout<<"Enter P2: ";
	string poly2;
	cin>>poly2;
	int p1[15]={0},p2[15]={0},res[15]={0};
	makeBinary(poly1,p1);
	makeBinary(poly2,p2);
	add(p1,p2,res);
	cout<<"The addition of the two polynomials is: ";
	displayBinary(res);

	for(int i=0;i<14;i++){
		res[i]=0;
	}

	sub(p1,p2,res);
	cout<<"The subtraction of the two polynomials is: ";
	displayBinary(res);

	for(int i=0;i<14;i++){
		res[i]=0;
	}

	mul(p1,p2,res);
	cout<<"The multiplication of the two polynomials is: ";
	displayBinary(res);	

	for(int i=0;i<14;i++){
		res[i]=0;
	}	

	div(p1,p2,res);
	cout<<"The division of the two polynomials is: ";
	displayBinary(res);	

	for(int i=0;i<14;i++){
		res[i]=0;
	}	

	mod(p1,p2,res);
	cout<<"The mod of the two polynomials is: ";
	displayBinary(res);	
}