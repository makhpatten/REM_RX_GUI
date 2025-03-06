
#define int8 int
#define int32 long

typedef struct TIME_REC_STRUCT {
   unsigned int dateMonth,dateDay,dateYear,timeHour,timeMinute,timeSecond;
} TIME_REC_STRUCT;

void julianToTime(unsigned int32 *timeJulian,TIME_REC_STRUCT *timeVal);
void timeToJulian(TIME_REC_STRUCT *timeVal, unsigned int32 *timeJulian);
