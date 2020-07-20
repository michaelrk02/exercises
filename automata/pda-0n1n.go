package main

import (
    "fmt"
    "github.com/michaelrk02/automata"
)

func main() {
    pda := automata.NewPushDownAutomata(4, 0, 2)

    pda.States[0] = func(token, top byte) (int, automata.PDAStackOp) {
        if (token == '0') && ((top == 0x00) || (top == 'A')) {
            return 0, &automata.PDAStackOpPush{Symbol: 'A'}
        }
        if (token == '1') && (top == 'A') {
            return 1, &automata.PDAStackOpIgnore{}
        }
        return 3, &automata.PDAStackOpIgnore{}
    }

    pda.States[1] = func(token, top byte) (int, automata.PDAStackOp) {
        if (token == '1') && (top == 'A') {
            return 1, &automata.PDAStackOpPop{}
        }
        if (token == 0x00) && (top == 'A') {
            return 2, &automata.PDAStackOpPop{}
        }
        return 3, &automata.PDAStackOpIgnore{}
    }

    pda.States[2] = func(token, top byte) (int, automata.PDAStackOp) {
        if (token == '1') {
            return 3, &automata.PDAStackOpIgnore{}
        }
        return 2, &automata.PDAStackOpIgnore{}
    }

    pda.States[3] = func(token, top byte) (int, automata.PDAStackOp) {
        return 3, &automata.PDAStackOpIgnore{}
    }

    for true {
        var in string
        fmt.Printf("input: ")
        fmt.Scanf("%s", &in)

        fmt.Printf("Accepted: %v\n", pda.Accepts(in))
    }
}

