//
//  main.cpp
//  Oweek
//
//  originally created by Tyler Buchman on 7/19/13 - Copyright (c) 2013 Tyler Buchman.
//  modified and adapted by Tom Wiesing - licensed under MIT license

/*
  Copyright (c) 2013-15 Tyler Buchman & Tom Wiesing

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <iostream>
#include <fstream>
using namespace std;

/**
 * A single student.
 */
struct Student
{
    string name; /** the students (last, first) name */
    string nationality; /** the students nationality */
    string major; /** the students major */
    int num; /** the number of the student */
};

/**
 * a list of students in a group
 */
struct NodeStudent
{
    struct Student s/** the actual student */;
    struct NodeStudent *next /** the next student */;
};

int main(int argc, const char * argv[])
{

    // CONFIG
    const int numStudents = 218; // the number of students
    const int numGroups = 24; // the number of groups
    // /CONFIG

    Student list[numStudents]; // we want to read the students in this list.


    struct NodeStudent n;
    struct NodeStudent *m;
    struct Student s;

    int i = 0, j;

    string temp;

    // open the input file.
    ifstream input;
    input.open("students.txt");
    if(input.is_open())
        cout << "opening student information file: success";
    else
        cout << "opening student information file: fail";
    cout << endl;

    // read in the student first names, line by line.
    while(i < numStudents && input.good())
    {
        getline(input, s.name);
        list[i++] = s;
    }

    // have a line of nothing.
    getline(input, temp);
    i = 0;

    // read in the last names, line by line.
    while(i < numStudents && input.good())
    {
        getline(input, temp);
        list[i].name = temp + ", " + list[i].name;
        list[i].num = i;
        i++;
    }

    // have a line of nothing.
    getline(input, temp);
    i = 0;

    // read in the nationailities, line by line.
    while(i < numStudents && input.good())
    {
        getline(input, list[i++].nationality);
    }

    getline(input, temp);
    i = 0;
    while(i < numStudents && input.good())
    {
        getline(input, list[i++].major);
    }

    input.close();

    struct NodeStudent groups[numGroups];
    for(i = 0; i < numGroups; i++)
    {
        struct NodeStudent st;
        st.next = nullptr;
        st.s = list[i];
        groups[i] = st;
    }
    int indexOfBest = 0;
    long score, bestScore = 0;

    for(i = numGroups; i < numStudents; i++) { // for each student
        s = list[i];
        indexOfBest = 0;
        bestScore = 1000000000;
        bool keepGoing = true;
        for(j = 0; j < numGroups; j++)
        {
            score = 0;
            n = groups[j];
            do
            {
//                cout << n.s.name << " || " << s.name << endl;////////////////////////////////
                if(n.s.nationality == s.nationality)
                    score += 10000;
                if(n.s.major == s.major)
                {
                    score += 100;
                    if(score % 10000 > 300) score += 1000000;
                }
                score += 1;
                if(score % 100 > (numStudents-1)/numGroups + 1) score += 10000000;
                if(n.next != nullptr)
                {
                    n = *n.next;
                    keepGoing = true;
                }
                else
                    keepGoing = false;
            }while (keepGoing);
            if(score < bestScore)
            {
                indexOfBest = j;
                bestScore = score;
            }
        }

        m = &groups[indexOfBest];
        cout << bestScore << endl;
        while(m->next != nullptr)
        {
            m = m->next;
        }
        struct NodeStudent *temp = new struct NodeStudent;
        temp->s = list[i];
        temp->next = nullptr;
        m->next = temp;
    }

    ofstream output("groups", ios::out | ios::binary);
    if(output.is_open())
        cout << "opening output file: success" << endl;
    else
        cout << "opening output file: fail" << endl;
    bool keepGoing = true;
    for(i = 0; i < numGroups; i++)
    {
        n = groups[i];
        output << "group " << i+1 << "\n";
        do {
            output << n.s.name << "\n";
            if(n.next != nullptr)
            {
                n = *n.next;
                keepGoing = true;
            }
            else keepGoing = false;
        }while (keepGoing);
        output << "\n";
    }
    output.close();

}
