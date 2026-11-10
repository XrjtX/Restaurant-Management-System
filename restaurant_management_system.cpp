#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<conio.h>
#include<ctime>
using namespace std;
class adminlogin
{
    char username[30],password[30];
    public:
    void setdata()
    {
        cout<<"Enter your username"<<endl;
        cin>>username;
         memset(password, 0, sizeof(password));
        cout<<"Enter your password"<<endl;
        int i = 0;
    char ch;
    while ((ch = _getch()) != '\r') {  // Enter key
        if (ch == '\b' && i > 0) {  // Handle backspace
            cout << "\b \b";
            i--;
        } else if (ch != '\b' && i < 29) {  // Max 29 chars + null
            password[i++] = ch;
            cout << '*';
        }
    }
    password[i] = '\0';  // Null terminate
    cout << endl;
    }
    void enter()
    {
        cout<<"Enter your username"<<endl;
        cin>>username;
         memset(password, 0, sizeof(password));
        cout<<"Enter your password"<<endl;
         int i = 0;
    char ch;
    while ((ch = _getch()) != '\r') {  // Enter key
        if (ch == '\b' && i > 0) {  // Handle backspace
            cout << "\b \b";
            i--;
        } else if (ch != '\b' && i < 29) {  // Max 29 chars + null
            password[i++] = ch;
            cout << '*';
        }
    }
    password[i] = '\0';  // Null terminate
    cout << endl;

    }
    char* getusername()
    {
        return username;
    }
    char* getpass()
    {
        return password;
    }

};
class inventory{
    char ingredients[30];
    float quantity;
    char unit[10];
    int ing_id;
    char expirydate[11];
    public:
    void setitems()
    {
        cout<<"Enter name of ingredient"<<endl;
        cin.ignore();
        cin.getline(ingredients,30);
        ing_id=generateID();
        cout<<"Enter quantity of food items"<<endl;
        cin>>quantity;
        cout<<"Enter unit(kg,litres,etc)"<<endl;
        cin>>unit;
        cout<<"Enter expiry date (YYYY-MM-DD)"<<endl;
        cin>>expirydate;
        }
    void displayinventory()
    {
        cout<<"|"<<setw(15)<<left<<ing_id<<"|"<<setw(10)<<left<<ingredients<<"\t\t"<<"|"<<setw(10)<<left<<quantity<<"\t"<<unit<<"|"<<setw(10)<<left<<expirydate<<"\t\t"<<"|"<<endl;
    }
    static int generateID() {
        ifstream fin("inventory.txt", ios::in|ios::binary);
        inventory temp;
        int maxID = 99;
        while (fin.read((char*)&temp, sizeof(temp))) {
            if (temp.ing_id > maxID) maxID = temp.ing_id;
        }
        fin.close();
        return maxID + 1;
    }
    void dinv()
    {
        cout<<"|"<<setw(15)<<left<<ing_id<<"|"<<setw(10)<<left<<ingredients<<"\t\t"<<"|"<<endl;
    }
    char* getingredients()
    {
        return ingredients;
    }
    int getingid()
    {
        return ing_id;
    }
    float getquantity()
    {
        return quantity;
    }
    char* getunit()
    {
        return unit;
    }
    void setquantity(float q)
    {
        quantity=q;
    }
    char* getexpirydate()
    {
        return expirydate;
    }
};
class menu{
protected:
char fooditems[30];
int fid;
int price;
public:
void setmenu()
{
    cout<<"Enter the item you want to add"<<endl;
    cin.ignore();
    cin.getline(fooditems,30);
    fid=generateFID();
    cout<<"Enter price of each food item"<<endl;
    cin>>price;
}
void displaymenu()
{
    cout<<"|"<<setw(15)<<left<<fid<<"|"<<setw(23)<<left<<fooditems<<"|"<<setw(15)<<left<<price<<"|"<<endl;   
}
    static int generateFID() {
        ifstream fin("menu1.txt", ios::in|ios::binary);
        menu temp;
        int maxID = 99;
        while (fin.read((char*)&temp, sizeof(temp))) {
            if (temp.fid > maxID) maxID = temp.fid;
        }
        fin.close();
        return maxID + 1;
    }
int getfid()
{
    return fid;
}
char* getfooditems()
{
    return fooditems;
}
int getprice()
{
    return price;
}
void setprice(int p)
{
    price=p;
}

};
class recipe{
    int menu_id;
    int ingredient_id;
    float quantity_req;
    public:
    void create_recipe(int menuid)
    {
        bool right=true;
         inventory e;
        ifstream fin;
         cout<<"-----------------------------------------"<<endl;
         cout<<"|INGREDIENT ID\t"<<setw(21)<<left<<"|INGREDIENTS\t"<<"|"<<endl;
         cout<<"-----------------------------------------"<<endl;
        fin.open("inventory.txt",ios::in|ios::binary);
                while(fin.read((char*)&e,sizeof(e)))
                {
                e.dinv();
                }
         cout<<"-----------------------------------------"<<endl;
            fin.close();
        cout<<"Enter number of ingredients in recipe:"<<endl;
        int count;
        cin>>count;
        for(int i=0;i<count;i++)
        {
            cout<<"Ingredient no."<<(i+1)<<"ID:";
            cin>>ingredient_id;
            cout<<"Quantity required:"<<endl;
            cin>>quantity_req;
            menu_id=menuid;
            if(validingid(ingredient_id)&& quantity_req>0)
            {
            saveinfile();
            }
            else{
                cout<<"Invalid values"<<endl;
                i--;
            }
        }
    }
    void saveinfile()
    {
        ofstream fout("recipe.txt",ios::app);
        fout.write((char*)this,sizeof(*this));
        fout.close();
    }
     bool validingid(int id)
  {
    inventory e;
    ifstream fin;
    fin.open("inventory.txt",ios::in);
    while(fin.read((char*)&e,sizeof(e)))
    {
        if(id==e.getingid()||id<0)
        {
            return true;
        }
    }
    return false;
    fin.close();
  }
    int getid()
    {
        return menu_id;
    }
    int geting_id()
    {
        return ingredient_id;
    }
    float getqty()
    {
        return quantity_req;
    }
};
class bill : public menu {
    int total;
    char custom_name[40];
    char timestamp[100];
    float quantity;

public:
    // Fill bill details from order
    void getbill(int id, char* name, int price, float qty) {
        fid = id;
        strcpy(fooditems, name);
        this->price = price;
        quantity = qty;
        total = price * quantity;

        // Get current date & time
        time_t now = time(0);
        strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    }

