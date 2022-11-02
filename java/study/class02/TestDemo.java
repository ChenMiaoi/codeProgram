import java.util.Scanner;

public class TestDemo {
    public static void main(String[] args) {
        int a = 10;
        //不能做switch参数的： long、float、double、boolean
        //能做的：整数、字符、枚举、字符串
        switch (a) {
            case 1:
                System.out.println("1");
                break;
            case 2:
                System.out.println("2");
                break;
            default:
                break;
        }
    }
    public static void main5(String[] args) {
        Scanner scan = new Scanner(System.in);
        while (scan.hasNext()) {
            int year = scan.nextInt();
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                System.out.println(year + " is leap year!");
            } else {
                System.out.println("This is not!");
            }
        }
    }
    public static void main4(String[] args) {
        int a = 10;
        if (a == 10) {
            System.out.println("hello");
        } else {
            System.out.println("hh");
        }
    }
    public static void main3(String[] args) {
        Scanner scan = new Scanner(System.in);
        int a = scan.nextInt();
        System.out.println(a);
        //注意，nextInt和nextLine不会放在一起使用
        //next以空格或回车作为结束标志，而nextLine以回车作为标志

        String str = scan.next();
        System.out.println(str);
    }
    public static void main2(String[] args) {
        System.out.println(10 % 3);
        System.out.println(-10 % 3);
        System.out.println(10 % -3);
        System.out.println(-10 % -3);
    }

    public static void main1(String[] args) {
        System.out.println(5 / 2);
        System.out.println(5.0 / 2);
        System.out.println((float) 5 / 2);
        System.out.println((float) (5.0 / 2));
    }
}
