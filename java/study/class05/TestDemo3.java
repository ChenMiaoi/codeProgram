class Person3 {
    public Person3() {
        System.out.println("Person3(init)");
    }
    public Person3(String name, int age) {
        this.name = name;
        this.age = age;
    }
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "Person3{" +
                "name='" + name + '\'' +
                ", age=" + age +
                '}';
    }
    private String name;
    private int age;
}
public class TestDemo3 {
    public static void main(String[] args) {
        Person3 person1 = new Person3("helo", 18);
        System.out.println(person1);
    }
    public static void main1(String[] args) {
        Person3 person = new Person3();
        Person3 person1 = new Person3("helo", 18);
    }
}