    // Store customer name
    void getinfo(char* name) {
        strcpy(custom_name, name);
    }

    // Print bill in table format
    void showbill() {
        cout << "|" << setw(10) << left << fid
             << "|" << setw(25) << left << fooditems
             << "|" << setw(15) << left << price
             << "|" << setw(15) << left << quantity
             << "|" << setw(15) << left << total
             << "|" << setw(30) << left << timestamp
             << "|\n";
    }

    // Simple display format
    void display() {
        cout << custom_name << endl;
        cout << fid << "\t" << fooditems << "\t" << price << "\t"
             << quantity << "\t" << total << endl;
    }

    // Getter for total
    int gettotal() {
        return total;
    }

    // Getter for customer name
    char* getname() {
        return custom_name;
    }

    // Getter for timestamp (const for safety)
    const char* getTimestamp() {
        return timestamp;
    }
};


class employee{
    char name[30],address[30];
    int salary,id;
    public:
    void getdata()
    {
        cout<<"Enter name of the employee"<<endl;
        cin>>name;
        cout<<"Enter id of the employee"<<endl;
        cin>>id;
        cout<<"Enter address of the employee"<<endl;
        cin>>address;
        cout<<"Enter the salary of the employee"<<endl;
        cin>>salary;
    }
    int getid()
    {
        return id;
    }
    int getsalary()
    {
        return salary;
    }
    void display()
    {
       cout<<"|"<<setw(7)<<left<<id<<"|"<<setw(23)<<left<<name<<"|"<<setw(22)<<left<<address<<"|"<<setw(16)<<left<<salary<<"|"<<endl;
    }
};
class earning{
 int money;
 public:
 earning()
 {
    money=0;
 }
 void view_earn()
 {
    cout<<"The earned amount is"<<money;
 }
 int setmoney()
 {
    return money;
 }
 void load()
 {
    ifstream fin("earning.txt",ios::binary);
    if(fin.read((char*)&(*this),sizeof(*this)))
        {

        }
        else
        {
            money=0;
        }
 }
 void getmoney(int x)
 {
   load();
    money=money+x;
    ofstream fout("earning.txt",ios::binary|ios::trunc);
    fout.write((char*)this,sizeof(*this));
    fout.close();
 }
};
class rating{
    int stars;
    char comment[100];
    char name[30];
    public:
    void input()
    {
        cout<<"Enter your name or you can leave it blank:"<<endl;
        cin.ignore();
        cin.getline(name,30);
        cout<<"Rate the restaurant(1-5):"<<endl;
        cin>>stars;
        cin.ignore();
        cout<<"Any feedback?"<<endl;
        cin.getline(comment,100);
    }
    void show()
    {
        cout<<"Customer Name:";
        if(strcmp(name,"")==0)
        {
            cout<<"Anonymous"<<endl;
        }
        else{
            cout<<name<<endl;
        }
        cout<<"Rating:"<<stars<<"\5"<<endl;
        cout<<"Feedback:"<<comment<<endl;
    }
      void saveToFile() 
     {
        ofstream fout("company_ratings.txt", ios::app | ios::binary);
        fout.write((char*)this, sizeof(*this));
        fout.close();
    }
    void showAllRatings() 
    {
        ifstream fin("company_ratings.txt", ios::binary);
        rating r;
        int count = 0;
        while (fin.read((char*)&r, sizeof(r))) {
            cout << "Rating #" << ++count << ":\n";
            r.show();
            cout << "-----------------------------\n";
        }
        fin.close();
        if (count == 0)
            cout << "No ratings available yet.\n";
    }
    int star()
    {
        return stars;
    }
    
};

    bool logged(char* username, char* password){
        adminlogin b;
        ifstream fin;
             fin.open("login.txt",ios::in|ios::binary);
             while(fin.read((char*)&b, sizeof(b))) 
             {
                if(strcmp(b.getusername(),username)==0&&strcmp(b.getpass(),password)==0)
                {
                    return true;
                }
         
             }
             return false;
             fin.close();
  }
  /* bool validfidn(int id, char* name)
  {
    inventory e;
    ifstream fin;
    fin.open("inventory.txt",ios::in|ios::binary);
    while(fin.read((char*)&e,sizeof(e)))
    {
        if(id==e.getfid()&&strcmp(e.getfooditems(),name)==0)
        {
            return true;
        }
    }
    fin.close();
    return false;
  }*/
  bool validid(int id)
  {
    employee e;
    ifstream fin;
    fin.open("employee.txt",ios::in);
    while(fin.read((char*)&e,sizeof(e)))
    {
        if(id==e.getid()||id<0)
        {
            return false;
        }
    }
    return true;
    fin.close();
  }
  
  bool validfname(char* fname)
  {
    inventory i;
    ifstream fin;
    fin.open("inventory.txt",ios::in|ios::binary);
    while(fin.read((char*)&i,sizeof(i)))
    {
        if(strcmp(i.getingredients(),fname)==0)
        {
            return true;
        }
    }
    return false;
    fin.close();
  }
  bool validmenu(char* fname)
  {
    menu m;
    ifstream fin;
    fin.open("menu1.txt",ios::in|ios::binary);
     while(fin.read((char*)&m,sizeof(m)))
    {
        if(strcmp(m.getfooditems(),fname)==0)
        {
            return true;
        }
    }
    return false;
    fin.close();
  }
