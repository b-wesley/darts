//simulates darts being thrown at a dart board in order to estimate pi


#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define s 10000

unsigned long inside = 0, outside = 0, total = 0, throws = 10000000, nThreads = 2;
long double pi, x, y, distance, centerX = (long double)s/2.0, centerY = (long double)s/2.0;

double getRunTime(double ti, double tf){
    double runTime = (tf - ti)/CLOCKS_PER_SEC;
    return runTime;
}

long double randFloat(long double min, long double max)
{
    long double range = (max - min);
    long double div = RAND_MAX /range;
    return min + (rand() / div);
}

void* dartThrow(){
    unsigned long in = 0, out = 0;

    for(int i = 0; i<(double)throws/(double)nThreads; i++){
        x = randFloat((long double) 0, (long double) s);
        y = randFloat((long double) 0, (long double) s);

        distance = sqrtl(powl((x-centerX),2)+powl((y-centerY),2));

        if(distance<(double)s/2.0){
            in++;
        }
        else{
            out++;
        }
    }
    inside += in;
    outside += out;

}

int main() {
    pthread_t thread1, thread2;

    clock_t ti, tf;

    ti = clock();

    pthread_create(&thread1, NULL, dartThrow, NULL);
    pthread_create(&thread2, NULL, dartThrow, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    tf = clock();
    double rt = getRunTime(ti, tf);

    total = inside + outside;
    pi = (long double) 4.0 * (long double)inside / (long double)total;

    printf("pi is approximately %Lf\n", pi);
    printf("Runtime: %f seconds \n", rt);
}
