#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include "motor_ctrl.h"

#define CLIP_LU( x, l, u ) ( ((x) < (l)) ? (l) : ( ((x) > (u)) ? (u) : (x) ) )
#define TIMES 1

int main(int argc, char **argv)
{
    int i;
    motor_ctrl_data mc;
    cv::Vec2d cont_val( 0.0, 0.0 );

    fprintf(stdout, "start\n");
    
    if( mc_init( mc, "", 1 ) )
    {
        fprintf(stderr, "mc_init error\n");
        return 1;
    }

    fprintf(stdout, "LOW\n");
    mc_set_val( mc, 0, 0 );

    sleep(1);

    for(i = 0; i < TIMES; i++) {
    
        fprintf(stdout, "HIGH(+1.0)\n");
        cont_val(0) = 1.0;
        cont_val(1) = 1.0;
    
        cont_val(0) = CLIP_LU( cont_val(0), -1.0, 1.0 );
        cont_val(1) = CLIP_LU( cont_val(1), -1.0, 1.0 );
        mc_set_val( mc, cont_val(0), cont_val(1) );

        sleep(1);

        fprintf(stdout, "LOW\n");
        mc_set_val( mc, 0, 0 );

        sleep(1);
    
        fprintf(stdout, "HIGH(-1.0)\n");
        cont_val(0) = -1.0;
        cont_val(1) = -1.0;
    
        cont_val(0) = CLIP_LU( cont_val(0), -1.0, 1.0 );
        cont_val(1) = CLIP_LU( cont_val(1), -1.0, 1.0 );
        mc_set_val( mc, cont_val(0), cont_val(1) );

        sleep(1);

        fprintf(stdout, "LOW\n");
        mc_set_val( mc, 0, 0 );

        sleep(1);

    }
    
    mc_fina( mc );
    fprintf(stdout, "end\n");

    return 0;
}    
