#include <iostream>
#include <string>
using namespace std;

// ================= STACK =================
struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

MoneyBundle* top = NULL;

// PUSH
void pushMoney(string serial, string type, int b100, int b50, int b20) {
    MoneyBundle* newNode = new MoneyBundle;

    newNode->serialNumber = serial;
    newNode->currencyType = type;
    newNode->billCounts[0] = b100;
    newNode->billCounts[1] = b50;
    newNode->billCounts[2] = b20;

    newNode->next = top;
    top = newNode;

    cout << "Para eklendi\n";
}

// POP
MoneyBundle* popMoney() {
    if (top == NULL) {
        cout << "Kasada para yok!\n";
        return NULL;
    }

    MoneyBundle* temp = top;
    top = top->next;
    return temp;
}

// ================= QUEUE =================
struct Customer {
    string customerName;
    string transactionType;
};

const int SIZE = 5;
Customer queueArr[SIZE];

int front = -1;
int rear = -1;

bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return (rear + 1) % SIZE == front;
}

// ENQUEUE
void enqueue(string name, string type) {
    if (isFull()) {
        cout << "Kuyruk dolu!\n";
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % SIZE;
    }

    queueArr[rear].customerName = name;
    queueArr[rear].transactionType = type;

    cout << "Musteri eklendi\n";
}

// DEQUEUE
Customer dequeue() {
    Customer temp;
    temp.customerName = "";
    temp.transactionType = "";

    if (isEmpty()) {
        cout << "Kuyruk bos!\n";
        return temp;
    }

    temp = queueArr[front];

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }

    return temp;
}

// ================= ISLEM =================
void processTransaction() {
    if (isEmpty()) {
        cout << "Musteri yok!\n";
        return;
    }

    if (top == NULL) {
        cout << "Para yok!\n";
        return;
    }

    Customer c = dequeue();
    MoneyBundle* m = popMoney();

    cout << "\nIslem yapildi:\n";
    cout << "Musteri: " << c.customerName << " (" << c.transactionType << ")\n";
    cout << "Kullanilan para: " << m->currencyType << " [";

    for (int i = 0; i < 3; i++) {
        cout << m->billCounts[i];
        if (i < 2) cout << ",";
    }
    cout << "]\n";

    delete m;
}

// ================= GOSTER =================
void displayMoney() {
    cout << "\n--- Para Kasasi ---\n";

    if (top == NULL) {
        cout << "Bos\n";
        return;
    }

    MoneyBundle* temp = top;

    while (temp != NULL) {
        cout << temp->serialNumber << " - " << temp->currencyType << " [";

        for (int i = 0; i < 3; i++) {
            cout << temp->billCounts[i];
            if (i < 2) cout << ",";
        }

        cout << "]\n";
        temp = temp->next;
    }
}

void displayQueue() {
    cout << "\n--- Musteri Kuyrugu ---\n";

    if (isEmpty()) {
        cout << "Bos\n";
        return;
    }

    int i = front;

    while (true) {
        cout << queueArr[i].customerName << " (" << queueArr[i].transactionType << ")\n";

        if (i == rear) break;
        i = (i + 1) % SIZE;
    }
}

// ================= TEMIZLE =================
void freeMemory() {
    while (top != NULL) {
        MoneyBundle* temp = top;
        top = top->next;
        delete temp;
    }
}

// ================= MAIN =================
int main() {
    int secim;
    string name, type, serial, currency;
    int b100, b50, b20;

    while (true) {
        cout << "\n1. Para ekle\n2. Musteri ekle\n3. Islem yap(withdraw-deposit)\n4. Goster\n5. Cikis\nSecim: ";
        cin >> secim;

        if (secim == 1) {
            cout << "Seri numarasi: ";
            cin >> serial;
            cout << "Para kuru: ";
            cin >> currency;
            cout << "100 50 20 adet gir: ";
            cin >> b100 >> b50 >> b20;

            pushMoney(serial, currency, b100, b50, b20);
        }
        else if (secim == 2) {
            cout << "Musteri adi: ";
            cin >> name;
            cout << "Islem tipi: ";
            cin >> type;

            enqueue(name, type);
        }
        else if (secim == 3) {
            processTransaction();
        }
        else if (secim == 4) {
            displayMoney();
            displayQueue();
        }
        else if (secim == 5) {
            freeMemory();
            cout << "Program kapandi\n";
            break;
        }
        else {
            cout << "Hatali secim!\n";
        }
    }

    return 0;
}
