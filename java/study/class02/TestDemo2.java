import java.util.Scanner;

public class TestDemo2 {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        while (scan.hasNextInt()) {
            int num = scan.nextInt();
            System.out.println(num);
        }
    }
    public static void main2(String[] args) {
        Scanner scan = new Scanner(System.in);
        int num = scan.nextInt();
        int sum = 0;
        for (int i = 1; i <= num; i++) {
            int ret = 1;
            for (int j = 1; j <= i; j++) {
                ret *= j;
            }
            sum += ret;
        }
        System.out.println(sum);
        scan.close();
    }
    public static void main1(String[] args) {
        Scanner scan = new Scanner(System.in);
        int num = scan.nextInt();
        while (num <= 200) {
            num++;
            if (num % 15 == 0) {
                System.out.println(num);
                break;
            }
        }
    }
}
