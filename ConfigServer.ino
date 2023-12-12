#define textBuffSize 50
EthernetClient client;
char textBuff[textBuffSize];
int charsReceived = 0;

void firstContactMessage() {
  client.println("Config tool:");
  String dhcpString;
  if (dhcpEnable == 0) {
    dhcpString = "False";
  } else {
    dhcpString = "True";
  }
  client.println("DHCP Enabled: " + dhcpString);
  client.println("IP Adress:    " + String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]));
  client.println("Subnet:       " + String(subnet[0]) + "." + String(subnet[1]) + "." + String(subnet[2]) + "." + String(subnet[3]));
  client.println("ATEM IP:      " + String(ipSwitcher[0]) + "." + String(ipSwitcher[1]) + "." + String(ipSwitcher[2]) + "." + String(ipSwitcher[3]));
  client.println("--- COMMANDS ---");
  client.println("dhcp <a>                - Set DHCP (y/n)");
  client.println("ipad <aaa.bbb.ccc.ddd>  - Set IP");
  client.println("snet <aaa.bbb.ccc.ddd>  - Set Subnet");
  client.println("atem <aaa.bbb.ccc.ddd>  - Set Atem IP");
  client.println("");
}

byte parseToByte(char a, char b, char c)
{
  char inData[] = {a,b,c};
  return (byte)strtoll(inData, NULL, 10);
}

void parseReceivedText()
{
  if(textBuff[1] == 'd' && textBuff[2] == 'h' && textBuff[3] == 'c' && textBuff[4] == 'p' && textBuff[5] == ' ') //Set DHCP
  {    
    if(textBuff[6] == 'y'){
      client.println("DHCP ENABLED - Please restart!");
      dhcpEnable = 1;
      eepromWrite();
    }else if(textBuff[6] == 'n'){
      client.println("DHCP DISABLED - Please restart!");
      dhcpEnable = 0;
      eepromWrite();
    }else{
      client.println("DHCP WRONG FORMATTED");
    }
  }
  else if(textBuff[1] == 'i' && textBuff[2] == 'p' && textBuff[3] == 'a' && textBuff[4] == 'd' && textBuff[5] == ' ') //Set IP Adress
  {
    if(!(textBuff[6] == '<' && textBuff[10] == '.' && textBuff[14] == '.' && textBuff[18] == '.' && textBuff[22] == '>')){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[7]) && isDigit(textBuff[8]) && isDigit(textBuff[9]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[11]) && isDigit(textBuff[12]) && isDigit(textBuff[13]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[15]) && isDigit(textBuff[16]) && isDigit(textBuff[17]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[19]) && isDigit(textBuff[20]) && isDigit(textBuff[21]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    ip[0] = parseToByte(textBuff[7],textBuff[8],textBuff[9]);
    ip[1] = parseToByte(textBuff[11],textBuff[12],textBuff[13]);
    ip[2] = parseToByte(textBuff[15],textBuff[16],textBuff[17]);
    ip[3] = parseToByte(textBuff[19],textBuff[20],textBuff[21]);
    eepromWrite();
    client.println("IP SET - Please restart!");    
  }
  else if(textBuff[1] == 's' && textBuff[2] == 'n' && textBuff[3] == 'e' && textBuff[4] == 't' && textBuff[5] == ' ')
  {
    if(!(textBuff[6] == '<' && textBuff[10] == '.' && textBuff[14] == '.' && textBuff[18] == '.' && textBuff[22] == '>')){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[7]) && isDigit(textBuff[8]) && isDigit(textBuff[9]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[11]) && isDigit(textBuff[12]) && isDigit(textBuff[13]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[15]) && isDigit(textBuff[16]) && isDigit(textBuff[17]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[19]) && isDigit(textBuff[20]) && isDigit(textBuff[21]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    subnet[0] = parseToByte(textBuff[7],textBuff[8],textBuff[9]);
    subnet[1] = parseToByte(textBuff[11],textBuff[12],textBuff[13]);
    subnet[2] = parseToByte(textBuff[15],textBuff[16],textBuff[17]);
    subnet[3] = parseToByte(textBuff[19],textBuff[20],textBuff[21]);
    eepromWrite();
    client.println("SUBNET SET - Please restart!");
  }
  else if(textBuff[1] == 'a' && textBuff[2] == 't' && textBuff[3] == 'e' && textBuff[4] == 'm' && textBuff[5] == ' ')
  {
    if(!(textBuff[6] == '<' && textBuff[10] == '.' && textBuff[14] == '.' && textBuff[18] == '.' && textBuff[22] == '>')){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[7]) && isDigit(textBuff[8]) && isDigit(textBuff[9]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[11]) && isDigit(textBuff[12]) && isDigit(textBuff[13]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[15]) && isDigit(textBuff[16]) && isDigit(textBuff[17]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    if(!(isDigit(textBuff[19]) && isDigit(textBuff[20]) && isDigit(textBuff[21]))){
      client.println("IP WRONG FORMATTED");
      return;
    }
    ipSwitcher[0] = parseToByte(textBuff[7],textBuff[8],textBuff[9]);
    ipSwitcher[1] = parseToByte(textBuff[11],textBuff[12],textBuff[13]);
    ipSwitcher[2] = parseToByte(textBuff[15],textBuff[16],textBuff[17]);
    ipSwitcher[3] = parseToByte(textBuff[19],textBuff[20],textBuff[21]);
    eepromWrite();
    client.println("ATEM IP SET - Please restart!");
  }  
  else
  {
    client.println(" -- COMMAND NOT FOUND");
  }
 }

void getReceivedText()
{
  char c;
  int charsWaiting;

  // copy waiting characters into textBuff
  //until textBuff full, CR received, or no more characters
  charsWaiting = client.available();
  while(charsReceived <= textBuffSize && c != 0x0d && charsWaiting > 0) {
    c = client.read();
    textBuff[charsReceived] = c;
    charsReceived++;
    charsWaiting--;   
  }
  //if CR found go look at received text and execute command
  if(c == 0x0d) {
    parseReceivedText();
    client.flush();
    charsReceived = 0; //count of characters received
    return;
  }

  // if textBuff full without reaching a CR, print an error message
  if(charsReceived >= textBuffSize) {
    client.println("BUFFER OVERRUN");
    client.flush();
    charsReceived = 0; //count of characters received
    return;
  }
  // if textBuff not full and no CR, do nothing else;
  // go back to loop until more characters are received

}

void TaskWebserver(void *pvParameters) {
  (void)pvParameters;
  server.begin();
  for (;;) {
    // Handle new/disconnecting clients.
    if (!haveClient) {
      // Check for new client connections.
      client = server.available();
      if (client) {
        haveClient = true;
        firstContactMessage();
      }
    } else {
      if (client.connected() && client.available()) getReceivedText();
      if (!client.connected()) {  //Timeout
        client.stop();
        client = EthernetClient();
        haveClient = false;
      }
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
