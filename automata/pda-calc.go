// Push-Down Automata application on simple calculator
//
// Inspired by random STEI ITB folk's big assignment (a.k.a. tugas besar / tubes) of formal language & automata theory on GitHub.
// But here the idea is to create a concrete syntax tree (impl. in binary tree) so we can recursively parse it with binary operations.
// Have fun learning :)

// For example: A + B * (C + D) + E ^ F ^ (G - H)
// CST representation:
//
//    __+__
//   /     \
//  A     __+__
//       /     \
//      *       ^
//     / \     / \
//    B   +   E   ^
//       / \     / \
//      C   D   F   -
//                 / \
//                G   H

// Another example: A + B + C + D + E
// CST representation
//
//          +
//         / \
//        +   E
//       / \
//      +   D
//     / \
//    +   C
//   / \
//  A   B

// Context-Free Grammar:
//  E -> I | F | E op E | (E)
//  I -> int | int I | - int | - int I
//  F -> I.I
//  int -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
//  op -> + | - | * | / | ^

package main

import (
    "fmt"
    "math"
    "strconv"
)

func main() {
    // construct pushdown automata
    pda := newPushdownAutomata(stateIDCount, stateIDExpr)
    var stk expressionStack

    pda.q[stateIDExpr] = &state{
        trans: func(ch byte) *transition {
            if isInt(ch) || ch == '-' {
                self := stk.top()
                stk.pop()
                if self != nil {
                    stk.push(&binaryExpr{op: self.(*binaryExpr).op, lhs: self.(*binaryExpr).lhs, rhs: makeExpr(ch)})
                } else {
                    stk.push(makeExpr(ch))
                }
                return &transition{q: stateIDInt}
            }
            if ch == '(' {
                if stk.top() == nil {
                    stk.pop()
                    stk.push(&binaryExpr{op: '+', lhs: makeExpr('0'), rhs: nil})
                }
                stk.push(nil)
                return &transition{q: stateIDExpr, push: 1}
            }
            if ch == 0x00 {
                if stk.top().(*binaryExpr).rhs != nil {
                    stk.aggregateAll()
                    return &transition{q: stateIDExpr}
                }
            }
            return &transition{q: stateIDError}
        },
    }

    pda.q[stateIDBinop] = &state{
        trans: func(ch byte) *transition {
            if isOp(ch) {
                stk.insertOp(ch)
                return &transition{q: stateIDExpr}
            }
            if ch == ')' {
                stk.aggregate()
                return &transition{q: stateIDBinop, push: 0xFF}
            }
            if ch == 0x00 {
                stk.aggregateAll()
                return &transition{q: stateIDExpr}
            }
            return &transition{q: stateIDError}
        },
    }

    pda.q[stateIDInt] = &state{
        trans: func(ch byte) *transition {
            if isInt(ch) {
                appendExpr(stk.top(), ch)
                return &transition{q: stateIDInt}
            }
            if ch == '.' {
                appendExpr(stk.top(), ch)
                return &transition{q: stateIDFloat}
            }
            if isOp(ch) {
                stk.insertOp(ch)
                return &transition{q: stateIDExpr}
            }
            if ch == ')' {
                stk.aggregate()
                return &transition{q: stateIDBinop, push: 0xFF}
            }
            if ch == 0x00 {
                stk.aggregateAll()
                return &transition{q: stateIDExpr}
            }
            return &transition{q: stateIDError}
        },
    }

    pda.q[stateIDFloat] = &state{
        trans: func(ch byte) *transition {
            if isInt(ch) {
                appendExpr(stk.top(), ch)
                return &transition{q: stateIDFloat}
            }
            if isOp(ch) {
                stk.insertOp(ch)
                return &transition{q: stateIDExpr}
            }
            if ch == ')' {
                stk.aggregate()
                return &transition{q: stateIDBinop, push: 0xFF}
            }
            if ch == 0x00 {
                stk.aggregateAll()
                return &transition{q: stateIDExpr}
            }
            return &transition{q: stateIDError}
        },
    }

    pda.q[stateIDError] = &state{
        trans: func(ch byte) *transition {
            return &transition{q: stateIDError}
        },
    }

    fmt.Println("Enter mathematical expression (without spaces)")
    for true {
        stk = make(expressionStack, 1)

        var expr string
        fmt.Printf("$ ")
        fmt.Scanf("%s", &expr)

        pda.stack = make(byteStack, 0)
        pda.qcur = 0
        for i := 0; i < len(expr); i++ {
            pda.feed(expr[i])
        }
        pda.feed(0x00)

        if pda.accepted() {
            result := evaluate(stk.top())
            fmt.Printf(" -> %v\n", result)
        } else {
            fmt.Println("Please check your syntax then try again")
        }
    }
}

func isInt(ch byte) bool {
    return (ch >= '0') && (ch <= '9')
}

func isOp(ch byte) bool {
    return isAddSub(ch) || isMulDiv(ch) || (ch == '^')
}

func isAddSub(ch byte) bool {
    return (ch == '+') || (ch == '-')
}

