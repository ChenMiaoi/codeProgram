import java.lang.reflect.Array;
import java.util.Arrays;

public class TestDemo {
    public static int maxNum(int[] array) {
        int max = array[0];
        for (int i = 0; i < array.length; i++) {
            if (max < array[i]) {
                max = array[i];
            }
        }
        return max;
    }
    public static void main(String[] args) {
        int[] array = {12, 2, 18, 24, 76, 13};
        System.out.println(maxNum(array));
    }
    public static void main8(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7};
        int[] ret1 = Arrays.copyOf(array, array.length);
        System.out.println(Arrays.toString(ret1));

        int[] ret2 = new int[array.length];
        System.arraycopy(array, 0, ret2, 0, array.length);
        System.out.println(Arrays.toString(ret2));

        int[] ret3 = array.clone();
        System.out.println(Arrays.toString(ret3));
    }
    public static String myToString(int[] array) {
        if (array.length == 0) {
            return "[]";
        }
        if (array == null) {
            return null;
        }
        int len = array.length;
        String str = "[";
        for (int i = 0; i < len; i++) {
            str += array[i];
            if (i < len - 1) {
                str += ", ";
            }
        }
        str += "]";
        return str;
    }

    public static void main7(String[] args) {
        int[] arr = {1, 2, 3, 4};
        String str = myToString(arr);
        System.out.println(str);
    }
    public static void main6(String[] args) {
        int[] array = {85, 2, 1, 6, 564, 456, 144, 121};
        Arrays.sort(array);
        System.out.println(Arrays.toString(array));
    }
    public static void main5(String[] args) {
        int[] array = null; //array引用的是一个空对象
    }
    public static void main4(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        String ret = Arrays.toString(array);
        System.out.println(ret);
    }
    public static void printArray(int[] array) {
        for (int val : array) {
            System.out.print(val + " ");
        }
        System.out.println();
    }
    public static void main3(String[] args) {
        int[] array = {1, 2, 3, 4};
        printArray(array);
    }
    public static void main2(String[] args) {
        int[] array = {1, 2, 3, 4};
        int len = array.length;
        System.out.println(len);
        for (int i = 0; i < len; i++) {
            System.out.println(array[i]);
        }
        System.out.println("======");
        for (int val : array) {
            System.out.println(val);
        }
    }
    //在java中，栈上的地址是取不到的
    //堆区的地址是真实的地址经过处理的，通过哈希映射
    public static void main1(String[] args) {
        int[] array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        //java的数组在堆上建立
        int[] array2 = new int[]{1, 2, 3, 4};
        int[] array3 = new int[4];
    }
}
