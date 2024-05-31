package main

import (
	"log"
	"math"

	"gonum.org/v1/gonum/mat"
)

func minusF(x [2]float64) [2]float64 {
	return [2]float64{
		(-1) * (math.Cos(x[0]) + x[1] - 1.5),
		(-1) * (2*x[0] - math.Sin(x[1]-0.5) - 1),
	}
}

func J(x [2]float64) [2][2]float64 {
	return [2][2]float64{
		{(-1) * math.Sin(x[0]), 1},
		{2, (-1) * math.Cos(x[1]-0.5)},
	}
}

func minusFLambda(l float64, x [2]float64) [2]float64 {
	return [2]float64{
		(-1) * (l*math.Cos(x[0]) + x[1] - 1.5),
		(-1) * (2*x[0] - l*math.Sin(x[1]-0.5) - 1),
	}
}

func JLambda(l float64, x [2]float64) [2][2]float64 {
	return [2][2]float64{
		{(-1) * l * math.Sin(x[0]), 1},
		{2, (-1) * l * math.Cos(x[1]-0.5)},
	}
}

func InfVecNorm(x [2]float64) float64 {
	if math.Abs(x[0]) > math.Abs(x[1]) {
		return math.Abs(x[0])
	} else {
		return math.Abs(x[1])
	}
}

func SolveSLAE(a [2][2]float64, b [2]float64) [2]float64 {
	_a := mat.NewDense(2, 2, []float64{a[0][0], a[0][1], a[1][0], a[1][1]})
	_b := mat.NewDense(2, 1, []float64{b[0], b[1]})
	_x := mat.NewDense(2, 1, nil)

	var qr mat.QR
	qr.Factorize(_a)

	err := qr.SolveTo(_x, false, _b)
	if err != nil {
		log.Fatalf("could not solve QR: %+v", err)
	}

	return [2]float64{_x.At(0, 0), _x.At(1, 0)}
}

// ? Графическое приближение
func Newton(x0, y0 float64, eps float64) [2]float64 {
	//var isFirst bool = false
	prevAppr, currAppr := [2]float64{}, [...]float64{x0, y0}
	for InfVecNorm([2]float64{currAppr[0] - prevAppr[0], currAppr[1] - prevAppr[1]}) > eps {
		tmp := [...]float64{currAppr[0], currAppr[1]}
		prevAppr[0], prevAppr[1] = tmp[0], tmp[1]
		d := SolveSLAE(J(currAppr), minusF(currAppr))
		d[0] += prevAppr[0]
		d[1] += prevAppr[1]

		_ = copy(currAppr[:], d[:])
		//isFirst = true
	}
	return currAppr
}

func Approximation(N float64) (float64, float64) {
	prevAppr, currAppr := [2]float64{}, [2]float64{0.5, 1.5} //! (x0, y0) нашли самостоятельно

	for i := 1.0; i < N+1; i++ {
		tmp := [...]float64{currAppr[0], currAppr[1]}
		prevAppr[0], prevAppr[1] = tmp[0], tmp[1]

		d := SolveSLAE(JLambda(i/N, currAppr), minusFLambda(i/N, currAppr))
		d[0] += prevAppr[0]
		d[1] += prevAppr[1]

		_ = copy(currAppr[:], d[:])
	}

	return currAppr[0], currAppr[1]
}
