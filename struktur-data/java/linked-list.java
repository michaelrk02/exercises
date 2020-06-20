package com.github.michaelrk02.datastructures;

import java.util.*;

public class Program {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n;
        System.out.printf("Enter number of elements: ");
        n = scanner.nextInt();

        LinkedList list = new LinkedList();
        for (int i = 0; i < n; i++) {
            int value;
            System.out.printf("Enter value #%d (integer): ", i);
            value = scanner.nextInt();

            list.push(value);
        }

        System.out.printf("Linked list array representation: %s\n", Arrays.toString(list.getArray()));
    }

}

public class ListItem {

    public ListItem previous; // previous node
    public ListItem next; // next node
    public int value; // node value

    public ListItem(ListItem previous, ListItem next, int value) {
        this.previous = previous;
        this.next = next;
        this.value = value;
    }

}

public class LinkedList {

    private ListItem begin; // head
    private ListItem end; // tail
    private int size; // size (cached)

    public LinkedList() {
        this.begin = null;
        this.end = null;
        this.size = 0;
    }

    public int push(int value) {
        if (this.size == 0) {
            this.begin = new ListItem(null, null, value);
            this.end = this.begin;
            this.size = 1;
        } else {
            this.end.next = new ListItem(this.end, null, value);
            this.end = this.end.next;
            this.size++;
        }
        return this.size;
    }

    public int pop() {
        if (this.size > 0) {
            if (this.size == 1) {
                this.begin = null;
                this.end = null;
                this.size = 0;
            } else {
                this.end.previous.next = null;
                this.end = this.end.previous;
                this.size--;
            }
        }
        return this.size;
    }

    public int[] getArray() {
        int[] array = new int[this.size];
        int position = 0;
        ListItem li = this.begin;
        while (li != null) {
            array[position] = li.value;
            position++;
            li = li.next;
        }
        return array;
    }

}
