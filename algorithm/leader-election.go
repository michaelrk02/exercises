package main

import (
    "fmt"
    "math/rand"
    "time"
)

func main() {
    rand.Seed(time.Now().Unix())

    var nodeCnt int
    fmt.Printf("# of nodes: ")
    fmt.Scanf("%d", &nodeCnt)

    nodes := make([]*node, nodeCnt)
    leaderCh := make(chan int)
    for i := 0; i < nodeCnt; i++ {
        uid := rand.Int()
        nodes[i] = newNode(uid, leaderCh)
        fmt.Printf(" -uid(%d): %d\n", i, uid)
    }
    for i := 0; i < nodeCnt; i++ {
        nodes[i].Next = nodes[(i + 1) % nodeCnt]
    }
    for i := 0; i < nodeCnt; i++ {
        go nodes[i].Elect()
    }
    leader := <-leaderCh
    fmt.Printf("Node with UID: %d is the leader\n", leader)
}

type node struct {
    uid int
    leaderCh chan int

    Next *node
    Msg chan int
}

func newNode(uid int, leaderCh chan int) *node {
    return &node{
        uid: uid,
        leaderCh: leaderCh,
        Msg: make(chan int, 1)}
}

func (n *node) Elect() {
    n.Next.Msg <- n.uid
    for {
        input := <-n.Msg
        if input > n.uid {
            n.Next.Msg <- input
        } else if input < n.uid {
            // no-op
        } else {
            n.leaderCh <- n.uid
        }
    }
}