void showBillsByDate(const char* targetDate) {
    bill b;
    ifstream fin("bill.txt", ios::in | ios::binary);
    bool found = false;
    char lastCustomer[40] = ""; // To track when customer changes
    char lcustomer[40];

    cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
    cout<<"|                                                   BILLS                                                            |"<<endl;
     cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
    cout <<"|Bills on date: " << targetDate<<"                                                                                           |" << endl;

    while (fin.read((char*)&b, sizeof(bill))) {
        if (strncmp(b.getTimestamp(), targetDate, 10) == 0) {
            if (strcmp(lastCustomer, b.getname()) != 0) {
                // New customer
              cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                strcpy(lastCustomer, b.getname());
                cout << "\nCustomer: " << lastCustomer << endl;
                 cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
                cout<<"|" << setw(10)<<left<<"FID"<<"|" <<setw(25)<<left<<"Item"<<"|"<<setw(15)<<left<<"Price"<<"|"<<setw(15)<<left<<"Qty"<<"|"<<setw(15)<<left<<"Total"<<"|"<<setw(30)<<left<<"Time"<<"|"<<endl;
                 cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
            }
            b.showbill();

            found = true;
        }
        
    }
     cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
    
    fin.close();

    if (!found) {
        cout << "No bills found on that date." << endl;
    }
}
bool validdate(char* date)
{
    if(strlen(date)==10&& date[4]=='-'&& date[7]=='-')
    {
        return true;
    }
    else{
        return false;
    }
}
void deleteexpired()
{
    ifstream fin;
    ofstream fout;
    fin.open("inventory.txt",ios::in);
    fout.open("temp.txt",ios::out);
    inventory e;
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char today[11];
    strftime(today, sizeof(today), "%Y-%m-%d", localtm);

    while (fin.read((char*)&e, sizeof(e))) {
        if (strcmp(e.getexpirydate(), today) >= 0) {
            fout.write((char*)&e, sizeof(e));  
        }
    }

    fin.close();
    fout.close();

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");
}
struct RecipeLine {
    int ing_id;
    float qtyperunit;
};
bool loadrecipe(int menuid, RecipeLine recipee[], int& count)
{  
    recipe r;
       count=0;
       ifstream fin;
       fin.open("recipe.txt",ios::in|ios::binary);
       while(fin.read((char*)&r,sizeof(r)))
       {
        if(r.getid()==menuid)
        {
            recipee[count].ing_id=r.geting_id();
            recipee[count].qtyperunit=r.getqty();
            count++;
        }
       }
       fin.close();
       /*if(count>0)
       {
        return true;
       }
       else{
        return false;
       }*/
      return count>0;
}

