#include "Job.h"

void Job::setSum()
{
        int temp = 0;
        for (int n : timesOnMachines) {
            temp += n;
        }
        sum = temp;
}
