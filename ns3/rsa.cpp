#include <bits/stdc++.h>
#include <gmp.h>

using namespace std;

gmp_randstate_t state;

void phi(mpz_t p,mpz_t q,mpz_t o)
{
	mpz_t a,b;
	mpz_inits(a,b,NULL);
	mpz_sub_ui(a,p,1);
	mpz_sub_ui(b,q,1);
	mpz_mul(o,a,b);
}

string encrypt(string publicKey, string Message)
{
	string delimiter = "|";
	string token_n = publicKey.substr(0, publicKey.find(delimiter));
	string token_e = publicKey.substr(publicKey.find(delimiter)+1);
	for(unsigned int i=0 ;i<token_e.length();i++)
	{
		if(token_e[i]<'0'||token_e[i]>'9')
			token_e[i]='\0';
	}
	cout<<"n:"<<token_n<<" e:"<<token_e.c_str()<<"h"<<endl;
	mpz_t e,n;
	mpz_init_set_str (n, token_n.c_str(), 10);
	mpz_init_set_str (e, token_e.c_str(), 10);
	gmp_printf("n:%Zd e:%Zd\n",n,e);
	
	mpz_t M,C[Message.length()];
	mpz_init(M);
	cout<<"Cipher text:";
	string cipherText="";
	for(unsigned int i=0;i<Message.length();i++)
	{	
		int ascii = (int)Message[i];
		mpz_init(C[i]);
		mpz_set_ui(M,ascii);
		mpz_powm(C[i],M,e,n);
		gmp_printf("%Zd ",C[i]);
		cipherText += mpz_get_str (NULL, 10, C[i]);
		cipherText += "|";
	}

	cout<<endl;

	return cipherText;
}

string decrypt(string privateKey, string Cipher)
{
	string delimiter = "|";
	string token_n = privateKey.substr(0, privateKey.find(delimiter));
	string token_d = privateKey.substr(privateKey.find(delimiter)+1);
	// cout<<"n:"<<token_n<<" d:"<<token_d<<endl;
	mpz_t d,n;
	mpz_init_set_str (n, token_n.c_str(), 10);
	mpz_init_set_str (d, token_d.c_str(), 10);
	// gmp_printf("n:%Zd e:%Zd\n",n,d);
	int len=0;
	for(unsigned int i=0;i<Cipher.length();i++)
	{
		if(Cipher[i]=='|')
			len++;
	}
	mpz_t M,C[len];
	mpz_init(M);

	int i=0;
  	string plainText="";

  	char *token = strtok(const_cast<char*>(Cipher.c_str()), "|"); 
    while (token != NULL) 
    { 
    	mpz_init_set_str (C[i], (const char*)token, 10);
    	mpz_powm(M,C[i],d,n);
		int ascii = mpz_get_ui(M);
		plainText += (char)ascii;
		// cout<<(char)ascii;
        // gmp_printf("%Zd ",C[i]);
        token = strtok(NULL, "|");
        i++; 
    } 

	return plainText;
}

void generate_random(mpz_t p,int range)
{
	mpz_t n_random,random_num;
	mpz_init(random_num);
	mpz_init_set_ui(n_random,range);				//defining upper-limit of random number.
	mpz_urandomm(p,state,n_random);
}

void find_params(mpz_t e,mpz_t d,mpz_t o)
{
	mpz_t g,x,y;
	mpz_inits(g,x,y,NULL);
	generate_random(e,mpz_get_ui(o));
	mpz_gcdext(g,x,y,e,o);		//ex+oy=g
	while(mpz_get_ui(g)!=1)
	{
		mpz_nextprime(e,e);
		mpz_gcdext(g,x,y,e,o);
	}
	mpz_mod(e,e,o);
	mpz_mod(x,x,o);
	mpz_set(d,x);
}

/*
** generate a public key(n,e) and private key(n,d) pair.
** the keys are set in the parameters which are enmpty strings passed by creator.
*/

void keygen(string &publicKey,string &privateKey)
{
	 /*---------------KEYGEN---------------------*/
   unsigned long int seed = time(NULL);
   gmp_randinit_mt(state);
   gmp_randseed_ui(state,seed);
   mpz_t p,q,n,o,e,d;
   mpz_inits(p,q,n,o,e,d,NULL);
   generate_random(p,100000);
   generate_random(q,100000);
   while(mpz_probab_prime_p(p,25)!=2)
     mpz_nextprime(p,p);
   while(mpz_probab_prime_p(q,25)!=2)
     mpz_nextprime(q,q);
    
   mpz_mul(n,p,q);
   phi(p,q,o);
   find_params(e,d,o);
   cout<<"***********KEYGEN************"<<endl;
   gmp_printf("p:%Zd q:%Zd\n",p,q);
   gmp_printf("n:%Zd\n",n);
   gmp_printf("phi(n):%Zd\n",o);
   gmp_printf("e:%Zd d:%Zd\n",e,d);
   string pubKey,privKey;
   pubKey = mpz_get_str (NULL, 10, n);
   pubKey += "|";
   pubKey += mpz_get_str (NULL, 10, e);
  
   privKey = mpz_get_str (NULL, 10, n);
   privKey += "|";
   privKey += mpz_get_str (NULL, 10, d);
 
   publicKey = pubKey;
   privateKey = privKey;
}

// int main()
// {
// 	/*---------------KEYGEN---------------------*/
// 	unsigned long int seed = time(NULL);
// 	gmp_randinit_mt(state);
// 	gmp_randseed_ui(state,seed);
// 	mpz_t p,q,n,o,e,d;
// 	mpz_inits(p,q,n,o,e,d,NULL);
// 	generate_random(p,100);
// 	generate_random(q,100);
// 	while(mpz_probab_prime_p(p,25)!=2)
// 		mpz_nextprime(p,p);
// 	while(mpz_probab_prime_p(q,25)!=2)
// 		mpz_nextprime(q,q);
	
// 	mpz_mul(n,p,q);
// 	phi(p,q,o);
// 	find_params(e,d,o);
// 	cout<<"***********KEYGEN************"<<endl;
// 	gmp_printf("p:%Zd q:%Zd\n",p,q);
// 	gmp_printf("n:%Zd\n",n);
// 	gmp_printf("phi(n):%Zd\n",o);
// 	gmp_printf("e:%Zd d:%Zd\n",e,d);
// 	cout<<endl;
// 	/*-------------KEYGEN END-----------------*/

// 	/*-------------Encryption-----------------*/
// 	cout<<"***********Encryption*************"<<endl;
// 	string msg;
// 	cout<<"Enter Plain-text to encrypt: ";
// 	getline(cin,msg);
// 	mpz_t M,C[msg.length()];
// 	mpz_init(M);
// 	cout<<"Cipher text:";
// 	for(int i=0;i<msg.length();i++)
// 	{	
// 		int ascii = (int)msg[i];
// 		mpz_init(C[i]);
// 		mpz_set_ui(M,ascii);
// 		encrypt(M,e,n,C[i]);
// 		gmp_printf("%Zd",C[i]);
// 	}
// 	cout<<endl;
// 	/*-------------Encryption End------------*/

// 	/*-------------Decryption----------------*/
// 	cout<<endl;
// 	cout<<"*************Decryption*************"<<endl;
// 	cout<<"Decipher text: ";
// 	for(int i=0;i<msg.length();i++)
// 	{	
// 		Decrypt(C[i],d,n,M);
// 		int ascii = mpz_get_ui(M);
// 		cout<<(char)ascii;
// 	}
// 	cout<<endl;
// 	/*-------------Decryption End-----------*/
// }	
