#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>


sem_t not_empty,empty;

pthread_mutex_t mutex;

int store[20];

int x=0,y=0;

int sum=0;

void *pro(void *arg)
{
int i=0;
while(i<30)
{
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    store[x] = i+1;
    x = (x+1)%20;

    pthread_mutex_unlock(&mutex);
    sem_post(&not_empty);

    i++;
}
return 0;
}

void *con(void *arg)
{
    int j,temp;
    while(j<30)
    {
    sem_wait(&not_empty);
    pthread_mutex_lock(&mutex);

    temp = store[y];
    y = (y + 1)%20;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    sum=sum+temp;
    j++;
    }
    return 0;
}

int main()
{
  sem_init(&not_empty, 0, 0);
  sem_init(&empty, 0, 20);
  pthread_t th1,th2,th3,th4;
  pthread_mutex_init(&mutex,NULL);

  pthread_create(&th1, NULL, pro, NULL);
  pthread_create(&th2, NULL, pro, NULL);
  pthread_create(&th3, NULL, con, NULL);
  pthread_create(&th4, NULL, con, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  pthread_join(th3, NULL);
  pthread_join(th4, NULL);

  printf("SUM is: %d\n", sum);
  return 0;

}
