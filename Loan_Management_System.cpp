#include <iostream>
#include <cctype>
using namespace std;


struct TranscationNode{
    int tid;
    int borrowerid;
    int lenderid;
    float amount;
    int borrowdDays;
    int allowedDays;
    float finePercentage;
    bool returned;
    TranscationNode* next;
};

struct UserNode{
    int id;
    string name;
    bool active;
    TranscationNode* borrowList;
    TranscationNode* PaymentList;
    UserNode*left;
    UserNode*rigth;
};

int safeInt(string prompt, int minVal, int maxVal){
    int val;
    while(true){
        cout << prompt;
        if(cin >> val){
            if(val >= minVal && val <= maxVal) break;
            else cout << "Value must be between " << minVal << " and " << maxVal << "\n";
        } else {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    return val;
}


UserNode*create(int i,string n,bool active){
    UserNode*newNode=new UserNode();
    newNode->id=i;
    newNode->name=n;
    newNode->active=active;
    newNode->borrowList=NULL;
    newNode->PaymentList=NULL;
    newNode->left=NULL;
    newNode->rigth=NULL;
    return newNode;
}
 
UserNode*add(UserNode*root,int i,string n,bool active){
    if(root==NULL){
        return create(i, n , active);
    }
    if(i<root->id){
        root->left=add(root->left,i,n,active);
    }
    else if(i>root->id){
        root->rigth=add(root->rigth,i,n,active);
    }
    else{
        cout<<"duplicate Id "<<endl;
    }
    return root;
}

bool search(UserNode*root,int key){
    if(root==NULL){
        return false;
    }
    if(root->id==key){
        return true;
    }
    if(key<root->id){
       return search(root->left,key);
    }
    else{
       return search(root->rigth,key);
    }
}

UserNode*Deletes(UserNode*root,int key){
    if(root==NULL){
        cout<<"No Id found "<<endl;
        return NULL;
    }
    if(root->id==key){
        if(root->active){
            root->active=false;
        cout<<"id Deactivated "<<endl;
        } else{
        cout<<"user already inactive ";
    }
    return root;
}
    if(key<root->id){
        root->left=Deletes(root->left,key);
    }
    else{
        root->rigth=Deletes(root->rigth,key);
    }
    return root;
}

void inorderDisplay(UserNode*root){
    if(root==NULL){
        return ;
    }
    inorderDisplay(root->left);

    cout<<"ID: "<< root->id<<endl;
    cout<<"Name: "<<root->name<<endl;
    cout<<"Status: "<<root->active<<endl;
    if(root->active){
        cout<<"Active "<<endl;
    }else{
        cout<<"In Active  "<<endl;
    }
    cout<<endl;

    inorderDisplay(root->rigth);
}

UserNode*Update(UserNode*root,int key){
    if(root==NULL){
        cout<<"No Id found "<<endl;
        return NULL;
    }
    if(key==root->id){
        string newname;
       
        cout<<"enter new name ";
        cin.ignore();
        getline(cin,newname);
        root->name=newname;
       char choice;
while(true){
    cout << "Do you want to change status (y/n): ";
    cin >> choice;

    if(choice == 'y' || choice == 'Y'){
        root->active = !root->active;
        break;
    }
    else if(choice == 'n' || choice == 'N'){
        break;
    }
    else{
        cout << "Invalid input! Enter y or n only.\n";
    }
}
        cout<<"User` Updateded "<<endl;
     return root;
    }
    
    if(key<root->id){
        root->left=Update(root->left,key);
    }
    else if(key>root->id){
        root->rigth=Update(root->rigth,key);
    }
    return root;
}

void listUser(UserNode*root){
    if(!root){
        cout<<"No user avaible "<<endl;
    }
    inorderDisplay(root);
}

UserNode*findUser(UserNode*root,int id){
        if(root==NULL){
            return NULL ;
        }
        if(root->id==id){
            return root;
        }
        else if(id<root->id){
            return findUser(root->left,id);
        }
        else{
            return findUser(root->rigth,id);
        }
    }
 


 TranscationNode*createTNode(int t,int bid,int lid,float am,int bdays,int allowD,float per,bool ret){
 TranscationNode*newNod=new TranscationNode();
    newNod->tid=t;
    newNod->borrowerid=bid;
    newNod->lenderid=lid;
    newNod->amount=am;
    newNod->borrowdDays=bdays;
    if(allowD<0){
        cout<<"ALlowed days can not be neg .setting to 0 "<<endl;
        allowD=0;
    }
    newNod->allowedDays=allowD;
    if(per<0){
        cout<<"percentage can not be neg .setting to 0 "<<endl;
        per=0;
    }
    newNod->finePercentage=per;
    newNod->returned=false;
    newNod->next=NULL;
    return newNod;
      
    }
     bool transExit(UserNode*root,int tid){
        if(root ==NULL){
            return false ;
        }
        TranscationNode*t=root->borrowList;
        while(t){
            if(t->tid==tid){
                return true;
            }
              t=t->next;
        }
        return transExit(root->left ,tid) ||  transExit(root->rigth ,tid);

    }


    int ntid=1;

TranscationNode*BorrowFriend(UserNode*Userroot){
    
    int borrowerid;
    int lenderid;
    float amount;
    int allowedDays;
   
    int tid=ntid++;
    cout<<"Transaction id "<<tid<<endl;

    if(tid<0){
        cout<<"Invalid Id "<<endl;
        return NULL;
    }
    if(transExit(Userroot,tid)){
        cout<<"transaction id already exit ";
        return NULL;
    }

    cout<<"enter borrwer id ";
    cin>>borrowerid;

    if(borrowerid<=0 || borrowerid >500){
        cout<<"Invalid ID "<<endl;
        return NULL;
    } 
    cout<<"enter lender id  ";
    cin>>lenderid;

    if(lenderid<=0 || lenderid >500){
        cout<<"Invalid ID "<<endl;
        return NULL;
    } 

    cout<<"enter amount ";
    cin>>amount;
    if(amount<=0){
        cout<<"Amount must postive "<<endl;
        return NULL;
    }

    cout<<"enter allowed days ";
    cin>>allowedDays;


    if(allowedDays<0){
        cout<<"Allowed Days not valid "<<endl;
        return NULL;
    }

    UserNode*borrower=findUser(Userroot,borrowerid);
    UserNode*lender=findUser(Userroot,lenderid);
    if(!borrower){
        cout<<"borrower id not found "<<endl;
        return NULL;
    }
     
     if(!lender){
        cout<<"lender not founded "<<endl;
        return NULL;
     }

    if(!borrower->active || !lender->active){
        cout<<"Can not create Transactions Borrower or lender is inactive "<<endl;
        return NULL;
    }

    if(borrowerid==lenderid){
        cout<<"Can not borrow from yourself "<<endl;
        return NULL;
    }

    int borrowedDays=0;
    float finePercentage=100;  // pr day fine 
   
     TranscationNode*newTranscation=createTNode(tid,borrowerid,lenderid,amount,0,allowedDays,finePercentage,false);
     newTranscation->next=borrower->borrowList;
     borrower->borrowList=newTranscation;

     TranscationNode*LTranscation=createTNode(tid,borrowerid,lenderid,amount,0,allowedDays,finePercentage,false);
     LTranscation->next=lender->PaymentList;
     lender->PaymentList=LTranscation;

     cout<<"Transaction added Succesfully "<<endl;
     return newTranscation;

}


bool returnloanH(UserNode* root,int tid,int returndays,int currentBorrowerID){
    if(returndays<0){
        cout<<"Returned days can not be neg setting to 0 "<<endl;
        returndays=0;
    }

     if(!root){
        return false;
     }
     if(returnloanH(root->left,tid,returndays,currentBorrowerID))
     return true;

    TranscationNode*temp=root->borrowList;
      while(temp){
        if(temp->tid==tid){
             if(temp->borrowerid != currentBorrowerID){
                cout << "You are not the current borrower of this loan\n";
                return true;
            }

            if(temp->returned){
                cout<<"Transaction id " << tid << "already done "<<endl;
                return true;
            }

            int lateEarlyDays = returndays - temp->allowedDays;  
            float fine = 0;
            if(lateEarlyDays > 0) {
                fine = lateEarlyDays * temp->finePercentage;
                cout << "Loan Return Details (Late)"<<endl;
                cout << "Transaction id: " << tid << "Original Amount: " << temp->amount 
                     << "\nLate by: " << lateEarlyDays << " days"
                     << "\nFine: " << fine << "\nTotal Payable: " << temp->amount + fine << endl;
            } else if(lateEarlyDays < 0) {
                cout << "Loan Return Details (Early)\n";
                cout << "Transaction id: " << tid << "\nOriginal Amount: " << temp->amount 
                     << "\nReturned early by: " << -lateEarlyDays << " days"
                     << "\nTotal Payable: " << temp->amount << endl;
            } else {
                cout << "Loan Return Details (On Time)\n";
                cout << "Transaction id: " << tid << "\nOriginal Amount: " << temp->amount 
                     << "\nReturned on time. Total Payable: " << temp->amount << endl;
            }

        temp->borrowdDays=returndays;
        temp->returned=true;

        UserNode*lender=findUser(root,temp->lenderid);
        if(lender){
            TranscationNode*L=lender->PaymentList;
            while(L){
                if(L->tid==tid){
                    L->returned=true;
                    break;
                }
                L=L->next;
            }
        }
        return true;
       
        }
        temp=temp->next;
      }

     return returnloanH(root->rigth,tid,returndays,currentBorrowerID);
    }

void returnloan(UserNode*root, int tid,int returndays){
     int currentBorrowerID;
    cout << "Enter your User ID to return loan: ";
    cin >> currentBorrowerID;

    if(!returnloanH(root,tid,returndays,currentBorrowerID))
    cout<<"Transaction Id not found "<<endl;
}


void displayTransaction(UserNode*root,int id ){
    UserNode* user=findUser(root,id);
    if(user==NULL){
        cout<<"User not found "<<endl;
        return ;
}
 
cout<<"Borrowed Transactions: "<<endl;
TranscationNode*borrow=user->borrowList;
if(!borrow){
    cout<<"NO borrowed Transactions "<<endl;
}

while(borrow){
     float fine = 0;
        int daysDiff = borrow->borrowdDays - borrow->allowedDays;

        if(borrow->returned && daysDiff > 0){
            fine = daysDiff * borrow->finePercentage;
        }

    UserNode* lender = findUser(root, borrow->lenderid);

    cout<<"Transaction Id "<<borrow->tid<<endl;
    if(lender){
        cout<<"Lender: "<<lender->name<<endl;
    }else{
        cout<<"Lender Not: "<<endl;
    }

    cout<<"Amount "<<borrow->amount<<endl;
    cout<<"Allowed Days "<<borrow->allowedDays<<endl;
    cout<<"Total Payable "<<borrow->amount +fine <<endl;

     if(borrow->returned){
        cout<<"Returned Yes "<<endl;
    }
     else {
            cout << "Returned: No\n";
        }


     if(daysDiff > 0) {
        cout << "Returned late by " << daysDiff << " days. Fine: " << fine << endl;
     }

    else if(daysDiff < 0) {
                cout << "Returned early by " << -daysDiff << " days.\n";
            }
    else{ cout << "Returned on time.\n";
            }


        cout << "Total Payable: " << borrow->amount + fine << endl;

    borrow=borrow->next;
}


cout<<"Payments Received: "<<endl;

TranscationNode*payment=user->PaymentList;

if(!payment){
    cout<<"NO payment Transactions "<<endl;
}
while(payment){
    UserNode*borrower=findUser(root,payment->borrowerid);

     float fine = 0;

        int daysDiff = payment->borrowdDays - payment->allowedDays;
        if(payment->returned && daysDiff > 0){
            fine = daysDiff * payment->finePercentage;
        }


    cout<<"Transaction Id "<<payment->tid<<endl;

    if(borrower){
        cout<<"Borrower: "<<borrower->name<<endl;
    }else{
        cout<<"Borrower Not "<<endl;
    }

    cout<<"Amount "<<payment->amount<<endl;
     if(daysDiff > 0) {
                cout << "Returned late by " << daysDiff << " days. Fine: " << fine << endl;
            }
            else if(daysDiff < 0) {
                cout << "Returned early by " << -daysDiff << " days.\n";
            }
            else{
                cout << "Returned on time.\n";
            }
    cout << "Total Payable: " << payment->amount + fine << endl;

    payment=payment->next;
}
}



bool loanTransfer(UserNode*root,int tid,int newBorrowerid){

    if(newBorrowerid<0 || newBorrowerid>500){
        cout<<"Invalid number "<<endl;
        return false ;
    }
    if(!root){
        return false  ;
    }
 if (loanTransfer(root->left,tid,newBorrowerid)){
    return true;
 }
        
    TranscationNode*curr=root->borrowList;
    
    while(curr){

    if(curr->tid==tid){
         UserNode*newBorrower=findUser(root,newBorrowerid);
         if(!newBorrower || !newBorrower->active){
            cout<<"New bowwer Invalid or In active "<<endl;
            return true ;
         }

        if(curr->returned){
            cout<<"Transaction Already Done "<<endl;
            return true ;
        }

        if(curr->borrowerid==newBorrowerid){
            cout<<"Can not transfer to same borrower "<<endl;
            return true  ;
        }
        if(curr->lenderid==newBorrowerid){
            cout<<"Can not transfer to lender "<<endl;
            return true ;
        }

        int oldBorrowerid=curr->borrowerid;
        UserNode*oldBorrowerNode=findUser(root,oldBorrowerid);

        curr->borrowerid=newBorrowerid;
        
        UserNode* lender = findUser(root, curr->lenderid);
            if (lender) {
                TranscationNode* t = lender->PaymentList;
                while (t) {
                    if (t->tid == tid) {
                        t->borrowerid = newBorrowerid;
                        break;
                    }
                    t = t->next;
                }
            }

            if (oldBorrowerNode) {
                TranscationNode* temp = oldBorrowerNode->borrowList;
                TranscationNode* prev = NULL;
                while (temp) {
                    if (temp->tid == tid) {
                        if (prev) prev->next = temp->next;
                        else oldBorrowerNode->borrowList = temp->next;
                        break;
                    }
                    prev = temp;
                    temp = temp->next;
                }
            }
           
            curr->next = newBorrower->borrowList;
            newBorrower->borrowList = curr;

if (!oldBorrowerNode) {
    cout << "Old borrower not found"<<endl;
    return true;
}

cout<<"Loan Transfer SucessFully from id "<<oldBorrowerNode->id<<" to  id"<< newBorrower->id <<endl;
       return true;
    }
    curr=curr->next;
}

  return  loanTransfer(root->rigth,tid,newBorrowerid);
}



void checkAccount(UserNode*root,int id){
if (id <0 || id>500){
    cout<<"Invalid "<<endl;
    return;
}
    UserNode*user=findUser(root,id);
    if(!user){
        cout<<"User not found "<<endl;
    }


    float totalBorrowed=0;
    float totallent=0;
    float totalfine=0;


TranscationNode*t=user->borrowList;

while(t){
    totalBorrowed+=t->amount;
    if(t->returned && t->allowedDays<t->borrowdDays){
        int late=t->borrowdDays - t->allowedDays;
        totalfine +=late*t->finePercentage;
    }
    t=t->next;
}
t=user->PaymentList;
while(t){
    totallent+= t->amount;
    t=t->next;
}

    cout<<"Account Summary "<<user->name<<endl;
    cout<<"Total Borrowd: "<<totalBorrowed <<endl;
    cout<<"Total lent: "<<totallent <<endl;
    cout<<"Total fine: "<<totalfine<<endl;
    cout<<"Total Payable: "<<totalBorrowed + totalfine <<endl;
    cout << "User Status: ";
if(user->active)
    cout << "Active" << endl;
else
    cout << "Inactive" << endl;
   
    
}



void checkTransactionsBtwUser(UserNode*root,int id1,int id2){

    if(id1 <0 || id1>500 ||id2<0 ||id2>500){
        cout<<"Invalid "<<endl;
        return;
    }
    UserNode*user1=findUser(root,id1);
    UserNode*user2=findUser(root,id2);

  if(!user1 ||!user2){
    cout<<"one or both not found "<<endl;
    return ;
  }

  float total1to2=0;
  float total2to1=0;
  bool found1to2 = false;
  bool found2to1 = false;
  

  TranscationNode* t=user1->borrowList;
  while(t){
    if(t->lenderid==id2){
        if(!found1to2){
        cout<<"transaction where user: " <<id1<< "bororwed from:" <<id2 <<endl;
        
        found1to2=true;
        }

    cout<<"Transaction id "<<t->tid<<endl;
    cout<<"Amount "<<t->amount<<endl;

  if (t->returned) {
                int diff = t->borrowdDays - t->allowedDays;
                if (diff > 0) cout << ", Returned late by " << diff << " days, Fine: " << diff * t->finePercentage;
                else if (diff < 0) cout << ", Returned early by " << -diff << " days";
                else cout << ", Returned on time";
            } else {
                cout << ", Not yet returned";
            }

            cout << endl;

            float fine = 0;
            if (t->returned && t->borrowdDays > t->allowedDays)
                fine = (t->borrowdDays - t->allowedDays) * t->finePercentage;

            total1to2 += t->amount + fine;
        }
        t = t->next;
    }

   t=user2->borrowList;
  while(t){
    if(t->lenderid==id1){
        if(!found2to1){
        cout<<"transaction where user: "<<  id2 << " bororwed from:" << id1 <<endl;
         found2to1=true;
        }
        
    cout<<"Transaction id "<<t->tid<<endl;
    cout<<"Amount "<<t->amount<<endl;
   
    if (t->returned) {
                int diff = t->borrowdDays - t->allowedDays;
                if (diff > 0) cout << ", Returned late by " << diff << " days, Fine: " << diff * t->finePercentage;
                else if (diff < 0) cout << ", Returned early by " << -diff << " days";
                else cout << ", Returned on time";
            } else {
                cout << ", Not yet returned";
            }

            cout << endl;

            float fine = 0;
            if (t->returned && t->borrowdDays > t->allowedDays)
                fine = (t->borrowdDays - t->allowedDays) * t->finePercentage;

            total2to1 += t->amount + fine;
        }
        t = t->next;
    }

if (!found1to2 && !found2to1) {
        cout << "\nNo transactions found between these users"<<endl;
        return;
    }

cout<<"Summary between users "<<endl;
 if (total1to2 > 0) cout << "User " << id1 << " owes User " << id2 << ": " << total1to2 << endl;
 if (total2to1 > 0) cout << "User " << id2 << " owes User " << id1 << ": " << total2to1 << endl;
}
  
void systemsummaryH(UserNode*root,int &totaluser,int &activeUsers,int &inactiveUsers,int &totalTranssactions,float &totalBorrowed,float &totalRecived,float &totalOut){
    if(root==NULL){
        return;
    }
   
    systemsummaryH(root->left,totaluser,activeUsers,inactiveUsers,totalTranssactions,totalBorrowed,totalRecived,totalOut);

    totaluser++;
    if(root->active){
        activeUsers++;
    }else{
        inactiveUsers++;
    }

    TranscationNode*t=root->borrowList;
    while(t){
        totalTranssactions++;
        totalBorrowed+=t->amount;
        float fine =0;
        if(t->returned && t->borrowdDays > t->allowedDays){
        int latedays = t->borrowdDays - t->allowedDays;
        fine = latedays * t->finePercentage;
    }

        if(t->returned){
            totalRecived+=t->amount + fine ;
        }
        else{
            totalOut+=t->amount +fine ;
        }
        t=t->next;
    }
    systemsummaryH(root->rigth,totaluser,activeUsers,inactiveUsers,totalTranssactions,totalBorrowed,totalRecived,totalOut);
}

void Summary(UserNode* root){
     int totaluser=0,activeUsers=0 ,inactiveUsers=0,totalTranssactions=0 ;
    float totalBorrowed=0 ,totalRecived=0,totalOut=0 ;

    systemsummaryH(root,totaluser,activeUsers,inactiveUsers,totalTranssactions,totalBorrowed,totalRecived,totalOut);
    
    cout<<"Summary System "<<endl;
    cout<<"Total users "<<totaluser <<endl;
    cout<<"Active Users "<<activeUsers <<endl;
    cout<<"In active Users "<<inactiveUsers<<endl;
    cout<<"Total Transactions "<<totalTranssactions<<endl;
    cout<<"Total borrowed "<<totalBorrowed<<endl;
    cout<<"Total Recived "<<totalRecived<<endl;
    cout<<"Total out "<<totalOut<<endl;
}


#include <cctype>

// Forward declarations of your functions
bool isValidName(const string& name){
    for(char c: name){
        if(!isalpha(c) && c != ' ') return false; // allow spaces in names
    }
    return !name.empty();
}


int main() {
    UserNode* root = NULL;
    int choice;

    do {
        cout << "\n=== Loan Management System ===\n";
        cout << "1. Add User\n"
             << "2. Update User\n"
             << "3. Delete User\n"
             << "4. Borrow Loan\n"
             << "5. Return Loan\n"
             << "6. Loan Transfer\n"
             << "7. Display Transactions\n"
             << "8. Check Account\n"
             << "9. Check Transactions Between Users\n"
             << "10. System Summary\n"
             << "11. List All Users\n"
            << "0. Exit\nChoice: ";
        choice = safeInt("Enter choice: ", 0, 11); // safe input for menu choice

        switch(choice) {
            case 1: {
                int id = safeInt("Enter User ID (1-500): ", 1, 500);
                cin.ignore(); // newline
                string name;
                do {
                    cout << "Enter Name (A-Z only): ";
                    getline(cin, name);
                    if(!isValidName(name)) cout << "Invalid name. Only letters allowed.\n";
                } while(!isValidName(name));

               char status;
bool active;

while (true) {
    cout << "Is Active? (y/n): ";
    cin >> status;

    if (status == 'y' || status == 'Y') {
        active = true;
        break;
    }
    else if (status == 'n' || status == 'N') {
        active = false;
        break;
    }
    else {
        cout << "Invalid input! Please enter only y or n.\n";
    }
}
                root = add(root, id, name, active);
                break;
            }

            case 2: {
                int id = safeInt("Enter User ID to update: ", 1, 500);
                root = Update(root, id);
                break;
            }
            case 3: {
                int id = safeInt("Enter User ID to deactivate: ", 1, 500);
                root = Deletes(root, id);
                break;
            }
            case 4:
                BorrowFriend(root);
                break;
            case 5: {
                int tid = safeInt("Enter Transaction ID: ", 1, 10000);
                int days = safeInt("Enter Returned Days: ", 0, 10000);
                returnloan(root, tid, days);
                break;
            }
            case 6: {
                int tid = safeInt("Enter Transaction ID: ", 1, 10000);
                int newBorrower = safeInt("Enter New Borrower ID: ", 1, 500);
                loanTransfer(root, tid, newBorrower);
                break;
            }
            case 7: {
                int id = safeInt("Enter User ID to display transactions: ", 1, 500);
                displayTransaction(root, id);
                break;
            }
            case 8: {
                int id = safeInt("Enter User ID to check account: ", 1, 500);
                checkAccount(root, id);
                break;
            }
            case 9: {
                int id1 = safeInt("Enter First User ID: ", 1, 500);
                int id2 = safeInt("Enter Second User ID: ", 1, 500);
                checkTransactionsBtwUser(root, id1, id2);
                break;
            }
            case 10:
                Summary(root);
                break;
            case 11:
                listUser(root);
                 break;
            case 0:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }

    } while(choice != 0);

    return 0;
}
