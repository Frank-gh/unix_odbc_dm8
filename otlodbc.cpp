#include <iostream>
using namespace std;
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include <stdio.h>


#define OTL_ODBC // CompileOTL 4.0/ODBC  
#define OTL_ODBC_UNIX // uncomment this line if UnixODBC is used
//#define OTL_UNICODE // Compile OTL with Unicode    --->屏蔽 使用时中文显示乱码

#include "otlv4.h" // include the OTL 4.0 header file

otl_connect db; // connect object

void insert()
{
    try
    {
        // VALUES(:id<int>, :name<char[21]>, :age<int>, :address<char[26]>, :salary<float>);",
        otl_nocommit_stream o;
        o.open(50, // buffer size
            "insert into SYSDBA.COMPANY(ID, NAME, AGE, ADDRESS, SALARY) \
            VALUES(:id<int>, :name<char[21]>, :age<int>, :address<char[26]>, :salary<float>);",
            // SQL statement
            db // connect object
        );
        
        o.set_flush(false);
        o.set_commit(1);
// #if defined(OTL_ANSI_CPP_11_VARIADIC_TEMPLATES)
//         otl_write_row(o,100,"夏铭序",39,"东方圣克拉",static_cast<float>(10000));
// #else
//         // when variadic template functions are not supported by the C++
//         // compiler, OTL provides nonvariadic versions of the same template
//         // functions in the range of [1..15] parameters
//         otl_write_row(o,100,"夏铭序",39,"东方圣克拉",static_cast<float>(10000));

//         // the old way (operators >>() / <<()) is available as always:
//         // o<<static_cast<float>(i)<<tmp;
// #end
        char name[50] = {"夏铭序11111111111111111111"}; 
        name[20] = '\0';
        o << 100 << name << 31 << "东方圣克拉" << static_cast<float>(10000);
        o << 101 << name << 32 << "东方圣克拉" << static_cast<float>(10000);

        o.flush();
        // db.commit();
    }
    catch(otl_exception& p)
    {
        cout<<"otl_exception:"<<endl;
        cerr<<p.msg<<endl; // print out error message
        cerr<<p.stm_text<<endl; // print out SQL that caused the error
        cerr<<p.var_info<<endl; // print out the variable that caused the error
    }

}  

void select()
{ 
    try{
        otl_stream ostream1(500, // buffer size
            "select * from company;",// SELECT statement
            db // connect object
            ); 
        // create select stream

        int id;
        int age;
        unsigned char name[255];
        unsigned char address[255];
        double salary;

        while(!ostream1.eof())
        { // while not end-of-data
            ostream1>>id;
            ostream1>>name;
            ostream1>>age;
            ostream1>>address;
            ostream1>>salary;
            cout<<"id="<<id<<endl;
            cout<<"age="<<age<<endl;
            cout<<"name="<<name<<endl;
            cout<<"address="<<address<<endl;
        }
    }
    catch(otl_exception& p)
    { // intercept OTL exceptions
        cout<<"otl_exception:"<<endl;
        cerr<<p.msg<<endl; // print out error message
        cerr<<p.stm_text<<endl; // print out SQL that caused the error
        cerr<<p.var_info<<endl; // print out the variable that caused the error
    }
}

int main()
{
    otl_connect::otl_initialize(); // initialize the database API environment
    try{
        db.auto_commit_off();
        db.rlogon("DSN=dm;UID=SYSDBA;PWD=xk.xmx190035;database=gchdb"); // connect to the database
        insert();
        select(); // select records from table
    }

    catch(otl_exception& p){ // intercept OTL exceptions
        cerr<<p.msg<<endl; // print out error message
        cerr<<p.stm_text<<endl; // print out SQL that caused the error
        cerr<<p.var_info<<endl; // print out the variable that caused the error
    }

    db.logoff(); // disconnect from the database

    return 0;

}