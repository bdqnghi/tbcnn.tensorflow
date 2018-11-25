class LRUCache {
    typedef std::map<int, int>::iterator Iterator;

public:
    LRUCache(int capacity) {
        elements.clear();
        events.clear();
        time_cut.clear();
        max_capacity = capacity;
        size = moment = 0;
    }

    int get(int key) {
        moment ++;
        if (elements.find(key) != elements.end()) {
            addEvent(key);
            return elements[key];
        }
        return -1;
    }

    void set(int key, int value) {
        moment ++;
        if (elements.find(key) != elements.end()) {
            addEvent(key);
            elements[key] = value;
            return;
        }
        if (size == max_capacity) {
            int erase_key = getTopEvent();
            elements.erase(elements.find(erase_key));
            size --;
        }
        addEvent(key);
        elements[key] = value;
        size ++;
    }

private:
    std::map<int, int> elements;
    std::map<int, int> events, time_cut;
    int max_capacity, size, moment;

    void addEvent(int key) {
        if (events.find(time_cut[key]) != events.end()) {
            events.erase(time_cut[key]);
        }
        time_cut[key] = moment;
        events[moment] = key;
    }

    int getTopEvent() {
        int result = (*events.begin()).second;
        events.erase(events.begin());
        return result;
    }
};

