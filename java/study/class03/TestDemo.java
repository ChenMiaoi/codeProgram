import java.util.Scanner;

/**
 * public static 返回值 方法名
 * public static：因为当前所有的方法，写完之后，会在main方法中调用
 * 因为main方法是public static的
 *
 * 返回值：可有可无，看自身需求
 */
public class TestDemo {
    public static int sum(int num1, int num2) {
        return num1 + num2;
    }
    public static double sum(double num1, double num2) {
        return num1 + num2;
    }
    public static void main(String[] args) {
        int n1 = 10;
        int n2 = 20;
        System.out.println(sum(n1, n2));

        double n3 = 1.02;
        double n4 = 2.15;
        System.out.println(sum(n3, n4));
    }
    public static int maxNum(int num1, int num2) {
        return num1 > num2 ? num1 : num2;
    }
    public static int threeMaxNum(int num1, int num2, int num3) {
        return (num1 > num2 ? num1 : num2) > num3 ? (num1 > num2 ? num1 : num2) : num3;
    }
    public static void main1(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n1 = scanner.nextInt();
        int n2 = scanner.nextInt();
        int ret = maxNum(n1, n2);
        System.out.println(ret);
    }
}
