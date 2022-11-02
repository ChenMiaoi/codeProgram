#include "blockQueue.hpp"

using namespace std;

pthread_mutex_t c_lock;
pthread_mutex_t p_lock;

void* comsumer_run(void* arg){
    BlockQueue* bq = (BlockQueue*)arg;
    while (true){
        //int n = 0;
        //lock
        //pthread_mutex_lock(&c_lock);
        Task t;
        bq->Get(t);
        cout << "consumer : " << t.x << " + " << t.y << " = " << t.Run() << endl;
        //unlock
        //pthread_mutex_unlock(&c_lock);
        //cout << "consumer data is : " << n << endl;
        sleep(1);
    }
}

void* productor_run(void* arg){
    BlockQueue* bq = (BlockQueue*)arg;
    //int count = 0;
    while (true){
        //int data = rand() % 10 + 1;
        //lock
        //pthread_mutex_lock(&p_lock);
        //count = count % 5 + 1;
        int x = rand() % 10 + 1;
        int y = rand() % 100 + 1;
        Task t(x, y);
        bq->Put(t);
        //unlock
        //pthread_mutex_lock(&p_lock);
        cout << "product Task is : " << x << " + " << y << " = ?" << endl;
        //sleep(1);
    }
}

int main() {
    BlockQueue* bq = new BlockQueue(5);
    pthread_t c, p;
    pthread_create(&c, nullptr, comsumer_run, (void*)bq);
    pthread_create(&p, nullptr, productor_run, (void*)bq);

    pthread_join(c, nullptr);
    pthread_join(p, nullptr);
    delete bq;
    return 0;
}
