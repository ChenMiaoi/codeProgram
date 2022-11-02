import java.util.Random;
import java.util.Scanner;

public class Work {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        Random random = new Random();   //如果在Random中给定了数字，则只有第一次随机
        int randNum = random.nextInt(100);
        System.out.println(randNum);

        while (true) {
            System.out.print("请输入您要猜的数字: ");
            int num = scan.nextInt();
            if (num < randNum) {
                System.out.println("您猜的数字小了！");
            } else if (num > randNum) {
                System.out.println("您猜的数字大了！");
            } else {
                System.out.println("您猜对了: " + num);
                break;
            }
        }
    }
}
