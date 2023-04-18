use crate::config::KERNEL_HEAP_SIZE;
use buddy_system_allocator::LockedHeap;

#[global_allocator]
static HEAP_ALLOCATOR: LockedHeap = LockedHeap::empty();                                // 堆空间的分配，LockedHeap确保了线程安全
static mut HEAP_SPACE: [u8; KERNEL_HEAP_SIZE] = [0; KERNEL_HEAP_SIZE];                  // 真正的堆空间的定义

pub fn init_heap() {                                                                    // 堆空间的初始函数
    unsafe {
        HEAP_ALLOCATOR
            .lock()                                                 // 获取锁资源
            .init(HEAP_SPACE.as_ptr() as usize, KERNEL_HEAP_SIZE);        // 初始化堆空间(内核)
    }
}

#[alloc_error_handler]
pub fn handle_alloc_error(layout: core::alloc::Layout) -> ! {                           // 分配错误
    panic!("Heap allocation error, layout = {:?}", layout);
}