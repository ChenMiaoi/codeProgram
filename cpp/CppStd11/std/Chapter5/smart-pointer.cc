#include <iostream>
#include <sys/mman.h>
#include <functional>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

/**
 * ! 使用智能指针是为了解决在多个pointer指向同一个对象，无法明确知道是否释放时
 * ? 自C++11起，就有了两大类的smart pointer
 *  ? class shared_ptr 实现共享式拥有概念，多个smart pointer可以指向相同对象，该对象和其相关资源会在“最后一个reference”被销毁
 *      ? -> 其提供了weak_ptr、bad_weak_ptr和enable_shared_from_this等辅助类
 *  ? class unique_ptr 实现独占式或严格拥有概念，保证同一时间内只有一个smart pointer可以指向该对象，且可以转交拥有权
*/

// ! shared_ptr的目的在于，在其所指向的对象不被需要之后，自动释放与对象相关的资源

void foo() {
    // ? 创建两个shared_ptr
    // ! 注意，这里是接受单一实参的explicit构造函数，因此只能通过显式声明，或者使用make_shared<>()
    std::shared_ptr<std::string> pNico (new std::string("nico"));
    std::shared_ptr<std::string> pJutty (new std::string("jutta"));

    // ? 使用shared_ptr
    (*pNico)[0] = 'N';
    pJutty->replace(0, 1, "J");

    // ! 将其多次放入容器中，如果是一般而言，我们放进去的是拷贝，执行的也是copy，而传入shared_ptr就相当于传入了reference,也就是std::ref
    std::vector<std::shared_ptr<std::string>> whoMadeCoffee;
    whoMadeCoffee.push_back(pJutty);
    whoMadeCoffee.push_back(pJutty);
    whoMadeCoffee.push_back(pNico);
    whoMadeCoffee.push_back(pJutty);
    whoMadeCoffee.push_back(pNico);

    // ? 进行打印操作
    for (auto ptr : whoMadeCoffee)
        std::cout << *ptr << " ";
    std::cout << "\n";

    // 重写数据
    *pNico = "Nicolai";
    for (auto ptr : whoMadeCoffee)
        std::cout << *ptr << " ";
    std::cout << "\n";

    // 打印其内部数据
    // ! 可以看见，第一个shared_ptr调用的结果反应的是其本身和三份拷贝的结果
    std::cout << "user count: " << whoMadeCoffee[0].use_count() << std::endl;
    std::cout << "user count: " << pNico.use_count() << std::endl;
}

void foo1() {
    // ! 这种是错误的
    // std::shared_ptr<std::string> p = new std::string("hello");
    std::shared_ptr<std::string> p = std::make_shared<std::string> ("hello");
    std::shared_ptr<std::string> p1 {new std::string("world")};

    // ! 另一种写法可以先声明，后赋值，但是也不能直接使用赋值，需要调用reset()接口
    std::shared_ptr<std::string> p2;
    // p2 = new std::string("hello");
    p2.reset(new std::string("hello"));
}

// ! 我们可以自己定义一份deleter，也就是析构器
/**
 * ! 但是，对于shared_ptr default deleter调用的是delete，因此无法解决delete[]的问题，此时就需要我们手动的
 * ! 定义我们自己的deleter
*/

void foo2() {
    std::shared_ptr<std::string> pNico (new std::string("nico"), [](std::string* p) {
        std::cout << "delete: " << *p << std::endl;
        delete p;
    });

    // std::shared_ptr<int> p (new int[10]); error
    std::shared_ptr<int> p (new int[10], [](int* p) {
        delete[] p;
    });
    /**
     * ! 但是，在unique_ptr中，其默认的辅助函数为 std::default_delete<>()，因此unique_ptr可以使用默认deleter
     * ? 显然，shared_ptr也可以使用这一辅助函数
    */
   std::shared_ptr<int> p1 (new int[10], std::default_delete<int[]>());
   std::unique_ptr<int[]> p2 (new int[10]);

   // ! 如果使用unique_ptr的时候想自己定义deleter，需要指明其类型
   std::unique_ptr<int, void (*)(int*)> p3 (new int[10], [](int* p) {
        delete[] p;
   });
}

/**
 * ! 制定自己的析构策略：例一，确保“指向某临时文件”最末一个reference被销毁时，该文件被移除
*/

class FileDeleter
{
private:
    std::string filename;
public:
    FileDeleter(const std::string& fn): filename(fn) { }
    void operator() (std::ofstream* fp) {
        fp->close();    // 关闭文件
        std::remove(filename.c_str());  // 删除
    }
};

