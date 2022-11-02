import test.inherit.Inherit;
import test.inherit.Student;

public class Main {
    public static void Test1() {
        Student s = new Student("Lily", 172, 92.5);
        System.out.println(s instanceof Inherit);
        System.out.println(s instanceof Student);
    }
    /*
    * @final
    * 1. 修饰变量：被其修饰的变量不可更改
    * 2. 修饰方法：被其修饰的方法不可重写，但是可以重载
    * 3. 修饰类： 被其修饰的类不能被继承
    * */
    public static void Test2() {
        Inherit i1 = new Inherit();
    }
    /*
    * @super
    * 1. 是父类对象的一个引用
    * 2. 可以使用super()调用父类的普通方法
    * 3. 在一个类中，如果构造方法没有在第一行显式的调用super()，则会默认调用super()，
    *       但此时super()调用的方法是父类的无参构造
    * */
    public static void main(String[] args) {
        Test1();
    }
}
