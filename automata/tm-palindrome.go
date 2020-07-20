package main

import (
    "fmt"
    "github.com/michaelrk02/automata"
)

func main() {
    tm := automata.NewTuringMachine(9, 0, 7, 8)

    tm.States[0] = func(token byte) (int, byte, automata.TMHeadDir) {
        if token == '0' {
            return 1, 'X', automata.TMHeadDirRight
        }
        if token == '1' {
            return 4, 'Y', automata.TMHeadDirRight
        }
        if (token == 'X') || (token == 'Y') {
            return 7, token, automata.TMHeadDirRight
        }
        return 8, token, automata.TMHeadDirRight
    }

    tm.States[1] = func(token byte) (int, byte, automata.TMHeadDir) {
        if (token == '0') || (token == '1') {
            return 1, token, automata.TMHeadDirRight
        }
        if (token == 'X') || (token == 'Y') || (token == 0x00) {
            return 2, token, automata.TMHeadDirLeft
        }
        return 8, token, automata.TMHeadDirRight
    }

    tm.States[2] = func(token byte) (int, byte, automata.TMHeadDir) {
        if token == '0' {
            return 3, 'X', automata.TMHeadDirLeft
        }
        if (token == 'X') || (token == 'Y') {
            return 7, token, automata.TMHeadDirRight
        }
        return 8, token, automata.TMHeadDirRight
    }

    tm.States[3] = func(token byte) (int, byte, automata.TMHeadDir) {
        if (token == '0') || (token == '1') {
            return 3, token, automata.TMHeadDirLeft
        }
        if (token == 'X') || (token == 'Y') || (token == 0x00) {
            return 0, token, automata.TMHeadDirRight
        }
        return 8, token, automata.TMHeadDirRight
    }

    tm.States[4] = func(token byte) (int, byte, automata.TMHeadDir) {
        if (token == '0') || (token == '1') {
            return 4, token, automata.TMHeadDirRight
        }
        if (token == 'X') || (token == 'Y') || (token == 0x00) {
            return 5, token, automata.TMHeadDirLeft
        }
        return 8, token, automata.TMHeadDirRight
    }

    tm.States[5] = func(token byte) (int, byte, automata.TMHeadDir) {
        if token == '1' {
            return 6, 'Y', automata.TMHeadDirLeft
        }
        if (token == 'X') || (token == 'Y') {
            return 7, token, automata.TMHeadDirRight
        }
        return 8, token, automata.TMHeadDirRight
    }

    tm.States[6] = func(token byte) (int, byte, automata.TMHeadDir) {
        if (token == '0') || (token == '1') {
            return 6, token, automata.TMHeadDirLeft
        }
        if (token == 'X') || (token == 'Y') || (token == 0x00) {
            return 0, token, automata.TMHeadDirRight
        }
        return 8, token, automata.TMHeadDirRight
    }

    tm.States[7] = func(token byte) (int, byte, automata.TMHeadDir) {
        return 7, token, automata.TMHeadDirRight
    }

    tm.States[8] = func(token byte) (int, byte, automata.TMHeadDir) {
        return 8, token, automata.TMHeadDirRight
    }

    for true {
        var s string
        fmt.Printf("input: ")
        fmt.Scanf("%s", &s)

        fmt.Printf("Accepted: %v\n", tm.Accepts(s))
    }
}
