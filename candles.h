typedef struct CandleStick {
   char * ticker;
   char * date;
   char * time;
   float open;
   float high;
   float low;
   float close;
   int volume;
} candlestick;

extern float opens[];
extern float highs[];
extern float lows[];
extern float closes[];
extern candlestick candles[];
extern candlestick m15candles[];
extern candlestick hcandles[];
extern candlestick 4hcandles[];
extern candlestick dcandles[];
extern candlestick wcandles[];
extern candlestick mcandles[];
extern candlestick ycandles[];
int numLines(FILE * fif);
void createM5();
void createM15();
void createM30();
void createH();
void createH4();
void createD();
void createW();
void createM();
void createY();

