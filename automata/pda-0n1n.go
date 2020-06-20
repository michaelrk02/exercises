package main

import (
    "fmt"
)

type byteStack []byte

func (s byteStack) top() byte {
    return s[0]
}

func (s *byteStack) push(c byte) {
    *s = append([]byte{c}, (*s)...)
}

func (s *byteStack) pop() {
    *s = (*s)[1:len(*s)]
}

func verify(s string) bool {
    stack := make(byteStack, 0)
    state := 0
    for _, input := range s {
        if state == 0 {
            if input == '0' {
                if len(stack) == 0 {
                    stack.push('A')
                } else if stack.top() == 'A' {
                    stack.push('A')
                }
            }
            if input == '1' {
                if len(stack) == 0 {
                } else if stack.top() == 'A' {
                    stack.pop()
                    state = 1
                }
            }
            continue
        }
        if state == 1 {
            if input == '0' {
                stack.push('X')
            }
            if input == '1' {
                if len(stack) == 0 {
                    stack.push('X')
                } else if stack.top() == 'A' {
                    stack.pop()
                }
            }
            continue
        }
    }
    return state == 1 && len(stack) == 0
}

func main() {
    var str string
    fmt.Printf("Enter input string: ")
    fmt.Scanf("%s", &str)

    fmt.Printf("Result: %v\n", verify(str))
}

