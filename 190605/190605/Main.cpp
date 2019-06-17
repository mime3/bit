#ifdef _DEBUG
#pragma comment(lib, "opencv_world346d.lib")
#else
#pragma comment(lib, "opencv_world346.lib")
#endif

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;



void print_matInfo(String m_name, Mat m)
{
	cout << "[" << m_name << " ���" << endl;
	cout << " ä�μ� = " << m.channels() << endl;
	cout << " �� x �� = " << m.rows << " X " << m.cols << endl << endl;
}

void print_vectorInfo(string v_name, vector<int> v)
{
	cout << "[" << v_name << "] = ";
	if (v.empty())
		cout << "���Ͱ� �������" << endl;
	else
		cout << ((Mat)v).reshape(1, 1) << endl;

	cout << ".size() = " << v.size() << endl;
}

void print_locateROI(String str, Mat m)
{
	Size size;
	Point pt;
	m.locateROI(size, pt);

	cout << "�θ�ũ�� " << size << ", ";
	cout << "[" << str << "] = ";
	cout << m.size() << " from" << pt << endl;
}

// mat::release() �޼ҵ�� ��� �����Ϳ� ���õ� ���� ī���͸� ���ҽ�Ŵ
// ���� ī���Ͱ� 0�� �����ϸ� ��� �����͸� �����ϰ�,
// ��� �����Ϳ� ���� ī������ �����ʹ� ��� NULL�� �����Ͽ� �޸𸮸� ����
// �Ϲ������� Mat Ŭ������ destructor() �� ���� �ڵ����� ȣ��Ǳ� ������ ��������� ȣ���ϴ� ��찡 �幰��.
void print_matInfo2(String name, Mat m)
{
	String mat_type;
	if (m.depth() == CV_8U)
		mat_type = "CV_8U";
	else if (m.depth() == CV_8S)
		mat_type = "CV_8S";
	else if (m.depth() == CV_16U)
		mat_type = "CV_16U";
	else if (m.depth() == CV_16S)
		mat_type = "CV_16S";
	else if (m.depth() == CV_32S)
		mat_type = "CV_32S";
	else if (m.depth() == CV_32F)
		mat_type = "CV_32F";
	else if (m.depth() == CV_64F)
		mat_type = "CV_64F";

	cout << name << " ũ��" << m.size() << ", ";
	cout << " �ڷ��� " << mat_type << "C" << m.channels() << endl;
	cout << m << endl << endl;
}

