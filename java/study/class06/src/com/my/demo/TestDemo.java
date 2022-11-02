package com.my.demo;    //必须加上包的路径

class Animal {
    public String name;

    public Animal(String name) {
        this.name = name;
    }
    public void  eat() {
        System.out.println("Animal::eat()");
    }
    private void sleep()  {
        System.out.println("Animal::sleep()");
    }
}

//java继承用extends关键字 -- 继承除构造函数外所有的
//在java中使用extends只有单继承
//如果父类有构造，那么子类要协助父类构造，使用super
/*
* this： 当前对象引用
* this(); 调用本类其他的构造方法
* this.data; 访问当前类中对象属性
* this.func(); 调用本类的其他成员方法
*
* super: 代表父类的引用
* super();  调用父类的构造方法
* super.data; 访问父类属性
* super.func(); 访问父类的成员方法
*/
class Cat extends Animal {
    public String name;

    public Cat(String name) {
        super(name);
    }
    @Override
    public void eat() {
        System.out.println("Cat::eat()");
    }
}

class Bird {
    public String name;
    public void fly() {
        System.out.println("Bird::fiy()");
    }
}

public class TestDemo {
    public static void main(String[] args) {

    }
}
