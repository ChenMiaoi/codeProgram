#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
//已知某种密码的加密规则是：用原来字母后面的第 4 个字母，代替原来的字母。
// 例如，将“China”转成密码，因为字母‘C’后面第 4 个字母是字母‘G’，因此用‘G’代替‘C’，以此类
//推。因此，“China”应译为“Glmre”。如果后面第 4 个大于字母‘z’或‘Z’，则回到字母表头部继
//续编码，即 26 个小写、大写字母分别形成环状编码。例如字母‘x’后的第 4 个字母是‘b’。
//编写程序，对任意输入的 5 位字母串，将其转换为密码，输出原文和密码。
//int main(){
//    int count = 0, x = 5;
//    int i;
//    while (x > 0){
//        printf("%d", x);
//        x /= 2;
//    }
//    printf("%d", x);
//    return 0;
//}