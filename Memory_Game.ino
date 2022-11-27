#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// Define custom bits for 'Up', 'Down', 'Left', and 'Right' arrows
byte upArrow[] = {
        B00100,
        B01110,
        B10101,
        B00100,
        B00100,
        B00100,
        B00100,
        B00100
};
/* The UP Arrow defined is as follows:
            ┌─┬─┬─┬─┬─┐
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │█│█│█│ │
            ├─┼─┼─┼─┼─┤
            │█│ │█│ │█│
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤ 
            │ │ │█│ │ │
            └─┴─┴─┴─┴─┘
*/

byte downArrow[] = {
        B00100,
        B00100,
        B00100,
        B00100,
        B00100,
        B10101,
        B01110,
        B00100
};
/* The DOWN Arrow defined is as follows:
            ┌─┬─┬─┬─┬─┐
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤ 
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │█│ │█│ │█│
            ├─┼─┼─┼─┼─┤
            │ │█│█│█│ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            └─┴─┴─┴─┴─┘
*/

byte leftArrow[] = {
        B00000,
        B00100,
        B01000,
        B11111,
        B01000,
        B00100,
        B00000,
        B00000
};
/* The LEFT Arrow defined is as follows:
            ┌─┬─┬─┬─┬─┐
            │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │█│ │ │ │
            ├─┼─┼─┼─┼─┤
            │█│█│█│█│█│
            ├─┼─┼─┼─┼─┤
            │ │█│ │ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤ 
            │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │
            └─┴─┴─┴─┴─┘
*/

byte rightArrow[] = {
        B00000,
        B00100,
        B00010,
        B11111,
        B00010,
        B00100,
        B00000,
        B00000
};
/* The RIGHT Arrow defined is as follows:
            ┌─┬─┬─┬─┬─┐
            │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │ │█│ │
            ├─┼─┼─┼─┼─┤
            │█│█│█│█│█│
            ├─┼─┼─┼─┼─┤
            │ │ │ │█│ │
            ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤ 
            │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │
            └─┴─┴─┴─┴─┘
*/



// Define custom characters for the Big Arrows //
byte bigUpArrowTopLeft[] = {
        B00000,
        B00000,
        B00000,
        B00001,
        B00010,
        B00100,
        B01111,
        B00000
};

byte bigUpArrowTopMiddle[] = {
        B00100,
        B01010,
        B10001,
        B00000,
        B00000,
        B00000,
        B10001,
        B10001
};

byte bigUpArrowTopRight[] = {
        B00000,
        B00000,
        B00000,
        B10000,
        B01000,
        B00100,
        B11110,
        B00000
};

byte bigUpArrowBottom[] = {
        B10001,
        B10001,
        B10001,
        B10001,
        B10001,
        B10001,
        B10001,
        B11111
};
/* The BIGUP Arrow defined is as follows:
            ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐
            │ │ │ │ │ │ │ │ │█│ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │█│ │█│ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │█│ │ │ │ │ │ │ │█│ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │█│ │ │ │ │ │ │ │ │ │█│ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │ │ │ │ │ │ │ │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │█│█│█│█│ │█│ │ │ │█│ │█│█│█│█│ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘
            ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│█│█│█│█│ │ │ │ │ │ │
            └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘
*/


byte bigDownArrowTop[] = {
        B11111,
        B10001,
        B10001,
        B10001,
        B10001,
        B10001,
        B10001,
        B10001
};

byte bigDownArrowBottomMiddle[] = {
        B10001,
        B10001,
        B00000,
        B00000,
        B00000,
        B10001,
        B01010,
        B00100
};

byte bigDownArrowBottomLeft[] = {
        B00000,
        B01111,
        B00100,
        B00010,
        B00001,
        B00000,
        B00000,
        B00000
};

byte bigDownArrowBottomRight[] = {
        B00000,
        B11110,
        B00100,
        B01000,
        B10000,
        B00000,
        B00000,
        B00000
};
/* The BIGDOWN Arrow defined is as follows:
            ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐
            │ │ │ │ │ │ │█│█│█│█│█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘
            ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │█│█│█│█│ │█│ │ │ │█│ │█│█│█│█│ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │█│ │ │ │ │ │ │ │ │ │ │ │█│ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │█│ │ │ │ │ │ │ │ │ │█│ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │█│ │ │ │ │ │ │ │█│ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │█│ │ │ │█│ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │█│ │█│ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │█│ │ │ │ │ │ │ │ │
            └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘
*/


byte bigLeftArrowBottomLeft[] = {
        B01000,
        B00101,
        B00011,
        B00001,
        B00000,
        B00000,
        B00000,
        B00000
};

byte bigLeftArrowBottomMiddle[] = {
        B00000,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

byte bigLeftArrowBottomRight[] = {
        B00001,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

byte bigLeftArrowTopRight[] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B00001,
        B00001
};

byte bigLeftArrowTopMiddle[] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B00000,
        B00000
};

