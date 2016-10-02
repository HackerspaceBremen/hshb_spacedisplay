#ifdef USE_STREAMING_PARSER

#include "SpaceAPI.h"
#include "JsonListener.h"
 
 void SpaceAPIListener::whitespace(char c) {
  Serial.println("whitespace");
}

void SpaceAPIListener::startDocument() {
  Serial.println("start document");
}

void SpaceAPIListener::key(String key) {
  Serial.println("key: " + key);
}

void SpaceAPIListener::value(String value) {
  Serial.println("value: " + value);
}

void SpaceAPIListener::endArray() {
  Serial.println("end array. ");
}

void SpaceAPIListener::endObject() {
  Serial.println("end object. ");
}

void SpaceAPIListener::endDocument() {
  Serial.println("end document. ");
}

void SpaceAPIListener::startArray() {
   Serial.println("start array. ");
}

void SpaceAPIListener::startObject() {
   Serial.println("start object. ");
}

#endif
