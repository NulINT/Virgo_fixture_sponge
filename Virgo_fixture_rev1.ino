const int LED_GREEN_1 = 37;
const int LED_GREEN_2 = 38;
const int LED_GREEN_3 = 39;
const int LED_GREEN_4 = 40;
const int LED_GREEN_5 = 41;
const int LED_GREEN_6 = 48;
const int LED_GREEN_7 = 43;
const int LED_GREEN_8 = 44;
const int LED_RED_1 = 45;
const int Linear_solenoid = 28;
const int button1 = 30;
const int button2 = 31;
const int button3 = 32;
const int button4 = 34;
const int button5 = 35;
const int button6 = 36;
const int notthing = 13;
const int BUZZER = 5;

bool state_1 = false ;
bool button1_pressed = false;
bool button2_pressed = false;
bool button3_pressed = false;
bool button4_pressed = false;
bool button5_pressed = false;
bool button6_pressed = false;

bool pre_1 = false;
bool pre_2 = false;
bool pre_3 = false;
bool pre_4 = false;
bool pre_5 = false;
bool pre_6 = false;
bool active_buzzer = false ;

unsigned long button1_pressed_time = 0;
unsigned long button2_pressed_time = 0;
unsigned long button3_pressed_time = 0;
unsigned long button4_pressed_time = 0;
unsigned long button5_pressed_time = 0;
unsigned long button6_pressed_time = 0;
unsigned long resetState = 0;

void check_button() {
  button1_pressed = digitalRead(button1) ;
  button2_pressed = digitalRead(button2) ;
  button3_pressed = digitalRead(button3) ;
  button4_pressed = digitalRead(button4) ;
  button5_pressed = digitalRead(button5) ;
  button6_pressed = digitalRead(button6) ;
  if (button1_pressed and button2_pressed and button3_pressed and button4_pressed  and state_1 == false and button5_pressed == false and button6_pressed == false) {
  button1_pressed_time = 0 ;
  button2_pressed_time = 0 ;
  button3_pressed_time = 0 ;
  button4_pressed_time = 0 ;
  button5_pressed_time = 0 ;
  button6_pressed_time = 0 ;
  resetState = millis();
  control_led();
  digitalWrite(BUZZER, 1);
  delay(500);
  digitalWrite(BUZZER, 0); 
  digitalWrite(Linear_solenoid,1);
  delay(5000);
  button1_pressed = digitalRead(button1) ;
  button2_pressed = digitalRead(button2) ;
  button3_pressed = digitalRead(button3) ;
  button4_pressed = digitalRead(button4) ;
  button5_pressed = digitalRead(button5) ;
  button6_pressed = digitalRead(button6) ;
  state_1 = true ;
}
  if (button5_pressed and button6_pressed and state_1 and button1_pressed == false and button2_pressed == false and button3_pressed == false and button4_pressed == false  ) {
  init();
  control_led();
  digitalWrite(BUZZER, 1);
  delay(500);
  digitalWrite(BUZZER, 0); 
  delay(5000);
  for (int i=0 ;i <= 1 ; i++){
      digitalWrite(BUZZER, 1);
      delay(1000);
      digitalWrite(BUZZER, 0);
      delay(500);      
    }
  delay(2000);
  digitalWrite(Linear_solenoid,0);
  button1_pressed = digitalRead(button1) ;
  button2_pressed = digitalRead(button2) ;
  button3_pressed = digitalRead(button3) ;
  button4_pressed = digitalRead(button4) ;
  button5_pressed = digitalRead(button5) ;
  button6_pressed = digitalRead(button6) ;
}
  if ((millis() - resetState > 60000  and state_1  == true  ) and ( button5_pressed == false or  button6_pressed == false )) {
      digitalWrite(LED_RED_1 ,1);
      digitalWrite(BUZZER, 1);
      delay(1000);
      digitalWrite(LED_RED_1 ,0);
      digitalWrite(BUZZER, 0);
      delay(2000);
     digitalWrite(Linear_solenoid,0);
    init();
  }

  if (button1_pressed and pre_1 == false ) {
  button1_pressed_time = millis();
  pre_1 = true; 
} else if (button1_pressed == false and pre_1  ){
  button1_pressed_time = 0 ;
  pre_1 = false; 
}

if (button2_pressed and pre_2 == false ) {
  button2_pressed_time = millis();
  pre_2 = true; 
} else if (button2_pressed == false and pre_2  ){
  button2_pressed_time = 0 ;
  pre_2 = false; 
}

if (button3_pressed and pre_3 == false ) {
  button3_pressed_time = millis();
  pre_3 = true; 
} else if (button3_pressed == false and pre_3  ){
  button3_pressed_time = 0 ;
  pre_3 = false; 
}

if (button4_pressed and pre_4 == false ) {
  button4_pressed_time = millis();
  pre_4 = true; 
} else if (button4_pressed == false and pre_4  ){
  button4_pressed_time = 0 ;
  pre_4 = false; 
}
  
}

