#define VEL_PIN 12
#define ANG_VEL_PIN 11
#define A1 3
#define A2 5
#define B1 6
#define B2 4

#define K 0.3

#define VEL_THRESHOLD 1470
#define ANG_VEL_THRESHOLD 1460
#define MOVE_THRESHOLD 10

#define WHEEL_DIAM 0.064 // m
#define WHEEL_LEN 0.085 // m

int vel = 0;
int ang_vel = 0;

void move_motor(int num, int val){
  if (num == 1){
    if (val < 0){
      digitalWrite(A1,LOW);
      analogWrite(A2,abs(val));
    }
    else{
      digitalWrite(A2,LOW);
      analogWrite(A1,val);
    }
  }
  else{
    if (val < 0){
      digitalWrite(B1,LOW);
      analogWrite(B2,abs(val));
    }
    else{
      digitalWrite(B2,LOW);
      analogWrite(B1,val);
    }
  } 
}

void move_motors(int left_val, int right_val){
  move_motor(0,left_val);
  move_motor(1,right_val);
}

int find_vl(int vel, int ang_vel){
  return (2*vel - WHEEL_LEN*ang_vel)/4;
}

int find_vr(int vel, int ang_vel){
  return (2*vel + WHEEL_LEN*ang_vel)/4;
}
  
void setup() {
  Serial.begin(9600);
  pinMode(VEL_PIN, INPUT);
  pinMode(ANG_VEL_PIN, INPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(B1,OUTPUT);
  pinMode(B2,OUTPUT);
}

void loop() {
  int new_ang_vel = pulseIn(ANG_VEL_PIN, HIGH);
  float err = new_ang_vel - ang_vel;
  ang_vel += K*err;

  int new_vel = pulseIn(VEL_PIN, HIGH);
  err = new_vel - vel;
  vel += K*err;

  int v = vel - VEL_THRESHOLD;
  int w = ang_vel - ANG_VEL_THRESHOLD;

  int left_vel = find_vl(v, w);
  int right_vel = find_vr(v, w);

  move_motors(left_vel, right_vel);
  
  Serial.print(left_vel);
  Serial.print('\t');
  Serial.print(right_vel);
  Serial.println('\t');
  
  delay(1);
}