int main()
{
    adminlogin a;
    int c,n,x,i;
    char ch;
    cout<<"==========================================="<<endl;
    cout<<"|       Restaurant Management System      | "<<endl;
    cout<<"==========================================="<<endl;
    cout<<"|1. Admin                                 |\n|2. Customer                              |\n|3. Exit                                  |"<<endl;
    cout<<"==========================================="<<endl;
    cout<<"Enter your choice"<<endl;
    cin>>c;
    switch(c)
    {
        case 1:
        system("cls");
        cout<<"1. Create a new account"<<endl;
        cout<<"2. login into existing"<<endl;
        cin>>n;
        system("cls");
        if(n==1)
        {
          ifstream fin_log("login.txt",ios::binary);
            if(fin_log)
            {
                cout<<"Verify as Admin:"<<endl;
                a.enter();
                if(logged(a.getusername(),a.getpass()))
                {
                    cout<<"Admin verified"<<endl;
                    system("cls");
                    cout<<"Enter username and password for new account"<<endl;
                    ofstream fout;
                    fout.open("login.txt",ios::out|ios::app|ios::binary);
                    a.setdata();
                    fout.write((char*)&a, sizeof(a));
                    fout.close();
                    cout<<"username and password saved"<<endl;
            
        }
    }
}
        if(n==2)
        {
            reenter:
            a.enter();
       
        if(logged(a.getusername(),a.getpass()))
        {
            do{
             system("cls");
            cout<<"you are entered"<<endl;
            //cout<<"1.Inventory\n 2.Menu \n 3.Employee \n 4.View Bill records \n 5.View Earnings"<<endl;
cout<< "+---------------------------+\n";
cout<< "|   1. Inventory            |\n";
cout<< "|   2. Menu                 |\n";
cout<< "|   3. Employees            |\n";
cout<< "|   4. View Bills           |\n";
cout<< "|   5. Earnings             |\n";
cout<< "|   6. View Rating          |\n";
cout<< "+---------------------------+\n";
cout<<"Enter your choice"<<endl;
            cin>>i;
            system("cls");
           switch(i)
           {
          //  char c[40];
           case 1:
           {
           char c[40];
           cout<<"==========================================="<<endl;
           cout<<"|                Inventory                |"<<endl;
           cout<<"==========================================="<<endl;
           cout<<"|          1.Add in Inventory             |\n";
           cout<<"|          2.View Inventory               |\n";
           cout<<"|          3.Update from Inventory        |\n";
           cout<<"|          4.Delete from Inventory        |\n";
           cout<<"==========================================="<<endl;
            cout<<"Enter your choice"<<endl;
            cin>>x;
            system("cls");
            if(x==1)
            {
                int count=0;
                inventory s;
                ifstream fin("inventory.txt",ios::in|ios::binary);
                s.setitems();
                if(!validfname(s.getingredients())&&s.getquantity()>0&&validdate(s.getexpirydate()))
                {
                ofstream fout;
                fout.open("inventory.txt",ios::out|ios::app|ios::binary);
                fout.write((char*)&s,sizeof(s));
                fout.close();
                }
                else if(s.getquantity()<0)
                {
                    cout<<"Invalid values"<<endl;
                }
                else if(validfname(s.getingredients()))
                {
                    cout<<"Fooditem already exists"<<endl;
                }
                else{
                    cout<<"Expiry date is in wrong format(correct format: YYYY-MM-DD)"<<endl;
                }
            }
            if(x==2)
            {
                inventory s;
                ifstream fin;
                 cout<<"---------------------------------------------------------------------------------"<<endl;
    cout<<"|INGREDIENT ID\t"<<setw(21)<<left<<"|INGREDIENTS\t"<<setw(12)<<left<<"|QUANTITY\t"<<setw(12)<<left<<"|EXPIRY DATE\t\t"<<"|"<<endl;
    cout<<"---------------------------------------------------------------------------------"<<endl;
                fin.open("inventory.txt",ios::in|ios::binary);
                while(fin.read((char*)&s,sizeof(s)))
                {
                s.displayinventory();
                }
                cout<<"---------------------------------------------------------------------------------"<<endl;
                fin.close();
            }
if(x==3)
{
    char ing[30];
    cout<<"Enter ingredient name you want to update"<<endl;
    cin.ignore();
    cin.getline(ing, 30);
    inventory e;
    bool found=false;
    int add_qty;
    ifstream fin;
    ofstream fout;
    fin.open("inventory.txt",ios::in|ios::binary);
    fout.open("temp.txt",ios::out|ios::binary);
    while(fin.read((char*)&e,sizeof(e)))
    {
        if(strcmp(e.getingredients(),ing)==0)
        {
            found=true;
            cout<<"Current quantity: "<<e.getquantity()<<"\t"<<e.getunit()<<endl;
            cout<<"Enter quantity to be added"<<endl;
            cin>>add_qty;
            e.setquantity(e.getquantity()+add_qty);
            cout<<"New quantity is: "<<e.getquantity()<<"\t"<<e.getunit()<<endl;
        }
        fout.write((char*)&e,sizeof(e));
    }
    fin.close();
    fout.close();
    remove("inventory.txt");
    rename("temp.txt","inventory.txt");
    if(found)
    {
        cout<<"Inventory updated successfully"<<endl;
    }
    else{
        cout<<"Ingredient not found in inventory"<<endl;
    }
}
    if(x==4)
    {
        char del_item[30];
        cout<<"Enter ingredient you want to delete"<<endl;
        cin>>del_item;
        inventory item;
        ifstream fin;
        ofstream fout;
        bool found=false;
        fin.open("inventory.txt",ios::in|ios::binary);
        fout.open("temp.txt",ios::out|ios::binary);
        while(fin.read((char*)&item,sizeof(item)))
        {
            if(strcmp(item.getingredients(),del_item)!=0)
            {
                fout.write((char*)&item,sizeof(item));
            }
            else{
                found=true;
            }
        }
        fin.close();
        fout.close();
        remove("inventory.txt");
        rename("temp.txt","inventory.txt");
        if(found)
        {
            cout<<"Ingredient removed from inventory"<<endl;
        }
        else{
            cout<<"Ingredient not found in inventory"<<endl;
        }
    }
            break;
}
            case 2:
            {
            char c[40];
           cout<<"======================================"<<endl;
           cout<<"|                Menu                |"<<endl;
           cout<<"======================================"<<endl;
           cout<<"|          1.Add in Menu             |\n";
           cout<<"|          2.View Menu               |\n";
           cout<<"|          3.Update from Menu        |\n";
           cout<<"|          4.Delete from Menu        |\n";
           cout<<"======================================"<<endl;
            cin>>x;
            system("cls");
            if(x==1)
            {
                menu m;
                recipe r;
                bool exists=true;
                m.setmenu();
                ifstream fin;
                fin.open("menu1.txt",ios::in|ios::binary);
                if(!validmenu(m.getfooditems())&& m.getprice()>0)
                {
                    exists=false;
                cout<<"Create recipe for the fooditem"<<endl;
                r.create_recipe(m.getfid());
                ofstream fout;
                fout.open("menu1.txt",ios::out|ios::app);
                fout.write((char*)&m,sizeof(m));
                }
            else if(validmenu(m.getfooditems()))
            {
                cout<<"Fooditem already exists"<<endl;
            }
            else
            {
                cout<<"Invalid values"<<endl;
            }

            }
            if(x==2)
            {
                menu m;
                ifstream fin;
                fin.open("menu1.txt",ios::in|ios::binary);
                 cout<<"---------------------------------------------------------"<<endl;
                 cout<<"|                       Menu                            |"<<endl;
                                 cout<<"---------------------------------------------------------"<<endl;
    cout<<"|FOOD ID\t"<<setw(19)<<left<<"|FOOD ITEM\t"<<setw(30)<<left<<"|PRICE\t\t|"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
               while(fin.read((char*)&m,sizeof(m)))
               {
                m.displaymenu();
               }
               fin.close();
            }
             cout<<"---------------------------------------------------------"<<endl;
            if(x==3)
            {
                int p;
                cout<<"Enter the name of fooditem you want to update price"<<endl;
                cin>>c;
                if(validmenu(c))
                {
                    
                menu men;
        ifstream fin("menu1.txt",ios::in|ios::binary);
        ofstream fout("temp.txt",ios::out|ios::binary);
        bool updated = false;

        while(fin.read((char*)&men,sizeof(men)))
        {
            if(strcmp(men.getfooditems(),c)== 0)
            {
                cout<<"Enter new price"<<endl;
                cin>>p;
                men.setprice(p);
                updated = true;
            }
            fout.write((char*)&men, sizeof(men));
        }

        fin.close();
        fout.close();
        remove("menu1.txt");
        rename("temp.txt", "menu1.txt");

        if(updated)
            cout<<"Menu updated successfully!"<<endl;
        else
            cout<<"Item not found!"<<endl;
    }
    else
    {
        cout<<"Food item not found in menu."<<endl;
    }
    }
     if(x==4)
    {
        char del_item[30];
        cout<<"Enter fooditem you want to delete"<<endl;
        cin>>del_item;
        menu men;
        ifstream fin;
        ofstream fout;
        bool found=false;
        fin.open("menu1.txt",ios::in|ios::binary);
        fout.open("temp.txt",ios::out|ios::binary);
        while(fin.read((char*)&men,sizeof(men)))
        {
            if(strcmp(men.getfooditems(),del_item)!=0)
            {
                fout.write((char*)&men,sizeof(men));
            }
            else{
                found=true;
            }
        }
        fin.close();
        fout.close();
        remove("menu1.txt");
        rename("temp.txt","menu1.txt");
        if(found)
        {
            cout<<"Fooditem removed from menu"<<endl;
        }
        else{
            cout<<"Fooditem not found in menu"<<endl;
        }
    }
            break;}
            case 3:
            {
            cout<<"1.Add employee details \n 2.View employee details \n 3. Delete employee records"<<endl;
            cin>>x;
            system("cls");
            employee e;
            if(x==1)
            {
                e.getdata();
                if(validid(e.getid())&&e.getsalary()>=0)
                {
                ofstream fout;
                fout.open("employee.txt",ios::out|ios::app);
                fout.write((char*)&e,sizeof(e));
                fout.close();
             }
             else if(e.getsalary()<0)
             {
                cout<<"Invalid values"<<endl;
             }
             else{
                cout<<"Employee id already exists"<<endl;
             }
        }
        if(x==2)
        {
            ifstream fin;
            fin.open("employee.txt",ios::in);
                cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"|ID\t"<<setw(23)<<left<<"|EMPLOYEE NAME\t"<<setw(16)<<left<<"|ADDRESS\t"<<setw(21)<<left<<"|SALARY\t\t|"<<endl;
    cout<<"-------------------------------------------------------------------------"<<endl;
            while(fin.read((char*)&e,sizeof(e)))
            {
                e.display();
            }
            fin.close();
             cout<<"-------------------------------------------------------------------------"<<endl;
        }
          if(x==3)
    {
        int del_item;
        cout<<"Enter employee id you want to delete"<<endl;
        cin>>del_item;
        employee emp;
        ifstream fin;
        ofstream fout;
        bool found=false;
        fin.open("employee.txt",ios::in|ios::binary);
        fout.open("temp.txt",ios::out|ios::binary);
        while(fin.read((char*)&emp,sizeof(emp)))
        {
            if(emp.getid()!=del_item)
            {
                fout.write((char*)&emp,sizeof(emp));
            }
            else{
                found=true;
            }
        }
        fin.close();
        fout.close();
        remove("employee.txt");
        rename("temp.txt","employee.txt");
        if(found)
        {
            cout<<"Employee record deleted"<<endl;
        }
        else{
            cout<<"Employee record not found "<<endl;
        }
    }
        break;}
        case 4:
    {
            char date[11]; // YYYY-MM-DD + null
            cout << "Enter date to view bills (YYYY-MM-DD): ";
            cin >> date;
            if(validdate(date))
            {
            showBillsByDate(date);
            }
            else{
                cout<<"Invalid date format"<<endl;
            }
            break;}
        case 5:
        {
        earning a;
        int n;
        cout<<"1. View all earnings"<<endl;
        cout<<"2. View earnings between dates"<<endl;
        cin>>n;
        if(n==1)
        {
        ifstream fin;
        fin.open("earning.txt",ios::in|ios::binary);
        while(fin.read((char*)&a,sizeof(a)))
        {
            a.view_earn();
        }
        cout<<endl;
        fin.close();
    }
  if(n==2)
  {     
char start_date[11], end_date[11];
cout << "Enter start date (YYYY-MM-DD): ";
cin >> start_date;
cout << "Enter end date (YYYY-MM-DD): ";
cin >> end_date;
if(validdate(start_date)&& validdate(end_date))
{
if (strcmp(start_date, end_date) > 0) {
    cout << "Start date is after end date. Swapping them." << endl;
    swap(start_date, end_date);
}
int earnings = 0;
bill b;
ifstream fin1("bill.txt", ios::binary);

while (fin1.read((char*)&b, sizeof(b))) {
    if (strncmp(b.getTimestamp(), start_date, 10) >= 0 &&
        strncmp(b.getTimestamp(), end_date, 10) <= 0) {
        earnings += b.gettotal();
    }
}
fin1.close();

cout << "Earnings from " << start_date << " to " << end_date << ": Rs. " << earnings << endl;
}
else{
    cout<<"Invalid date format(proper format: YYYY-MM-DD)"<<endl;
}
  }

        break;}
        case 6:
        {
        rating r;
        r.showAllRatings();
        break;}
    }
        cout<<"do you want to continue(y/n)"<<endl;
        cin>>ch;
    }while(ch!='n');
    }
        else
        {
            cout<<"password incorrect"<<endl;
            int z;
            cout<<"Do you want to reenter(1) or forgot password(2)"<<endl;
            cin>>z;
            if(z==1)
            {
                goto reenter;
            }
            else if(z==2)
            {
             ifstream fin_log("login.txt",ios::binary);
             ofstream fout("temp.txt",ios::out|ios::app|ios::binary);
            if(fin_log)
            {
                char username[30];
                bool changed=false;
                cout<<"Verify as Admin:"<<endl;
                a.enter();
                if(logged(a.getusername(),a.getpass()))
                {
                    cout<<"Admin verified"<<endl;
                    cout<<"enter your username"<<endl;
                    cin>>username;
                    adminlogin previous=a;
                    while(fin_log.read((char*)&a,sizeof(a)))
                    {
                        if((strcmp(a.getusername(),username))==0)
                        {
                            cout<<"enter new username and password"<<endl;
                            a.enter();
                            fout.write((char*)&a,sizeof(a));
                            changed=true;
                        }
                        else{
                            fout.write((char*)&previous,sizeof(previous));
                        }
                    }
                    fin_log.close();
                    fout.close();
                    if(changed)
                    {
                        remove("login.txt");
                        rename("temp.txt","login.txt");
                        cout<<"Password changed successfully"<<endl;
                    }
                    else{
                        remove("temp.txt");
                        cout<<"Username not found"<<endl;
                    }
                }
            }
        }
    }
}
    break;
      //Customer part
    case 2:
    int ch;
    dash:
    system("cls");
    cout<<"================================================"<<endl;
    cout<<"|       WELCOME TO OUR RESTAURANT              | "<<endl;
    cout<<"================================================"<<endl;
    cout<<"|                1. View Menu                  | "<<endl;
    cout<<"|                2. Place Order                | "<<endl;
    cout<<"|                3. Rate the Restaurant        | "<<endl;
    cout<<"================================================"<<endl;
    cout<<"Enter your choice"<<endl;
    cin>>n;
    system("cls");
    deleteexpired();
    if(n==1)
    {
        menu m;
        ifstream fin;
        fin.open("menu1.txt",ios::in|ios::binary);
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"|                       Menu                            |"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"|FOOD ID\t"<<setw(19)<<left<<"|FOOD ITEM\t"<<setw(30)<<left<<"|PRICE\t\t|"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
       while(fin.read((char*)&m,sizeof(m)))
       {
        m.displaymenu();
       }
     cout<<"---------------------------------------------------------"<<endl;
       fin.close();
       cout<<"Do you want to go back to dashboard(1) or Exit(2)"<<endl;
       cin>>ch;
       if(ch==1)
       {
        goto dash;
       }
       else{
        exit;
       }
    }
   if(n==2)
    {
        char choice;
        int count=0;
        inventory e[100];
        bill b[100];
        float q;
        int j=-1;
        char customer_name[40];
        int order_grand_total = 0;
        cout<<"\n--- Customer Order ---"<<endl;
        cout<<"Enter your name: ";
        cin>>customer_name;
        ifstream fin1;
        fin1.open("inventory.txt",ios::in|ios::binary);
        while(fin1.read((char*)&e[count],sizeof(inventory)))
        {
            count++;
        }
        fin1.close();
        do{
        menu m;
        ifstream fin;
        fin.open("menu1.txt",ios::in|ios::binary);
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"|                       Menu                            |"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    cout<<"|FOOD ID\t"<<setw(19)<<left<<"|FOOD ITEM\t"<<setw(30)<<left<<"|PRICE\t\t|"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
       while(fin.read((char*)&m,sizeof(m)))
       {
        m.displaymenu();
       }
    cout<<"---------------------------------------------------------"<<endl;
       fin.close();
       cout<<endl<<"enter foodid of food you want to order"<<endl;
       cin>>x;
       cout<<"Enter quantity"<<endl;
       cin>>q;
 if(q<10)
 {
 RecipeLine recipe[20];
 int rec_count=0;
bool recipeloaded=loadrecipe(x,recipe,rec_count);
if(recipeloaded)
{
    bool availability=true;
    for(int r=0;r<rec_count;r++)
    {
        bool found=false;
        for(int i=0;i<count;i++)
        {
            if(recipe[r].ing_id==e[i].getingid())
            {
                if(e[i].getquantity()<(recipe[r].qtyperunit*q))
                {
                    availability=false;
                }
                found=true;
                break;
            }
        }
        if(!found)
        {
            availability=false;
        }
    }
    if(availability)
    {
        for(int r=0;r<rec_count;r++)
        {
            for(int i=0;i<count;i++)
            {
                if(e[i].getingid()==recipe[r].ing_id)
                {
                    float newqty=e[i].getquantity()-(recipe[r].qtyperunit*q);
                    e[i].setquantity(newqty);
                    break;
                }
            }
        }

menu m;
ifstream fin;
fin.open("menu1.txt",ios::in|ios::binary);
while(fin.read((char*)&m,sizeof(m)))
{
    if(m.getfid()==x)
    {
        j++;
        b[j].getbill(x,m.getfooditems(),m.getprice(),q);
        b[j].getinfo(customer_name);
        order_grand_total+=b[j].gettotal();
        break;
    }
}
fin.close();
cout<<"Item ordered successsfully"<<endl;
}
 else{
    cout<<"Sorry Not enough ingredients"<<endl;
   }
}
else{
    cout<<"No recipe found for this item"<<endl;
}
}
else{
    cout<<"Sorry we are incapable of making this much item right now"<<endl;
}

     cout<<"do you want to order again(y/n)"<<endl;
        cin>>choice;
    }while(choice!='n');
    ofstream fout;
    fout.open("inventory.txt",ios::out|ios::binary|ios::trunc);
    for(i=0;i<count;i++)
    {
        fout.write((char*)&e[i],sizeof(inventory));
    }
    fout.close();
    fout.open("bill.txt",ios::out|ios::app);
    for(i=0;i<=j;i++)
    {
        fout.write((char*)&b[i],sizeof(bill));
    }
fout.close();
cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
 cout<<"|" << setw(10)<<left<<"FID"<<"|" <<setw(25)<<left<<"Item"<<"|"<<setw(15)<<left<<"Price"<<"|"<<setw(15)<<left<<"Qty"<<"|"<<setw(15)<<left<<"Total"<<"|"<<setw(30)<<left<<"Time"<<"|"<<endl;
 cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;

for(i=0;i<=j;i++)
{
    b[i].showbill(); 
}
cout<<"---------------------------------------------------------------------------------------------------------------------"<<endl;
 
cout<<"Grand total:"<<order_grand_total<<endl;
earning a;
a.getmoney(order_grand_total);
    }
    if(n==3)
    {
        rating r;
        r.input();
        if(r.star()<0||r.star()>5)
        {
            cout<<"Invalid stars"<<endl;
        }
        else{
            r.saveToFile();
        }
    }
    
       break;
       case 3:
       exit;
        }
    return 0;
}