const int photoiresistor_pin = A4;
const int led_pin = 9;
const int regulator_pin = A0;

float raw_reading;
float filtered_reading = 0;
float alpha = 0.2;
float regulator_reading_value;

float set_point_voltage;

float integral = 0;
float prev_error = 0;
float output = 0;

int delay_time = 100;
unsigned long last_time = 0;

float dt_sec;
float kp = 2.5;
float ki = 1;
float kd = 0;

void setup() {
  pinMode(photoiresistor_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(regulator_pin, INPUT);
  Serial.begin(9600);

  raw_reading = analogRead(photoiresistor_pin);
  filtered_reading = raw_reading;

  last_time = millis();
}

void loop() {

  unsigned long now = millis();

  dt_sec = (now - last_time) / 1000.0;
  last_time = now;

  raw_reading = analogRead(photoiresistor_pin);
  regulator_reading_value = analogRead(regulator_pin);
  set_point_voltage = regulator_reading_value*(5./1023.);

  float raw_voltage = raw_reading*(5./1023.);
  float set_point_value = regulator_reading_value;
  
  filtered_reading =
      alpha * raw_reading +
      (1 - alpha) * filtered_reading;

  float error = set_point_value - filtered_reading;

  integral += error * dt_sec;
  integral = constrain(integral, -1000, 1000);
  float proportional = kp * error;
  float derivative = (error - prev_error) / dt_sec;
  prev_error = error;
  output = proportional + (ki * integral) + (kd * derivative);
  output = constrain(output, 0, 255);

  float output_voltage = output*(5./255.);

  analogWrite(led_pin, output);

  Serial.print("Setpoint:");
  Serial.print(set_point_voltage);
  Serial.print(",Reading:");
  Serial.print(raw_voltage);
  Serial.print(",PWM_output:");
  Serial.println(output_voltage);

  delay(delay_time);
}
