// Code generated by Arduino IoT Cloud, DO NOT EDIT.
const char DEVICE_LOGIN_NAME[]  = "97da790f-b2a9-4fb3-ba91-7c0c9f274d20";

const char SSID[]               = "DeeThunder";    // Network SSID (name)
const char PASS[]               = "12345678";   // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = "PfvX4VjwjXyZ1@RYMiFaxNiPT";    // Secret device password

void onSocketChange();

CloudSwitch socket;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(socket, READWRITE, ON_CHANGE, onSocketChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
