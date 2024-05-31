package main

import (
	"fmt"
	"math"
)

// ! Задани 1
var (
	myf  = func(x float64) float64 { return 3*x - math.Cos(x) - 1 }
	myf1 = func(x float64) float64 { return 3 + math.Sin(x) }
	myf2 = func(x float64) float64 { return math.Cos(x) }
)

// ! Задание 2
var ()

func main() {
	// a, b := localize(-10, 10, myF)
	// fmt.Println(newtonMethod(a, b, myF, myF1, math.Pow(10, -4)))

	//fmt.Println(Newton(0.50, 0.60, math.Pow(10, -4)))
	x0, y0 := Approximation(1000)
	fmt.Printf("Приближение %v, %v\n", x0, y0)
	fmt.Printf("Решение %v\n", Newton(x0, y0, math.Pow(10, -4)))
}
