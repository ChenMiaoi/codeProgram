public class DataType {
    public static void main(String[] args) {
        String str = "hello";
        System.out.println(str);
        final int NUM = 10;
    }
    public static void main7(String[] args) {
        boolean flag = true;
    }
    public static void main6(String[] args) {
        byte a = 1;
        System.out.println(Byte.MIN_VALUE);
        System.out.println(Byte.MAX_VALUE);
    }
    /**
     * 注意char类型占两个字节
     * Unicode -- 包含很多字符，比如中文，其他各种语言
     * @param args
     */
    public static void main5(String[] args) {
        char ch = 'c';
        System.out.println(Character.MAX_VALUE);
        System.out.println(Character.MIN_VALUE);
    }
    public static void main4(String[] args) {
        float a = 12.5f;
        System.out.println(Float.MAX_VALUE);
        System.out.println(Float.MIN_VALUE);
    }
    public static void main3(String[] args) {
        double a = 12.5;
        System.out.println(Double.MAX_VALUE);
        System.out.println(Double.MIN_VALUE);
    }
    /**
     *
     * @param args
     */
    public static void main2(String[] args) {
        for (int i = 0; i < args.length; i++) {
            System.out.println(args[i]);
        }
        System.out.println("wuhu");
    }
    public static void main1(String[] args) {
        /*
            1. 整形int -- 4字节
            2. java的标识符：数字、字母、下划线、$，依旧不允许数字开头，不建议以$开头
            3. 长整形long -- 8字节
        */
        int a = 10;
        System.out.println(Integer.MAX_VALUE);
        System.out.println(Integer.MIN_VALUE);

        long b = 10;
        System.out.println("long Max: " + Long.MAX_VALUE);
        System.out.println("long Min: " + Long.MIN_VALUE);
        // System.out.println(a);  //打印且换行
        // System.out.printf("%d\n", a);   //以格式化输出内容
        // System.out.print(a);    //只打印不换行
    }
}
