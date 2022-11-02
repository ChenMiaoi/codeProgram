#include <ThreadPool.hpp>

int main(){
    ThreadPool* tp = new ThreadPool();
    tp->ThreadPoolInit();

    //server
    while (true){
        int x = rand() % 10 + 1;
        Task t(x);
        tp->Put(t);
        sleep(2);
    }
    tp->ThreadQuit();
    return 0;
}