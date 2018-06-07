/*
   ===========================================
      Copyright (c) 2018 Stefan Kremser
             github.com/spacehuhn
   ===========================================
 */

#include <SimpleMap.h>

SimpleMap<String, String>* myMap;

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("STARTED!");

    myMap = new SimpleMap<String, String>([](String a, String b) -> int {
        if (a > b) return 1;

        if (a == b) return 0;

        if (a < b) return -1;
    });
    myMap->put("one", "1");
    myMap->put("two", "2");
    myMap->put("three", "3");

    Serial.println(myMap->toJson());

    Serial.println("one: " + myMap->get("one"));
    Serial.println("two: " + myMap->get("two"));
    Serial.println("three: " + myMap->get("three"));
    Serial.println("four: " + myMap->get("four"));

    myMap->put("three", "33");
    Serial.println();

    Serial.println(myMap->toJson());

    Serial.println("one: " + myMap->get("one"));
    Serial.println("two: " + myMap->get("two"));
    Serial.println("three: " + myMap->get("three"));
    Serial.println("four: " + myMap->get("four"));

    Serial.println("has three: " + (String)myMap->has("three"));
    Serial.println("has vier: " + (String)myMap->has("vier"));

    myMap->remove("three");

    Serial.println("has three: " + (String)myMap->has("three"));
    Serial.println("has vier: " + (String)myMap->has("vier"));

    Serial.println(myMap->toJson());
    myMap->remove("two");
    Serial.println(myMap->toJson());
}

void loop() {
    // put your main code here, to run repeatedly:
}