byte bigLeftArrowTopLeft[] = {
        B00000,
        B00000,
        B00000,
        B00001,
        B00011,
        B00101,
        B01000,
        B10000
};
/* The BIGLEFT Arrow defined is as follows:
            ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │█│ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │█│█│ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │█│ │█│ │█│█│█│█│█│ │█│█│█│█│█│
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │█│ │ │ │ │ │ │ │ │ │ │ │ │ │ │█│
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │█│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │█│
            └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘
            ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐
            │ │█│ │ │ │ │ │ │ │ │ │ │ │ │ │ │█│
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │█│ │█│ │█│█│█│█│█│ │█│█│█│█│█│
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │█│█│ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │█│ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘
*/


byte bigRightArrowTopRight[] = {
        B00000,
        B00000,
        B00000,
        B10000,
        B11000,
        B10100,
        B00010,
        B00001
};

byte bigRightArrowTopMiddle[] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B00000,
        B00000
};

byte bigRightArrowTopLeft[] = {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B10000,
        B10000
};

byte bigRightArrowBottomLeft[] = {
        B10000,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

byte bigRightArrowBottomMiddle[] = {
        B00000,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00000
};

byte bigRightArrowBottomRight[] = {
        B00010,
        B10100,
        B11000,
        B10000,
        B00000,
        B00000,
        B00000,
        B00000
};
/* The BIGRIGHT Arrow defined is as follows:
            ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │█│ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │█│█│ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │█│█│█│█│█│ │█│█│█│█│█│ │█│ │█│ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │█│ │ │ │ │ │ │ │ │ │ │ │ │ │ │█│ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │█│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │█│
            └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘
            ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐ ┌─┬─┬─┬─┬─┐
            │█│ │ │ │ │ │ │ │ │ │ │ │ │ │ │█│ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │█│█│█│█│█│ │█│█│█│█│█│ │█│ │█│ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │█│█│ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │█│ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤ ├─┼─┼─┼─┼─┤
            │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
            └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘ └─┴─┴─┴─┴─┘
*/


// Definitions for the basic UP, DOWN, LEFT, and RIGHT arrows
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Definitions for the colours of the LCD backlight
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

// Declaring the default values of the game variables
int numberOfSymbols;  // The minimum number of symbols possible
int sequenceLength;   // The minimum sequence length
int delayTime;     // The default delay time. In future versions of the game, this may be changable
double timeLimit;  // The default time limit between entering the symbols

int maxSequenceLength = 10;
int minSequenceLength = 2;
int maxNumberOfSymbols = 4;
int minNumberOfSymbols = 2;
int minDelayTime = 200;
int maxDelayTime = 1000;
double minTimeLimit = 0.50;
double maxTimeLimit = 10.00;

int attemptNumber = 1;  // The number of attempts for a level is set to 1 by default when the game is first run
double numberOfSecsToComplete;
char *sequence;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// This is the setup method, which is first called when the program is run. Here, some of the ////////////
///////////////////////////////////////////// default settings are set /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    randomSeed(analogRead(0)); // This ensures that the random function works correctly every time the game is run

    Serial.begin(9600);

    lcd.begin(16, 2);
    lcd.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////// This method is effectively the main menu of the game, where the user can choose between //////////////
/////////////////////////////////////// entering story mode or practice mode ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
    // The number of seconds to complete a level and the number of retries of a level are reset to their default values when at the menu
    numberOfSecsToComplete = 0;
    attemptNumber = 1;
    lcd.setBacklight(WHITE);

    // The small UP and DOWN arrows are created to help with the user interface of the menu system
    lcd.createChar(UP, upArrow);
    lcd.createChar(DOWN, downArrow);

    bool mainMenuChoice = false;
    uint8_t buttons = lcd.readButtons();

    // Loop if a main menu choice has not been made
    if (!mainMenuChoice) {
        lcd.setCursor(0, 0);
        lcd.print("Story Mode");
        lcd.setCursor(0, 1);
        lcd.print("Practice Mode");

        lcd.setCursor(15, 0);
        lcd.write(UP);
        lcd.setCursor(15, 1);
        lcd.write(DOWN);

        if (buttons & BUTTON_UP) {
            playStoryMode();
            mainMenuChoice = true;
        }
        if (buttons & BUTTON_DOWN) {
            setupPracticeMode();
            mainMenuChoice = true;
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////// This method is responsible for setting up the game by getting input for the number of symbols, //////////
/////////////////////// the sequence length, and the time limit between entering each symbol ///////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setupPracticeMode() {
    numberOfSymbols = 2;    // The minimum number of symbols possible
    sequenceLength = 2;     // The minimum sequence length
    timeLimit = 2.50;       // The default time limit
    delayTime = 1000;       // The default delay time

    bool setNumberOfSymbols = false;
    bool setSequenceLength = false;
    bool setTimeLimit = false;
    bool setDelayTime = false;
    uint8_t buttons = lcd.readButtons();

    scrollDisplay("               Entering Practice Mode", 35, false, false);
    scrollDisplay("Press LEFT in the menu for help", 14, true, true);

    /////////////////////////////////////////
    ///// Setting the number of symbols /////
    /////////////////////////////////////////
    // Loop while the number of symbols is not set
    while (!setNumberOfSymbols) {
        buttons = lcd.readButtons();
        lcd.print("No. Symbols");
        lcd.setCursor(0, 1);
        lcd.print(numberOfSymbols);

        formatMenuArrows(numberOfSymbols, minNumberOfSymbols, maxNumberOfSymbols);
        listenForHelp(0);

        // If the UP button is pressed and the number of symbols is less than 4, increase the number of symbols by 1
        if (buttons & BUTTON_UP) {
            if (numberOfSymbols < maxNumberOfSymbols) {
                numberOfSymbols++;
                delay(150);
            }
        }

        // If the DOWN button is pressed and the number of symbols is greater than 2, decrease the number of symbols by 1
        if (buttons & BUTTON_DOWN) {
            if (numberOfSymbols > minNumberOfSymbols) {
                numberOfSymbols--;
                delay(150);
            }
        }

        // If the SELECT button is pressed then break out of the loop
        if (buttons & BUTTON_SELECT) {
            setNumberOfSymbols = true;
            delay(150);
        }
    }

    /////////////////////////////////////////
    ////// Setting the sequence length //////
    /////////////////////////////////////////
    lcd.clear();

    // Loop while the sequence length is not set
    while (!setSequenceLength) {
        buttons = lcd.readButtons();
        lcd.print("Sequence Length");
        lcd.setCursor(0, 1);
        lcd.print(sequenceLength);

        formatMenuArrows(sequenceLength, minSequenceLength, maxSequenceLength);
        listenForHelp(1);

        // If the UP button is pressed and the sequence length < 10, increase the sequence length by 1
        if (buttons & BUTTON_UP) {
            if (sequenceLength < maxSequenceLength) {
                sequenceLength++;
                delay(150);
            }
        }

        // If the DOWN button is pressed and the sequence length > 2, decrease the sequence length by 1
        if (buttons & BUTTON_DOWN) {
            if (sequenceLength > minSequenceLength) {
                sequenceLength--;
                delay(150);
                lcd.setCursor(0, 1); // These two lines clear the bottom line of the lcd in the case that the user has entered a sequence length of 10 and then wishes to decrease it.
                lcd.print("     "); // Without this, only the first digit would be cleared, and therefore 9 would show as 90, 8 would show as 80, and so on...
                lcd.setCursor(0, 0);
            }
        }

        // If the SELECT button is pressed then break out of the loop
        if (buttons & BUTTON_SELECT) {
            setSequenceLength = true;
            delay(150);
        }
    }

    /////////////////////////////////////////
    ///////// Setting the time limit ////////
    /////////////////////////////////////////
    lcd.clear();

    // Loop while the time delay is not set
    while (!setTimeLimit) {
        buttons = lcd.readButtons();
        lcd.print("Time Limit");
        lcd.setCursor(0, 1);
        lcd.print(timeLimit);

        formatMenuArrows(timeLimit, minTimeLimit, maxTimeLimit);
        listenForHelp(2);

        // If the UP button is pressed and the time limit < 10, increase the time limit by 0.5
        if (buttons & BUTTON_UP) {
            if (timeLimit < maxTimeLimit) {
                timeLimit += 0.5;
                delay(150);
            }
        }

        // If the DOWN button is pressed and the time limit > 1, decrease the time limit by 0.5
        if (buttons & BUTTON_DOWN) {
            if (timeLimit > minTimeLimit) {
                timeLimit -= 0.5;
                delay(150);
                lcd.setCursor(0, 1); // These two lines clear the bottom line of the lcd in the case that the user has entered a time limit of 10.00 and then wishes to decrease it.
                lcd.print("     "); // Without this, only the first digits would be cleared, and therefore 9.50 would show as 9.500, 9.00 would show as 9.000, and so on...
                lcd.setCursor(0, 0);
            }
        }

        // If the SELECT button is pressed then break out of the loop
        if (buttons & BUTTON_SELECT) {
            setTimeLimit = true;
            delay(150);
        }
    }

    /////////////////////////////////////////
    ///////// Setting the delay time ////////
    /////////////////////////////////////////
    lcd.clear();

    // Loop while the time delay is not set
    while (!setDelayTime) {
        buttons = lcd.readButtons();
        lcd.print("Delay Time");
        lcd.setCursor(0, 1);
        lcd.print(delayTime / 1000.00);

        formatMenuArrows(delayTime, minDelayTime, maxDelayTime);
        listenForHelp(3);

        // If the UP button is pressed and the delay time < 1000, increase the delay time by 50
        if (buttons & BUTTON_UP) {
            if (delayTime < maxDelayTime) {
                delayTime += 50;
                delay(150);
            }
        }

        // If the DOWN button is pressed and the delay time > 200, decrease the delay time by 50
        if (buttons & BUTTON_DOWN) {
            if (delayTime > minDelayTime) {
                delayTime -= 50;
                delay(150);
            }
        }

        // If the SELECT button is pressed then break out of the loop
        if (buttons & BUTTON_SELECT) {
            setDelayTime = true;
            delay(300);
        }
    }
    startPracticeMode();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////// This method is responsible for initialising practice mode. It then checks if the inputted answer /////////
///////////////////// to a level is correct, and acts accordingly based on the different cases /////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void startPracticeMode() {
    generateSequence();
    outputSequence();

    // If playPracticeMode() returns true, and hence the correct sequence has been entered, call levelCorrect()
    if (playLevel()) {
        levelCorrect();
    }
    // If playPracticeMode() returns false, then the user has failed the level
    else {
        levelWrong();
    }

    free(sequence);
    delay(8000);
    lcd.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////// This method is responsible for generating the random sequence of symbols, based on the inputted //////////
///////////////////////////// values for the sequence length and the number of symbols /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void generateSequence() {
    // This allocates some space in memory for the size of the sequence
    char *createdSequence = (char *) malloc(sequenceLength);

    // Loop for the length of the sequence number of times
    for (int i = 0; i < sequenceLength; i++) {
        // Generate a random number between 0 and the number of symbols set, and add it to the sequence
        createdSequence[i] = (random(0, numberOfSymbols));
    }
    sequence = createdSequence;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////// This method is responsible for outputting the generated symbol sequence to the LCD screen ////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void outputSequence() {
    lcd.clear();

    // Loop through the sequence
    for (int i = 0; i < sequenceLength; i++) {
        lcd.setBacklight(WHITE);

        // These 4 IF ELSE blocks check the current value of the sequence, and create the corresponding arrow
        if (sequence[i] == UP) {
            createBigUpArrow();
        } else if (sequence[i] == DOWN) {
            createBigDownArrow();
        } else if (sequence[i] == LEFT) {
            createBigLeftArrow();
        } else {
            createBigRightArrow();
        }

        delay(delayTime);
        lcd.clear();
        lcd.setBacklight(TEAL);
        delay(250);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////// This method is responsible for getting user input for the symbol sequence and validating if the //////////
//////////////////////////////////////////////// sequence is correct ///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool playLevel() {
    int numberOfInputSymbols = 0;
    double currentMillis = 0.00;
    bool validSequence = false;
    uint8_t buttons = lcd.readButtons();

    // This allocates some space in memory for the size of the input sequence
    char *inputSequence = (char *) malloc(sequenceLength);

    lcd.setBacklight(WHITE);
    scrollDisplay("Enter the sequence", 16, true, false);

    // Loop until the user has inputted as many characters as the sequence length
    while (numberOfInputSymbols < sequenceLength) {
        buttons = lcd.readButtons();

        // If the time limit has been used up, inform the user that they have failed the level as they have run out of time
        if (timeLimit - (currentMillis / 1000.00) == 0.00) {
            lcd.setBacklight(RED);
            scrollDisplay("You ran out of time!", 3, true, true);
            return false;
        }
        // In the other case that the user has not run out of time, read the button input
        else {
            displayCountdownToLCD(currentMillis);
            // Increment the current milliseconds by 50 (0.05 seconds) and delay for this duration of time too
            currentMillis += 50;
            delay(50);


            // If the UP button is pressed, perform the following actions
            if (buttons & BUTTON_UP) {
                numberOfSecsToComplete += (currentMillis / 1000.0);  // Update the value of numberOfSecsToComplete
                inputSequence[numberOfInputSymbols] = UP;  // Add the value of the UP symbol (0) to the input sequence
                numberOfInputSymbols++;   // Increment the number of symbols inputted by 1
                deleteBigCharacter();     // Remove the current character from the LCD
                createBigUpArrow();       // Output the big arrow to the LCD
                currentMillis = 0;
                delay(150);
            }
            // If the DOWN button is pressed, perform the following actions
            if (buttons & BUTTON_DOWN) {
                numberOfSecsToComplete += (currentMillis / 1000.0);
                inputSequence[numberOfInputSymbols] = DOWN;
                numberOfInputSymbols++;
                deleteBigCharacter();
                createBigDownArrow();
                currentMillis = 0;
                delay(150);
            }
            // If the LEFT button is pressed, perform the following actions
            if (buttons & BUTTON_LEFT) {
                numberOfSecsToComplete += (currentMillis / 1000.0);
                inputSequence[numberOfInputSymbols] = LEFT;
                numberOfInputSymbols++;
                deleteBigCharacter();
                createBigLeftArrow();
                currentMillis = 0;
                delay(150);
            }
            // If the RIGHT button is pressed, perform the following actions
            if (buttons & BUTTON_RIGHT) {
                numberOfSecsToComplete += (currentMillis / 1000.0);
                inputSequence[numberOfInputSymbols] = RIGHT;
                numberOfInputSymbols++;
                deleteBigCharacter();
                createBigRightArrow();
                currentMillis = 0;
                delay(150);
            }
        }
    }
    
    // Validate if the input sequence is equal to the original symbol sequence
    for (int i = 0; i < sequenceLength; i++) {
        if (sequence[i] != inputSequence[i]) {
            validSequence = false;
            return false;
        } else {
            validSequence = true;
        }
    }
    free(inputSequence);

    return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////// This method is responsible for acting accordingly if the user got the symbol sequence correct ///////////
////////////////////// and outputting the relevant information about their attempt to the LCD //////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void levelCorrect() {
    numberOfSecsToComplete = numberOfSecsToComplete - (sequenceLength * 0.1);
    /* Because of the delay(100) to ensure the clock works correctly, the sequence length multiplied by the equivalent of delay(100), so 0.1, is required to be subtracted. */
    /* Without this, numberOfSecsToComplete would be too large. */
    /* For example, if the sequence length is 2, and the user takes 0.5 seconds on each symbol, the time to complete should be 1 second, but is calculated to be 1.2 seconds. */
    /* Hence, this line would subtract 2 * 0.1 = 0.2 from this value to ensure that the numberOfSecsToComplete is calculated correctly */

    lcd.clear();
    lcd.setBacklight(GREEN);
    lcd.print("Correct");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("It took you...");
    delay(1000);
    lcd.clear();

    lcd.print(numberOfSecsToComplete);
    lcd.print(" seconds &");
    lcd.setCursor(0, 1);
    lcd.print(attemptNumber);
    if (attemptNumber == 1) {
        lcd.print(" attempt");
    } else {
        lcd.print(" attempts");
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////// This method is responsible for handling what happens if the user gets a level incorrect. It is //////////
////////////////////// responsible for counting the number of retries and acting accordingly ///////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void levelWrong() {
    bool retryLevelCorrect = false;
    attemptNumber = 1;

    lcd.clear();

    // Loop while the retry limit has not been met
    while (attemptNumber < 3) {
        numberOfSecsToComplete = 0;
        lcd.setBacklight(RED);

        if (askRetryLevel()) {
            lcd.clear();
            outputSequence();
            if (playLevel()) {
                levelCorrect();
                retryLevelCorrect = true;
                break;
            }
        } else {
            break;
        }
    }

    if (!retryLevelCorrect) {
        lcd.setBacklight(RED);
        if (attemptNumber >= 3) {
            scrollDisplay("You have used all 3 of your attempts.", 19, true, true);
        }
        displayCorrectSequence();
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////// This method is responsible for getting user input for if the user would like to retry a level ///////////
////////////////////////////// in the case that they got the symbol sequence incorrect /////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool askRetryLevel() {
    bool setRetryLevel = false;
    bool retryLevel = false;
    uint8_t buttons = lcd.readButtons();

    scrollDisplay("Wrong. Would you like to retry?", 14, true, true);
    scrollDisplay("Press UP for Yes, or DOWN for No.", 16, true, true);

    lcd.createChar(UP, upArrow);
    lcd.createChar(DOWN, downArrow);

    lcd.print("YES");
    lcd.setCursor(0,1);
    lcd.print("NO");
    lcd.setCursor(15,0);
    lcd.write(UP);
    lcd.setCursor(15,1);
    lcd.write(DOWN);

    while (!setRetryLevel) {
        buttons = lcd.readButtons();
        if (buttons & BUTTON_UP) {
            retryLevel = true;
            setRetryLevel = true;
            attemptNumber++;
            delay(250);
        }
        if (buttons & BUTTON_DOWN) {
            retryLevel = false;
            setRetryLevel = true;
            delay(250);
        }
    }

    return retryLevel;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////// This method is responsible for outputting the correct sequence to the screen if the user gets the /////////
////////////////////////////////////////////////// level incorrect /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayCorrectSequence() {
    lcd.createChar(UP, upArrow);
    lcd.createChar(DOWN, downArrow);
    lcd.createChar(LEFT, leftArrow);
    lcd.createChar(RIGHT, rightArrow);

    lcd.setBacklight(RED);

    scrollDisplay("The correct sequence was: ", 8, true, true);

    lcd.print("Correct Sequence");
    lcd.setCursor(0, 1);
    for (int i = 0; i < sequenceLength; i++) {
        lcd.print(sequence[i]);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// This method is responsible for scrolling text across the screen for a duration of time. It ////////////
///////////////////////////////// takes the text and scroll duration as parameters /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void scrollDisplay(String textToScroll, int scrollTime, bool delayAtStart, bool delayAtEnd) {
    lcd.clear();
    lcd.print(textToScroll);
    if (delayAtStart) {
        delay(1000);
    }

    for (int i = 0; i <= scrollTime; i++) {
        lcd.scrollDisplayLeft();
        delay(250);
    }

    if (delayAtEnd) {
        delay(1000);
    }
    lcd.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// This method is responsible for formatting the menu arrows correctly so that the up and down ///////////
////////////////////// arrows display correctly on the screen based on the actions available ///////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void formatMenuArrows(int variable, int min, int max) {
    // These 3 IF ELSE blocks format the up and down arrows depending upon whether the user can increase or decrease the number of symbols
    if (variable == min) {
        lcd.setCursor(15, 0);
        lcd.write(UP);
        lcd.setCursor(15, 1);
        lcd.print(" ");
    } else if (variable == max) {
        lcd.setCursor(15, 0);
        lcd.print(" ");
        lcd.setCursor(15, 1);
        lcd.write(DOWN);
    } else {
        lcd.setCursor(15, 0);
        lcd.write(UP);
        lcd.setCursor(15, 1);
        lcd.write(DOWN);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// This method is responsible for listening for a left button press (help in the menu screen) ////////////
///////////////////////////////// and outputs the correct help message accordingly /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void listenForHelp(int menuOption) {
    uint8_t buttons = lcd.readButtons();
    if (buttons & BUTTON_LEFT) {
        lcd.setBacklight(YELLOW);
        switch (menuOption) {
            case 0:
                scrollDisplay("This is the number of different symbols", 22, true, true);
                scrollDisplay("It can be between 2 and 4", 8, true, true);
                break;
            case 1:
                scrollDisplay("This is the total number of symbols", 18, true, true);
                scrollDisplay("It can be between 2 and 10", 9, true, true);
                break;
            case 2:
                scrollDisplay("The time you have to enter the symbol", 20, true, true);
                scrollDisplay("It can be between 0.50 and 10.00", 15, true, true);
                break;
            case 3:
                scrollDisplay("The time each symbol is shown for", 16, true, true);
                scrollDisplay("It can be between 0.20 and 1.00", 14, true, true);
                break;
        }
        lcd.setBacklight(WHITE);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////// This method is responsible for displaying the countdown clock to the LCD /////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayCountdownToLCD(double currentMillis) {
    // Calculate the number of seconds taken by the user
    double secs = currentMillis / 1000.00;
    lcd.setCursor(12, 0);
    // Output the number of seconds remaining, to 2 decimal places
    lcd.print(timeLimit - secs, 2);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// This method is responsible for deleting a big character from the LCD ///////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void deleteBigCharacter() {
    lcd.setCursor(0, 0);
    lcd.print("        ");
    lcd.setCursor(0, 1);
    lcd.print("        ");
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////// This method is responsible for creating the relevent characters for a big up arrow and //////////////
////////////////////////////////////// outputting these characters to the LCD //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createBigUpArrow() {
    lcd.createChar(0, bigUpArrowTopLeft);
    lcd.createChar(1, bigUpArrowTopMiddle);
    lcd.createChar(2, bigUpArrowTopRight);
    lcd.createChar(3, bigUpArrowBottom);

    lcd.setCursor(0, 0);
    lcd.write(0);
    lcd.setCursor(1, 0);
    lcd.write(1);
    lcd.setCursor(2, 0);
    lcd.write(2);
    lcd.setCursor(1, 1);
    lcd.write(3);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////// This method is responsible for creating the relevent characters for a big down arrow and /////////////
////////////////////////////////////// outputting these characters to the LCD //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createBigDownArrow() {
    lcd.createChar(0, bigDownArrowTop);
    lcd.createChar(1, bigDownArrowBottomLeft);
    lcd.createChar(2, bigDownArrowBottomMiddle);
    lcd.createChar(3, bigDownArrowBottomRight);

    lcd.setCursor(1, 0);
    lcd.write(0);
    lcd.setCursor(0, 1);
    lcd.write(1);
    lcd.setCursor(1, 1);
    lcd.write(2);
    lcd.setCursor(2, 1);
    lcd.write(3);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////// This method is responsible for creating the relevant characters for a big left arrow and /////////////
////////////////////////////////////// outputting these characters to the LCD //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createBigLeftArrow() {
    lcd.createChar(0, bigLeftArrowTopLeft);
    lcd.createChar(1, bigLeftArrowTopMiddle);
    lcd.createChar(2, bigLeftArrowTopRight);
    lcd.createChar(3, bigLeftArrowBottomLeft);
    lcd.createChar(4, bigLeftArrowBottomMiddle);
    lcd.createChar(5, bigLeftArrowBottomRight);

    lcd.setCursor(0, 0);
    lcd.write(0);
    lcd.setCursor(1, 0);
    lcd.write(1);
    lcd.setCursor(2, 0);
    lcd.write(2);
    lcd.setCursor(0, 1);
    lcd.write(3);
    lcd.setCursor(1, 1);
    lcd.write(4);
    lcd.setCursor(2, 1);
    lcd.write(5);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////// This method is responsible for creating the relevant characters for a big right arrow and ////////////
////////////////////////////////////// outputting these characters to the LCD //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createBigRightArrow() {
    lcd.createChar(0, bigRightArrowTopLeft);
    lcd.createChar(1, bigRightArrowTopMiddle);
    lcd.createChar(2, bigRightArrowTopRight);
    lcd.createChar(3, bigRightArrowBottomLeft);
    lcd.createChar(4, bigRightArrowBottomMiddle);
    lcd.createChar(5, bigRightArrowBottomRight);

    lcd.setCursor(0, 0);
    lcd.write(0);
    lcd.setCursor(1, 0);
    lcd.write(1);
    lcd.setCursor(2, 0);
    lcd.write(2);
    lcd.setCursor(0, 1);
    lcd.write(3);
    lcd.setCursor(1, 1);
    lcd.write(4);
    lcd.setCursor(2, 1);
    lcd.write(5);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////// This method is responsible for starting the story mode and initialising the game play. The ////////////
//////////////// levels start easy and get progressively more difficult as further documented below ////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void playStoryMode() {
    int level = 1;
    int cursorPosition = 0;
    bool stillAlive = true;
    numberOfSymbols = 2;
    sequenceLength = 2;
    timeLimit = 10.00;
    delayTime = 1000;

    scrollDisplay("               Entering Story Mode", 32, false, false);

    // Loop while the user has not got a level wrong yet
    while (stillAlive) {
        // Calculate the level difficulty
        double difficulty = numberOfSymbols + sequenceLength + (10 - timeLimit) + (4 * (1 - (delayTime / 1000.00)));

        lcd.clear();
        // Display the level the user is on
        if (level < 10) {
            lcd.setCursor(8, 0);
            cursorPosition = 15;
        } else {
            lcd.setCursor(7, 0);
            cursorPosition = 14;
        }
        lcd.print("Level: ");

        for (int i = 0; i < 5; i++) {
            lcd.setCursor(cursorPosition, 0);
            lcd.print("  ");
            delay(250);
            lcd.setCursor(cursorPosition, 0);
            lcd.print(level);
            delay(250);
        }

        // Write level details to the Serial Monitor
        Serial.print("Level: ");
        Serial.print(level);
        Serial.print("     No. Symbols: ");
        Serial.print(numberOfSymbols);
        Serial.print("     Sequence Length: ");
        Serial.print(sequenceLength);
        Serial.print("     Time Delay: ");
        Serial.print(timeLimit);
        Serial.print("     Delay Time: ");
        Serial.print(delayTime);
        Serial.print("     Difficulty: ");
        Serial.println(difficulty);

        delay(1000);

        generateSequence();
        outputSequence();

        // If the level is completed correctly
        if (playLevel()) {
            lcd.setBacklight(GREEN);
            // If the level = 35 (Max Level) display a completion message
            if(level == 35){
              scrollDisplay("You've completed the game - well done!", 21, true, true);
              break;
            }
            delay(250);
            lcd.setBacklight(WHITE);
            level++;
            increaseLevelDifficulty(level);
        }
        // If the level is completed incorrectly, display the level which the user reached
        else {
            lcd.setBacklight(RED);
            scrollDisplay("Wrong. You made it to level: ", 11, true, true);
            lcd.setCursor(7, 0);
            lcd.setBacklight(GREEN);
            lcd.print(level);
            delay(1500);

            displayCorrectSequence();
            stillAlive = false;
            delay(2000);
        }
    }
    
    lcd.clear();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////// This method is responsible for increasing the difficulty of the level, so that the game gets ///////////
/////////////////////////////////////////// progressively more difficult ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void increaseLevelDifficulty(int level) {
    // These 5 IF ELSE blocks alter the time limit that the user has, based on the current level and current time limit
    if (level < 9) {
        timeLimit--;
    } else if (level >= 10 & level <= 13) {
        timeLimit -= 0.25;
    } else if (level >= 16 & level <= 18) {
        timeLimit -= 0.25;
    } else if (level >= 19 & timeLimit > (minTimeLimit + 0.05)) {
        timeLimit -= 0.05;
    }

    // This IF block alters the sequence length. It is increased by 1 whenever the level is a multiple of 3, until it reaches the maximum sequence length limit
    if (level % 3 == 0 & sequenceLength < maxSequenceLength) {
        sequenceLength++;
    }

    // This IF block alters the delay time between displaying the symbols in the sequence. After level 12, and until the delayTime = 200, it is decreased by 0.1 seconds every 2 levels
    if (level >= 12 & delayTime > minDelayTime) {
        if (level % 2 == 0) {
            delayTime -= 100;
        }
    }

    // This IF block alters the number of symbols in the sequence. It is increased on each level that is a multiple of 5.
    if (numberOfSymbols != maxNumberOfSymbols & (level % 5 == 0)) {
        numberOfSymbols++;
    }
}


/* The level difficulty for story mode is described in the below table:
 
            ┌──────────┬──────────┬──────────┬──────────┬──────────┬──────────┐ 
            │   Level  │No. Symbol│Seq Length│Time Limit│Delay Time│Difficulty│ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    1     │    2     │    2     │    10    │   1000   │    4     │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    2     │    2     │    2     │    9     │   1000   │    5     │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    3     │    2     │    3     │    8     │   1000   │    7     │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    4     │    2     │    3     │    7     │   1000   │    8     │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    5     │    3     │    3     │    6     │   1000   │    10    │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    6     │    3     │    4     │    5     │   1000   │    12    │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    7     │    3     │    4     │    4     │   1000   │    13    │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    8     │    3     │    4     │    3     │   1000   │    14    │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    9     │    3     │    5     │    3     │   1000   │    15    │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    10    │    4     │    5     │   2.75   │   1000   │  16.25   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    11    │    4     │    5     │   2.50   │   1000   │  16.50   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    12    │    4     │    6     │   2.25   │   900    │  18.15   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    13    │    4     │    6     │    2     │   900    │  18.40   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    14    │    4     │    6     │    2     │   800    │  18.80   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    15    │    4     │    7     │    2     │   800    │  19.80   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    16    │    4     │    7     │   1.75   │   700    │  20.45   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    17    │    4     │    7     │   1.50   │   700    │  20.70   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    18    │    4     │    8     │   1.25   │   600    │  22.35   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    19    │    4     │    8     │   1.20   │   600    │  22.40   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    20    │    4     │    8     │   1.15   │   500    │  22.85   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    21    │    4     │    9     │   1.10   │   500    │  23.90   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    22    │    4     │    9     │   1.05   │   400    │  24.35   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    23    │    4     │    9     │    1     │   400    │  24.40   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    24    │    4     │    10    │   0.95   │   300    │  25.85   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    25    │    4     │    10    │   0.90   │   300    │  25.90   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    26    │    4     │    10    │   0.85   │   200    │  26.35   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    27    │    4     │    10    │   0.80   │   200    │  26.40   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    28    │    4     │    10    │   0.75   │   200    │  26.45   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    29    │    4     │    10    │   0.70   │   200    │  26.50   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    30    │    4     │    10    │   0.65   │   200    │  26.55   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    31    │    4     │    10    │   0.60   │   200    │  26.60   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    32    │    4     │    10    │   0.55   │   200    │  26.65   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │    33    │    4     │    10    │   0.50   │   200    │  26.70   │ 
            ├──────────┼──────────┼──────────┼──────────┼──────────┼──────────┤
            │ After Level 33, the levels continue, but difficulty wont change │
            └──────────┴──────────┴──────────┴──────────┴──────────┴──────────┘
            
 * Difficulty is calculated as follows:                     
 *          (Number Of Symbols) + (Sequence Length) + (10 - Time Limit) + (4 * (1000 - Delay Time))
 * For example, for level 9:
 *          Difficulty = 3 + 5 + (10 - 3) + (4 * (1000 - 1000)) 
 *          Difficulty = 3 + 5 + 7 + 0
 *          Difficulty = 15
 * The difficulty has no impact on the level or the game, and instead is a way to numerically track the changes to each level as the level progress          
 * 
 *          
 * The number of symbols changes as follows:
 *          If the level number is a multiple of 5, increase the number of symbols by 1, until the maximum number of symbols (4) has been reached
 *           
 *           
 * The sequence length changes as follows:          
 *          If the level number is a multiple of 3, increase the sequence length by 1, until the maximum sequence length (10) has been reached
 *          
 *          
 * The time limit changes as follows:
 *          Until level 8, decrease the time limit by 1 for each level
 *          Between level 10 and level 12, decrease the time limit by 0.25 for each level
 *          Between level 16 and level 18, decrease the time limit by 0.25 for each level
 *          After level 18, and until the time limit reaches 0.50, decrease the time limit by 0.05 for each level
 *          
 *          
 * The delay time changes as follows:
 *          Until level 11, the delay time does not change
 *          After level 11, if the level number is a multiple of 2, decrease the delay time by 1000 (0.1 seconds), until the delay time reaches 200 (0.2 seconds)        
 */
