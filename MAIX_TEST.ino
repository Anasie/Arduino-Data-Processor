
void setup() {
  Serial.begin(9600);
}

void loop() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char receivedData[100]; // Increase the buffer size to accommodate larger data
  int values[20];         // Array to store the values
  int numValues = 0;      // Variable to track the number of values received

  while (Serial.available() > 0) {
    char newData = Serial.read();

    if (newData == startMarker) {
      recvInProgress = true;
      ndx = 0;
      receivedData[ndx] = '\0'; // Null-terminate the string
    } else if (recvInProgress) {
      if (newData != endMarker) {
        receivedData[ndx] = newData;
        ndx++;
        if (ndx >= sizeof(receivedData)) {
          ndx = sizeof(receivedData) - 1;
        }
      } else {
        receivedData[ndx] = '\0'; // Null-terminate the string
        recvInProgress = false;

        // Tokenize the received data
        char* token;
        char* tempData = receivedData;
        int index = 0;

        token = strtok(tempData, ",");
        while (index < 20 && token != NULL) {
          values[index] = atoi(token);
          token = strtok(NULL, ",");
          index++;
        }
        numValues = index;
      }
    }
  }

  // Print the received values
  for (int i = 0; i < numValues; i++) {
    Serial.print("v");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(values[i]);
  }

  // Add any additional processing or code here

  delay(100); // Adjust the delay as needed for your application
}
