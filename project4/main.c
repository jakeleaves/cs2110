/* DO NOT REMOVE INCLUDES */
#include "part1-porting_assembly.h"
#include "part2-calendar.h"

int main(void) {

    /* Call your part1 and part2 functions here if you would like to test them yourself */
    int test_value = compare(2, 3);
    printf("Expected Return Value: -1\nActual Return Value: %d\n", test_value);

    initialize_calendar();
    int add_calendar_event(date d, event new_event);
    date d;
    d.month = 1;
    d.day = 1;
    event new_event;
    int g = add_calendar_event(d, new_event);
    printf("Expected 1, but got %d\n", calendar_2021[0].num_events);
    printf("Expected 0, but got %d\n", g);
    }

