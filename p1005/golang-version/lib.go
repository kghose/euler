package main

import (
	"slices"
)

type ListStatus int

const (
	SumsToTarget ListStatus = iota
	LessThanTarget
	ExceedsTarget
)

func checkList(list []int, target int) ListStatus {
	sum := 0
	for _, i := range list {
		sum = sum + i
	}
	if sum < target {
		return LessThanTarget
	}
	if sum == target {
		return SumsToTarget
	}
	return ExceedsTarget
}

func getLists(currentI int, partialList []int, target int, primes *[]int) [][]int {
	results := [][]int{}
	for i := currentI; i < len(*primes); i++ {
		newPartialList := append(slices.Clone(partialList), (*primes)[i])
		cl := checkList(newPartialList, target)
		switch cl {
		case SumsToTarget:
			return append(
				results,
				newPartialList)
		case LessThanTarget:
			results = append(
				results,
				getLists(i+1, newPartialList, target, primes)...)
		default:
			return results
		}
	}
	return results
}

func moduloProduct(list []int, modulo int) int {
	prod := 1
	for _, i := range list {
		prod = (prod * i) % modulo
	}
	return prod
}
