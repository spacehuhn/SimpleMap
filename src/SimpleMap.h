#ifndef SimpleMap_h
#define SimpleMap_h

#include <stddef.h>
#include <functional>

template<class T, class U>
struct Node {
    T           key;
    U           data;
    Node<T, U>* next;
};

template<typename T, typename U>
class SimpleMap {
    public:
        std::function<int(T a, T b)>compare = NULL;

        SimpleMap(std::function<int(T a, T b)>compare);
        ~SimpleMap();

        virtual int size();
        virtual void clear();
        virtual void remove(T key);
        virtual void put(T key, U obj);
        virtual U get(T key);
        virtual bool has(T key);
        virtual String toJson();

    protected:
        int listSize;
        Node<T, U>* listBegin;
        Node<T, U>* listEnd;

        // Helps get() method by saving last position
        Node<T, U>* lastNodeGot = NULL;
        int lastIndexGot        = 0;
        bool isCached           = false;

        virtual Node<T, U>* getNode(T key);
        virtual Node<T, U>* getNodeIndex(int index);
};

template<typename T, typename U>
SimpleMap<T, U>::SimpleMap(std::function<int(T a, T b)>compare) {
    SimpleMap<T, U>::compare = compare;
    listBegin                = NULL;
    listEnd                  = NULL;
    listSize                 = 0;
}

// Clear Nodes and free Memory
template<typename T, typename U>
SimpleMap<T, U>::~SimpleMap() {
    clear();
}

template<typename T, typename U>
U SimpleMap<T, U>::get(T key) {
    Node<T, U>* h = getNode(key);
    return h ? h->data : U();
}

template<typename T, typename U>
Node<T, U>* SimpleMap<T, U>::getNode(T key) {
    if (listSize > 0) {
        if ((compare(key, listBegin->key) < 0) || (compare(key, listEnd->key) > 0)) return NULL;

        isCached     = true;
        lastIndexGot = 0;
        lastNodeGot  = listBegin;

        Node<T, U>* h = listBegin;

        int lowerEnd = 0;
        int upperEnd = listSize - 1;
        int res;
        int mid = (lowerEnd + upperEnd) / 2;

        int hIndex = 0;

        while (lowerEnd <= upperEnd) {
            h      = lastNodeGot;
            hIndex = lastIndexGot;

            res = compare(key, getNodeIndex(mid)->key);

            if (res == 0) {
                return getNodeIndex(mid);
            } else if (res < 0) {
                // when going left, set cached node back to previous cached node
                lastNodeGot  = h;
                lastIndexGot = hIndex;
                isCached     = true;

                upperEnd = mid - 1;
                mid      = (lowerEnd + upperEnd) / 2;
            } else if (res > 0) {
                lowerEnd = mid + 1;
                mid      = (lowerEnd + upperEnd) / 2;
            }
        }
    }
    return NULL;
}

template<typename T, typename U>
Node<T, U>* SimpleMap<T, U>::getNodeIndex(int index) {
    if ((index < 0) || (index >= listSize)) {
        return NULL;
    }

    Node<T, U>* hNode = listBegin;
    int c             = 0;

    if (isCached && (index >= lastIndexGot)) {
        c     = lastIndexGot;
        hNode = lastNodeGot;
    }

    while (hNode != NULL && c < index) {
        hNode = hNode->next;
        c++;
    }

    if (hNode) {
        isCached     = true;
        lastIndexGot = c;
        lastNodeGot  = hNode;
    }

    return hNode;
}

template<typename T, typename U>
void SimpleMap<T, U>::clear() {
    Node<T, U>* h = listBegin;
    Node<T, U>* toDelete;

    while (h != NULL) {
        toDelete = h;
        h        = h->next;
        delete toDelete;
    }

    listBegin = NULL;
    listEnd   = NULL;
    listSize  = 0;
}

template<typename T, typename U>
int SimpleMap<T, U>::size() {
    return listSize;
}

template<typename T, typename U>
void SimpleMap<T, U>::put(T key, U obj) {
    // create new node
    Node<T, U>* newNode = new Node<T, U>();
    newNode->next = NULL;
    newNode->data = obj;
    newNode->key  = key;

    // look if already in list
    Node<T, U>* h = listBegin;
    Node<T, U>* p = NULL;
    bool found    = false;

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
        if (h == listBegin) listBegin = newNode;

        if (h == listEnd) listEnd = newNode;

        if (p) p->next = newNode;
        newNode->next = h->next;
        delete h;
    }

    // create new node
    else {
        if (listSize == 0) {
            // add at start (first node)
            listBegin = newNode;
            listEnd   = newNode;
        } else {
            if (key >= listEnd->key) {
                // add at end
                listEnd->next = newNode;
                listEnd       = newNode;
            } else if (key <= listBegin->key) {
                // add at start
                newNode->next = listBegin;
                listBegin     = newNode;
            } else {
                // insertion sort
                h     = listBegin;
                p     = NULL;
                found = false;

                while (h != NULL && !found) {
                    if (compare(h->key, key) > 0) {
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

template<typename T, typename U>
void SimpleMap<T, U>::remove(T key) {
    if (listSize > 0) {
        if ((compare(key, listBegin->key) < 0) || (compare(key, listEnd->key) > 0)) return;

        Node<T, U>* h = listBegin;
        Node<T, U>* p = NULL;
        bool found    = false;

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

template<typename T, typename U>
bool SimpleMap<T, U>::has(T key) {
    return getNode(key) != NULL;
}

template<typename T, typename U>
String SimpleMap<T, U>::toJson() {
    String json = "{";

    /*
        Node<T,U>* h = listBegin;

        while (h != NULL) {
            json += "\"" + h->key + "\":\"" + h->data + "\"";

            if (h->next) json += ",";
            h = h->next;
        }
     */
    json += "}";
    return json;
}

#endif // ifndef SimpleMap_h