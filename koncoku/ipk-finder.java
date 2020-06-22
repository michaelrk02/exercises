import java.util.*; // Buat `Arrays.*`

public class Program {

    // Entry point
    //

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n;
        System.out.printf("Masukkan banyaknya IPK: ");
        n = scanner.nextInt();

        float[] X = new float[n];
        for (int i = 0; i <= n-1; i++) {

            float ipk;
            System.out.printf("Masukkan IPK ke-%d: ", (i + 1));
            //ipk = scanner.nextFloat(); // comment/uncomment untuk masukin manual

            // comment/uncomment untuk masukin otomatis
            // {{
            ipk = (float)Math.random() * 4.0f; // random [0.0, 1.0) -> faktor = 4
            ipk = Math.round(ipk * 100.0f) / 100.0f; // pembulatan 2 digit di belakang koma
            System.out.printf("%.2f (otomatis)\n", ipk);
            // }}

            X[i] = ipk; // isi elemen ke-i dengan ipk
        }

        sort(X); // urutkan data
        System.out.printf("Data IPK terurut: %s\n", Arrays.toString(X));

        float ipkFind;
        System.out.printf("Cari yang IPK-nya berapa bro? ");
        ipkFind = scanner.nextFloat();

        int result = binarySearch(X, ipkFind); // temukan posisi ipk
        if (result == -1) {
            System.out.println("Sori gaketemu brow :(");
        } else {
            System.out.printf("Ketemu gan, dia di urutan ke-%d\n", (result + 1));
        }

        System.out.println("Semoga bermanfaat :D");
    }

    // MULAI GAPENTING INI -_-
    //

    public static void sort(float[] arr) {
        //int steps = 0;
        if (arr.length > 0) {
            for (int i = 1; i <= arr.length - 1; i++) {
                int j = i;
                while ((j > 0) && (arr[j - 1] > arr[j])) {
                    float tmp = arr[j - 1];
                    arr[j - 1] = arr[j];
                    arr[j] = tmp;
                    j--;
                    //steps++;
                }
            }
        }
        //System.out.printf("Steps: %d\n", steps);
    }

    public static int binarySearch(float[] arr, float v) {
        return internalBinarySearch(arr, v, 0, arr.length - 1);
    }

    private static int internalBinarySearch(float[] arr, float v, int left, int right) {
        if ((left >= right) && (arr[left] != v)) {
            return -1;
        }

        int middle = (left + right) / 2;
        if (arr[middle] > v) {
            return internalBinarySearch(arr, v, left, middle - 1);
        } else if (arr[middle] < v) {
            return internalBinarySearch(arr, v, middle + 1, right);
        }
        return middle;
    }

}
