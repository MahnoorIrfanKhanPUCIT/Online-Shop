#include <iostream>
#include <string.h>

using namespace std;

class Product
{
	//DATA MEMBERS
	string name;
	double price;
	int quantity;
	int id;
	static int count;

public:

	//CONSTRUCTORS

	//default
	Product()
	{
		name = " ";
		price = 0.0;
		quantity = 0;
		id = 0;

		count++;
	}

	//parameterised
	Product(string name, double price, int quantity, int id)
	{
		this->name = name;
		this->price = price;
		this->quantity = quantity;
		this->id = id;

		count++;
	}

	//destructor
	~Product()
	{
		count--;
	}


	//GETTERS

	string getName()const
	{
		return name;
	}

	double getPrice()const
	{
		return price;
	}

	int getQuantity()const
	{
		return quantity;
	}

	int getId()const
	{
		return id;
	}

	static int getCount()
	{
		return count;
	}


	//SETTERS

	void setName(string name)
	{
		this->name = name;
	}

	void setPrice(double price)
	{
		if (price >= 0)
		{
			this->price = price;
		}
		else
		{
			this->price = 0.0;
		}
	}

	void setQuantity(int quantity)
	{
		if (quantity >= 0)
		{
			this->quantity = quantity;
		}
		else
		{
			this->quantity = 0;
		}
	}

	void setId(int id)
	{
		if (id >= 0)
		{
			this->id = id;
		}
		else
		{
			this->id = 0;
		}
	}

	void print()const
	{
		cout << "*****PRODUCT INFO*****" << endl;
		cout << "NAME: " << name << endl;
		cout << "PRICE: " << price << endl;
		cout << "QUANTITY: " << quantity << endl;
		cout << "ID: " << id << endl;

	}

	//OPERATOR OVERLOAD

	//<
	bool operator<(const Product& obj)const
	{
		return (price < obj.price);
	}

	//>
	bool operator>(const Product& obj)const
	{
		return (price > obj.price);
	}
};

int Product::count = 0;

class Shop
{
	//DATA MEMBERS
	Product* products;
	int totalProducts;
	int currentProducts;

public:

	//CONSTRUCTOR

	//parameterised
	Shop(Product *products,int totalProducts,int currentProducts)
	{
		this->totalProducts = totalProducts;
		this->currentProducts = currentProducts;
		this->products = new Product[totalProducts];

		for (int i = 0; i < totalProducts; i++)
		{
			this->products[i] = products[i];
		}
	}

	//copy
	Shop(const Shop& obj)
	{
		this->totalProducts = obj.totalProducts;
		this->currentProducts = obj.currentProducts;
		this->products = new Product[totalProducts];

		for (int i = 0; i < currentProducts; ++i)
		{
			products[i] = obj.products[i];
		}
	}

	//destructor
	~Shop()
	{
		delete[] products;
	}

	//GETTERS
	Product* getProduct(int id)const
	{
		for (int i = 0; i < currentProducts; i++)
		{
			if (products[i].getId() == id)
			{
				return &products[i];
			}
		}
		return nullptr;
	}

	int getTotalProducts()const
	{
		return totalProducts;
	}

	int getCurrentProducts()const
	{
		return currentProducts;
	}

	//MEMBER FUNCTIONS

	void addProduct(int id, string name, double price, int quantity)
	{
		if (currentProducts < totalProducts)
		{
			Product product(name, price, quantity, id);//take a new product
			products[currentProducts] = product;//add it to the existing array

			currentProducts++;//increment the count
		}
		else
		{
			cout << "The inventory is full." << endl;
		}
	}

	bool removeProduct(int id)
	{
		for (int i = 0; i < currentProducts; i++)	
		{
			if (products[i].getId() == id) //if condition is true 
			{
				for (int j = i; j < currentProducts - 1; j++)  //the loop will operate to decrement the present size by one and then shifting the elements to one left side of the array
				{
					products[j] = products[j + 1];  //iff index at 0 is the required id then the arr[1] would be moved to arr[0] 
				}
				currentProducts--;
				return true;
			}
		}
		return false;
	}

