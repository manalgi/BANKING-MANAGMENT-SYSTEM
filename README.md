# BANKING-MANAGMENT-SYSTEM
simple version of banking system


--- used the read/write file code (advantage, saves memory) which means for each update had to creat a temp file
    in order to copy all necessary data with the updated one.
    
--- 90% completed, need some more changes as:
  1)varify user input is according to the format
  2)cusmoter account actually exist 
  3)testing
  
--- the system has 5 options :
  0)the main
        -the user has 6 option to choose, where the last one is to exit the program if not it will keep running in a loop. 
  1)adding new account: 
        -automaticlly will creat new file with the name "DB.txt" unless it is already exist.
        -call the function check() where it will check what is the last Customer ID that has been created and will increase 
        by 1 in order to keep the IDs orginized and unique
        -call the function new_acc() where the user input his data and then the data will be written into the DB.txt  file
  2)updating it
        -call the function edit() where the user has two choice of update; his address or his phone number.
        -the function will create new file "DBtemp.txt" and copy the data from DB.txt except the new edited one.
        -DB.txt will get deleted and DBtemp.txt will become the new updated file by rename it to DB.txt
  3)removing it
        -call the function earse() , the user will enter the ID number of the wanted customer
        -the function will create new file "DBtemp.txt" and copy the data from DB.txt except the one that need to be deleted.
        -DB.txt will get deleted and DBtemp.txt will become the new updated file by rename it to DB.txt
  4)transaction from one account to other |deposit |withdraw
        -call the function transact() , the user will have 3 option of transaction:
            -deposite money; 
            -withdraw money
            -send money to another account 
        -the function will create new file "DBtemp.txt" and copy the data from DB.txt and will calculate the new amount of money
        in the wanted account accordingly (adding|reduching). and if the user chose optiong 3 (send money) and the account exist 
        in the system DB then it will also be calculated and updated.
        -DB.txt will get deleted and DBtemp.txt will become the new updated file by rename it to DB.txt
  5)showing list of all customers
        -call the function view_list() and will read and output all the accounts data that exist in the file DB.txt
        
        
 for compilation:
    -open terminal and change the directory/folder to where the source code is
    -compile: g++ main.cpp -o main.exe
    -run the executable: main.exe
    
