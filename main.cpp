#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>
using namespace std;

//Function Prototyping

void Header(string,int);

void Menue();
	void guestMenue();
	void guestSelection(int);
	
	void userMenue();
	void userSelection(int);
	
	void adminMenue();
	void adminSelection(int);
	void Manage_user_accounts();
		void display_user_accounts();
			void deleteUserML();
	

void availableService();
	void Available_Service_Menue();
		void List_Services(string);
		void Search_services();
		void buyService();
	bool Available_Service_Selection(int);
void availableProduct();
	void Available_Product_Menue();
		void List_Product(string);
		void Search_Product();
		void buyProduct();
	bool Available_Product_Selection(int);

void login();
void signup();
void logout();
void Manage_login();
	void admin_login_Menue();
	bool admin_login_Selection(int);
	
	void user_login_Menue();
	bool user_login_Selection(int);
	
	void changePassword();
	bool deleteAccount();

void Manage_Services_Proucts();
	void Manage_Services_Proucts_Menue();
	bool Manage_Services_Proucts_Selection(int);
		void Add_Services();
		void Delete_Services();
		void Update_Services();
		void Add_Products();
		void Delete_Products();
		void Update_Products();

void cart();
	float find_price_delete_cart(string,int);
	void bill();
void money_total(int , bool, bool);

void resetCartSystem();


//Gloabal Variable
bool loginStatus = 0;
bool loginAdminStatus = 0;
string password = "";
string username = "";
string UP[2];
float total = 0;

//Constants

int main() {
	resetCartSystem();
	Menue();
	return 0;
}

void resetCartSystem(){
	ofstream sCartFile("Cart\\cart_S.txt");
	ofstream pCartFile("Cart\\cart_P.txt");
	sCartFile.close();
	pCartFile.close();
	total = 0;	
}

string path = "Main Menue";
void Header(string ipath="", int status =-1){
	system("CLS");
	cout << "\t\t\t==============\n"
		 << "\t\t\tBest Auto Part\n"
	 	 << "\t\t\t==============\n\n" ;
	 	 
	if(ipath != "" && status == 1){
		path += " -> " + ipath;
	}else if (status ==0){
		ipath = " -> " + ipath;
	    path.replace(path.find(ipath), ipath.length(), "");  
	}
	
	
	cout << path << "\n-----------------------------------------------------------------------\n";	
	money_total(0,1,1);
}

void money_total(int price = 0 , bool add = 1, bool show = 0){
	
	if(add){
		total += price;
	}else{
		total -= price;
	}
	
	if(show)
		cout << "\t\t\t\t\t\t\t\t" << fixed << setprecision(2) << total << " LKR";
}

void Menue(){
	while(true){
		
		Header();
		
		if(loginStatus)
			(loginAdminStatus)?adminMenue():userMenue();
		else
			guestMenue();
	
		int option = 0;
		cout << "\nEnter the option : ";
		cin >> option;
		if(!cin){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "invalid option\n";
			system("PAUSE");
		}else{
			if(loginStatus)
				(loginAdminStatus)?adminSelection(option):userSelection(option);
			else
				guestSelection(option);
		}
		
	}
		 
}

void guestMenue(){
	
	cout << "\n\tGuest\n\n";
	
	cout << "1. Available Services\n"
		 << "2. Available Proucts\n" 
		;
	
	cout << "\n3. Login\n" 
		 << "4. Signup\n"
	     << "0. Exit\n";
}

void guestSelection(int option){
	switch(option){
		case 1:
			availableService();
			break;
		case 2:
			availableProduct();
			break;
		case 3:
			login();
			break;
		case 4:
			signup();
			break;
		case 0:
			system("CLS");
			exit(0);
			break;
		default:
			cout << "invalid option\n";
		}
}


void availableService(){
	bool stop = 0;
	while(!stop){
		Header("Available Service",1);
		cout << "\n\tAvailable Service\n";
		
		Available_Service_Menue();
		
		int option = 0;
		cout << "\nEnter the option : ";
		cin >> option;
		if(!cin){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Invalid option\n";
			system("PAUSE");
		}else{
			stop = Available_Service_Selection(option);
		}
		
		Header("Available Service",0);
	}
}

void Available_Service_Menue(){
	cout << "\n1. List Services\n"
		 << "2. Search Services\n" 
		;
		
	if(loginStatus || loginAdminStatus){
		cout << "3. Buy\n";
	}
	
	cout << "\n0. Back\n";
}

