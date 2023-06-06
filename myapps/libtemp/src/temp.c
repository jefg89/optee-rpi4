#include <temp.h>
#include <stdlib.h>
#include <time.h>

float get_current_temperature(THERMAL_ZONE_ID tzid){
    FILE *fptr;
    char temp_str [7];
    fptr = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    fgets(temp_str, 7, fptr);
    float curr_temp = (atoi(temp_str)/1000.0);
    fclose(fptr);
    return curr_temp;

}

float * sample_t_seconds(THERMAL_ZONE_ID tzid, unsigned int sampling_time_ms, unsigned int duration_seconds) {
    int n_size = (1000 * duration_seconds/sampling_time_ms);
    float * temps = (float *) (malloc(n_size* sizeof(float)));
    
    
    for (size_t i = 0; i < n_size; i++){
        int  cont  = 0;
        temps[i] = get_current_temperature(THERMAL_ZONE_0);
        clock_t start = clock();
        while (cont){
            clock_t end = clock();
            float milli_seconds = (float)(end - start) / (1000 * CLOCKS_PER_SEC);
            cont = (milli_seconds >= sampling_time_ms);
        }   
  
    }
    
    


    return temps;
}