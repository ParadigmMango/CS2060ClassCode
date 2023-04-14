//!  Exam 2 Practice
/*!
  \file exam2Practice.c
  \author Jacob Hartt (jacobjhartt@gmail.com)
  \version 1.0
  \date 04-17-2023
 */

#include <stdio.h>

#define FILE_MODE "w"
#define FILE_PATH "gym.txt"
#define GYM_SIZE 3
#define NEWBORN_WORKOUT_HEART_RATE 220.0
#define NAME_SIZE 20
const double zonePercentages[3] = {0.6, 0.7, 0.8};


typedef struct member 
{
    char name[NAME_SIZE + 1];
    int age;
    float zone;
    double heartRate;
} Member;


void display(Member gym[], size_t size);

void sort(Member gym[], size_t size);

void summaryToStream(FILE *stream, Member gym[], size_t size);

void update(Member gym[], size_t size);

void write(const char *path, Member gym[], size_t size);


int main(void)
{
    Member staticMember = {"Static", 45, 3, 0};
    Member dynamicMember = {"Dynamic", 23, 1, 0};
    Member queueMember = {"Queue", 19, 2, 0};
    Member gym[GYM_SIZE] = {staticMember, dynamicMember, queueMember};

    sort(gym, GYM_SIZE);
    update(gym, GYM_SIZE);
    display(gym, GYM_SIZE);
    write(FILE_PATH, gym, GYM_SIZE);
    
    return 0;
} // main


void display(Member gym[], size_t size)
{
    summaryToStream(stdout, gym, size);
} // display

void sort(Member gym[], size_t size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (gym[j].age > gym[j+1].age) {
                Member temp = gym[j];
                gym[j] = gym[j+1];
                gym[j+1] = temp;
            }
        }
    }
} // sort

void summaryToStream(FILE *stream, Member gym[], size_t size)
{
    for (size_t i = 0; i < size; i++) {
        Member *currMember = &gym[i];

        fprintf(stream, "%-21s  %3d  %3.2f\n", currMember->name, currMember->age,
                currMember->heartRate);
    }
} // display

void update(Member gym[], size_t size)
{
    for (size_t i = 0; i < size; i++) {
        Member *currMember = &gym[i];

        double maxHeartRate = NEWBORN_WORKOUT_HEART_RATE - currMember->age;

        double workoutHeartRate = maxHeartRate * 
                                  zonePercentages[((int)currMember->zone) - 1];

        currMember->heartRate = workoutHeartRate;
    }
} // update

void write(const char *path, Member gym[], size_t size)
{
    FILE *output = fopen(path, FILE_MODE);

    summaryToStream(output, gym, size);

    fclose(output);
} // write
