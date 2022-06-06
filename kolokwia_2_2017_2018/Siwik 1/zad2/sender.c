#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <unistd.h>
#include <sys/mman.h>

#define SHM_NAME "/kol_shm"
#define MAX_SIZE 1024

int main(int argc, char **argv)
{
    
   if(argc !=2){
    printf("Not a suitable number of program parameters\n");
    return(1);
   }

   /***************************************
   Utworz/otworz posixowy obszar pamieci wspolnej "reprezentowany" przez SHM_NAME
   zapisz tam wartosc przekazana jako parametr wywolania programu
   posprzataj
   *****************************************/
    int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0666);
    ftruncate(shm_fd, MAX_SIZE);
    int *shm = mmap(NULL, MAX_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    *shm = atoi(argv[1]);
//    printf("%d\n", *shm);

    munmap(shm, MAX_SIZE);

    return 0;
}
