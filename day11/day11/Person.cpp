#include "Person.h"

Person::Person()
{
	_perName = nullptr;
	_perAge = 0;
}

Person::Person(const char* perName, int perAge) : _perAge(perAge)
{
	int size = strlen(perName) + 1;
	_perName = new char[size];
	StringCchCopyA(_perName, size, perName);
}

Person::~Person()
{
	delete[] _perName;
	_perName == nullptr;
}

void Person::SetName(char* perName)
{
	if (_perName != nullptr)
		delete[] _perName;

	int size = strlen(perName) + 1;
	_perName = new char[size];
	StringCchCopyA(_perName, size, perName);
}

char* Person::GetName()
{
	return _perName;
}

void Person::SetAge(int age)
{
	_perAge = age;
}

int Person::GetAge()
{
	return _perAge;
}

Subject::Subject(const char* subjName, int subjScore) : _subjScore(subjScore)
{
	int size = strlen(subjName) + 1;
	_subjName = new char[size];
	StringCchCopyA(_subjName, size, subjName);
}

Subject::~Subject()
{
	delete[] _subjName;
	_subjName == nullptr;
}

void Subject::SetScore(int Score)
{
	_subjScore = Score;
}

int Subject::GetScore()
{
	return _subjScore;
}

void Subject::SetName(char* subjName)
{
	if (_subjName != nullptr)
		delete[] _subjName;

	int size = strlen(subjName) + 1;
	_subjName = new char[size];
	StringCchCopyA(_subjName, size, subjName);
}

char* Subject::GetName()
{
	return _subjName;
}

Student::Student() : _id(Student::_seed++)
{
	_totalScore = 0;
	_averageScore = 0;
	_deleted = true;
	_subject[0] = nullptr;
	_subject[1] = nullptr;
	_subject[2] = nullptr;
}

Student::Student(const char* name, int age)
	: Person(name, age), _id(Student::_seed++), _totalScore(0), _averageScore(0)
{
	_subject[KOREAN] = new Subject("국어");
	_subject[ENGLISH] = new Subject("영어");
	_subject[MATH] = new Subject("수학");
	_deleted = false;
}

Student::~Student()
{
	delete _subject[KOREAN];
	delete _subject[ENGLISH];
	delete _subject[MATH];
}

int Student::GetTotal()
{
	return _totalScore;
}

int Student::GetAverage()
{
	return _averageScore;
}

void Student::AddSubjectScore(SUBJECT_NO subjectNo, int score)
{
	_totalScore -= _subject[subjectNo]->GetScore();
	_subject[subjectNo]->SetScore(score);
	_totalScore += score;

	_averageScore = _totalScore / 3;
}

void Student::PrintScore()
{
	if (_deleted == true)
		printf("%c %5s(%2d) %3d %3d %3d %3d %3d\n",
			'*', GetName(), GetAge(),
			_subject[KOREAN]->GetScore(),
			_subject[ENGLISH]->GetScore(),
			_subject[MATH]->GetScore(),
			_totalScore, _averageScore);
	else
		printf("%d %5s(%2d) %3d %3d %3d %3d %3d\n",
		_id, GetName(), GetAge(),
		_subject[KOREAN]->GetScore(),
		_subject[ENGLISH]->GetScore(),
		_subject[MATH]->GetScore(),
		_totalScore, _averageScore);
}

void Student::AddStudent()
{
	_deleted = false;
}

void Student::DeleteStudent()
{
	_deleted = true;
}

GradeHandler::GradeHandler(char* name, int stuTop) : _studentTop(stuTop)
{
	int size = strlen(name) + 1;
	_UVsityName = new char[size];
	StringCchCopyA(_UVsityName, size, name);

	if (_studentTop < 0)
		_studentTop = 1;
	_std = new Student[_studentTop];
}

void GradeHandler::PrintStuList()
{
	printf("학번 이름(나이) 국어 영어 수학 총점 평균\n");
}

void GradeHandler::SetIndex()
{
	_stuIndex += 1;
}

int GradeHandler::GetIndex()
{
	return _stuIndex;
}

int GradeHandler::GetTop()
{
	return _studentTop;
}

Student* GradeHandler::GetStudent()
{
	return _std;
}

void GradeHandler::AddStudent(char* name, int age)
{
	_std[_stuIndex].SetName(name);
	_std[_stuIndex].SetAge(age);
}

void GradeHandler::UpdateStudent(char* name, int age, int id)
{
	_std[id - 1].SetName(name);
	_std[id - 1].SetAge(age);
}

void GradeHandler::DeleteStudent(int id)
{
	_std[id - 1].DeleteStudent();
}
