#include <sys/time.h>
#include <cstdlib>
#include <cstdint>
#include<iostream>
using namespace std;
static __always_inline uint64_t rdtsc()
{
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc"
                         : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}
class Timer
{
public:
    Timer()
    {
        total.tv_sec = total.tv_usec = 0;
        diff.tv_sec = diff.tv_usec = 0;
    }

    double duration()
    {
        double duration;

        duration = (total.tv_sec) * 1000000.0; // sec to us
        duration += (total.tv_usec);           // us

        return duration * 1000.0; //ns
    }

    void start()
    {
        gettimeofday(&t1, NULL);
    }

    void end()
    {
        gettimeofday(&t2, NULL);
        timersub(&t2, &t1, &diff);
        timeradd(&diff, &total, &total);
    }

    void reset()
    {
        total.tv_sec = total.tv_usec = 0;
        diff.tv_sec = diff.tv_usec = 0;
    }

    timeval t1, t2, diff;
    timeval total;
};
#define CPU_FREQUENCY 2.4 // 2.4 GHZ
class cpuCycleTimer
{
public:
    long long t1, t2, total;
    int count = 0;

    cpuCycleTimer()
    {
        reset();
    }
    void start()
    {
        t1 = rdtsc();
    }
    void end()
    {
        t2 = rdtsc();
        total += t2 - t1;
        count++;
    }
    void reset()
    {
        count = t1 = t2 = total = 0;
    }
    double duration()
    { // ns
        return total / CPU_FREQUENCY;
    }
};

int main()
{
    Timer mytimer;
    cpuCycleTimer cputimer;
    double a=0.344,b=0.4234;
    mytimer.start();
    // do some work
    for(int i=0;i<10000;i++)
    {
        a = a*b;
        b = b/a;
        a = a*b+b/a;
        b = b*b*b;
    }
    mytimer.end();
    cout<< "when using gettimeofday, consume " << mytimer.duration() << "ns" << endl;

    cputimer.start();
    // do some work
    for(int i=0;i<10000;i++)
    {
        a = a*b;
        b = b/a;
        a = a*b+b/a;
        b = b*b*b;
    }
    cputimer.end();
    cout<< "when using rdtsc, consume " << cputimer.duration() << "ns" << endl;
    return 0;
}