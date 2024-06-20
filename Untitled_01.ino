#include <LiquidCrystal.h>

LiquidCrystal lcd ( 13, 12 ,14 ,15 ,16 ,17 );
byte rowPins [] = { 7, 6, 5, 4 };
byte colPins [] = { 11, 10, 9, 8 };
const byte buzzerPin = 3;

int a, b;
boolean aPress, bPress;
int inputSwitch;
boolean cal;

int keys [ 4 ] [ 4 ] = 
{
  { 1, 2, 3, 11 },
  { 4, 5, 6, 12 },
  { 7, 8, 9, 13 },
  { 15, 0, 16, 14 }
};
/*
  11: +
  12: -
  13: *
  14: /
  15: CLS
  16: Enter
*/

void setup ()
{
  cal = true;
  aPress = false;
  bPress = false;
  inputSwitch = 1;
  a = 0;
  b = 0;

  for ( int i = 0; i < 4; i ++ )
  {
    pinMode ( rowPins [ i ], OUTPUT );
    digitalWrite ( rowPins [ i ], HIGH );

    pinMode ( colPins [ i ], INPUT );
  }

  pinMode ( buzzerPin, OUTPUT );

  Serial.begin ( 9600 );

  lcd.begin ( 16, 2 );
  lcd.cursor ();
  lcd.blink ();
  lcd.home ();
  lcd.print ( "1115107" );
  lcd.setCursor ( 0, 1 );
}

void loop ()
{
  for ( int i = 0; i < 4; i ++ )
  {
    digitalWrite ( rowPins [ i ], LOW );

    for ( int j = 0; j < 4; j ++ )
    {
      if ( digitalRead ( colPins [ j ] ) == LOW )
      {
        delay ( 20 );

        switch ( keys [ i ] [ j ] )
        {
          case 11:
            break;

          case 12:
            break;

          case 14:
            break;

          case 13: // *
            if ( cal )
            {
              tone ( buzzerPin, 1000, 200 );

              if ( aPress )
              {
                lcd.setCursor ( 1, 1 );
                lcd.print ( "*" );

                inputSwitch = 2;
              }

              else
              {
                lcdReset ();
                lcd.print ( "0" );

                cal = false;
              } 
            }

            break;

          case 15:  // CLR
            for ( int i = 0; i < 3; i ++ )
            {
              tone ( buzzerPin, 1000, 100 );
              delay ( 200 );
            }

            lcdReset ();
            btnStateReset ();

            inputSwitch = 1;
            cal = true;

            break;

          case 16: // Enter
            if ( cal )
            {
              tone ( buzzerPin, 1000, 1000 );

              if ( bPress )
              {
                lcd.setCursor ( 3, 1 );
                lcd.print ( "=" );
                lcd.print ( a * b );

                cal = false;
              }

              else
              {
                lcdReset ();
                lcd.print ( "0" );

                cal = false;
              }
            }

            break;

          default:
            if ( cal )
            {
              switch ( inputSwitch )
              {
                case 1:
                  a = keys [ i ] [ j ];

                  Serial.println ( a );
                  lcd.setCursor ( 0, 1 );
                  lcd.print ( a );

                  aPress = true;

                  break;

                case 2:
                  b = keys [ i ] [ j ];

                  Serial.println ( b );
                  lcd.setCursor ( 2, 1 );
                  lcd.print ( b );

                  bPress = true;

                  break;

                default:
                  break;

              }
            }

            break;
        }

        while ( digitalRead ( colPins [ j ] ) == LOW )
        {
          delay ( 1 );
        }

        delay ( 20 ); 
      }
    }

    digitalWrite ( rowPins [ i ], HIGH );
  }
}

void lcdReset ()
{
  lcd.clear ();
  lcd.home ();
  lcd.print ( "1115107" );
  lcd.setCursor ( 0, 1 );
}

void btnStateReset ()
{
  aPress = false;
  bPress = false;
}