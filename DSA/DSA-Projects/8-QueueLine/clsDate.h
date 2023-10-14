#pragma once //For Invoking Duplication
#pragma warning(disable : 4996) //For Current Date

#include <iostream>
#include<ctime>
#include<vector>
#include<assert.h>
#include<string>
#include"clsString.h"


//#define ll long long
using namespace std;

class clsDate
{
private:
    short _Day;
    short _Month;
    short _Year;


    short ReadPositiveNumber(string Message)
    {
        short Number = 0;
        do
        {
            cout << Message;
            cin >> Number;
        } while (Number <= 0);

        return Number;
    }


public:

    //First Constructor 
    //Default Constructor Initiate Date By The Current Date
    clsDate()
    {
        clsDate Current = clsDate::GetSystemDate();
        _Day = Current._Day;
        _Month = Current._Month;
        _Year = Current._Year;
    }

    //Get Current Date
    static clsDate GetSystemDate()
    {
        clsDate CurrentD(0, 0, 0);

        // get time now
        time_t t = time(0);
        tm* now = localtime(&t);

        CurrentD._Year = (short)now->tm_year + 1900;
        CurrentD._Month = (short)now->tm_mon + 1;
        CurrentD._Day = (short)now->tm_mday;

        return CurrentD;
    }

    //OverLoaded Constructor
    clsDate(string sDate)
    {
        vector<string>vDate = clsString::Split(sDate, "/");
        _Day = stoi(vDate[0]);
        _Month = stoi(vDate[1]);
        _Year = stoi(vDate[2]);

    }

    //OverLoaded Constructor
    clsDate(short Day, short Month, short Year)
    {
        _Day = Day;
        _Month = Month;
        _Year = Year;
    }

    clsDate(short DateOrderInYear, short Year)
    {
        clsDate Date = clsDate::DateFromDayOrderInYear(DateOrderInYear, Year);
        _Day = Date._Day;
        _Month = Date._Month;
        _Year = Date._Year; 
    }

    void SetDay(short Day)
    {
        _Day = Day;
    }

    short GetDay()
    {
        return _Day;
    }

       __declspec(property(get = GetDay, put = SetDay)) short Day;

       /// /////////////
    void SetMonth(short Month)
    {
        _Month = Month;
    }

    short GetMonth()
    {
        return _Month;
    }

       __declspec(property(get = GetMonth, put = SetMonth)) short Month;

       /////////////////////

    void SetYear(short Year)
    {
        _Year = Year;
    }

    short GetYear()
    {
        return _Year;
    }
      __declspec(property(get = GetYear, put = SetYear)) short Year;


      //////////////////////

