#include<gmp.h>
#include<stdio.h>
#include<math.h>
void main()
{
  mpz_t gamma,pubA,q,nx,y,a,b,A,B,gen,m,k,t,c1,c2,temp,prk,pubk,delta,n;
  int i,bt;
  unsigned long seed ;
  mpz_inits(gamma,pubA,q,nx,y,a,b,A,B,gen,m,k,t,c1,c2,temp,prk,pubk,delta,n,NULL);

  mpz_set_ui(b,1000);				/*Random number generation*/
  gmp_randstate_t s;
  gmp_randinit_mt(s);

  seed=time(NULL);
  gmp_randseed_ui(s,seed);
  printf("\nEnter bits p followed by q :");
  scanf("%d",&bt);
  do
  {
		mpz_rrandomb(q,s,bt);
		mpz_nextprime(q,q);
		mpz_mul_ui(temp,q,2);
		mpz_add_ui(temp,temp,1);
		mpz_set(n,temp);
  }while(mpz_probab_prime_p(n,10)!=2);

  for(i=1;i<20;i++)
  {
		mpz_set_ui(t,i);
		mpz_powm_ui(c1,t,2,n);
		mpz_powm(c2,t,q,n);
		if((mpz_cmp_ui(c1,1)!=0)&&(mpz_cmp_ui(c1,1)!=0))
		      break;
  }

  mpz_set_ui(gen,i);
  gmp_printf("\nGenerator : %Zd",gen);
  mpz_sub_ui(temp,n,2);
  mpz_urandomm(a,s,temp);
  mpz_powm(pubA,gen,a,n);
  gmp_printf("\nPublickey: %Zd and \n Privatekey: %Zd \n",pubA,a);
  mpz_urandomm(m,s,n);
  mpz_urandomm(k,s,temp);
  mpz_powm(gamma,gen,k,n);
  mpz_powm(delta,pubA,k,n);
  mpz_mul(delta,delta,m);
  mpz_mod(delta,delta,n);
  gmp_printf("\nm = %Zd\nk = %Zd\nCiphertext (C1,C2) : ( %Zd , %Zd )\n",m,k,gamma,delta);
  mpz_sub(temp,n,a);
  mpz_sub_ui(temp,temp,1);
  mpz_powm(A,gamma,temp,n);
  mpz_mul(A,A,delta);
  mpz_mod(A,A,n);
  gmp_printf("\nPlain Text Text is : %Zd\n",A);


}
