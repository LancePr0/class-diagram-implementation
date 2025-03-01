#include <iostream>
#include <string>

using namespace std;

class Product {
public:
    string id;
    string name;
    int price;

    Product(string id, string name, int price) {
        this->id = id;
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart {
public:
    Product* cart[10];
    int quantities[10];
    int count;

    ShoppingCart() {
        count = 0;
    }

    void addProduct(Product* product, int quantity) {
        cart[count] = product;
        quantities[count] = quantity;
        count++;
        cout << "Product added successfully!\n";
    }

    void viewCart() {
        cout << "Product ID   Name          Price   Quantity\n";
        for (int i = 0; i < count; i++) {
            cout << cart[i]->id << "          " << cart[i]->name;
            for (int j = cart[i]->name.length(); j < 15; j++) cout << " ";
            cout << cart[i]->price << "      " << quantities[i] << endl;
        }
    }
};

class Order {
public:
    ShoppingCart cart;
    int totalAmount;

    Order(ShoppingCart c) {
        cart = c;
        totalAmount = 0;
        for (int i = 0; i < cart.count; i++) {
            totalAmount += cart.cart[i]->price * cart.quantities[i];
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
        
        if (choice == 1) {
            cout << "Product ID    Name            Price\n";
            for (int i = 0; i < 5; i++) {
                cout << products[i].id << "          " << products[i].name;
                for (int j = products[i].name.length(); j < 15; j++) cout << " ";
                cout << products[i].price << endl;
            }
            
            while (true) {
                cout << "Enter the ID of the product you want to add in the shopping cart (or type 'exit' to go back): ";
                string pid;
                cin >> pid;
                if (pid == "exit") break;
                
                bool found = false;
                for (int i = 0; i < 5; i++) {
                    if (products[i].id == pid) {
                        cout << "Enter quantity: ";
                        int qty;
                        cin >> qty;
                        cart.addProduct(&products[i], qty);
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Invalid Product ID!\n";
            }
        }
        
        else if (choice == 2) {
            if (cart.count == 0) {
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