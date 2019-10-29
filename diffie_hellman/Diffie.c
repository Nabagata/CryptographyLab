#include<gmp.h>
#include<stdio.h>
#include<math.h>
void main()
{
  mpz_t c2,temp,x,y,a,b,A,B,gen,q,prk,pubk,n,t,c1;
  int i,bt;
  unsigned long seed ;
  mpz_inits(c2,temp,x,y,a,b,A,B,gen,q,prk,pubk,n,t,c1,NULL);
  
  mpz_set_ui(b,1000);  			/*Random number generation*/
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
  }while(mpz_probab_prime_p(n,100)==1 || mpz_probab_prime_p(n,10)!=2);

  for(i=1;i<20;i++)
  {
    mpz_set_ui(t,i);
    mpz_powm_ui(c1,t,2,n);
    mpz_powm(c2,t,q,n);
    if((mpz_cmp_ui(c1,1)!=0)&&(mpz_cmp_ui(c1,1)!=0))
    {
      break;
    }
  }
  mpz_set_ui(gen,i);
  gmp_printf("\nGenerator : %Zd",gen);

  mpz_sub_ui(temp,n,2);
  mpz_urandomm(x,s,temp); 
  mpz_urandomm(y,s,temp); 
  mpz_powm(a,gen,x,n);
  mpz_powm(b,gen,y,n);
  gmp_printf("\nA send : %Zd\nB send : %Zd", a,b);
  mpz_powm(A,b,x,n);
  mpz_powm(B,a,y,n);
  gmp_printf("\nA computes : %Zd and \nB computes : %Zd\n", A,B);
}
   