bool Available_Service_Selection(int option){		
	switch(option){
		case 1:
			Header("List Services",1);
			List_Services("Services\\service.txt");
			system("PAUSE");
			Header("List Services",0);
			break;
		case 2:
			Search_services();
			break;
		case 0:
			return 1;
			break;
		default:
			if(loginStatus || loginAdminStatus){
				buyService();
			}else{
				cout << "invalid option\n";
				system("PAUSE");
			}
	}
	return 0;
}

void buyProduct(){
	while(1){
		
		Header("Buy Product",1);
		
		cout << "\n\t\tBuy Product\n\n";
		
		int pNum = 0, i = 0 , j= 0 , quantity = 0;;
		string line[20], catchLine, Product;
		float pprice;
		
		cout << "Enter Product number : ";
		cin >> pNum;
		
	
		ifstream infile("Product\\Product.txt");
					
		while(getline(infile,line[i])){		
				
			if( (pNum-1) == i){
				catchLine = line[i];
				break;
			}
			i++;
		}
		infile.close();
		
		if(catchLine != ""){
			long long int pos = 0;
			string delimiter = ",";
			while ((pos = catchLine.find(delimiter)) != string::npos) {
			    Product = catchLine.substr(0, pos);
			    catchLine.erase(0, pos + delimiter.length());
			    pprice = stoi( catchLine.substr(0, catchLine.size()-4) );
			}
			
			cout << "Enter the quantity : ";
			cin >> quantity;
			
			cout << "\nProduct		: " << Product
				 << "\nUnit price 	: " << pprice
				 << "\nQuantity        : " << quantity
				 << "\nPrice		: " << pprice*quantity;
			
			{
				ofstream outfile("cart\\cart_P.txt",ios::app);
				outfile << Product << "," << pprice*quantity << endl;
				outfile.close();
			}
			
			cout << "\n\n Successfully added to cart\n";
				 
			money_total(pprice*quantity,1,0);
		}else{
			cout << "Invalid Product number\n";
		}
		
		char yn;
		cout << "\nDo you want to buy more Products? (y/n) : ";
		cin >> yn;
		bool askReturn = true;
		
		while (askReturn){
			if(yn == 'n'){
				askReturn = false;
				break;
			}else if(yn == 'y'){
				break;
			}else{
				cout << "Invalid option\n";
			}
		}
		
		if (!askReturn){
			system("PAUSE");
			Header("Buy Product",0);
			break;
		}
	
		system("PAUSE");
		Header("Buy Product",0);
	}
	
	
}

void buyService(){
	while(1){
		
		Header("Buy Service",1);
		
		cout << "\n\t\tBuy Service\n\n";
		
		int sNum = 0, i = 0 , j= 0 , quantity = 0;;
		string line[20], catchLine, service;
		float sprice;
		
		cout << "Enter service number : ";
		cin >> sNum;
		
	
		ifstream infile("Services\\service.txt");
					
		while(getline(infile,line[i])){		
				
			if( (sNum-1) == i){
				catchLine = line[i];
				break;
			}
			i++;
		}
		infile.close();
		
		if(catchLine != ""){
			long long int pos = 0;
			string delimiter = ",";
			while ((pos = catchLine.find(delimiter)) != string::npos) {
			    service = catchLine.substr(0, pos);
			    catchLine.erase(0, pos + delimiter.length());
			    sprice = stoi( catchLine.substr(0, catchLine.size()-4) );
			}
			
			cout << "Enter the quantity : ";
			cin >> quantity;
			
			cout << "\nService		: " << service
				 << "\nUnit price 	: " << sprice
				 << "\nQuantity        : " << quantity
				 << "\nPrice		: " << sprice*quantity;
			
			{
				ofstream outfile("cart\\cart_S.txt",ios::app);
				outfile << service << "," << sprice*quantity << endl;
				outfile.close();
			}
			
			cout << "\n\n Successfully added to cart\n";
				 
			money_total(sprice*quantity,1,0);
		}else{
			cout << "Invalid service number\n";
		}
		
		char yn;
		cout << "\nDo you want to buy more services? (y/n) : ";
		cin >> yn;
		bool askReturn = true;
		
		while (askReturn){
			if(yn == 'n'){
				askReturn = false;
				break;
			}else if(yn == 'y'){
				break;
			}else{
				cout << "Invalid option\n";
			}
		}
		
		if (!askReturn){
			system("PAUSE");
			Header("Buy Service",0);
			break;
		}
	
		system("PAUSE");
		Header("Buy Service",0);
	}
	
	
}

