package simulasi.terminal;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Scanner;

public class Program {

    public static int maxQ1 = 10;
    public static int maxQ2 = 10;
    public static String path = "terminal.txt";

    public static void main(String[] args) {
        try {
            Scanner input = new Scanner(new File(path));

            AntrianBus Q1 = new AntrianBus(maxQ1);
            AntrianBus Q2 = new AntrianBus(maxQ2);

            while (input.hasNext()) {
                String namaBus = input.next();
                int jumlahPenumpang = input.nextInt();
                int jalur = input.nextInt();

                if (jalur == 1) {
                    Q1.tambahBus(namaBus, jumlahPenumpang);
                } else if (jalur == 2) {
                    Q2.tambahBus(namaBus, jumlahPenumpang);
                }
            }

            System.out.printf("* Jalur 1: ");
            Q1.print();

            System.out.printf("* Jalur 2: ");
            Q2.print();
        } catch (FileNotFoundException ex) {
            System.out.println("File tidak ditemukan!");
        }
    }

    public static String fixString(String str) {
        if ((str.charAt(0) == '"') || (str.charAt(0) == '\'')) {
            return str.substring(1, str.length() - 2);
        }
        return str;
    }

}

public class AntrianBus {

    public LinkedList<Bus> queue;
    public int max;

    public AntrianBus(int max) {
        this.queue = new LinkedList<Bus>();
        this.max = max;
    }

    public void tambahBus(String nama, int jumlahPenumpang) {
        this.cekNamaBus(nama);
        this.cekKapasitas();
        this.queue.addFirst(new Bus(nama, jumlahPenumpang));
    }

    public void cekNamaBus(String nama) {
        if (this.queue.size() > 0) {
            if (this.queue.getLast().nama.compareTo(nama) == 0) {
                this.queue.removeLast();
            }
        }
    }

    public void cekKapasitas() {
        if (this.queue.size() >= max) {
            this.queue.removeLast();
        }
    }

    public void print() {
        System.out.printf("ANTRIAN( ");
        int totalPenumpang = 0;
        ListIterator<Bus> iterator = this.queue.listIterator(0);
        Bus bus = null;
        while (iterator.hasNext()) {
            bus = iterator.next();
            totalPenumpang += bus.jumlahPenumpang;
            System.out.printf("%s(%d) ", bus.nama, bus.jumlahPenumpang);
        }
        System.out.printf(") [%d penumpang]\n", totalPenumpang);
    }

}

public class Bus {

    public String nama;
    public int jumlahPenumpang;

    public Bus(String nama, int jumlahPenumpang) {
        this.nama = nama;
        this.jumlahPenumpang = jumlahPenumpang;
    }

}
