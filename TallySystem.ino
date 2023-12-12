#include <FreeRTOS.h>
#include <task.h>
#include <map>
#include <EEPROM.h>
#include <SPI.h>
#include <Ethernet.h>
#include <CRC8.h>


#include <ATEMbase.h>
#include <ATEMmin.h>

TaskHandle_t TaskAtem_Handler;
TaskHandle_t TaskSerial_Handler;
TaskHandle_t TaskWebserver_Handler;

void TaskAtem( void *pvParameters );
void TaskSerial(void* pvParameters);
void TaskWebserver(void* pvParameters);

ATEMmin AtemSwitcher;
uint8_t tally[20];
EthernetServer server(23);

uint8_t source[] = {6, 7, 8, 9};
uint8_t previewOut[] = {1, 3, 5, 7};
uint8_t programOut[] = {0, 2, 4, 6};

//Ethernet Config
byte mac[] = {
  0x10, 0xA2, 0xBB, 0xCC, 0xDA, 0x02
};
uint8_t  dhcpEnableFallback = 1;
uint8_t  ipFallback[] = {192, 168, 178, 250};  //Fallback IP - if EEPROM fails to load!
uint8_t  subnetFallback[] = {255, 255, 255, 0};  //Fallback Subnet - if EEPROM fails to load!
uint8_t  ipSwitcherFallback[] = {192, 168, 178, 251};  //Fallback Subnet - if EEPROM fails to load!

uint8_t  dhcpEnable = 0;
uint8_t  eepromError = 0;
uint8_t  ip[4];  //Fallback IP - if EEPROM fails to load!
uint8_t  subnet[4];  //Fallback Subnet - if EEPROM fails to load!
uint8_t  ipSwitcher[4];  //Fallback Subnet - if EEPROM fails to load!


bool haveClient = false;
bool firstContact = false;

//Status Variablen
uint8_t dataChange; // Aktualisierung der Daten!
uint8_t ethernetStatus; // Status des Ethernet Controllers 1 - Ethernet fail! 2 - Link Down 3 - Link UP
uint8_t atemStatus; // Status des ATEM Controllers 0 - No connection / 1 - Connected
IPAddress activeIP; // Real IP


void setup() {
  Serial.begin(9600);
  delay( 500 / portTICK_PERIOD_MS );
   Serial.println("======== Start ========");
  EEPROM.begin(128);
  xTaskCreate(
    TaskAtem
    ,  "Atem Communication"  // A name just for humans
    ,  256  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL //Parameters for the task
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  &TaskAtem_Handler ); //Task Handle

  xTaskCreate(
    TaskWebserver
    ,  "Webserver"
    ,  512  // Stack size
    ,  NULL //Parameters passed to the task function
    ,  1  // Priority
    ,  &TaskWebserver_Handler );  //Task handle

  // xTaskCreate(
  //   TaskSerial
  //   ,  "Serial"
  //   ,  256  // Stack size
  //   ,  NULL //Parameters passed to the task function
  //   ,  1  // Priority
  //   ,  &TaskSerial_Handler );  //Task handle

}
void loop() {

}
