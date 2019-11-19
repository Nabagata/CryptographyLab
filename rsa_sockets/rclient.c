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
    mpz_t n , e , M , C;
    mpz_inits(n , e , M , C , NULL);
    
    char* buffer;
    buffer = malloc(10000);
    
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


    if(connect(sfd , (struct sockaddr *) &addr , sizeof(addr)) < 0)
    {
        printf("Error in connect");
        fflush(stdout);
    }
    
    else
    {
        printf("\nsuccessfully connected\n");
    }

    read(sfd , buffer , 10000);
    mpz_set_str(n , buffer , 62);
    gmp_printf("\nn is - %Zd\n" , n);   

    read(sfd , buffer , 10000);
    mpz_set_str(e , buffer , 62);
    gmp_printf("\ne is - %Zd\n" , e);   


    printf("\nEnter the message - ");
    scanf("%s" , buffer);
    mpz_set_str(M , buffer , 62); 
    gmp_printf("\nM is - %Zd\n" , M);   

    
    mpz_powm(C , M , e , n);
    gmp_printf("\nC is - %Zd \n" , C);
    mpz_get_str(buffer , 62 , C);
    write(sfd , buffer , 10000);
}
