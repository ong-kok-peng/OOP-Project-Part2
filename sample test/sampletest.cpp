#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

class Product {
private:
    string name;
    double price;
public:
    Product(string name, double price) : name(name), price(price) {}
    string getName() { return name; }
    double getPrice() { return price; }
};

class ProductsRO {
public:
    virtual vector<Product> getAllProducts() = 0;
};

class Products : public ProductsRO {
private:
    vector<Product> allproducts;

public:
    Products() { allproducts = {}; }
    void addItem(Product item) {
        allproducts.push_back(item);
    }
    vector<Product> getAllProducts() override {
        return allproducts;
    }
};

class ProductsModifier {
private:
    Products& theproducts;
public:
    ProductsModifier(Products& p) : theproducts{ p } {}
    bool addProduct(string name, double price) {
        regex destPattern(R"(^[a-zA-Z ]+$)");
        if (regex_match(name, destPattern) && price >= 0.0 && price <100.0) {
            Product newProduct(name, price);
            theproducts.addItem(newProduct);
            return true;
        }
        else {
            //error: name or/and price validation failed
            return false;
        }
    }
};

class ProductsViewer { 
private:
    ProductsRO& viewproducts;
public:
    ProductsViewer(ProductsRO& pro) : viewproducts{ pro } {}
    void dispProducts() {
        vector<Product> productsList = viewproducts.getAllProducts();
        if (productsList.size() > 0) {
            for (int a = 0; a < productsList.size(); a++) {
                cout << (a + 1) << ") Name: " << productsList[a].getName() << " Price: " << productsList[a].getPrice() << "\n";
            }
        }
        else {
            cout << "There are no products.\n";
        }
    }
};

int main() {
    Products products;

    ProductsModifier modifyProducts(products);
    ProductsViewer viewProducts(products);
    
    while (true) {
        string productname; double productprice;

        cout << "What is the product name? Or type \"CANCEL\" to stop entering input.\n";
        getline(cin, productname);

        if (productname == "CANCEL") { break; }

        cout << "What is the product price? ";
        cin >> productprice;

        if (cin.fail()) {
            cout << "\nInvalid text input. Please try again\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (modifyProducts.addProduct(productname, productprice)) { cout << "\nProduct added!\n"; }
        else { cout << "\nInvalid product name or/and price is entered.\n"; }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush any leftover newline after the cin
    }

    cout << "\nAll the products shown here:\n";
    viewProducts.dispProducts();
    return 0;
}
