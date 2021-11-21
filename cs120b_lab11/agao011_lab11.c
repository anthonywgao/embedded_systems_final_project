/*	Author: agao011
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo:https://youtu.be/ePcNwHRGBMo
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "scheduler.h"
#include "timer.h"
#endif

#define input ((~PINA) & 0x0F)
#define dfreq 293.67
#define efreq 329.63
#define ffreq 370.0
#define gfreq 392.0
#define afreq 440.0

void set_PWM(double frequency)
{
    static double current_frequency;
    if (frequency != current_frequency)
    {
        if (!frequency)
        {
            TCCR3B &= 0x08;
        }
        else
        {
            TCCR3B |= 0x03;
        }
        if (frequency < 0.954)
        {
            OCR3A = 0xFFFF;
        }
        else if (frequency > 31250)
        {
            OCR3A = 0x0000;
        }
        else
        {
            OCR3A = (short)(8000000 / (128 * frequency)) - 1;
        }
        TCNT3 = 0;
        current_frequency = frequency;
    }
}
void PWM_on()
{
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}
void PWM_off()
{
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}
//song parameters
// int tone[10] = {261.63, 261.63, 523.25, 392, 21.827 * 16, 349.23, 329.63, 261.63, 329.63, 349.23};
// int rest[9] = {1, 1, 2, 4, 3, 3, 2, 1, 1};
// int length[10] = {1, 1, 2, 2, 1, 1, 2, 1, 1};
unsigned int beat = 0;

int row1count = 0;
int row2count = 0;
int row3count = 0;
int row4count = 0;
//int row5count = 0;

//displays
unsigned char row1;
unsigned char row2;
unsigned char row3;
unsigned char row4;
unsigned char row5;

//game metrics
int combometer;
int score;

//state machines
enum modes
{
    menu,
    playgame,
    showscore
} mode;
enum displays
{
    display1,
    display2,
    display3,
    display4,
    display5
} display;
enum row1states
{
    row1note,
    row1off
} row1state;
enum row2states
{
    row2note,
    row2off
} row2state;
enum row3states
{
    row3note,
    row3off
} row3state;
enum row4states
{
    row4note,
    row4off
} row4state;
enum row5states
{
    row5note,
    row5off
} row5state;
enum buttons
{
    wait,
    press
} button;

void playSong()
{
    if (beat > 0)
    {
        if (beat == 300)
        {
            row1count = 0;
            row1state = row1note;
        }
        else if (beat == 1000)
        {
            set_PWM(dfreq);
        }
        else if (beat == 1300)
        {
            row3count = 0;
            row3state = row3note;
        }
        else if (beat == 2000)
        {
            set_PWM(gfreq);
        }
        else if (beat == 2300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 3000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 3300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 3800)
        {
            set_PWM(0);
        }
        else if (beat == 4000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 4300)
        {
            row1count = 0;
            row1state = row1note;
        }
        else if (beat == 5000)
        {
            set_PWM(efreq);
        }
        else if (beat == 5300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 6000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 6300)
        {
            row3count = 0;
            row3state = row3note;
        }
        else if (beat == 7000)
        {
            set_PWM(gfreq);
        }
        else if (beat == 8000)
        {
            set_PWM(0);
        }
        else if (beat == 8300)
        {
            row1count = 0;
            row1state = row1note;
        }
        else if (beat == 9000)
        {
            set_PWM(efreq);
        }
        else if (beat == 9300)
        {
            row4count = 0;
            row4state = row4note;
        }
        else if (beat == 10000)
        {
            set_PWM(afreq);
        }
        else if (beat == 10300)
        {
            row3count = 0;
            row3state = row3note;
        }
        else if (beat == 11000)
        {
            set_PWM(gfreq);
        }
        else if (beat == 11300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 12000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 12300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 12800)
        {
            set_PWM(0);
        }
        else if (beat == 13000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 13300)
        {
            row3count = 0;
            row3state = row3note;
        }
        else if (beat == 14000)
        {
            set_PWM(gfreq);
        }
        else if (beat == 14300)
        {
            row4count = 0;
            row4state = row4note;
        }
        else if (beat == 15000)
        {
            set_PWM(afreq);
        }
        else if (beat == 16000)
        {
            set_PWM(0);
        }
        else if (beat == 16300)
        {
            row1count = 0;
            row1state = row1note;
        }
        else if (beat == 17000)
        {
            set_PWM(dfreq);
        }
        else if (beat == 17300)
        {
            row3count = 0;
            row3state = row3note;
        }
        else if (beat == 18000)
        {
            set_PWM(gfreq);
        }
        else if (beat == 18300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 19000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 19300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 19800)
        {
            set_PWM(0);
        }
        else if (beat == 20000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 20300)
        {
            row1count = 0;
            row1state = row1note;
        }
        else if (beat == 21000)
        {
            set_PWM(efreq);
        }
        else if (beat == 21300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 22000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 22300)
        {
            row3count = 0;
            row3state = row3note;
        }
        else if (beat == 23000)
        {
            set_PWM(gfreq);
        }
        else if (beat == 24000)
        {
            set_PWM(0);
        }
        else if (beat == 24300)
        {
            row4count = 0;
            row4state = row4note;
        }
        else if (beat == 25000)
        {
            set_PWM(afreq);
        }
        else if (beat == 25300)
        {
            row1count = 0;
            row1state = row1note;
        }
        else if (beat == 26000)
        {
            set_PWM(efreq);
        }
        else if (beat == 27000)
        {
            set_PWM(0);
        }
        else if (beat == 27300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 28000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 28300)
        {
            row2count = 0;
            row2state = row2note;
        }
        else if (beat == 28800)
        {
            set_PWM(0);
        }
        else if (beat == 29000)
        {
            set_PWM(ffreq);
        }
        else if (beat == 29300)
        {
            row3count = 0;
            row3state = row3note;
        }
        else if (beat == 30000)
        {
            set_PWM(gfreq);
        }
        else if (beat == 30300)
        {
            row4count = 0;
            row4state = row4note;
        }
        else if (beat == 31000)
        {
            set_PWM(afreq);
        }
        else if (beat == 32000)
        {
            set_PWM(0);
        }
        else if (beat == 32300)
        {
            row3count = 0;
            row3state = row3note;
        }
        else if (beat == 33000)
        {
            set_PWM(gfreq);
        }
        else if (beat == 35000)
        {
            set_PWM(0);
        }
    }
}

void tick()
{
    //led matrix display flicker
    switch (display)
    {
    case display1:
        PORTD = 0xFE;
        PORTC = row1;
        display = display2;
        break;
    case display2:
        PORTD = 0xFD;
        PORTC = row2;
        display = display3;
        break;
    case display3:
        PORTD = 0xFB;
        PORTC = row3;
        display = display4;
        break;
    case display4:
        PORTD = 0xF7;
        PORTC = row4;
        display = display5;
        break;
    case display5:
        PORTD = 0xEF;
        PORTC = row5;
        display = display1;
        break;
    default:
        display = display1;
        break;
    }

    //modes
    switch (mode)
    {
    case menu:
        row1 = 0xFF;
        row2 = 0xFF;
        row3 = 0xFF;
        row4 = 0xFF;
        row5 = 0xFF;
        if (input)
        {
            mode = playgame;
        }
        break;
    case playgame:
        row1 = 0x00;
        row2 = 0x00;
        row3 = 0x00;
        row4 = 0x00;
        row5 = 0x00;
        //notes
        switch (row1state)
        {
        case row1off:
            row1 = 0x00;
            if ((button == wait) && (input & 0x08))
            {
                combometer = 0;
            }
            break;
        case row1note:
            if (row1count > 800)
            {
                row1state = row1off;
            }
            else if (row1count > 700)
            {
                row1 = 0x80;
                if ((button == wait) && (input & 0x08))
                {
                    combometer++;
                    score += combometer;
                }
            }
            else if (row1count > 600)
            {
                row1 = 0x40;
                if ((button == wait) && (input & 0x08))
                {
                    combometer++;
                    score += combometer;
                }
            }
            else if (row1count > 500)
            {
                row1 = 0x20;
            }
            else if (row1count > 400)
            {
                row1 = 0x10;
            }
            else if (row1count > 300)
            {
                row1 = 0x08;
            }
            else if (row1count > 200)
            {
                row1 = 0x04;
            }
            else if (row1count > 100)
            {
                row1 = 0x02;
            }
            else
            {
                row1 = 0x01;
            }
            if ((row1count < 600) && (button == wait) && (input & 0x08))
            {
                combometer = 0;
            }
            row1count++;
            break;
        }
        switch (row2state)
        {
        case row2off:
            row2 = 0x00;
            if ((button == wait) && (input & 0x04))
            {
                combometer = 0;
            }
            break;
        case row2note:
            if (row2count > 800)
            {
                row2state = row2off;
            }
            else if (row2count > 700)
            {
                row2 = 0x80;
                if ((button == wait) && (input & 0x04))
                {
                    combometer++;
                    score += combometer;
                }
            }
            else if (row2count > 600)
            {
                row2 = 0x40;
                if ((button == wait) && (input & 0x04))
                {
                    combometer++;
                    score += combometer;
                }
            }
            else if (row2count > 500)
            {
                row2 = 0x20;
            }
            else if (row2count > 400)
            {
                row2 = 0x10;
            }
            else if (row2count > 300)
            {
                row2 = 0x08;
            }
            else if (row2count > 200)
            {
                row2 = 0x04;
            }
            else if (row2count > 100)
            {
                row2 = 0x02;
            }
            else
            {
                row2 = 0x01;
            }
            if ((row2count < 600) && (button == wait) && (input & 0x04))
            {
                combometer = 0;
            }
            row2count++;
            break;
        }
        switch (row3state)
        {
        case row3off:
            row3 = 0x00;
            if ((button == wait) && (input & 0x02))
            {
                combometer = 0;
            }
            break;
        case row3note:
            if (row3count > 800)
            {
                row3state = row3off;
            }
            else if (row3count > 700)
            {
                row3 = 0x80;
                if ((button == wait) && (input & 0x02))
                {
                    combometer++;
                    score += combometer;
                }
            }
            else if (row3count > 600)
            {
                row3 = 0x40;
                if ((button == wait) && (input & 0x02))
                {
                    combometer++;
                    score += combometer;
                }
            }
            else if (row3count > 500)
            {
                row3 = 0x20;
            }
            else if (row3count > 400)
            {
                row3 = 0x10;
            }
            else if (row3count > 300)
            {
                row3 = 0x08;
            }
            else if (row3count > 200)
            {
                row3 = 0x04;
            }
            else if (row3count > 100)
            {
                row3 = 0x02;
            }
            else
            {
                row3 = 0x01;
            }
            if ((row3count < 600) && (button == wait) && (input & 0x02))
            {
                combometer = 0;
            }
            row3count++;
            break;
        }
        switch (row4state)
        {
        case row4off:
            row4 = 0x00;
            if ((button == wait) && (input & 0x01))
            {
                combometer = 0;
            }
            break;
        case row4note:
            if (row4count > 800)
            {
                row4state = row4off;
            }
            else if (row4count > 700)
            {
                row4 = 0x80;
                if ((button == wait) && (input & 0x01))
                {
                    combometer++;
                    score += combometer;
                }
            }
            else if (row4count > 600)
            {
                row4 = 0x40;
                if ((button == wait) && (input & 0x01))
                {
                    combometer++;
                    score += combometer;
                }
            }
            else if (row4count > 500)
            {
                row4 = 0x20;
            }
            else if (row4count > 400)
            {
                row4 = 0x10;
            }
            else if (row4count > 300)
            {
                row4 = 0x08;
            }
            else if (row4count > 200)
            {
                row4 = 0x04;
            }
            else if (row4count > 100)
            {
                row4 = 0x02;
            }
            else
            {
                row4 = 0x01;
            }
            if ((row4count < 600) && (button == wait) && (input & 0x01))
            {
                combometer = 0;
            }
            row4count++;
            break;
        }
        //combometer
        if (combometer == 0)
        {
            row5 = 0x00;
        }
        else if (combometer == 1)
        {
            row5 = 0x80;
        }
        else if (combometer == 2)
        {
            row5 = 0xC0;
        }
        else if (combometer == 3)
        {
            row5 = 0xE0;
        }
        else if (combometer == 4)
        {
            row5 = 0xF0;
        }
        else if (combometer == 5)
        {
            row5 = 0xF8;
        }
        else if (combometer == 6)
        {
            row5 = 0xFC;
        }
        else if (combometer == 7)
        {
            row5 = 0xFE;
        }
        else
        {
            row5 = 0xFF;
        }

        playSong();

        beat++;
        if (beat >= 36000)
        {
            beat = 0;
            mode = showscore;
        }
        break;
    case showscore:
        row1 = 0x00;
        row2 = 0x00;
        row3 = 0x00;
        row4 = 0x00;
        row5 = 0x00;

        if (score > 50)
        {
            //display A
            row2 = 0x78;
            row3 = 0x14;
            row4 = 0x78;
        }
        else if (score > 40)
        {
            //display B
            row2 = 0x7C;
            row3 = 0x54;
            row4 = 0x6C;
        }
        else if (score > 30)
        {
            //display C
            row2 = 0x7C;
            row3 = 0x44;
            row4 = 0x44;
        }
        else if (score > 20)
        {
            //display D
            row2 = 0x7C;
            row3 = 0x44;
            row4 = 0x38;
        }
        else
        {
            //display F
            row2 = 0x7C;
            row3 = 0x14;
            row4 = 0x14;
        }
        if (input)
        {
            combometer = 0;
            score = 0;
            mode = menu;
        }
        break;
    }

    //buttonpress
    switch (button)
    {
    case wait:
        if (input)
        {
            button = press;
        }
        break;
    case press:
        if (!input)
        {
            button = wait;
        }
        break;
    }
}

int main(void)
{
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xF0;
    PORTB = 0x0F;
    DDRC = 0xFF;
    PORTC = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;

    PWM_on();
    set_PWM(0);
    combometer = 0;
    score = 0;

    button = wait;
    mode = menu;
    display = display1;
    row1state = row1off;
    row2state = row2off;
    row3state = row3off;
    row4state = row4off;
    row5state = row5off;

    static task task1;
    task *tasks[] = {&task1};
    const unsigned short numTasks = sizeof(tasks) / sizeof(task *);

    // Task 1
    task1.state = 0;       //Task initial state.
    task1.period = 2;      //Task Period.
    task1.elapsedTime = 2; //Task current elapsed time.
    task1.TickFct = &tick; //Function pointer for the tick.

    TimerSet(1);
    TimerOn();

    unsigned short i; // Scheduler for-loop iterator
    while (1)
    {
        for (i = 0; i < numTasks; i++)
        {
            if (tasks[i]->elapsedTime == tasks[i]->period)
            {
                tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                tasks[i]->elapsedTime = 2;
            }
            tasks[i]->elapsedTime = 2;
        }
        while (!TimerFlag)
            ;
        TimerFlag = 0;
    }
    return 0;
}
