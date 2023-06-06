#ifndef NW_LIB_TEMP_H
#define NW_LIB_TEMP_H

#include <stdio.h>

#define THERMAL_ZONE_0 0


typedef unsigned int THERMAL_ZONE_ID; 



float get_current_temperature(THERMAL_ZONE_ID tzid);

float * sample_t_seconds(THERMAL_ZONE_ID tzid, unsigned int sampling_time_ms, unsigned int duration_seconds);


#endif /*NW_LIB_TEMP_H*/