class Person {
    public void eat() {
        System.out.println("eat");
    }
    public void sleep() {
        System.out.println("sleep");
    }
    public static void hello() {
        System.out.println("static hello");
        //静态方法内部，不允许访问非静态的数据成员
    }
    public String name;
    public int age;
    //如何访问静态数据成员？直接用类名访问
    public static int size = 10;
}

public class TestDemo {
    public static void main(String[] args) {
        Person person = new Person();
        System.out.println(Person.size);
        Person.hello();
        person.eat();
        person.sleep();
    }
    public static void main2(String[] args) {
        Person person = new Person();
        // 引用类型的默认值是null,内部类型的默认值是0, boolean的默认值是false
        System.out.println(person.name);
        System.out.println(person.age);
    }
    public static void main1(String[] args) {
        Person person1 = new Person();
        Person person2 = new Person();
        Person person3 = new Person();
        Person person4 = new Person();
    }
}
