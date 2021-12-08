/*
 * ----------------------------------------------------------------------------------------------
 * ArduinoSD_Workshop.ino
 * IEEE Section 4 ArduinoSD Workshop
 * 
 * This workshop will use an Arduino board with an SD Adapter Module to 
 * 
 * @license This code is in the public domain.
 * 
 * Created 07-DEC-2021
 * by Fernando Leira Cortel
 * Modified 07-DEC-2021
 * by Fernando Leira Cortel
 * ----------------------------------------------------------------------------------------------
 */

#include <SPI.h>
#include <SD.h>

#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

File inputFile;
File outputFile;

String inp = "";
String out_msg;

// All of the code for this workshop will be inside the setup() function
void setup() {
  // Start Serial and wait until is opened
  Serial.begin(9600);
  while (!Serial);

  // Start SD Card
  Serial.println("--> Starting SD Card");
  if (!SD.begin(4)) {
    Serial.println("Error opening SD Card");
    while (1);
  }
  Serial.println("SD Card started!");

  // If input fiel does not exist, create one with demo name
  if (!SD.exists(INPUT_FILENAME)) {
    inputFile = SD.open(INPUT_FILENAME, FILE_WRITE);
    inputFile.println("John Doe");
    inputFile.close();
  } 
  
  // Open input file
  inputFile = SD.open(INPUT_FILENAME);
  if (inputFile) {
    Serial.println("Input file opened");
    Serial.println("Reading input file...");
    // Add chars readed from input file until the end
    while (inputFile.available()) {
      inp += inputFile.read();
    }
    Serial.println("Done");
    
    // Close input file
    inputFile.close();
    Serial.println("Input file closed");
  }
  else {
    Serial.println("Error opening input file");
  }

  // Create and open output file
  outputFile = SD.open(OUTPUT_FILENAME, FILE_WRITE);
  if (outputFile) {
    Serial.println("Output file opened");
    Serial.println("Writing to output file...");
    out_msg = "Hello " + inp + "!";
    outputFile.println(out_msg);
    Serial.println("Done");
    
    // Close output file
    outputFile.close();
    Serial.println("Output file closed");
  }
  else {
    Serial.println("Error opening output file");
  }
}


// loop() function is empty
void loop() {

}
