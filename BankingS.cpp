//program imitating banking system via atm machine
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class BankingS
{
    public:
    string name;
    int accn,pin;
    double amt=0;
    BankingS()
    {
        name="";
        accn=0;pin=0;
        amt=0;
    }
    void universal(string u)
    {
        ifstream file("universal.txt");
        if(file)
        {
            fstream efile("universal.txt",ios::in|ios::out|ios::ate);
            efile<<u<<endl;
            efile.seekp(0,ios::end);
            efile.close();
            return;
        }
        ofstream ofile("universal.txt");
        ofile<<u<<endl;
        return;
    }
    int writer(string file,double exe)
    {
        amt=exe;
        ofstream outputFile(file);
        if(!outputFile)
        {
            cerr<<"Error opening file for writting"<<endl;
            return 1;
        }
        outputFile<<amt<<"\t\t\t\t\t\t"<<endl;
        outputFile<<"Name: "<<name<<endl;
        outputFile<<"Account No.: "<<accn<<endl;
        outputFile<<"Transaction Details: "<<endl;
        outputFile.close();
        return 0;
    }
    int edthistory(string file, double d, double w)
    {
        fstream outputFile(file,ios::in|ios::out|ios::ate);
        if(d==0)
        {
            outputFile<<"Withdrawn Rs. "<<w<<endl;
            outputFile.seekp(0,ios::end);
            outputFile.close();
        }
        if(w==0)
        {
            outputFile<<"Deposited Rs. "<<d<<endl;
            outputFile.seekp(0,ios::end);
            outputFile.close();
        }
    }
    int updatebalance(int amt,string file)
    {
        fstream outputFile(file);
        outputFile<<amt;
        outputFile.close();
        return 0;
    }
    int reader(string file)
    {
        ifstream inputFile(file);
        if(!inputFile)
        {
            cerr<<"Error showing details"<<endl;
            return 1;
        }
        string line;
        int i=0;
        while(getline(inputFile,line))
        {
            i++;
            if(i==1)
            continue;
            cout<<line<<endl;
        }
        return 0;
    }
    int create()
    {
        amt=0;
        cout<<"Enter your name (without spaces)"<<endl;
        cin>>name;
        cout<<"Enter your custom account number"<<endl;
        cin>>accn;
        for(;;)
        {
            cout<<"Enter your pin (4digit)"<<endl;
            cin>>pin;
            if(pin>=1000&&pin<=9999)
            break;
            else
            {
                cout<<"Enter 4 digit pin only"<<endl;
                continue;
            }
        }
        string filename;
        filename=to_string(accn)+to_string(pin)+".txt";
        ofstream outputFile(filename);
        if(outputFile.is_open())
        {
            writer(filename,amt);
            cout<<"Account created Successfully"<<endl;
        }
        else
        {
            cout<<"Account not created try again"<<endl;
        }
        universal(filename);
        return 0;
    }
    int withdraw(double take,string file,double exe)
    {
        amt=exe;
        if(amt<take)
        {
            cout<<"Insufficient funds"<<endl;
            return 1;
        }
        else
        {
            cout<<take<<" Rs. Withdrawn Successfully"<<endl;
            amt-=take;
            updatebalance(amt,file);
            edthistory(file,0,take);
            return 0;
        }
        return 0;
    }
    int deposit(double give,string file,double exe)
    {
        amt=exe;
        cout<<give<<" Rs. Deposited Successfully"<<endl;
        amt+=give;
        updatebalance(amt,file);
        edthistory(file,give,0);
        return 0;
    }
    int credit(string file,double exe,double cre)
    {
        amt=exe;
        amt+=cre;
        updatebalance(amt,file);
        fstream efile(file,ios::in|ios::out|ios::ate);
        efile<<cre<<" Rs. Credited"<<endl;
        efile.seekp(0,ios::end);
        efile.close();
        return 0;
    }
    int debit(string file,double exe,double deb)
    {
        amt=exe;
        cout<<deb<<" Rs. Debited"<<endl;
        amt-=deb;
        updatebalance(amt,file);
        fstream efile(file,ios::in|ios::out|ios::ate);
        efile<<deb<<" Rs. Debited"<<endl;
        efile.seekp(0,ios::end);
        efile.close();
        return 0;
    }
    int transactTo(string file,double exe,int f)
    {
        ifstream rfile("universal.txt");
        string line,line2="";
        while(getline(rfile,line))
        {
            if((stoi(line))/10000==f)
            {
                line2=line;
                break;
            }
        }
        if(line2=="")
        {
            cout<<"Account not found"<<endl;
            return 0;
        }
        cout<<"Account found, Enter the amount to be transferred"<<endl;
        double tamt;
        cin>>tamt;
        credit(line2,balance(line2),tamt);
        debit(file,balance(file),tamt);
        return 0;
    }
    int balance(string file)
    {
        ifstream inputFile(file);
        if(!inputFile)
        {
            cerr<<"Error opening file for writting"<<endl;
            return 1;
        }
        string line;
        int i=0;
        while(getline(inputFile,line))
        {
            i++;
            amt=stod(line);
            if(i>0)
            break;
        }
        return amt;
    }
    double interest(double time,string file)
    {
        double s;
        s=balance(file)*0.05*time;
        return s;
    }
    int login()
    {
        int accn;
        cout<<"Enter your account number"<<endl;
        cin>>accn;
        cout<<"Enter you pin"<<endl;
        cin>>pin;
        string file=to_string(accn)+to_string(pin)+".txt";
        ifstream inputFile(file);
        if(!inputFile)
        {
            cout<<"Invalid Username or Password"<<endl;
            return 1;
        }
        else
        cout<<"Welcome"<<endl;
        cout<<"Enter the operation"<<endl;
        cout<<"1. Show Account Balance"<<endl;
        cout<<"2. Withdraw Money"<<endl;
        cout<<"3. Deposit Money"<<endl;
        cout<<"4. Transfer Money"<<endl;
        cout<<"5. Show details"<<endl;
        cout<<"6. Predict Maturity Amount"<<endl;
        cout<<"7. Exit"<<endl;
        int choice;
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                balance(file);
                cout<<"Remaning Balance: "<<amt<<endl;
                return 0;
            }
            case 2:
            {
                cout<<amt<<endl;
                cout<<"Enter the amount"<<endl;
                double take;
                cin>>take;
                withdraw(take,file,balance(file));
                cout<<amt<<endl;
                return 0;
            }
            case 3:
            {
                cout<<"Enter the amount to be deposited"<<endl;
                double give;
                cin>>give;
                deposit(give,file,balance(file));
                return 0;
            }
            case 4:
            {
                int accn2;
                cout<<"Enter the recipient Account No. "<<endl;
                cin>>accn2;
                transactTo(file,balance(file),accn2);
                return 0;
            }
            case 5:
            {
                cout<<"Showing account details: "<<endl;
                reader(file);
                cout<<"Net Balance: "<<balance(file)<<endl;
                return 0;
            }
            case 6:
            {
                double time;
                cout<<"Enter expected time period on current balance"<<endl;
                cin>>time;
                cout<<"Current Balance: "<<balance(file)<<endl;
                cout<<"Maturity Value after "<<time<<" years: "<<interest(time,file)+balance(file)<<endl;
                cout<<"Rate of Interest: 5\% .p.a"<<endl;
                return 0;
            }
            case 7:
            {
                cout<<"Thank you!"<<endl;
                return 1;
            }
            default:
            {
                cout<<"Invalid input. Login again"<<endl;
                return 1;
            }
        }
    }
};
int main()
{
    BankingS bank;
    cout<<"Welcome to Anand Bank"<<endl;
    for(;;)
    {
        int choice;
        cout<<"Enter the choice from below options"<<endl;
        cout<<"1.Login"<<endl;
        cout<<"2.Create Account"<<endl;
        cin>>choice;
        if(choice==1)
        {
            if(bank.login()==1)
            return 0;
        }
        else if(choice==2)
        {
            bank.create();
            continue;
        }
        else
        cout<<"Invalid entry please try again"<<endl;

        for(int i=0;i<=100000;i++);

        cout<<"Do you want to continue? (y/n)"<<endl;
        char c;
        cin>>c;
        if(c=='y'||c=='Y')
        continue;
        else
        {
            cout<<"Thank You! Please visit us again"<<endl;    
            return 1;
        }
    }
}