#include <Servo.h> 
#define GREEN 2
#define YELLOW 3
#define RED 4
#define L1 134
#define L2 81
#define L3 74
#define pi 3.14159265358

#define sqr(x) ((x) * (x))

Servo ground, shoulder, pen;

int rad_to_angle(float rad) {
   return rad / pi * 180; 
}

void move_to_xyz(int x, int y, int z) {
    float t1 = atan2(y, x);
    float p = sqrt(sqr(x) + sqr(y));
    float c3 = (sqr(p) + sqr(z - L1) - sqr(L2) - sqr(L3)) / (2 * L2 * L3);
    float s3 = sqrt(1 - sqr(c3));
    float t3 = atan2(s3, c3);
    float k1 = L2 + L3 * c3;
    float k2 = L3 * s3;
    float t2 = atan2(p, (z - L1)) - atan2(k2, k1);
    Serial.write(rad_to_angle(t1));
    Serial.write(", ");
    Serial.write(rad_to_angle(pi - t2));
    Serial.write(", ");
    Serial.write(rad_to_angle(t3));
    Serial.write("\n");
//    move_to(rad_to_angle(t1), rad_to_angle(pi - t2), rad_to_angle(t3));
}


void move_to(int t1, int t2, int t3) {
  int init_t1 = ground.read();
  int init_t2 = shoulder.read();
  int init_t3 = pen.read();
  int num_iters =  max(max(abs(t1 - init_t1), abs(t2 - init_t2)), abs(t3 - init_t3));
  for (int i = 0; i < num_iters; ++i) {
     ground.write(map(i, 0, num_iters - 1, init_t1, t1));
     shoulder.write(map(i, 0, num_iters - 1, init_t2, t2));
     pen.write(map(i, 0, num_iters - 1, init_t3, t3));    
     delay(20);
  } 
}

void blink(int pin, int iters) {
   for (int i = 0; i < iters; ++i) {
      digitalWrite(pin, HIGH);
      delay(500);
      digitalWrite(pin, LOW);
      delay(500);
   } 
}

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  
  digitalWrite(RED, HIGH);
  
  ground.attach(10);
  shoulder.attach(9);
  pen.attach(11);
  
  move_to(0, 90, 0); 
  delay(15000);
  blink(RED, 5);
  
  digitalWrite(YELLOW, HIGH);
  
  move_to(45, 45, 0);
  delay(2000);
  
  digitalWrite(YELLOW, LOW);
  
  Serial.begin(9600);
  
}

void loop() {
//  if(Serial.available() > 0) {
//    while (!(Serial.read() == 's'));
//    digitalWrite(GREEN, HIGH);
//    int t1 = Serial.parseInt();
//    int t2 = Serial.parseInt();
//    int t3 = Serial.parseInt();
//    move_to(t1, t2, t3);
//    digitalWrite(GREEN, LOW);
//  }
move_to(90, 82, 90);
move_to(86, 82, 94);
move_to(81, 81, 96);
move_to(75, 80, 98);
move_to(68, 80, 100);
move_to(61, 79, 101);
move_to(53, 79, 102);
move_to(45, 78, 102);
move_to(37, 79, 102);
move_to(29, 79, 101);
move_to(22, 80, 100);
move_to(15, 80, 98);
move_to(9, 81, 96);
move_to(4, 82, 94);
move_to(0, 82, 90);
move_to(0, 82, 90);
move_to(4, 82, 94);
move_to(9, 81, 96);
move_to(15, 80, 98);
move_to(22, 80, 100);
move_to(29, 79, 101);
move_to(37, 79, 102);
move_to(45, 78, 102);
move_to(53, 79, 102);
move_to(61, 79, 101);
move_to(68, 80, 100);
move_to(75, 80, 98);
move_to(81, 81, 96);
move_to(86, 82, 94);
move_to(90, 82, 90);
}