void List_Services(string path){
	
	cout << "\n\t\t    List Services\n\n";
	
	string line[100], SANDP[200];
	int n = 0;
	
	ifstream infile(path);
	
	while(getline(infile,line[n])){
    	n++;
   	}
   	infile.close();
   	
   	int i = 0;
	for(int j = 0 ; j < n ; j++){
		long long int pos = 0;
		string delimiter = ",";
		while ((pos = line[j].find(delimiter)) != string::npos) {
		    SANDP[i] = line[j].substr(0, pos);
		    line[j].erase(0, pos + delimiter.length());
		    SANDP[i+1] = line[j].substr(0, pos+10);
			i+=2;
		}
	}
	
	int z = 0;
	cout << "\tName \t\t\t\tPrice" << "\n\n"; 
	for(int i = 0 ; i < (n*2) ; i+=2){
		cout <<  left <<setw(2) << ++z << " " << setw(32) << left << SANDP[i] << "\t" <<setw(32) <<SANDP[i+1] << "\n"; 
	}
	
	cout << endl;
	
}

void Search_services(){
	Header("Search Services",1);
	
	cout << "\n\t\t    Search Services\n\n";
	
	string line[10],SSP[20], Pname;
	bool isHas = false;
	int n = 0;
	
	cout << "Enter service name : ";
	cin >> Pname;
	
	ifstream infile("Services\\service.txt");
	for(int i = 0 ; i < 10 ; i++){
	    while(!infile.fail()){
	    	getline(infile,line[i]);
	    	if ( (line[i].find(Pname)) != (string::npos)){
				isHas = true;
				n++;
	        	break;
	       }
	   	}
	}
	infile.close();
    
    if(isHas){
		int pos = 0 , i = 0;
		string UP[2],delimiter = ",";
		for(int j = 0 ; j < n ; j++){
			while ((pos = line[j].find(delimiter)) != string::npos) {
			    SSP[i] = line[j].substr(0, pos);
			    line[j].erase(0, pos + delimiter.length());
			    SSP[i+1] = line[j].substr(0, pos+10);
				i+=2;
			}
		}
		
		int z = 0;
		cout << endl << setw(20) << "Name" << setw(28)  << "Price" << "\n\n"; 
		for(int i = 0 ; i < (n*2) ; i+=2){
			cout <<  left <<setw(2) << ++z << " " << setw(32) << left << SSP[i] << "\t" <<setw(32) <<SSP[i+1] << "\n"; 
		}
	}else{
		cout << "\nService not found, make sure search word is correct by checking in service list\n";
	}
		
	cout << endl;
	system("PAUSE");
	Header("Search Services",0);
}

void availableProduct(){
	bool stop = 0;
	while(!stop){
		Header("Available Product",1);
		cout << "\n\tAvailable Product\n";
		
		Available_Product_Menue();
		
		int option = 0;
		cout << "\nEnter the option : ";
		cin >> option;
		if(!cin){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Invalid option\n";
			system("PAUSE");
		}else{
			stop = Available_Product_Selection(option);
		}
		
		Header("Available Product",0);
	}
}

void Available_Product_Menue(){
	cout << "\n1. List Product\n"
		 << "2. Search Product\n" 
		;
			
	if(loginStatus || loginAdminStatus){
		cout << "3. Buy\n";
	}
	
	cout << "\n0. Back\n";
}

bool Available_Product_Selection(int option){		
	switch(option){
		case 1:
			Header("List Product",1);
			List_Product("Product\\Product.txt");
			system("PAUSE");
			Header("List Product",0);
			break;
		case 2:
			Search_Product();
			break;
		case 0:
			return 1;
			break;
		default:
			if(loginStatus || loginAdminStatus){
				buyProduct();
			}else{
				cout << "invalid option\n";
				system("PAUSE");
			}
	}
	return 0;
}

void List_Product(string path){
	
	cout << "\n\t\t    List Product\n\n";
	
	string line[100], SANDP[200];
	int n = 0;
	
	ifstream infile(path);
	
	while(getline(infile,line[n])){
    	n++;
   	}
   	infile.close();
   	
   	int i = 0;
	for(int j = 0 ; j < n ; j++){
		long long int pos = 0;
		string delimiter = ",";
		while ((pos = line[j].find(delimiter)) != string::npos) {
		    SANDP[i] = line[j].substr(0, pos);
		    line[j].erase(0, pos + delimiter.length());
		    SANDP[i+1] = line[j].substr(0, pos+10);
			i+=2;
		}
	}
	
	int z = 0;
	cout << "\tName \t\t\t\tPrice" << "\n\n"; 
	for(int i = 0 ; i < (n*2) ; i+=2){
		cout <<  left <<setw(2) << ++z << " " << setw(32) << left << SANDP[i] << "\t" <<setw(32) <<SANDP[i+1] << "\n"; 
	}
	
	cout << endl;
	
}

