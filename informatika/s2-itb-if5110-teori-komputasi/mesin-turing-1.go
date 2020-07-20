// Mesin Turing (bagian 1)
// Deskripsi PR: Rancanglah mesin Turing yang menerima bahasa dengan string bit '0' dan '1' yang sama banyaknya
// Link: http://informatika.stei.itb.ac.id/~rinaldi.munir/TeoriKomputasi/2015-2016/IF5110%20-%20Mesin%20Turing%20(Bagian%201)%20-%202015.pptx
package main

import (
    "fmt"
    "github.com/michaelrk02/automata"
)

func main() {
    tm := automata.NewTuringMachine(7, 0, 5, 6)

    tm.States[0] = func(token byte) (int, byte, automata.TMHeadDir) {
        switch token {
        case 'X':
            return 0, 'X', automata.TMHeadDirRight
        case 'Y':
            return 0, 'Y', automata.TMHeadDirRight
        case '0':
            return 1, 'X', automata.TMHeadDirRight
        case '1':
            return 3, 'Y', automata.TMHeadDirRight
        case 0x00:
            return 5, 0x00, automata.TMHeadDirRight
        }
        return 6, token, automata.TMHeadDirRight
    }

    tm.States[1] = func(token byte) (int, byte, automata.TMHeadDir) {
        switch token {
        case 'X':
            return 1, 'X', automata.TMHeadDirRight
        case 'Y':
            return 1, 'Y', automata.TMHeadDirRight
        case '0':
            return 1, '0', automata.TMHeadDirRight
        case '1':
            return 2, 'Y', automata.TMHeadDirLeft
        }
        return 6, token, automata.TMHeadDirRight
    }

    tm.States[2] = func(token byte) (int, byte, automata.TMHeadDir) {
        switch token {
        case '0':
            return 2, '0', automata.TMHeadDirLeft
        case '1':
            return 2, '1', automata.TMHeadDirLeft
        case 'X':
            return 0, 'X', automata.TMHeadDirRight
        case 'Y':
            return 2, 'Y', automata.TMHeadDirLeft
        }
        return 6, token, automata.TMHeadDirRight
    }

    tm.States[3] = func(token byte) (int, byte, automata.TMHeadDir) {
        switch token {
        case 'X':
            return 3, 'X', automata.TMHeadDirRight
        case 'Y':
            return 3, 'Y', automata.TMHeadDirRight
        case '0':
            return 4, 'X', automata.TMHeadDirLeft
        case '1':
            return 3, '1', automata.TMHeadDirRight
        }
        return 6, token, automata.TMHeadDirRight
    }

    tm.States[4] = func(token byte) (int, byte, automata.TMHeadDir) {
        switch token {
        case '0':
            return 4, '0', automata.TMHeadDirLeft
        case '1':
            return 4, '1', automata.TMHeadDirLeft
        case 'X':
            return 4, 'X', automata.TMHeadDirLeft
        case 'Y':
            return 0, 'Y', automata.TMHeadDirRight
        }
        return 6, token, automata.TMHeadDirRight
    }

    tm.States[5] = func(token byte) (int, byte, automata.TMHeadDir) {
        return 5, token, automata.TMHeadDirRight
    }

    tm.States[6] = func(token byte) (int, byte, automata.TMHeadDir) {
        return 6, token, automata.TMHeadDirRight
    }

    for true {
        var s string
        fmt.Printf("input: ")
        fmt.Scanf("%s", &s)

        fmt.Printf("Accepted: %v\n", tm.Accepts(s))
    }
}

