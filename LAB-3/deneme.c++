#include <iostream>
#include <string>

int main() {
    std::string kelime;
    std::cout << "Test edilecek kelimeyi gir: ";
    std::cin >> kelime;
    std::cout << "Girilen laaa kelimenin uzunlugunu yaz bro: " << kelime.length() << " karakter." << std::endl;
    return 0;
}

