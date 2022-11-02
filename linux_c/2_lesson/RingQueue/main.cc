#include "RingQueue.hpp"

using namespace std;

pthread_mutex_t c_lock;
pthread_mutex_t p_lock;

void* consumer(void* arg){
    RingQueue* rq = (RingQueue*)arg;
    while (true){
        //sleep(1);
        int data = 0;
        //lock
        pthread_mutex_lock(&c_lock);
        rq->Get(data);
        //unlock
        pthread_mutex_unlock(&c_lock);
        std::cout << "consumer done...# " << data << std::endl;
    }
}

void* productor(void* arg){
    RingQueue* rq = (RingQueue*)arg;
    int count = 100;
    while (true){
        sleep(1);
        //lock
        pthread_mutex_lock(&p_lock);
        rq->Put(count++);
        //unlock
        pthread_mutex_unlock(&p_lock);
        if (count > 110){
            count = 100;
        }
        std::cout << "productor done...# " << std::endl;
    }
}

int main() {
    pthread_t c, c1, c2, p, p1, p2;
    RingQueue* rq = new RingQueue();
    pthread_create(&c, nullptr, consumer, rq);
    pthread_create(&c1, nullptr, consumer, rq);
    pthread_create(&c2, nullptr, consumer, rq);
    pthread_create(&p, nullptr, productor, rq);
    pthread_create(&p1, nullptr, productor, rq);
    pthread_create(&p2, nullptr, productor, rq);

    pthread_join(c, nullptr);
    pthread_join(c1, nullptr);
    pthread_join(c2, nullptr);
    pthread_join(p, nullptr);
    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);

    delete rq;
    return 0;
}
