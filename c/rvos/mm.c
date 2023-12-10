#include "os.h"

/**
 * 获取定义在`mem.S`中的全局变量
 */
extern uint32_t TEXT_START;
extern uint32_t TEXT_END;
extern uint32_t DATA_START;
extern uint32_t DATA_END;
extern uint32_t RODATA_START;
extern uint32_t RODATA_END;
extern uint32_t BSS_START;
extern uint32_t BSS_END;
extern uint32_t HEAP_START;
extern uint32_t HEAP_SIZE;

/* `_alloc_start` 指向物理地址开始的堆地址处 */
static uint32_t _alloc_start = 0;
/* `_alloc_end` 指向物理地址结束的堆地址处 */
static uint32_t _alloc_end   = 0;
/* `_page_nums` 维护了实际可以申请的最大页数 */
static uint32_t _page_nums   = 0;

#define PAGE_SIZE (1 << 12)
#define PAGE_ORDER 12

#define PAGE_TAKEN (uint8_t)(1 << 0)
#define PAGE_LAST  (uint8_t)(1 << 1)

/**
 * 页描述结构体
 * 
 * flags:
 *    - bit 0: 表示该页已经被申请(taken)
 *    - bit 1: 表示该页是分配的内存块的最后一块
 * 
 * uint8_t:
 * -----------------------------------------------------------
 *  0       0       0       0       0       0       0       0
 * -----------------------------------------------------------
 *  ^       ^       ^       ^       ^       ^       ^       ^
 *  |                Reserved               |     last?    taken?
 */
typedef struct page {
    uint8_t flags;
} page_t;

/**
 * 清除标志位
 * 
 * @param page 需要被清除的页 
 */
static inline void page_clean(page_t* page) {
    page->flags = !PAGE_TAKEN;
}

/**
 * 对物理地址进行对齐操作，以4096一页为基础
 * 这就使得，每次分配页都一定是从以4096对齐处开始的
 *  
 * @param pa 需要对齐的物理地址
 * @return uint32_t 返回对齐后的地址
 */
static inline uint32_t page_align(uint32_t pa) {
    uint32_t order = (1 << PAGE_ORDER) - 1;
    return (pa + order) & (~order);
}

/**
 * 检查该页是否可用(空闲)
 * 
 * @param page 需要进行检查的页
 * @return int 如果已经被分配，就返回0，否则返回1
 */
static inline int is_free(page_t* page) {
    if (page->flags & PAGE_TAKEN) return 0;
    else return 1;
}

/**
 * 设置标志位
 *      - PAGE_TAKEN: 标识该页已经被分配
 *      - PAGE_LAST: 标识该页是已分配内存块的最后一页
 * 
 * @param page 需要被标记的页
 * @param flags PAGE_TAKEN、PAGE_LAST
 */
static inline void set_flag(page_t* page, uint8_t flags) {
    page->flags |= flags;
}

/**
 * 检查是否到达已分配的最后页
 * 
 * @param page 需要检查的页
 * @return int 如果是最后一块，返回1，否则返回0
 */
static inline int is_last(page_t* page) {
    if (page->flags & PAGE_LAST) return 1;
    else return 0;
}

/**
 * 内存管理的初始化函数，我们假设起始的8页用于页描述结构体
 * 为什么假定8页？
 *      计算式为：8 x 4096(页大小) x 4096(每一个字节维护一个页描述结构体) = 128MB
 *
 * 因为我们的页描标识符内部是一个uint8_t的字段，也就是说该结构体只占1字节，刚好契合，
 * @code
 *  page_t* page = (page_t*)HEAP_START
 * @endcode
 * 通过指针强转，能够实现每一次页表加一步进长度就是一个页描述符的长度
 */
void page_init(void) {
    /**
     * 我们需要保留`8页(8 x 4096)`来维护一个页描述结构体
     * 使其能够管理至少 `128MB(8 x 4096 x 4096)`
     */
    _page_nums = (HEAP_SIZE / PAGE_SIZE) - 8;
    printf("HEAP START = %x, HEAP SIZE = %x, num of pages = %d\n", 
        HEAP_START, HEAP_SIZE, _page_nums);
    
    /* 对每一个页描述符进行清空 */
    page_t* page = (page_t*)HEAP_START;
    for (int i = 0; i < _page_nums; i++, page++) {
        page_clean(page);
    }

    /* 计算除预留8页后的起始地址和结束地址 */
    _alloc_start = page_align(HEAP_START + 8 * PAGE_SIZE);
    _alloc_end   = _alloc_start + (PAGE_SIZE * _page_nums);

    printf("TEXT:      %x -> %x\n", TEXT_START, TEXT_END);
    printf("RODATA:    %x -> %x\n", RODATA_START, RODATA_END);
    printf("DATA:      %x -> %x\n", DATA_START, DATA_END);
    printf("BSS:       %x -> %x\n", BSS_START, BSS_END);
    printf("HEAP:      %x -> %x\n", _alloc_start, _alloc_end);
}

/**
 * 进行一个粗粒度的页表分配(一次分配 npages 页)
 * 
 * @param npages 需要分配多少页
 * @return void* 返回分配页的起始地址
 */
void* page_alloc(int npages) {
    int found = 0;

    /* 每一次都从堆可分配地址最开始处寻找空闲内存 */
    page_t* page = (page_t*)HEAP_START;
    for (int i = 0; i <= (_page_nums - npages); i++, page++) {
        /* 通过is_free判断分配标志位是否为1 */
        if (is_free(page)) {
            found = 1;

            /* 此处要寻找连续的足够npages * PAGE_SIZE的内存块
               因为此时的机制很简单，只允许连续分配这样的简单操作 */
            page_t* page_j = page + 1;
            for (int j = i + 1; j < (i + npages); j++, page_j++) {
                if (!is_free(page_j)) {
                    found = 0;
                    break;
                }
            }

            /* 为该连续的内存块设置分配标志位，并返回其首地址 */
            if (found) {
                page_t* page_k = page;
                for (int k = i; k < (i + npages); k++, page_k++) {
                    set_flag(page_k, PAGE_TAKEN);
                }
                /* 标记该内存块的最后一个页为LAST */
                page_k--;
                set_flag(page_k, PAGE_LAST);

                return (void*)(_alloc_start + i * PAGE_SIZE);
            }
        }
    }

    return NULL;
}

/**
 * 简单的页表释放
 * 
 * @param p 需要释放的页表首地址
 */
void page_free(void* p) {
    /* 如果传入空或者无效的地址 */
    if (!p || (uint32_t)p >= _alloc_end) return;

    /* 计算出该地址属于哪一个页描述符管理 */
    page_t* page = (page_t*)HEAP_START;
    page += ((uint32_t)p - _alloc_start) / PAGE_SIZE;

    /* 对其管理的页描述符进行清空 */
    while (!is_free(page++)) {
        page_clean(page);
        if (is_last(page)) {
            break;
        }
    }
}

void page_test() {
    void* p = page_alloc(2);
    printf("p = %x\n", p);
    page_free(p);

    void* p1 = page_alloc(5);
    printf("p1 = %x\n", p1);
}