void control_led() {
  digitalWrite(LED_GREEN_1, button1_pressed);
  digitalWrite(LED_GREEN_2, button2_pressed);
  digitalWrite(LED_GREEN_3, button3_pressed);
  digitalWrite(LED_GREEN_4, button4_pressed);
  digitalWrite(LED_GREEN_5, button5_pressed);
  digitalWrite(LED_GREEN_6, button6_pressed);
  
}

void control_BUZZER() {

  
   if ((button1_pressed || button2_pressed || button3_pressed || button4_pressed) and state_1 ) {
    active_buzzer = true;
  }
  
  if ((button1_pressed || button2_pressed || button3_pressed || button4_pressed) and (button5_pressed || button6_pressed)) {
    active_buzzer = true;
  }
   if ((button5_pressed || button6_pressed ) && state_1 == false) {
    active_buzzer = true;
  }
    if (button1_pressed && millis() - button1_pressed_time  > 3000 ) {
    Serial.println("1 press long");
    active_buzzer = true;
  } else if (button2_pressed && millis() - button2_pressed_time > 3000 ) {
    Serial.println("2 press long");
    active_buzzer = true;
  }else if (button3_pressed && millis() - button3_pressed_time > 3000  ) {
    Serial.println("3 press long");
    active_buzzer = true;
  }else if (button4_pressed && millis() - button4_pressed_time  > 3000 ) {
    Serial.println("4 press long");
    active_buzzer = true;
  }
  if (active_buzzer ) {
    digitalWrite(LED_GREEN_8,0);
    for (int i=0 ;i <= 2 ; i++){
      digitalWrite(LED_RED_1 ,1);
      digitalWrite(BUZZER, 1);
      //tone(BUZZER, 1000);
      delay(500);
      digitalWrite(LED_RED_1 ,0);
      digitalWrite(BUZZER, 0);
      //noTone(BUZZER);
      delay(500);
      active_buzzer = false;
    }
    digitalWrite(LED_GREEN_8,1);
}
}

void init() {
  bool state_1 = false ;
bool button1_pressed = false;
bool button2_pressed = false;
bool button3_pressed = false;
bool button4_pressed = false;
bool button5_pressed = false;
bool button6_pressed = false;

bool pre_1 = false;
bool pre_2 = false;
bool pre_3 = false;
bool pre_4 = false;
bool pre_5 = false;
bool pre_6 = false;
bool active_buzzer = false ;

unsigned long button1_pressed_time = 0;
unsigned long button2_pressed_time = 0;
unsigned long button3_pressed_time = 0;
unsigned long button4_pressed_time = 0;
unsigned long button5_pressed_time = 0;
unsigned long button6_pressed_time = 0;
unsigned long resetState = 0;

}
void setup() {
  Serial.begin(115200);
  button1_pressed = false;
  button2_pressed = false;
  button3_pressed = false;
  button4_pressed = false;
  button5_pressed = false;
  button6_pressed = false;
  digitalWrite(LED_GREEN_1, LOW);
  digitalWrite(LED_GREEN_2, LOW);
  digitalWrite(LED_GREEN_3, LOW);
  digitalWrite(LED_GREEN_4, LOW);
  digitalWrite(LED_GREEN_5, LOW);
  digitalWrite(LED_GREEN_6, LOW);
  digitalWrite(LED_GREEN_7, HIGH);
  digitalWrite(LED_GREEN_8, HIGH);
  digitalWrite(LED_RED_1, LOW);
  digitalWrite(Linear_solenoid, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(notthing,LOW);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(button5, INPUT);
  pinMode(button6, INPUT);

  pinMode(Linear_solenoid, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(notthing,OUTPUT);
}

void loop() {
  
  check_button();
  control_led();
  control_BUZZER();
}

