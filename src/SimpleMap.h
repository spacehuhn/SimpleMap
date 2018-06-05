#ifndef SimpleMap_h
#define SimpleMap_h

template<class T>
struct Node {
  String key;
  T        data;
  Node<T>* next;
};

template<typename T>
class SimpleMap {
  public:
    SimpleMap();
    ~SimpleMap();

    int size();
    void clear();
    void remove(String key);
    void put(String key, T obj);
    T get(String key);
    bool has(String key);
    String toJson();

  protected:
    int listSize;
    Node<T>* listBegin;
    Node<T>* listEnd;

    Node<T>* getNode(String key);
};

template<typename T>
SimpleMap<T>::SimpleMap() {
  listBegin = NULL;
  listEnd   = NULL;
  listSize  = 0;
}

// Clear Nodes and free Memory
template<typename T>
SimpleMap<T>::~SimpleMap() {
  clear();
}

template<typename T>
void SimpleMap<T>::clear() {
  Node<T> h = listBegin;
  Node<T> toDelete;
  while (h) {
    toDelete = h;
    h = h->next;
    delete toDelete;
  }

  listBegin = NULL;
  listEnd   = NULL;
  listSize  = 0;
}

template<typename T>
int SimpleMap<T>::size() {
  return listSize;
}

template<typename T>
void SimpleMap<T>::put(String key, T obj) {
  // create new node
  Node<T>* newNode = new Node<T>();
  newNode->next = NULL;
  newNode->data = obj;
  newNode->key = key;

  // look if already in list
  Node<T>* h = listBegin;
  Node<T>* p = NULL;
  bool found = false;
  
  if (listSize > 0) {
    while (h != NULL && !found) {
      if (h->key == key) {
        found = true;
      } else {
        p = h;
        h = h->next;
      }
    }
  }

  // replace old node with new one
  if (found) {
    if(h == listBegin) listBegin = newNode;
    if(h == listEnd) listEnd = newNode;
    if (p) p->next = newNode;
    newNode->next = h->next;
    delete h;
  } 
  
  // create new node
  else {
    if (listSize == 0) {
      // add at start (first node)
      listBegin = newNode;
      listEnd = newNode;  
    } else {
      if(key >= listEnd->key) {
        // add at end
        listEnd->next = newNode;
        listEnd = newNode;
      } else if(key <= listBegin->key) {
        // add at start
        newNode->next = listBegin;
        listBegin = newNode;
      } else {
        // insertion sort
        h = listBegin;
        p = NULL;
        found = false;
        while (h != NULL && !found) {
          if (h->key > key) {
            found = true;
          } else {
            p = h;
            h = h->next;
          }
        }
        newNode->next = h;
        if (p) p->next = newNode;
      }
    }
    
    listSize++;
  }
}

template<typename T>
T SimpleMap<T>::get(String key) {
  Node<T>* h = getNode(key);
  return h ? h->data : T();
}

template<typename T>
Node<T>* SimpleMap<T>::getNode(String key) {
  if (listSize > 0) {
    if(key < listBegin->key || key > listEnd->key) return NULL;
    Node<T>* h = listBegin;
    while (h) {
      if (h->key == key) return h;
      else h = h->next;
    }
  }
  return NULL;
}

template<typename T>
void SimpleMap<T>::remove(String key) {
  if (listSize > 0) {
    if(key < listBegin->key || key > listEnd->key) return;
    
    Node<T>* h = listBegin;
    Node<T>* p = NULL;
    bool found = false;
    while (h != NULL && !found) {
      if (h->key == key) {
        found = true;
      } else {
        p = h;
        h = h->next;
      }
    }
    if (found) {
      if (p) p->next = h->next;
      else listBegin = h->next;
      if (listEnd == h) listEnd = p;
      listSize--;
      delete h;
    }
  }
}

template<typename T>
bool SimpleMap<T>::has(String key) {
  return getNode(key) != NULL;
}

template<typename T>
String SimpleMap<T>::toJson() {
  String json = "{";

  Node<T>* h = listBegin;
  while (h != NULL) {
    json += "\"" + h->key + "\":\"" + h->data + "\"";
    if (h->next) json += ",";
    h = h->next;
  }

  json += "}";
  return json;
}

#endif