import java.util.Arrays;
class Sort {
    public void selectionSort(int[] array) {
        for (int i = 0; i < array.length; i++) {
            int minIndex = i;
            for (int j = i + 1; j < array.length; j++) {
                if (array[j] < array[minIndex]) {
                    minIndex = j;
                }
            }
            if (i != minIndex) {
                int temp = array[i];
                array[i] = array[minIndex];
                array[minIndex] = temp;
            }
        }
    }
    public void insertSort(int[] array) {
        for (int i = 1; i < array.length; i++) {
            int insertValue = array[i];
            int j = i - 1;
            for (; (j >= 0) && (insertValue < array[j]); j--) {
                array[j + 1] = array[j];
            }
            array[j + 1] = insertValue;
        }
    }
}
public class Main {
    public static void main(String[] args) {
        int[] array = new int[] {3, 4, 2, 1, 5, 6, 7, 8, 30, 50, 133, 24, 5, -4, 7, 0};
        Sort s = new Sort();
        // s.selectionSort(array);
        s.insertSort(array);
        System.out.println(Arrays.toString(array));
    }
}