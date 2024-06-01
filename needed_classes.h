#include <iostream>
#include <iomanip> 
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <set>
#include<unordered_set>
using namespace std;
class course
{
	string name;
	string code;
	bool Requirement;
	int Maximum_number_of_Students;
	int Hours;
	string Instructor;

public:
	int fail_num = 0, pass_num = 0;
	course(string);
	unordered_set<course*>* pre_required_courses;
	string get_name();
	string get_code();
	bool get_Requirement();
	float pass_percentage();
	void decrementEnrollment();
	int get_hours();
	string get_Instructor();
	int get_max();
	void set_name(string);
	void set_code(string);
	void set_requirment(bool);
	void set_maxnum(int);
	void set_hours(int);
	void set_instructor(string);
	course();
	unordered_set<course*>* get_pre_required_courses();
	void set_pre_required_course(unordered_set<course*>*);
	course(vector<string> info);
	course(string Name, string Code, bool req, unordered_set<course*>* p_r_c, int hours, string ins_name, int stuNumber,int pass,int fail);
	~course();
};
//------------------------------------------------------------//
class student
{	
	string Name,Email,Password;
	int Id;
	float GPA;
	int Maximum_hours_allowed;
	unordered_map<string, float> *  Finished_courses;
	vector<string> * Courses_in_progress;
	stack<string> undo_del;
public:
	int hours_taken = 0;
	bool warning;
	int year;
	student();
	void display_student_data();
	void BFS(string code, string space, unordered_map<string, course>* courses);
	void display_all_available_courses(unordered_map<string, course>* courses,bool calling_from_another_fun);
	student(vector<string>* values, unordered_map<string, float>* finishedCourse);
	bool hasPrerequisites(course c);
	void display_Student_courses(unordered_map<string, course>* courses);
	void registerCourse(unordered_map<string,course> * courses);
	vector<string>* get_course_in_progress();
	float get_GPA();
	unordered_map<string, float>* get_Finished_courses();
	vector<string>* get_course();
	void set_hours(int hours);
	string get_password();
	string get_name();
	string get_Email();
	void set_GPA(float gpa);
	int get_id();
	int get_Maximum_hours_allowed();
	int get_year();
	void View_details_of_a_specific_course(unordered_map<string, course>* courses);
	void display_Student_courses_grades(unordered_map<string, course>* courses);
	void edit(unordered_map<string, course>* courses, bool call_to_edit_hours,string code[], int hour = 0);
	void filterCourseHours(unordered_map<string, course>* courses);
	void filterBy(unordered_map<string, course>* courses);
	void filterCoursereq(unordered_map<string, course>* courses);
	bool operator<(const student& other);
	~student();
};
//------------------------------------------------------------//
class files_d
{
	unordered_map<int, student> * data;
	unordered_map<string, course>* Courses;
	int size_stude[4]={0,0,0,0};
public:
	files_d();
	void readCourse();
	unordered_map<int, student> * copy();
	unordered_map<string, course> * copy_c();
	void save_students_data();
	void save_course_data();
	int get_at(int i);
	~files_d();
};
//------------------------------------------------------------//
class University
{
	unordered_map<int ,student> *  Students;
	unordered_map<string, course>* Courses;
	void choose_fun(int answer,int id);
	bool isDemand(course, course, unordered_set<course*>* visitedTree);   //the base function
	int Demand(course a, course b, unordered_set<course*>* VisitedTree, unordered_set<course*>* deleter);  //0 :- mean they aren't demand  , 1:- mean a is bigger , 2:- mean that b is bigger 
	double* ptr;
public:
	University();
	void fitchData();
	void means(double arr[]);
	void showText2(unordered_set<course*>* v, string selectedCourse, bool section, course* C = NULL, bool fromMain = true);
	void show_stat();
	int size_stude[4] = { 0,0,0,0 };
	bool coursePreRequisite(course* C = NULL, bool fromMain = true);
	void showCourse(bool showOnlyCourseCode);
	void showText(int count, string code, string name, string elective, string maxNumber, int hours, string instructor);
	void addCourse(bool call,string last_code);
	University(files_d * data);
	void login(string info[]);
	unordered_map<int, student>* get_stud();
	unordered_map<string, course>* get_Courses();
	float get_student_avg_gpa(int year);
	~University();
};
//------------------------------------------------------------//
class admin
{
private:
	string Name;
	string Password;
	University* uni;
	void choose_fun(int ans);
	double mean[3], variance[3];
public:
	void List_of_all_courses_of_a_specific_student(unordered_map<int, student>* Students, unordered_map<string, course>* Courses);
	void view_students_in_specific_course(unordered_map<int, student>* Students, unordered_map<string, course>* courses);
	void add_Course_Grade_for_each_Student(unordered_map<int, student>* stud, unordered_map<string, course>* courses);
	void addStudent(unordered_map<int, student>* data, unordered_map<string, course>* Courses);
	double * get_mean();
	admin(University* uni_ptr);
	void editCourse(unordered_map<string, course>* courses, unordered_map<int, student>* stud);
	void login(string info[]);
	void fit(unordered_map<int, student>* Students,int arr[]);
	bool predict_(float gpa,int year);
	~admin();
};
//-----------------//