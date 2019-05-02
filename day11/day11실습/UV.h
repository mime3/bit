#pragma once
#pragma once
#include <strsafe.h>
class Person
{
	char* _perName;
	int		_perAge;
public:
	Person();
	Person(const char* perName, int perAge);
	~Person();

	void SetName(char* perName);
	char* GetName();
	void SetAge(int age);
	int GetAge();
};

class Subject
{
	char* _subjName;
	int		_subjScore;
public:
	Subject(const char* subjName, int subjScore = 0);
	~Subject();
	void SetScore(int Score);
	int GetScore();
	void SetName(char* subjName);
	char* GetName();

};

enum SUBJECT_NO
{
	KOREAN,
	ENGLISH,
	MATH
};

class Student : public Person
{
public:

private:
	static int  _seed;
	const int	_id;
	int			_totalScore;
	int			_averageScore;
	Subject*	_subject[3]; // ±¹¿µ¼ö
	bool		_deleted;
public:
	Student();
	Student(const char* name, int age);
	~Student();

	int GetTotal();
	int GetAverage();
	bool GetDeleted();

	void AddSubjectScore(SUBJECT_NO subjectNo, int score);
	void PrintScore();
	void AddStudent();
	void DeleteStudent();
};

class GradeHandler
{
	char* _UVsityName;
	Student* _std;
	int _stuIndex = 0;
	int _studentTop;
public:
	GradeHandler(char* name, int stuTop);
	void PrintStuList();
	void SetIndex();
	int GetIndex();
	int GetTop();
	Student* GetStudent();
	void AddStudent(char* name, int age);
	void UpdateStudent(char* name, int age, int id);
	void DeleteStudent(int id);
};