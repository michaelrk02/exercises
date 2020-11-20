package main

import (
    "fmt"
)

func merge(arr []int, aLeft, aRight, bLeft, bRight int) {
    size := bRight - aLeft + 1
    temp := make([]int, size)
    base := aLeft

    for i := 0; i < size; i++ {
        if aLeft > aRight {
            temp[i] = arr[bLeft]
            bLeft++
            continue
        }
        if bLeft > bRight {
            temp[i] = arr[aLeft]
            aLeft++
            continue
        }
        if arr[aLeft] < arr[bLeft] {
            temp[i] = arr[aLeft]
            aLeft++
        } else {
            temp[i] = arr[bLeft]
            bLeft++
        }
    }

    for i := 0; i < size; i++ {
        arr[base + i] = temp[i]
    }
}

func mergeSort(arr []int, left, right int) {
    if left >= right {
        return
    }

    middle := (left + right) / 2
    mergeSort(arr, left, middle)
    mergeSort(arr, middle + 1, right)
    merge(arr, left, middle, middle + 1, right)
}

func sort(arr []int) {
    mergeSort(arr, 0, len(arr) - 1)
}

func main() {
    arr := []int{9, 4, 1, 2, 8, 18, 2, 5}
    fmt.Printf("Array: %v\n", arr)
    sort(arr)
    fmt.Printf("Sorted: %v\n", arr)
}

