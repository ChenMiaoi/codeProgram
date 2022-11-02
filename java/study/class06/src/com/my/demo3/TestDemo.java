package com.my.demo3;

class Animal  {
    String name;

    public Animal(String name) {
        this.name = name;
        System.out.println("Animal(String)");
    }
}

class Cat extends Animal {
    String name;
    public Cat(String name) {
        super(name);
        System.out.println("Cat(String)");
    }
    public void eat() {
        System.out.println("Cat::eat()");
    }
}

class Bird extends Animal {
    String name;

    public Bird(String name, String name1) {
        super(name);
        this.name = name1;
        System.out.println("Bird(String)");
    }
    public void fly() {
        System.out.println("Bird::fly()");
    }
}

public class TestDemo {
    public static void main(String[] args) {

    }
}
