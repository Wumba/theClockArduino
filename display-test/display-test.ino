// structure for station list
typedef struct
{
  char url[150];   // stream url
  char name[32];   // stations name
  uint8_t enabled; // flag to activate the station
} Station;

#define STATIONS 30 // number of stations in the list

// gloabal variables
Station stationlist[STATIONS];
String ssid = "";
String pkey = "";
String ntp = "de.pool.ntp.org";
boolean connected;
uint8_t curStation = 0;  // index for current selected station in stationlist
uint8_t curGain = 200;   // current loudness
uint8_t actStation = 0;  // index for current station in station list used for streaming
uint32_t lastchange = 0; // time of last selection change
char title[64];          // character array to hold meta data message
bool newTitle = false;
uint32_t tick = 0;   // last tick-counter value to trigger timed event
uint32_t discon = 0; // tick-counter value to calculate disconnected time

// setup
void setup()
{

  setup_display(); // setup display interface

  displayClear();
  displayMessage(0, "Test");
  displayMessage(1, "Test");

  // successful connection
  //  displayClear();
  // setup real time clock
  configTzTime("CET-1CEST,M3.5.0/03,M10.5.0/03", ntp.c_str());
  // show date and time and the name of the station
  displayDateTime();
}

void loop()
{
}
