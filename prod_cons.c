#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex, empty_spaces, filled_spaces;
int x = 0;
int p = 0;
int c = 0;
int n = 0;
int buffer_size = 0;
int *buffer = NULL;

void *producer(void *args);
void *consumer(void *args);
int produce(void);
void insert(int some_product);
void consume(void);


int main() {
    int prod_qtt, cons_qtt, i, j;
    
    scanf("%d %d %d %d", &prod_qtt, &cons_qtt, &n, &buffer_size);

    buffer = calloc(buffer_size, sizeof(int));

    sem_init(&mutex, 0, 1);
    sem_init(&empty_spaces, 0, buffer_size);
    sem_init(&filled_spaces, 0, 0);

    int prod_id[prod_qtt];
    int cons_id[cons_qtt];

    pthread_t producers[prod_qtt];
    pthread_t consumers[cons_qtt];

    for (i = 0; i < prod_qtt; i++) {
        prod_id[prod_qtt] = i;
        pthread_create(&producers[i], NULL, producer, &prod_id[i]);
    }

    for (j = 0; j < cons_qtt; j++) {
        cons_id[cons_qtt] = j;
        pthread_create(&consumers[j], NULL, consumer, &cons_id[j]);
    }

    for (i = 0; i < prod_qtt; i++) {
        pthread_join(producers[i], NULL);
    }

    for (j = 0; j < cons_qtt; j++) {
        pthread_join(consumers[j], NULL);
    }
    
    return 0;
}

int produce(void) {
    int product;
    product = 2 * x + 1;
    if ( x < n) {
        x++;
    } else if ( x == n) {
        x = 0;
    }
    return product;
}

void insert(int some_product) {
    if (buffer[p] == 0) {
        buffer[p] = some_product;
    }
    
}

void *producer(void* args) {
    int *id = args;
    while (1) {
        sem_wait(&empty_spaces);
        sem_wait(&mutex);
        int the_product = produce();
        if (buffer[p] == 0){
            printf("Produtor %d produzindo %d na posição %d\n", *id, the_product, p);
            insert(the_product);
        }
        p++;
        if (p == buffer_size){
            p = 0;
        }
        sem_post(&mutex);
        sem_post(&filled_spaces);
    }

}

void consume(void) {
    if (buffer[c] != 0) {
        buffer[c] = 0;
    }
}

void *consumer(void* args) {
    int *id = args;
    while (1) {
        sem_wait(&filled_spaces);
        sem_wait(&mutex);
        if (buffer[c] != 0) {
            printf("Consumidor %d consumindo %d da posição %d\n", *id, buffer[c], c);
            consume();
        }
        c++;
        if (c == buffer_size) {
            c = 0;
        }
        sem_post(&mutex);
        sem_post(&empty_spaces);
    }
}