/* DO NOT REMOVE INCLUDES */
#include "part2-calendar.h"

/* GLOBAL CALENDAR ARRAY */
date calendar_2021[NUM_DAYS];

/**
 * @brief Initialize the entire calendar
 *            Set each date in calendar_2021 to the correct month, day, and year.
 *            Also, set each date's num_events value to 0
 */
void initialize_calendar(void) {
    int day, month;
    for (int i = 0; i <= 364; i++) {
        if ((i >= 0) && (i < 31)) {
            day = i + 1;
            month = 1;
        } else if ((i >= 31) && (i <= 58)) {
            day = i - 30;
            month = 2;
        } else if ((i > 58) && (i <= 89)) {
            day = i - 58;
            month = 3;
        } else if ((i > 89) && (i <= 119)) {
            day = i - 89;
            month = 4;
        } else if ((i > 119) && (i <= 150)) { 
            day = i - 119;
            month = 5;
        } else if ((i > 150) && (i <= 180)) {
            day = i - 150;
            month = 6;
        } else if ((i > 180) && (i <= 211)) {
            day = i - 180;
            month = 7;
        } else if ((i > 211) && (i <= 242)) {
            day = i - 211;
            month = 8;
        } else if ((i > 242) && (i <= 272)) {
            day = i - 242;
            month = 9;
        } else if ((i > 272) && (i <= 303)) {
            day = i - 272;
            month = 10;
        } else if ((i > 303) && (i <= 333)) {
            day = i - 303;
            month = 11;
        } else if (i > 333) {
            day = i - 333;
            month = 12;
        }    
        calendar_2021[i].month = month;
        calendar_2021[i].day = day;
        calendar_2021[i].year = 2021;
        calendar_2021[i].num_events = 0;
    } 
    return;
}

/**
 * @brief Compare the times of two events and determine if they 'overlap'
 *             See PDF section - Calendar Conditions - for how we define 'overlap'
 * 
 * @param e1 event 1
 * @param e2 event 2
 * @return int SUCCESS or ERROR
 */
int check_event_overlap(event e1, event e2){

    int a = 0;
    double e1s = e1.start.hour + (double)(e1.start.minute)/60;
    double e1e = e1.end.hour + (double)(e1.end.minute)/60;
    double e2s = e2.start.hour + (double)(e2.start.minute)/60;
    double e2e = e2.end.hour + (double)(e2.end.minute)/60;
    
    // if start and end times are the same
    if ((e1s == e2e) || (e2s == e1e)) {
        a = -1;
    }

    if (e1s == e2s) {
        a = -1;
    }
    
    if ((e1s > e1e) || (e2s > e2e)) {
        a = -1;
    }
    if ((e1s > e2s) && (e1s < e2e)) {
        a = -1;
    }
    if ((e2s > e1s) && (e2s < e1e)) {
        a = -1;
    }
    if ((e1e > e2s) && (e1e < e2e)) {
        a = -1;
    }
    if ((e2e > e1s) && (e2e < e1e)) {
        a = -1;
    }
    return a;
}

/**
 * @brief Add new event to the calendar on the specified 
 *             Remember event times canNOT overlap
 *             Consider using your check_event_overlap() function
 * 
 * @param d used to locate the date's index in calendar_2021
 * @param new_event event being added
 * @return int SUCCESS or ERROR
 */
int add_calendar_event(date d, event new_event){
    
    /* Remove once the function is implemented */
    int calendar_index(int day, int month);
    int i = calendar_index(d.day, d.month);
    double nes = new_event.start.hour + (double)(new_event.start.minute)/60;
    double nee = new_event.end.hour + (double)(new_event.end.minute)/60;
    for (int j = 0; j <= calendar_2021[i].num_events; j++) {
        if (check_event_overlap(calendar_2021[i].events[j], new_event) == -1) {
            return ERROR;
        }
        
    }
    if ((calendar_2021[i].num_events >= MAX_NUM_EVENTS) || (nes > nee)) {
        return ERROR;
    } else {
        int index = calendar_2021[i].num_events;
        calendar_2021[i].events[index] = new_event;
        calendar_2021[i].num_events ++;
        return SUCCESS;
    }
}