func isMulDiv(ch byte) bool {
    return (ch == '*') || (ch == '/')
}

type stateID = int
const (
    stateIDExpr stateID = iota  // expects - | int | (
    stateIDBinop                // expects op | )
    stateIDInt                  // expects int | . | op | )
    stateIDFloat                // expects int | op | )
    stateIDError
    stateIDCount
)

type pushdownAutomata struct {
    stack byteStack
    q []*state
    n int
    qcur, qfinal stateID
}

func newPushdownAutomata(n int, qfinal stateID) *pushdownAutomata {
    pda := new(pushdownAutomata)
    pda.stack = make(byteStack, 0)
    pda.q = make([]*state, n)
    pda.n = n
    pda.qcur = 0
    pda.qfinal = qfinal
    return pda
}

func (pda *pushdownAutomata) feed(ch byte) {
    q := pda.q[pda.qcur]
    if q == nil {
        panic(fmt.Sprintf("no state with ID: %d", pda.qcur))
    }

    trans := q.trans(ch)
    if trans == nil {
        panic(fmt.Sprintf("no transition is available at state %d with input %c", pda.qcur, ch))
    }

    pda.qcur = trans.q
    switch trans.push {
    case 0x00:
    case 0xFF:
        pda.stack.pop()
    default:
        pda.stack.push(trans.push)
    }
}

func (pda *pushdownAutomata) accepted() bool {
    return (pda.qcur == pda.qfinal) && (len(pda.stack) == 0)
}

type byteStack []byte

func (s *byteStack) top() byte {
    return (*s)[len(*s) - 1]
}

func (s *byteStack) push(ch byte) {
    *s = append(*s, ch)
}

func (s *byteStack) pop() {
    if (len(*s) == 0) {
        panic("stack is empty")
    }
    *s = (*s)[0:len(*s) - 1]
}

type state struct {
    trans transitionFunc
}

type transitionFunc = func(byte) *transition

type transition struct {
    q stateID
    push byte // 0x00: no-op; 0xFF: pop
}

type expression interface{}

func makeExpr(ch byte) expression {
    return &binaryExpr{op: '+', lhs: &unaryExpr{n: "0"}, rhs: &unaryExpr{n: string([]byte{ch})}}
}

func appendExpr(expr expression, ch byte) {
    bexpr := expr.(*binaryExpr)
    rhs, ok := bexpr.rhs.(*binaryExpr)
    if ok {
        appendExpr(rhs, ch)
    } else {
        bexpr.rhs.(*unaryExpr).n += string([]byte{ch})
    }
}

func evaluate(expr expression) float64 {
    if expr == nil {
        panic("trying to evaluate nil expression")
    }
    if uexpr, ok := expr.(*unaryExpr); ok {
        n, _ := strconv.ParseFloat(uexpr.n, 64)
        return n
    }
    if bexpr, ok := expr.(*binaryExpr); ok {
        switch bexpr.op {
        case '+':
            return evaluate(bexpr.lhs) + evaluate(bexpr.rhs)
        case '-':
            return evaluate(bexpr.lhs) - evaluate(bexpr.rhs)
        case '*':
            return evaluate(bexpr.lhs) * evaluate(bexpr.rhs)
        case '/':
            return evaluate(bexpr.lhs) / evaluate(bexpr.rhs)
        case '^':
            return math.Pow(evaluate(bexpr.lhs), evaluate(bexpr.rhs))
        }
    }
    panic("unknown expression type")
    return 0.0
}

type expressionStack []expression

func (s *expressionStack) isMulDiv() bool {
    if expr, ok := s.top().(*binaryExpr); ok {
        return isMulDiv(expr.op)
    }
    return true
}

func (s *expressionStack) isPow() bool {
    if expr, ok := s.top().(*binaryExpr); ok {
        return expr.op == '^'
    }
    return false
}

func (s *expressionStack) top() expression {
    return (*s)[len(*s) - 1]
}

func (s *expressionStack) push(expr expression) {
    *s = append(*s, expr)
}

func (s *expressionStack) pop() {
    if (len(*s) == 0) {
        panic("stack is empty")
    }
    *s = (*s)[0:len(*s) - 1]
}

func (s *expressionStack) insertOp(ch byte) {
    if (isMulDiv(ch) && !s.isMulDiv()) || (ch == '^') {
        s.push(&binaryExpr{op: ch, lhs: s.top().(*binaryExpr).rhs, rhs: nil})
    } else {
        self := s.top()
        s.pop()
        s.push(&binaryExpr{op: ch, lhs: self, rhs: nil})
    }
}

func (s *expressionStack) aggregate() {
    top := s.top()
    s.pop()
    self := s.top()
    s.pop()
    s.push(&binaryExpr{op: self.(*binaryExpr).op, lhs: self.(*binaryExpr).lhs, rhs: top})
}

func (s *expressionStack) aggregateAll() {
    for len(*s) > 1 {
        s.aggregate()
    }
}

type unaryExpr struct {
    n string
}

type binaryExpr struct {
    op byte
    lhs, rhs expression
}

