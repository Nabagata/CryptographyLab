#include<stdio.h>
#include<gmp.h>

void egcd(mpz_t a,mpz_t b)
{
mpz_t x,s,t,r,old_s,old_t,old_r,zero,temp,quotient,tempq,temps,n,add_result,mod_result1,mod_result2,real_res;
mpz_inits(x,s,t,r,old_s,old_t,old_r,zero,temp,quotient,tempq,temps,n,add_result,mod_result1,mod_result2,real_res,NULL);

mpz_set_ui(s,0);
mpz_set_ui(t,1);
mpz_set_ui(old_s,1);
mpz_set_ui(old_t,0);
mpz_set(r,b);
mpz_set(old_r,a);


while(mpz_cmp(r,zero)!=0)
{
mpz_fdiv_q(quotient,old_r,r);

mpz_set(temp,r);
mpz_mul(tempq,quotient,temp);
mpz_sub(r,old_r,tempq);
mpz_set(old_r,temp);

mpz_set(temp,s);
mpz_mul(tempq,quotient,temp);
mpz_sub(s,old_s,tempq);
mpz_set(old_s,temp);

mpz_set(temp,t);
mpz_mul(tempq,quotient,temp);
mpz_sub(t,old_t,tempq);
mpz_set(old_t,temp);
}
gmp_printf("\nGCD(%Zd,%Zd) = %Zd \n\n",a,b,old_r);
gmp_printf("Value of X:%Zd and Y:%Zd \n\n",old_s,old_t);

if(mpz_cmp_ui(old_r,1)!=0)
	printf("Modular inverse doesn't exist\n\n");
else
{
	mpz_mod(mod_result1,old_s,b);
	mpz_add(add_result,mod_result1,b);
	mpz_mod(mod_result2,add_result,b);
	gmp_printf("The modular multiplicative inverse is %Zd\n\n",mod_result2);
	mpz_invert(real_res,a,b);
	gmp_printf("Accodrding to the library function is %Zd\n\n",real_res);		
}	

}



void main(void)
{
	int size;
	mpz_t a,b;
	gmp_randstate_t state;
	mpz_init(a);
	mpz_init(b);
	
	printf("Enter the size of the number to find GCD : ");
	scanf("%d",&size);
	gmp_randinit_default(state);
	mpz_rrandomb(a, state, size);
	mpz_rrandomb(b, state, size);
	gmp_printf("Two randomly generated number is  : %Zd and %Zd\n ",a,b);
	egcd(a,b);
	
}
