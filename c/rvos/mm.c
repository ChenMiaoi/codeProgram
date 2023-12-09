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
 */
typedef struct page {
    uint8_t flags;
} page_t;

static inline void page_clean(page_t* page) {
    page->flags = !PAGE_TAKEN;
}

static inline uint32_t page_align(uint32_t pa) {
    uint32_t order = (1 << PAGE_ORDER) - 1;
    return (pa + order) & (~order);
}

void page_init(void) {
    /**
     * 我们需要保留`8页(8 x 4096)`来维护一个页描述结构体
     * 使其能够管理至少 `128MB(8 x 4096 x 4096)`
     */
    _page_nums = (HEAP_SIZE / PAGE_SIZE) - 8;
    printf("HEAP START = %x, HEAP SIZE = %x, num of pages = %d\n", HEAP_START, HEAP_SIZE, _page_nums);
    
    page_t* page = (page_t*)HEAP_START;
    for (int i = 0; i < _page_nums; i++, page++) {
        page_clean(page);
    }

    _alloc_start = page_align(HEAP_START + 8 * PAGE_SIZE);
    _alloc_end   = _alloc_start + (PAGE_SIZE * _page_nums);

    printf("TEXT:      %x -> %x\n", TEXT_START, TEXT_END);
    printf("RODATA:    %x -> %x\n", RODATA_START, RODATA_END);
    printf("DATA:      %x -> %x\n", DATA_START, DATA_END);
    printf("BSS:       %x -> %x\n", BSS_START, BSS_END);
    printf("HEAP:      %x -> %x\n", _alloc_start, _alloc_end);
}