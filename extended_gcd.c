#include<gmp.h>

int main()
{
  mpz_t a,b,d,x,y,x1,x2,y1,y2,q,r,t;
  mpz_inits(a,b,d,x,y,x1,x2,y1,y2,q,r,t,NULL);
  gmp_scanf("%Zd %Zd",a,b);

  if(mpz_cmp_ui(b,0)==0){
    mpz_set(d,a);
    mpz_set_ui(x,1);
    mpz_set_ui(y,0);
  }
  mpz_set_ui(x2,1);
  mpz_set_ui(x1,0);
  mpz_set_ui(y2,0);
  mpz_set_ui(y1,1);

  while(mpz_cmp_ui(b,0)>0){
    mpz_fdiv_q(q,a,b);
    mpz_mul(t,q,b);
    mpz_sub(r,a,t);
    mpz_mul(t,q,x1);
    mpz_sub(x,x2,t);
    mpz_mul(t,q,y1);
    mpz_sub(y,y2,t);

    mpz_set(a,b);
    mpz_set(b,r);
    mpz_set(x2,x1);
    mpz_set(x1,x);
    mpz_set(y2,y1);
    mpz_set(y1,y);
  }
  mpz_set(d,a);
  mpz_set(x,x2);
  mpz_set(y,y2);

  gmp_printf("%Zd\n",d);
}
