// Extension of GaussianElimination.cpp
package main

import (
    "fmt"
)

type Vector struct {
    Dim int
    Data []float32
}

func (lhs Vector) MulScalar(s float32) Vector {
    for i := 0; i < lhs.Dim; i++ {
        lhs.Data[i] *= s
    }
    return lhs
}

func (lhs Vector) Add(rhs Vector) Vector {
    for i := 0; i < lhs.Dim; i++ {
        lhs.Data[i] += rhs.Data[i]
    }
    return lhs
}

type Matrix struct {
    Rows, Cols int
    Data [][]float32
}

func (m *Matrix) Row(n int) Vector {
    var v Vector
    v.Dim = m.Cols
    v.Data = make([]float32, m.Cols)
    copy(v.Data, m.Data[n])
    return v
}

func (m *Matrix) Print() {
    for i := 0; i < m.Rows; i++ {
        fmt.Printf("[")
        for j := 0; j < m.Cols; j++ {
            fmt.Printf("%.2f", m.Data[i][j] + 0.0)
            if j < m.Cols - 1 {
                fmt.Printf(", ")
            }
        }
        fmt.Printf("]\n")
    }
}

func main() {
    var eq Matrix

    var n int
    for {
        fmt.Printf("Linear equation problems (>1): ")
        fmt.Scanf("%d", &n)
        if n > 1 {
            break
        }
    }

    eq.Rows = n
    eq.Cols = n + 1
    eq.Data = make([][]float32, eq.Rows)
    for i := 0; i < eq.Rows; i++ {
        eq.Data[i] = make([]float32, eq.Cols)

        fmt.Printf("E%d (L... R): ", i + 1)
        for j := 0; j < eq.Cols; j++ {
            fmt.Scanf("%f", &eq.Data[i][j])
        }
    }

    fmt.Println("MATRIX REPRESENTATION:")
    eq.Print()

    // row echelon form construction
    for i := 1; i < eq.Rows; i++ {
        upperLeftNz := eq.Data[i - 1][i - 1]
        for j := i; j < eq.Rows; j++ {
            leftNz := eq.Data[j][i - 1]
            factor := -leftNz / upperLeftNz

            upperRow := eq.Row(i - 1)
            upperRow = upperRow.MulScalar(factor)

            eq.Data[j] = eq.Row(j).Add(upperRow).Data
        }
    }

    fmt.Println("ROW ECHELON FORM:")
    eq.Print()

    // left-hand diagonal matrix construction
    for i := eq.Rows - 2; i >= 0; i-- {
        lowerRightNz := eq.Data[i + 1][i + 1]
        for j := i; j >= 0; j-- {
            rightNz := eq.Data[j][i + 1]
            factor := -rightNz / lowerRightNz

            lowerRow := eq.Row(i + 1)
            lowerRow = lowerRow.MulScalar(factor)

            eq.Data[j] = eq.Row(j).Add(lowerRow).Data
        }
    }

    fmt.Println("LEFT-HAND DIAGONAL FORM:")
    eq.Print()

    // left-hand identity matrix construction
    for i := 0; i < eq.Rows; i++ {
        eq.Data[i] = eq.Row(i).MulScalar(1.0 / eq.Data[i][i]).Data
    }

    fmt.Println("LEFT-HAND IDENTITY FORM:")
    eq.Print()

    // print solutions
    fmt.Println("SOLUTIONS")
    for i := 0; i < eq.Rows; i++ {
        fmt.Printf("X%d: %.2f\n", i + 1, eq.Data[i][eq.Cols - 1])
    }
}
