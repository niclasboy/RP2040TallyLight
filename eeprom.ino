#define dhcp 0

#define ipl1 1
#define ipl2 2
#define ipl3 3
#define ipl4 4

#define sub1 5
#define sub2 6
#define sub3 7
#define sub4 8

#define ipa1 9
#define ipa2 10
#define ipa3 11
#define ipa4 12

#define errorCorrection 100

CRC8 crc;

void eepromWrite()
{
  crc.setInitial(0x15);
  crc.restart();
  EEPROM.write(dhcp, dhcpEnable);
  crc.add(dhcpEnable);
  EEPROM.write(ipl1,ip[0]);
  EEPROM.write(ipl2,ip[1]);
  EEPROM.write(ipl3,ip[2]);
  EEPROM.write(ipl4,ip[3]);
  crc.add((uint8_t*)ip, 4);
  EEPROM.write(sub1,subnet[0]);
  EEPROM.write(sub2,subnet[1]);
  EEPROM.write(sub3,subnet[2]);
  EEPROM.write(sub4,subnet[3]);
  crc.add((uint8_t*)subnet, 4);
  EEPROM.write(ipa1, ipSwitcher[0]);
  EEPROM.write(ipa2, ipSwitcher[1]);
  EEPROM.write(ipa3, ipSwitcher[2]);
  EEPROM.write(ipa4, ipSwitcher[3]);
  crc.add((uint8_t*)ipSwitcher, 4);
  EEPROM.write(errorCorrection, crc.calc());
  EEPROM.commit();
}

void readSettings()
{
  crc.setInitial(0x15);
  crc.restart();
  dhcpEnable = EEPROM.read(dhcp);
  crc.add(dhcpEnable);
  ip[0] = EEPROM.read(ipl1);
  ip[1] = EEPROM.read(ipl2);
  ip[2] = EEPROM.read(ipl3);
  ip[3] = EEPROM.read(ipl4);
  crc.add((uint8_t*)ip, 4);
  subnet[0] = EEPROM.read(sub1);
  subnet[1] = EEPROM.read(sub2);
  subnet[2] = EEPROM.read(sub3);
  subnet[3] = EEPROM.read(sub4);
  crc.add((uint8_t*)subnet, 4);
  ipSwitcher[0] = EEPROM.read(ipa1);
  ipSwitcher[1] = EEPROM.read(ipa2);
  ipSwitcher[2] = EEPROM.read(ipa3);
  ipSwitcher[3] = EEPROM.read(ipa4);
  crc.add((uint8_t*)ipSwitcher, 4);
  uint8_t correctionCRC = EEPROM.read(errorCorrection);
  if(correctionCRC != crc.calc())
  {
    //Error EEPROM
    eepromError = 1;
    dhcpEnable = dhcpEnableFallback;
    memcpy(ip, ipFallback, 4);
    memcpy(subnet, subnetFallback, 4);    
    memcpy(ipSwitcher, ipSwitcherFallback, 4);
    eepromWrite();
  }
  String dhcpString;
  if (dhcpEnable == 0) {
    dhcpString = "False";
  } else {
    dhcpString = "True";
  }
  Serial.println("DHCP Enabled: " + dhcpString);
  Serial.println("IP Adress:    " + String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]));
  Serial.println("Subnet:       " + String(subnet[0]) + "." + String(subnet[1]) + "." + String(subnet[2]) + "." + String(subnet[3]));
  Serial.println("ATEM IP:      " + String(ipSwitcher[0]) + "." + String(ipSwitcher[1]) + "." + String(ipSwitcher[2]) + "." + String(ipSwitcher[3]));
}