#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "candles.h"

float profit = 0;
float b = 0;
float s = 0;

int vector(candlestick c) {
	float change;
	change = (c.open - c.close);
	switch(c.volume){
		case 483840:
			change = (change / 483840) * 100;
		case 40320:
			change = (change / 40320) * 100;
		case 10080:
			change = (change / 10080) * 100;
		case 1440:
			change = (change / 1440) * 100;
		case 240:
			change = (change / 240) * 100;
		case 60:
			change = (change / 60) * 100;
		case 30:
			change = (change / 30) * 100;
		case 15:
			change = (change / 15) * 100;
		case 5:
			change = (change / 5) * 100;
		default:
			change = (change / 1) * 100;

	};

	return change;

};

void BUY(candlestick c) {
	printf("Order: BUY Size: .05 Date: %d Time: %d Price: %f\n", c.date, c.time, c.close);
	b = 1;
	if(s = 1){
		profit = profit + .05 * abs(o - c.close);
		printf("Current Profit: %f\n", profit);
	};
};

void SELL(candlestick c) {
	printf("Order: SELL Size: .05 Date: %d Time: %d Price: %f\n", c.date, c.time, c.close);
	s = 1;
	if(b = 1){
		profit = profit + .05 * abs(o - c.close);
		printf("Current Profit: %f\n", profit);
	};
};
//Relative Strength Index

float rsi(candlestick c[]) {
	float avgU = 0;
	float avgD = 0;
	float r = 0;
	int i = 0;
	for(i = 0; i < sizeof(c)/sizeof(candlestick); i++) {
		float currentChange = vector(c[i]);
		switch(i%14) {
			case 13:
				r = 100 - (100 / (1 + ((avgU / 14) / (avgD / 14))))
			default:
				if(currentChange > 0){
					avgU = avgU + currentChange
				} else if(currentChange < 0) {
					avgD = avgD + abs(currentChange);
				};
				if(i > 13) {
					r = 100 - (100 / (1 + ((((avgU * 13) + currentChange) / 14) / (((avgU * 13) + currentChange) / 14)))); 
				};
		};
		if(r <= 30) {
			//buy
			o = c[i].close
			BUY()
		} else if(r >= 70) {
			//sell
			o = c[i].close
			SELL()
		}
	};
};