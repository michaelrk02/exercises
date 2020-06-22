package latihan.ll;

import java.util.*;

public class Program {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n;
        System.out.printf("Masukkan jumlah angka: ");
        n = scanner.nextInt();

        List list = new List();

        for (int i = 0; i < n; i++) {
            int value;
            System.out.printf("Masukkan angka ke-%d: ", i);
            value = scanner.nextInt();

            list.append(value);
        }

        list.multiplyBy3Each();

        System.out.printf("List sementara: %s\n", list.toString());

        int deleteNumber;
        System.out.printf("Hapus angka: ");
        deleteNumber = scanner.nextInt();

        list.findAndDelete(deleteNumber);

        System.out.printf("List sekarang: %s\n", list.toString());
    }

}

public class List {
    Node first;
    Node last;
    int count;

    public List() {
        this.first = null;
        this.last = null;
        this.count = 0;
    }

    public void append(int value) {
        if (this.count == 0) {
            Node newNode = new Node(null, value);

            this.first = newNode;
            this.last = newNode;
        } else {
            Node newNode = new Node(null, value);

            this.last.next = newNode;
            this.last = newNode;
        }
        this.count++;
    }

    public void multiplyBy3Each() {
        for (Node iterator = this.first; iterator != null; iterator = iterator.next) {
            iterator.value = iterator.value * 3;
        }
    }

    public void findAndDelete(int target) {
        for (Node iterator = this.first; iterator != null; iterator = iterator.next) {
            // cek jika elemen yang akan dihapus merupakan elemen pertama
            if ((iterator == this.first) && (iterator.value == target)) {
                this.first = iterator.next;

                this.count--;
                break; // wes mandeg. ngisor ki rasah digagas neh
            }

            // elemen/node yang akan dihapus: iterator.next
            // cek jika elemen yang akan dihapus merupakan elemen yang kedua dan seterusnya
            if ((iterator.next != null) && (iterator.next.value == target)) {
                // cek jika elemen yang akan dihapus merupakan elemen yang terakhir
                if (iterator.next == this.last) {
                    iterator.next = null;
                    this.last = iterator;
                } else {
                    iterator.next = iterator.next.next;
                }

                this.count--;
                break;
            }
        }
    }

    public String toString() {
        int[] array = new int[this.count];
        int index = 0;
        for (Node iterator = this.first; iterator != null; iterator = iterator.next) {
            array[index] = iterator.value;
            index++;
        }

        return Arrays.toString(array);
    }
}

public class Node {
    public Node next;
    public int value;

    public Node(Node next, int value) {
        this.next = next;
        this.value = value;
    }
}