int main()
{
	//Mat m1(2, 3, CV_8U, 2);
	//Mat m2(2, 3, CV_8U, Scalar(10));

	//Mat m3 = m1 + m2;
	//Mat m4 = m2 - 6;
	//Mat m5 = m1;

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;
	//cout << "[m4] = " << endl << m4 << endl << endl;

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m5] = " << endl << m5 << endl;
	//m5 = 100;
	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m5] = " << endl << m5 << endl;



	// resize �̾� ���̰ų� �ڸ�, ���϶� ���� 2�� �ʱ�ȭ
	//Mat m = (Mat_<uchar>(2, 4) << 1, 2, 3, 4, 5, 6, 7, 8);
	//cout << "[m] = " << endl << m << endl << endl;

	//m.resize(1);
	//cout << "m.resize(1) = " << endl << m << endl;
	//m.resize(3);
	//cout << "m.resize(3) = " << endl << m << endl << endl;
	//m.resize(5, Scalar(50));
	//cout << "m.resize(5) = " << endl << m << endl;


	// reshape(int cn, int rows)
	// ���� �� �� ��� ��ü ���Ҽ��� �¾ƾ���
	// create(int rows, int cols, int type, int ndims, int* sizes)
	// ������ �����ϴ� ����� ����, ��, ��, �ڷ����� �����Ͽ� �ٽû���
	// ������İ� ũ��� �ڷ����� �ٸ��� ���� �޸𸮸� �����ϰ� ���ο� �����͸� ����
	//Mat m1(2, 6, CV_8U);
	//Mat m2 = m1.reshape(2);
	//Mat m3 = m1.reshape(3, 2);

	//print_matInfo("m1(2,6)", m1);
	//print_matInfo("m2 = m1.reshape(2)", m2);
	//print_matInfo("m3 = m1.reshape(3, 2)", m3);

	//m1.create(3, 5, CV_16S);
	//print_matInfo("m1.create(3, 5,  CU_16S)", m1);


	// clone 
	// ������� �����ؼ� ���ο� ��� ����
	// copyto
	// ��ĵ����͸� ���ڷ� �Էµ� mat ��Ŀ� ����
	// convertto
	// ��Ŀ����� Ÿ���� �����Ͽ� ������ ����� mat�� ��ȯ
	//double data[] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.9, 9.9, 10, 11, 12 };
	//Mat m1(3, 4, CV_64F, data);
	//Mat m2 = m1.clone();
	//Mat m3, m4;
	//m1.copyTo(m3);
	//m1.convertTo(m4, CV_8U);

	//cout << "m1 = " << m1 << endl << endl;
	//cout << "m2 = " << m2 << endl << endl;
	//cout << "m3 = " << m3 << endl << endl;
	//cout << "m4 = " << m4 << endl << endl;


	//Mat m = Mat::eye(10, 10, CV_32FC1);
	//cout << "Element (3,3) is " << m.at<float>(3, 3) << endl;

	//Mat m2 = Mat::eye(10, 10, CV_32FC2);
	//cout << "Element (3,3) is " << m2.at<Vec2f>(3, 3)[0] << ", " << m2.at<Vec2f>(3, 3)[1] << endl;
	//
	//Mat m3 = Mat::eye(10, 10, traits::Type<Complex<float>>::value);
	//cout << "Element (3,3) is " << m3.at<Complexf>(3, 3).re << " + " << m3.at<Complexf>(3, 3).im << "i"<< endl;

	//int sz[3] = { 4,4,4 };
	//Mat m4(3, sz, CV_32FC3);
	//randu(m4, -1.0f, 1.0f);
	////cout << "m4 = " << endl << m4 << endl << endl; // 3���� �迭 cout �Ұ�

	//float max = 0.0f;
	//MatConstIterator_<Vec3f> it = m4.begin<Vec3f>();
	//float len2;
	//while (it != m4.end<Vec3f>())
	//{
	//	cout << (*it)[0] << ", " << (*it)[1] << ", " << (*it)[2] << endl;
	//	len2 = (*it)[0] * (*it)[0] * (*it)[1] * (*it)[1] * (*it)[2] * (*it)[2];
	//	if (len2 > max)
	//		max = len2;
	//	it++;
	//}
	//cout << "max = " << max << endl;



	//vector<Point> v1;

	//v1.push_back(Point(10, 20));
	//v1.push_back(Point(20, 30));
	//v1.push_back(Point(50, 60));

	//vector<float> v2(3, 9.25);
	//Size arr_size[] = { Size(2,2), Size(3,3), Size(4,4) };
	//int arr_int[] = { 10,20,30,40,50 };

	//vector<Size> v3(arr_size, arr_size + sizeof(arr_size) / sizeof(Size));
	//vector<int> v4(arr_int + 2, arr_int + sizeof(arr_int) / sizeof(int));

	//cout << "[v1] " << (Mat)v1 << endl << endl;
	//cout << "[v2] " << ((Mat)v2).reshape(1, 1) << endl << endl;
	//cout << "[v3] " << ((Mat)v3).reshape(1, 1) << endl << endl;
	//cout << "[v4] " << ((Mat)v4).reshape(1, 1) << endl << endl;



	//int arr[] = { 10,20,30,40,50 };
	//vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));

	//print_vectorInfo("v1", v1);

	//v1.insert(v1.begin() + 2, 100);
	//print_vectorInfo("v1.insert(2)", v1);
	//cout << ".capacity() = " << v1.capacity() << endl << endl;

	//v1.erase(v1.begin() + 3);
	//print_vectorInfo("v1.erase(3)", v1);
	//cout << ".capacity() = " << v1.capacity() << endl << endl;

	//v1.clear();
	//print_vectorInfo("v1.clearf()", v1);


	//vector<double> v1, v2;
	//v1.reserve(10000000);

	//double start_time = clock();
	//for (int i = 0; i < v1.capacity(); i++)
	//{
	//	v1.push_back(i);
	//}
	//printf("reserve() ��� %5.2f ms\n", (clock() - start_time));

	//start_time = clock();
	//for (int i = 0; i < v1.capacity(); i++)
	//{
	//	v2.push_back(i);
	//}
	//printf("reserve() �̻�� %5.2f ms\n", (clock() - start_time));



	//Range(int start, int end)
	// start <= ���� < end 
	// int size() sub sequence�� ũ�� ��ȯ
	// bool empty() : is sub sequence empty ?
	// Range all() : ��ü �������� range�� ��ȯ
