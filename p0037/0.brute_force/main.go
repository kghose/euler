package main

import (
	"bufio"
	"compress/gzip"
	"fmt"
	"os"
	"strings"
	"strconv"
)

type void struct{}

var member void

func load_primes() (map[string]void, []string, error) {

	primes := make(map[string]void)
	prime_list := make([]string, 0, 5800000)

	primes_file := "../../primes_100M.txt.gz"

	file, err := os.Open(primes_file)
	if err != nil {
		fmt.Println("Error opening file:", err)
		return primes, prime_list, err
	}
	defer file.Close() // Ensure the file is closed

	gz_reader, err := gzip.NewReader(file)
	if err != nil {
		fmt.Println("Failed to create gzip reader: ", err)
		return primes, prime_list, err
	}
	defer gz_reader.Close()

	scanner := bufio.NewScanner(gz_reader)
	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		primes[line] = member
		prime_list = append(prime_list, line)
		// fmt.Println(line)
	}

	if err := scanner.Err(); err != nil {
		fmt.Println("Error scanning file:", err)
	}

	return primes, prime_list, nil
}

func left_truncatable(number string, primes map[string]void) bool {
	lt_number := number[1:]
	_, ok := primes[lt_number]
	if ok {
		if len(lt_number) == 1 {
			return true
		}
		return left_truncatable(lt_number, primes)
	} else {
		return false
	}

}

func right_truncatable(number string, primes map[string]void) bool {
	rt_number := number[:len(number)-1]
	_, ok := primes[rt_number]
	if ok {
		if len(rt_number) == 1 {
			return true
		}
		return right_truncatable(rt_number, primes)
	} else {
		return false
	}

}

func main() {

	primes, prime_list, _ := load_primes()
	fmt.Println(fmt.Sprintf("Loaded %v primes", len(primes)))

	truncatable_primes_sum := 0
	
	for _, number := range prime_list {
		if len(number) < 2 {
			continue
		}

		if left_truncatable(number, primes) && right_truncatable(number, primes) {
			fmt.Println(number)
			int_num, _ := strconv.Atoi(number)
			truncatable_primes_sum = truncatable_primes_sum + int_num
		}
	}

	fmt.Println("Total is ", truncatable_primes_sum)
}
