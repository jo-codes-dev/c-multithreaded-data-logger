#ifndef LOGGER_H
#define LOGGER_H

#include <windows.h>
#include <time.h>

/* Data structure to hold each sensor record */
typedef struct {
    int id;
    float value;
    time_t timestamp;
} Data;

/* Maximum size of shared buffer */
#define BUFFER_SIZE 10

/* Shared buffer (acts like a queue) */
extern Data buffer[BUFFER_SIZE];

/* Control variables */
extern int count;        // current number of elements in buffer
extern int next_id;      // auto-increment ID generator

/* Synchronization lock (mutex equivalent) */
extern CRITICAL_SECTION lock;

#endif