      //////////////////////////
      // Is Leap Year ////
    static  bool IsLeapYear(short Year)
    {
        return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0);
    }

    bool IsLeapYear()
    {
        return IsLeapYear(_Year);
    }

    ////////////////////////////
    ////Number Of Days Hours Minutes Seconds  In A Year////

    static int NumberOfDaysInYear(short Year)
    {
        return (IsLeapYear(Year)) ? 366 : 365;
    }

    int NumberOfDaysInYear()
    {
        return NumberOfDaysInYear(_Year);
    }

    static int NumberOfHoursInYear(short Year)
    {
        return NumberOfDaysInYear(Year) * 24;
    }

    int NumberOfHoursInYear()
    {
        return NumberOfHoursInYear(_Year);
    }

    static int NumberOfMinutesInYear(short Year)
    {
        return NumberOfHoursInYear(Year) * 60;
    }

    int NumberOfMinutesInYear()
    {
        return NumberOfMinutesInYear(_Year);
    }

    static int NumberOfSecondsInYear(short Year)
    {
        return NumberOfMinutesInYear(Year) * 60;
    }

    int NumberOfSecondsInYear()
    {
        return NumberOfSecondsInYear(_Year);
    }
    //////////////////////////////////////

    // Tomorrow
    static clsDate GetTommorrow(clsDate Date)
    {
        switch (Date._Month)
        {
            //month's day = 30
        case 4:
        case 6:
        case 9:
        case 11:
            if (Date._Day == 30)
            {
                Date._Day = 1;
                Date._Month += 1;
            }
            else
                Date._Day += 1;
            break;
            /* ****************** */
            //month's day = 31
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
            if (Date._Day == 31)
            {
                Date._Day = 1;
                Date._Month += 1;
            }
            else
                Date._Day += 1;

            break;

        case 12:
            if (Date._Day == 31)
            {
                Date._Day = 1;
                Date._Month = 1;
                Date._Year += 1;
            }
            break;

        case 2:
            //29(leap year condition ??) || 28
            if ((Date._Year % 4 == 0 && Date._Year % 100 != 0) || (Date._Year % 400 == 0))
            {
                if (Date._Day == 29)
                {
                    Date._Day = 1;
                    Date._Month += 1;
                }
                else
                    Date._Day += 1;
            }
            else
            {
                if (Date._Day == 28)
                {
                    Date._Day = 1;
                    Date._Month += 1;
                }
                else
                    Date._Day += 1;
            }
        }
        return Date;
    }

    clsDate GetTommorrow()
    {
        return GetTommorrow(*this);
    }

    ///////////////
    ////Print Date///
     void Print()
    {
        cout <<DateToString() << endl;
    }

    ////////////////////
    ///////Number Of Days Hours Minutes Seconds  In A Month

    static short NumberOfDaysInAMonth(short Month, short Year)
    {
        short arrNumberOfDays[13] = { 0, 31,28,31,30,31,30,31,31,30,31,30,31 };
        return (Month == 2 && IsLeapYear(Year)) ? 29 : arrNumberOfDays[Month];
    }

    short NumberOfDaysInAMonth()
    {
        return NumberOfDaysInAMonth(_Month, _Year);
    }


    static short NumberOfHoursInAMonth(short Month, short Year)
    {
        return NumberOfDaysInAMonth(Month, Year) * 24;
    }

    short NumberOfHoursInAMonth()
    {
        return NumberOfHoursInAMonth(_Month, _Year);
    }

    static  int NumberOfMinutesInAMonth(short Month, short Year)
    {
        return NumberOfHoursInAMonth(Month, Year) * 60;
    }

    int NumberOfMinutesInAMonth()
    {
        return NumberOfMinutesInAMonth(_Month, _Year);
    }

    static int NumberOfSecondsInAMonth(short Month, short Year)
    {
        return NumberOfMinutesInAMonth(Month, Year) * 60;
    }

    int NumberOfSecondsInAMonth()
    {
        return NumberOfSecondsInAMonth(_Month, _Year);
    }

    ////////////////
    /////////// Day Name////
    //"Day Order [0 - 6] => [Sunday - Saturday] Considered To Gregorian Calender....";
    static short DayOfWeekOrder(clsDate Date)
    {
        short A, Y, M;
        A = (14 - Date._Month) / 12;
        Y = Date._Year - A;
        M = Date._Month + (12 * A) - 2;

        return (Date._Day + Y + (Y / 4) - (Y / 100) + (Y / 400) + ((31 * M) / 12)) % 7;

    }

    short DayOfWeekOrder()
    {
        return DayOfWeekOrder(*this);
    }

    static  string DayShortName(short Order)
    {
        string arrDayNames[7] = { "Sun" , "Mon" , "Tues" , "Wed" , "Thu" , "Fri" , "Sat" };
        return arrDayNames[Order];
    }


    string DayName()
    {
        return DayShortName(DayOfWeekOrder());
    }

    ///////////////////////////////
    //////Month Calender////////

    static string MonthShortName(short Order)
    {
        string arrMonthsNames[12] = { "Jan" , "Feb" , "Mar" , "Apr" , "May" , "Jun" , "Jul" ,"Aug" ,"Sep" , "Oct" , "Nov" ,"Des" };
        return arrMonthsNames[Order - 1];
    }

    string MonthShortName()
    {
        return MonthShortName(DayOfWeekOrder());
    }

    static void PrintMonthCalender(short Month, short Year)
    {
        short NumberOfDaysInACertainMonth = NumberOfDaysInAMonth(Month, Year);

        // Index of the day from 0 to 6
         //To Know Starting Day And Number Of Spaces 
        short Current = clsDate::DayOfWeekOrder(clsDate(1, Month, Year));

        NumberOfDaysInACertainMonth = NumberOfDaysInAMonth(Month, Year);

        // Print the current month name  
        printf("\n  _______________%s_______________\n\n",
            MonthShortName(Month).c_str());

        // Print the columns    

        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
        // Print appropriate spaces

        short i;
        for (i = 0; i < Current; i++)
            printf("     ");

        for (short j = 1; j <= NumberOfDaysInACertainMonth; j++)
        {
            printf("%5d", j);

            if (++i == 7)
            {
                i = 0;
                printf("\n");
            }
        }

        printf("\n  _________________________________\n");

    }

    void PrintMonthCalender()
    {
        PrintMonthCalender(_Month, _Year);
    }

    /////////////////////////////
    //////Year Calender////////

    void PrintYearCalender(short Year)
    {
        cout << "-----------------------------------------\n\n";
        cout << "\t Calendar - " << Year << endl << endl;
        cout << "-----------------------------------------\n\n";

        for (size_t Month = 1; Month <= 12; Month++)
        {
            PrintMonthCalender(Month, Year);
        }

    }

    /////////////////////////////
    /////////Days From The Beginning Of The Year/////////

    static short DaysFromTheBeginningOfTheYear(clsDate Date) // Month=5 
    {
        short TotalDays = 0;

        for (short M = 1; M <= Date._Month - 1; M++) // 1 + 2 + 3 + 4 +(Number Of Days In 5)
        {
            TotalDays += NumberOfDaysInAMonth(M, Date._Year);
        }
        TotalDays += Date._Day;

        return TotalDays;
    }

    short DaysFromTheBeginningOfTheYear()
    {
        return DaysFromTheBeginningOfTheYear(*this);
    }

    ////////////////////////////////
    /////////Take A Total Days And Convert It Back To Date

    static clsDate DateFromDayOrderInYear(short DateOrderInAYear, short Year)
    {
        //DateOrderInAYear = DaysFromTheBeginningOfTheYear(Day, Month, Year);
        clsDate Date;
        short RemainningDays = DateOrderInAYear;
        short MonthDays = 0;

        Date._Month = 1;
        Date._Year = Year;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date._Month, Year);

            if (RemainningDays > MonthDays)
            {
                RemainningDays -= MonthDays;
                Date._Month++;
            }
            else
            {
                Date._Day = RemainningDays;
                break;
            }
        }

        return Date;
    }

    clsDate DateFromDayOrderInYear()
    {
        return DateFromDayOrderInYear(DaysFromTheBeginningOfTheYear(), _Year);
    }

    //////////////////////////////////////////

    static clsDate DateAfterAddingDays(short Days, clsDate Date)
    {

        short RemainningDays = Days + DaysFromTheBeginningOfTheYear(clsDate(Date._Day, Date._Month, Date._Year));
        short MonthDays = 0;

        //I Will Counting From The Beginning Of The Year
        Date._Month = 1;

        while (true)
        {
            MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);

            if (RemainningDays > MonthDays)
            {
                RemainningDays -= MonthDays;
                Date._Month++;

                if (Date._Month > 12)
                {
                    Date._Month = 1;
                    Date._Year++;
                }

            }
            else
            {
                Date._Day = RemainningDays;
                break;
            }
        }

        return Date;

    }

    //I Made An Op OverLoding To Fasilitate The Code
    clsDate operator+(short NumberOfDays)
    {
        return DateAfterAddingDays(NumberOfDays, *this);
    }


    ////////////////////////////////////////
     ////////////

    static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
    {
        return  (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ? (Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ? Date1._Day < Date2._Day : false)) : false);
    }

    bool operator<(clsDate Date2)
    {
        return IsDate1BeforeDate2(*this, Date2);
    }

    ////////////////////////////

    static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2)
    {
        return  ((Date1._Year == Date2._Year) && (Date1._Month == Date2._Month) && (Date1._Day == Date2._Day));
    }

    bool operator==(clsDate Date2)
    {
        return IsDate1EqualToDate2(*this, Date2);
    }


    static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
    {
        return  (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2));
    }

    bool operator>(clsDate Date2)
    {
        return IsDate1AfterDate2(*this, Date2);
    }

    //In InputValidate Project I Need IsDateBetween() 
    
    static bool IsDateBetween(clsDate Date1, clsDate StartDate, clsDate EndDate)
    {
        return
            (((IsDate1AfterDate2(Date1, StartDate) || Date1 == StartDate) && (IsDate1BeforeDate2(Date1, EndDate) || Date1 == EndDate))
            ||
            ((IsDate1AfterDate2(Date1, EndDate) || Date1 == EndDate) && (IsDate1BeforeDate2(Date1, StartDate) || Date1 == StartDate)));//if He Swapped
    }

    bool IsMeBetween(clsDate StartDate, clsDate EndDate)
    {
        return IsDateBetween(*this, StartDate, EndDate);
    }

    //////////////////////////

    static clsDate ReadFullDate()
    {
        clsDate Date;

        cout << "Enter A Day: ";
        cin >> Date._Day;

        cout << "Enter A Month: ";
        cin >> Date._Month;

        cout << "Enter A Year: ";
        cin >> Date._Month;

        return Date;

    }

    friend istream& operator>>(istream& Input, clsDate& Date)
    {
        cout << "Enter A Day: ";
        Input >> Date._Day;

        cout << "Enter A Month: ";
        Input >> Date._Month;

        cout << "Enter A Year: ";
        Input >> Date._Year;

        return Input;
    }

    friend ostream& operator<<(ostream& Output, clsDate& Date)
    {
        Output << Date._Day << "/" << Date._Month << "/" << Date._Year << endl;
        return Output;
    }

    /////////////
     ////Last Day , Last Month

    static bool IsLastDayInMonth(clsDate Date)
    {
        return (Date._Day == NumberOfDaysInAMonth(Date._Month, Date._Year));
    }

    bool IsLastDayInMonth()
    {
        return (_Day == NumberOfDaysInAMonth(_Month, _Year));
    }

    static bool IsLastMonthInYear(short Month)
    {
        return (Month == 12);
    }

    bool IsLastMonthInYear()
    {
        return (_Month == 12);
    }

    ////////////////////
    /////////Increase Date By One Day

    static clsDate IncreaceDateByOneDay(clsDate& Date)
    {
        if (IsLastDayInMonth(Date) && IsLastMonthInYear(Date._Month))
        {
            Date._Day = 1;
            Date._Month = 1;
            Date._Year++;

        }

        else if (IsLastDayInMonth(Date))
        {
            Date._Day = 1;
            Date._Month++;
        }

        else
        {
            Date._Day++;
        }

        return Date;
    }

    void AddOneDay()
    {
          IncreaceDateByOneDay(*this);
    }
    ////////////////////

    //////////////////////////
    //////Diff In Days +,-

    ////////////////////////////////////////////////////////////////////////////////////////

    //Swap 2 Sturcture Objects
    static void SwapDates(clsDate& Date1, clsDate& Date2)
    {
        clsDate Temp;
        Temp._Day = Date1._Day;
        Temp._Month = Date1._Month;
        Temp._Year = Date1._Year;

        Date1._Day = Date2._Day;
        Date1._Month = Date2._Month;
        Date1._Year = Date2._Year;

        Date2._Day = Temp._Day;
        Date2._Month = Temp._Month;
        Date2._Year = Temp._Year;

    }

    void SwapDates(clsDate Date2)
    {
        SwapDates(*this, Date2);
    }

    static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
    {
        //this will take care of negative diff
        int Days = 0;
        short SawpFlagValue = 1;

        if (!IsDate1BeforeDate2(Date1, Date2))
        {
            //Swap Dates 
            SwapDates(Date1, Date2);
            SawpFlagValue = -1;

        }

        while (IsDate1BeforeDate2(Date1, Date2))
        {
            Days++;
            Date1 = IncreaceDateByOneDay(Date1);
        }

        return IncludeEndDay ? ++Days * SawpFlagValue : Days * SawpFlagValue;
    }

    int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
    {
        return GetDifferenceInDays(*this, Date2, IncludeEndDay);
    }

    static int CalculateMyAgeInDays(clsDate DateOfBirth)
    {
        return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
    }

    //above no need to have nonstatic function for the object because it does not depend on any data from it.


    /////////////////////////////////////////////////////////////////////////////

     //Increase Date By 1 Day

     //Make Static Functions For Outside Users

    static  void IncreaseDateByOneDay(clsDate& Date)
    {
        if (IsLastDayInMonth(Date) && IsLastMonthInYear(Date._Month))
        {
            Date._Day = 1;
            Date._Month = 1;
            Date._Year++;

        }



        else if (IsLastDayInMonth(Date))
        {
            Date._Day = 1;
            Date._Month++;
        }

        else
        {
            Date._Day++;
        }
    }

    void IncreaseDateByOneDay()
    {
        IncreaseDateByOneDay(*this);
    }

    //Increase Date By X Days
   static void IncreaseDateByXDays(short XDays, clsDate& Date)
    {
        for (short i = 1; i <= XDays; i++)
        {
            IncreaseDateByOneDay(Date);
        }
    }

   void IncreaseDateByXDays(short XDays)
   {
       IncreaseDateByXDays(XDays, *this);
   }

    static void IncreaseDateByOneWeek(clsDate& Date)
    {
        IncreaseDateByXDays(7, Date);
    }
    void IncreaseDateByOneWeek()
    {
        IncreaseDateByOneWeek(*this);
    }

    static void IncreaseDateByXWeeks(short NumberOfWeeks, clsDate& Date)
    {
        for (short i = 1; i <= NumberOfWeeks; i++)
        {
            IncreaseDateByOneWeek(Date);
        }
    }

    void IncreaseDateByXWeeks(short NumberOfWeeks)
    {
        IncreaseDateByXWeeks(NumberOfWeeks, *this);
    }

    static void IncreaseDateByOneMonth(clsDate& Date)///////////////////////////////////////////
    {

        if (Date._Month == 12)
        {
            Date._Month = 1;
            Date._Year++;
        }
        else
        {
            Date._Month++;
        }

        //last check day in date should not exceed max days in the current month
        // example if date is 31/1/2022 increasing one month should not be 31/2/2022, it should// be 28/2/2022
        short NumberOfDaysInACurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

        if (Date._Day > NumberOfDaysInACurrentMonth)
        {
            Date._Day = NumberOfDaysInACurrentMonth;
        }
    }

    void IncreaseDateByOneMonth( )
    {
        IncreaseDateByOneMonth(*this);
    }

    static void IncreaseDateByXMonths(short NumberOfMonths, clsDate& Date)
    {
        for (short i = 1; i <= NumberOfMonths; i++)
        {
            IncreaseDateByOneMonth(Date);
        }
    }

    void IncreaseDateByXMonths(short NumberOfMonths)
    {
        IncreaseDateByXMonths(NumberOfMonths, *this);
    }

    static void IncreaseDateByOneYear(clsDate& Date)
    {
        Date._Year++;
    }

    void IncreaseDateByOneYear()
    {
        IncreaseDateByOneYear(*this);
    }

 
    static void IncreaseDateByXYears(short Years, clsDate& Date)
    {

        Date._Year += Years;
    }

    void IncreaseDateByXYears(short Years)
    {
        IncreaseDateByXYears(Years, *this);
    }

    static void IncreaseDateByOneDecade(clsDate& Date)
    {
        Date._Year += 10;
    }

    void IncreaseDateByOneDecade()
    {
        IncreaseDateByOneDecade(*this);
    }

    static void IncreaseDateByXDecades(short NumberOfDecades, clsDate& Date)
    {
        Date._Year += NumberOfDecades * 10;/////// Decade = 10 Years
    }

    void IncreaseDateByXDecades(short NumberOfDecades)
    {
        IncreaseDateByXDecades(NumberOfDecades, *this);
    }


    static void IncreaseDateByOneCentury(clsDate& Date)
    {
        Date._Year += 100;
    }

    void IncreaseDateByOneCentury()
    {
        IncreaseDateByOneCentury(*this);
    }

    static void IncreaseDateByXCenturies(short Centries, clsDate& Date)
    {
        Date._Year += Centries * 100;
    }

    void IncreaseDateByXCenturies(short Centries)
    {
        IncreaseDateByXCenturies(Centries, *this);
    }

    static void IncreaseDateByOneMillennium(clsDate& Date)
    {
        Date._Year += 1000;

    }

    void IncreaseDateByOneMillennium()
    {
        IncreaseDateByOneMillennium(*this);
    }

    //////////////////////////////////////////////
    ///////// Decrease Function Are The Same Logic 
   ///////////////////////////////////////////////

  static  void DecreaseDateByOneDay(clsDate& Date)
    {
        if (Date._Day == 1 && Date._Month == 1)
        {
            Date._Year--;
            Date._Day = 31;
            Date._Month = 12;
        }

        else if (Date._Day == 1)
        {
            Date._Month--;

            Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
        }

        else
        {
            Date._Day--;
        }
    }

  void DecreaseDateByOneDay()
  {
      DecreaseDateByOneDay(*this);
  }

  static void DecreaseDateByXDays(short Days, clsDate& Date)
    {
        for (short i = 1; i <= Days; i++)
        {
            DecreaseDateByOneDay(Date);
        }
    }

  void DecreaseDateByXDays(short Days)
  {
      DecreaseDateByXDays(Days, *this);
  }

  static void DecreaseDateByOneWeek(clsDate& Date)
    {
        DecreaseDateByXDays(7, Date);
    }

  void DecreaseDateByOneWeek()
  {
      DecreaseDateByOneWeek(*this);
  }

  static void DecreaseDateByXWeeks(short Weeks, clsDate& Date)
    {
        for (short i = 1; i <= Weeks; i++)
        {
            DecreaseDateByOneWeek(Date);
        }
    }

  void DecreaseDateByXWeeks(short Weeks)
  {
      DecreaseDateByXWeeks(Weeks, *this);
  }

  static  void DecreaseDateByOneMonth(clsDate& Date)///////////////////////////////////////////
    {
        //Update Month And Year
        if (Date._Month == 1)
        {
            Date._Year--;
            Date._Month = 12;
        }
        else
        {
            Date._Month--;
        }

          short NumberOfDaysInACurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

        if (Date._Day > NumberOfDaysInACurrentMonth)
        {
            Date._Day = NumberOfDaysInACurrentMonth;
        }
    }

  void DecreaseDateByOneMonth()
  {
      DecreaseDateByOneMonth(*this);
  }

  static void DecreaseDateByXMonths(short Months, clsDate& Date)
    {
        for (short i = 1; i <= Months; i++)
        {
            DecreaseDateByOneMonth(Date);
        }
    }

  void DecreaseDateByXMonths(short Months)
  {
      DecreaseDateByXMonths(Months, *this);
  }

  static void DecreaseDateByOneYear(clsDate& Date)
    {
        Date._Year--;
    }
 
  void DecreaseDateByOneYear()
  {
      DecreaseDateByOneYear(*this);
  }

  static void DecreaseDateByXYears(short Years, clsDate& Date)
    {
        Date._Year -= Years;
    }

  void DecreaseDateByXYears(short Years)
  {
      DecreaseDateByXYears(Years, *this);
  }

  static void DecreaseDateByOneDecade(clsDate& Date)
    {
        Date._Year -= 10;
    }
  void DecreaseDateByOneDecade()
  {
      DecreaseDateByOneDecade(*this);
  }

  static void DecreaseDateByXDecadesFaster(short Decades, clsDate& Date)
    {
        Date._Year -= Decades * 10;/////// Decade = 10 Years
    }

  void DecreaseDateByXDecadesFaster(short Decades)
  {
      DecreaseDateByXDecadesFaster(Decades, *this);
  }

  static void DecreaseDateByOneCentury(clsDate& Date)
    {
        Date._Year -= 100;
    }

  void DecreaseDateByOneCentury()
  {
      DecreaseDateByOneCentury(*this);
  }

  static void DecreaseDateByXCenturies(short Centries, clsDate& Date)
    {
        Date._Year -= Centries * 100;
    }

  void DecreaseDateByXCenturies(short Centries)
  {
      DecreaseDateByXCenturies(Centries, *this);
  }

  static void DecreaseDateByOneMillennium(clsDate& Date)
    {
        Date._Year -= 1000;

    }
  void DecreaseDateByOneMillennium()
  {
       DecreaseDateByOneMillennium(*this);
  }

  /////////////////////////////////////////////////
  ///////////////////
  ////////////////////////////////////////////////


  static bool IsEndOfWeek(clsDate& Date)
  {
      return DayOfWeekOrder(Date) == 6; //Saturday
  }

  bool IsEndOfWeek()
  {
      return IsEndOfWeek(*this);
  }

  static bool IsItWeekEnd(clsDate& Date)
  {
      return DayOfWeekOrder(Date) == 5; //Friday
  }

  bool IsItWeekEnd()
  {
      return IsItWeekEnd(*this);
  }

  static bool IsItABussinussDay(clsDate& Date)
  {
      return !IsItWeekEnd(Date);
  }

  bool IsItABussinussDay()
  {
      return  IsItABussinussDay(*this);
  }

  static  short DaysUntillEndOfWeek(clsDate& Date)
  {

      return 6 - DayOfWeekOrder(Date);
  }


  short DaysUntillEndOfWeek()
  {
      return  DaysUntillEndOfWeek(*this);
  }

  static short DaysUntillEndOfMonth(clsDate& Date)
  {

      clsDate EndOfMonthDate;
      EndOfMonthDate._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
      EndOfMonthDate._Month = Date._Month;
      EndOfMonthDate._Year = Date._Year;

      return GetDifferenceInDays(Date, EndOfMonthDate, true);
  }
  short DaysUntillEndOfMonth()
  {
      return  DaysUntillEndOfMonth(*this);
  }


  static short DaysUntillEndOfYear(clsDate& Date)
  {

      clsDate EndOfYearDate;
      EndOfYearDate._Day = 31;
      EndOfYearDate._Month = 12;
      EndOfYearDate._Year = Date._Year;

      return GetDifferenceInDays(Date, EndOfYearDate, true);
  }

  short DaysUntillEndOfYear()
  {
      DaysUntillEndOfYear(*this);
  }

  
 

  static short CalculateActualVacations(clsDate& StartDate, clsDate& EndDate)
  {
      //WeekEnds Dosen't Calculate

      short DaysCount = 0;

      while (IsDate1BeforeDate2(StartDate, EndDate))
      {

          if (IsItABussinussDay(StartDate))
          {
              DaysCount++;
          }

          IncreaceDateByOneDay(StartDate);
      }

      return DaysCount;
  }

  short CalculateActualVacations(clsDate EndDate)
  {
      return CalculateActualVacations(*this, EndDate);
  }


  //////////////////////////////
  /////Calculate Vacations Return Date
  ////////////////////////////

  static clsDate CalculateEndOfVacationDate(clsDate StartDate, short VacationNumber)
  {
      //I Receieved StartDate By Value To Make A Copy From It ,Then Return It As An End Date  
      while (VacationNumber)
      {
          if (IsItABussinussDay(StartDate))
          {
              VacationNumber--;
          }

          IncreaceDateByOneDay(StartDate);

      }

      return StartDate;
  }

  enum enDateCompare { Before = -1, Equal = 0, After = 1 };

  static enDateCompare CompareDates(clsDate& Date1, clsDate& Date2)
  {
      if (IsDate1AfterDate2(Date1, Date2))
          return enDateCompare::After;

      else if (IsDate1EqualToDate2(Date1, Date2))
          return  enDateCompare::Equal;

      return enDateCompare::Before;
  }

  enDateCompare CompareDates(clsDate& Date2)
  {
      return CompareDates(*this, Date2);
  }

  //////////////////////////////
  

  static bool ValidateDay(const clsDate& Date)
  {
      return !(Date._Day<1 || Date._Day>NumberOfDaysInAMonth(Date._Month, Date._Year));
  }

  static bool ValidateMonth(short Month)
  {
      return !(Month < 1 || Month>12);
  }

  static bool ValidateYear(short Year)
  {
      return (Year > 0);
  }

 static bool IsAValidDate(const clsDate& Date)
  {
      return(ValidateDay(Date) && ValidateMonth(Date._Month) && ValidateYear(Date._Year));
  }
 bool IsValid()
 {
     return IsAValidDate(*this);
 }


 /// ////////////////////

  static clsDate StringToDate(string sDate)
 {
     vector<string>vDateRecord =clsString::Split(sDate, "/");
     //assert(vDateRecord.size() == 3);

     clsDate Date;
     Date._Day = stoi(vDateRecord[0]);
     Date._Month = stoi(vDateRecord[1]);
     Date._Year = stoi(vDateRecord[2]);

     return Date;

 }

 /* clsDate StringToDate(string sDate)
  {
      return StringToDate( sDate);
  }
  */