void foo3() {
    std::shared_ptr<std::ofstream> fp (
        new std::ofstream("tmpfile.txt"), FileDeleter("temfile.txt")
    );
}

/**
 * ! 例二，使用shared_ptr处理共享内存
*/

class ShareMemoryDetacher { // ! 实际上可以由lambda表达式代替，作为deleter不允许抛出异常
public:
    void operator() (int* p) noexcept {
        std::cout << "unlink /tmp1234" << std::endl;
        /**
         * ! shm_unlink(const char* name)
         * ! 删除shm_open()所创建的共享内存对象
         * 
         * @param name 已存在的共享内存对象名
         * 
         * @return 如果成功，返回0，否则返回-1表示失败
        */
        if (shm_unlink("/tmp1234") != 0) {
            std::cerr << "OOPS: shm_unlink() failed" << std::endl;
        }
    }
};

std::shared_ptr<int> getShareIntMemory(int num) {
        void* mem;
        /**
         * ! shm_open(const char* name, int oflag, mode_t mode)
         * ! 其创建或者打开一个新的 、已经存在的POSIX标准的共享内存对象，POSIX共享内存对象实际上是一个句柄，
         * ! 不相关的进程可以通过mmap来使用同一区域的共享内存
         * 
         * @param name 指定要创建或打开的共享内存对象名，为了可移植使用，共享内存对象应该由 /somename 形式的名称所标识
         *              也就是说，一个以null结束字符串最多到 NAME_MAX(0..255)个字符，且其由一个初始斜杠，后跟一个或多个字符(其中不能包含斜杠)组成
         * 
         * @param oflag 是一个位掩码，通过将O_RDONLY or O_RDWR中的一个与下列任何其他标志进行OR运算而创建的
         * @param O_RDONLY 打开共享内存对象进行读访问
         * @param O_RDWR 打开共享内存对象进行读写访问
         * @param O_CREAT 如果该共享内存对象不存在，则创建。对象的用户和组所有权取自调用进程的对应有效ID，对象的权限位根据mode_t的低九位设置
         *                除了那些在进程文件模式创建的掩码中所设置的位(umask)
         * 
         * @param mode 其指定创建新文件时所被应用的文件模式位，如果在oflag中既没有指定O_CREAT又没有指定O_TMPFILE，那么可以省略该参数(一般用0来表示省略)
         *             如果在标志位中指定了O_CREAT或O_TMPFILE，那么必须提供其所需要的mode参数，否则堆栈中的一些任意字节将用作文件模式
         *             有效模式(effictive)通常由进程的umask作为基准而修改：在默认没有ACL的情况下，其mode = mode & ~umask
         * @param S_IRWXU 00700 user可读写执行权限
         * @param S_IRUSR 00400 user可读权限
         * @param S_IWUSR 00200 user可写权限
         * @param S_IXUSR 00100 user可执行权限
         * @param S_IRWXG 00070 group可读写执行权限
         * ...
         * 
         * @return 如果执行成功，返回一个文件描述符(非负整数)，否则返回-1表示失败
        */
        int shmfd = shm_open("/tmp1234", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
        if (shmfd < 0) {
            throw std::string(strerror(errno));
        }
        if (ftruncate(shmfd, num * sizeof(int)) == -1) {
            throw std::string(strerror(errno));
        }
        /**
         * ! mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset)
         * ! 其在调用进程的的虚拟地址空间中创建一个新映射集合。新映射的起始地址在addr中指定，length参数指定映射长度(必须大于0)
         * 
         * @param addr 如果参数为NULL(nullptr)，则由内核选择创建映射的(一般是页面对齐的)地址，并且，这种方式是创建映射集合最简便的方式。
         *             如果 addr 不为 NULL，那么内核会将其作为放置映射的提示； 在 Linux 上，内核将选择附近的页面边界（
         *             但始终高于或等于 /proc/sys/vm/mmap_min_addr 指定的值）并尝试在那里创建映射。 如果那里已经存在另一个映射，
         *             内核会选择一个新地址，该地址可能取决于也可能不取决于提示。 新映射的地址作为调用结果返回。
         * @param length 文件映射的内容使用从文件描述符fd引入的文件中的偏移量offset开始的length字节进行初始化。其偏移量offset必须是
         *               sysconf(_SC_PAGE_SIZE)的整数倍
         * ! 当mmap()成功返回后，文件描述符可以直接被关闭，而不会影响mapping
         * @param prot 该参数描述了映射所需的内存保护(并且不得与文件的打开模式冲突)。其是以PROT_NONE为基准进行或操作
         * @param PROT_NONE Pages可能不会被获取
         * @param PROT_EXEC Pages可能被执行
         * @param PROT_READ Pages可能被读取
         * @param PROT_WRITE Pages可能被写入
         * 
         * @param flags 该参数决定了映射集合的更新是否对映射同一区域的其他进程可见，以及更新是否传递到底层文件
         * @param MAP_SHARED 共享该映射。映射的更新对于映射同一区域的其他进程是可见的，并且(在文件支持的映射的情况下)被传递到底层文件
         * @param MAP_PRVATE 创建一个私有的写时拷贝映射。对映射的更新对映射同一文件的其他进程不可见，并且不会传递到基础文件。 
         *                   未指定在映射区域中是否可见调用 mmap() 后对文件所做的更改。
         * 
         * @param fd 通过shm_open所或许到的文件描述符
         * @param offset 在文件描述符中对应的偏移量
         * 
         * @return 如果成功，mmap返回一个指向映射集合区域的指针，否则返回MAP_FAILED(即为(void*)-1)
        */
        mem = mmap(nullptr, num * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
        if (mem == MAP_FAILED) {
            throw std::string(strerror(errno));
        }
        return std::shared_ptr<int> (static_cast<int*>(mem), ShareMemoryDetacher());
    }

void foo4() {
    // ! 获取100int单位大小的共享内存
    std::shared_ptr<int> smp(getShareIntMemory(100));
    // ? 初始化共享内存
    for (int i = 0; i < 100; i++)
        smp.get()[i] = i * 42;  // ! shared_ptr不提供指针运算和operator[]，因此如果想要直接访问，必须通过get()来获取被包覆(wrapped)的内部指针
        // ? 其类似于 (&*smp)[i] = i * 42 或者说 (&(*smp))[i] = i * 42;
    std::cout << "<return>" << std::endl;

    // 释放共享内存
    smp.reset();
} 

/**
 * ! 虽然shared_ptr好用，但是对于类似所谓的cycle reference(环式指向)，也就是说，如果两个对象使用的shared_ptr互相指向对方，且不存在其他
 * ! reference指向它们的时候，想要释放这两个互相指向的资源是很困难的，因为每一个对象的use_count()总是存在的。另一个例子就是“明确想共享但不愿拥有”的情况。
 * ! 因此，标准库提供了weak_ptr，允许你“共享但不拥有”某对象。
*/

class Person {
public:
    std::string name;
    std::shared_ptr<Person> mother;
    std::shared_ptr<Person> father;
    // std::vector<std::shared_ptr<Person>> kids;
    // ! 采用weak_ptr
    std::vector<std::weak_ptr<Person>> kids;

    Person (const std::string& n, std::shared_ptr<Person> m = nullptr, std::shared_ptr<Person> f = nullptr)
        : name(n)
        , mother(m)
        , father(f) {}
    
    ~Person() {
        std::cout << "delete " << name << std::endl;
    }
};

std::shared_ptr<Person> initFamily (const std::string& name) {
    std::shared_ptr<Person> mom(new Person(name + "'s mom"));
    std::shared_ptr<Person> dad(new Person(name + "'s dad"));
    std::shared_ptr<Person> kid(new Person(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

void foo5() {
    std::shared_ptr<Person> p = initFamily("nico");
    // ! 在p被另外一个对象赋值之前，其内部的nico被共享了三次，父 -> nico，母 -> nico, nico -> 父母
    std::cout << "nico's family exists" << "\n"
              << "- nico is shared " << p.use_count() << " times" << "\n"
              << "- name of 1st kid of nico's mom: " << p->mother->kids[0].lock()->name << std::endl;
    // ! lock()会产出一个empty shared_ptr
    p = initFamily("jim");
    std::cout << "jim's family exists" << std::endl;
    // ! 可以发现，这里出去以后，析构函数未能被调用，当p重新被赋值时，其析构函数因为Person还至少被一个shared_ptr所指向而无法释放
}

/**
 * ! 误用shared_ptr，除了上述的循环依赖外，还有一种可能就是必须确保某对象只被一组shared_ptr拥有
*/

void foo6() {
    int* p = new int;
    std::shared_ptr<int> sp1(p);
    std::shared_ptr<int> sp2(p); // ! error， 因为sp1和sp2在丢失p的时候进行对应的销毁，因此p会被销毁两次

    // ! 因此，如果你需要这样做，那么应该以下面这一种方式
    std::shared_ptr<int> s1(new int);
    std::shared_ptr<int> s2(s1); // ! OK
}

/**
 * ! unique_ptr独占式智能指针，该指针要求其所指向的对象只有唯一拥有者，因此，当unique_ptr销毁时，其所指向的对象也自动被销毁
*/

class A {
   
};

void foo7() {
    std::unique_ptr<A> ptr(new A);

    std::unique_ptr<std::string> up(new std::string("nico"));
    (*up)[0] = 'N';
    up->append("lai");
    std::cout << *up << std::endl;

    // ! 可以使用release()获取所拥有的对象并放弃其拥有权
    std::string* sp = up.release();
    if (up) 
        std::cout << *up << std::endl;
}

void foo8() {
    std::string* sp = new std::string("hello");
    std::unique_ptr<std::string> up1(sp);
    // std::unique_ptr<std::string> up2(sp); // ! 此处显然是错误的，要保证unique_ptr只有一个指向 
    // ! 但是，C++11其提供了移动语义，我们可以将所有权交付给up2
    std::unique_ptr<std::string> up2(std::move(up1)); // OK
    std::unique_ptr<std::string> up3 = std::move(up2); // OK
    std::cout << *up3 << std::endl;

    // ! 如果在移动前，需要移动的对象已经有了一个拥有权，那么在之后失去拥有权了并不会获得一个“指向无物”的新拥有权
    // ! 如果想指派新值，那么新值必须也是unique
    up2 = std::unique_ptr<std::string> (new std::string("world"));
    std::cout << *(up2) << std::endl;
}

void sink(std::unique_ptr<std::string> up) {
    std::cout << "sink: " << *up << std::endl;
}

std::unique_ptr<std::string> source() {
    std::unique_ptr<std::string> up(new std::string("source's src"));
    // ! 在此处不需要显式的调用std::move()，因为C++语法会进行对应的RVO优化
    return up;
}

void foo9() {
    // ! 当函数是接收端，如果我们传入一个std::move()，那么调用的函数参数会得到unique的所有权，并且在函数结束时被delete
    std::unique_ptr<std::string> up(new std::string("hello"));
    sink(std::move(up));
    if (up == nullptr)
        std::cout << "up was moved" << std::endl;
    
    // ! 当函数是供应端，如果函数返回一个unique，其拥有权便会被转移
    std::unique_ptr<std::string> p;
    for (int i = 0; i < 10; i++) {
        p = source();
        std::cout << "source was moved #" << i << ": " << *p << std::endl;
    }
}

// ! 如果你使用unique代替普通指针，那么就不再需要析构函数，因为对象被删除会连带所有成员被删除

class ClassA {
public:
    ClassA(int var): a(var) {}
private:
    int a;
};

class ClassB {
public:
    ClassB(int var1, int var2)
        : ptr1(new ClassA(var1))
        , ptr2(new ClassA(var2)) {}
    ClassB(const ClassB& x)
        : ptr1(new ClassA(*x.ptr1)) // 隐式类型转化了
        , ptr2(new ClassA(*x.ptr2)) {}
    const ClassB& operator= (const ClassB& x) {
        *ptr1 = *x.ptr1;
        *ptr2 = *x.ptr2;
        return *this;
    }
    // ~ClassB() {
    //     delete ptr1;
    //     delete ptr2;
    // } ! 如果将类型改为unique则不再需要
private:
    // ClassA* ptr1;
    // ClassA* ptr2;
    std::unique_ptr<ClassA> ptr1;
    std::unique_ptr<ClassA> ptr2;
};

// ! 当我们想要处理array时，unique提供了一个偏特化接口，但是该接口不再提供*或 -> 而是提供operator[]

template<typename T>
using uniquePtr = std::unique_ptr<T, void(*)(T*)>;
void foo10() {
    std::unique_ptr<int[]> up(new int[10]{0});
    std::cout << up[5] << std::endl;

    // ! 自定义deleter，需要指出其类型
    std::unique_ptr<int, void(*)(int*)> up1(new int, [](int* p){
        delete p;
        std::cout << "delete p" << std::endl;
    });
    std::unique_ptr<int, std::function<void(int*)>> up2(new int, [](int* p) {
        delete p;
        std::cout << "delete p" << std::endl;
    });
    
    // ! 为了避免必须指明delete类型，可以使用alias template
    uniquePtr<int> up3(new int, [](int* p) {
        delete p;
        std::cout << "delete p" << std::endl;
    });
}

int main() { 
    foo();
    foo2();
    foo3();
    foo4();
    foo5();
    foo7();
    foo8();
    foo9();
    foo10();
    return 0;
}