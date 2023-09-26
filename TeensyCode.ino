
#define relay_all 7
#define relay_drive 24
#define relay_arm 25



#define CURR_ARM 22
#define CURR_DRIVE 21
#define CURR_ALL 20

#define DRIVE_IN_1A 29  ///A BRIDGE
#define DRIVE_IN_1B 30   //// B BRIDGE
#define DRIVE_IN_2A 31 /// 31 and 31 are CS (Chip Select) and SCK which can be set to digital HIGH/LOW
#define DRIVE_IN_2B 32 

#define DRV_EN_A 34
#define DRV_EN_B 35

String incomingByte;
int state;
#include<iostream>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay_all, OUTPUT);
  pinMode(relay_drive, OUTPUT);
  pinMode(relay_arm, OUTPUT);

  pinMode(DRIVE_IN_1A, OUTPUT);
  pinMode(DRIVE_IN_1B, OUTPUT);
  pinMode(DRIVE_IN_2A, OUTPUT);
  pinMode(DRIVE_IN_2B, OUTPUT);
  
  pinMode(DRV_EN_A, OUTPUT);
  pinMode(DRV_EN_B, OUTPUT);

  pinMode(CURR_ARM, INPUT);
  pinMode(CURR_ALL, INPUT);  
  pinMode(CURR_ARM, INPUT);

  pinMode(26, OUTPUT);
  drivee(DRIVE_IN_1A, DRIVE_IN_2A, DRIVE_IN_1B, DRIVE_IN_2B);  ////Setting up bridge A and B to allow current to flow through bridges.
  
  drive_en(DRV_EN_A, HIGH);   //Turning the enable pin for BRIDGE A high to activate bridge. If low, bridge A off!
  drive_en(DRV_EN_B, HIGH);   //Turning the enable pin for BRIDGE A high to activate bridge. If low, bridge A off!

  
  relay_init(relay_all, HIGH);
  relay_init(relay_drive, HIGH);
  relay_init(relay_arm, HIGH);


    

}


int check_state(String my_str,int i){

  char ind_char= my_str.charAt(i+1);
  char one ='1';
  char zero = '0';
  //Serial.println(ind_char);
  if (ind_char==one) {
    int state = 1;
    //Serial.println("YWES");
    //Serial.println(state);
    return state;
  }
  else{
    //Serial.println("nope");
    int state = 0;
    return state;
  }


}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available() > 0) {
      // read the incoming byte:
//      String New_String = Serial.readString(); 
//      String crazy = "hi"+ New_String;
      //Serial.print("crazy");
String incomingString = Serial.readString();
      //Serial.print(incomingString);
    String my_str = incomingString;
   
   
   String comp;
   for(int i = 0; i<my_str.length(); i++) {
      char cur_char = my_str.charAt(i);
      //Serial.println(my_str.charAt(i));
      //Serial.println(cur_char);
      //Serial.println(comp);
      comp = comp + cur_char;
      if (cur_char == ':'){
        //Serial.print(comp);
        
          if (comp=="arm:"){
             int state = check_state(my_str, i);
             relay_init(relay_arm, state);
             Serial.println("arm");
             Serial.println(state);
             digitalWrite(26, HIGH);

          }
          if (comp=="all:"){
             int state = check_state(my_str, i);
             relay_init(relay_all, state);
             Serial.println("all");
                          Serial.println(state);
          }
          if (comp=="drive:"){
             int state = check_state(my_str, i);
             relay_init(relay_drive, state);
             Serial.println("arm");
                          Serial.println(state);
          }
          if (comp=="control:"){
             int state = check_state(my_str, i);
             relay_init(relay_drive, state);
             relay_init(relay_all, state);
             relay_init(relay_arm, state);
             Serial.println("arm");
                          Serial.println(state);
                          break;
          }
          i+=2;   
          comp = "";
      
      }

            //tSerial.println(comp);
      
      

      
        
      

      
   }
   //delay(10);
      }


    
    static unsigned long
        timeRelay = 0;
    unsigned long
        timeNow;

        
    //update every 50mS
    timeNow = millis();

//    if( timeNow - timeRelay >= 150 )
//    {
//        timeRelay = timeNow;
//        relay_control(CURR_ALL, relay_all);
//        relay_control(CURR_DRIVE, relay_drive);
//        relay_control(CURR_ARM, relay_arm);
//          
//    }

    

    

}
// if (Serial1.available() > 0){ 
     // state = Serial1.read(); }
