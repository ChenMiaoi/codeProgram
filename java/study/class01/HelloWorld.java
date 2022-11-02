/*
 一个java文件中只能有一个public的类
 且类名和java的文件名是相同的
 类名采用大驼峰的代码风格
 一个类会生成一个字节码文件(.class) -- 为了方便使用，需要哪一个类就加载哪一个.class文件
 */

public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("HelloWorld");
    }
}
