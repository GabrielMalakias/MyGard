#include<stdlib.h>

// Digital entries
const int digital_13 = 13;

// Analog entries
const int analog_a0 = 0;

// Calc variables
float calc_digital_13;

// Read variables 
int analog_a0_input = 0;


  
// Entry delimiter
const char entry_delimiter = '%';

void setup() {
// Set serial baud
  Serial.begin(9600);

// Start pin modes
  pinMode(digital_13, OUTPUT);
}

void loop() {
  String out_1; 
  String incoming;
  
  // Reads data
  analog_a0_input = analogRead(analog_a0);
  

 // send data only when you receive data:
 while (Serial.available()) {
    // read the incoming byte: i:1;v:on;t:actuator%
    incoming = Serial.readStringUntil('\n');
    if (incoming.indexOf(";t:actuator%") > -1) {
      //i:1;v:on
      incoming.replace(";t:actuator%", "");
      analyzeActuators(incoming);
    }
 }
  

  // Writes serial
 out_1 = output_1(analog_a0_input);
 Serial.println(out_1);
  
  // Delay
  delay(1000);
}

//i:1;v:19.55
void analyzeActuators(String in) {
   int index = in.indexOf(";");
   String identifier = in.substring(0, index);
   String value = in.substring(index+1);

   if(identifier == "i:2") {
      define_status_input_2(value);
   }
}

void define_status_input_2(String value) {
  if(value == "v:on") {
    digitalWrite(digital_13, HIGH); 
  } else if(value == "v:off") {
    digitalWrite(digital_13, LOW);
  }
}

String output_1(int input) {
  String out = "i:1;";
  out += "v:";
  out += input * 0.4887585532;
  out += ";t:sensor";
  out += entry_delimiter;
  return out;
}
