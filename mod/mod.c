#include<gmp.h>
#include<time.h>

int main()
{
  int size;
	mpz_t a,b,n,t1,t2,t3;
	gmp_randstate_t state;
  gmp_randinit_mt(state);
  unsigned long seed;
  seed = time(NULL);
  gmp_randseed_ui(state,seed);
	mpz_inits(a,b,n,t1,t2,t3,NULL);
	// mpz_init(b);
  // mpz_init(n);

	gmp_printf("Enter the size of the number : ");
	gmp_scanf("%d",&size);
	gmp_randinit_default(state);
	mpz_rrandomb(a, state, size);
	mpz_rrandomb(b, state, size);
  mpz_rrandomb(n, state, size);
	gmp_printf("Three randomly generated numbers are  : %Zd %Zd %Zd \n\n",a,b,n);
  mpz_add(t1,a,b);
  mpz_mod(t2,t1,n);
	gmp_printf("(a+b) mod n is %Zd\n\n",t2);
  mpz_mod(t1,a,n);
	gmp_printf("a mod n is %Zd\n\n",t1);
  mpz_mod(t2,b,n);
	gmp_printf("b mod n is %Zd\n\n",t2);
  mpz_add(t3,t1,t2);
  mpz_mod(t2,t3,n);
	gmp_printf("(a mod n + b mod n) mod n is %Zd\n\n",t2);
  mpz_sub(t1,a,b);
  mpz_mod(t2,t1,n);
	gmp_printf("(a-b) mod n is %Zd\n\n",t2);
  mpz_mul(t1,a,b);
  mpz_mod(t2,t1,n);
	gmp_printf("(a*b) mod n is %Zd\n\n",t2);
}