void Search_Product(){
	Header("Search Product",1);
	
	cout << "\n\t\t    Search Product\n\n";
	
	string line[10],SSP[20], Pname;
	bool isHas = false;
	int n = 0;
	
	cout << "Enter Product name : ";
	cin >> Pname;
	
	ifstream infile("Product\\Product.txt");
	for(int i = 0 ; i < 10 ; i++){
	    while(!infile.fail()){
	    	getline(infile,line[i]);
	    	if ( (line[i].find(Pname)) != (string::npos)){
				isHas = true;
				n++;
	        	break;
	       }
	   	}
	}
	infile.close();
    
    if(isHas){
		int pos = 0 , i = 0;
		string UP[2],delimiter = ",";
		for(int j = 0 ; j < n ; j++){
			while ((pos = line[j].find(delimiter)) != string::npos) {
			    SSP[i] = line[j].substr(0, pos);
			    line[j].erase(0, pos + delimiter.length());
			    SSP[i+1] = line[j].substr(0, pos+10);
				i+=2;
			}
		}
		
		int z = 0;
		cout << endl << " " << setw(20) << "Name" << setw(28)  << "Price" << "\n\n"; 
		for(int i = 0 ; i < (n*2) ; i+=2){
			cout <<  left <<setw(2) << ++z << " " << setw(32) << left << SSP[i] << "\t" <<setw(32) <<SSP[i+1] << "\n"; 
		}
	}else{
		cout << "\nProduct not found, make sure search word is correct by checking in service list\n";
	}
		
	cout << endl;
	system("PAUSE");
	Header("Search Product",0);
}

void adminMenue(){
	
	if (loginAdminStatus){
		cout << "\n\tWelcome admin "<< username << "\n\n";
	}else{
		cout << "\n\tWelcome "<< username << "\n\n";
	}
	
	
	cout << "1. Available Services\n"
		 << "2. Available Proucts\n" 
		 << "3. Manage Services & Proucts\n" 
		 << "4. Manage login\n"
		 << "5. Cart\n"
		;
	
	cout << "\n6. Logout\n" 
	     << "0. Exit\n";
}

void adminSelection(int option){
	switch(option){
		case 1:
			availableService();
			break;
		case 2:
			availableProduct();
			break;
		case 3:
			Manage_Services_Proucts();
			break;
		case 4:
			Manage_login();
			break;
		case 5:
			cart();
			break;	
		case 6:
			logout();
			break;
		case 0:
			system("CLS");
			exit(0);
			break;
		default:
			cout << "invalid option\n";
		}
}

void Manage_Services_Proucts(){
	bool stop = 0;
	while(!stop){
		Header("Manage Services Proucts",1);
		cout << "\n\tManage Services Proucts\n";
		
		 Manage_Services_Proucts_Menue();
		
		int option = 0;
		cout << "\nEnter the option : ";
		cin >> option;
		if(!cin){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Invalid option\n";
			system("PAUSE");
		}else{
			stop =  Manage_Services_Proucts_Selection(option);
		}
		
		Header("Manage Services Proucts",0);
	}
}

void Manage_Services_Proucts_Menue(){
	cout << "\nServices:\n"
		 << "    1. Add Services\n"
		 << "    2. Delete Services\n"
		 << "    3. Update Services\n"
		;
	
	cout << "\nProucts:\n"
		 << "    4. Add Proucts\n"
		 << "    5. Delete Proucts\n"
		 << "    6. Update Proucts\n"
		;
		
	cout << "\n0. Back\n";
}

bool Manage_Services_Proucts_Selection(int option){
	switch(option){
		case 1:
			Add_Services();
			break;
		case 2:
			Delete_Services();
			break;
		case 3:
			Update_Services();
			break;
		case 4:
			Add_Products();
			break;
		case 5:
			Delete_Products();
			break;
		case 6:
			Update_Products();
			break;
		case 0:
			return 1;
			break;
		default:
			cout << "invalid option\n";
	}
	return 0;
}

