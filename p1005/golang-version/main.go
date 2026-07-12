package main

import (
	"bufio"
	"compress/gzip"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func loadPrimes(m int) []int {
	file, _ := os.Open("../primes_100M.txt.gz")
	defer file.Close()
	gzReader, _ := gzip.NewReader(file)
	scanner := bufio.NewScanner(gzReader)

	primes := []int{}
	for scanner.Scan() {
		a := strings.TrimSpace(scanner.Text())
		p, _ := strconv.Atoi(a)
		primes = append(primes, p)
		if p > m {
			break
		}
	}
	fmt.Printf("Prime count = %d\n", len(primes))

	return primes
}

func main() {
	target := 2026

	primes := loadPrimes(target)

	lists := getLists(0, []int{}, target, &primes)

	median := len(lists) / 2

	fmt.Printf("L = %d, median = %d, val = %v\n", len(lists), median, lists[median-1])

	p := moduloProduct(lists[median-1], 1000000000)
	fmt.Printf("Product = %d\n", p)
}
