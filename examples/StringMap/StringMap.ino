/*
   ===========================================
      Copyright (c) 2018 Stefan Kremser
             github.com/spacehuhn
   ===========================================
 */

#include <SimpleMap.h>

SimpleMap<String>* myMap;

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("STARTED!");

  myMap = new SimpleMap<String>();
  myMap->put("one","1");
  myMap->put("two","2");
  myMap->put("three","3");

  Serial.println(myMap->toJson());
  
  Serial.println("one: "+myMap->get("one"));
  Serial.println("two: "+myMap->get("two"));
  Serial.println("three: "+myMap->get("three"));
  
  myMap->put("three","33");
  Serial.println();
  
  Serial.println(myMap->toJson());
  
  Serial.println("one: "+myMap->get("one"));
  Serial.println("two: "+myMap->get("two"));
  Serial.println("three: "+myMap->get("three"));

  Serial.println("has three: "+(String)myMap->has("three"));
  Serial.println("has vier: "+(String)myMap->has("vier"));

  myMap->remove("three");
  
  Serial.println("has three: "+(String)myMap->has("three"));
  Serial.println("has vier: "+(String)myMap->has("vier"));

  Serial.println(myMap->toJson());
  myMap->remove("two");
  Serial.println(myMap->toJson());

  Serial.println("END!");
}

void loop() {
  // put your main code here, to run repeatedly:

}