void Add_Products(){
	string Product, price;
	Header("Add Products",1);
	cout << "\nAdd Products\n\n";
	
	ifstream infile("Product\\Product.txt");

    if(infile){
    	
    	ofstream outfile("Product\\Product.txt", ios::app);
    	
    	cout << "Enter Product name : ";
		cin >> Product;
		
		cout << "Enter Product Price : ";
		cin >> price;
	
	    outfile << Product << "," << price << " LKR" << endl;
		outfile.close();
		cout << "Product added successfully\n";
	
	}else{
		cout << "Unable to access data file\n";
	}
	
	system("PAUSE");
	Header("Add Products",0);
}

void Add_Services(){
	string service, price;
	Header("Add Services",1);
	cout << "\nAdd Services\n\n";
	
	ifstream infile("Services\\service.txt");

    if(infile){
    	
    	ofstream outfile("Services\\service.txt", ios::app);
    	
    	cout << "Enter service name : ";
		cin >> service;
		
		cout << "Enter service Price : ";
		cin >> price;
	
	    outfile << service << "," << price << " LKR" << endl;
		outfile.close();
		cout << "Service added successfully\n";
	
	}else{
		cout << "Unable to access data file\n";
	}
	
	system("PAUSE");
	Header("Add Services",0);
}

void delete_S_P(string path, int sNum){
	string line[50];
	int i = 0 , j= 0;
	ifstream infile(path);
					
	while(getline(infile,line[i])){		
			
		if( (sNum) == i){
			line[i] = "";
		}
		i++;

	}
	infile.close();

	ofstream outfile(path);;
	while(i>j){
		if(line[j] !=""){
			outfile << line[j] << endl;
		}
		j++;
	}
	outfile.close();
}

void Delete_Products(){
	Header("Delete Products",1);
	
	cout << "\n\tDelete Products\n\n";
	
	int sNum = 0;
	cout << "Enter Products number : ";
	cin >> sNum;
	
	string line[50], catchLine;
	int i = 0 , j= 0;
	ifstream infile("Product\\Product.txt");
				
	while(getline(infile,line[i])){		
		if( (sNum-1) == i){
			catchLine = line[i];
		}
		i++;
	}
	infile.close();
	
	cout << "Confirm : \n"
		 << "	Once you deleted, \'" << catchLine << "\' no longer available to be a user of this\n"
		 << "	Do you want to delete (y/n) : "
		 ;
		 
	char yn;
	cin >> yn;
	
	if (yn == 'y'){
		{
			delete_S_P("Product\\Product.txt", (sNum-1) );
		}
		cout << "Deletion process successed\n";
	}else if(yn == 'n'){
		cout << "Deletion process cancelled\n";
	}else{
		cout << "invalid option\n";
	}
		 
	system("PAUSE");
	Header("Delete Products",0);
}

void Delete_Services(){
	Header("Delete Services",1);
	
	cout << "\n\tUpdate Services\n\n";
	
	int sNum = 0;
	cout << "Enter service number : ";
	cin >> sNum;
	
	string line[20], catchLine;
	int i = 0 , j= 0;
	ifstream infile("Services\\service.txt");
				
	while(getline(infile,line[i])){		
			
		if( (sNum-1) == i){
			catchLine = line[i];
		}
		i++;
	}
	infile.close();
	
	cout << "Confirm : \n"
		 << "	Once you deleted, \'" << catchLine << "\' no longer available to be a user of this\n"
		 << "	Do you want to delete (y/n) : "
		 ;
		 
	char yn;
	cin >> yn;
	
	if (yn == 'y'){
		{
			delete_S_P("Services\\service.txt", (sNum-1) );
		}
		cout << "Deletion process successed\n";
	}else if(yn == 'n'){
		cout << "Deletion process cancelled\n";
	}else{
		cout << "invalid option\n";
	}
		 
	system("PAUSE");
	Header("Delete Services",0);
}

void Update_Products(){
	Header("Update Products",1);
	
	cout << "\n\tUpdate Products\n\n";
	
	int sNum = 0;
	cout << "Enter Product number : ";
	cin >> sNum;
	
	string line[50], catchLine;
	int i = 0 , j= 0;
	ifstream infile("Product\\Product.txt");
				
	while(getline(infile,line[i])){		
			
		if( (sNum-1) == i){
			catchLine = line[i];
			line[i] = "";
		}
		i++;
	}
	infile.close();
	
	cout << "Confirm : \n"
		 << "	Are you going to update \' " << catchLine << " \' (y/n) : "
		 ;
		 
	char yn;
	cin >> yn;
	
	if (yn == 'y'){
		{	
			delete_S_P("Product\\Product.txt", (sNum-1) );
			
			string Product, price;
			ofstream outfile("Product\\Product.txt", ios::app);;
			
			cout << "Enter Product name : ";
			cin >> Product;
			
			cout << "Enter Product Price : ";
			cin >> price;
		
		    outfile << Product << "," << price << " LKR" << endl;
			outfile.close();
			cout << "Product updated successfully\n";
		}
	}else if(yn == 'n'){
		cout << "Deletion process cancelled\n";
	}else{
		cout << "invalid option\n";
	}
		 
	system("PAUSE");
	Header("Update Products",0);
}

