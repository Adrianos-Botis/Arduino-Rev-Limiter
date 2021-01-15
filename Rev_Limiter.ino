// Rev-Limiter Code for Arduino Project Hub
//
//Written by Adrianos Botis: adrianosbotis@gmail.com
//
//Use at your own and change the parameters: rpm_val to set the rpm limit of your engine.
//You can also change the delay of milliseconds at the end of the code to set how fast your engine will be switched on-off.
//


const int sensor_pin = 3;
// set number of hall trips for RPM reading (higher improves accuracy)
float sensor_thresh = 44.0;  //Changed the threshold value to 44 wich corresponds to 1 rotation
float rev_limit = 8000.0;    // Set your rev limiter rpm of your choice
int ignition = 2;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // make the sensor pin an input:
  pinMode(sensor_pin, INPUT);
  pinMode(ignition, OUTPUT);
}

// this loop routine runs over and over again forever:
void loop() {
  // preallocate values for tach
  float hall_count = 1.0;
  float start = micros();
  bool on_state = false;
  // counting number of times the hall sensor is tripped
  // but without double counting during the same trip
  while(true){
    if (digitalRead(sensor_pin) == 1){
      if (on_state==false){
        on_state = true;
        hall_count+=1.0;
      }
    } else{
      on_state = false;
    }
    
    if (hall_count>=sensor_thresh){
      break;
    }
  }
  
  // print information about Time and RPM
  float end_time = micros();
  float time_passed = ((end_time-start)/1000000.0);
  Serial.print("Time Passed: ");
  Serial.print(time_passed);
  Serial.println("s");
  float rpm_val = (60/(2*time_passed));
   if(rpm_val > rev_limit){
     digitalWrite(ignition, HIGH);
     } 
     else { 
     digitalWrite(ignition, LOW);
  } 
  
  Serial.print(rpm_val);
  delay(1);        // delay in between reads for stability
}
