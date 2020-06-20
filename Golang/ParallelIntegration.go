package main

import (
    "fmt"
    "math"
    "time"
)

func dummy() {
    // There's nothing to do here
}

// Natural logarithm function
// Precomputed area between 1 and 1000 = 5908.76
func f(x float64) float64 {
    return math.Log(x)
}
const UPPER_BOUND = 1000.0
const LOWER_BOUND = 1.0

//
// Integrate with Riemann sum (trapezoidal form)
//

func integrateParallel(low, high, accuracy float64, resultCh chan float64) {
    steps := int(1.0 / accuracy)
    stride := (high - low) / float64(steps)
    result := 0.0
    for i := 0; i < steps; i++ {
        lb := low + float64(i) * stride
        ub := low + float64(i + 1) * stride
        result += (f(lb) + f(ub)) * stride / 2
    }
    resultCh <- result
}

func integrateSerial(low, high, accuracy float64) float64 {
    steps := int(1.0 / accuracy)
    stride := (high - low) / float64(steps)
    result := 0.0
    for i := 0; i < steps; i++ {
        lb := low + float64(i) * stride
        ub := low + float64(i + 1) * stride
        result += (f(lb) + f(ub)) * stride / 2
    }
    return result
}

func main() {
    var threads int
    fmt.Printf("Specify number of threads: ")
    fmt.Scanf("%d", &threads)

    var accuracy float64
    fmt.Printf("Enter accuracy (smaller is better): ")
    fmt.Scanf("%f", &accuracy)

    stride := (UPPER_BOUND - LOWER_BOUND) / float64(threads)

    var startTime, stopTime int64
    var sum float64

    //
    // BEGIN PARALLEL REGION
    //

    finished := 0
    sumCh := make(chan float64)
    sum = 0.0
    threadSpawnTime := int64(0)
    startTime = time.Now().UnixNano()

    for i := 0; i < threads; i++ {
        low := LOWER_BOUND + float64(i) * stride
        high := LOWER_BOUND + float64(i + 1) * stride

        spawnStart := time.Now().UnixNano()
        go integrateParallel(low, high, accuracy, sumCh)
        spawnStop := time.Now().UnixNano()

        threadSpawnTime += (spawnStop - spawnStart)
    }

    for finished < threads {
        sum += <-sumCh
        finished++
    }

    stopTime = time.Now().UnixNano()

    //
    // END SERIAL REGION
    //

    fmt.Printf("The result is: %f\n", sum)
    fmt.Printf("Parallel execution time: %dns\n", (stopTime - startTime - threadSpawnTime))
    // NOTE: The parallel execution time excludes the time required by spawning each thread

    sum = 0.0

    //
    // BEGIN SERIAL REGION
    //

    startTime = time.Now().UnixNano()

    for i := 0; i < threads; i++ {
        low := LOWER_BOUND + float64(i) * stride
        high := LOWER_BOUND + float64(i + 1) * stride
        sum += integrateSerial(low, high, accuracy)
    }

    stopTime = time.Now().UnixNano()

    //
    // END SERIAL REGION
    //

    fmt.Printf("The result is: %f\n", sum)
    fmt.Printf("Serial execution time: %dns\n", (stopTime - startTime))
}

// RESULT:
// Average parallel : serial time ratio = 1 : 2

