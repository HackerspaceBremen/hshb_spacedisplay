 #ifdef USE_STREAMING_PARSER
 
 #include "DWDAPI.h"
 #include "JsonListener.h"

 void DWDListener::whitespace(char c) {
  Serial.println("whitespace");
}

void DWDListener::startDocument() {
  Serial.println("start document");
}

void DWDListener::key(String key) {
  Serial.println("key: " + key);
}

void DWDListener::value(String value) {
  Serial.println("value: " + value);
}

void DWDListener::endArray() {
  Serial.println("end array. ");
}

void DWDListener::endObject() {
  Serial.println("end object. ");
}

void DWDListener::endDocument() {
  Serial.println("end document. ");
}

void DWDListener::startArray() {
   Serial.println("start array. ");
}

void DWDListener::startObject() {
   Serial.println("start object. ");
}
#endif
