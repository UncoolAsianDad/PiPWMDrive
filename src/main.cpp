#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <ctype.h>
#include <ncurses.h>


void stop() {
    digitalWrite(2,1);
    digitalWrite(3,1);
    digitalWrite(4,1);
    digitalWrite(5,1);
}


void right() {
    stop();
    digitalWrite(2,1);
    digitalWrite(3,0);
    digitalWrite(4,0);
    digitalWrite(5,1);
}

void left() {
    stop();
    digitalWrite(2,0);
    digitalWrite(3,1);
    digitalWrite(4,1);
    digitalWrite(5,0);
}

void backward() {
    stop();
    digitalWrite(2,1);
    digitalWrite(3,0);
    digitalWrite(4,1);
    digitalWrite(5,0);
}


void forward() {
    stop();
    digitalWrite(2,0);
    digitalWrite(3,1);
    digitalWrite(4,0);
    digitalWrite(5,1);
}

void setup() {
    if (wiringPiSetup() < 0) {
	printf("Error Setup\n");
	exit(1);
    }
    // software pwm
    softPwmCreate(0, 0, 100);
    softPwmCreate(1, 0, 100);

    // direction control
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    stop();
    sleep(1);
}

int main(int argc, char** argv) {
    int ch;
    bool quit = false;
    


    setup();
    //use ncurses
    initscr(); cbreak(); noecho();
    keypad(stdscr, TRUE);

    printw("Use Arrow Keys to move, Space to stop, Q to quit.\n");
    //get errors
	while(!quit) {
	    while( (ch = getch()) == ERR);

//		printf("%c\n\r", ch);
            
            switch (ch) {
		case 'q':
			quit = true;
			break;
		case ' ':
			stop();
			break;

		case KEY_UP:
			forward();
			break;
		case KEY_DOWN:
			backward();
			break;
		case KEY_LEFT:
			left();
			break;
		case KEY_RIGHT:
			right();
			break;
	    }
	    delay(100);

	}
	stop();
	endwin();
    
	printf("Bye.\n");

    return 0;
}
