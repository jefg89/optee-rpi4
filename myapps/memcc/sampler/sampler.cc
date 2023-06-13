#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include <unistd.h>


using namespace std;
using namespace std::chrono;

// from https://www.geeksforgeeks.org/extract-integers-string-c/
/// @brief Quick and dirty string to integer conversion. Return the first number sequence, without spaces, found in a string.
/// @param str Input string
/// @return First integer sequence in the string
unsigned int atoif(string str)
{
    stringstream ss;
    /* Storing the whole string into string stream */
    ss << str;
 
    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {
        /* extracting word by word from stream */
        ss >> temp;
 
        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
            return found;
    }
    return 0;
}


/// @brief Returns the current used memory in the system from /proc/meminfo
/// @return Current used memory 
unsigned int getUsedMem() {
//  auto start = high_resolution_clock::now();
    std::string content[4];
    std::ifstream memfile ("/proc/meminfo"); 
    unsigned int used, total, free, buffers , cached;
    if (memfile.is_open()) {
        std::string tmp;
        std::getline (memfile, tmp); //MemTotal
        content[0] = tmp;
        std::getline (memfile, tmp); //MemFree
        content[1] = tmp;
        std::getline (memfile, tmp); //MemAvailable
        //ignore this one
        std::getline (memfile, tmp); //Buffers
        content[2] = tmp;
        std::getline (memfile, tmp); //Cached
        content[3] = tmp;
        memfile.close();   
    }
    total = atoif(content[0]);
    free  = atoif(content[1]);
    buffers = atoif(content[2]);
    cached = atoif(content[3]);
    used = total - free - buffers - cached;
    return used;
}

// precise sleep method 
// from https://blat-blatnik.github.io/computerBear/making-accurate-sleep-function/
void preciseMilliSleep(double milli_seconds) {
    static double estimate = 1e-3;
    static double mean = 1e-3;
    static double m2 = 0;
    static int64_t count = 1;

    while (milli_seconds > estimate) {
        auto start = high_resolution_clock::now();
        this_thread::sleep_for(microseconds(100));
        auto end = high_resolution_clock::now();

        double observed = (end - start).count() / 1e6; //Diff in milliseconds
        milli_seconds -= observed;

        ++count;
        double delta = observed - mean;
        mean += delta / count;
        m2   += delta * (observed - mean);
        double stddev = sqrt(m2 / (count - 1));
        estimate = mean + stddev;
    }
    // spin lock
    auto start = high_resolution_clock::now();
    while ((high_resolution_clock::now() - start).count() / 1e6 < milli_seconds);
}


/// @brief Samples the memory usage at a specific sampling time
/// @param dest Destination array 
/// @param samp_t  Sampling time in ms
/// @param NUM_SAMPLES Number of samples to be saved
void sampleMemoryUsage(unsigned int * dest, double samp_t, size_t NUM_SAMPLES) {
    for (size_t i = 0; i < NUM_SAMPLES; i++){
        auto start = high_resolution_clock::now();
        dest[i] = getUsedMem();
        auto end = high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        double sleep_time = samp_t - elapsed.count();
        preciseMilliSleep(sleep_time);
    }
    
}



int main(int argc, char const *argv[])
{  
    double samp_t = atof(argv[1]);
    unsigned int dur = atoi(argv[2]);
    size_t NUM_SAMPLES = 1000*dur/samp_t;

    unsigned int *dest  =(unsigned int*) (malloc(NUM_SAMPLES*sizeof(unsigned int)));
    sampleMemoryUsage(dest, samp_t, NUM_SAMPLES);
   
    for (size_t i = 0; i < NUM_SAMPLES; i++)
        cout << dest[i] << endl;
    return 0;
}
