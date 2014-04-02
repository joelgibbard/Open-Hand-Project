/*  
    The code in this project will be for use with the Open Hand Project robotic hand.

    Copyright (C) 2014  Joel Gibbard (Author)
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    25/03/2014
    

    
This code opens and closes the robotic hand based on digital push buttons.
Details of the hardware setup will be made available at www.openhandproject.org.
It uses an arduino along with the Aruino Motor controller V3 board to control the motors of the hand.

This code is part of the Open Hand Project, visit www.openhandproject.org to learn more.

*/

//Pin Definition

const int 
PWM_A   = 3,      //Speed
DIR_A   = 12,      //Direction
BRAKE_A = 9,      //Brake
SNS_A   = A0,      //Current Sense
PWM_B   = 11,
DIR_B   = 13,
BRAKE_B = 8,
SNS_B   = A1,
PWM_C   = 2,
DIR_C   = 7,
BRAKE_C = 5,
SNS_C   = A2,
PWM_D   = 6,
DIR_D   = 10,
BRAKE_D = 4,
SNS_D   = A3,

DI0     = 18,      //Digital Inputs      18 and 19 for Seeduino 58 and 59 for Mega
DI1     = 19;

//Variable definition
int state = 1;    //Hand state, 0 = Open 1 = Closed.
boolean STOP_A = 0;
boolean STOP_B = 0;
boolean STOP_C = 0;
boolean STOP_D = 0;
int Threshold = 50;    //0 to 57
int Speed = 255;

void setup(){
  
  Serial.begin(9600);        //Serial for debugging
  
  pinMode(DI0, INPUT);
  pinMode(DI1, INPUT);
  pinMode(BRAKE_A, OUTPUT);  // Brake pin on channel A
  pinMode(DIR_A, OUTPUT);    // Direction pin on channel A
  pinMode(BRAKE_B, OUTPUT);  
  pinMode(DIR_B, OUTPUT);    
  pinMode(BRAKE_C, OUTPUT);  
  pinMode(DIR_C, OUTPUT);  
  pinMode(BRAKE_D, OUTPUT);  
  pinMode(DIR_D, OUTPUT); 
  
}

void loop(){
  Serial.print(digitalRead(DI0));    //DEBUG
  Serial.print("    ");
  Serial.print(STOP_A);
  Serial.println(STOP_B);
  
  
  if(digitalRead(DI0) == HIGH){        //If Open button is pressed...
    if(state == 0){                 //If hand is open, move thumb position
    thumbmove();
    }
    else{
    Serial.println("opening");      //DEBUG
    openclose(1);                  //call Open/Close subroutine to Open
    }
  }
  
  if(digitalRead(DI1) == HIGH){        //If close button is pressed, close
    Serial.println("closing");    //DEBUG
    openclose(0);                  //call Open/Close subroutine to Close
   }
  
}

void openclose(boolean function){
  
   digitalWrite(BRAKE_A, LOW);    //Disable brakes
   digitalWrite(BRAKE_B, LOW);
   digitalWrite(BRAKE_C, LOW);
   digitalWrite(BRAKE_D, LOW);
   delay(100);
   
   digitalWrite(DIR_A, function);  //Set direction
   digitalWrite(DIR_B, function);
   digitalWrite(DIR_C, function);  
   digitalWrite(DIR_D, function);   
   
   analogWrite(PWM_A, Speed);     // Set the speed of the motors, 255 is the maximum value
   analogWrite(PWM_B, Speed);
   analogWrite(PWM_C, Speed);
   analogWrite(PWM_D, Speed);
   
   delay(20);                    //Delay for current spike
   
   while(STOP_A == 0 || STOP_B == 0 || STOP_C == 0 || STOP_D == 0){    //Continue until all motors have stopped
     if(analogRead(SNS_A)>=Threshold){
       digitalWrite(PWM_A, 0);
       digitalWrite(BRAKE_A, HIGH);
       STOP_A = 1;
       Serial.println("stopped");    //DEBUG
     }
     if(analogRead(SNS_B)>=Threshold){
       digitalWrite(PWM_B, 0);
       digitalWrite(BRAKE_B, HIGH);
       STOP_B = 1;
     }
     if(analogRead(SNS_C)>=Threshold){
       digitalWrite(PWM_C, 0);
       digitalWrite(BRAKE_C, HIGH);
       STOP_C = 1;
     }
     if(analogRead(SNS_D)>=Threshold){
       digitalWrite(PWM_D, 0);
       digitalWrite(BRAKE_D, HIGH);
       STOP_D = 1;
     }
   }
   
   STOP_A = 0;              //Reset stop values
   STOP_B = 0;  
   STOP_C = 0;
   STOP_D = 0;
}

void thumbmove(){
}
