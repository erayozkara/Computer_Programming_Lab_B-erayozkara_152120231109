#include <iostream>
#include <string>
using namespace std;

// Sayfa yapýsý
struct Page {
    string url;
    string title;
    int accessTime[3]; // saat, dakika, saniye
    Page* next;
    Page* prev;
};

// global pointerlar
Page* head = NULL;
Page* tail = NULL;
Page* current = NULL;

// yeni sayfa ekleme (sona ekliyoruz)
void visitPage(string url, string title, int h, int m, int s) {
    Page* yeni = new Page;

    yeni->url = url;
    yeni->title = title;
    yeni->accessTime[0] = h;
    yeni->accessTime[1] = m;
    yeni->accessTime[2] = s;

    yeni->next = NULL;
    yeni->prev = NULL;

    // liste boþsa
    if (head == NULL) {
        head = yeni;
        tail = yeni;
        current = yeni;
    }
    else {
        // sona ekle
        tail->next = yeni;
        yeni->prev = tail;
        tail = yeni;

        // en son gidilen sayfa current olur
        current = yeni;
    }

    cout << "Sayfa eklendi\n";
}

// geri gitme
void back() {
    if (current == NULL || current->prev == NULL) {
        cout << "Geri gidilemez\n";
    } else {
        current = current->prev;
        cout << "Geri gidildi\n";
    }
}

// ileri gitme
void forward() {
    if (current == NULL || current->next == NULL) {
        cout << "Ileri gidilemez\n";
    } else {
        current = current->next;
        cout << "Ileri gidildi\n";
    }
}

// mevcut sayfayý silme
void deleteCurrent() {
    if (current == NULL) {
        cout << "Silinecek sayfa yok\n";
        return;
    }

    Page* temp = current;

    // tek eleman varsa
    if (head == tail) {
        head = NULL;
        tail = NULL;
        current = NULL;
    }
    // baþtaysa
    else if (current == head) {
        head = head->next;
        head->prev = NULL;
        current = head;
    }
    // sondaysa
    else if (current == tail) {
        tail = tail->prev;
        tail->next = NULL;
        current = tail;
    }
    // ortadaysa
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        current = current->next;
    }

    delete temp;
    cout << "Sayfa silindi\n";
}

// geçmiþi yazdýr
void display() {
    if (head == NULL) {
        cout << "Gecmis bos\n";
        return;
    }

    Page* gez = head;
    int i = 1;

    while (gez != NULL) {
        cout << i << ". ";

        // current olaný belirt
        if (gez == current) {
            cout << "[SU AN] ";
        }

        cout << gez->title << " (" << gez->url << ") ";

        // saat yazdýrma
        cout << "[";
        for (int j = 0; j < 3; j++) {
            cout << gez->accessTime[j];
            if (j < 2) cout << ":";
        }
        cout << "]\n";

        gez = gez->next;
        i++;
    }
}

// memory temizleme
void temizle() {
    Page* temp = head;

    while (temp != NULL) {
        Page* next = temp->next;
        delete temp;
        temp = next;
    }
}

int main() {
    int secim;
    string url, title;
    int h, m, s;

    while (true) {
        cout << "\n1- Ziyaret et\n2- Geri\n3- Ileri\n4- Sil\n5- Goster\n6- Cikis\nSecim: ";
        cin >> secim;

        if (secim == 1) {
            cout << "URL gir: ";
            cin >> url;
            cout << "Baslik gir: ";
            cin >> title;
            cout << "Saat dk sn gir: ";
            cin >> h >> m >> s;

            visitPage(url, title, h, m, s);
        }
        else if (secim == 2) {
            back();
        }
        else if (secim == 3) {
            forward();
        }
        else if (secim == 4) {
            deleteCurrent();
        }
        else if (secim == 5) {
            display();
        }
        else if (secim == 6) {
            temizle();
            cout << "Program bitti\n";
            break;
        }
        else {
            cout << "Yanlis secim\n";
        }
    }

    return 0;
}
