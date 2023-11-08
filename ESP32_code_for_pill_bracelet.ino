#include <WiFi.h>
#include <Arduino.h>
#include <U8x8lib.h> 
 //The above code block Imports libraries for Wifi connection, arduino and screen graphics respectively

#define LEFT_COLUMN 1
#define MIDDLE_COLUMN 6
#define RIGHT_COLUMN 11
#define TOP_LINE 0
#define MIDDLE_LINE 3
#define BOTTOM_LINE 6
#define COLUMN(j) j
#define LINE(i) i 
//The above code block sets the components of the screen as variables so text can be displayed on it.

#define print(column, line, string) \
  ; \
  u8x8.drawString(column, line, string);
//Uses u8x8 library to draw the string on the screen when it is printed


U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(22, 21, U8X8_PIN_NONE);//Sets SCL and SDA pins


void initializeScreen() {//Initia.izes the screen
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_pxplusibmcgathin_f);
}


String ClientRequest;//Variable that holds the value sent from the phone to the URL
WiFiServer server(80);//Sets up the wifi server
void setup() {
  ClientRequest = "";

  pinMode(27, INPUT);
  pinMode(18, INPUT);
  pinMode(34, INPUT);
  pinMode(4, INPUT);
//Sets the input pins to read values from the buttons

  Serial.begin(115200);//Begins BAUDS
  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("ROHIT", "RockyDog");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.println("..");
  }
  initializeScreen();


  u8x8.clear();//Empties screen

  
  
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));//Prints IP adress of esp32
  server.begin();
  u8x8.clear();
}


void loop() {
  int aa = digitalRead(27);
  int bb = digitalRead(18);
  int cc = digitalRead(4);
  int dd = digitalRead(34);
//Reads boolean value representing burtton's state

  WiFiClient client = server.available();
  if (!client) { return; }
 //Checks if the server is available

  while (!client.available()) { delay(1); }//Waits till it is available
  ClientRequest = (client.readStringUntil('\r'));
  ClientRequest.remove(0, 5);
  ClientRequest.remove(ClientRequest.length() - 9, 9);
 //Gets readable value   

   if (Serial.available() > 0) {
    if (ClientRequest == "3&submit=Submit" ) {
    u8x8.clear();

    // Draw the big number 3 using asterisks (*)
    print(LEFT_COLUMN, MIDDLE_LINE - 1, "   ***   ");
    print(LEFT_COLUMN, MIDDLE_LINE, "      *  ");
    print(LEFT_COLUMN, MIDDLE_LINE + 1, "   ***   ");
    print(LEFT_COLUMN, MIDDLE_LINE + 2, "      *  ");
    print(LEFT_COLUMN, MIDDLE_LINE + 3, "   ***   ");
     delay(5000);
    u8x8.clear();
  }
  if (ClientRequest == "4&submit=Submit" ) {
    u8x8.clear();
    print(LEFT_COLUMN, MIDDLE_LINE - 1, "   *  *   ");
    print(LEFT_COLUMN, MIDDLE_LINE, "   *  *   ");

    print(LEFT_COLUMN, MIDDLE_LINE + 1, "   ****   ");

    print(LEFT_COLUMN, MIDDLE_LINE + 2, "      *   ");

    print(LEFT_COLUMN, MIDDLE_LINE + 3, "      *   ");
     delay(5000);
    u8x8.clear();
  }
  if (ClientRequest == "1" ) {
    u8x8.clear();
    print(LEFT_COLUMN, MIDDLE_LINE - 1, "     **  ");
    print(LEFT_COLUMN, MIDDLE_LINE, "    * *  ");
    print(LEFT_COLUMN, MIDDLE_LINE + 1, "      *  ");
    print(LEFT_COLUMN, MIDDLE_LINE + 2, "      *  ");
    print(LEFT_COLUMN, MIDDLE_LINE + 3, "     *** ");
     delay(5000);
    u8x8.clear();
  }
  if (ClientRequest == "2&submit=Submit" ) {
    u8x8.clear();
    print(LEFT_COLUMN, MIDDLE_LINE - 1, "    **** ");
    print(LEFT_COLUMN, MIDDLE_LINE, "       * ");
    print(LEFT_COLUMN, MIDDLE_LINE + 1, "    **** ");
    print(LEFT_COLUMN, MIDDLE_LINE + 2, "    *    ");
    print(LEFT_COLUMN, MIDDLE_LINE + 3, "    **** ");
    delay(5000);
    u8x8.clear();
  }
   }
//Checks what the value written to the URL by the smartphone is and prints the associated number


  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println(String(aa) + " "+String(bb) + " "+String(cc) +" "+ String(dd));
  //Sends the value of the buttons as a string to the app

client.println("</html>");

delay(1);
client.flush();
delay(1000);
}