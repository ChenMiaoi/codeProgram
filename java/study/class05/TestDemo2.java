class Person1 {
    public Person1 Get() {
        return this;
    }
    public void Set(String name, int age) {
        _name = name;
        _age = age;
    }
    private String _name;
    private int _age;
}

public class TestDemo2 {
    public static void main(String[] args) {
        Person1 person = new Person1();
        person.Set("heh", 18);
        person.Get();
    }
}
