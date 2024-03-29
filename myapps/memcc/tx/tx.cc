#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <thread>
#include <bitset>
#include <fstream>

#include "hamming-codec.h"

using namespace std;
using namespace std::chrono;

const int MEGABYTE = (1024*1024);
size_t SIZE_BYTES = (2 * MEGABYTE); // 



float zero_ms = 150;


int BIT_PULSE_COUNT = 2; 


int PACKAGE_BIT_COUNT = 4;


void sendOne();
void sendZero();



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

/**
 * Manipulate memory usage to pulse in signal (high)
 */
void pulse() {
    auto end = high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed;
    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < 1; i++){ //50 did something, 10 also, 5 also
        char* pBigArray  = (char*)malloc(SIZE_BYTES * sizeof(char));
        char* pDestArray = (char*)malloc(SIZE_BYTES * sizeof(char));
        memset(pBigArray,  0xA + i, SIZE_BYTES * sizeof(char));
        free(pBigArray);
        free(pDestArray);
    
    }
    

   
    end = high_resolution_clock::now();
    elapsed = end-start;
    cout << "Copied in  " << elapsed.count() << "ms" << endl;
    end = high_resolution_clock::now();
    elapsed = end-start;
    zero_ms = elapsed.count();
}

/**
 * Sleep to keep memory usage signal constant (low)
 */
void rest() {
    cout << "-- Sleeping -- " << endl;
    auto start2 = high_resolution_clock::now();
    preciseMilliSleep(zero_ms);
    auto end2 = high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed2 = end2-start2;
    cout << "Slept for: " << elapsed2.count() << "ms" << endl;
}

/**
 * @brief Send a specific binary string through the channel
 *
 * @param binaryString string to send
 */
void sendData(string binaryString) {
    //std::ofstream ofencoded ("samples/encoded.txt", std::ofstream::app); 
    uint32_t binStrLength = binaryString.length();

    // Calculate how many bits are left
    int modCount = binStrLength % PACKAGE_BIT_COUNT;

    if (modCount != 0) {
        cout << "-- WARNING: Data is not divisible by bit count --" << endl;
        cout << "Original: " << binaryString << " with length " << binStrLength << endl;
        cout << "Correcting... " << endl;
        // Correct number to be divisible by 4 by adding 0s to the left
        int bitsToAppend = PACKAGE_BIT_COUNT - modCount;

        for (int i = 0; i < bitsToAppend; i++) {
            binaryString = "0" + binaryString;
        }

        // Get new length, as it has changed from before
        binStrLength = binaryString.length();
        cout << "Corrected: " << binaryString << " with length " << binStrLength << endl;
    }

    // Define indexes
    string encodedData = "";
    unsigned int indexStart = 0;
    unsigned int indexEnd = indexStart + PACKAGE_BIT_COUNT;
    cout << "-- Encoding packages... --" << endl;

    while (indexEnd != (binStrLength + PACKAGE_BIT_COUNT)) {
        // Encode binary string with Hamming code
        string package = binaryString.substr(indexStart, PACKAGE_BIT_COUNT);
        cout << "Extracted package: " << package << " between pos " << indexStart << " and " << indexEnd << endl;
        uint64_t intData = stoi(package, 0, 2);
        string encodedPackage = hamming_codec::encode(intData, PACKAGE_BIT_COUNT);
        encodedPackage = "1" + encodedPackage;
        cout << "Encoded package as: " << encodedPackage << " with length " << encodedPackage.length() << endl;
        encodedData += encodedPackage;

        indexStart += PACKAGE_BIT_COUNT;
        indexEnd += PACKAGE_BIT_COUNT;
    }

    cout << "-- Done with package creation. Ready to send --" << endl;
    cout << "Encoded: " << encodedData << " with length " << encodedData.length() << endl;
    cout << "Original: " << binaryString << " with length " << binStrLength << endl;
    //ofencoded << encodedData << endl;

    // Rest to calibrate 0
    sendZero();

    // Analyze bit string and send it bit by bit
    cout << "-- Sending... --" << endl;
    preciseMilliSleep(100);
    for (string::size_type i = 0; i < encodedData.size(); i++) {
        // Convert char to int
        int num = encodedData[i] - '0';

        cout << "(" << i + 1 << "/" << encodedData.size() << ") " << endl;

        auto startBitSend = high_resolution_clock::now();
        if (num == 1) {
            cout << "Sending 1..." << endl;
            sendOne();
        } else {
            cout << "Sending 0..." << endl;
            sendZero();
        }
        auto endBitSend = high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsedBitSend = endBitSend-startBitSend;
        cout << "BIT SENT IN  " << elapsedBitSend.count() << "ms" << endl;
        zero_ms = elapsedBitSend.count();
    }
}

/**
 * @brief Sends a 1 through the usage covert chennel
 *
 */
void sendOne() {
    for (int i = 0; i < BIT_PULSE_COUNT; i++) {
        pulse();
        //rest();
    }
}

/**
 * @brief Sends a 0 through the memory usage covert channel
 *
 */
void sendZero() {
        rest();
}


int main(int argc, char const *argv[])
{
    auto start = high_resolution_clock::now();

    // Data to send
    //string data = "0100111001100001011101000111010101110010011001011110001010000000100110010111001100100000011001100110100101110010011100110111010000100000011001110111001001100101011001010110111000100000011010010111001100100000011001110110111101101100011001000010110000001010010010000110010101110010001000000110100001100001011100100110010001100101011100110111010000100000011010000111010101100101001000000111010001101111001000000110100001101111011011000110010000101110000010100100100001100101011100100010000001100101011000010111001001101100011110010010000001101100011001010110000101100110111000101000000010011001011100110010000001100001001000000110011001101100011011110111011101100101011100100011101100001010010000100111010101110100001000000110111101101110011011000111100100100000011100110110111100100000011000010110111000100000011010000110111101110101011100100010111000001010010101000110100001100101011011100010000001101100011001010110000101100110001000000111001101110101011000100111001101101001011001000110010101110011001000000111010001101111001000000110110001100101011000010110011000101110000010100101001101101111001000000100010101100100011001010110111000100000011100110110000101101110011010110010000001110100011011110010000001100111011100100110100101100101011001100010110000001010010100110110111100100000011001000110000101110111011011100010000001100111011011110110010101110011001000000110010001101111011101110110111000100000011101000110111100100000011001000110000101111001001011100000101001001110011011110111010001101000011010010110111001100111001000000110011101101111011011000110010000100000011000110110000101101110001000000111001101110100011000010111100100101110"; // test
    std::string data = std::bitset<8>(atoi(argv[1])).to_string(); // string conversion
    sendData(data);
    auto end = high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    cout << "DONE. Sent in  " << elapsed.count() << "ms" << endl;

    return 0;
}
