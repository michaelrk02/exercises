package latihan.dll;

import java.util.*;

public class Program {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n;
        System.out.printf("Masukkan jumlah data: ");
        n = scanner.nextInt();
        scanner.nextLine();

        List list = new List();

        for (int i = 0; i < n; i++) {
            String nama;
            System.out.printf("Masukkan nama #%d: ", i);
            nama = scanner.nextLine();

            String nomorHp;
            System.out.printf("Masukkan nomor HP #%d: ", i);
            nomorHp = scanner.nextLine();

            list.append(nama, nomorHp);
        }

        list.print();

        String cariNama;
        System.out.printf("Masukkan nama yg akan dicari: ");
        cariNama = scanner.nextLine();

        Node result = list.binarySearch(cariNama);
        if (result == null) {
            System.out.println("Tidak ditemukan");
        } else {
            System.out.printf("Ada pada indeks ke-%d\n", list.getNodeIndex(result));

            String gantiNama;
            System.out.printf("Ganti dengan: ");
            gantiNama = scanner.nextLine();

            result.nama = gantiNama;

            System.out.println("Data terbaru:");
            list.print();
        }
    }

}

public class List {
    public Node first;
    public Node last;
    public int count;

    public void append(String nama, String nomorHp) {
        if (this.count == 0) {
            Node newNode = new Node(null, null, nama, nomorHp);

            this.first = newNode;
            this.last = newNode;
        } else {
            Node newNode = new Node(this.last, null, nama, nomorHp);

            this.last.next = newNode;
            this.last = newNode;
        }
        this.count++;
    }

    public Node binarySearch(String nama) {
        return internalBinarySearch(nama, 0, count - 1);
    }

    public void print() {
        System.out.println("List nama & nomor telepon:");
        for (Node iterator = this.first; iterator != null; iterator = iterator.next) {
            System.out.printf("%s (%s)\n", iterator.nama, iterator.nomorHp);
        }
    }

    public int getNodeIndex(Node node) {
        int index = 0;
        for (Node iterator = this.first; iterator != null; iterator = iterator.next) {
            if (iterator == node) {
                return index;
            }
            index++;
        }
        return -1;
    }

    public Node getIndexNode(int index) {
        int curr = 0;
        for (Node iterator = this.first; iterator != null; iterator = iterator.next) {
            if (curr == index) {
                return iterator;
            }
            curr++;
        }
        return null;
    }

    private Node internalBinarySearch(String nama, int left, int right) {
        if ((left == right) && (this.getIndexNode(left).nama.compareToIgnoreCase(nama) != 0)) {
            return null;
        }

        int middle = (left + right) / 2;

        Node centerNode = this.getIndexNode(middle);
        if (centerNode.nama.compareToIgnoreCase(nama) > 0) {
            return internalBinarySearch(nama, left, middle - 1);
        } else if (centerNode.nama.compareToIgnoreCase(nama) < 0) {
            return internalBinarySearch(nama, middle + 1, right);
        }

        return centerNode;
    }
}

public class Node {
    public Node prev;
    public Node next;
    public String nama;
    public String nomorHp;

    public Node(Node prev, Node next, String nama, String nomorHp) {
        this.prev = prev;
        this.next = next;
        this.nama = nama;
        this.nomorHp = nomorHp;
    }
}
