import java.util.Scanner;

public class Main {
    public static void Work1() {
        System.out.println("a\ta^2\ta^3");
        for (int i = 1; i <= 4; i++) {
            System.out.printf("%d\t%d\t%d\n", i, (int)Math.pow(i, 2), (int)Math.pow(i, 3));
        }
    }

    public static void Work2() {
        int sum = 0;
        for (int i = 1; i < 10; i++) {
            sum += i;
        }
        System.out.println("The 10 sum is: " + sum);
    }

    public static void Work3() {
        double pi = 1;
        int flag = -1;
        for (int i = 1; i < 1000; i++) {
            pi += (1.0 / (i * 2 + 1)) * flag;
            flag *= -1;
        }
        System.out.println("The Pi is:" + (pi * 4));
    }

    // something wrong!
    public static void Work4() {
        int birthSec = 7;
        int deathSec = 13;
        int moveSec = 45;
        double nowAllPeople = 312032486;
        long yeadSec = 365 * 24 * 60 * 60 * 5;
        nowAllPeople += yeadSec * 1.0 / birthSec;
        nowAllPeople -= yeadSec * 1.0 / deathSec;
        nowAllPeople += yeadSec * 1.0 / moveSec;
        System.out.printf("The 5 years after is: %f\nBut the people is int, so is: %d\n", nowAllPeople, (int)nowAllPeople + 1);
    }

    public static void Work5() {
        System.out.print("Enter an integer between 0 and 1000: ");
        Scanner scanner = new Scanner(System.in);
        int num = scanner.nextInt();
        int sumNum = 0;
        int temp = num;
        while (temp != 0) {
            sumNum += temp % 10;
            temp /= 10;
        }
        System.out.println("The sum of all digits in " + num + " is " + sumNum);
    }

