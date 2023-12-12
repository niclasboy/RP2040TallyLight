byte counter1;
bool errorBlink;

void TaskAtem(void *pvParameters __attribute__((unused)))  // This is a Task.
{
  for (int i = 0; i < 4; i++) {    
    setOutputPort(previewOut[i], programOut[i]);
  }
  for (int i = 0; i < 4; i++) {    
    testOutputBlocking(previewOut[i], programOut[i]);
  }
  readSettings();
  Ethernet.init(17);
  if(dhcpEnable == 1)
  {
    if (Ethernet.begin(mac) == 0) {
      // Check for Ethernet hardware present
      if (Ethernet.hardwareStatus() == EthernetNoHardware) {
        dataChange = 1;
        ethernetStatus = 0;
        while (true) {
          vTaskDelay(1);  // do nothing, no point running without Ethernet hardware
        }
      }   
      Ethernet.begin(mac, ip, subnet); // initialize the Ethernet device not using DHCP:
    }
  }
  else
  {
    Ethernet.begin(mac,ip, subnet);
  }  
  AtemSwitcher.begin(ipSwitcher);
  AtemSwitcher.connect();
  for (;;) {

  

    Ethernet.maintain();
    auto link = Ethernet.linkStatus();
    switch (link) {
    case LinkON:
      if(ethernetStatus != 3)
      {
        ethernetStatus = 3;
        dataChange = 1;
      }
      if(activeIP != Ethernet.localIP())
      {
        activeIP = Ethernet.localIP();
        dataChange = 1;
      }      
      
      break;
    case LinkOFF:
      if(ethernetStatus != 2)
      {
        ethernetStatus = 2;
        dataChange = 1;
      }   
      break;
    }
    AtemSwitcher.runLoop();
    if(AtemSwitcher.isConnected()){
      atemStatus = 1;
    }else{
      atemStatus = 0;
    }
    if(atemStatus){
      for (int i = 0; i < 4; i++) {
        setOutputByIndex(source[i], previewOut[i], programOut[i]);
      }  
    }else{
      counter1++;
      if(counter1 > 20){ //Alle 20 Sekunden aufrufen!
        counter1 = 0;
        if(errorBlink){
          errorBlink = false;
          for (int i = 0; i < 4; i++) {
            testProgramm(previewOut[i], programOut[i]);
          }
        }else{
          errorBlink = true;
          for (int i = 0; i < 4; i++) {
            testPreview(previewOut[i], programOut[i]);
          }
        }
      }
    }      
    vTaskDelay(100);  // 100 tick delay (100ms) in between reads for stability
  }
}

