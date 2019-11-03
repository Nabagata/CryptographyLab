#include<gmp.h>

int main()
{
  mpz_t a,b,t,op;
  mpz_inits(a,b,op,t,NULL);
  gmp_scanf("%Zd %Zd %Zd",a,b,op);

  if(mpz_cmp_ui(op,1)==0){ mpz_add(t,a,b); gmp_printf("%Zd\n",t);}
  else if(mpz_cmp_ui(op,2)==0){ mpz_sub(t,a,b); gmp_printf("%Zd\n",t);}
  else if(mpz_cmp_ui(op,3)==0){ mpz_mul(t,a,b); gmp_printf("%Zd\n",t);}
  else if(mpz_cmp_ui(op,4)==0){ mpz_fdiv_q(t,a,b); gmp_printf("%Zd\n",t);}
}
