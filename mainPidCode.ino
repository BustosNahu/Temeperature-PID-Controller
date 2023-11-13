#include <PID_v1.h>

#include <DHT.h>

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321


// Define the DHT11 sensor pin
const int dhtPin = 13;

// Define the setpoint temperature
const double setpointTemperature = 29.0;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
const double KP = 20;
const double KI = 0;
const double KD = 0;
// Create a PID object
PID myPID(&Input, &Output, &setpointTemperature, KP, KI, KD, AUTOMATIC);

// Create a DHT object
DHT dht(dhtPin, DHTTYPE);

// Setup the motor driver pin
int enA = 11; // PWM for Motor A
int in1 = 7;  // Control Rotation of Motor A
int in2 = 8;  // Control Rotation of Motor A

void setup() {

  Serial.begin(9600);

  //Setup pines
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(dhtPin,INPUT);
  // Initialize the PID object

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255);

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
  digitalWrite(in1, LOW); // Input1 LOW = move forward
  digitalWrite(in2, HIGH);  // Input2 HIGH = move forward

  if(Output < 30){
    digitalWrite(in1, HIGH); // Input1 LOW = move forward
    digitalWrite(in2, LOW);  // Input2 HIGH = move forward
    Serial.println("MOTOR STOP");

  }else{
    Serial.println("MOTOR FORWARD");
  }

  analogWrite(enA, Output); // PWM output
  // Print the temperature and the PID output to the serial monitor
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("PID output: ");
  Serial.println(Output);


  // Delay for 1 second
  delay(500);
}