void Update_Services(){
	Header("Update Services",1);
	
	cout << "\n\tUpdate Services\n\n";
	
	int sNum = 0;
	cout << "Enter service number : ";
	cin >> sNum;
	
	string line[20], catchLine;
	int i = 0 , j= 0;
	ifstream infile("Services\\service.txt");
				
	while(getline(infile,line[i])){		
			
		if( (sNum-1) == i){
			catchLine = line[i];
		}
		i++;
	}
	infile.close();
	
	cout << "Confirm : \n"
		 << "	Are you going to update \' " << catchLine << " \' (y/n) : "
		 ;
		 
	char yn;
	cin >> yn;
	
	if (yn == 'y'){
		{	
			delete_S_P("Services\\service.txt", (sNum-1) );
			
			string service, price;
			ofstream outfile("Services\\service.txt", ios::app);;
			
			cout << "Enter service name : ";
			cin >> service;
			
			cout << "Enter service Price : ";
			cin >> price;
		
		    outfile << service << "," << price << " LKR" << endl;
			outfile.close();
			cout << "Service updated successfully\n";
		}
	}else if(yn == 'n'){
		cout << "Deletion process cancelled\n";
	}else{
		cout << "invalid option\n";
	}
		 
	system("PAUSE");
	Header("Update Services",0);
}

void userMenue(){
	
	if (loginAdminStatus){
		cout << "\n\tWelcome admin "<< username << "\n\n";
	}else{
		cout << "\n\tWelcome "<< username << "\n\n";
	}
	
	
	cout << "1. Available Services\n"
		 << "2. Available Proucts\n" 
		 << "3. Manage login\n"
		 << "4. Cart\n"
		;
	
	cout << "\n5. Logout\n" 
	     << "0. Exit\n";
}

void userSelection(int option){
	switch(option){
		case 1:
			availableService();
			break;
		case 2:
			availableProduct();
			break;
		case 3:
			Manage_login();
			break;
		case 4:
			cart();
			break;	
		case 5:
			logout();
			break;
		case 0:
			system("CLS");
			exit(0);
			break;
		default:
			cout << "invalid option\n";
		}
}


void logout(){
	loginStatus = false;
	loginAdminStatus = false;
	resetCartSystem();
	Menue();
}

void signup(){
	Header("Signup",1);
	cout << "\nCreate Account\n\n";
	
	cout << "Enter username : ";
	cin >> username;
	
	ifstream infile("Login\\" + username + ".txt");

    if(!infile){
		cout << "Enter password : ";
		cin >> password;
		UP[1] = password;
		cout << "Confirm password : ";
		cin >> password;
		
		if(UP[1] == password){
		
			ofstream outfile("Login\\" + username + ".txt");
		    outfile << username << "," << password;
			outfile.close();
			
			ofstream masterFile("Login\\LMaster.txt",ios::app);
			masterFile << username << "," << password << endl;
			masterFile.close();

			cout << "Account created successfully\n";
		}else{
			cout << "Password mismatched\n";
		}
	
	}else{
		cout << "Username already taken\n";
	}
	
	system("PAUSE");
	Header("Signup",0);
}

void login(){ 
	string line;
	bool valid = false, isHas = false;
	
	Header("Login",1);
	
	cout << "\n\tLogin\n\n";
	
    cout << "Enter username : ";
    cin >> username;
	
    cout << "Enter password : ";
    cin >> password;
	
    ifstream infile("Login\\" + username + ".txt");
    while(!infile.fail()){
    	getline(infile,line);
    	if ( (line.find(username)) != (string::npos)){
			isHas = true;
        	break;
       }
   	}
	infile.close();
    
    if(isHas){
		int pos = 0;
		string UP[2],delimiter = ",";
		while ((pos = line.find(delimiter)) != string::npos) {
		    UP[0] = line.substr(0, pos);
		    line.erase(0, pos + delimiter.length());
		    UP[1] = line.substr(0, pos);
		}
		
		for(int i =0 ; i < 2 ; i++){	
		    if(username==UP[i] && password==UP[i+1]){
		    	valid = true;
		    	break;
		    }
		}
		
		if(valid){
			cout << "\nAccess Granted...\n";
		    loginStatus = true;
		    if(username.find("#") != string::npos){
		    	loginAdminStatus = 1;
			}else{
				loginAdminStatus = 0;
			}
		   
		}else{
			cout << "\nAccess Denied...Invalid Password.\n\n";
		    loginStatus = false;
		}
			  
	}else{
		cout << "\nAccess Denied...Account not found\n\n";
	    loginStatus = false;
	}
	 system("PAUSE");
	 Header("Login",0);
}

