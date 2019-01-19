#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "candles.h"

static int t = numLines(fp);
static float opens[t];
static float highs[t];
static float lows[t];
static float closes[t];
static candlestick candles[t];
static int t5 = t/5
static int t15 = t/15
static int t30 = t/30
static int h = t/60
static int 4h = t/240
static int 1d = t/1440
static int 1w = t/10080
static int 1m = t/40320
static int 1y = t/483840
static candlestick m5candles[t5]
static candlestick m15candles[t15]
static candlestick hcandles[h]
static candlestick 4hcandles[4h]
static candlestick dcandles[1d]
static candlestick wcandles[1w]
static candlestick mcandles[1m]
static candlestick ycandles[1y]

int numLines(FILE * fif) {
	int count = 0;
	char c;
	for (c = getc(fif); c != EOF; c = getc(fif)) { 
        if (c == '\n') {// Increment count if this character is newline 
            count = count + 1; 
        };
    };
  
    // Close the file 
    fclose(fif);
    return count;
};

void createM1() {
	//m1stick m1;
    FILE * fp;
    //char * candle[];

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("EURUSD.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    fp = fopen("EURUSD.txt", "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read); = 54 bytes
        //printf("%s", line);
        candlestick m1; 
        int x = 0;
        int y = 0;
        int i = 0;
        char * pt;
        pt = strtok(line,",");
            while(pt != NULL){
                //printf("%s ", pt);
                switch(y%8) {
                    case 0:
                        m1.ticker = pt;
                    case 1:
                        m1.date = pt;
                    case 2:
                        m1.time = pt;
                    case 3:
                        m1.open = atof(pt);
                        opens[x] = m1.open;
                    case 4:
                        m1.high = atof(pt);
                        highs[x] = m1.high;
                    case 5:
                        m1.low = atof(pt);
                        lows[x] = m1.low;
                    case 6:
                        m1.close = atof(pt);
                        closes[x] = m1.close;
                    case 7:
                        m1.volume = atoi(pt);
                }
                y++;
                pt = strtok(NULL, ",");
        }        
        candles[x] = m1;
        x++;
    };


    fclose(fp);
    if (line)
        free(line);

    return candles;
};

void createM5() { 
	float m5high = 0;
	float m5low = 0;
	int x = 0; 
	candlestick m5;
	for(i = 0; i < t5; i++) {
		switch(i%5) {
			case 0:
				m5.open = candles[i].open;
				m5high = candles[i].high;
				m5low = candles[i].low
			case 4:
				m5high = fmaxf(m5high, highs[i-1]);
				m5low = fmaxf(m5low, lows[i-1]);
				m5.close = candles[i].close;
				m5.high = m5high;
				m5.low = m5low;
				m5.volume = 5;
				m5.ticker = "EURUSD";
				m5.date = candles[i].date;
				m5.time = candles[i].time;
				m5candles[x] = m5;
				x++;
			default:
				m5high = fmaxf(m5high, highs[i-1]);
				m5low = fmaxf(m5low, lows[i-1]);
		};
	};
}; 

void createM15() { 
	float m15high = 0;
	float m15low = 0;
	int x = 0;
	candlestick m15;
	for(i = 0; i < t5; i++) {
		switch(i%3) {
			case 0:
				m15.open = m5candles[i].open;
				m15high = m5candles[i].high;
				m15low = m5candles[i].low
			case 2:
				m15high = fmaxf(m15high, m5candles[i-1].high);
				m15low = fmaxf(m15low, m5candles[i-1].low);
				m15.close = m5candles[i].close;
				m15.high = m15high;
				m15.low = m15low;
				m15.volume = 15;
				m15.ticker = "EURUSD";
				m15.date = m5candles[i].date;
				m15.time = m5candles[i].time;
				m15candles[x] = m15;
				x++;
			default:
				m15high = fmaxf(m15high, m5candles[i-1].high);
				m15low = fmaxf(m15low, m5candles[i-1].low);
		};
	};
	return m15candles;
};

void createM30() { 
	float m30high = 0;
	float m30low = 0;
	int x = 0;
	candlestick m30;
	for(i = 0; i < t15; i++) {
		switch(i%2) {
			case 0:
				m30.open = m15candles[i].open;
				m30high = m15candles[i].high;
				m30low = m15candles[i].low
			case 1:
				m30high = fmaxf(m30high, m15candles[i-1].high);
				m30low = fmaxf(m30low, m15candles[i-1].low);
				m30.close = m5candles[i].close;
				m30.high = m15high;
				m30.low = m15low;
				m30.volume = 30;
				m30.ticker = "EURUSD";
				m30.date = m5candles[i].date;
				m30.time = m5candles[i].time;
				m30candles[x] = m15;
				x++;
			default:
				m30high = fmaxf(m30high, m15candles[i-1].high);
				m30low = fmaxf(m30low, m15candles[i-1].low);
		};
	};
	return m30candles;
};

void createH() { 
	float hhigh = 0;
	float hlow = 0;
	int x = 0;
	candlestick h;
	for(i = 0; i < t30; i++) {
		switch(i%2) {
			case 0:
				h.open = m30candles[i].open;
				hhigh = m30candles[i].high;
				hlow = m30candles[i].low
			case 1:
				hhigh = fmaxf(hhigh, m30candles[i-1].high);
				hlow = fmaxf(hlow, m30candles[i-1].low);
				h.close = m30candles[i].close;
				h.high = hhigh;
				h.low = hlow;
				h.volume = 60;
				h.ticker = "EURUSD";
				h.date = m30candles[i].date;
				h.time = m30candles[i].time;
				hcandles[x] = h;
				x++;
			default:
				m15high = fmaxf(m15high, m5candles[i-1].high);
				m15low = fmaxf(m15low, m5candles[i-1].low);
		};
	};
	return hcandles;
};

