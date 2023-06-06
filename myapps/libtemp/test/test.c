#include <stdio.h>
#include <temp.h>



int main(int argc, char const *argv[])
{
    printf("Hello world from test app \n");
    printf("Configuration: sampling time %s ms  \t duration %s s \n", argv[1], argv [2]);
    float * temps = sample_t_seconds(THERMAL_ZONE_0, (unsigned int) argv[1], (unsigned int)argv[2]);
    
    for (size_t i = 0; i < 10000/5; i++){
        printf("%f \n", temps [i]);
    }
    return 0;
}
