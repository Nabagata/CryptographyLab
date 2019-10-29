#include<stdio.h>
#include<gmp.h>
#include<time.h>
#include<string.h>

void main()
{
char str[100];int i;
int flag=0;
mpz_t cipher[100];
for(i=0;i<99;i++)
	mpz_init(cipher[i]);

mpz_t p,q,x,p1,q1,phi,e,t1,d,msg,cip,n,t2;
mpz_inits(p,q,x,p1,q1,phi,e,t1,d,msg,cip,n,t2,NULL);
gmp_randstate_t s;
gmp_randinit_mt(s);
unsigned long seed;
seed=time(NULL);
gmp_randseed_ui(s,seed);
mpz_set_ui(x,100000000000);
mpz_urandomm(p,s,x);
mpz_urandomm(q,s,x);

mpz_nextprime(p,p);
mpz_nextprime(q,q);

//mpz_set_ui(p,11);
//mpz_set_ui(q,7);
gmp_printf("p:%Zd  q:%Zd\n",p,q);
mpz_mul(n,p,q);
gmp_printf("n:%Zd\n",n);
mpz_sub_ui(p,p,1);
mpz_sub_ui(q,q,1);
mpz_mul(phi,p,q);
//gmp_printf("%Zd  %Zd\n",p,q);

while(!flag)
{
	mpz_urandomm(e,s,phi);	
	mpz_gcd(t1,e,phi);
	if(mpz_cmp_ui(t1,1)==0)
	{	flag=1;
		break;
	}
}
mpz_invert(d,e,phi);
gmp_printf("Public Key e: %Zd n: %Zd\n",e,n);
gmp_printf("Private Key d: %Zd\n",d);
printf("Enter the message : ");
//gmp_scanf("%Zd",msg);
scanf("%s",str);
printf("Cipher text : ");
for(i=0;i<strlen(str);i++)
{
	int MSG=(int)str[i];
	mpz_add_ui(msg,t2,MSG);
	mpz_powm(cip,msg,e,n);
	mpz_set(cipher[i],cip);
	//gmp_printf("ASCII text : %Zd\n",msg);
	gmp_printf("%Zd",cip);
}

	printf("\nMessage text : ");
	for(i=0;i<strlen(str);i++)
	{
	mpz_powm(msg,cipher[i],d,n);
	int car=mpz_get_ui(msg);
	printf("%c",car);
	}
	printf("\n");
}