void createH4() { 
	float h4high = 0;
	float h4low = 0;
	int x = 0;
	candlestick h4;
	for(i = 0; i < h; i++) {
		switch(i%4) {
			case 0:
				h4.open = m5candles[i].open;
				h4high = m5candles[i].high;
				h4low = m5candles[i].low
			case 3:
				h4high = fmaxf(h4high, hcandles[i-1].high);
				h4low = fmaxf(h4low, hcandles[i-1].low);
				h4.close = hcandles[i].close;
				h4.high = hhigh;
				h4.low = hlow;
				h4.volume = 240;
				h4.ticker = "EURUSD";
				h4.date = hcandles[i].date;
				h4.time = hcandles[i].time;
				h4candles[x] = h;
				x++;
			default:
				h4high = fmaxf(h4high, hcandles[i-1].high);
				h4low = fmaxf(h4low, hcandles[i-1].low);
		};
	};
	return h4candles;
};

void createD() { 
	float dhigh = 0;
	float dlow = 0;
	int x = 0;
	candlestick d;
	for(i = 0; i < 4h; i++) {
		switch(i%6) {
			case 0:
				d.open = h4candles[i].open;
				dhigh = h4candles[i].high;
				dlow = h4candles[i].low
			case 5:
				dhigh = fmaxf(dhigh, h4candles[i-1].high);
				dlow = fmaxf(dlow, h4candles[i-1].low);
				d.close = h4candles[i].close;
				d.high = dhigh;
				d.low = dlow;
				d.volume = 1440;
				d.ticker = "EURUSD";
				d.date = h4candles[i].date;
				d.time = h4candles[i].time;
				dcandles[x] = d;
				x++;
			default:
				dhigh = fmaxf(dhigh, h4candles[i-1].high);
				dlow = fmaxf(dlow, h4candles[i-1].low);
		};
	};
	return dcandles;
};

void createW() { 
	float whigh = 0;
	float wlow = 0;
	int x = 0;
	candlestick w;
	for(i = 0; i < 1d; i++) {
		switch(i%7) {
			case 0:
				w.open = dcandles[i].open;
				whigh = dcandles[i].high;
				wlow = dcandles[i].low
			case 6:
				whigh = fmaxf(whigh, dcandles[i-1].high);
				wlow = fmaxf(wlow, dcandles[i-1].low);
				w.close = dcandles[i].close;
				w.high = whigh;
				w.low = wlow;
				w.volume = 10080;
				w.ticker = "EURUSD";
				w.date = dcandles[i].date;
				w.time = dcandles[i].time;
				wcandles[x] = w;
				x++;
			default:
				whigh = fmaxf(whigh, dcandles[i-1].high);
				wlow = fmaxf(wlow, dcandles[i-1].low);
		};
	};
	return wcandles;
};

void createM() { 
	float mhigh = 0;
	float mlow = 0;
	int x = 0;
	candlestick m;
	for(i = 0; i < 1w; i++) {
		switch(i%4) {
			case 0:
				m.open = wcandles[i].open;
				mhigh = wcandles[i].high;
				mlow = wcandles[i].low
			case 3:
				mhigh = fmaxf(mhigh, wcandles[i-1].high);
				mlow = fmaxf(mlow, wcandles[i-1].low);
				m.close = wcandles[i].close;
				m.high = mhigh;
				m.low = mlow;
				m.volume = 40320;
				m.ticker = "EURUSD";
				m.date = wcandles[i].date;
				m.time = wcandles[i].time;
				mcandles[x] = m;
				x++;
			default:
				mhigh = fmaxf(mhigh, wcandles[i-1].high);
				mlow = fmaxf(mlow, wcandles[i-1].low);
		};
	};
	return mcandles;
};

void createY() { 
	float yhigh = 0;
	float ylow = 0;
	int x = 0;
	candlestick y;
	for(i = 0; i < 1m; i++) {
		switch(i%12) {
			case 0:
				y.open = mcandles[i].open;
				yhigh = mcandles[i].high;
				ylow = mcandles[i].low
			case 11:
				yhigh = fmaxf(yhigh, mcandles[i-1].high);
				ylow = fmaxf(ylow, mcandles[i-1].low);
				y.close = ycandles[i].close;
				y.high = yhigh;
				y.low = ylow;
				y.volume = 483840;
				y.ticker = "EURUSD";
				y.date = mcandles[i].date;
				y.time = mcandles[i].time;
				ycandles[x] = y;
				x++;
			default:
				yhigh = fmaxf(yhigh, mcandles[i-1].high);
				ylow = fmaxf(ylow, mcandles[i-1].low);
                //printf("M5 %d, %s , %s, %s, %f , %f , %f , %f\n ", m5tick, m5candles[m5tick].ticker, m5candles[m5tick].date, m5candles[m5tick].time, m5candles[m5tick].open, m5candles[m5tick].high, m5candles[m5tick].low, m5candles[m5tick].close);
		};
	};
	return ycandles;
};




