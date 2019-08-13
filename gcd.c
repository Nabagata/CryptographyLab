#include<gmp.h>

int main()
{
  mpz_t a,b,t;
  mpz_inits(a,b,t,NULL);
  gmp_scanf("%Zd %Zd",a,b);
  while(mpz_cmp_ui(b,0)!=0){
    mpz_set(t,b);
    mpz_mod(b,a,b);
    mpz_set(a,t);
  }
  gmp_printf("%Zd\n",a);
}
