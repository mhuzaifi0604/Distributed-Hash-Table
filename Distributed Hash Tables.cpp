/*
	Data Final Project:-
	Group Members:
Ubaidullah Malik 20I-0541
Muhammad Huzaifa 20I-0604
*/

#include<iostream>
#include<queue>
#include<string>
#include<list>	//Including Necessory Libraries
#include<cmath>


using namespace std;

struct RingStruct;
class RingModel;	//Declaring necessory structs and classes

//Function for calculating hash of machines + corresponding data
int calculatehash(int value, int idenspce)
{
	return value % idenspce; //returning hashed value
}

template <typename T>
bool Contains(T data, list<T> Linkedlist)
{
	if (!Linkedlist.empty())
	{
		typename list <T> ::iterator it;
		for (it = Linkedlist.begin(); it != Linkedlist.end(); ++it)
		{
			if ((*it) == data)
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}

template <typename T>
void Remove_Data(T data, list<T>& Linkedlist)
{
	list<T> NewList;
	if (!Linkedlist.empty())
	{
		typename list <T> ::iterator it;
		for (it = Linkedlist.begin(); it != Linkedlist.end(); ++it)
		{
			if ((*it) != data)
			{
				NewList.push_back(*it);
			}
		}
	}
	Linkedlist = NewList;
}

//Structure of every node for AVL Tree
struct AVLnode
{
	int key;
	list<string> datalist;
	int height;
	AVLnode* left; // Declaring necessory variables & pointers
	AVLnode* right;

	// Default Constructor
	AVLnode()
	{
		key = 0;
		height = -1; //Assigning Default values
		left = NULL;
		right = NULL;
	};

	// Parameterized Constructor
	AVLnode(int k, string d)
	{
		key = k;
		datalist.push_back(d);
		height = 0;
		left = NULL; //Assigning paremeters to varibles and pointers
		right = NULL;
	};

	AVLnode(int k, list<string >d)
	{
		key = k;
		datalist = d;
		height = 0;
		left = NULL; //Assigning paremeters to varibles and pointers
		right = NULL;
	};

	//Parameterized constructotor
	AVLnode(int k, list<string>d, int h, AVLnode* l, AVLnode* r)
	{
		key = k;
		datalist = d; //Assigning
		height = h; //  |
		left = l; // Parameters
		right = r;
	}
};

class AVLTree
{
	AVLnode* root; // Decalring root of Tree

	// PRIVATE FUNCTIONS for Getting rid of Memory INFLATION

	// Function for getting height of each node
	int getheight(AVLnode* node)
	{
		if (node == NULL)
			return -1; //returning -1 in case of empty tree
		return node->height; // returning height of node
	}

	// Function for getting max value
	int max(int num1, int num2)
	{
		return (num1 > num2 ? num1 : num2);// returning max value
	}

	// Function for getting balances factor for each node
	int getbalancefactor(AVLnode* node)
	{
		if (node == NULL)
			return 0; //returning 0 in case of no node
		return getheight(node->left) - getheight(node->right); //returning balance factor by subtracting height of left & right tree
	}

	// Function for displaying nodes inorder
	void inorder(AVLnode* currnode)
	{
		if (currnode != NULL)
		{
			inorder(currnode->left); // Recursive function for left child
			cout << currnode->key << "    " << "\t\t";
			typename list <string> ::iterator it;
			// Running loop until node/data ends
			for (it = currnode->datalist.begin(); it != currnode->datalist.end(); ++it)
			{
				cout << *it << " ";// printing root node
			}
			cout << endl;
			inorder(currnode->right); // recursive function for right child
		}
	}

	// Function for rotating right ( Single Rotation)
	AVLnode* singlerotationwithright(AVLnode* previousroot)
	{
		AVLnode* newroot = previousroot->left;
		AVLnode* temp = newroot->right; //Declaring nodes

		newroot->right = previousroot;
		previousroot->left = temp;// swapping nodes

		previousroot->height = max(getheight(previousroot->left),
			getheight(previousroot->right)) + 1; // Calculating maximum node height

		newroot->height = max(getheight(newroot->left),
			getheight(newroot->right)) + 1;// Calculating maximum node height

		return newroot;// Returning new root for tree after rotation
	}

	//Function for rotating left ( Single Rotation)
	AVLnode* singlerotationwithleft(AVLnode* previousroot)
	{
		AVLnode* newroot = previousroot->right;
		AVLnode* temp = newroot->left;  // Declaring/ Assigning nodes

		newroot->left = previousroot;
		previousroot->right = temp;// Swapping Nodes

		previousroot->height = max(getheight(previousroot->left),
			getheight(previousroot->right)) + 1; // Calculating Maximum node height

		newroot->height = max(getheight(newroot->left),
			getheight(newroot->right)) + 1;// Calculating maximim node height

		return newroot; // Returning new root after rotation
	}

	// Function for right left ( Double ) Rotation
	AVLnode* doublerotationrightleft(AVLnode* previousroot)
	{
		//calling single right rotation Function
		previousroot->right = singlerotationwithright(previousroot->right);
		// Calling Single left rotation Function
		AVLnode* newroot = singlerotationwithleft(previousroot);
		// Returning new root after doubly rotation
		return newroot;
	}

	// Function for left right ( Double ) Rotation
	AVLnode* doublerotationleftright(AVLnode* previousroot)
	{
		// Calling single left rotation function
		previousroot->left = singlerotationwithleft(previousroot->left);
		// Calling single right rotation function
		AVLnode* newroot = singlerotationwithright(previousroot);
		// Returning new root after doubly rotation
		return newroot;
	}

	// Function for inserting key value pair at each node in AVL Tree
	AVLnode* AVLinsertion(int key, string data, AVLnode* currnode)
	{
		if (currnode == NULL)
		{
			currnode = new AVLnode(key, data);// Inserting 1st node
			return currnode;// Returning node
		}
		else if (key < currnode->key)//Insertion for left child(AVL == Balanced)
		{
			currnode->left = AVLinsertion(key, data, currnode->left);//Left Child
			if (getbalancefactor(currnode) == 2)//If balance factor is > 1 then applying rotations
			{
				if (key < currnode->left->key)
					currnode = singlerotationwithright(currnode); //RR rotation
				else
					currnode = doublerotationleftright(currnode); //LR rotation
			}
		}
		else if (key > currnode->key)
		{
			currnode->right = AVLinsertion(key, data, currnode->right);
			if (getbalancefactor(currnode) == -2)
			{
				if (key > currnode->right->key)
					currnode = singlerotationwithleft(currnode); //LL rotation
				else
					currnode = doublerotationrightleft(currnode); //RL rotation
			}
		}
		else if (key == currnode->key)
		{
			if (!Contains(data, currnode->datalist))
			{
				currnode->datalist.push_back(data);
			}
		}
		currnode->height = (max(getheight(currnode->left), getheight(currnode->right))) + 1;
		return currnode;
	}

	AVLnode* AVLinsertion(int key, list<string> data, AVLnode* currnode)
	{
		if (currnode == NULL)
		{
			currnode = new AVLnode(key, data);// Inserting 1st node
			return currnode;// Returning node
		}
		else if (key < currnode->key)//Insertion for left child(AVL == Balanced)
		{
			currnode->left = AVLinsertion(key, data, currnode->left);//Left Child
			if (getbalancefactor(currnode) == 2)//If balance factor is > 1 then applying rotations
			{
				if (key < currnode->left->key)
					currnode = singlerotationwithright(currnode); //RR rotation
				else
					currnode = doublerotationleftright(currnode); //LR rotation
			}
		}
		else if (key > currnode->key)
		{
			currnode->right = AVLinsertion(key, data, currnode->right);
			if (getbalancefactor(currnode) == -2)
			{
				if (key > currnode->right->key)
					currnode = singlerotationwithleft(currnode); //LL rotation
				else
					currnode = doublerotationrightleft(currnode); //RL rotation
			}
		}
		currnode->height = (max(getheight(currnode->left), getheight(currnode->right))) + 1;
		return currnode;
	}

	// Function for searching key value pair at each node in AVL Tree
	AVLnode* AVLsearch(int key, string data, AVLnode* currnode, bool& specialcase)
	{
		if (currnode == NULL)
		{
			return currnode;// Returning root in case of only one node
		}
		else if (key < currnode->key)
		{
			currnode->left = AVLinsertion(key, data, currnode->left);
			if (getbalancefactor(currnode) == 2)
			{
				if (key < currnode->left->key)
					currnode = singlerotationwithright(currnode); //RR rotation
				else
					currnode = doublerotationleftright(currnode); //LR rotation
			}
		}
		else if (key > currnode->key)
		{
			currnode->right = AVLinsertion(key, data, currnode->right);
			if (getbalancefactor(currnode) == -2)
			{
				if (key > currnode->right->key)
					currnode = singlerotationwithleft(currnode); //LL rotation
				else
					currnode = doublerotationrightleft(currnode); //RL rotation
			}
		}
		else if (key == currnode->key)
		{
			if (Contains(data, currnode->datalist))
			{
				specialcase = true;
				cout << endl;
				cout << "Data found!" << endl;
			}
		}
		currnode->height = (max(getheight(currnode->left), getheight(currnode->right))) + 1;
		return currnode;
	}

	// Function for deleting key value pair at any node in aVL Tree
	AVLnode* AVLdeletion(int key, string data, AVLnode* currnode)
	{
		if (currnode == NULL)
			return NULL;//Returning NULL in case of empty tree

		else if (key < currnode->key)
		{ // Recursive function for left child
			currnode->left = AVLdeletion(key, data, currnode->left);
		}
		else if (key > currnode->key)
		{ //Recursive function for right child
			currnode->right = AVLdeletion(key, data, currnode->right);
		}
		else if (key == currnode->key)
		{ // Deleting node if key matches current node's key
			Remove_Data(data, currnode->datalist);
			if (currnode->datalist.empty())
			{
				//Deleting Leaf Node
				if (currnode->left == NULL && currnode->right == NULL)
				{
					delete currnode;
					currnode = NULL;
				}
				//Deleting node ith only right child
				else if (currnode->left == NULL)//Left child is NULL
				{
					AVLnode* temp = currnode;
					currnode = currnode->right;

					delete temp;//deleting node
				}
				//Deleting node with only left child
				else if (currnode->right == NULL)//right child is NULL
				{
					AVLnode* temp = currnode;
					currnode = currnode->left;

					delete temp;//Deleting node
				}
				//Deleting node with two children
				else
				{
					AVLnode* temp = currnode->right;
					while (temp->left)
					{//treversing to the least of tree ( Left Most )
						temp = temp->left;
					}

					currnode->key = temp->key;
					currnode->datalist = temp->datalist;
					//recursive function for right child
					currnode->right = AVLDeletionUsingKey(temp->key, currnode->right);
				}
			}
		}

		if (currnode == NULL)
			return NULL;

		//calculating height after deletion
		currnode->height = max(getheight(currnode->left),
			getheight(currnode->right)) + 1;

		//left subtree is heavy
		if (getbalancefactor(currnode) == 2)
		{
			//checking if left child of left subtree exists or not
			if (getbalancefactor(currnode->left) >= 0)
			{
				currnode = singlerotationwithright(currnode);
			}
			else if (getbalancefactor(currnode->left) < 0)
			{
				currnode = doublerotationleftright(currnode);
			}
		}

		//right subtree is heavy
		else if (getbalancefactor(currnode) == -2)
		{
			//checking if right child or right subtree exists or not
			if (getbalancefactor(currnode->right) <= 0)
			{
				currnode = singlerotationwithleft(currnode);
			}
			else if (getbalancefactor(currnode->left) > 0)
			{
				currnode = doublerotationrightleft(currnode);
			}
		}

		return currnode;
	}

	// Function for deleting node using keys
	AVLnode* AVLDeletionUsingKey(int key, AVLnode* currnode)
	{
		if (currnode == NULL)
			return NULL;//Returning NULL in case of empty tree

		else if (key < currnode->key)
		{
			//Recursive function for left child
			currnode->left = AVLDeletionUsingKey(key, currnode->left);
		}
		else if (key > currnode->key)
		{
			//Recursive function for right child
			currnode->right = AVLDeletionUsingKey(key, currnode->right);
		}
		else if (key == currnode->key)
		{
			//Delting node if key matches its own key
			AVLnode* temp = currnode;
			currnode = currnode->left;
			temp->datalist.clear();//clearing all data
			delete temp;// Deleting node
		}

		if (currnode == NULL)
			return NULL;//returning null id node is NULL

			//calculating height after deletion
		currnode->height = max(getheight(currnode->left),
			getheight(currnode->right)) + 1;

		//left subtree is heavy
		if (getbalancefactor(currnode) == 2)
		{
			//checking if left child of left subtree exists or not
			if (getbalancefactor(currnode->left) >= 0)
			{
				currnode = singlerotationwithright(currnode); //Single right rotation
			}
			else if (getbalancefactor(currnode->left) < 0)
			{
				currnode = doublerotationleftright(currnode);// LR rotation
			}
		}

		//right subtree is heavy
		else if (getbalancefactor(currnode) == -2)
		{
			//checking if right child or right subtree exists or not
			if (getbalancefactor(currnode->right) <= 0)
			{
				currnode = singlerotationwithleft(currnode);// Single left Rotation
			}
			else if (getbalancefactor(currnode->left) > 0)
			{
				currnode = doublerotationrightleft(currnode);//RL rotation
			}
		}

		return currnode;
	}
public://Public Functions

	AVLTree()// Default cinstructor for AVL Tree
	{
		root = NULL;//Default root value ( NULL )
	}

	// Parameterized Constructor
	AVLTree(AVLTree& Obj)
	{
		root = NULL;
		root = Copy(Obj.getroot());
	}

	//Operataor overloading
	AVLTree& operator=(AVLTree& Obj)
	{
		root = Copy(Obj.getroot());
		return *this;
	}
	//Getter Function for root of tree
	AVLnode* getroot()
	{
		return root;//returning root
	}
	//Function calling (Private) inorder display function
	void DisplayInOrder()
	{
		inorder(root);
	}
	//Function calling (Private) insertion function
	void insert(int key, string data)
	{
		root = AVLinsertion(key, data, root);
	}
	//Function calling (Private) Deletion function
	void remove(int key, string data)
	{
		root = AVLdeletion(key, data, root);
	}
	//Function calling (Private) Search function
	bool search(int key, string data)
	{
		bool spccase = false;
		AVLnode* currnode = AVLsearch(key, data, root, spccase);
		return spccase;
	}
	//Function for clearing all the data in the AVL Tree
	void clear()//to delete all elements that are in queue
	{
		if (root != NULL)
		{
			queue<AVLnode*> Q;// Object of Queue with AVLnode datatype
			AVLnode* currnode = NULL;
			Q.push(root);//Pushing root in Queue
			// loop runs until queue is empty
			while (!Q.empty())
			{
				currnode = Q.front();
				Q.pop();//Popping front node

				if (currnode->left != NULL)
					Q.push(currnode->left);//Pshinf left child
				if (currnode->right != NULL)
					Q.push(currnode->right);// Pushing right child

				delete currnode;// Deleting parent node
			}

			root = NULL;// Clearing root at the end
		}
	}

	void SplitAVL(int key, AVLnode* curr, AVLTree& T2, AVLTree& T3)
	{
		if (curr == NULL)
		{
			return;
		}
		if (curr->key <= key)
		{
			T2.root = AVLinsertion(curr->key, curr->datalist, T2.root);
		}
		if (curr->key > key)
		{
			T3.root = AVLinsertion(curr->key, curr->datalist, T3.root);
		}
		SplitAVL(key, curr->left, T2, T3);
		SplitAVL(key, curr->right, T2, T3);
	}

	void SplitAVL(int key, AVLTree T1, AVLTree& T2, AVLTree& T3)
	{
		SplitAVL(key, T1.root, T2, T3);
	}

	void NodesInsertion(AVLnode* curr, AVLTree& T)
	{
		if (curr == NULL)
		{
			return;
		}
		else
		{
			T.root = AVLinsertion(curr->key, curr->datalist, T.root);
			NodesInsertion(curr->left, T);
			NodesInsertion(curr->right, T);
		}
	}

	void MergeAVL(AVLTree& T1, AVLTree T2, AVLTree T3)
	{
		T1 = T2;
		NodesInsertion(T3.root, T1);
	}

	int Checkheight()
	{
		return getheight(root); //returning height of root
	}
	// Function for copying AVL Tree
	AVLnode* Copy(AVLnode* Obj)
	{
		if (Obj != NULL)// If tree is not Empty
		{
			AVLnode* left = Copy(Obj->left);//Left Child
			AVLnode* right = Copy(Obj->right);//right Child
			return new AVLnode(Obj->key, Obj->datalist, Obj->height, left, right);
		}
		else
		{
			//Returning NULL if tree is emoty
			return NULL;
		}
	}

	// Destructor Function
	~AVLTree()
	{
		//Calling clear function
		clear();
	}
};

//structure for doubly link list of routing table
struct RT_node
{
	RingStruct* Obj;// Object of circular list's node (Ring DHT)
	RT_node* next;
	RT_node* prev;
	RT_node() {// Default Constructor
		next = prev = NULL;
	}
	//Parameterized Constructor
	RT_node(RingStruct* Obj) {
		this->Obj = Obj;
		next = prev = NULL;
	}
};

class Routing_table
{
	RT_node* head; //Declaring head and tail
	RT_node* tail;
public:
	//Default constructor for routing table
	Routing_table()
	{
		head = tail = NULL;
	}
	//Function for inserting machine in routing table
	void insertnode(RingStruct* Obj)
	{
		RT_node* newnode = new RT_node(Obj);// newnode
		if (!head)// Inserting 1st node
		{
			head = newnode;// making head a newnode
			newnode->prev = NULL;
		}
		else
		{//Inserting node at the end of list
			RT_node* curr = head;
			while (curr->next)
			{
				curr = curr->next;
			}
			curr->next = newnode;
			newnode->prev = curr;// Setting next and previous pointers
			tail = newnode;// Setting tail of list
		}

	}
	// Function for getting routing table cleared
	void clear()
	{
		RT_node* curr = head;// Temporary pointer pointing head
		RT_node* newone = NULL;
		while (curr)
		{// getting every node in list deleted
			newone = curr->next;
			delete curr;// Deleting temoorary current pointer
			curr = newone;
		}
		head = NULL;// Making head and tail NULL at the end
		tail = NULL;
	}

	//Getter Function for getting head of list( Routing Table )
	RT_node* geth()
	{
		if (head != NULL)
		{
			return head;// returning head
		}
		else
		{
			return NULL;
		}
	}
};

//Struct for singly Circular list( Ring DHT )
struct RingStruct
{
public:
	int machine_id;
	int hashed_machine_id; // Declaring
	AVLTree AVL; // |
	Routing_table RT; // necessory
	RingStruct* next; // variables, pointers & objects
	// Default Constructor
	RingStruct()
	{
		machine_id = -1;
		hashed_machine_id = -1;
		next = NULL;
	};
};

class RingModel
{
	RingStruct* head;
	list<int> ActiveMachines;
	int identifier_space; // Declaring necessor variables
	int num_of_machines;

public:

	//Default constructor for class RingModel
	RingModel()
	{

		head = NULL;
		identifier_space = 0;//Assigning default values
		num_of_machines = 0;
		//Printing project name
		cout << "\n\n\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
		cout << "\t\t\t@@@@@@@@@ Distributed Hash Tables @@@@@@@@@\n";
		cout << "\t\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n";

		int num_of_bits = 0, mac_id = 0;
		cout << "\tPlease specify the system artictechture in number of bits(e.g 4): ";
		cin >> num_of_bits;

		identifier_space = pow(2, num_of_bits);
		// getting number of machines
		cout << "\n\tPlease specify the number of machines that you want create: ";
		cin >> num_of_machines;
		// no.of macs should be less then identifier space
		while (num_of_machines > identifier_space)
		{
			cout << "\n\tError, Number of Machines cannot be greator than identifier space" << endl;
			cout << "\n\tIdentifier space = " << identifier_space << endl;
			cout << "\n\tPlease specify the number of machines that you want create: ";
			cin >> num_of_machines;
		}
		// Getting user choice for assigning mac IDs
		int choice = 0;
		cout << "\n\t\tPlease enter a choice: " << endl;
		cout << "\n\t[1]-Press 1 to Randomly Assign ID's to machines" << endl;
		cout << "\n\t[2]-Press 2 to Manually Assign ID's to machines" << endl;
		cout << "\n\t[3]-Press 3 to Exit\n\n\t\tChoose: ";
		cin >> choice;
		// Check for wrong user choice
		while (choice < 0 && choice>3)
		{
			cout << "\n\tError specifying choice!" << endl;
			cout << "\n\tPlease enter a Valid choice: " << endl;
			cout << "\n\t[1]-Press 1 to Randomly Assign ID's to machines" << endl;
			cout << "\n\t[2]-Press 2 to Manually Assign ID's to machines" << endl;
			cout << "\n\t[3]-Press 3 to Exit\n\n\t\tChoose: ";
			cin >> choice;
		}
		// Switch for each case for asssigning values to machines
		switch (choice)
		{
		case 1://randomly assign
		{
			int temp_val = 0;
			int temp_id = identifier_space / num_of_machines;
			//Loop runs till the number of machines
			for (int i = 0; i < num_of_machines; i++)
			{
				CreateMachines(temp_val, temp_val);// creatin machine with id
				ActiveMachines.push_front(temp_val);// Pushing active macs in a queue
				ActiveMachines.sort();// Sorting machines in queue
				temp_val = temp_val + temp_id;
			}
			cout << num_of_machines << " Machines created Successfully!" << endl;
			cout << endl;
			set_routingtable();// Setting routing table for Machines
			displaymachinesstatus();// Displays each mac's status
			Menu();// calling Menu ( Driver Function ) for user ease
		}
		case 2://manually assign
		{
			int temp_val = 0;
			for (int i = 0; i < num_of_machines; i++)//Same as random assign
			{
				cout << "Please input ID for Machine " << i + 1 << " : ";
				cin >> mac_id;// Getting mac id from user
				temp_val = calculatehash(mac_id, identifier_space);
				CreateMachines(mac_id, temp_val);
				ActiveMachines.push_front(temp_val);// Same as random assign
				ActiveMachines.sort();
			}
			cout << endl << num_of_machines << " Machines created Successfully!" << endl;
			cout << endl;
			set_routingtable();
			displaymachinesstatus();// Same as Random Assign
			Menu();
		}
		case 3:
		{
			cout << "\n\t\tHave A Nice Day\n\t\t Bye Bye!!" << endl;
			exit(0);//exiting if user wants
		}
		}




	}

	//function for creating user prescribed machines
	void CreateMachines(int mac_id, int hashed_mac_id)
	{
		RingStruct* current = head;

		RingStruct* newP = new RingStruct;
		newP->machine_id = mac_id; // Assigning values
		newP->hashed_machine_id = hashed_mac_id;
		newP->next = NULL;

		if (current == NULL)//if head is NULL
		{
			head = newP; //1st mac creation
			head->next = head;
		}
		else//Head not being NULL
		{
			if (current->hashed_machine_id >= newP->hashed_machine_id)
			{
				while (current->next != head)//Circular Traversal
				{
					current = current->next;
				}

				current->next = newP;//Inserting mac at the end
				newP->next = head;
				head = newP;
			}
			else
			{
				while (current->next != head && current->next->hashed_machine_id < newP->hashed_machine_id)
				{
					current = current->next;
				}
				newP->next = current->next;
				current->next = newP;
			}
		}

	}

	//Function for displaying each mac's status
	void displaymachinesstatus()
	{
		int i = 1;
		cout << "Active machines are: " << endl;
		typename list <int> ::iterator it;
		//Printing active machines from the list of machines
		for (it = ActiveMachines.begin(); it != ActiveMachines.end(); ++it)//(While active macines doesn't end)
		{
			cout << i++ << " : " << *it << endl;
		}
		i = 1;
		cout << endl;
		//Printing Machines along with their hashed ids
		cout << "Machines and their Hashed IDs: " << endl;
		if (isEmpty())
		{
			// If thee are no machines in the list
			cout << "\nList is Empty.\n";
			return;
		}
		RingStruct* curr = head;
		int count = 1;
		do
		{
			// Printing machine no along with their hashed and unhashed ids
			cout << "Machine no : " << i++ << endl;
			cout << "Machine ID: " << curr->machine_id << " || ";
			cout << "Hashed ID: " << curr->hashed_machine_id << " ";
			cout << endl;

			cout << endl;
			cout << endl;
			curr = curr->next;// Moving to next machine
		} while (curr != head);
		cout << endl;
	}

	void displayallinfomachinesstatus()
	{
		int i = 1;
		cout << "Active machines are: " << endl;
		typename list <int> ::iterator it;
		//Printing active machines from the list of machines
		for (it = ActiveMachines.begin(); it != ActiveMachines.end(); ++it)//(While active macines doesn't end)
		{
			cout << i++ << " : " << *it << endl;
		}
		i = 1;
		cout << endl;
		//Printing Machines along with their hashed ids
		cout << "Machines and their Hashed IDs: " << endl;
		if (isEmpty())
		{
			// If thee are no machines in the list
			cout << "\nList is Empty.\n";
			return;
		}
		RingStruct* curr = head;
		int count = 1;
		do
		{
			// Printing machine no along with their hashed and unhashed ids
			cout << "Machine no : " << i++ << endl;
			cout << "Machine ID: " << curr->machine_id << " || ";
			cout << "Hashed ID: " << curr->hashed_machine_id << " ";
			cout << endl << endl;
			cout << "Routing table: " << endl;
			display_routingtable(curr);// Printing Routing table of each machine
			cout << endl << endl;
			cout << "AVL Tree: " << endl;
			cout << "Key " << "\t\tData Values" << endl;
			curr->AVL.DisplayInOrder();

			cout << endl;
			cout << endl;
			curr = curr->next;// Moving to next machine
		} while (curr != head);
		cout << endl;
	}

	//function for Getting active machines
	void getactivemachines()
	{
		cout << endl;
		int i = 1;
		cout << "Active machines are: " << endl;
		typename list <int> ::iterator it;
		//Getting active machines until list ends
		for (it = ActiveMachines.begin(); it != ActiveMachines.end(); ++it)
		{
			cout << i++ << " : " << *it << endl;// Getting machine at i node
		}
	}

	//Function for searching machine based on hashed ID
	RingStruct* SearchMachine(int hashedid)
	{
		if (isEmpty())//returning NULL if their aren't any machines
		{
			return NULL;
		}
		RingStruct* curr = head;
		do
		{
			if (curr->hashed_machine_id == hashedid)
			{//Loop braeks if hashed id matches
				break;
			}

			curr = curr->next;
		} while (curr != head);

		if (curr == NULL)//Returning NULL if node not found
		{
			return NULL;
		}
		else
		{
			return curr;// Returning Searched node
		}
	}

	// Driver Function For user Ease
	void Menu()
	{
		int key = 0;
		string value;// Declaring Variables
		int mac_option = 0;
	menu:
		int choice = 0;
		cout << "-----------------------------------------------\n" << endl;
		cout << "[1]-Press 1 Insert Key Data pair." << endl; // Insertion
		cout << "[2]-Press 2 Search Key Data pair." << endl; // Searching
		cout << "[3]-Press 3 Remove Key Data pair." << endl; // Removal
		cout << "[4]-Press 4 to Insert(Create) a new Machine." << endl; // Mac Addition
		cout << "[5]-Press 5 to Remove an Existing Machine." << endl;
		cout << "[6]-Press 6 to Print Routing Table of a Machine." << endl;
		cout << "[7]-Press 7 to Print AVL of a Machine." << endl;
		cout << "[8]-Press 8 to Display All info of Existing Machines." << endl;
		cout << "[0]-Press 0 To exit." << endl;
		cout << "-----------------------------------------------\n" << endl;
		cout << "Please enter a choice: ";
		cin >> choice;
		//Check for invalid input
		while (choice < 0 && choice>6)
		{
			cout << "-----------------------------------------------\n" << endl;
			cout << "Please enter a Valid choice: " << endl;
			cout << "[1]-Press 1 Insert Key Data pair." << endl;
			cout << "[2]-Press 2 Search Key Data pair." << endl;
			cout << "[3]-Press 3 Remove Key Data pair." << endl;
			cout << "[4]-Press 4 to Insert(Create) a new Machine." << endl;
			cout << "[5]-Press 5 to Remove an Existing Machine." << endl;
			cout << "[6]-Press 6 to Print Routing Table of a Machine." << endl;
			cout << "[7]-Press 7 to Print AVL of a Machine." << endl;
			cout << "[8]-Press 8 to Display All info of Existing Machines." << endl;
			cout << "[0]-Press 0 To exit." << endl;
			cout << "-----------------------------------------------\n" << endl;
			cout << "Error specifying the respective choice: ";
			cin >> choice;
			cout << endl;
		}
		// Switch case for user choice
		switch (choice)
		{
		case 1:
		{
			//Getting key of data
			cout << "Please enter a Key: ";
			cin >> key;

			//Getting data in string
			cin.ignore();
			cout << "Please enter a string: ";
			getline(cin, value);

			//Function calling active macs
			getactivemachines();

			//Machine in which user wants to insert data
			cout << "Please select a machine you want to insert data in: ";
			cin >> mac_option;

			//If machine entered is not in active machines list
			while (!Contains(mac_option, ActiveMachines))
			{
				cout << "Please select a Valid machine you want to insert data in: ";
				cin >> mac_option;
			}
			//Diaplaying routing table of machine
			RingStruct* temp = SearchMachine(mac_option);
			cout << "\nStarting from ";
			RingStruct* RoutedNode = Mac_Routing(calculatehash(key, identifier_space), temp, checkcase(calculatehash(key, identifier_space)));
			cout << " End \n";
			//Inserting key data pair
			InsertDataUsingKeyValue(calculatehash(key, identifier_space), value, RoutedNode);

			goto menu;
		}
		//Same as case 01
		case 2:
		{
			cout << "Please enter a Key: ";
			cin >> key;

			cin.ignore();
			cout << "Please enter a string: ";
			getline(cin, value);

			getactivemachines();

			cout << "Please select a machine you want to search data in: ";
			cin >> mac_option;

			while (!Contains(mac_option, ActiveMachines))
			{
				cout << "Please select a Valid machine you want to search data in: ";
				cin >> mac_option;
			}
			// Displaying machines's routing table
			RingStruct* temp = SearchMachine(mac_option);
			cout << "\nStarting From ";
			RingStruct* RoutedNode = Mac_Routing(calculatehash(key, identifier_space), temp, checkcase(calculatehash(key, identifier_space)));
			cout << " End\n";
			//Searching with the help of key alue pair
			SearchDataUsingKeyValue(calculatehash(key, identifier_space), value, RoutedNode);
			goto menu;
		}
		// same as case 1 & 2
		case 3:
		{
			cout << "Please enter a Key: ";
			cin >> key;

			cin.ignore();
			cout << "Please enter a string: ";
			getline(cin, value);

			getactivemachines();

			cout << "Please select a machine you want to Remove data from: ";
			cin >> mac_option;

			while (!Contains(mac_option, ActiveMachines))
			{
				cout << "Please select a Valid machine you want to Remove data from: ";
				cin >> mac_option;
			}
			// Displaying Routing Table of MAchines
			RingStruct* temp = SearchMachine(mac_option);
			cout << "\nStarting From ";
			RingStruct* RoutedNode = Mac_Routing(calculatehash(key, identifier_space), temp, checkcase(calculatehash(key, identifier_space)));
			cout << " End\n";
			// removing data with the help of key value pair
			RemoveDataUsingKeyValue(calculatehash(key, identifier_space), value, RoutedNode);
			goto menu;
		}
		case 4:
		{// Adding a new machine in ring DHT
			int choice = 0;
			cout << "Please enter a choice: " << endl;
			cout << "[1]-Press 1 to Randomly Assign ID's to machines" << endl;
			cout << "[2]-Press 2 to Manually Assign ID's to machines" << endl;//Asking for ID Assigning
			cout << "[3]-Press 3 to return to Main Menu" << endl;
			cin >> choice;
			// Check for Invalid Input
			while (choice < 0 && choice>3)
			{
				cout << "Error specifying choice!" << endl;
				cout << "Please enter a Valid choice: " << endl;
				cout << "[1]-Press 1 to Randomly Assign ID's to machines" << endl;
				cout << "[2]-Press 2 to Manually Assign ID's to machines" << endl;
				cout << "[3]-Press 3 to return to Main Menu" << endl;
				cin >> choice;
			}
			// Switch for user choice
			switch (choice)
			{
			case 1:
			{
				int Id = 0, hashed_id = 0;
				num_of_machines++;// Adding 1 in no.of machines

				int iterator = 0;

				//Check for ID with machine already exiting
				do
				{
					Id = iterator;
					iterator++;
					if (iterator >= identifier_space)
					{
						cout << "There is no space for new Machine, Capacity Full!" << endl;
						goto menu;
					}
				} while (Contains(calculatehash(Id, identifier_space), ActiveMachines));
				//RingStruct* mac = SearchMachine(calculatehash(Id, identifier_space));
				ActiveMachines.push_front(calculatehash(Id, identifier_space));//Pushing new machine in queue
				ActiveMachines.sort();// Sorting again all achines
				CreateMachines(Id, calculatehash(Id, identifier_space));//Creating newly added machine

				RingStruct* currmachine = SearchMachine(calculatehash(Id, identifier_space));
				RingStruct* succ = Parent_mac(calculatehash(Id + 1, identifier_space));

				AVLTree temp = succ->AVL;

				temp.SplitAVL(calculatehash(Id, identifier_space), temp, currmachine->AVL, succ->AVL);

				clear_routingtable();
				set_routingtable();//setting routing table
				displaymachinesstatus();
				goto menu;
			}
			case 2:
			{
				int Id = 0, hashed_id = 0;
				cout << "Please enter an ID for the new Machine: ";
				cin >> Id;

				while (!Contains(calculatehash(Id, identifier_space), ActiveMachines))
				{
					cout << "Please enter a Valid ID!" << endl;
					cout << "Same ID exists before: ";
					cin >> Id;
				}

				//RingStruct* mac = SearchMachine(calculatehash(Id, identifier_space));
				ActiveMachines.push_front(calculatehash(Id, identifier_space));//Pushing new machine in queue
				ActiveMachines.sort();// Sorting again all achines
				CreateMachines(Id, calculatehash(Id, identifier_space));//Creating newly added machine

				RingStruct* currmachine = SearchMachine(calculatehash(Id, identifier_space));
				RingStruct* succ = Parent_mac(calculatehash(Id + 1, identifier_space));

				AVLTree temp = succ->AVL;

				temp.SplitAVL(calculatehash(Id, identifier_space), temp, currmachine->AVL, succ->AVL);

				clear_routingtable();
				set_routingtable();//setting routing table
				displaymachinesstatus();
				goto menu;
			}
			case 3:
			{
				goto menu;//back to menu
			}
			}

			goto menu;//back to menu
		}
		case 5:
		{
			int id = 0, hashed_id = 0;

			getactivemachines();
			cout << "Please select a machine you want to Remove data from: ";
			cin >> id;//Getting id for which data is being removed

			while (!Contains(id, ActiveMachines))
			{
				cout << "Please select a Valid machine you want to Remove: ";
				cin >> id;//Getting valid machine id
			}


			num_of_machines--;//Decraesing no.of machines by 01
			if (num_of_machines == 0)
			{
				cout << endl;
				cout << "This is the only Machine Left, Cannot delete!" << endl;
				cout << endl;
				num_of_machines++;
				goto menu;
			}

			Remove_Data(id, ActiveMachines);//Removing machine

			RingStruct* currmachine = SearchMachine(calculatehash(id, identifier_space));
			RingStruct* succ = Parent_mac(calculatehash(id + 1, identifier_space));

			AVLTree temp = succ->AVL;
			temp.MergeAVL(succ->AVL, currmachine->AVL, temp);

			Remove(currmachine);

			clear_routingtable();
			set_routingtable();//Setting routing table
			displaymachinesstatus();

			goto menu;//back to menu
		}
		case 6:
		{
			//Function calling active macs
			getactivemachines();

			//Machine in which user wants to display routing atble
			cout << "Please select a machine you want to Print routing table of: ";
			cin >> mac_option;

			//If machine entered is not in active machines list
			while (!Contains(mac_option, ActiveMachines))
			{
				cout << "Please select a Valid machine you want to Print routing table of: ";
				cin >> mac_option;
			}
			//Diaplaying routing table of machine
			RingStruct* temp = SearchMachine(mac_option);
			cout << "Routing Table: " << endl;
			display_routingtable(temp);
			goto menu;
		}
		case 7:
		{
			getactivemachines();

			//Machine in which user wants to display AVL
			cout << "Please select a machine you want to Print AVL tree of: ";
			cin >> mac_option;

			//If machine entered is not in active machines list
			while (!Contains(mac_option, ActiveMachines))
			{
				cout << "Please select a Valid machine you want to Print AVL tree of: ";
				cin >> mac_option;
			}
			//Diaplaying routing table of machine
			RingStruct* temp = SearchMachine(mac_option);
			cout << "AVL tree: " << endl;
			temp->AVL.DisplayInOrder();
			goto menu;
		}
		case 8:
		{
			displayallinfomachinesstatus();
			goto menu;
		}
		case 0:
		{
			cout << "\n\t\tHave A Nice Day \n\t\t Bye Bye !!" << endl;
			exit(0);//exiting program
		}

		}

	}

	//Function for inserting data based on key value pair
	void InsertDataUsingKeyValue(int key, string data, RingStruct* Obj)
	{
		Obj->AVL.insert(key, data);//calling avl insertion
		return;
	}

	//Function for Searching data based on key value pair
	void SearchDataUsingKeyValue(int key, string data, RingStruct* Obj)
	{
		if (Obj->AVL.search(key, data))//Calling AVl Searching Function
		{
			cout << "Details: " << endl;
			cout << "Hashed Machine ID: " << Obj->hashed_machine_id << endl;
			cout << endl;
		}
		else// If data od=r tree is not found
		{
			cout << "Data not found :(" << endl;
			cout << endl;
		}
	}

	//Function for removing data based on key value pair
	void RemoveDataUsingKeyValue(int key, string data, RingStruct* Obj)
	{
		Obj->AVL.remove(key, data);//Calling AVl removal functon
		return;
	}

	//Function for finding parent ( successor ) or specific machine
	RingStruct* Parent_mac(int Mac_hash) {
		RingStruct* min = head;
		RingStruct* max = head;//max and min nodes of list
		while (max->next != head)
		{
			max = max->next;// Calculating maximum node
		}

		if (Mac_hash <= min->hashed_machine_id || Mac_hash > max->hashed_machine_id)
		{
			return head;//Returning head if hash is between least and greatest machine
		}
		else
		{
			//If hash is greater then machine hash traversing it till its equal or smaller
			RingStruct* curr = head;
			while (Mac_hash > curr->hashed_machine_id)
			{
				curr = curr->next;
			}
			return curr;//returning machine (parent)
		}
	}

	// Function for setting routing table of machines
	void set_routingtable() {

		RingStruct* curr = head;
		RingStruct* set;//parent of machine whichuser entered
		int n = log2(identifier_space);//getting bits of system

		do
		{
			int i = 1;
			while (i <= n)//Loop runs till system bits
			{
				int formula = pow(2, i - 1);
				//Calculating successor according to the formula p=2 raise to power i-1
				set = Parent_mac(calculatehash((curr->hashed_machine_id) + formula, identifier_space));
				//Inserting machine into routing table(doubly list)
				curr->RT.insertnode(set);
				i++;
			}
			curr = curr->next;//Moving to next mac
		} while (curr != head);
	}

	//Function for clearing routing table
	void clear_routingtable() {
		RingStruct* curr = head;
		do
		{
			curr->RT.clear();//Calling clear function in routing table list
			curr = curr->next;
		} while (curr != head);
	}

	//Function for Displaying routing table of each machine
	void display_routingtable(RingStruct* obj)
	{
		RT_node* curr = obj->RT.geth();// Getting head node of routing table list
		while (curr != NULL)
		{
			//Getting hashed machine ids of each machine in routing table of a specific machine
			cout << curr->Obj->hashed_machine_id << " ";
			curr = curr->next;//moving ono nexr machine
		}
	}

	// Function for returning machines based on indexes
	RingStruct* ReturnMachine(RingStruct* Obj, int index)
	{
		int count = 0;
		RT_node* curr = Obj->RT.geth();//getting machine at head of list


		while (curr && count != index)
		{
			count++;
			curr = curr->next;// traversing towards the desired machine
		}
		if (curr == NULL)
		{
			return NULL;
		}
		else
		{
			return curr->Obj;// Returning the desired MAchine
		}
	}

	// Function for setting and checking routing table for each machine
	RingStruct* Mac_Routing(int hashedkey, RingStruct* machine, bool loopedcase)
	{
		cout << " ----> " << machine->hashed_machine_id;//Printing arrow for saperating each mac

		//Returning machine if hashed id maches its own id
		if (machine->hashed_machine_id == hashedkey)
		{
			cout << endl;
			return machine;//returning machine
		}

		if (machine->hashed_machine_id > hashedkey)
		{
			if (Parent_mac(hashedkey) == machine)
			{
				cout << endl;
				//returning machine if user entered key < machine key
				return machine;
			}
			else
			{
				//if not above cases then traversing to the next machines and checking each mac's ID
				int j = 0;
				RingStruct* curr_mac = ReturnMachine(machine, j);
				RingStruct* next_mac = ReturnMachine(machine, j + 1);

				while (j < log2(identifier_space) - 1 && hashedkey < next_mac->hashed_machine_id)
				{
					j++;
					curr_mac = next_mac;//moving onto the next mac for checking
					if (j + 1 < log2(identifier_space))
						next_mac = ReturnMachine(machine, j + 1);//returning J+1 th machine
				}
				//Looped case is a special case when key > max mac & key < min mac
				return Mac_Routing(hashedkey, curr_mac, loopedcase);//Recursive function
			}
		}
		//Same if statement as previous
		//Just returning machine if machine key< entered key
		if (machine->hashed_machine_id < hashedkey)
		{
			RingStruct* curr_mac = ReturnMachine(machine, 0);
			// If jashed key is smaller
			if ((hashedkey <= curr_mac->hashed_machine_id) || (loopedcase && curr_mac == head))
			{
				cout << " ----> " << curr_mac->machine_id;
				return curr_mac;// returning current mac for routing table
			}
			else
			{
				int j = 0;
				RingStruct* next_mac = ReturnMachine(machine, j + 1);

				while (j < log2(identifier_space) - 1 && hashedkey > next_mac->hashed_machine_id)
				{
					j++;
					curr_mac = next_mac;
					if (j + 1 < log2(identifier_space))
						next_mac = ReturnMachine(machine, j + 1);
					//Breaking loop if its a looped case
					if (loopedcase && next_mac == head)
						break;
				}
				// Recursive function
				return Mac_Routing(hashedkey, curr_mac, loopedcase);
			}
		}

	}

	//Function for returning parent machine based on hashed key entered
	bool checkcase(int hashedkey)
	{
		return (Parent_mac(hashedkey) == head);
	}

	//Function for checking empty list
	bool isEmpty()
	{
		if (head == NULL)
			return true;//returning true if list is empty
		return false;
	}

	void Remove(RingStruct* currmachine)
	{
		if (isEmpty())
		{
			return;  //list empty
		}
		if (head == currmachine && head->next == head)
		{
			delete head;
			head = NULL;
			return;
		}

		RingStruct* currnode = head;
		RingStruct* prev = NULL;

		if (head == currmachine)
		{
			while (currnode->next != head)
			{
				currnode = currnode->next;
			}
			currnode->next = head->next;
			delete head;
			head = currnode->next;
			return;
		}
		else
		{
			while ((currnode->next != head) && (currnode->next != currmachine))
			{
				currnode = currnode->next;
			}

			if (currnode->next == currmachine)
			{
				prev = currnode->next;
				currnode->next = prev->next;
				delete prev;
			}
			else
			{
				return;
			}
		}
	}

	// Function for clearing all data in the circular list
	void Clear()
	{
		if (head == NULL)
			return;// Returns null if head is NULL

		RingStruct* curr = head->next;
		RingStruct* next = NULL;
		while (curr != head)
		{
			next = curr->next;
			delete curr;//Deleting every node
			curr = next;
		}

		delete head;//Deleting head at the end
		head = NULL;
	}

	//Destructor function for RingModel
	~RingModel()
	{
		Clear();//Calling Clear Function
	}
};

int main()
{
	//Calling Default Constructor for Ring Model
	RingModel R1;




	return 0;
}