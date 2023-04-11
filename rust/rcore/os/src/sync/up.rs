use core::cell::{RefCell, RefMut};

pub struct UPSafeCell<T> {
    inner: RefCell<T>                                       // 智能指针，允许拥有不可变引用时修改数据 -> 内部可变性
}

unsafe impl<T> Sync for UPSafeCell<T> {}                    // 保证在多个线程内共享数据安全

impl<T> UPSafeCell<T> {
    pub unsafe fn new(value: T) -> Self {
        Self {
            inner: RefCell::new(value),
        }
    }
    pub fn exclusive_access(&self) -> RefMut<'_, T> {       // RefMut是RefCell的一个智能指针，允许在拥有可变引用时修改数据
        self.inner.borrow_mut()
    }
}