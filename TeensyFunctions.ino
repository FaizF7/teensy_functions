void drive_en(int DRIVE_EN_PIN, bool stat) {
  digitalWrite(DRIVE_EN_PIN, stat); 
}


void drivee(int DRIVE_IN_1A, int DRIVE_IN_2A, int DRIVE_IN_1B, int DRIVE_IN_2B) {
    digitalWrite(DRIVE_IN_1A, HIGH); 
    digitalWrite(DRIVE_IN_2A, LOW); 
    
    digitalWrite(DRIVE_IN_1B, HIGH); 
    digitalWrite(DRIVE_IN_2B, LOW); 
}




void relay_init(int relay_pin, bool x) {
  digitalWrite(relay_pin, x);
    
}



float voltage_current(float avg_v) {
    float curr = (2.5 - avg_v*(5.0/1024))/0.185;  //could just use voltages as a threshold. 0 curr gives 2.5 V, higher current gives 0V. 
    return curr;
}



float avg_voltage(int curr_read_pin) {  

    int n = 40;
    float Samples = 0;
    
    for (int x = 0; x < n; x++){ //Get 150 samples
        //AcsValue = analogRead(A0);     //Read current sensor values   
        int a1 = analogRead( curr_read_pin );  //CURR_DRIVE
        Samples = Samples + a1;
        //Samples = Samples + AcsValue;  //Add samples together
        delay (3); // let ADC settle before next sample 3ms
    }
    float avg = Samples/n;
    return avg;
}




/// IF CURRENT TOO HIGH, E-STOP. Do we turn everything off
void relay_control(int curr_read_pin, int relay_pin) {
  float thresh = 6.5;        /// max current is 13.51 /// WE don't know 
  
  float avg_v = avg_voltage(curr_read_pin);
  float current = voltage_current(avg_v);

  if (current > thresh) {
    digitalWrite(relay_pin, LOW);
  }
    
      //Do we need to auto turn it back on????????
      
  }


//void LEDs(int led1, int led2, int led3, int led4) {
//
//  ////CONDITIONAL LEDs
//  digital
//
//
//  
//}




///
