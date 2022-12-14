# Memory Pool

---  

## 内存池需要解决的问题

- 效率问题
  - 申请内存的效率问题
- 内存碎片问题
  - 申请空间后，释放资源了可能导致空间上会不连续，虽然有连续的空间，但是无法再次开辟一个较大的空间

## malloc

> 实际上C/C++最终申请内存是使用的malloc，new是通过封装malloc实现的。
> **malloc实际上就是一个内存池**

## 为什么学习tcmalloc

- tcmalloc是用于优化C++写多线程应用的，比与glibc 2.3的malloc更快。这个模块可以用来让MySQL在高并发下的内存占用更加稳定

## 定长内存池设计

- 解决固定大小的内存申请释放需求
  - 性能能够达到极致
  - 不用考虑内存碎片