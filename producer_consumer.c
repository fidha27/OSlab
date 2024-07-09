#include<stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int sem=1;
int no=1;
int state=0;

void wait(int *sema)
{
        pthread_mutex_lock(&mutex);
        while(*sema<=0)
        {
        pthread_cond_wait(&cond,&mutex);
        }
        (*sema)--;
        pthread_mutex_unlock(&mutex);
}
void signal(int *sema)
{
        pthread_mutex_lock(&mutex);
        (*sema)++;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);

}
void *producer(void *args)
{
        while(1)
        {
                wait(&sem);
                if(state==0)
                {
                        printf("Producer produce:%d\n",no);
                        no++;
                        state=1;
                }
                signal(&sem);
                sleep(1);
        }
        pthread_exit(NULL);
}
void *consumer(void *args)
{
        while(1)
        {
                wait(&sem);
                if(state==1)
                {
                        printf("Consumer consumes:%d\n",no);
                        no++;
                        state=0;
                }
                signal(&sem);
                sleep(1);
        }
        pthread_exit(NULL);
}
void main()
{
        pthread_t id1,id2;
        pthread_mutex_init(&mutex,NULL);
        pthread_cond_init(&cond,NULL);

        pthread_create(&id1,NULL,producer,NULL);
        pthread_create(&id2,NULL,consumer,NULL);

        pthread_join(id1,NULL);
        pthread_join(id2,NULL);

        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
}


