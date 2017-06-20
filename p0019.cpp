/*

Counting Sundays
Problem 19 
You are given the following information, but you may prefer to do some research for yourself.

1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?

*/

/*
    Conventions: 

    Days of the week:
    SUN = 0, MON, TUE, WED, THU, FRI, SAT

    Months:
    JAN = 0, FEB, MAR, APR, MAY, JUN, JLY, AUG, SEP, OCT, NOV, DEC

*/
#include <iostream>

const std::string DOW[] = {
    "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};

const std::string MONTH[] = {
    "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JLY", "AUG", "SEP", "OCT", "NOV", "DEC"
};

const int days_in_month_table[] = {
//  J   F   M   A   M   J   J   A   S   O   N   D
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31  
};

struct Day {
    int dow;    // SUN = 0, MON, TUE, WED, THU, FRI, SAT
    int dom;
    int month;  // JAN = 0, FEB, MAR, APR, MAY, JUN, JLY, AUG, SEP, OCT, NOV, DEC
    int year;
};

std::ostream& operator << (std::ostream &o, const Day& day) {
    return o << DOW[day.dow] << ", " << day.dom + 1 << "  " << MONTH[day.month] << " " << day.year;
}


int days_in_month(const Day& day) {
    if (
        (day.month == 1) &&           // February? Gotta handle leap years 
        (day.year % 4 == 0) &&        // A leap year occurs on any year evenly divisible by 4
        (
            (day.year % 100) ||       // But not on a century
            (day.year % 400 == 0)     // unless it is divisible by 400
        ))   
    {   
        return 29;
    }
    return days_in_month_table[day.month];
}

bool sunday_on_the_first(const Day& day) {
    return (day.dow == 0) && (day.dom == 0);
}

Day next_day(const Day& day) {
    Day new_day(day);
    new_day.dow = (day.dow + 1) % 7;
    new_day.dom = day.dom + 1;
    if (new_day.dom == days_in_month(day)) {
        new_day.dom = 0;
        new_day.month = day.month + 1;
        if (new_day.month == 12) {
            new_day.month = 0;
            new_day.year = day.year + 1;
        }
    }
    return new_day;
}


int main(int argc, char *argv[]) {
    Day day;
    // 1 Jan 1900 was a Monday
    day.dow = 1;     // Monday
    day.dom = 0;     // 1st
    day.month = 0;   // JAN
    day.year = 1900; // 1900
    
    while(day.year < 1901) day = next_day(day);
    std::cout << "Starting at " << day << std::endl;
    
    int sundays = 0;

    while(day.year < 2001) {
        if (sunday_on_the_first(day)) sundays++;
        day = next_day(day);
    }
    std::cout << "Stopped before " << day << std::endl;

    std::cout << "There are " << sundays << " Sundays that fell on the first of the month" << std::endl;
}
