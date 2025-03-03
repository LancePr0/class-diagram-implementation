#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Product {
private:    
    string id;
    string name;
    int price;

public:
    Product(string id, string name, int price) {
        this->id = id;
        this->name = name;
        this->price = price;
    }

    string getId() { return id; }
    string getName() { return name; }
    int getPrice() { return price; }
};

class ShoppingCart {
private:    
    Product* cart[10];
    int quantities[10];
    int count;
    
public:
    ShoppingCart() { count = 0; }

    void addProduct(Product* product, int quantity) {
        if (count < 10) {
            cart[count] = product;
            quantities[count] = quantity;
            count++;
            cout << "Product added successfully!\n";
        } else {
            cout << "Cart is full!\n";
        }
    }

    void viewCart() {
        cout << "Product ID   Name          Price   Quantity\n";
        for (int i = 0; i < count; i++) {
            cout << cart[i]->getId() << "          " << cart[i]->getName();
            for (int j = cart[i]->getName().length(); j < 15; j++) cout << " ";
            cout << cart[i]->getPrice() << "      " << quantities[i] << endl;
        }
    }

    int getCount() { return count; }
    Product* getProduct(int index) { return cart[index]; }
    int getQuantity(int index) { return quantities[index]; }
};

class Order {
private:
    ShoppingCart cart;
    int totalAmount;    
    
public:
    Order(ShoppingCart c) : cart(c) {
        totalAmount = 0;
        for (int i = 0; i < cart.getCount(); i++) {
            totalAmount += cart.getProduct(i)->getPrice() * cart.getQuantity(i);
        }
    }

    void viewOrder() {
        cout << "Total Amount: " << totalAmount << "\nOrder Details:\n";
        cart.viewCart();
    }
};

int main() {
    Product products[] = {
        Product("ABC", "Paper", 20),
        Product("CDE", "Pencil", 10),
        Product("EFG", "Notebook", 50),
        Product("HIJ", "Eraser", 5),
        Product("KLM", "Marker", 30)
    };
    
    ShoppingCart cart;
    Order* orders[10];
    int orderCount = 0;
    
    while (true) {
        cout << "\nMenu:\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\nEnter choice: ";
        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }
        
        if (choice == 1) {
            cout << "Product ID    Name            Price\n";
            for (int i = 0; i < 5; i++) {
                cout << products[i].getId() << "          " << products[i].getName();
                for (int j = products[i].getName().length(); j < 15; j++) cout << " ";
                cout << products[i].getPrice() << endl;
            }
            
            while (true) {
                cout << "Enter the ID of the product you want to add in the shopping cart (or type 'exit' to go back): ";
                string pid;
                cin >> pid;
                if (pid == "exit") break;
                
                bool found = false;
                for (int i = 0; i < 5; i++) {
                    if (products[i].getId() == pid) {
                        int qty;
                        while (true) {
                            cout << "Enter quantity: ";
                            cin >> qty;
                            if (cin.fail() || qty <= 0) {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid quantity! Please enter a valid number.\n";
                            } else {
                                break;
                            }
                        }
                        cart.addProduct(&products[i], qty);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid Product ID!\n";
            }
        }
        
        else if (choice == 2) {
            if (cart.getCount() == 0) {
                cout << "Shopping cart is empty!\n";
            } else {
                cart.viewCart();
                cout << "Do you want to check out all the products? (Y/N): ";
                char ch;
                cin >> ch;
                if (ch == 'Y' || ch == 'y') {
                    orders[orderCount] = new Order(cart);
                    orderCount++;
                    cart = ShoppingCart();
                    cout << "You have successfully checked out the products!\n";
                }
            }
        }
        
        else if (choice == 3) {
            for (int i = 0; i < orderCount; i++) {
                cout << "\nOrder ID: " << i + 1 << endl;
                orders[i]->viewOrder();
            }
        }
        
        else if (choice == 4) {
            break;
        }
    }
    
    return 0;
}
