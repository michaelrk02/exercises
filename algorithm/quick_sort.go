package main

import (
    "fmt"
)

func partition(arr []int, left, right int) int {
    pivot := arr[(left + right) / 2]
    i := left
    j := right
    for {
        for arr[i] < pivot {
            i++
        }
        for arr[j] > pivot {
            j--
        }
        if i >= j {
            return j
        }
        temp := arr[i]
        arr[i] = arr[j]
        arr[j] = temp
    }
    return -1
}

func quickSort(arr []int, left, right int) {
    if left >= right {
        return
    }

    p := partition(arr, left, right)
    quickSort(arr, left, p)
    quickSort(arr, p + 1, right)
}

func sort(arr []int) {
    quickSort(arr, 0, len(arr) - 1)
}

func main() {
    arr := []int{2, 5, 7, 4, 6, 1, 3, 8, 9}
    fmt.Printf("Array: %v\n", arr)
    sort(arr)
    fmt.Printf("Sorted: %v\n", arr)
}

