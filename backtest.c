#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "candles.h"
#include "algor.h"


//<TICKER>,<DTYYYYMMDD>,<TIME>,<OPEN>,<HIGH>,<LOW>,<CLOSE>,<VOL>

#define _GNU_SOURCE
int timeframe;
int main(){
    printf("Initializing.....");
    createM1();
    createM5();
    createM15();
    createM30();
    createH();
    createH4();
    createD();
    createW();
    createM();
    createY();
    printf("done.");
    printf(
        "Please choose a timeframe from the list below:\n
        1: M1 (1 minute)\n
        2: M5 (5 minutes)\n
        3: M15 (15 minutes)\n
        4: M30 (30 minutes)\n
        5: 1H (hourly)\n
        6: 4H (4 hours)\n
        7: 1D (daily)\n
        8: 1W (weekly)\n
        9: 1M (monthly)\n
        0: 1Y (yearly)\n");
    while(!isdigit(fgets(timeframe, 16, stdin)) && timeframe >= 0 && timeframe <= 9){
        fgets(timeframe, 16, stdin);
    };
    printf("Starting bot...");
    switch(timeframe) {
        case 1: 
            rsi(candles[]);
        case 2: 
            rsi(m5candles[]);
        case 3: 
            rsi(m15candles[]);
        case 4: 
            rsi(m30candles[]);
        case 5: 
            rsi(hcandles[]);
        case 6: 
            rsi(4hcandles[]);
        case 7: 
            rsi(dcandles);
        case 8: 
            rsi(wcandles);
        case 9: 
            rsi(mcandles);
        case 0: 
            rsi(ycandles);

    }
};