/**
 * @brief Remmove an event from the specified 
 *             Remember to shift any subsequent events 'up' in the array
 * 
 *  EX:
 *      Remove Event at index 2:
 *          - [e1, e2, e3, e4, e5]
 *          - [e1, e2, e4, e5]
 * 
 * @param d used to locate the date's index in calendar_2021
 * @param event_index index of the event to remove
 * @return int SUCCESS or ERROR
 */
int remove_calendar_event(date d, int event_index){
    
    /* Remove once the function is implemented */
    int calendar_index(int day, int month);
    int i = calendar_index(d.day, d.month);
    for (int j = event_index; j < calendar_2021[i].num_events; j++) {
        calendar_2021[i].events[j] = calendar_2021[i].events[j + 1];
    }
    if ((event_index >= 0) && (event_index < calendar_2021[i].num_events)) {
        calendar_2021[i].num_events --;
        return SUCCESS;
    } else {
        return ERROR;
    }
    
}
/**
 * @brief Modify a specific event's start time and end time
 * 
 * @param d used to locate the date's index in calendar_2021
 * @param event_index index of the event to modify
 * @param start new event start time
 * @param end new event end time
 * @return int SUCCESS or ERROR
 */
int change_event_time(date d, int event_index, time start, time end){

    /* Remove once the function is implemented */
    int calendar_index(int day, int month);
    int i = calendar_index(d.day, d.month);
    
    if ((event_index > 0) && (event_index < calendar_2021[i].num_events)) {
        calendar_2021[i].events[event_index].start.minute = start.minute;
        calendar_2021[i].events[event_index].start.hour = start.hour;
        calendar_2021[i].events[event_index].end.minute = end.minute;
        calendar_2021[i].events[event_index].end.hour = end.hour;
        return SUCCESS;
    } else {
        return ERROR;
    }
}

/**
 * @brief Modify a specifc event's description string
 * 
 * @param d used to locate the date's index in calendar_2021
 * @param event_index index of the event to modify
 * @param description new string to copy into the event's description
 * @return int SUCCESS or ERROR
 */
int change_event_description(date d, int event_index, char description[SIZE_DESCRIPTION]){
    
    /* Remove once the function is implemented */
    int calendar_index(int day, int month);
    int i = calendar_index(d.day, d.month);
    for (int j = 0; j < SIZE_DESCRIPTION; j++) {
        calendar_2021[i].events[event_index].description[j] = description[j];
    }
    if (event_index < calendar_2021[i].num_events) {
        return SUCCESS;
    } else {
        return ERROR;
    }

}

/**
 * @brief Sort a date's event array by start time (earliest time to latest time)
 * 
 * @param d used to locate the date's index in calendar_2021
 */
void sort_events(date d){
    int calendar_index(int day, int month);
    int i = calendar_index(d.day, d.month);
    int t1, t2;

    for (int k = 0; k < calendar_2021[i].num_events; k++) {
        for (int j = 0; j < calendar_2021[i].num_events - 1; j++) {
            t1 = calendar_2021[i].events[j].start.hour + (double)(calendar_2021[i].events[j].start.minute)/60;
            t2 = calendar_2021[i].events[j + 1].start.hour + (double)(calendar_2021[i].events[j + 1].start.minute)/60;
            if (t1 > t2) {
                event temp = calendar_2021[i].events[j];
                calendar_2021[i].events[j] = calendar_2021[i].events[j + 1];
                calendar_2021[i].events[j + 1] = temp;
            }
        }
    }  
}

/**
 * @brief Destroy the calendar - set each calendar date month, day, year, and num_events to 0
 */
void destroy_calendar(void){
    
    for(int i = 0; i <= 364; i++) {
        calendar_2021[i].month = 0;
        calendar_2021[i].day = 0;
        calendar_2021[i].year = 0;
        calendar_2021[i].num_events = 0;
    }
}
// helper functions
//finds the calendar's exact day of the year given a date
int calendar_index(int day, int month){
    int index;
    for(int i = 0; i <= 364; i++) {
        if ((calendar_2021[i].month == month) && (calendar_2021[i].day == day)) {
            index = i;
        }
    }
    return index;
}
