auto __untie_cin = cin.tie(nullptr);
auto __unsync_ios_stdio = ios_base::sync_with_stdio(false);

struct Node {
    int key = 0, val = 0;
    Node *next = nullptr, *prev = nullptr;
};

class LRUCache {
private:
    unordered_map<int, Node*> mp;
    int capacity;

    Node *head, *tail;

public:
    LRUCache(int capacity): capacity(capacity) {
        head = new Node();
        tail = new Node();

        head->next = tail;
        tail->prev = head;
    }

    void push(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    Node* pop(Node* node) {
        node->next->prev = node->prev;
        node->prev->next = node->next;

        return node;
    }

    int get(int key) {
        if (auto it = mp.find(key); it != mp.end()) {
            push(pop(it->second));
            return it->second->val;
        }

        return -1;
    }
    
    void put(int key, int value) {
        if (auto it = mp.find(key); it != mp.end()) {
            push(pop(it->second));
            it->second->val = value;
            return;
        }

        Node* node;
        if (mp.size() < capacity) {
            node = new Node();
        }
        else {
            node = pop(tail->prev);
            mp.erase(node->key);
        }

        node->key = key;
        node->val = value;
        mp[key] = node;
        push(node);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */