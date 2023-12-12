void setOutputPort(uint8_t previewPin, uint8_t programmPin)
{
   pinMode(previewPin, OUTPUT);
   pinMode(programmPin, OUTPUT);
}

void testOutputBlocking(uint8_t previewPin, uint8_t programmPin)
{
  digitalWrite(programmPin, HIGH);
  vTaskDelay(500);
  digitalWrite(programmPin, LOW);
  digitalWrite(previewPin, HIGH);
  vTaskDelay(500);
  digitalWrite(programmPin, LOW);
  digitalWrite(previewPin, LOW);
}

void testProgramm(uint8_t previewPin, uint8_t programmPin){
    digitalWrite(programmPin, HIGH);
    digitalWrite(previewPin, LOW);
}

void testPreview(uint8_t previewPin, uint8_t programmPin){
    digitalWrite(programmPin, LOW);
    digitalWrite(previewPin, HIGH);
}

void setOutputByIndex(uint16_t sources, uint8_t previewPin, uint8_t programmPin)
{
  uint16_t atemTallyFlag = AtemSwitcher.getTallyByIndexTallyFlags(sources);
  if (atemTallyFlag & (1 << 0)) //Program
  {
    digitalWrite(programmPin, HIGH);
    digitalWrite(previewPin, LOW);
    return;
  }
  if (atemTallyFlag & (1 << 1)) //Preview
  {
    digitalWrite(programmPin, LOW);
    digitalWrite(previewPin, HIGH);
    return;
  }
  digitalWrite(programmPin, LOW);
  digitalWrite(previewPin, LOW);
}