	void displayProduct()const
	{
		for (int i = 0; i < currentProducts; i++)
		{
			products[i].print();
		}
	}

	bool updatePrice(int id, double price)
	{
		for (int i = 0; i < currentProducts; i++)
		{
			if (products[i].getId() == id)
			{
				products[i].setPrice(price);
				return true;
			}
		}
		return false;
	}

	bool updateQuantity(int id, int quantity)
	{
		for (int i = 0; i < currentProducts; i++)
		{
			if (products[i].getId() == id)
			{
				products[i].setQuantity(quantity);
				return true;
			}
		}
		return false;
	}
};

class Cart
{
	//DATA MEMBERS
	Product* products;
	int size;
	int currentSize;
	double totalCost;

	//CONSTRUCTORS
	
	//default
	Cart(int size)
	{
		this->size = size;
		this->currentSize = 0;
		this->totalCost = 0.0;

		products = new Product [size];

		for (int i = 0; i < size; i++)
		{
			products[i] = Product();
		}
	}

	//copy
	Cart(const Cart& obj)
	{
		this->size = obj.size;
		this->currentSize = obj.currentSize;
		this->totalCost = obj.totalCost;

		products = new Product[size];

		for (int i = 0; i < size; i++)
		{
			products[i] = obj.products[i];
		}
	}

	//destructor
	~Cart()
	{
		delete[] products;
	}

	//MEMBER FUNCTION

	bool addProduct(Shop* shop, int id, int quantity) //pointer to shop object
	{
		Product* product = shop->getProduct(id);

		if (product == nullptr || product->getQuantity() < quantity)
		{
			return false; //if the product is not in shop or the cart is the shop didnot have that item for the customer
		}

		if (currentSize >= size)
		{
			return false;
		}

		products[currentSize + 1] = *product;

		totalCost = (totalCost + (product->getPrice() * quantity));
		return true;
	}

	bool removeProduct(int id)
	{
		int index = -1;

		for (int i = 0; i < currentSize; i++)
		{
			if (products[i].getId() == id)
			{
				index = i;
			}
		}

		if (index == -1)
		{
			return false;
		}

		Product rmProduct = products[index];
		int rmQuantity = products[index].getQuantity();

		for (int i = index; i < currentSize-1; i++)//shift the elements to left
		{
			products[i] = products[i + 1];
		}

		currentSize--;

		totalCost = (totalCost - (rmProduct.getPrice() * rmQuantity));

		return true;
	}

	bool updateQuantity(Shop* shop, int id, int quantity)
	{
		Product* product = shop->getProduct(id);

		if (product == nullptr || quantity <= 0 || quantity > products->getQuantity())
		{
			return false; //if the id is not present, no item is added or the added item are more than present inventory
		}

		for (int i = 0; i < currentSize; i++)
		{
			if (products[i].getId() == id)
			{
				int oldQuantity = products[i].getQuantity();
				totalCost = (totalCost - (product->getPrice() * oldQuantity));
				totalCost = (totalCost + (product->getPrice() * quantity));

				return true;
			}
		}
		return false;
	}

	double getTotalCost()const
	{
		return totalCost;
	}

	void displayCart()const
	{
		cout << "CART ITEMS: " << endl;

		for (int i = 0; i < currentSize; i++)
		{
			products[i].print();
		}

		cout << "TOTAL COST:  " << totalCost << endl;
	}

	void clearCart(Shop* shop)
	{
		delete[] products;
		products = new Product[size];
		currentSize = 0;
		totalCost = 0.0;
	}
};

ostream& operator<<(ostream& o_obj, const Product& p_obj)
{
	o_obj << "PRODUCT ID: " << p_obj.getId() << endl;
	o_obj << "PRODUCT NAME: " << p_obj.getName() << endl;
	o_obj << "PRODUCT PRICE: " << p_obj.getPrice() << endl;
	o_obj << "PRODUCT QUANTITY: " << p_obj.getQuantity() << endl;

	return o_obj;
}


int main()
{
	Product products[5] = {
		Product("pencil",20,101,2),
		Product("book",50,102,2),
		Product("eraser",10,103,2),
		Product("marker",20,104,2),
		Product("copy",30,105,2),
	};
}