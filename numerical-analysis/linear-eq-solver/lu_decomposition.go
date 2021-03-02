package main

import (
    "fmt"
)

type vector []float64
type matrix []vector

func newMatrix(r, c int, initial float64) matrix {
    m := make(matrix, r)
    for i := 0; i < r; i++ {
        m[i] = make(vector, c)
        for j := 0; j < c; j++ {
            m[i][j] = initial
        }
    }
    return m
}

func newIdentity(n int) matrix {
    m := newMatrix(n, n, 0.0)
    for i := 0; i < n; i++ {
        m[i][i] = 1.0
    }
    return m
}

func (m matrix) copyFrom(input matrix) {
    for i := range input {
        copy(m[i], input[i])
    }
}

func (v vector) mulScalar(s float64) vector {
    r := make(vector, len(v))
    for i := range v {
        r[i] = s * v[i]
    }
    return r
}

func (v1 vector) addVector(v2 vector) vector {
    if len(v1) != len(v2) {
        panic("incompatible vector sizes")
    }

    v := make(vector, len(v1))
    for i := range v1 {
        v[i] = v1[i] + v2[i]
    }
    return v
}

func decompose(input matrix) (matrix, matrix) {
    lower := newIdentity(len(input))

    upper := newMatrix(len(input), len(input), 0.0)
    upper.copyFrom(input)
    for i := range upper {
        for j := i + 1; j < len(upper); j++ {
            factor := upper[j][i] / upper[i][i]
            lower[j][i] = factor
            upper[j] = upper[j].addVector(upper[i].mulScalar(-factor))
        }
    }

    return lower, upper
}

func backwardSub(m matrix, v vector) vector {
    r := make(vector, len(v))
    for i := len(v) - 1; i >= 0; i-- {
        sigma := 0.0
        for j := len(v) - 1; j > i; j-- {
            sigma = sigma + m[i][j] * r[j]
        }
        r[i] = (v[i] - sigma) / m[i][i]
    }
    return r
}

func forwardSub(m matrix, v vector) vector {
    r := make(vector, len(v))
    for i := 0; i < len(v); i++ {
        sigma := 0.0
        for j := 0; j < i; j++ {
            sigma = sigma + m[i][j] * r[j]
        }
        r[i] = (v[i] - sigma) / m[i][i]
    }
    return r
}

// Ax = b
//
// if A = LU then
// LUx = b
//
// if Ux = y then
// Ly = b
func solve(l, u matrix, b vector) vector {
    y := forwardSub(l, b)
    return backwardSub(u, y)
}

func main() {
    var n int
    fmt.Printf("Enter number of variables: ")
    fmt.Scanf("%d", &n)

    left := newMatrix(n, n, 0.0)
    right := make(vector, n)
    fmt.Printf("Enter %d numbers each line to represent %d coefficients and 1 constant\n", n + 1, n)
    for i := 0; i < n; i++ {
        fmt.Printf("R%d: ", i + 1)
        for j := 0; j < n + 1; j++ {
            if j == n {
                fmt.Scanf("%f", &right[i])
            } else {
                fmt.Scanf("%f", &left[i][j])
            }
        }
    }

    fmt.Println("Decomposing ...")
    l, u := decompose(left)

    fmt.Println("L matrix:")
    for i := range l {
        fmt.Printf("%v\n", l[i])
    }

    fmt.Println("U matrix:")
    for i := range u {
        fmt.Printf("%v\n", u[i])
    }

    fmt.Println("Solving ...")
    r := solve(l, u, right)
    fmt.Printf("Solution: %v\n", r)
}

