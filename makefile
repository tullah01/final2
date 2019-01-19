all: backtest.o candles.o algor.o
	gcc backtest.o candles.o

backtest.o: backtest.c
	gcc -c backtest.c

candles.o: candles.c candles.h
	gcc -c candles.c

algor.o: algor.c algor.h
	gcc -c algor.c

run:
	./a.out

clean: 
	rm ./a.out
	rm *.o