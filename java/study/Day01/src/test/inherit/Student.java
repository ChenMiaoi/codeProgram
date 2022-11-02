package test.inherit;

public class Student extends Inherit {
    public Student(String name, int height, double score) {
        this.name = name;
        this.height = height;
        this.score = score;
    }

    @Override
    public void rest() {
        System.out.println("回宿舍睡觉!");
    }
    public void study() {
        System.out.println("学习! " + this.name);
    }

    double score;
}
