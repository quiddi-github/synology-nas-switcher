/*
Webserver zum Steuern einer Zentralheizung mit Wasserkreislauf
 */

#include <SPI.h>
#include <Ethernet.h>
#include <MemoryFree.h>
const int led1 = 2;          //relay1
const int led2 = 3;          //relay2
const int led3 = 4;          //relay3
const int led4 = 5;          //relay4

void(* resetFunc) (void) = 0; //declare reset function @ address 0

unsigned long ZeitNAS=0;  //some global variables available anywhere in the program
bool NASAn = false;

byte mac[] = { 0x1E, 0xAD, 0x2E, 0xEF, 0xFE, 0xEA };   // mac address
byte ip[] = { 192, 168, 0, 250 };                      // configurate il vostro IP a vostra scelta("192.168.1.89")
byte gateway[] = { 192, 168, 0, 253 };                   // internet access router
byte subnet[] = { 255, 255, 255, 0 };                  //subnet mask
EthernetServer server(80);                             //server port     
//String readString;

void setup() {
 // Apro la comunicazione seriale:
  //Serial.begin(9600);
   //while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
 // }
  //Imposto i pin come OUTPUT
  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, HIGH);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  

  // Inizio la comunicazione Ethernet con il server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
 // Serial.print("server is at ");
 // Serial.println(Ethernet.localIP());
}


void loop() {
  String readString;
  unsigned long AktuelleZeit=0;
  int AnFurNAS = 0;
  int AnFurNASSek = 0;
  AktuelleZeit = millis();
  // Creo una connessione al client
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //Leggo i caratteri da HTTP
        if (readString.length() < 100) {
          //Inserisco i caratteri nella stringa 
          readString += c;
          //Serial.print(c);
         }

         //Se la richiesta HTTP è andata a buon fine
         if (c == '\n') {          
           Serial.println(readString); //scrivi sul monitor seriale per debugging

           if(NASAn){
            AnFurNAS = (ZeitNAS-AktuelleZeit)/60000;
            AnFurNASSek = ((ZeitNAS-AktuelleZeit)-(AnFurNAS * 60000))/1000;
           }
           client.println("HTTP/1.1 200 OK"); //Invio nuova pagina
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://www.progettiarduino.com/uploads/8/1/0/8/81088074/style3.css' />");
           client.println("<TITLE>NAS</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>NAS Power-Button betatigen</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">NAS Power Button betatigen</a>");          //Modifica a tuo piacimento:"Accendi LED 1"
           //client.println("<a href=\"/?button1off\"\">Wasser ausschalten</a><br />");    //Modifica a tuo piacimento:"Spegni LED 1" 
           if(NASAn){
            client.print("<p>Power-Button noch betatigt fur ");
            client.print(AnFurNAS);
            client.print(" Minuten, ");
            client.print(AnFurNASSek);
            client.print(" Sekunden.");
            client.print("</p>");
            }
           else{client.println("<br />"); client.println("<br />"); client.println("<br />");}
           client.println("<br />");
          client.println("<br />"); 
          client.println("<br />"); 
          client.println("<br />");
           client.println("<br />");
           client.println("<a href=\"/\"\">F5</a>");      
           client.println("<br />"); 
           client.println("<br />"); 
           client.println("<br />"); 
           client.println("Freier Speicher:"); 
           client.println(freeMemory());
           client.println("<br />"); 
           client.println("An seit:");  
           client.println(AktuelleZeit/1000);
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           client.stop();
           //Controlli su Arduino: Se è stato premuto il pulsante sul webserver
           if (readString.indexOf("?button1on") >0){
               ZeitNAS = AktuelleZeit+2000;
           }
           if (readString.indexOf("?button1off") >0){
               ZeitNAS = AktuelleZeit;
           }


           if (ZeitNAS > AktuelleZeit){
              digitalWrite(led1, LOW);//Relai ist LOW-Active
              NASAn = true;
           }
           else{
              digitalWrite(led1, HIGH);//Relai ist LOW-Active
              NASAn = false;
           }
            //Cancella la stringa una volta letta
            readString="";  
           
         }
       }
    }
}
if (ZeitNAS <= AktuelleZeit){
  digitalWrite(led1, HIGH);//Relai ist LOW-Active
  NASAn = false;
  }
if ((AktuelleZeit > 600000)&&(!NASAn)){
    resetFunc();  //call reset
}

}
