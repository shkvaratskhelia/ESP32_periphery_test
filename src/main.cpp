#include <Arduino.h>
#include <../src/Config/cinfig.h>
#include <Wire.h>
#include <Ethernet/Ethernet.h>
#include <Periphery/periphery.h>
#include <../src/RFID_readers/SerialReader/ReaderController.h>

#define SERIAL_READER
// #define I2C_READER

EthernetClient ethernetClient;
uint8_t default_mac[6] = {0xe4, 0x88, 0x13, 0x4a, 0x85, 0x90};
char * default_host = "www.google.com";
uint16_t default_port = 80;
#ifdef SERIAL_READER
EMReaderController _reader_controller;
#endif

// void Ligt_up_Led(uint8_t pin, char * text);
// void Buzz(uint8_t pin);
// void Open_Relay(uint8_t pin);
void Periphery_Thread(void (* function)(Periphery * Periphery));
void Set_Start_Times(Periphery * Periphery);
void Set_Up_Pinmodes(Periphery * Periphery);
void Check_n_Set_Pinmodes(Periphery * Periphery);
void Init_Ethernet();
void Test_Ethernet();

// Periphery * Red_LED = new Periphery(LED_PIN_RED, 1000);
// Periphery * Green_LED = new Periphery(LED_PIN_GREEN, 1000);
// Periphery * Blue_LED = new Periphery(LED_PIN_BLUE, 1000);

// Periphery Periphery_Stack[7];
std::vector<Periphery> Periphery_Stack = {
  Periphery(LED_PIN_RED, 1000, 0),
  Periphery(LED_PIN_GREEN, 1000, 500),
  Periphery(LED_PIN_BLUE, 1000, 1500),
};

void setup() {
  delay(1000);
  Serial.begin(SERIAL_BAUD_RATE);
  delay(1000);
  Serial.println("RGB_LED_INITIATED...");
  delay(1000);
  printf("Starting Set Up \n");
  Periphery_Thread(Set_Start_Times);
  // pinMode(LED_PIN_RED, OUTPUT);
  // pinMode(LED_PIN_GREEN, OUTPUT);
  // pinMode(LED_PIN_BLUE, OUTPUT);
  // pinMode(DOOR_RELAY_IN, OUTPUT);
  // pinMode(DOOR_RELAY_OUT, OUTPUT);
  // pinMode(BUZZER_PIN, OUTPUT);
  // pinMode(BUZZER_PIN_2, OUTPUT);
  delay(10);
  pinMode(W5500_CHIP_SELECT_PIN, OUTPUT);
  Init_Ethernet();
}

void loop() {
  // Ligt_up_Led(LED_PIN_RED, "Lighting up LED_PIN_RED");
  // Ligt_up_Led(LED_PIN_GREEN, "Lighting up LED_PIN_GREEN");
  // Ligt_up_Led(LED_PIN_BLUE, "Lighting up LED_PIN_BLUE");
  // Buzz(BUZZER_PIN);
  // Open_Relay(DOOR_RELAY_IN);
  // Buzz(BUZZER_PIN_2);
  // Open_Relay(DOOR_RELAY_OUT);
  // Set_Up_Pinmodes();
  Periphery_Thread(Check_n_Set_Pinmodes);
  Periphery_Thread(Set_Up_Pinmodes);
  Test_Ethernet();
  #ifdef SERIAL_READER
  _reader_controller.Main_Thread();
  #endif
}

void Ligt_up_Led (uint8_t pin, char * text)
{
  // Serial.println(text);
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(200);
}

void Buzz (uint8_t pin) 
{
  digitalWrite(pin, HIGH);
  delay(300);
  digitalWrite(pin, LOW);
  delay(300);
}

void Open_Relay (uint8_t pin) 
{
  digitalWrite(pin, HIGH);
  delay(300);
  digitalWrite(pin, LOW);
  delay(300);
}

void Init_Ethernet ()
{
  Ethernet.init(W5500_CHIP_SELECT_PIN);
  if (Ethernet.begin(default_mac, ETHERNET_CONNECT_TIMEOUT, ETHERNET_RESPONSE_TIMEOUT) == 0)
  {
    Serial.println("Ethernet begin Error !");
    return;
  }
  ethernetClient.connect(default_host, default_port);
}

void Test_Ethernet ()
{
  static uint32_t start_t = millis();
  if (start_t + 5000 < millis())
  {
    start_t = millis();
    if (Ethernet.linkStatus() != LinkON)
    {
      Serial.println("No ethernet link status !");
      return;
    }
    if (!Ethernet.localIP())
    {
      Serial.println("No local IP !");
      return;
    }
    if (!ethernetClient.connected())
    {
        Serial.println("ethernetClient not connected !");
      return;
    }
    Serial.println("Ethernet working properly ");
  }
}

void Periphery_Thread (void (* function)(Periphery * Periphery))
{
  for (std::vector<Periphery>::iterator it = Periphery_Stack.begin(); it != Periphery_Stack.end(); ++it) {
    function(&*it);
  }
}

void Check_n_Set_Pinmodes (Periphery * periphery) 
{
  if (periphery->_initiated && periphery->_start + periphery->_delay + periphery->_time_shift < millis()) {
    // Serial.println("Cheking Periphery : %d", std::distance(Periphery_Stack.begin(), &*periphery));
    periphery->_start = millis();
    periphery->_status = !periphery->_status;
  }
  digitalWrite(periphery->_pin, periphery->_status);
}

void Set_Up_Pinmodes (Periphery * periphery)
{
  // if (periphery->_initiated)
  //   return;
  // if (millis() > (periphery->_start + periphery->_time_shift))
  // {
  //   printf("Seting pin to output mode : %d; initiated : %d; start time : %d; time shift set at : %d; \n", periphery->_pin, periphery->_initiated, periphery->_start, periphery->_time_shift);
  //   periphery->_initiated = true;
  //   pinMode(periphery->_pin, OUTPUT);
  // }
}

void Set_Start_Times (Periphery * periphery)
{
  printf("Initiating pin : %d; at time point : %d; system time: %d; \n", periphery->_pin, periphery->_start, millis());
}