    public static void Work6() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the amount of water in kilogram: ");
        double kiloGram = scanner.nextDouble();
        System.out.print("Enter the initial temperature: ");
        double startTemp = scanner.nextDouble();
        System.out.print("Enter the final temperature: ");
        double endTemp = scanner.nextDouble();
        double Q = kiloGram * (endTemp - startTemp) * 4184;
        System.out.print("The energy needed is " + Q);
    }

    public static void Work7() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter speed v: ");
        double v = scanner.nextDouble();
        System.out.print("Enter acceleration a: ");
        double a = scanner.nextDouble();
        double runWayLength = Math.pow(v, 2) / (2 * a);
        System.out.println("The minimun runway length for this airplane is " + runWayLength + " meters");
    }

    public static void Work8() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the amount to be saved for each month: ");
        double monthDollar = scanner.nextDouble();
        System.out.print("Enter the annual interest rate: ");
        double interest = scanner.nextDouble();
        double monthInter = 0.01 * interest / 12;
        System.out.print("Enter the number of months: ");
        int month = scanner.nextInt();
        double sumMoney = monthDollar;
        while (month-- != 0) {
            sumMoney *= (1 + monthInter);
            sumMoney += monthDollar;
        }
        System.out.println("After the 6th month, the account value is " + (sumMoney - monthDollar));
    }

    public static void Work9() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter weight is pounds: ");
        double pounds = scanner.nextDouble();
        double kiloGram = 0.4539237 * pounds;
        System.out.print("Enter hight in inches: ");
        double inches= scanner.nextDouble();
        double height = 0.0254 * inches;
        System.out.println("BMI is " + (kiloGram / Math.pow(height, 2)));
    }

    public static void Work10() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the side: ");
        double side = scanner.nextDouble();
        System.out.println("The area of hexagon is " + (3 * Math.sqrt(3) / 2) * Math.pow(side, 2));
    }

    public static void Work11() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter balance and annual interest rate: ");
        double balance = scanner.nextDouble();
        double rate = scanner.nextDouble();
        System.out.println("The interest is " + balance * (rate / 1200.0));
    }

    public static void Work12() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a, b, c: ");
        double a = scanner.nextDouble();
        double b = scanner.nextDouble();
        double c = scanner.nextDouble();
        double deta = Math.pow(b, 2) - 4 * a * c;
        if (deta == 0) {
            double x = (-b + Math.sqrt(deta)) / (2 * a);
            System.out.println("The equation has one root: " + x);
        }else if (deta > 0) {
            double x1 = (-b + Math.sqrt(deta)) / (2 * a);
            double x2 = (-b - Math.sqrt(deta)) / (2 * a);
            System.out.println("The equation has two root: " + x1 + " and " + x2);
        }else {
            System.out.println("The equation has no realroots");
        }
    }

    public static void Work13() {
        Scanner scanner = new Scanner(System.in);
        int num1 = (int)(Math.random() * 10);
        int num2 = (int)(Math.random() * 10);
        int num3 = (int)(Math.random() * 10);
        while (true) {
            System.out.print("Enter a num to equal the three num's sum: ");
            int sum = scanner.nextInt();
            if (sum == (num1 + num2 + num3)) {
                System.out.println("You win!");
                break;
            } else {
                System.out.println("You should think twice and try again!");
                if (sum > (num1 + num2 + num3)) {
                    System.out.println("Guess Bigger!");
                }else {
                    System.out.println("Guess Lower!");
                }
            }
        }
    }

    public static void Work14() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the first 9 digit of an ISBN as interger: ");
        String check = scanner.next();
        int sum = 0;
        for (int i = 0; i < 9; i++) {
            sum += ((check.charAt(i) - '0') * (i + 1));
        }
        if (sum % 11 == 10) {
            System.out.println("The ISBN-10 number is " + check + "X");
            return;
        }
        System.out.println("The ISBN-10 number is " + check + (sum % 11));
    }

    public static void Work15() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a three-digit inerger: ");
        int num = scanner.nextInt();
        if ((num / 100) == (num % 10)) {
            System.out.println(num + " is a palindrome!");
        }else {
            System.out.println(num + " is not a palindrome!");
        }
    }

    public static void Work16() {
        // scissor - 0, rock - 1, paper - 2
        Scanner scanner = new Scanner(System.in);
        System.out.print("User(scissor(0), rock(1), paper(2)): ");
        int user_done = scanner.nextInt();
        int computer_done = (int)(Math.random() * 3);
        System.out.print("Computer(scissor(0), rock(1), paper(2)): " + computer_done);
        System.out.println("");
        switch (user_done) {
            case 0:
                if (computer_done == 0) {
                    System.out.println("The computer is scissor. You are scissor too. It is a draw");
                }else if (computer_done == 1) {
                    System.out.println("The computer is rock. You are scissor. Computer Win");
                }else {
                    System.out.println("The computer is paper. You are scissor. You Win");
                }
                break;
            case 1:
                if (computer_done == 0) {
                    System.out.println("The computer is scissor. You are rock. You Win");
                }else if (computer_done == 1) {
                    System.out.println("The computer is rock. You are rock. Ti is a draw");
                }else {
                    System.out.println("The computer is paper. You are rock. Computer Win");
                }
                break;
            case 2:
                if (computer_done == 0) {
                    System.out.println("The computer is scissor. You are paper. Computer Win");
                }else if (computer_done == 1) {
                    System.out.println("The computer is rock. You are paper. You Win");
                }else {
                    System.out.println("The computer is paper. You are paper. It is a draw");
                }
                break;
            default:
                System.out.println("Input Error!");
        }
    }

    public static void Work17() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter year(e.g. 2012): ");
        int year = scanner.nextInt();
        System.out.print("Enter month(1~12): ");
        int month = scanner.nextInt();
        System.out.print("Enter the day of the month(1~31): ");
        int day = scanner.nextInt();
        if (month == 1 || month == 2) {
            month += 12;
            year--;
        }
        int h = (day + 26 * (month + 1) / 10 + year % 100 + year % 100 / 4 + Math.abs((year / 100)) / 4 + 5 * Math.abs((year / 100))) % 7;
        switch (h) {
            case 0: System.out.println("Day of the week is Saturday");
                break;
            case 1: System.out.println("Day of the week is Sunday");
                break;
            case 2: System.out.println("Day of the week is Monday");
                break;
            case 3: System.out.println("Day of the week is Tuesday");
                break;
            case 4: System.out.println("Day of the week is Wednesday");
                break;
            case 5: System.out.println("Day of the week is Thursday");
                break;
            case 6: System.out.println("Day of the week is Friday");
                break;
        }
    }

    public static void Work18() {
        Scanner scanner = new Scanner(System.in);
        String[] card = new String[] {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        String[] color = new String[] {"Clubs", "Diamonds", "Hearts", "Spares"};
        System.out.print("Pick a card(Y/N): ");
        char key = scanner.next().charAt(0);
        switch (key) {
            case 'y':
            case 'Y':
                int rand = (int)(Math.random() * 53);
                System.out.println("The card you picked is " + card[rand % 13] + " of " + color[rand % 4]);
                break;
            case 'n':
            case 'N':
                return;
            default:
                System.out.println("Enter a wrong option");
                break;
        }
    }

    public static void Work19() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an integer: ");
        int num = scanner.nextInt();
        System.out.println("Is " + num + " divisible by 5 and 6? " + (num % 5 == 0 && num % 6 == 0));
        System.out.println("Is " + num + " divisible by 5 or 6? " + (num % 5 == 0 || num % 6 == 0));
        System.out.println("Is " + num + " divisible by 5 or 6, but not both? " + ((num % 5 == 0 || num % 6 == 0) && (num % 30 != 0)));
    }

    public static void Work20() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the exchange rate from dollars to RMB: ");
        double rate = scanner.nextDouble();
        System.out.print("Enter 0 to convert dollar to RMB and 1 vice versa: ");
        int option = scanner.nextInt();
        switch (option) {
            case 0:
                System.out.print("Enter dollar amount: ");
                double dollar = scanner.nextDouble();
                System.out.println("$" + dollar + " is " + (dollar * rate) + " Yuan");
                break;
            case 1:
                System.out.print("Enter RMB amount: ");
                double RMB = scanner.nextDouble();
                System.out.println(RMB + " Yuan is $" + (RMB / rate));
                break;
            default:
                System.out.println("Incorrect input");
                break;
        }
    }

    public static void Work21() {
        Scanner scanner = new Scanner(System.in);
        double[] p0 = new double[2];
        double[] p1 = new double[2];
        double[] p2 = new double[2];
        System.out.print("Enter three points for p0, p1, p2: ");
        p0[0] = scanner.nextDouble(); p0[1] = scanner.nextDouble();
        p1[0] = scanner.nextDouble(); p1[1] = scanner.nextDouble();
        p2[0] = scanner.nextDouble(); p2[1] = scanner.nextDouble();
        double dist = (p1[0] - p0[0]) * (p2[1] - p0[1]) - (p2[0] - p0[0]) * (p1[1] - p0[1]);
        if (dist > 0) {
            System.out.printf("(%.1f, %.1f) is on the left side of the line from (%.1f, %.1f) to (%.1f, %.1f)\n", p2[0], p2[1], p0[0], p0[1], p1[0], p1[1]);
        }else if (dist < 0) {
            System.out.printf("(%.1f, %.1f) is on the right side of the line from (%.1f, %.1f) to (%.1f, %.1f)\n", p2[0], p2[1], p0[0], p0[1], p1[0], p1[1]);
        }else {
            System.out.printf("(%.1f, %.1f) is on the line from (%.1f, %.1f) to (%.1f, %.1f)\n", p2[0], p2[1], p0[0], p0[1], p1[0], p1[1]);
        }
    }
    public static void main(String[] args) {
        Work21();
    }
}