//	Range r1(0, 3), r2(3, 7);
//	int data[] =
//	{
//	  10,11,12,13,14,15,16,
//	  20,21,22,23,24,25,26,
//	  30,31,32,33,34,35,36,
//	  40,41,42,43,44,45,46
//	};
//#ifdef VER1
//	Mat m1, m2;
//	m1 = Mat(4, 7, CV_32S, data);
//	m2 = m1(r1, r2);
//	
//	cout << "[m1�� 2�� ��] = " << m1.row(2) << endl;
//	cout << "[m1�� 1�� ��] = " << endl << m1.col(1) << endl;
//	cout << "[m1�� (0~2�� ���)] = " << endl << m1.rowRange(r1) << endl << endl;
//	cout << "[m1] = " << endl << m1 << endl << endl;
//
//	m2.setTo(50);
//	cout << "[m2] = " << endl << m2 << endl;
//	cout << "[m1] = " << endl << m1 << endl << endl;
//#else
//	Mat m1(5, 7, CV_32S, data);
//	Mat m2 = m1(r1, r2);
//	Mat m3 = m1(r1, r1);
//
//	cout << "[m1] = " << endl << m1 << endl;
//	cout << "[m2] = " << endl << m2 << endl;
//	cout << "[m3] = " << endl << m3 << endl;
//
//
//	print_locateROI("m2", m2);
//	print_locateROI("m3", m3);
//
//	m2.adjustROI(-1, 1, 2, -1);
//	m3.adjustROI(0, -1, -2, 2);
//
//	cout << endl << "<���ɿ��� ���� ��>" << endl;
//	print_locateROI("m2", m2);
//	print_locateROI("m3", m3);
//	cout << endl;
//	cout << "[���� m2] = " << endl << m2 << endl;
//	cout << "[���� m3] = " << endl << m3 << endl;
//#endif



	//Mat m1, m2, m3;
	//Mat m4 = Mat::zeros(2, 6, CV_8UC1);
	//Mat add1(2, 3, CV_8UC1, Scalar(100));
	//Mat add2 = (Mat)Mat::eye(4, 3, CV_8UC1);

	//m1.push_back(100);
	//m1.push_back(200);
	//m2.push_back(100.5);
	//m2.push_back(200.6);
	//m3.push_back(add1);
	//m3.push_back(add2);

	//m4.push_back(add1.reshape(1, 1));
	//m4.push_back(add2.reshape(1, 2));

	//print_matInfo2("m1", m1);
	//print_matInfo2("m2", m2);
	//print_matInfo2("m3", m3);
	//print_matInfo2("m4", m4);

	//m1.pop_back(1);
	//m2.pop_back(2);
	//m3.pop_back(3);
	//cout << "m1" << endl << m1 << endl;
	//cout << "m2" << endl << m2 << endl;
	//cout << "m3" << endl << m3 << endl;


	
	//Mat m1(2, 6, CV_8SC1, Scalar(100));
	//Mat m2(3, 3, CV_32S);
	//Range r1(0, 2), r2(0, 2);
	//Mat m3 = m1(r1, r2);

	//print_matInfo("m1", m1);
	//print_matInfo("m2", m2);
	//print_matInfo("m3", m3);

	//m2.release();
	//m3.release();
	//print_matInfo("m2", m2);
	//print_matInfo("m3", m3);
	//print_matInfo("m1", m1);

	//m1.release();
	//print_matInfo("m1", m1);



	//cross() ����, dot() ����, inv() �����, mul ��Į���, t() ��ġ���
	//float data[] =
	//{
	//	1,0,2,
	//	-3,2,6,
	//	-1,-2,3
	//};
	//Mat m1(3, 3, CV_32F, data);
	//Mat m2(Matx13f(6, 30, 8));
	//Mat m2_t = m2.t();

	//Mat m1_inv = m1.inv(DECOMP_LU);
	//Mat x = m1_inv * m2_t;

	//cout << "[m1] = " << endl << m1 << endl << endl;
	//cout << "[m1_inv] = " << endl << m1_inv << endl << endl;
	//cout << "[m2_t] = " << endl << m2_t << endl;

	//cout << "������������ �� x1 x2 x3 = " << x.t() << endl << endl;
	////cout << "[m2_t] = " << endl << m2_t << endl << endl;



	//saturate_cast<_Tp>
	// ���� �������� �÷� ������ȯ ��� / ���� ����, ������, ������ ���� �پ��� �������� 8bit ������ ����� ����� ���� �� ����
	// �̷��� ����� �������� 8bit�� �����ϱ� ���� ��ȭ��� ������ ���
	// �������� 8bit �ʰ��� 0�Ǵ� 255�� ����� ������ ����
	// �⺻ �ڷ����� ���ؼ��� ��ȭ����� �����ϵ��� saturate_cast<_Tp>()
	// ���ø� �޼ҵ带 ����
	//Matx<uchar, 2, 2> m1;
	//Matx<ushort, 2, 2> m2;
	//
	//m1(0, 0) = -50;
	//m1(0, 1) = 300;
	//m1(1, 0) = saturate_cast<uchar>(-50);
	//m1(1, 1) = saturate_cast<uchar>(300);

	//m2(0, 0) = -50;
	//m2(0, 1) = 80000;
	//m2(1, 0) = saturate_cast<ushort>(-50);
	//m2(1, 1) = saturate_cast<ushort>(80000);

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	


	
	String msg1 = "a is one";
	String msg2 = "a is two";
	String msg3 = "a is three";
	int a;

	while (true)
	{
		cout << "input a : ";
		cin >> a;

		try
		{
			if (a == 0)
				CV_Error(Error::StsDivByZero, "a is zero");
			if (a == 1)
				CV_Error(Error::StsBadSize, msg1);
			if (a == 2)
				CV_Error_(Error::StsOutOfRange, ("%s : %d", msg2.c_str(), a));
			if (a == 3)
				CV_Error_(Error::StsBadArg, ("%s : %d", msg3.c_str(), a));
			CV_Assert(a != 4);
		}
		catch (Exception& e)
		{
			cout << "Exception code (" << e.code << "):" << e.what();
			cout << endl;

			if (e.code == Error::StsAssert)
				break;
		}
	}
	

	return 0;
}