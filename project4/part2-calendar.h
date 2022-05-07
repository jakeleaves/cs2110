#ifndef __CALENDAR__
#define __CALENDAR__

/* DO NOT MODIFY FILE */

#include <stdio.h>

#define UNUSED(x) ((void)x)

#define MAX_NUM_EVENTS 10
#define SIZE_DESCRIPTION 100
#define NUM_DAYS 365

#define ERROR -1
#define SUCCESS 0

typedef struct _time_ {
    int hour;
    int minute;
} time;

typedef struct _event_ {
    char description[SIZE_DESCRIPTION];
    time start;
    time end;
} event;

typedef struct _date_ {
    int month;
    int day;
    int year;
    int num_events;
    event events[MAX_NUM_EVENTS];
} date;

extern date calendar_2021[NUM_DAYS]; // External for Autograder Use

extern void initialize_calendar(void);
extern int check_event_overlap(event e1, event e2);
extern int add_calendar_event(date d, event new_event);
extern int remove_calendar_event(date d, int event_index);
extern int change_event_time(date d, int event_index, time start, time end);
extern int change_event_description(date d, int event_index, char description[]);
extern void sort_events(date d);
extern void destroy_calendar(void);

#endif // __CALENDAR__
