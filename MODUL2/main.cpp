#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <queue>
#include <cstdlib>
#include <ctime>

const int BUFFER_SIZE = 10;

std::queue<int> buffer;
pthread_mutex_t mutex;
pthread_cond_t cond_non_empty;
pthread_cond_t cond_non_full;

void* generator(void* arg)
{
    srand(time(nullptr));
    while (true)
    {
        sleep(5);
        int num = rand() % 4 + 1;

        pthread_mutex_lock(&mutex);
        while (buffer.size() == BUFFER_SIZE)
       	{
            pthread_cond_wait(&cond_non_full, &mutex);
        }
        buffer.push(num);
        pthread_cond_signal(&cond_non_empty);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

void* reader(void* arg)
{
    while (true)
    {
        pthread_mutex_lock(&mutex);
        while (buffer.empty()) 
	{
            pthread_cond_wait(&cond_non_empty, &mutex);
        }
        int num = buffer.front();
        buffer.pop();
        std::cout << num << std::endl;
        pthread_cond_signal(&cond_non_full);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main()
{
    pthread_t generator_thread, reader_thread;
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond_non_empty, nullptr);
    pthread_cond_init(&cond_non_full, nullptr);

    pthread_create(&generator_thread, nullptr, generator, nullptr);
    pthread_create(&reader_thread, nullptr, reader, nullptr);

    pthread_join(generator_thread, nullptr);
    pthread_join(reader_thread, nullptr);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_non_empty);
    pthread_cond_destroy(&cond_non_full);

    return 0;
}
