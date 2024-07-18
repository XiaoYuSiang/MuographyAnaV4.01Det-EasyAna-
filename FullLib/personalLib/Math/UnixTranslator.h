#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
//GMT+8
//2021/1/1-1609430400
Int_t Month2021[12]={31,59,90,120,151,181,212,243,273,304,334,365};
char MonthName[13][5]={
  "-","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"
};
Int_t UTtDGMT2021(Int_t t){//UnixTranslatortotalDayGMT2021
  return (t-1609430400)/86400;
}
Int_t UTMGMT2021(Int_t t){//UnixTranslatorMonthGMT2021
  Int_t dD = (t-1609430400)/86400;
  if(dD<Month2021[0]){
    return 1;
  }
  for(Int_t i=0;i<12;i++){
    if(dD-Month2021[11-i]>=0)  return (13-i);
  }
  throw;
}
Int_t UTDGMT2021(Int_t t){//UnixTranslatorDayGMT2021
  Int_t dD = (t-1609430400)/86400;
  if(dD<Month2021[0]){
    return dD;
  }
  for(Int_t i=0;i<12;i++){
    if(dD-Month2021[11-i]>=0)  return dD-Month2021[11-i]+1;
  }
  throw;
}
Int_t DUTGMT2021(Int_t d){//DaytoUnixTranslatorGMT2021
  return (1609430400+d*86400);
}
Int_t DUTGMT2021(Int_t m,Int_t d){//DaytoUnixTranslatorGMT2021
  //if (m==1) (1609430400+(d-1)*86400);
  return (1609430400+(Month2021[m-2]+d-1)*86400);
}
Int_t LDTDGMT2021(Int_t dlarge){//LargeDateToDateGMT2021
  if(dlarge<Month2021[0]){
    return dlarge;
  }
  for(Int_t i=0;i<12;i++){
    if(dlarge-Month2021[11-i]>=0){
      return dlarge-Month2021[11-i]+1;
    }
  }
  throw;
}

Int_t LDTMGMT2021(Int_t dlarge){//LargeDateToMonthGMT2021
  if(dlarge<Month2021[0]){
    return 1;
  }
  for(Int_t i=0;i<12;i++){
    if(dlarge-Month2021[11-i]>=0){
      return (13-i);
    }
  }
  throw;
}
//1609430400



void unixTimeToHumanReadable(long int seconds, Int_t &tYear, Int_t &tMonth, Int_t &tDate, Int_t &tHour, Int_t &tMinute, Int_t &tSecond, Int_t timeZone = +0) {

  // Save the time in Human
  // readable format
  string ans = "";

  // Number of days in month
  // in normal year
  Int_t daysOfMonth[] = { 31, 28, 31, 30, 31, 30,
			31, 31, 30, 31, 30, 31 };

  long int currYear, daysTillNow, extraTime,
    extraDays, index, date, month, hours,
    minutes, secondss, flag = 0;

  // Calculate total days unix time T
  seconds = seconds + timeZone * 60 * 60;
  daysTillNow = seconds / (24 * 60 * 60);
  extraTime = seconds % (24 * 60 * 60);
  currYear = 1970;

  // Calculating currrent year
  while (daysTillNow >= 365) {
    if (currYear % 400 == 0 || (currYear % 4 == 0 && currYear % 100 != 0)) {
      daysTillNow -= 366;
    }
    else {
      daysTillNow -= 365;
    }
    currYear += 1;
  }

  // Updating extradays because it
  // will give days till previous day
  // and we have include current day
  extraDays = daysTillNow + 1;

  if (currYear % 400 == 0
    || (currYear % 4 == 0 
    && currYear % 100 != 0)) flag = 1;
  // Calculating MONTH and DATE
  month = 0, index = 0;
  if (flag == 1) {
    while (true) {
      if (index == 1) {
        if (extraDays - 29 < 0) break;
        month += 1;
        extraDays -= 29;
      }else{
        if (extraDays - daysOfMonth[index%12]< 0) {
          break;
        } 
        month += 1;
        extraDays -= daysOfMonth[index%12];
      }
      index += 1;
    }
  }
  else {
    while (true) {
      if (extraDays- daysOfMonth[index%12]< 0) {
        break;
      }
      month += 1;
      extraDays -= daysOfMonth[index%12];
      index += 1;
    }
  }

  // Current Month
  if (extraDays > 0) {
    month += 1;
    date = extraDays;
  }else {
    if (month == 2 && flag == 1) date = 29;
    else date = daysOfMonth[month - 1];
  }

  // Calculating HH:MM:YYYY
  hours = extraTime / 3600;
  minutes = (extraTime % 3600) / 60;
  secondss = (extraTime % 3600) % 60;

  tYear   = (Int_t) currYear;
  tMonth  = (Int_t) month;
  tDate   = (Int_t) date;
  tHour   = (Int_t) hours;
  tMinute = (Int_t) minutes;
  tSecond = (Int_t) secondss;
  // Return the time
}

Long64_t YMDHmSZtoUT(const Int_t tYear=1970, const Int_t tMonth=1 , const Int_t tDate=1,const Int_t tHour = 0,const Int_t tMinute = 0,const Int_t tSecond = 0,const Int_t timeZone = +8){
  Int_t daysOfMonth[12] = {
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31 
  };

  long int currYear= 1970, daysTillNow =0;
  // cout<<tYear<<endl;
  for(int y=currYear; y<tYear; y++){
    if(y%400==0 || ( y%4==0 && y%100!=0 )) daysTillNow++;
  }
  // cout<<daysTillNow<<endl;
  
  daysTillNow += 365*(tYear-currYear);
  for(int m=0; m<tMonth-1; m++){
    daysTillNow += daysOfMonth[m];
    if((m>2)&&(tYear%400==0 || ( tYear%4==0 && tYear%100!=0 ))) daysTillNow++;
  }
  // cout<<daysTillNow<<endl;
  daysTillNow += tDate-1;
  Long64_t UT = ((daysTillNow*24+tHour - timeZone)*60+tMinute)*60+tSecond;
  // cout<<UT<<endl;
  
  return UT;
  
}