import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

public class Main {
    public static void Test1() {
        String str1 = "aabb";       //不可变字符序列
        StringBuilder str2 = null;  //可变字符序列，线程不安全，效率高
        StringBuffer str3 = null;   //可变字符序列，线程安全，效率低

        str2 = new StringBuilder("Hello");
        str2.append(123);
        str2.append(456);
        System.out.println(str2);
        str2.append("aa").append("bb");
        System.out.println(str2);

        String str = "";
        long num1 = Runtime.getRuntime().freeMemory();
        long time1 = System.currentTimeMillis();
        for (int i = 0; i < 5000; i++) {
            str += i;
        }
        long num2 = Runtime.getRuntime().freeMemory();
        long time2 = System.currentTimeMillis();
        System.out.println("String占用内存: " + (num1 - num2));
        System.out.println("String占用时间: " + (time2 - time1));

        long num3 = Runtime.getRuntime().freeMemory();
        long time3 = System.currentTimeMillis();
        StringBuilder str4 = new StringBuilder("");
        for (int i = 0; i < 5000; i++) {
            str4.append(i);
        }
        long num4 = Runtime.getRuntime().freeMemory();
        long time4 = System.currentTimeMillis();
        System.out.println("StringBuilder占用内存: " + (num3 - num4));
        System.out.println("StringBuilder占用时间: " + (time4 - time3));
    }

    public static void Test2() throws ParseException {
        /*
        * 时间处理类
        * Date
        * DateFormat -> SimpleDateFormat
        * Calendar
        * */
        Date d1 = new Date();       //如果没有传参，默认是当前时刻
        System.out.println(d1);
        System.out.println(d1.getTime());

        //使用SimpleDateFormat的格式为: yyyy-MM-dd hh:mm:ss
        SimpleDateFormat s1 = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");

        //将字符串转化为时间对象 需要抛出ParseException异常
        Date d2 = s1.parse("1971-12-4 12:32:51");
        System.out.println(d2);
        //将时间对象转化为字符串
        String dayTime = s1.format(new Date());
        System.out.println(s1);
        System.out.println(dayTime);

        //Calendar是一个抽象类，GregorianCalendar中的月份表示，一月是从0开始的
        GregorianCalendar calendar = new GregorianCalendar(2999, 10, 9, 22, 10, 50);
        // 获得日期
        int year = calendar.get(Calendar.YEAR);
        int month = calendar.get(Calendar.MONTH);
        int day = calendar.get(Calendar.DAY_OF_MONTH);
        int day2 = calendar.get(Calendar.DATE);
        int date = calendar.get(Calendar.DAY_OF_WEEK);
        //设置日期
        calendar.set(Calendar.YEAR, 2999);
        //日期计算
        calendar.add(Calendar.YEAR, -1);
        //日历对象和时间对象转化
        Date d = calendar.getTime();

        GregorianCalendar calendar1 = new GregorianCalendar();
        calendar1.setTime(new Date());
    }

    public static void Test3() throws IOException {
        /*
        * File 类
        * */
        File fp = new File("./test.txt");
        //创建文件 --> 是以创建对象给的路径作为基准
        fp.createNewFile();
        System.out.println("File是否存在: " + fp.exists());
        System.out.println("File是否是目录: " + fp.isDirectory());
        System.out.println("File是否是文件: " + fp.isFile());
        System.out.println("File最后修改时间: " + new Date(fp.lastModified()));
        System.out.println("File的大小: " + fp.length());
        System.out.println("File的文件名: " + fp.getName());
        System.out.println("File的文件路径: " + fp.getPath());
    }
    public static void main(String[] args) throws ParseException, IOException {
        Test3();
    }
}