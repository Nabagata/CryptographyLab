#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

int main()
{    
    mpz_t p , q , n , p_1 , q_1 , phi_n , e , d , bits_512 , random , rem , M , C , gcd;
    mpz_inits(p , q , n , p_1 , q_1 , phi_n , e , d , bits_512 , random , rem , e , d , M , C , gcd , NULL);

    char* buffer;
    buffer = malloc(100000);
    
    mpz_ui_pow_ui(bits_512 , 2 , 512);
    
    gmp_randstate_t state;
    gmp_randinit_default(state);
    
    struct timeval t;
    gettimeofday(&t , NULL);
    int seed = t.tv_usec;
    
    gmp_randseed_ui(state , seed);
    
    mpz_urandomb(random , state , 512);
    mpz_add(p , bits_512 , random);
    mpz_nextprime(p , p);
    
    mpz_urandomb(random , state , 512);
    mpz_add(q , bits_512 , random);
    mpz_nextprime(q , q);
    
    mpz_sub_ui(p_1 , p , 1);
    mpz_sub_ui(q_1 , q , 1);
    
    mpz_mul(n , p , q);
    mpz_mul(phi_n , p_1 , q_1);
    
    mpz_urandomb(random , state , 512);
    mpz_add(e , bits_512 , random);
    mpz_gcd (gcd , e , phi_n);         
    while(mpz_cmp_ui(gcd , 1) != 0)
    {
        mpz_urandomb(random , state , 512);
        mpz_add(e , bits_512 , random);
        mpz_gcd (gcd , e , phi_n);         
    }
    
    mpz_invert(d , e , phi_n);

    int sfd = socket(AF_INET , SOCK_STREAM , 0);
    if(sfd < 0)
    {
        printf("Error in creating socket\n");
        fflush(stdout);   
    }

    struct sockaddr_in addr;
    bzero((char*)&addr , sizeof(addr));

    addr.sin_family = AF_INET ;
    addr.sin_addr.s_addr = INADDR_ANY ;
    addr.sin_port = htons(2000);

    if( bind(sfd , (struct sockaddr *) &addr , sizeof(addr)) < 0 )
    {
        printf("Error in binding\n");
        fflush(stdout);
    }
   
    listen(sfd , 7);
    socklen_t cli_len = sizeof(struct sockaddr_in);
    int nsfd = accept(sfd , (struct sockaddr *) &addr , &cli_len);
    if(nsfd < 0)
    {
        printf("Error in accept\n");
        fflush(stdout);
    }
    
    else
    {
        printf("\nsuccessfully connected\n");
    }

    gmp_printf("\nn is - %Zd\n" , n);   
    mpz_get_str(buffer , 62 , n);
    write(nsfd , buffer , 10000);

    gmp_printf("\ne is - %Zd\n" , e);   
    mpz_get_str(buffer , 62 , e);
    write(nsfd , buffer , 10000);

    read(nsfd , buffer , 10000);
    mpz_set_str(C , buffer , 62);
    gmp_printf("\nC is - %Zd\n" , C);

    mpz_powm(M , C , d , n);
    gmp_printf("\nM is - %Zd \n" , M);
    mpz_get_str(buffer , 62 , M);
    printf("\nThe message is - %s\n" , buffer);
}