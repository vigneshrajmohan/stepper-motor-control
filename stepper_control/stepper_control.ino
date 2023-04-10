#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define Pulse 9 // stepper1
#define Dir 8 // stepper1

long delay_Micros = 1800; // Set value
float half_circle_counter = 800; // adjust this value until it steps aa full half circle (180 degs)
int speed_delay = 350; // make value smaller for faster motor, larger for slower
float counter1 = 0;
float curr_deg1 = 0;
float goal_deg1 = 0;
float m1_limit = 180;


void setup(){
  pinMode(Pulse,OUTPUT);
  pinMode(Dir,OUTPUT);
  digitalWrite(Dir,LOW);
  
  Serial.begin(9600);
}

void turnClockwise(){
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  delayMicroseconds(speed_delay);
  digitalWrite(9, LOW);
  delayMicroseconds(speed_delay);
}

void turnCounter(){
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  delayMicroseconds(speed_delay);
  digitalWrite(9, LOW);
  delayMicroseconds(speed_delay);
}

void turnClockwiseDegs(float degs){
  counter1 = 0;
  float goal = half_circle_counter*(degs/180);
  while (counter1 < goal){
    turnClockwise();
    counter1++;
  }
}

void turnCounterDegs(float degs){
  counter1 = 0;
  float goal = half_circle_counter*(degs/180);
  while (counter1 < goal){
    turnCounter(); 
    counter1++;
  }
}

void turnDegrees(float degs){
  float degs_to_turn = abs(degs);
  if (degs < 0){
    turnCounterDegs(degs_to_turn);
  }
  else{
    turnClockwiseDegs(degs_to_turn);
  }
  curr_deg1 += degs;
}

bool deg_check(float degs){
  float new_deg = curr_deg1 + degs;
  if (new_deg > m1_limit){
    return false;
  }
  if (new_deg < 0){
    return false;
  }
  return true;
}

bool deg_desired_check(float degs){
  return !(degs > m1_limit || degs < 0);
}

float amount_to_turn(float desired_degs){
  float goal = desired_degs - curr_deg1;
  return goal;
}


/** COMMAND INSTRUCTIONS:

to set Stepper1: "m25" for example, if you want to set it to 25 degrees
to set light color: "c23,233,124" for example if you want to set rgb to 23,244,124

**/
void loop()
{
  if (Serial.available()) { // Check if there is incoming data
    String command = Serial.readStringUntil('\n');
    if (command.substring(0, 1).equals("m")){
      int firstCommaIndex = command.indexOf(',');
      int m1_init = command.substring(1, firstCommaIndex).toFloat();
      int m1_new = command.substring(firstCommaIndex + 1).toFloat(); 
      
      curr_deg1 = m1_init;
      if (deg_desired_check(m1_new)){
        goal_deg1 = m1_new;
      }
      if (curr_deg1 != goal_deg1){
        turnDegrees(amount_to_turn(goal_deg1));
      }
      Serial.print("Set Stepper1 to degree: "); // Print a message to the serial monitor
      Serial.print(m1_new); // Print the received value
      Serial.print(" from: "); // Print a message to the serial monitor
      Serial.print(m1_init); // Print the received value
    }
  }
  delay(100); // Wait for a short period to avoid sending too much data too quickly
}
