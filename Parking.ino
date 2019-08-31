
const int BUZZER_PIN_ = 8;
const int TRIG_PIN_ = 4;
const int ECHO_PIN_ = 5;

int D = 0;
int ii;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN_, OUTPUT);
  pinMode(ECHO_PIN_, INPUT);
  pinMode(BUZZER_PIN_, OUTPUT);
  delay(100);
}


void loop() {
  get_distance();
  beep();
  //Serial.println(D);
}

void beep() {
  D = clamp(D, 1, 100);
  if(D > 3) {
    delay(D * 10);
  }
    Serial.println(D);
    for(ii = 0; ii < 50; ++ii) {
      digitalWrite(BUZZER_PIN_, HIGH); 
      delay(1);
      digitalWrite(BUZZER_PIN_, LOW);
      delay(1);    
    }
}

void get_distance() {
  digitalWrite(TRIG_PIN_,LOW);
  delayMicroseconds(5);
  
  digitalWrite(TRIG_PIN_, HIGH);
  delayMicroseconds(10);
  
  int dist_aux = int(0.017 *  pulseIn(ECHO_PIN_, HIGH));

  D = (D * 0.5) + (dist_aux * 0.5) ;  
}

int clamp(int value, int min_, int max_) {
  if(value > max_) {
      value = max_;
  } else if(value < min_) {
      value = min_;
  }

  return value;
}
