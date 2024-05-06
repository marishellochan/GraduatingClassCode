#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;

int main(){

    ifstream studentfile;
    ofstream studentCSfile;
    ifstream CSfile;
    ofstream Summaryfile;

    string ID;
    string f_name, l_name, degree;
    string award_f_name, award_l_name;
    int year;
    int level_one_c, level_two_c, level_three_c;
    int level_two_three_c=0;
    int more_l_one_c=0, more_l_two_three_c=0, more_f_points=0;
    int f_credits;
    int q_points;
    int not_needed, count;
    float gpa=0;
    float award_gpa=0;
    float max=INT_MIN;
    int sum_CS_Students=0, sum_graduate_CS_Students=0, sum_First_Class=0;


    studentfile.open("Students.txt");
    studentCSfile.open("Students-CS.txt");

    if(studentfile.is_open()==false)
    {
        cout << "Error in Student file. Aborting ....";
        exit(1);
    }

    if(studentCSfile.is_open()==false)
    {
        cout << "Error in Student Computer Science file. Aborting ....";
        exit(1);

    }

    studentfile >> ID;

    while(ID!="END")
    {
        studentfile >> f_name;
        studentfile >> l_name;
        studentfile >> degree;

        if ( degree=="BSc_Computer_Science" || degree=="BSc_Computer_Science_Special")
        {
            studentCSfile << ID << "\t";
            studentCSfile << f_name << "\t";
            studentCSfile << l_name<< "\t";
            studentCSfile << degree << "\t";

            studentfile >> year;

            studentfile >> level_one_c;
            studentCSfile << level_one_c << "\t";

            studentfile >> level_two_c;
            studentCSfile << level_two_c << "\t";

            studentfile >> level_three_c;
            studentCSfile << level_three_c << "\t";

            studentfile >> f_credits;
            studentCSfile << f_credits << "\t";

            studentfile >> q_points;
            studentCSfile << q_points << "\t";

            sum_CS_Students=sum_CS_Students+1;

            studentCSfile << endl;

        }

        else
        {
            for (count=1; count <=6; count++)
            {
                studentfile >> not_needed;
            }
        }

        studentfile >> ID;

    }

    studentCSfile << "END";

    studentfile.close();
    studentCSfile.close();

    CSfile.open("Students-CS.txt");
    Summaryfile.open("Students-CS-Summary.txt");


    if(CSfile.is_open()==false)
    {
        cout << "Error in Student Computer Science file. Aborting ....";
        exit(1);

    }

    if(Summaryfile.is_open()==false)
    {
        cout << "Error in Summary Student Computer Science file. Aborting ....";
        exit(1);

    }

    CSfile >> ID;



    while(ID!="END")
    {
        Summaryfile << "******************************************************************"<< endl;

        CSfile >> f_name;
        CSfile >> l_name;
        CSfile >> degree;
        CSfile >> level_one_c;
        CSfile >> level_two_c;
        CSfile >> level_three_c;
        CSfile >> f_credits;
        CSfile >> q_points;

        Summaryfile << fixed << setprecision(2);
        gpa= q_points/((level_two_c+level_three_c)*1.0);

        Summaryfile << "Student ID:       \t"<< ID<< endl;
        Summaryfile << "Student Name:     \t"<< l_name << ", "<< f_name<< endl;
        Summaryfile << "Degree Programme: \t"<< degree << endl;
        Summaryfile << "Degree GPA:       \t"<< gpa << endl;


        level_two_three_c =level_two_c+level_three_c;

        if( level_one_c <24 || level_two_three_c<60|| f_credits<9)
        {
            Summaryfile << "Can Gaduate:       \t No. Needs: ";

            if (f_credits<9)
            {
                more_f_points=9-f_credits;
                Summaryfile << more_f_points << " Foundation credits. ";
            }
            if(level_one_c<24)
            {
                more_l_one_c=24-level_one_c;

                Summaryfile << more_l_one_c << " Level 1 credits. ";
            }
            if(level_two_three_c<60)
            {
                more_l_two_three_c=60-level_two_three_c;
                Summaryfile << more_l_two_three_c << " Level 2/3 credits. ";
            }


            Summaryfile<< endl;
        }
        else
        {

            if (gpa<2.0)
            {
                Summaryfile << "Can Gaduate:       \t No. Meets requirements but GPA is less than 2.0";
            }
            else
            {
                if (gpa>=2.0 && gpa<=2.49)
                {
                    Summaryfile <<"Can Graduate:       Yes, Pass.";
                }
                else if (gpa>=2.50 && gpa<=2.99)
                {
                    Summaryfile <<"Can Graduate:       Yes, with Lower Second Class Honors.";
                }
                else if (gpa>=3.00 && gpa<=3.59)
                {
                    Summaryfile <<"Can Graduate:       Yes, with Upper Second Class Honors.";
                }
                else if(gpa>=3.60)
                {
                    Summaryfile <<"Can Graduate:       Yes, with First Class Honors.";
                    sum_First_Class=sum_First_Class+1;
                }
                sum_graduate_CS_Students=sum_graduate_CS_Students+1;

                if(gpa > max)
                {
                    max=gpa;
                    award_gpa=gpa;
                    award_f_name=f_name;
                    award_l_name=l_name;
                }
            }

            Summaryfile << endl;

        }



        Summaryfile << "------------------------------------------------------------------"<< endl;

        CSfile >> ID;

    }


    Summaryfile << endl;
    Summaryfile << "Number of Students Processed:                           \t" << sum_CS_Students << endl;
    Summaryfile << "Number of graduating students:                          \t" << sum_graduate_CS_Students << endl;
    Summaryfile << "Number of students graduating with First Class Honours: \t" << sum_First_Class << endl << endl;

    Summaryfile << "Student who gets the Turing Award for Excellence in Computer Science:" << endl;
    Summaryfile << "First Name: \t" << award_f_name << endl;
    Summaryfile << "Last Name:  \t" << award_l_name << endl;
    Summaryfile << "GPA:        \t" << award_gpa << endl;

    CSfile.close();
    Summaryfile.close();

    return 0;

}
