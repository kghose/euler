package main

import (
	"fmt"
	"testing"

	"github.com/google/go-cmp/cmp"
)

func TestCheckList(t *testing.T) {
	tests := []struct {
		name   string
		list   []int
		target int
		want   ListStatus
	}{
		{
			"=",
			[]int{2, 5, 13},
			20,
			SumsToTarget,
		},
		{
			"<",
			[]int{2, 5, 13},
			22,
			LessThanTarget,
		},
		{
			">",
			[]int{2, 5, 13},
			18,
			ExceedsTarget,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			got := checkList(tt.list, tt.target)
			if diff := cmp.Diff(tt.want, got); diff != "" {
				t.Errorf(
					"checkList failed (-want, +got):\n%s",
					diff)
			}
		})
	}
}

func TestGetLists(t *testing.T) {
	primes := []int{2, 3, 5, 7, 11, 13, 17, 19}
	tests := []struct {
		target int
		want   [][]int
	}{
		{
			1,
			[][]int{},
		},
		{
			2,
			[][]int{{2}},
		},
		{
			5,
			[][]int{
				{2, 3},
				{5},
			},
		},
		{
			10,
			[][]int{
				{2, 3, 5},
				{3, 7},
			},
		},
		{
			20,
			[][]int{
				{2, 5, 13},
				{2, 7, 11},
				{3, 17},
				{7, 13},
			},
		},
	}

	for _, tt := range tests {
		t.Run(fmt.Sprintf("Target=%d", tt.target), func(t *testing.T) {
			got := getLists(0, []int{}, tt.target, &primes)
			if diff := cmp.Diff(tt.want, got); diff != "" {
				t.Errorf(
					"checkList failed (-want, +got):\n%s",
					diff)
			}
		})
	}
}
