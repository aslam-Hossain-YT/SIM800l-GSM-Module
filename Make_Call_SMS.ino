char phone_no[]="+8801877543825"; //change +88 with country code and 01888176220 with phone number to sms

#define bt_M  5 // Button1 Pin A0 use for Send Message
#define bt_C  6 // Button2 Pin A1 use for Call

#define LED 2 // Led Pin D2 use for LED

char inchar; // Will hold the incoming character from the Serial shield

void setup(){// put your setup code here, to run once

Serial.begin(19200);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)  
Serial.begin(19200);   //Begin serial communication with Arduino and SIM800L

pinMode(bt_M, INPUT_PULLUP); // declare bt_M as input
pinMode(bt_C, INPUT_PULLUP); // declare bt_C as input

pinMode(LED,OUTPUT); // declare LED as output
  
Serial.println("Initializing....");
// Initialize the Serial module
  Serial.println("AT");
  delay(1000);
  Serial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  Serial.println("AT+CNMI=2,2,0,0,0"); // Configure module to forward SMS to serial
  delay(1000);

  Serial.println("Ready to receive SMS..."); 

}

void loop(){

if(Serial.available() >0){inchar=Serial.read(); Serial.print(inchar); 
 if(inchar=='R'){inchar=Serial.read(); 
 if(inchar=='I'){inchar=Serial.read();
 if(inchar=='N'){inchar=Serial.read();
 if(inchar=='G'){  
    initModule("ATH","OK",1000); // this command is used for Call busy
    }
   }
  }
 }

else if(inchar=='L'){delay(10); inchar=Serial.read(); 
     if(inchar=='E'){delay(10); inchar=Serial.read();
     if(inchar=='D'){delay(10); inchar=Serial.read();

     if(inchar=='1'){digitalWrite(LED, 1); sendSMS(phone_no,"LED is On");}
else if(inchar=='0'){digitalWrite(LED, 0); sendSMS(phone_no,"LED is Off");}
     }
    }
  }
}

int buttonstate1 = digitalRead(bt_M);
int buttonstate2 = digitalRead (bt_C);

Serial.print("buttonstate1 = ");
Serial.println(buttonstate1);
Serial.print("buttonstate2 = ");
Serial.println(buttonstate2);
delay(500);

  if(buttonstate1 == 0){
  sendSMS(phone_no,"Aslam Hossain YouTube. Do Subscribe!");
  }
  else if(buttonstate2 == 0){
  callUp(phone_no);
  }

delay(10);
}



void sendSMS(char *number, char *msg){
Serial.print("AT+CMGS=\"");Serial.print(number);Serial.println("\"\r\n"); //AT+CMGS=”Mobile Number” <ENTER> - Assigning recipient’s mobile number
delay(500);
Serial.println(msg); // Message contents
delay(500);
Serial.write(byte(26)); //Ctrl+Z  send message command (26 in decimal).
delay(3000);  
}

void callUp(char *number){
Serial.print("ATD + "); Serial.print(number); Serial.println(";"); //Call to the specific number, ends with semi-colon,replace X with mobile number
delay(20000);       // wait for 20 seconds...
Serial.println("ATH"); //hang up
delay(100);  
}


void initModule(String cmd, char *res, int t){
while(1){
    Serial.println(cmd);
    Serial.println(cmd);
    delay(100);
    while(Serial.available()>0){
       if(Serial.find(res)){
        Serial.println(res);
        delay(t);
        return;
       }else{Serial.println("Error");}}
    delay(t);
  }
}
