#include "needed_classes.h"
#include <iostream>
#include <iomanip> 
#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include<stack>
#include <set>
#include <unordered_map>
#include<windows.h>
using namespace std;
#define M_PI 3.14159265358979323846
admin::admin(University* uni_ptr) {
	uni = uni_ptr;
	Name = "admin";
	Password = "password";
	fit(uni->get_stud(),uni->size_stude);
	unordered_map<int, student>::iterator it = uni->get_stud()->begin();
	for (it; it != uni->get_stud()->end(); it++)
	{
		it->second.warning = predict_(it->second.get_GPA(),it->second.get_year());
	}
}
void admin::view_students_in_specific_course(unordered_map<int, student>* Students, unordered_map<string, course>* Courses) {
	system("cls");
	string code;
	int i = 0;
	for (unordered_map<string, course>::iterator it = Courses->begin(); it != Courses->end(); it++) {
		cout << i + 1 << " . " << it->second.get_name() << " ( " << it->second.get_code() << " )\n";
		i++;
	}
	cout << "Write the course code please : ";
	cin >> code;
	system("cls");
	for (unordered_map<int, student> ::iterator it = Students->begin(); it != Students->end(); it++)
	{
		for (int x = 0; x < it->second.get_course_in_progress()->size(); x++) {

			if (code == it->second.get_course_in_progress()->at(x)) {
				cout << "Name " << it->second.get_name() << endl;
			}
		}
	}
	char x;
	cout << "press any thing to exit\n";
	cin >> x;
}
void admin::editCourse(unordered_map<string, course>* courses, unordered_map<int, student>* stud)
{
	system("cls");
	string courseCode;
	for (unordered_map<string, course> ::iterator it = courses->begin(); it != courses->end(); it++)
	{
		cout << "|-> " << it->second.get_name() << " | code : " << it->second.get_code() << " | Hours : " << it->second.get_hours() << endl;
	}
	cout << "Enter code of course you want to edit : ";
	cin >> courseCode;
	if ((*courses).find(courseCode) != (*courses).end())
	{
		uni->addCourse(true,courseCode);
		cout << "Edit done successfully!!\n";
		Sleep(2000);
		return;
	}
	else
	{
		cout << "We can not find this course you can add new course or return to home..\nPress any thing to back to home : ";
		char x;
		cin >> x;
	}
	Sleep(4000);
}
void admin::add_Course_Grade_for_each_Student(unordered_map<int, student>* stud, unordered_map<string, course>* courses)
{
begin:
	system("cls");
	cout << "Enter Student ID : ";
	int id;
	cin >> id;
	char choice;
	vector<string>* courses_in_progress = (*stud)[id].get_course_in_progress();
	unordered_map<string, float>* finishedCourse = (*stud)[id].get_Finished_courses();
	if ((*stud)[id].get_course_in_progress()->empty())
		cout << "This student does't have an courses in progress \n\n ";
	else {
		float sum = 0;
		int size = (courses_in_progress)->size();
		for (int i = 0; i < size; i++)
		{
			string random_num;
			string code = (*stud)[id].get_course_in_progress()->at(i);
			cout << "enter grade for the student  f/F/0 if fail " << courses->find(code)->second.get_name() << " grade : ";
			cin >> random_num;
			cout << "you just have inserted the gpa " << random_num << " to the course ( " << courses->find(code)->second.get_name() << " ) \n ";
			if (random_num=="f"||random_num=="F" || stof(random_num)<1.0)
			{
				sum += 0.0;
				courses->find(code)->second.fail_num += 1;
				(*stud)[id].set_hours((*stud)[id].get_Maximum_hours_allowed() + courses->find(code)->second.get_hours());
			}
			else
			{
				sum += stof(random_num);
				(*stud)[id].hours_taken += courses->find(code)->second.get_hours();
				(*stud)[id].set_hours((*stud)[id].get_Maximum_hours_allowed() + courses->find(code)->second.get_hours());
				finishedCourse->insert(make_pair(code, stof(random_num)));
				courses->find(code)->second.pass_num += 1;
			}
		}
		if ((*stud)[id].hours_taken / 36 > 0.700000001)
		{
			(*stud)[id].year += 1;
			(*stud)[id].hours_taken = 0;
		}
		(*courses_in_progress).clear();
		if (size != 0)
		{
			sum /= size;
			if ((*stud)[id].get_GPA()==0. && (*stud)[id].get_year()==1)
			{
				(*stud)[id].set_GPA( sum );
			}
			else
			{
				(*stud)[id].set_GPA(((*stud)[id].get_GPA() + sum) / 2);
				(*stud)[id].warning = predict_((*stud)[id].get_GPA(), (*stud)[id].get_year());
			}
		}
	}
	cout << "Courses grades added successfully. \n ";
	Sleep(2000);
	cout << "Do you want to add another student ? y/n ";
	cin >> choice;
	if (choice == 'y' || choice == 'Y')
		goto begin;
}
void admin::addStudent(unordered_map<int, student>* data, unordered_map<string, course>* Courses)
{
	system("cls");
	string name, email, password;
	int id = data->size() + 1;
	int maxHours = 21;
	int year;
	float GPA;
	cout << "Enter student name: ";
	cin >> name;
	cout << "Enter academic year: ";
	cin >> year;
	password = to_string(id) + "p";
	email = to_string(id) + "@gmail.com";
	if (year != 1)
	{
gpa:
		cout << "Enter GPA: ";
		cin >> GPA;
		if (GPA > 4)
		{
			cout << "please enter valid GPA 4~0\n";
			Sleep(2000);
			goto gpa;
		}
	}
	else
		GPA = 0.0;
	unordered_map<string, float>* finished_c = new unordered_map<string, float>();
	if (year > 1)
	{
	begin:
		system("cls");
		unordered_map<string, course>::iterator it = Courses->begin();
		for (it; it != Courses->end(); it++)
		{
			cout << "Course Name : " << it->second.get_name() << " Code : " << it->second.get_code() << endl;
		}
		cout << "\n \n Enter courses code that student finished and his grades.\nPress q for exit and keep it\n";
		string code, grade;
		cin >> code;
		if (code == "q" || code == "Q")
		{
			goto skip;
		}
		if (Courses->find(code) == Courses->end())
		{
			cout << "Please enter valid code\n";
			Sleep(2000);
			goto begin;
		}
		cin >> grade;
		if (grade == "Q" || grade == "q")
		{
			goto skip;
		}
		else
		{	
			finished_c->insert(make_pair(code, stof(grade)));
		}
		goto begin;
	}
skip:
	vector<string>* values = new vector<string>{ to_string(id),name, email, password, to_string(maxHours), to_string(year),to_string(GPA)};
	student newStudent(values, finished_c);
	(*data)[id] = newStudent;
	cout << "New student added successfully." << endl;
	cout << "Name : " << name << " |  ID : " << id << " | password : " << password << endl;
	Sleep(6000);
}
void admin::List_of_all_courses_of_a_specific_student(unordered_map<int, student>* Students, unordered_map<string, course>* Courses) {
begin:
	system("cls");
	int id;
	cout << "enter id of specific student to see his/her progressed & finished courses" << endl;
	cin >> id;
	if ((*Students).find(id) != Students->end()) {
		cout << "courses in progress are : " << endl;
		for (int j = 0; j < (*Students)[id].get_course_in_progress()->size(); j++)
		{
			cout << (*Courses)[(*Students)[id].get_course_in_progress()->at(j)].get_name() << endl;
		}
		cout << "finished cousrses are : " << endl;
		for (unordered_map<string, float>::iterator it = (*Students)[id].get_Finished_courses()->begin();
			it != (*Students)[id].get_Finished_courses()->end();
			it++)
		{
			cout << (*Courses)[it->first].get_name() << " His grade : " << it->second << endl;
		}
	}
	else
	{
		cout << "Student not found \n";
		Sleep(2000);
		goto begin;
	}
	char x;
	cout << "press any thing to exit\n";
	cin >> x;
}
void admin::login(string info[]) {
	if (info[0] == Name && info[1] == Password) {
begin:
		while (true)
		{
			system("cls");
			cout << ">> Hello Admin <<\n";
			string answer;
			cout << "--> press 1 for Add new Course\n";
			cout << "--> press 2 for Enter Course Prerequisite.\n";
			cout << "--> press 3 for View List of all students in a Specific Course\n";
			cout << "--> press 4 for Add Course grade for each student\n";
			cout << "--> press 5 for View List of all courses (Finished - Progressed) of a specific student.\n";
			cout << "--> press 6 for Edit all Course data\n";
			cout << "--> press 7 for Add new students\n";
			cout << "--> press 0 for Exit\n";
			cin >> answer;
			try
			{
				stoi(answer);
			}
			catch (const std::exception&)
			{
				cout << "Enter valid input\n";
				Sleep(2000);
				goto begin;
			}
			if (stoi(answer) == 0)
			{
				return;
			}
			choose_fun(stoi(answer));
		}
	}
}
void admin::choose_fun(int ans) {
	if (ans > 7 || ans < 1) {
		cout << "please enter valid number\n";
		cin >> ans;
		if (ans == 0)
		{
			return;
		}
		choose_fun(ans);
		return;
	}
	switch (ans)
	{
	case 1:
		uni->addCourse(false,"");
		break;
	case 2:
		uni->coursePreRequisite(NULL, 1);
		break;
	case 3:
		view_students_in_specific_course(uni->get_stud(), uni->get_Courses());
		break;
	case 4:
		add_Course_Grade_for_each_Student(uni->get_stud(), uni->get_Courses());
		break;
	case 5:
		List_of_all_courses_of_a_specific_student(uni->get_stud(), uni->get_Courses());
		break;
	case 6:
		editCourse(uni->get_Courses(), uni->get_stud());
		break;
	case 7:
		addStudent(uni->get_stud(), uni->get_Courses());
		break;
	}
}
admin::~admin() {

}
//---------------------------------------------------------//
student::student(vector<string>* values, unordered_map<string, float>* finishedCourse) {
	Courses_in_progress = new vector<string>();
	Id = stoi((*values)[0]);
	Name = (*values)[1];
	Email = (*values)[2];
	Password = (*values)[3];
	Maximum_hours_allowed = stoi((*values)[4]);
	year = stoi((*values)[5]);
	GPA = stof((*values)[6]);
	for (int i = 7; i < (*values).size(); i++)
	{
		Courses_in_progress->push_back((*values)[i]);
	}
	Finished_courses = finishedCourse;
}
vector<string>* student::get_course_in_progress() {
	return Courses_in_progress;
}
unordered_map<string, float>* student::get_Finished_courses() {
	return Finished_courses;
}
void student::set_GPA(float gpa)
{
	GPA = gpa;

}
vector<string>* student::get_course() {
	return Courses_in_progress;
}
void student::registerCourse(unordered_map<string, course>* courses)
{
begin:
	system("cls");
	cout << "Available courses (press q to exit ) : \n";
	int i = 0;
	for (unordered_map<string, course>::iterator it = courses->begin(); it != courses->end(); it++) {
		cout << i + 1 << " . " << it->second.get_name() << " ( " << it->second.get_code() << " )\n";
		i++;
	}
	string choice;
	cout << "Enter the course code you want to register for note write it as u see: ";
	cout << "Note hours u have is : " << Maximum_hours_allowed << endl;
	cin >> choice;
	if (choice == "q" or choice == "Q")
	{
		return;
	}
	if ((*courses).find(choice) == (*courses).end())
	{
		cout << "Enter  valid code \n";
		Sleep(3000);
		goto begin;
	}
	if ((*courses)[choice].get_Requirement() && !hasPrerequisites((*courses)[choice])) {
		cout << "You have not completed the pre-required courses for this course " << (*courses)[choice].get_name() << ".\n";
		Sleep(3000);
		goto begin;
	}
	if (find((*Courses_in_progress).begin(), (*Courses_in_progress).end(), choice) != (*Courses_in_progress).end()

		||                 //or                 u can't take course u hava take or u already take now 

		(*Finished_courses).find(choice) != (*Finished_courses).end()) {
		cout << "You have already taken or are currently taking this course.\n";
		Sleep(3000);
		goto begin;
	}
	if (Maximum_hours_allowed - (*courses)[choice].get_hours() < 0)
	{
		cout << "You can't registered for this course\n";
		Sleep(2000);
		goto begin;
	}
	if ((*courses)[choice].get_max() == 0)
	{
		cout << "You can't registered for this course\n";
		Sleep(2000);
		goto begin;
	}
	Courses_in_progress->push_back((*courses)[choice].get_code());
	Maximum_hours_allowed -= (*courses)[choice].get_hours();
	(*courses)[choice].decrementEnrollment();
	cout << "You have successfully registered for " << (*courses)[choice].get_name() << " ( " << (*courses)[choice].get_code() << " ).\n";
	Sleep(2000);
	goto begin;
}
bool student::hasPrerequisites(course c) {
	unordered_set<course*>::iterator pre_it = c.get_pre_required_courses()->begin();
	for (pre_it; pre_it != c.get_pre_required_courses()->end(); pre_it++)
	{
		if ((*Finished_courses).find((*pre_it)->get_code()) == (*Finished_courses).end()) {
			return false;
		}
	}
	return true;
}
string student::get_name() {
	return Name;
}
string student::get_password() {
	return Password;
}
string student::get_Email() {
	return Email;
}
int student::get_Maximum_hours_allowed() {
	return Maximum_hours_allowed;
}
int student::get_id() {
	return Id;
}
int student::get_year() {
	return year;
}
bool student::operator<(const student& other) {
	return Id < other.Id;
}
void student::display_Student_courses(unordered_map<string, course>* courses)
{
	system("cls");
	if ((*Courses_in_progress).size() == 0) {
		cout << "NO Courses is taken Currently\n";
		Sleep(2000);
		return;
	}
	for (int i = 0; i < (*Courses_in_progress).size(); i++) {
		string id = (*Courses_in_progress)[i];
		unordered_map<string, course>::iterator it = (*courses).find(id);
		if (it != courses->end())
		{
			cout << "Course NAME : " << it->second.get_name();
		}
		cout << endl;
	}
	char x;
	cout << "press any thing for Exit\n";
	cin >> x;
}
void student::edit(unordered_map<string, course>* courses, bool call_to_edit_hours, string new_last_code[], int hour) {
	if (call_to_edit_hours)
	{
		for (int i = 0; i < Courses_in_progress->size(); i++)
		{
			if (Courses_in_progress->at(i) == new_last_code[1])
			{
				(*Courses_in_progress)[i] = new_last_code[0];
			}
		}
		unordered_map<string, float>::iterator it = Finished_courses->find(new_last_code[1]);
		if (Finished_courses->find(new_last_code[1]) != Finished_courses->end())
		{
			float num = it->second;
			Finished_courses->erase(new_last_code[1]);
			Finished_courses->insert(make_pair(new_last_code[0], num));
			Maximum_hours_allowed = max(Maximum_hours_allowed + hour, 0);
		}
		return;
	}
fun_begin:
	system("cls");
	cout << "this is student Data\n";
	cout << "Name : " << Name << endl;
	cout << "Password : " << Password << endl;
	cout << "If you went unerroll course press 1 \n";
	cout << "If you went to change name or password press 2 \n";
	cout << "If you went to re enroll press 3 \n";
	cout << "If you went to exit or save press 4 \n";
	int x;
	try
	{
		cin >> x;
	}
	catch (const std::exception&)
	{
		cout << "enter valid input\n";
		Sleep(2000);
		goto fun_begin;
	}
	if (x == 1)
	{
		cout << "Courses Student is take currently \n";
		for (int i = 0; i < (*Courses_in_progress).size(); i++)
		{
			cout << "-> " << (*courses)[(*Courses_in_progress)[i]].get_name()
				<< " " << (*courses)[(*Courses_in_progress)[i]].get_code() << endl;
		}
		if ((*Courses_in_progress).size() == 0)
		{
			cout << "No courses is taken currently\n";
			Sleep(2000);
			goto fun_begin;
		}
		string code;
		cout << "type course code to unenroll \n";
		cin >> code;
		if (find((*Courses_in_progress).begin(), (*Courses_in_progress).end(), code) == (*Courses_in_progress).end()) {
			system("cls");
			cout << "Please type code correctly\n";
			goto fun_begin;
		}
		else
		{
			this->undo_del.push(code);
			Maximum_hours_allowed += (*courses)[code].get_hours();
			(*Courses_in_progress).erase(find((*Courses_in_progress).begin(), (*Courses_in_progress).end(), code));
			for (int i = 0; i < (*Courses_in_progress).size(); i++)
			{
				cout << "-> " << (*courses)[(*Courses_in_progress)[i]].get_name() << endl;
			}
			cout << "Done";
			Sleep(2000);
			goto fun_begin;
		}
	}
	else if (x == 2)
	{
		cout << "edit the name and password if you went to keep one of them press k | K if you went to back press q \n";
		string nm, pas;
		cout << "Name : ";
		cin >> nm;
		cout << "Password : ";
		cin >> pas;
		if (nm == "Q" || nm == "q")
		{
			goto fun_begin;
		}
		else if (nm != "K" && nm != "k")
		{
			Name = nm;
		}
		if (pas == "Q" || pas == "q")
		{
			goto fun_begin;
		}
		else if (pas != "K" && pas != "k")
		{
			Password = pas;
		}
		cout << "Done";
		Sleep(1000);
		goto fun_begin;
	}
	else if (x == 3)
	{
		if (undo_del.size() != 0)
		{
			(*Courses_in_progress).push_back(this->undo_del.top());
			Maximum_hours_allowed -= (*courses)[undo_del.top()].get_hours();
			cout << "Done you renroll in : " << (*courses)[undo_del.top()].get_name() << endl;
			undo_del.pop();
			Sleep(2000);
			goto fun_begin;
		}
		else
		{
			cout << "No courses to unenroll\n";
			Sleep(2000);
			goto fun_begin;
		}
	}
	else if (x == 4)
	{
		return;
	}
	else
	{
		cout << "Please type valid number\n";
		Sleep(2000);
		goto fun_begin;
	}
}
void student::filterBy(unordered_map<string, course>* courses)
{
	system("cls");
	int choice;
	cout << "1-Filter by Hours\n2-Filter by required or not\npress 0 to Exit\nAnswer : ";
	cin >> choice;
	if (choice == 1)
	{
		filterCourseHours(courses);
	}
	else if (choice == 2) {

		filterCoursereq(courses);
	}
	else {
		system("cls");
		return;
	}

}
void student::filterCoursereq(unordered_map<string, course>* courses)
{
	system("cls");
	int ans;
	cout << "1-Elective courses.\n2-Requirement courses.\npress 0 for Exit\nAnswer : ";
	cin >> ans;
	unordered_map<string, course>::iterator it = courses->begin();
	if (ans == 0)
	{
		return;
	}
	else if (ans == 1) {
		system("cls");
		cout << "Elective courses are: \n\n";
		for (it; it != courses->end(); it++)
		{

			if (!it->second.get_Requirement())
			{
				cout << it->second.get_name() << endl;
			}
		}
	}
	else if (ans == 2) {
		system("cls");
		cout << "Requirement courses are: \n\n";
		for (it; it != courses->end(); it++)
		{

			if (it->second.get_Requirement())
			{
				cout << it->second.get_name() << endl;
			}
		}
	}
	char x;
	cout << "press 0 for Exit\n";
	cin >> x;
}
float student::get_GPA() {
	return GPA;
}
void student::display_all_available_courses(unordered_map<string, course>* courses, bool calling_from_another_fun)
{
	system("cls");
	int i = 1;
	unordered_map<string, course> ::iterator it;
	cout << "  \t\t\t\t\t\t <<----All available Courses---->> \t\t\t\t\t\t  \n";
	it = courses->begin();
	while (it != courses->end()) {
		cout << i << ". " << it->second.get_name() << " ( " << it->second.get_code() << " ) ";
		cout << " (Instructor) : " << it->second.get_Instructor() << endl;
		it++;
		i++;
	}
	cout << endl;
	if (!calling_from_another_fun)
	{
		char x;
		cout << "enter any thing to exit : " << endl;
		cin >> x;
	}
}
void student::filterCourseHours(unordered_map<string, course>* courses)
{
begin:
	system("cls");
	int choice;
	cout << "1-courses with 2 hours.\n2-courses with 3 hours.\n3-courses with 4 hours.\npress 0 for Exit\nAnswer : ";
	cin >> choice;
	switch (choice)
	{
	case 0: {
		return;
		break;
	}
	case 1: {system("cls");
		cout << "Courses with 2 hours are :\n\n";
		for (unordered_map<string, course>::iterator it = courses->begin(); it != courses->end(); it++)
		{
			if (it->second.get_hours() == 2) {
				cout << it->second.get_name() << endl;
			}
		}
		break;
	}
	case 2: {system("cls");
		cout << "Courses with 3 hours are :\n\n";
		for (unordered_map<string, course>::iterator it = courses->begin(); it != courses->end(); it++)
		{
			if (it->second.get_hours() == 3) {
				cout << it->second.get_name() << endl;
			}
		}
		break;
	}
	case 3: {system("cls");
		cout << "Courses with 4 hours are :\n\n";
		for (unordered_map<string, course>::iterator it = courses->begin(); it != courses->end(); it++)
		{
			if (it->second.get_hours() == 4) {
				cout << it->second.get_name() << endl;
			}
		}
		break;
	}
	default: {
		cout << "Enter valid number!\n";
		goto begin;
		break;
	}
	}
	char x;
	cout << "press 0 for Exit\n";
	cin >> x;
}
void student::display_Student_courses_grades(unordered_map<string, course>* courses)
{
	system("cls");
	for (unordered_map<string, float>::iterator it = Finished_courses->begin(); it != Finished_courses->end(); it++)
	{
		string id = it->first;
		unordered_map<string, course>::iterator it_2 = (*courses).find(id);
		if (it_2 != courses->end())
		{
			cout << "Course Name : " << it_2->second.get_name() << " Grade : " << it->second;
		}
		cout << endl;
	}
	cout << "CGPA : " << GPA << endl;
	char x;
	cout << "press 0 for Exit\n";
	cin >> x;
}
void student::display_student_data()
{
	system("cls");
	cout << "<----- Student Details --->\n";
	cout << "Name : " << Name << endl;
	cout << "ID : " << Id << endl;
	cout << "Email : " << Email << endl;
	cout << "Password : " << Password << endl;
	cout << "Comulative GPA : " << GPA << endl;
	cout << "Academic year : " << year << endl;
	cout << "Maximum hours allowed : " << Maximum_hours_allowed << endl;
	cout << "Academic year : " << year << endl;
	if (warning)
		cout << "You have Warning  \n";
	else
		cout << "You don't have any Warning  \n\n";

begin:
	char m;
	cout << "Enter Q or q to exit : ";
	cin >> m;
	if (m == 'q' || m == ' Q')
		return;
	else
		cout << "invalid input \n ";
	goto begin;
}
void student::BFS(string code,string space,unordered_map<string, course>* courses) {
	string arrow = ">";
	unordered_set<course*>* pre = courses->find(code)->second.get_pre_required_courses();
	unordered_set<course*>::iterator pre_it = pre->begin();
	if (pre->size()!=0)
	{
		for (pre_it; pre_it != pre->end(); pre_it++)
		{
			cout <<" "<< space << arrow << (*pre_it)->get_name() << endl;
			BFS((*pre_it)->get_code(), space + space + space, courses);
		}
	}
	else
	{
		return;
	}
}
void student::View_details_of_a_specific_course(unordered_map<string, course>* courses) {
begin:
	system("cls");
	display_all_available_courses(courses, true);
	string ans;
	cout << "Write course Code to view more details : (press q to back) ";
	cin >> ans;
	if (ans == "q")
	{
		return;
	}
	if (courses->find(ans) != courses->end())
	{
		system("cls");
		unordered_map<string, course>::iterator it = courses->find(ans);
		cout << "Here details about " << it->second.get_name() << endl;
		cout << "Code : " << it->first << endl;
		cout << "Hours : " << it->second.get_hours() << endl;
		cout << "Instructor :" << it->second.get_Instructor() << endl;
		unordered_set<course*>* pre = it->second.get_pre_required_courses();
		if (pre->size() != 0)
		{
			cout << "Pre Required Courses for this Course : \n";
			unordered_set<course*>::iterator pre_it = pre->begin();
			int i = 0;
			string space = "-";
			string arrow = ">";
			for (pre_it; pre_it != pre->end(); pre_it++)
			{
				cout << i + 1 <<space <<arrow << (*pre_it)->get_name()<< endl;
				BFS((*pre_it)->get_code(), space + space + space, courses);
				i++;
			}
		}
		else
		{
			cout << "No Pre Required Courses for this Course\n";
		}
		string word;
		if (it->second.get_Requirement())
			word = "Requirement";
		else
			word = "Elective";
		cout << "It's " << word << " Course.\n";
	}
	else
	{
		cout << "please try again with Correct Code\n";
		cout << "Write course Code to view more details : ";
		Sleep(3000);
		goto begin;
	}
	char x;
	cout << "press any thing for Exit\n";
	cin >> x;
}
void student::set_hours(int hours) {
	Maximum_hours_allowed = hours;
}
student::student() {

}
student::~student() {

}
//--------------------------------------------------------//
University::University()
{

}
University::University(files_d* data) {
	//copy the map b3den amsh ale fat 3shan memory
	Students = data->copy();
	for (int i = 0; i < 4; i++)
	{
		size_stude[i] = data->get_at(i);
	}
	Courses = data->copy_c();
}
unordered_map<int, student>* University::get_stud() {
	return Students;
}
unordered_map<string, course>* University::get_Courses() {
	return Courses;
}
void University::showCourse(bool showOnlyCourseCode)
{
	if (showOnlyCourseCode)
	{
		for (unordered_map<string, course>::iterator it = Courses->begin(); it != Courses->end(); it++)
		{
			cout << " code= " << it->second.get_code() << " Name " << it->second.get_name() << endl;
		}
	}
	else
	{
		for (unordered_map<string, course>::iterator it = Courses->begin(); it != Courses->end(); it++)
		{
			cout << "Name " << it->second.get_name() << " code= " << it->second.get_code() << "elective" << endl;
		}
	}
}
void University::login(string info[]) {
	if (info[0] == "admin")
	{
		return;
	}
	int id;
	try {
		id = stoi(info[0]);
	}
	catch (exception& ex) {
		cout << "Please Write Valid ID\n";
		Sleep(2000);
	}
	if ((*Students).find(id) == (*Students).end())
	{
		cout << "Not Found \n";
		Sleep(3000);
	}
	else
	{
		if ((*Students)[id].get_password() == info[1])
		{
here:
			while (true)
			{
				system("cls");
				cout << ">> Hello " << (*Students)[id].get_name() << " <<\n";
				if ((*Students)[id].warning)
				{
					cout << "Your GPA is Low please study Hard this Term\n";
				}
				string answer;
				cout << "--> press 1 for View List of all available courses\n";
				cout << "--> press 2 for Filter courses\n";
				cout << "--> press 3 for View details of a specific course\n";
				cout << "--> press 4 for Register for a course\n";
				cout << "--> press 5 for View all his/her courses\n";
				cout << "--> press 6 for View his/her courses grades and cumulative GPA\n";
				cout << "--> press 7 for Edit his/her data\n";
				cout << "--> press 8 for display student data\n";
				cout << "--> press 9 to display some Statistics \n";
				cout << "--> press 0 for Exit\n";
				cin >> answer;
				try
				{
					stoi(answer);
				}
				catch (const std::exception&)
				{
					cout << "Enter valid input\n";
					Sleep(2000);
					goto here;
				}
				if (stoi(answer) == 0)
				{
					return;
				}
				choose_fun(stoi(answer), id);
			}
		}
		else
		{
			cout << "Worng password\n";
			Sleep(2000);
		}
	}
}
void University::choose_fun(int ans, int id) {
	if (ans > 9 || ans < 1) {
		cout << "please enter valid number\n";
		cin >> ans;
		if (ans == 0)
		{
			return;
		}
		choose_fun(ans, id);
		return;
	}
	switch (ans)
	{
	case 1:
		(*Students)[id].display_all_available_courses(Courses, false);
		break;
	case 2:
		(*Students)[id].filterBy(Courses);
		break;
	case 3:
		(*Students)[id].View_details_of_a_specific_course(Courses);
		break;
	case 4:
		(*Students)[id].registerCourse(Courses);
		break;
	case 5:
		(*Students)[id].display_Student_courses(Courses);
		break;
	case 6:
		(*Students)[id].display_Student_courses_grades(Courses);
		break;
	case 7:
		(*Students)[id].edit(Courses, 0, {});
		break;
	case 8:
		(*Students)[id].display_student_data();
		break;
	case 9:
		show_stat();
		break;
	}
}
void University::fitchData()				//this function convert the temp pointers courses to network of connected courses
{
	for (unordered_map<string, course>::iterator it = Courses->begin(); it != Courses->end(); it++)
	{
		unordered_set<course*>* set = new unordered_set<course*>();
		for (unordered_set<course*>::iterator inner_itrator = Courses->at(it->first).pre_required_courses->begin(); inner_itrator != Courses->at(it->first).pre_required_courses->end(); inner_itrator++)
		{
			course* temp = *inner_itrator;												// we did this to get the code of the course
			set->insert(&Courses->at(temp->get_code()));								//now we are connecting things togather
			delete temp;
		}
		Courses->at(it->first).pre_required_courses->clear();
		Courses->at(it->first).pre_required_courses = set;
	}
}
void University::showText(int count, string code, string name, string elective, string maxNumber, int hours, string instructor)
{

	system("cls");
	cout << "Enter: to fill next attribute            ^B: to back off                   ^E: to go back to Main menu " << endl << endl;
	if (count >= 1)
	{
		cout << "Course Code: " << code << endl;
	}
	if (count >= 2)
	{
		cout << "Course Name: " << name << endl;
	}
	if (count >= 3)
	{
		cout << "Is this course elective? " << elective << endl;
	}
	if (count >= 4)
	{
		cout << "Maximum number of Students: " << maxNumber << endl;
	}
	if (count >= 5)
	{
		cout << "Course Hours: " << hours << endl;
	}
	if (count >= 6)
	{
		cout << "Instructor: " << instructor << endl;
	}

}
void University::addCourse(bool call, string last_code = "")			/*cout << string(str.length(), '\b');*/
{
	system("cls");
	string name = "B";
	string Code = "B";
	string elective = "B";
	bool Elective;
	string maxNumber = "B";
	int MaxNumber = 0;
	string hours = "1"; //use  stoi
	string instructor = "B";
	string preReq = "B";
	vector<string>preRequisite;
	cout << "Enter: to fill next attribute            ^B: to back off                   ^E: to go back to Main menu " << endl << endl;

input_code:

	cout << "Course Code: ";
	cin >> Code;
	if (Code == "B" or Code == "E") {
	Exit:											//We should go back to main menu from here
		return;
	}
	else
	{
		for (int i = 0; i < Code.size(); i++)			/* To convert code to uppercase*/
		{
			Code[i] = (char)toupper(Code[i]);
		}
		unordered_map<string, course>::const_iterator find_code = Courses->find(Code);     //check if the course code is valid
		if (find_code != Courses->end())			//This mean that the course code is in the list of courses 
		{
			showText(0, Code, name, elective, maxNumber, 0, instructor);
			cout << "Sorry, But this course is already Exist." << endl;
			goto input_code;
		}
	}
input_Name:
#undef max
	cout << "Course Name: ";
	char str[80];
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(str, 80);
	name = str;

	for (int i = 0; i < name.size(); i++)
	{
		if (name[i] == ' ')
		{
			name[i] = '_';
		}
	}

	if (name == "B")
	{
		showText(0, Code, name, elective, maxNumber, 0, instructor);
		goto input_code;
	}
	else if (name == "E")
	{
		goto Exit;
	}
input_elective:
	cout << "Is this course elective? ";
	cin >> elective;
	if (elective == "B")
	{
		showText(1, Code, name, elective, maxNumber, 0, instructor);
		goto input_Name;
	}
	else if (elective == "E")
	{
		goto Exit;
	}
	else
	{
		for (int i = 0; i < elective.size(); i++)			/* To convert code to uppercase*/
		{
			elective[i] = (char)toupper(elective[i]);
		}
		if (elective == "1" or elective == "Y" or elective == "YES" or elective == "T" or elective == "TRUE")
		{
			Elective = false;
		}
		else if (elective == "0" or elective == "N" or elective == "NO" or elective == "F" or elective == "FASLE")
		{
			Elective = true;
		}
		else
		{
			showText(2, Code, name, elective, maxNumber, 0, instructor);
			cout << "Invalid Input, Please enter (T/F) or (YES/NO) or (1/0)" << endl;
			goto input_elective;
		}
	}
input_maxNum:
	cout << "Maximum number of Students: ";
	cin >> maxNumber;
	if (maxNumber == "B")
	{
		showText(2, Code, name, elective, maxNumber, 0, instructor);
		goto input_elective;
	}
	else if (maxNumber == "E")
	{
		goto Exit;
	}
	else
	{
		try                                                    //if user enter letters "ABC" this block will throw an exception
		{
			MaxNumber = stoi(maxNumber);
		}
		catch (exception& e)
		{
			showText(3, Code, name, elective, maxNumber, 0, instructor);
			cout << "Please enter Numbers only." << endl;
			goto input_maxNum;
		}
	}
input_Hours:
	cout << "Course Hours: ";
	cin >> hours;
	if (hours == "B")
	{
		showText(3, Code, name, elective, maxNumber, 0, instructor);
		goto input_maxNum;
	}
	else if (hours == "E")
	{
		goto Exit;
	}
	else
	{
		if (hours != "2" and hours != "3" and hours != "4")
		{
			showText(4, Code, name, elective, maxNumber, 0, instructor);
			cout << "Invalid input you have to choose one of these options(2/3/4)" << endl;
			goto input_Hours;

		}
	}
input_instructor:
	cout << "Instructor: ";
	char st[80];
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.getline(st, 80);
	instructor = st;
	for (int i = 0; i < instructor.size(); i++)
	{
		if (instructor[i] == ' ')
		{
			instructor[i] = '_';
		}
	}
	if (instructor == "B")
	{
		showText(4, Code, name, elective, maxNumber, stoi(hours), instructor);
		goto input_Hours;
	}
	else if (instructor == "E")
	{
		goto Exit;
	}
input_preRequisite:
	unordered_set<course*>* v = new unordered_set<course*>();
	course* q = new course(name, Code, Elective, v, stoi(hours), instructor, MaxNumber, 0, 0);
	Courses->insert(make_pair(q->get_code(), *q));
	if (call)
	{
		int dif_Hours = (*Courses)[last_code].get_hours() - stoi(hours);
		unordered_map<int, student>::iterator it = Students->begin();
		string new_last_code[2] = { Code,last_code };
		for (it; it != Students->end(); it++)
		{
			it->second.edit(Courses, true, new_last_code, dif_Hours);
		}
		(*Courses).erase(last_code);
	}
	bool choose = coursePreRequisite(q, false);
	if (!choose)
	{
		Courses->erase(q->get_code());
		showText(5, Code, name, elective, maxNumber, stoi(hours), instructor);
		delete q, v;
		goto input_instructor;
	}
	else
	{
		return;
	}
}
void University::showText2(unordered_set<course*>* v, string selectedCourse, bool section, course* C, bool fromMain)
{
	system("cls");
	cout << "Enter: to fill next attribute            ^B: to back off                   ^E: to go back to Main menu " << endl << endl;
	cout << "Please choose one of the following Courses" << endl;
	showCourse(true);
	cout << endl;
	if (section)
	{
		if (fromMain)
			cout << "select coures: " << selectedCourse << endl << endl;
		else
			cout << "select coures: " << selectedCourse << ",  Course Name: " << C->get_name() << ", elective: " << !C->get_Requirement() << ", Max Number of students: " << C->get_max() << ", Hours: " << C->get_hours() << ", Instructor: " << C->get_Instructor() << endl << endl;

		cout << "          ^S: To Save data             ^C: To select onther course" << endl;

		for (unordered_set<course*>::iterator it = v->begin(); it != v->end(); it++)												//loop to show all new preRequsitis.
		{
			course* x = *it;
			cout << selectedCourse << " Pre-requisite: " << x->get_code() <<"  "<< x->get_name() << endl;
		}
		cout << selectedCourse << " Pre-requisite: ";
	}
}
bool University::coursePreRequisite(course* C, bool fromMain)
{
ReEnter:
	string selectedCourse = " ";
	string preRequist;
	unordered_set<course*>* preRe;
	unordered_set<course*>* backup = new unordered_set<course*>();
	unordered_set<course*> x;
	showText2(&x, " ", 0);
input_selectCourse:
	if (fromMain)
	{
		cout << "select coures: ";
		cin >> selectedCourse;
	}
	else
	{
		selectedCourse = C->get_code();
	}
	cout << endl;
	if (selectedCourse == "B" || selectedCourse == "E")
	{
	exit:											//here we go out
		return 0;
	}
	else                                                            //entering value
	{
		if (fromMain)
		{
			for (int i = 0; i < selectedCourse.size(); i++)			/* To convert code to uppercase*/
			{
				selectedCourse[i] = (char)toupper(selectedCourse[i]);
			}
			try                                                                 //-->HERE we can replace this block of code  with find() , but i think this way is much faster to search<--  
			{
				course c = Courses->at(selectedCourse);				           //this mean we have found the key			
			}
			catch (exception& fastFindFaild1)                                         //This mean that this course isn't in the list of courses
			{
				showText2(&x, selectedCourse, 0);
				cout << " this course isn't in the list." << endl;
				goto input_selectCourse;
			}
		}
		/*Until now we have the coures which we will add to it his preRequisites so next block of code to enter preRequisite*/
		preRe = Courses->at(selectedCourse).get_pre_required_courses();
		*backup = *Courses->at(selectedCourse).get_pre_required_courses();

	}
	if (fromMain)
		showText2(preRe, selectedCourse, 1);
	else
		showText2(preRe, selectedCourse, 1, C, false);
input_preReq:

	cin >> preRequist;

	if (preRequist == "E")
	{
		unordered_set<course*>* cvb = Courses->at(selectedCourse).pre_required_courses;
		Courses->at(selectedCourse).pre_required_courses->clear();
		delete cvb;
		Courses->at(selectedCourse).pre_required_courses = backup;
		goto exit;
	}
	else if (preRequist == "B")
	{
		if (preRe->size() != 0)
		{
			preRe->erase(--(preRe->end()));				//delete last element from the unordred_map
			showText2(preRe, selectedCourse, 1);
			goto input_preReq;
		}
		else
		{
			delete backup;
			goto exit;
		}
	}
	else if (preRequist == "C")
	{
		system("cls");
		unordered_set<course*>* cvb = Courses->at(selectedCourse).pre_required_courses;
		Courses->at(selectedCourse).pre_required_courses->clear();
		delete cvb;
		Courses->at(selectedCourse).pre_required_courses = backup;
		goto ReEnter;
	}
	else if (preRequist == "S")																		//save in the baises list
	{																								//DELETE ALL OLD COURSES.
		delete backup;
		if (fromMain)
			goto exit;
		else
			return true;
	}
	else                                                                          //we have entered course
	{
		for (int i = 0; i < preRequist.size(); i++)								/* To convert code to uppercase*/
		{
			preRequist[i] = (char)toupper(preRequist[i]);
		}
		if (preRequist == selectedCourse)
		{
			if (fromMain)
				showText2(preRe, selectedCourse, 1);
			else
				showText2(preRe, selectedCourse, 1, C, false);
			cout << preRequist << "   Invalid Course code ,you can't make the course pre-requisite of it self." << endl;
			cout << selectedCourse << " Pre-requisite: ";
			goto input_preReq;
		}
		try
		{
			course c = Courses->at(preRequist);
		}
		catch (exception& fastFindFaild2)
		{
			if (fromMain)
				showText2(preRe, selectedCourse, 1);
			else
				showText2(preRe, selectedCourse, 1, C, false);
			cout << preRequist << "   Invalid Course code please check the list of courses codes" << endl;
			cout << selectedCourse << " Pre-requisite: ";
			goto input_preReq;
		}

		/*Condition for repetition of same course code*/

		if (preRe->count(&Courses->at(preRequist)) != 0)     //this course have been added before 
		{
			if (fromMain)
				showText2(preRe, selectedCourse, 1);
			else
				showText2(preRe, selectedCourse, 1, C, false);
			cout << preRequist << " This course code have been added before." << endl;
			cout << selectedCourse << " Pre-requisite: ";
			goto input_preReq;
		}



		preRe->insert(&Courses->at(preRequist));
		int counter = 0;
		unordered_set<course*>* visited = new unordered_set<course*>();/*HELLO MAN WE HAVE SAVE POINT JUST RIGHT HERE*/
		for (unordered_set<course*>::iterator it = preRe->begin(); it != preRe->end(); it++)
		{
			int choose;												/* SOME CHANGES HAPPENED HERE WATCH OUT*/
			counter++;
			course* temp = *it;
			if (temp->get_code() != preRequist)
			{
				course b = Courses->at(temp->get_code());   //I have only the name of the course so i used "Courses->at(preRe->at(i))" to get object of class
				course* a = &Courses->at(preRequist);		//new value
				choose = Demand(*a, b, visited, preRe);
				visited->erase(a);
			}
			else
			{
				continue;
			}
			if (choose == 2)					//list is bigger than new
			{
				preRe->erase(&Courses->at(preRequist));
				showText2(preRe, selectedCourse, 1);
				cout << preRequist << " It is implied that this course is pre-Requisite course for " << temp->get_name() << endl;
				break;

			}
			else if (choose == 1)				//new is bigger than list
			{

				if (preRe->size() > 2)
				{
					--it;
					preRe->erase(&Courses->at(temp->get_code()));//PRO
					continue;
				}
				else
				{

					preRe->erase(&Courses->at(temp->get_code()));//PRO
					it = preRe->begin();
					break;
				}
				//preRe->erase(&Courses->at(temp->get_code()));//PRO
				//continue;
			}
		}
		delete visited;
		cout << selectedCourse << " Pre-requisite: ";
		goto input_preReq;
	}
}//                       intro     software engineer
bool University::isDemand(course a, course b, unordered_set<course*>* visitedTree)
{
	//see if the course in the very relative list

	course* x = &Courses->at(a.get_code());//target
	course* z = &Courses->at(b.get_code());//have the list
	if (visitedTree->count(z) == 0)
	{
		visitedTree->insert(z);
		if (b.get_pre_required_courses()->count(x) != 0)
		{
			return true;
		}
	}



	for (unordered_set<course*>::iterator it = b.pre_required_courses->begin(); it != b.pre_required_courses->end(); it++)
	{
		course* l = *it;
		course t = Courses->at(l->get_code());
		if (isDemand(a, t, visitedTree))
		{
			return true;
		}
	}
	return false;
}
int University::Demand(course fromTheList, course freshValue, unordered_set<course*>* VisitedTree, unordered_set<course*>* deleter)
{
	if (isDemand(fromTheList, freshValue, VisitedTree))
	{
		return 2;
	}
	//else
	//{
	//	for (unordered_set<course*>::iterator it = deleter->begin(); it != deleter->end(); it++)
	//	{
	//		course* w = *it;
	//		course* x = &Courses->at(w->get_code());
	//		VisitedTree->erase(x);
	//	}
	//}

	else if (isDemand(freshValue, fromTheList, VisitedTree))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
float University::get_student_avg_gpa(int year) {
	float sum = 0;
	unordered_map<int, student>::iterator it = Students->begin();
	for (it; it != Students->end(); it++)
	{
		if (it->second.get_year() == year)
		{
			sum += it->second.get_GPA();
		}
	}
	int size;
	if (size_stude[year - 1] == 0)
		sum = 0;
	else
		sum /= size_stude[year - 1];
	return sum;
}
University::~University() {

}
void University::means(double arr[]) {
	ptr = arr;
}
void University::show_stat() {
	system("cls");
	unordered_map<string, course>::iterator it = Courses->begin();
	for (it; it != Courses->end(); it++)
	{
		cout << it->second.get_name() << " Pass rate = " << it->second.pass_percentage() << endl;
	}
	cout << "Average GPA for Every Year : " << ptr[0] << " " << ptr[1]<<" "<< ptr[2]<<endl;
	char x;
	cout << "press any thing to exit\n";
	cin >> x;
}
//--------------------------------------------------------//
course::course() {

}
course::course(string c)
{
	code = c;
	name = "NoT UsEd";
	Instructor = "NoT UsEd";

}
int course::get_hours() {
	return Hours;
}
course::course(vector<string> info)
{
	name = info.at(0);
	code = info.at(1);
	if (info.at(2) == "0") Requirement = true; else  false;
	Maximum_number_of_Students = stoi(info.at(3));
	Hours = stoi(info.at(4));
	Instructor = info.at(5);
	fail_num = stoi(info.at(6));
	pass_num = stoi(info.at(7));
	int i = 8;
	unordered_set<course*>* y = new unordered_set<course*>();
	while (true)
	{
		try
		{
			string x = info.at(i);
			course* q = new course(x);
			y->insert(q);
			i++;
		}
		catch (exception& ex)
		{
			pre_required_courses = y;
			break;
		}

	}

}
void course::set_name(string Name)
{
	name = Name;
}
void course::set_code(string code)
{
	this->code = code;
}
void course::set_requirment(bool Requirement)
{
	this->Requirement = Requirement;
}
void course::set_maxnum(int maximum)
{
	Maximum_number_of_Students = maximum;
}
void course::set_pre_required_course(unordered_set<course*>* precode)			//GRAPH TOCH HAS BEEN ADDED**
{
	pre_required_courses->clear();

	if (precode->size() == 0)
	{
		return;
	}
	else {
		pre_required_courses = precode;
	}
}
float course::pass_percentage() {
	if ((pass_num + fail_num)!=0)
	{
		float part1 = (pass_num + fail_num);
		float pass_rate = float(pass_num / part1);
		return (pass_rate);
	}
	else
	{
		return 0;
	}
}
void course::set_hours(int hours)
{
	Hours = hours;
}
void course::set_instructor(string Instructor)
{
	this->Instructor = Instructor;
}
string course::get_name() {
	return name;
}
string course::get_code() {
	return code;
}
bool course::get_Requirement() {
	return Requirement;
}
unordered_set<course*>* course::get_pre_required_courses() {
	return pre_required_courses;
}
void course::decrementEnrollment() {
	Maximum_number_of_Students--;
}
course::course(string Name, string Code, bool req, unordered_set<course*>* p_r_c, int hours, string ins_name, int stuNumber,int pass,int fail) {
	name = Name;
	code = Code;
	Requirement = req;
	pre_required_courses = p_r_c;
	Hours = hours;
	Instructor = ins_name;
	Maximum_number_of_Students = stuNumber;
	pass_num = pass;
	fail_num = fail;
}
string course::get_Instructor() {
	return Instructor;
}
int course::get_max() {
	return Maximum_number_of_Students;
}
course::~course() {
	
}
//--------------------------------------------------------//
files_d::files_d() {
	this->readCourse();
	data = new unordered_map<int, student>();
	string filename = "data.txt";
	ifstream file(filename);
	cout << "please wait data is loading\n";
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			istringstream iss(line);
			vector<string>* row = new vector <string>(istream_iterator<string>{iss}, istream_iterator<string>());
			getline(file, line);
			istringstream issnext(line);
			getline(file, line);
			istringstream grades(line);
			vector<string>* nextRow = new vector <string>(istream_iterator<string>{issnext}, istream_iterator<string>());
			vector<string>* grade = new vector <string>(istream_iterator<string>{grades}, istream_iterator<string>());
			unordered_map<string, float>* courses_and_grades = new unordered_map<string, float>();
			for (int i = 0; i < grade->size(); i++)
			{
				courses_and_grades->insert(make_pair(nextRow->at(i), stof(grade->at(i))));
			}
			int id = stoi((*row)[0]);
			data->insert(make_pair(id, student(row, courses_and_grades)));
			size_stude[stoi(row->at(5)) - 1]++;
		}
		file.close();
		system("cls");
	}
}
unordered_map<int, student>* files_d::copy() {
	return data;
}
unordered_map<string, course>* files_d::copy_c() {
	return Courses;
}
void files_d::readCourse()
{
	ifstream courseFile("courseFile.txt");
	Courses = new unordered_map<string, course>();
	if (courseFile.is_open())
	{
		string cruser;
		while (getline(courseFile, cruser))
		{
			istringstream iss(cruser);
			vector<string> input(istream_iterator<string>{iss}, istream_iterator<string>());
			course* c = new course(input);
			string id = input[1];
			Courses->insert(make_pair(id, *c));
		}
		courseFile.close();
	}
}
void files_d::save_students_data() {
	ofstream MyFile("data.txt");
	MyFile << "";
	for (unordered_map<int, student>::iterator it = data->begin();
		it != data->end(); it++)
	{
		MyFile << it->first << " "
			<< it->second.get_name() << " "
			<< it->second.get_Email() << " "
			<< it->second.get_password() << " "
			<< it->second.get_Maximum_hours_allowed() << " "
			<< it->second.get_year() << " "
			<< it->second.get_GPA() << " ";
		vector<string>* Courses_in_progress = it->second.get_course_in_progress();
		for (int i = 0; i < (*Courses_in_progress).size(); i++)
		{
			MyFile << (*Courses_in_progress)[i];
			if (i != (*Courses_in_progress).size() - 1)
			{
				MyFile << " ";
			}
		}
		MyFile << endl;
		for (unordered_map<string, float>::iterator it_f = it->second.get_Finished_courses()->begin();
			it_f != it->second.get_Finished_courses()->end(); it_f++)
		{
			if (it_f != it->second.get_Finished_courses()->begin())
			{
				MyFile << " ";
			}
			MyFile << it_f->first;
		}
		MyFile << endl;
		for (unordered_map<string, float>::iterator it_f = it->second.get_Finished_courses()->begin();
			it_f != it->second.get_Finished_courses()->end(); it_f++)
		{
			if (it_f != it->second.get_Finished_courses()->begin())
			{
				MyFile << " ";
			}
			MyFile << it_f->second;
		}
		MyFile << endl;
	}
}
void files_d::save_course_data() {
	ofstream MyFile("courseFile.txt");
	MyFile << "";

	for (unordered_map<string, course>::iterator it = Courses->begin(); it != Courses->end(); it++)
	{
		MyFile << it->second.get_name() << " "
			<< it->first << " ";
		if (it->second.get_Requirement())
			MyFile << "0 ";
		else
			MyFile << "1 ";
		MyFile << it->second.get_max() << " "
			<< it->second.get_hours() << " "
			<< it->second.get_Instructor() << " "
			<< it->second.fail_num << " " << it->second.pass_num << " ";
		unordered_set<course*>::iterator t = it->second.get_pre_required_courses()->begin();
		for (t; t != it->second.get_pre_required_courses()->end(); t++)
		{
			course* x = *t;
			MyFile << x->get_code() << " ";
		}
		MyFile << endl;
	}
}
int files_d::get_at(int i) {
	return size_stude[i];
}
files_d::~files_d() {
	save_students_data();
	save_course_data();
}
//***************************//
void admin::fit(unordered_map<int, student>* Students,int arr_size[]) {
	for (int i = 2; i <= 4; i++)
	{
		double sum = 0;
		variance[i-2] = 0;
		int size = arr_size[i-1]; 
		if (size == 0)
			size = 1;
		for (unordered_map<int, student>::iterator it = Students->begin(); it != Students->end(); it++)
		{
			if (it->second.get_year()==i)
			{
				sum += it->second.get_GPA();
			}
		}
		mean[i-2] = sum / size;
		for (unordered_map<int, student>::iterator it = Students->begin(); it != Students->end(); it++)
		{
			if (it->second.get_year() == i) {
				double deviation = it->second.get_GPA() - mean[i - 2];
				variance[i - 2] += deviation * deviation;
			}
		}
		variance[i-2] /= size;
	}
}
bool admin::predict_(float gpa,int year) {
	double x = sqrt(variance[year-2]);
	double a = 1 / (x * sqrt(2 * M_PI));
	double b = -0.5 * pow((gpa - mean[year-2]), 2) / variance[year-2];
	double res = a * exp(b);
	if (res < 0.02)
	{
		return true;
	}
	return false;
}
double * admin::get_mean() {
	return mean;
}