void Manage_login(){
	bool stop = 0;
	while(!stop){
		Header("Manage login",1);
		cout << "\n\tLogin\n";
		
		if(loginAdminStatus)
			admin_login_Menue();
		else
			user_login_Menue();
		
		int option = 0;
		cout << "\nEnter the option : ";
		cin >> option;
		if(!cin){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "Invalid option\n";
			system("PAUSE");
		}else{
			if(loginAdminStatus){
				stop = admin_login_Selection(option);
			}else
				stop = user_login_Selection(option);
		}
		
		Header("Manage login",0);
	}
}

void admin_login_Menue(){
	cout << "\nManage login Menue\n\n";
	
	cout << "1. Change Password\n"
		 << "2. Manage user accounts\n"
		 << "3. Delete Account\n" 
		;

	cout << "\n0. Back\n";
}

bool admin_login_Selection(int option){
	switch(option){
		case 1:
			changePassword();
			break;
		case 2:
			Manage_user_accounts();
			break;
		case 3:
			return deleteAccount();
			break;
		case 0:
			return 1;
			break;
		default:
			cout << "invalid option\n";
	}
	return 0;
}

void user_login_Menue(){
	cout << "\nManage login Menue\n\n";
	
	cout << "1. Change Password\n"
		 << "2. Delete Account\n" 
		;

	cout << "\n0. Back\n";
}

bool user_login_Selection(int option){
	switch(option){
		case 1:
			changePassword();
			break;
		case 2:
			return deleteAccount();
			break;
		case 0:
			return 1;
			break;
		default:
			cout << "invalid option\n";
	}
	return 0;
}

void changePassword(){
	Header("Change Password",1);
	
	cout << "\nChange Password\n\n";
	UP[1] = password;
	cout << "Enter old password : ";
	cin >> password;
	
	if(UP[1] == password){
		cout << "Enter new password : ";
		cin >> UP[1];
		{
			deleteUserML();
			ofstream outfile("Login\\LMaster.txt", ios::app);
	  	 	outfile << username << "," << UP[1] << endl;
			outfile.close();
		}
		ofstream outfile("Login\\" + username + ".txt");
	    outfile << username << "," << UP[1];
		outfile.close();
		
		cout << "Password changed successfully\n";
		
	}else{
		cout << "Invalid Password\n";
	}
	system("PAUSE");
	Header("Change Password",0);
}

bool deleteAccount(){
	Header("Delete Account",1);
	
	cout << "\n\tDelete Account\n\n";
	
	cout << "Confirm : \n"
		 << "	Once you deleted you are no longer authorized to be a user of this\n"
		 << "	Do you want to delete (y/n) : "
		 ;
		 
	char yn;
	cin >> yn;
	
	if (yn == 'y'){
		const string fileName = "Login\\" + username + ".txt";
		remove(fileName.c_str());
		deleteUserML();
		cout << "Account deleted successfully\n";
		
		loginStatus = 0;
		system("PAUSE");
		Header("Delete Account",0);
		return 1;
	}else if(yn == 'n'){
		cout << "Deletion process cancelled\n";
	}else{
		cout << "invalid option\n";
	}
		 
	system("PAUSE");
	Header("Delete Account",0);
	return 0;
}

void deleteUserML(){
		string line[100];
		int i = 0 , j= 0;
		ifstream infile("Login\\LMaster.txt");
		
		string lineCheck = username + "," + password;
		
		while(getline(infile,line[i])){		
			
			if(lineCheck == line[i]){
				line[i] = "";
			}
			i++;

		}
		infile.close();

		ofstream outfile("Login\\LMaster.txt");
		while(i>j){
			if(line[j] !=""){
				outfile << line[j] << endl;
			}
			j++;
		}
		outfile.close();
}

