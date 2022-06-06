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

    sleep(1);
    int val =0;
    /*******************************************
    Utworz/otworz posixowy obszar pamieci wspolnej "reprezentowany" przez SHM_NAME
    odczytaj zapisana tam wartosc i przypisz ja do zmiennej val
    posprzataj
    *********************************************/
    int shm_fd = shm_open(SHM_NAME, O_RDWR | O_CREAT, 0666);
//    ftruncate(shm_fd, MAX_SIZE);
    int *shm = mmap(NULL, MAX_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    val = *shm;



    munmap(shm, MAX_SIZE);
    shm_unlink(SHM_NAME);

	printf("%d square is: %d \n",val, val*val);
    return 0;
}
