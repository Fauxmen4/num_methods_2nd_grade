package main

import (
	"math"
)

var (
	halfDivIter = func(a, b float64) float64 { return (a + b) / 2 }
	chordIter   = func(a, b float64, f func(x float64) float64) float64 { return a - (b-a)*f(a)/(f(b)-f(a)) }
	newtonIter  = func(x float64, f, f1 func(x float64) float64) float64 { return x - f(x)/f1(x) }
)

func localize(A, B float64, f func(x float64) float64) (float64, float64) {
	var i float64 = 1 //? начальный размер шага
	for {
		var step float64 = 1 / i
		var current float64 = A
		for current < B {
			if f(current)*f(current+step) < 0 {
				return current, current + step
			}
			current++
		}
		i++
	}
}

func newtonMethod(A, B float64, f, f1 func(x float64) float64, eps float64) float64 {
	var a, b float64 = A, B
	var prev_x, current_x float64 = (-1) * math.Pow(10, 4), 3.3 //a
	for math.Abs(prev_x-current_x) > eps {
		var tmp float64 = current_x
		current_x = newtonIter(current_x, f, f1)
		if current_x < a || current_x > b {
			current_x = chordIter(a, b, f)
			// current_x = halfDivIter(a, b)
		}
		c := f(current_x)
		if c < 0 {
			a = current_x
		} else {
			b = current_x
		}
		prev_x = tmp
	}
	return current_x
}