/*
    MORSE CODE CONVERSION

    NOTE :  Space between two words     denoted by the character ' '        (space)
            Space between two letters   denoted by the character '_'        (underscore)

    Morse code representation in the output:-

            Dash (three point)          denoted by '----'                   (3 hyphens, +3 beep sounds)
            Dot (one point)             denoted by '-'                      (1 hyphen , +1 beep sound )
            Spaces                      denoted by '#'                      (hash     ,      no sound )
                - 3 points for space between 2 letters : ###
                - 7 points for space between 2 words   : #######

    TO BE DONE :
    - Conversion from uint8_t to int
      Problem:-
      Not sure how the values are assigned. For example, if the current is going to be measured as a value from 0-255 how are we converting that to mA?
                                            What value does 255 (the max) correspond to since we just know that any value >2000 = 'U'
                                            I think, we need to test here what the bounds on the measurement are

      For the moment, I have assumed that this conversion is already done and so I have declared int values for the measured quantities.

    Code by : Priyanka DAS, X2013 Ecole polytechnique
*/

#include <iostream>
#include <windows.h>        // for the sound in the fancy output uniquely, not required in the final code

using namespace std;

const int delay = 100;      // (ms) duration of the interval
const int freq = 1000;      // (Hz) because audible but not very high-pitched

string morse[] = {
            "0000000"           ,// space between words
            "000"               ,// space between letters
            "10111"             ,// A
            "111010101"         ,// B
            "11101011101"       ,// C
            "1110101"           ,// D
            "1"                 ,// E
            "101011101"         ,// F
            "111011101"         ,// G
            "1010101"           ,// H
            "101"               ,// I
            "1011101110111"     ,// J
            "111010111"         ,// K
            "101110101"         ,// L
            "1110111"           ,// M
            "11101"             ,// N
            "11101110111"       ,// O
            "10111011101"       ,// P
            "1110111010111"     ,// Q
            "1011101"           ,// R
            "10101"             ,// S
            "111"               ,// T
            "1010111"           ,// U
            "101010111"         ,// V
            "101110111"         ,// W
            "11101010111"       ,// X
            "1110101110111"     ,// Y
            "11101110101"       ,// Z
            "1110111011101110111"   ,// 0
            "10111011101110111"     ,// 1
            "101011101110111"       ,// 2
            "1010101110111"         ,// 3
            "10101010111"           ,// 4
            "101010101"             ,// 5
            "11101010101"           ,// 6
            "1110111010101"         ,// 7
            "111011101110101"       ,// 8
            "11101110111011101"     // 9
};

int indexConvert(char a){
    if(a==' ')                return 0;
    else if(a=='_')           return 1;
    else if(a=='A')           return 2;
    else if(a=='B')           return 3;
    else if(a=='C')           return 4;
    else if(a=='D')           return 5;
    else if(a=='E')           return 6;
    else if(a=='F')           return 7;
    else if(a=='G')           return 8;
    else if(a=='H')           return 9;
    else if(a=='I')           return 10;
    else if(a=='J')           return 11;
    else if(a=='K')           return 12;
    else if(a=='L')           return 13;
    else if(a=='M')           return 14;
    else if(a=='N')           return 15;
    else if(a=='O')           return 16;
    else if(a=='P')           return 17;
    else if(a=='Q')           return 18;
    else if(a=='R')           return 19;
    else if(a=='S')           return 20;
    else if(a=='T')           return 21;
    else if(a=='U')           return 22;
    else if(a=='V')           return 23;
    else if(a=='W')           return 24;
    else if(a=='X')           return 25;
    else if(a=='Y')           return 26;
    else if(a=='Z')           return 27;
    else if(a=='0')           return 28;
    else if(a=='1')           return 29;
    else if(a=='2')           return 30;
    else if(a=='3')           return 31;
    else if(a=='4')           return 32;
    else if(a=='5')           return 33;
    else if(a=='6')           return 34;
    else if(a=='7')           return 35;
    else if(a=='8')           return 36;
    else if(a=='9')           return 37;
}

// VBAT CONVERSION
char readVBat (int val){
    if(val < 6000)          return 'A';
    else if(val > 8400)     return 'Z';
    else return char(66+(val-6000)/100);
}

// CURRENT CONVERSION
char readCurrent (int val){
    if(val > 2000)          return 'U';
    else return char(65+(val/100));
}

// TEMPERATURE CONVERSION
char readTBat (int val){
    if(val < -20)            return 'A';
    else if(val > 60)        return 'R';
    else return char(66+(val+20)/5);
}

// Generates the message to be converted to booleans
string generateMsg(int v_bat, int I_consumed, int I_solar, int temp_bat ){
    string msg = "F_R_0_1 ";
    msg = msg + readVBat(v_bat) + '_' + readCurrent(I_consumed) + '_' + readCurrent(I_solar) + '_' + readTBat(temp_bat);
    return msg;
}

// Generates a concatenated string of the Morse code used for converting into boolean array (further below)
string StringOutput(string str){
    string temp;
    for(int i=0 ; i<str.length() ; i++){
        temp.append(morse[indexConvert(str[i])]);
    }
    return temp;
}


/* Display functions not required in final .cpp */

void displayMsg(string str){
    string temp = StringOutput(str);
    for(int i=0 ; i<temp.length() ; i++){
        if(temp[i]=='1')    cout<<"-";
        else                cout<<"#";
    }
}

void beepMsg(string str){
    string temp = StringOutput(str);
    for(int i=0 ; i<temp.length() ; i++){
        if(temp[i]=='1')    { cout<<"-"; Beep(freq,delay) ; }
        else                { cout<<"#"; Sleep(delay)     ; }
    }
}

void displayBool(bool msg[], int boolSize){
    for(int i=0 ; i<boolSize ; i++){
        if(msg[i])          { cout<<"-"; Beep(freq,delay) ; }
        else                { cout<<"#"; Sleep(delay)     ; }
    }
}


/* This function returns the boolean msg array that can be passed onto the port - has to be done from inside, otherwise too complicated to return a boolean array */

void boolOutput(string str){
    string temp = StringOutput(str);
    bool output[temp.length()];

    for(int i=0 ; i<temp.length() ; i++){
        if(temp[i]=='1')    output[i] = true;
        else                output[i] = false;
    }

    displayBool(output,temp.length());
}

/* Tests */

void conversionTest(){
    cout<<"\n\nVBAT\n\n";
    for(int i=0 ; i<26 ; i++)
        cout<<5999+i*100<<" "<<readVBat(5999+i*100)<<endl;

    cout<<"\n\nCurrent\n\n";
    for(int i=0 ; i<26 ; i++)
        cout<<i*100<<" "<<readCurrent(i*100)<<endl;

    cout<<"\n\nTemperature\n\n";
    for(int i=0 ; i<26 ; i++)
        cout<<-30+i*5<<" "<<readTBat(-30+i*5)<<endl;
}

void msgTest(){
//    string msg = "S_O_S";
    string msg = generateMsg(6000,301,201,0);

    cout<<endl<<"Message : "<<msg<<endl;
    cout<<endl<<"Time interval (ms) : "<<delay<<endl;

    cout<<endl<<"\nMorse code simulation : "<<endl;     beepMsg(msg);
    cout<<endl<<"\nNormal morse display  : "<<endl;     displayMsg(msg);
    cout<<endl<<"\nBoolean table display : "<<endl;     boolOutput(msg);
}

int main( void )
{
    msgTest();
    conversionTest();

    return 0;
}
