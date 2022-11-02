#ifndef __PROTOCOL__H__
#define __PROTOCOL__H__

typedef class request{
public:
    int x;
    int y;
    char op; //"+", "-", "*", "/", "%"
}request_t;

typedef class response{
public:
    int code;   //0-->success, 1,2,3,4->不同的错误信息
    int result;
}response_t;

#endif // __PROTOCOL__H__