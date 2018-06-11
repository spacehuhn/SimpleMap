# SimpleMap 
Associative arrays with Arduino! 

Nothing big, just my own implementation of an associative array - also known as Map or HashMap (when you're coming from Java) for all kind of Arduino projects.  

I wrote it to use in my Arduino projects and to learn more about datastructures and C++.  

## Installation

1) [Download](https://github.com/spacehuhn/SimpleMap/archive/master.zip) the source code from GitHub.  
2) Unzip and rename the Folder name to "SimpleMap".  
3) Paste it in your Library folder (Usually located somewhere at documents/Arduino/libraries).  
4) Restart the Arduino IDE.  

You can also just download the [SimpleMap.h](https://github.com/spacehuhn/SimpleMap/blob/master/src/SimpleMap.h) 
file and paste it in your Arduino sketch folder.  

## Usage

### Include the library
```c++
#include <SimpleMap.h>  
```

### Creating a map
```c++
// A map of strings
// Please not that it's necessary to provide a compare function, because it's needed to keep the map sorted!  
SimpleMap<String, String> *myMap = new SimpleMap<String, String>([](String &a, String &b) -> int {
	if (a == b) return 0;      // a and b are equal
	else if (a > b) return 1;  // a is bigger than b
	else return -1;            // a is smaller than b
});
```

### Getting the map size
```c++
int theSize = myMap->size();
```

### Adding elements
```c++
myMap->put("one", "1");
myMap->put("two", "2");
myMap->put("three", "3");
```

### Getting elements
```c++
// get value of element with key "one"
String one = myMap->get("one");

// get index of element with key "one"
int i = myMap->getIndex("one");

// get key of element at index i
String oneKey = myMap->getKey(i);

// get value of element at index i
String oneValue = myMap->getData(i);

// check if element is in list
bool hasOne = myMap->has("one");
```

### Replacing elements
```c++
// to replace or change a value is the same operation as to add value
myMap->put("one", "1"); // adds element with key "one" and value "1"
myMap->put("one", "11"); // sets the value of element with key "one" to "11"
```

### Removing elements
```c++
// remove element with key "one"
myMap->remove("one");

// remove element at index 0
myMap->remove(0);

// clear() will erase the entire map, leaving it with 0 elements
myMap->clear();

// Please note that clear() wont free memory from pointers, you have to manually delete/free those!
// Example:
while(myMap->size() > 0){
	delete myMap->get(0).somePointer;
	myMap->remove(0);
}
```

### Locking the map
```c++
// disables to remove() and put() fore new elements (changing values is allowed!)
myMap->lock();

// Please note that clear() will unlock the map again! A locked map does not protect against clear()

// allow put() and remove() again
myMap->unlock();

// ask if map is locked
bool isLocked = myMap->isLocked();
```
