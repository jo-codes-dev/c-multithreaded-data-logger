#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "logger.h"

Data buffer[BUFFER_SIZE];
int count = 0;
int next_id = 1;
CRITICAL_SECTION lock;
/* Thread function  */
DWORD WINAPI sensorThread(LPVOID param);
DWORD WINAPI loggerThread(LPVOID param);
DWORD WINAPI monitorThread(LPVOID param);

DWORD WINAPI sensorThread(LPVOID param)
{
    while (1)
    {
        /* Generate random sensor value */
        float value = (rand() % 500) / 10.0f;   // e.g., 0.0 to 50.0

        /* Create data object */
        Data newData;
        newData.id = next_id++;
        newData.value = value;
        newData.timestamp = time(NULL);

        /* Enter critical section (lock) */
        EnterCriticalSection(&lock);

        if (count < BUFFER_SIZE)
        {
            buffer[count] = newData;
            count++;

            printf("[Sensor] ID:%d Value:%.2f added to buffer (count=%d)\n",
                   newData.id, newData.value, count);
        }
        else
        {
            printf("[Sensor] Buffer FULL! Data dropped\n");
        }

        /* Exit critical section */
        LeaveCriticalSection(&lock);

        /* Wait 1 second */
        Sleep(1000);
    }

    return 0;
}


DWORD WINAPI loggerThread(LPVOID param)
{
    FILE *fp = fopen("data.txt", "a");

    if (fp == NULL)
    {
        printf("[Logger] Error opening file!\n");
        return 0;
    }

    while (1)
    {
        EnterCriticalSection(&lock);

        if (count > 0)
        {
            /* Take first element from buffer */
            Data d = buffer[0];

            /* Shift remaining elements (queue behavior) */
            for (int i = 1; i < count; i++)
            {
                buffer[i - 1] = buffer[i];
            }

            count--;

            LeaveCriticalSection(&lock);

            /* Write to file */
            fprintf(fp, "ID:%d | Value:%.2f | Time:%lld\n",
                    d.id, d.value, (long long)d.timestamp);
            fflush(fp);

            printf("[Logger] Saved ID:%d to file (buffer count=%d)\n", d.id, count);
        }
        else
        {
            LeaveCriticalSection(&lock);
            printf("[Logger] Buffer empty...\n");
        }

        Sleep(2000);  // run every 2 seconds
    }

    fclose(fp);
    return 0;
}

DWORD WINAPI monitorThread(LPVOID param)
{
    while (1)
    {
        EnterCriticalSection(&lock);

        int current_count = count;   // read shared variable safely

        LeaveCriticalSection(&lock);

        printf("[Monitor] System Running | Buffer Count = %d\n", current_count);

        Sleep(3000);  // every 3 seconds
    }

    return 0;
}

int main() {
    /* Initialize lock */
    InitializeCriticalSection(&lock);

    HANDLE t1, t2, t3;

    /* Create threads */
    t1 = CreateThread(NULL, 0, sensorThread, NULL, 0, NULL);
    t2 = CreateThread(NULL, 0, loggerThread, NULL, 0, NULL);
    t3 = CreateThread(NULL, 0, monitorThread, NULL, 0, NULL);

    /* Wait forever (or until program closed) */
    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);
    WaitForSingleObject(t3, INFINITE);

    /* Cleanup */
    DeleteCriticalSection(&lock);

    return 0;
}