/*
   ===========================================
      Copyright (c) 2018 Stefan Kremser
             github.com/spacehuhn
   ===========================================
 */

#include <SimpleMap.h>

SimpleMap<String, String>* myMap;

String toJSON() {
    String s;

    s += '{';

    for (int i = 0; i < myMap->size(); i++) {
        s += "\"" + myMap->getKey(i) + "\":\"" + myMap->getData(i) + "\"";

        if (i < myMap->size() - 1) s += ',';
    }
    s += "}";
    return s;
}

void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("STARTED!");

    // create a map
    myMap = new SimpleMap<String, String>([](String& a, String& b) -> int {
        if (a == b) return 0;

        if (a > b) return 1;

        /*if (a < b) */ return -1;
    });

    // adding elements
    myMap->put("one", "1");
    myMap->put("two", "2");
    myMap->put("three", "3");

    Serial.println(toJSON());

    // getting elements
    Serial.println("\"one\": " + myMap->get("one"));
    Serial.println("\"two\": " + myMap->get("two"));
    Serial.println("\"three\": " + myMap->get("three"));
    Serial.println("\"four\": " + myMap->get("four"));

    // getting index of elements
    Serial.println("index of \"one\": " + (String)myMap->getIndex("one"));
    Serial.println("index of \"two\": " + (String)myMap->getIndex("two"));
    Serial.println("index of \"three\": " + (String)myMap->getIndex("three"));
    Serial.println("index of \"four\": " + (String)myMap->getIndex("four"));

    // changing element values
    myMap->put("three", "33");

    Serial.println(toJSON());
    Serial.println();

    // getting elements
    Serial.println("\"one\": " + myMap->get("one"));
    Serial.println("\"two\": " + myMap->get("two"));
    Serial.println("\"three\": " + myMap->get("three"));
    Serial.println("\"four\": " + myMap->get("four"));

    // check if elements in map
    Serial.println("has \"three\": " + (String)myMap->has("three"));
    Serial.println("has \"vier\": " + (String)myMap->has("vier"));

    // remove an element
    myMap->remove("three");

    // check if elements in map
    Serial.println("has \"three\": " + (String)myMap->has("three"));
    Serial.println("has \"vier\": " + (String)myMap->has("vier"));

    Serial.println(toJSON());
    myMap->remove(1); // delete element at index 1 (1 = index of elemt with key "two")
    Serial.println(toJSON());

    // lock map
    myMap->lock();
    myMap->put("four", "4");
    Serial.println(toJSON());
    Serial.println("Locked: " + (String)myMap->isLocked());

    // unlock map
    myMap->unlock();
    myMap->put("four", "4");
    Serial.println(toJSON());
    Serial.println("Locked: " + (String)myMap->isLocked());
}

void loop() {
    // put your main code here, to run repeatedly:
}