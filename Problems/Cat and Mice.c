#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include<unistd.h>

#define NumBowls 4
#define NumCats  6
#define NumMice  2
#define CatWait  5      	// max time in seconds a cat sleeps
#define CatEat   1       	//how long in seconds a cat is eating
#define NumTimeCatEat 4     // how many times a cat wants to eat 
#define MouseWait     3     //max time in seconds a mouse sleeps
#define MouseEat      1     // how long in seconds a mouse is eating
#define NumTimeMouseEat 4   // how many times a mouse wants to eat

typedef struct Bowl {
    int FreeBowls;
    int CatsEating;
    int MiceEating;            // how many Mice are eating at the moment 
    int CatsWaiting;           // how many cats are waiting for Bowl 
    enum {NoneEating,CatEating,MouseEating} status[NumBowls];         // status of each Bowl 
    pthread_mutex_t mutex;      // mutex for accessing Bowl 
    pthread_cond_t FreeConditionVariable;     // used to wait for a free Bowl 
    pthread_cond_t CatConditionVariable;      // used to wait for coming cats 
} B;

static const char *progname = "animals";

static void DumpBowl(char *name, pthread_t animal, char *what, B *Bowl, int MyBowl)
{
    int i;
    printf("[    ");
    for (i = 0; i < NumBowls; i++) {
        if (i) printf(":");
        switch (Bowl->status[i]) {
        case NoneEating:
            printf("  -  ");
            break;
        case CatEating:
            printf("  cat %d",i);
            break;
        case MouseEating:
            printf("  mouse  %d",i);
            break;
        }}
            printf("     ] %s (   id %x  ) %s eating from Bowl %d \n", name, animal, what, MyBowl);

        }


static void* cat(void *arg)
{
    B *Bowl = (B *) arg;
    int n = NumTimeCatEat;
    int MyBowl = -1;
    int i;

    for (n = NumTimeCatEat; n > 0; n--) {

        pthread_mutex_lock(&Bowl->mutex);
        pthread_cond_broadcast(&Bowl->CatConditionVariable);
        Bowl->CatsWaiting++;
        while (Bowl->FreeBowls <= 0 || Bowl->MiceEating > 0) {
            pthread_cond_wait(&Bowl->FreeConditionVariable, &Bowl->mutex);
        }
        Bowl->CatsWaiting--;

        if(Bowl->FreeBowls > 0)
        {
        Bowl->FreeBowls--;
        if(Bowl->CatsEating < NumCats)
        {
        Bowl->CatsEating++;

        for (i = 0; i < NumBowls && Bowl->status[i] != NoneEating; i++) ;
        MyBowl = i;
        if(Bowl->status[MyBowl] == NoneEating)
        {
        Bowl->status[MyBowl] = CatEating;
        DumpBowl("cat", pthread_self(), "started", Bowl, MyBowl);
        pthread_mutex_unlock(&Bowl->mutex);

        sleep(1);

        pthread_mutex_lock(&Bowl->mutex);
        if(Bowl->FreeBowls < NumBowls)
        {
        Bowl->FreeBowls++;
        if(Bowl->CatsEating > 0)
        {
        Bowl->CatsEating--;
        Bowl->status[MyBowl] = NoneEating;

        pthread_cond_broadcast(&Bowl->FreeConditionVariable);
        DumpBowl("cat", pthread_self(), "finished", Bowl, MyBowl);
        pthread_mutex_unlock(&Bowl->mutex);

        sleep(5);
    	}}}}}}

    return 0;
}
static void* mouse(void *arg)
{
    B *Bowl = (B *) arg;
    int n = NumTimeMouseEat;
    struct timespec ts;
    struct timeval tp;
    int MyBowl;
    int i;

    for (n = NumTimeMouseEat; n > 0; n--) {

        pthread_mutex_lock(&Bowl->mutex);

        while (Bowl->FreeBowls <= 0 || Bowl->CatsEating > 0
               || Bowl->CatsWaiting > 0) {
            pthread_cond_wait(&Bowl->FreeConditionVariable, &Bowl->mutex);
        }

        if(Bowl->FreeBowls > 0)
        {
        Bowl->FreeBowls--;
        if(Bowl->CatsEating == 0)
        {
		if(Bowl->MiceEating < NumMice)
        {
		 Bowl->MiceEating++;

        for (i = 0; i < NumBowls && Bowl->status[i] != NoneEating; i++) ;
        MyBowl = i;
        if(Bowl->status[MyBowl] == NoneEating)
        {
        Bowl->status[MyBowl] = MouseEating;
        DumpBowl("mouse", pthread_self(), "started", Bowl, MyBowl);
        pthread_mutex_unlock(&Bowl->mutex);

		pthread_mutex_lock(&Bowl->mutex);
        pthread_cond_timedwait(&Bowl->CatConditionVariable, &Bowl->mutex, &ts);
        pthread_mutex_unlock(&Bowl->mutex);
        
		sleep(1);
        
		pthread_mutex_lock(&Bowl->mutex);
        if(Bowl->FreeBowls < NumBowls)
        {
        Bowl->FreeBowls++;
        if(Bowl->CatsEating == 0)
        {
        if(Bowl->MiceEating > 0)
        {
        Bowl->MiceEating--;
        Bowl->status[MyBowl]=NoneEating;

        pthread_cond_broadcast(&Bowl->FreeConditionVariable);
        DumpBowl("mouse", pthread_self(), "finished", Bowl, MyBowl);
        pthread_mutex_unlock(&Bowl->mutex);

		sleep(3);
    }}}}}}}}

    return NULL;
}
int main()
{
    int i, err;
    B _Bowl, *Bowl;
    pthread_t cats[NumCats];
    pthread_t Mice[NumMice];
    Bowl = &_Bowl;
    memset(Bowl, 0, sizeof(B));
    Bowl->FreeBowls = NumBowls;
    pthread_mutex_init(&Bowl->mutex, NULL);
    pthread_cond_init(&Bowl->FreeConditionVariable, NULL);
    pthread_cond_init(&Bowl->CatConditionVariable, NULL);

	for (i = 0; i < NumCats; i++) {
        err = pthread_create(&cats[i], NULL, cat, Bowl);
        if (err != 0) {
            printf(stderr, "%s: %s(): unable to create cat thread %d: %s\n",progname, __func__, i, strerror(err));
        }
    }

	for (i = 0; i < NumMice; i++) {
        err = pthread_create(&Mice[i], NULL, mouse, Bowl);
        if (err != 0) {
            printf(stderr, "%s: %s(): unable to create mouse thread %d: %s\n",progname, __func__, i, strerror(err));
        }
    }
    for (i = 0; i < NumCats; i++) {
        (void) pthread_join(cats[i], NULL);
    }
    for (i = 0; i < NumMice; i++) {
        (void) pthread_join(Mice[i], NULL);
    }

    pthread_mutex_destroy(&Bowl->mutex);
    pthread_cond_destroy(&Bowl->FreeConditionVariable);
    pthread_cond_destroy(&Bowl->CatConditionVariable);

    return 1;
}