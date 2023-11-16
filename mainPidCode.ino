#include <PID_v1.h>

#include <DHT.h>

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321


// Define the DHT11 sensor pin
const int dhtPin = 13;

// Define the setpoint temperature
const double setpointTemperature = 25.4;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
const double KP = 3;
const double KI = 5;
const double KD = 0.1;
// Create a PID object
PID myPID(&Input, &Output, &setpointTemperature, KP, KI, KD, AUTOMATIC);

// Create a DHT object
DHT dht(dhtPin, DHTTYPE);

// Setup the motor driver pin
int enA = 11; // PWM for Motor A
int in1 = 7;  // Control Rotation of Motor A
int in2 = 8;  // Control Rotation of Motor A

int ledSetPoint = 20;
int enB = 10; //pwm for LEd
int in3 = 12;  // Control Rotation of Motor A
int in4 = 9;  // Control Rotation of Motor A

void setup() {

  Serial.begin(9600);

  //Setup pines
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(dhtPin,INPUT);
  // Initialize the PID object

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(30,255);

  // Initialize the DHT sensor
  dht.begin();
}

// Main loop
void loop() {
  // Read the temperature from the DHT sensor
  double temperature = dht.readTemperature();
  // Calculate the PID output
  Input = temperature;

  myPID.Compute();
  // Set the PWM of the motor driver based on the PID output

  analogWrite(enB, ledSetPoint);
  digitalWrite(in3, HIGH); //led on
  digitalWrite(in4, LOW);

  if(Output < 30){
    digitalWrite(in1, LOW); // Input1 LOW = move forward
    digitalWrite(in2, LOW);  // Input2 HIGH = move forward
    Serial.println("Motor STOP");
  }else{
    digitalWrite(in1, LOW); // Input1 LOW = move forward
    digitalWrite(in2, HIGH);  // Input2 HIGH = move forward
    Serial.println("Motor FORWARD");
  }

  analogWrite(enA, (abs(Output))); // PWM output
  // Print the temperature and the PID output to the serial monitor
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("PID output: ");
  Serial.println(abs(Output));


  // Delay for 1 second
  delay(500);
}
