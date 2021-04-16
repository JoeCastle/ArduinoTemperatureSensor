//Include necessary header files
#include <ESP8266WiFi.h>
#include <TextFinder.h>

//Declare variables
float tempCelsius;
int tempPin = A0;
int redLed = 14;
int amberLed = 4;
int greenLed = 5;

//Hotspot ID and password
const char* hotspotID = "";
const char* hotspotPassword = "";

//Host name
const char* host = "";

//Boundary temperatures
int minTemp = 0;
int maxTemp = 0;

//Create wifi client
WiFiClient client;

//Setup
void setup() {
  //Set LED pin modes to output
  pinMode(redLed, OUTPUT);//Red
  pinMode(amberLed, OUTPUT);//Amber
  pinMode(greenLed, OUTPUT);//Green

  Serial.begin(115200);

  //Display the name of the hotspot/network we are connecting to
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(hotspotID);

  //Connect to the hotspot/network using the ID and password
  WiFi.begin(hotspotID, hotspotPassword);

  //Outout "." while not connected to a WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //When connected to a hotspot/network, output the IP address
  Serial.println("");
  Serial.println("Successfully connected to hotspot");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

//Loop
void loop() {
  delay(3000);

  //Output the name of the host we are about to connect to
  Serial.println("");
  Serial.println("");
  Serial.print("Connecting to host: ");
  Serial.println(host);

  //Call the function to get the boundary temperatures from the website
  getTemperatures();

  //this read in the output voltage from the LM35 temperature sensor.
  int sensorOutput = analogRead(tempPin);

  //Work out temperature in degrees celsius from volts.
  float mVolts = (sensorOutput/1024.0) * 3300; //Convert output voltage to millivolts.
  float tempCelsius = mVolts/10; //Convert millivolts to degrees celsius.

  //Output temperature in degrees celsius to the console every three seconds.
  Serial.print("Temperature: ");
  Serial.print(tempCelsius);
  Serial.print("*C");
  Serial.println();

  //Call the function to post the temperature read from the LM35 sensor to the website
  postTemperatures(tempCelsuis);

  //Turn on LED based on the room temperature.
  //Temp too cold.
  if (tempCelsius < minTemp) {
    digitalWrite(redLed, LOW);
    digitalWrite(amberLed, HIGH);
    digitalWrite(greenLed, LOW);
  //Temp too hot.
  } else if (tempCelsius > maxTemp) {
    digitalWrite(redLed, HIGH);
    digitalWrite(amberLed, LOW);
    digitalWrite(greenLed, LOW);
  //Temp ok.
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(amberLed, LOW);
    digitalWrite(greenLed, HIGH);
  }

  //Close the connection
  Serial.println();
  Serial.println();
  Serial.println("Closing connection");
  client.stop();

  delay(3000);
}

//The get request. Retrieves the boundary temperatures from the website
void getTemperatures(){
  //Connect the client to the host using the host name and the port number
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection to host failed");
  }

  //Output a message when we have successfully connected to the host
  Serial.println("Successfully connected to host");
  Serial.println("");
  Serial.println("");

  //Create the HTTP request that will be sent via the post request
  String httpRequest = "user=name&pw=password&id=2";

  //The URL that the HTTP request will be sent to
  const char* url = "/arduino/_device/getTemp.php";
  
  //Output the URL that we are requesting
  Serial.print("Requesting URL: ");
  Serial.println(url);

  //This is the "GET" request. However we will be using a POST request to send information first
  char outputStorage[64];

  //Send request type and protocol type to website
  sprintf(outputStorage,"POST %s HTTP/1.1",url);
  client.println(outputStorage);

  //Send host name to website
  sprintf(outputStorage,"Host: %s",host);
  client.println(outputStorage);

  //Send content type to website
  client.println("Connection: close\r\nContent-Type: application/x-www-form-urlencoded");

  //Send content length to website
  sprintf(outputStorage,"Content-Length: %u\r\n",httpRequest.length());
  client.println(outputStorage);
  
  //Send the variables to the website (httpRequest)
  client.print(httpRequest);

  Serial.println("Successfully requested the URL.");
  Serial.println("");
  Serial.println("");

  Serial.println("Retrieving boundary temperatures.");

  //Get the boundary temperatures
  //Using TextFinder, find the MaxTemp field and store it's value in a variable
  TextFinder theFinder(client);
  if(theFinder.find("MaxTemp: ")) {
    maxTemp = theFinder.getValue();
    Serial.print("The max temp from the website: ");
    Serial.println(maxTemp);
  }

  //Using TextFinder, find the MinTemp field and store it's value in a variable
  if(theFinder.find("MinTemp: ")) {
    minTemp = theFinder.getValue();
    Serial.print("The min temp from the website: ");
    Serial.println(minTemp);
  }
}

//The post request. Sends the sensor reading to the website
void postTemperatures(float temperature) {
  //Connect the client to the host using the host name and the port number
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection to host failed");
  }

  //Output a message when we have successfully connected
  Serial.println("Successfully connected to host");
  Serial.println("");
  Serial.println("");

  //Create the HTTP request that will be sent via the post request and append the temperature on the end
  String httpRequest = "user=name&pw=password&id=2&loc=MIOpenDeck&temp=";
  httpRequest += temperature;

  //This is the specific URL that we are sending the information to
  const char* url = "/arduino/_device/postTemp.php";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  Serial.println("");

  //This is the POST request. See getTemperatures() for more detailed comments
  char outputStorage[64];
  
  sprintf(outputStorage,"POST %s HTTP/1.1",url);
  client.println(outputStorage);
  
  sprintf(outputStorage,"Host: %s",host);
  client.println(outputStorage);
  
  client.println("Connection: close\r\nContent-Type: application/x-www-form-urlencoded");
  
  sprintf(outputStorage,"Content-Length: %u\r\n",httpRequest.length());
  client.println(outputStorage);

  //Send the variables
  client.print(httpRequest);

  Serial.println("Successfully requested the URL.");
  Serial.println("");
  Serial.println("");
}