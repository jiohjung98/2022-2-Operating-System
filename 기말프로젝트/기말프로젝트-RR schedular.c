/* 레퍼런스 작성
https://www.javatpoint.com/round-robin-program-in-c
java point c tutorial : c programs
Round Robin Program in C */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
  int sum = 0, arrivalT[10], burstT[10], temp[10], quant, count = 0, NOP = 10, NOWP, wt = 0, tat = 0;
  float avg_wt, avg_tat;

  srand((unsigned)time(0));

  // Number of waiting Process, Number of Process
  NOWP = NOP;

  // Init processes
  for (int i = 0; i < NOP; i++)
  {
    arrivalT[i] = i;
    // assume : there is no process that has 0 burst time
    while (1)
    {
      int r = rand() % 20;
      burstT[i] = r;
      if (r > 0)
        break;
    }
    printf("Process %d => AT: %d, BT: %d\n", i, arrivalT[i], burstT[i]);

    // temporary burst time array for scheduling
    temp[i] = burstT[i];
  }
  printf("Random processes generated\n");
  printf("Time quantum: ");
  scanf("%d", &quant);

  printf("\n Process No. \t Arrival Time \t Burst Time \t TAT \t\t Waiting Time ");

  // execution
  int i = 0;
  while (NOWP != 0) // finish condition : all jobs done
  {
    if (temp[i] <= quant && temp[i] > 0)
    {
      // case : process can terminate in quantum time
      sum += temp[i];
      temp[i] = 0;

      // flag for process termination
      count = 1;
    }
    else if (temp[i] > 0)
    {
      // case : process cannot terminate in quantum time
      temp[i] = temp[i] - quant;
      sum = sum + quant;
    }

    if (temp[i] == 0 && count == 1)
    {
      // if process terminated
      NOWP--; // decrement the waiting process no.
      printf("\nProcess %d \t %d \t\t %d\t\t %d\t\t %d", i, arrivalT[i], burstT[i], sum - arrivalT[i], sum - arrivalT[i] - burstT[i]);

      // wt tat variables for calculate average value
      wt = wt + sum - arrivalT[i] - burstT[i];
      tat = tat + sum - arrivalT[i];
      count = 0;
    }

    if (i == NOP - 1)
    {
      // case : nth process used cpu, loop back to 1th process
      i = 0;
    }
    else if (arrivalT[i + 1] <= sum)
    {
      // case : next process is in queue
      i++;
    }
    else
    {
      // case : next process is not arrived yet, loop back to 1th process
      i = 0;
    }
  }

  avg_wt = wt * 1.0 / NOP;
  avg_tat = tat * 1.0 / NOP;
  printf("\n Average Turn Around Time: \t%f", avg_tat);
  printf("\n Average Waiting Time: \t%f", avg_wt);

  return 0;
}
