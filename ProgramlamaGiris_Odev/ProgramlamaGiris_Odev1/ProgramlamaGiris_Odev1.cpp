
// GeliÞtirici : Muhammet Emir Aþýlý
// Öðrenci No : B221200062
// Ödev No : 1
// Ödev Konusu : Sipariþ Planlama


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <random>
#include <string>

#define red     "\033[31m"
#define green   "\033[32m"
#define reset   "\033[0m"

using namespace std;

struct Customer {
    int customerNo;
    string* Addres;
    int orderAmount;

};

void dash() {
    for (int i = 0; i <= 25; i++) {
        cout << "--";
    }
    cout << endl;
}

void file(const string& fileName, const vector<Customer>& customerList) {

    ofstream file(fileName);

    if (!file.is_open()) {
        cerr << "Dosya açýlamadý: " << fileName << std::endl;
    }

    file << "\t" << "Sipariþ Listesi" << endl;
    file << "---------------------------------" << endl;
    file << "Müþteri NO" << "\t\t" << "Adres" << "\t\t\t" << "Tutar" << endl;

    for (const auto& Customer : customerList) {
        file << Customer.customerNo << "\t\t\t" << Customer.Addres << "\t\t" << Customer.orderAmount << "\n";
    }

    file.close();
}

void file2(const string& fileName, const vector<Customer>& routeList, const int& totalAmount) {

    ofstream file(fileName, ios::app);

    if (!file.is_open()) {
        cerr << "Dosya açýlamadý: " << fileName << std::endl;
    }

    file << endl << endl << "---------------------------------" << endl;
    file << "\t" << "Daðýtým Rotasý" << endl;
    file << "---------------------------------" << endl;

    for (const auto& Customer : routeList) {
        file << Customer.customerNo << "\t\t\t" << Customer.Addres << "\t\t" << Customer.orderAmount << "\n";
    }

    file << endl << endl << "---------------------------------" << endl;
    file << "Toplam Tutar: " << totalAmount << endl;
    file << "---------------------------------" << endl;

    file.close();
}

int main()
{
    setlocale(LC_ALL, "Turkish");

    const int customerQuantity = 10;
    const int minOrderAmount = 100;
    const int maxOrderAmount = 1000;


    vector <Customer> customerList;
    vector <Customer> routeList;

    for (int i = 0; i < customerQuantity; i++) {

        Customer customer;
        customer.customerNo = i;
        customer.Addres = new string(to_string(i));
        customer.orderAmount = minOrderAmount + rand() % (maxOrderAmount - minOrderAmount + 1);
        customerList.push_back(customer);
    }

    file("siparisler.txt", customerList);

    routeList = customerList;

    cout << "MÜÞTERÝ NO" << setw(15) << "Adres" << setw(20) << "Tutar" << endl;

    random_shuffle(routeList.begin(), routeList.end());

    int maxAmount = routeList[0].orderAmount;
    int minAmount = routeList[0].orderAmount;
    int totalAmount = 0;

    for (const auto& Customer : routeList) {
        if (Customer.orderAmount > maxAmount) {
            maxAmount = Customer.orderAmount;
        }

        if (Customer.orderAmount < minAmount) {
            minAmount = Customer.orderAmount;
        }
    }


    for (const auto& Customer : routeList) {

        if (Customer.orderAmount == maxAmount) {
            cout << green;
        }

        if (Customer.orderAmount == minAmount) {
            cout << red;
        }

        cout << Customer.customerNo << setw(27) << Customer.Addres << setw(15) << Customer.orderAmount << endl;
        if (!(Customer.orderAmount == maxAmount && Customer.orderAmount == minAmount)) {
            cout << reset;
        }

        totalAmount += Customer.orderAmount;

    }

    dash();

    cout << setw(40) << "Toplam Tutar: " << totalAmount << endl;

    dash();

    cout << endl;

    file2("siparisler.txt", routeList, totalAmount);

    for (int i = 0; i < customerQuantity; i++) {
        for (int j = 0; j < customerQuantity; j++) {
            cout << setw(8) << customerList[i].orderAmount - customerList[j].orderAmount;
        }
        cout << endl;
    }

    system("pause");

    return 0;
}


