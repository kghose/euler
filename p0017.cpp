/*

    Euler problem 17

    Number letter counts

    If the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 
    3 + 3 + 5 + 4 + 4 = 19 letters used in total.

    If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how 
    many letters would be used?

    NOTE: Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) 
    contains 23 letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" 
    when writing out numbers is in compliance with British usage.

    compile: g++ --std=c++14 p0017.cpp -o p0017
    run: ./p0017

*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>


const std::vector<std::string> a0_19 = {
    "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
    "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
} ;
    

const std::vector<std::string> a20_90 = {    
    "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
} ;


std::string replace(std::string src, const std::string& search, const std::string& replace) {
    size_t pos = 0;
    while ((pos = src.find(search, pos)) != std::string::npos) {
         src.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return src;
}


/* 

    1 - 20 ad hoc
    21 - twenty one
    35 - thirty five
    342 - three hundred and forty two
    512 - five hundred and twelve

*/ 

std::string number_in_words(int number) {
    assert( 0 < number );
    assert( number < 1001);

    int thousands = number / 1000;
    int hundreds = (number % 1000) / 100;
    int tens = (number % 100) / 10;
    int units = number % 10;

    std::string words = "";
    if (thousands) words += a0_19[thousands] + " thousand";
    if (hundreds) words += a0_19[hundreds] + " hundred";
    if (tens * 10 + units > 19) {
        if (thousands || hundreds) words += " and ";
        words += a20_90[tens];
        if (units) words += "-" + a0_19[units];
    } else if (tens * 10 + units > 0) {
        if (thousands || hundreds) words += " and ";
        words += a0_19[tens * 10 + units];
    }
    return words;
}


int main(int argc, char *argv[]) {
    
    std::string word;
    int letter_count = 0;
    for(int i = 1; i <= 1000; i++)
        letter_count += replace(replace(number_in_words(i), " ", ""), "-", "").length();
    std::cout << letter_count << std::endl;
    
    //std::cout << number_in_words(std::stoi(argv[1])) << std::endl ; 
}