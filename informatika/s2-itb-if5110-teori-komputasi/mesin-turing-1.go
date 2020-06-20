// Mesin Turing (bagian 1)
// Deskripsi PR: Rancanglah mesin Turing yang menerima bahasa dengan string bit '0' dan '1' yang sama banyaknya
// Link: http://informatika.stei.itb.ac.id/~rinaldi.munir/TeoriKomputasi/2015-2016/IF5110%20-%20Mesin%20Turing%20(Bagian%201)%20-%202015.pptx
package main

import (
    "fmt"
    "math/rand"
    "time"
)

func validate(str string) bool {
    input := []byte(str)
    state := 0
    i := 0
    for {
        if i > len(input) - 1 {
            break
        }
        sym := input[i]
        if state == 0 {
            if sym == '0' {
                state = 1
                input[i] = 'X'
                i++
                continue
            }
            if sym == '1' {
                state = 3
                input[i] = 'Y'
                i++
                continue
            }
            if sym == 'X' || sym == 'Y' {
                i++
                continue
            }
        }
        if state == 1 {
            if sym == '0' || sym == 'X' || sym == 'Y' {
                i++
                continue
            }
            if sym == '1' {
                state = 2
                input[i] = 'Y'
                i--
                continue
            }
        }
        if state == 2 {
            if sym == '0' || sym == '1' || sym == 'Y' {
                i--
                continue
            }
            if sym == 'X' {
                i++
                state = 0
                continue
            }
        }
        if state == 3 {
            if sym == '1' || sym == 'X' || sym == 'Y' {
                i++
                continue
            }
            if sym == '0' {
                state = 4
                input[i] = 'X'
                i--
                continue
            }
        }
        if state == 4 {
            if sym == '0' || sym == '1' || sym == 'X' {
                i--
                continue
            }
            if sym == 'Y' {
                i++
                state = 0
                continue
            }
        }
    }

    return state == 0
}

func shuffle(s []byte) []byte {
    length := len(s)
    mapping := make([]int, length)
    available := make([]int, length)
    shuffled := make([]byte, length)
    for i := 0; i < length; i++ {
        available[i] = i
    }
    for i := 0; i < length; i++ {
        index := rand.Intn(len(available))
        mapping[i] = available[index]
        available = append(available[0:index], available[index + 1:]...)
    }
    for i := 0; i < length; i++ {
        shuffled[i] = s[mapping[i]]
    }
    return shuffled
}

func main() {
    rand.Seed(time.Now().Unix())
    for {
        var expectCh string
        fmt.Printf("Expect truthness? (Y/N) ")
        fmt.Scanf("%s", &expectCh)

        var length int
        fmt.Printf("Random string length: ")
        fmt.Scanf("%d", &length)

        expect := expectCh == "Y" || expectCh == "y"
        if expect && length % 2 == 1 {
            fmt.Printf("String length must be an even number!\n")
            continue
        }

        input := make([]byte, length)
        count0 := length / 2
        if !expect {
            count0 = rand.Intn(length + 1)
        }
        for i := 0; i < count0; i++ {
            input[i] = '0'
        }
        for i := count0; i < length; i++ {
            input[i] = '1'
        }
        input = shuffle(input)

        str := string(input)
        fmt.Printf("String: %s\n", str)
        fmt.Printf("Result: %v\n", validate(str))
    }
}