void Manage_user_accounts(){
	bool stop = 0;
	while(!stop){
		Header("Manage user accounts",1);
		
		cout << "\n\tManage user accounts\n\n";
		
		display_user_accounts();
		
		cout << "\nEnter user username : ";
		cin >> username;
		
		ifstream infilet("Login\\" + username + ".txt");
	
	    if(infilet){
			cout << "Enter user password : ";
			cin >> password;
			
			user_login_Menue();
		
			int option = 0;
			cout << "\nEnter the option : ";
			cin >> option;
			if(!cin){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "Invalid option\n";
				system("PAUSE");
			}else{
				stop = user_login_Selection(option);
			}
		}else{
			cout << "Account not found\n";
		}
		
		
		
			
		//system("PAUSE");
		Header("Manage user accounts",0);
	}
}

void display_user_accounts(){
	
	string line[100], DUA[200];
	int n = 0;
	
	ifstream infile("Login\\LMaster.txt");
	
	while(getline(infile,line[n])){
    	n++;
   	}
   	infile.close();
   	
   	int i = 0;
	for(int j = 0 ; j < n ; j++){
		int pos = 0;
		string delimiter = ",";
		while ((pos = line[j].find(delimiter)) != string::npos) {
		    DUA[i] = line[j].substr(0, pos);
		    line[j].erase(0, pos + delimiter.length());
		    DUA[i+1] = line[j].substr(0, pos);
		    i+=2;
		}
	}

	int z = 0;
	cout << "    Username\tPassword \n";
	for(int i = 0 ; i < n*2 ; i+=2){
		cout <<  setw(3) << ++z << " " << DUA[i] << "\t\t" << DUA[i+1] << "\n"; 
	}
}

void cart(){
	int sNum;
	char yn;
	
	string sline = "", pline = "";
	
	ifstream sinfile("Cart\\cart_S.txt");			
	getline(sinfile,sline);
	sinfile.close();
	
	ifstream pinfile("Cart\\cart_P.txt");			
	getline(pinfile,pline);
	pinfile.close();


	if( (sline != "") || (pline != "") ){
		Header("Cart",1);
		if(sline != ""){
			do{
				Header("Cart",0);
				Header("Cart",1);
					
				cout << "\n\t\t\t  Cart\n";
					
				List_Services("Cart\\cart_S.txt");
					
				cout << "Do you want to remove any service from the cart? (y/n) : ";
				cin >> yn;
					
				
				if(yn == 'y'){
					cout << "\nEnter the service number : ";
					cin >> sNum;
					money_total(find_price_delete_cart("Cart\\cart_S.txt",sNum),0,0);
					delete_S_P("Cart\\cart_S.txt", (sNum-1) );
				}
					
			}while(yn == 'y');
		}
		
		if(pline != ""){

			do{
				
				Header("Cart",0);
				Header("Cart",1);
				cout << "\n\t\t\t  Cart\n";
				List_Services("Cart\\cart_S.txt");
				
				
				List_Product("Cart\\cart_P.txt");
				
				cout << "Do you want to remove any product from the cart? (y/n) : ";
				
				cin >> yn;
				
				if(yn == 'y'){
					cout << "\nEnter the product number : ";
					cin >> sNum;
					money_total(find_price_delete_cart("Cart\\cart_P.txt",sNum),0,0);
					delete_S_P("Cart\\cart_P.txt", (sNum-1) );
				}
			
			}while(yn == 'y');
		}
		bill();
		Header("Cart",0);
	}else{
		cout << "\t\t Cart is empty \n";
		system("PAUSE");
	}
	

}

void bill(){
	Header("Bill",1);
			
	cout << "\n\t\t\t  Bill\n";	
	
	List_Services("Cart\\cart_S.txt");
	List_Product("Cart\\cart_P.txt");
	
	cout << setw(16) <<"Customer name : " << username << "\n";
	cout << setw(16) << "Total Price  :"  << total << "\n";
	
	cout << "\n\t\tThank you!\n\n";	
	
	resetCartSystem();

	system("Pause");
	Header("Bill",0);
}

float find_price_delete_cart(string path, int num){
	string line[50], SANDP[100];
	int n = 0;
	
	ifstream infile(path);
	
	while(getline(infile,line[n])){
    	n++;
   	}
   	infile.close();
   	
   	int i = 0;
	for(int j = 0 ; j < n ; j++){
		long long int pos = 0;
		string delimiter = ",";
		while ((pos = line[j].find(delimiter)) != string::npos) {
		    SANDP[i] = line[j].substr(0, pos);
		    line[j].erase(0, pos + delimiter.length());
		    SANDP[i+1] = line[j].substr(0, pos+10);
			i+=2;
		}
	}
	if(num>n)
		return 0.00;
	else
		return stof(SANDP[(2*num)-1]);
}