static string DateToString(clsDate Date)/////////////////////////////////Simple,simple
 {
     return to_string(Date._Day) + "/" + to_string(Date._Month) + "/" + to_string(Date._Year);
 }

string DateToString()
{
    return  DateToString(*this);
}


//Fotmat Date

static string ReplaceWordInString(string sBase, string StingToReplace, string ReplaceTo)
{
    short PosOfTarget = 0;

    while ((PosOfTarget = sBase.find(StingToReplace)) != std::string::npos)
    {
        //replace(From , Size , " ")
        sBase.replace(PosOfTarget, StingToReplace.length(), ReplaceTo);
    }

    return sBase;
}

static string FormateDate(clsDate Date, string DateFormate = "dd/mm/yyyy")
{
    string FormattedDateString = "";

    FormattedDateString = ReplaceWordInString(DateFormate, "dd", to_string(Date._Day));
    FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(Date._Month));
    FormattedDateString = ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date._Year));
                                                                                          
    return FormattedDateString;
}

string FormateDate( string DateFormate = "dd/mm/yyyy")
{
    return FormateDate(*this, DateFormate);
}


static clsDate GetBigDate(clsDate& Date1, clsDate& Date2)
{
    if (CompareDates(Date1, Date2) == enDateCompare::After || CompareDates(Date1, Date2) == enDateCompare::Equal)
        return Date1;

    else
        return Date2;
}

clsDate GetBigDate( clsDate& Date2) {
    return GetBigDate(*this, Date2);
}

static clsDate GetSmallDate(clsDate& Date1, clsDate& Date2)
{
    if (CompareDates(Date1, Date2) == enDateCompare::After || CompareDates(Date1, Date2) == enDateCompare::Equal)
        return Date2;

    else
        return Date1;
}

clsDate GetSmallDate(clsDate& Date2)
{
    return GetSmallDate(*this, Date2);
}


static string GetSystemDateTimeString()
{
    time_t t = time(0);  // get time now

    tm* now = localtime(&t);

     string sDate =to_string(now->tm_mday);
     sDate +="/" +to_string(now->tm_mon + 1);
     sDate += "/" + to_string(now->tm_year + 1900);

    string sTime = to_string(now->tm_hour);
    sTime += ":" + to_string(now->tm_min);
    sTime += ":" + to_string(now->tm_sec);

    return sDate+" - "+ sTime;
}



};
