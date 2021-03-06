#ifdef _DEBUG
#pragma comment(lib, "opencv_world346d.lib")
#else
#pragma comment(lib, "opencv_world346.lib")
#endif

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
int main()
{
	//Mat image(300, 400, CV_8UC1, Scalar(200));
	//imshow("영상보기", image);
	//waitKey(0);

	//Point_<int> pt1(100, 200);
	//Point_<float> pt2(92.3f, 125.23f);
	//Point_<double> pt3(100.2, 300.9);

	//Point2i pt4(120, 69);
	//Point2f pt5(0.3f, 0.f), pt6(0.f, 0.4f);
	//Point2d pt7(0.25, 0.6);

	//Point pt8 = pt1 + (Point)pt2;
	//Point2f pt9 = pt6 * 3.14f;
	//Point2d pt10 = (pt3 + (Point2d)pt6) * 10;

	//cout << "pt8 = " << pt8.x << ", " << pt8.y << endl;
	//cout << "[pt9] = " << pt9 << endl;
	//cout << (pt2 == pt6) << endl;
	//cout << "pt7과 pt8의 내적" << pt7.dot(pt8) << endl;
	//cout << "pt8과 pt7의 내적" << pt8.dot(pt7) << endl;



	//Point3_<int> pt1(100, 200, 300);
	//Point3_<float> pt2(92.3, 125.23, 250.f);
	//Point3f pt3(0.3f, 0.f, 15.f);
	//Point3d pt4(0.25, 0.6, 33.3);

	//Point3i pt5 = pt1 + (Point3i)pt2;
	//Point3f pt6 = pt2 * 3.14f;
	//Point3d pt7 = ((Point3d)pt3 + pt4) * 10.f;

	//cout << "두 벡터의 내적(pt4, pt7)" << pt4.dot(pt7) << endl;
	//cout << "두 벡터의 내적(pt4, pt7)" << pt7.dot(pt4) << endl;
	//cout << "pt5 = " << pt5.x << "," << pt5.y << "," << pt5.z << endl;
	//cout << "[pt6] = " << pt6 << endl;
	//cout << "[pt7] = " << pt7 << endl;


	//Size_<int> sz1(100, 200);
	//Size_<float> sz2(192.3f, 25.3f);
	//Size_<double> sz3(100.2, 30.9);

	//Size sz4(120, 69);
	//Size2f sz5(0.3f, 0.f);
	//Size2d sz6(0.25, 0.6);

	//Point2d pt1(0.25, 0.6);
	//Size2i sz7 = sz1 + (Size2i)sz2;
	//Size2d sz8 = sz3 + (Size2d)sz2;
	//Size2d sz9 = sz5 + (Size2f)sz2;

	//cout << "sz1.width = " << sz1.width;
	//cout << ", sz1.height = " << sz1.height << endl;
	//cout << "sz1 넓이 = " << sz1.area() << endl;
	//cout << "[sz7] = " << sz7 << endl;
	//cout << "[sz8] = " << sz8 << endl;
	//cout << "[sz9] = " << sz9 << endl;


	//Size2d sz(100.5, 60.6);
	//Point2f pt1(20.f, 30.f), pt2(100.f, 200.f);

	//Rect_<int> rect1(10, 10, 30, 50);
	//Rect_<float> rect2(pt1, pt2);
	//Rect_<double> rect3(Point2d(20.5, 10), sz);

	//Rect rect4 = rect1 + (Point)pt1; // rect1 이 pt1만큼 이동
	//Rect2f rect5 = rect2 + (Size2f)sz; // rect2 의 넓이가 sz만큼 커짐
	//Rect2d rect6 = rect1 & (Rect)rect2; // 두 rect의 겹치는 영역 , |는 두개를 포함하는 영역

	//cout << "rect3 = " << rect3.x << ", " << rect3.y << ", ";
	//cout << rect3.width << "x" << rect3.height << endl;
	//cout << "rect4 = " << rect4.tl() << " " << rect4.br() << endl;
	//cout << "rect5 크기 = " << rect5.size() << endl;
	//cout << "[rect6] = " << rect6 << endl;


	//Vec<int, 2> v1(5, 12);
	//Vec<double, 3> v2(40, 130.7, 125.6);
	//Vec2b v3(10, 10);
	//Vec6f v4(40.f, 230.25f, 525.6f);
	//Vec3i v5(200, 230, 250);

	//Vec3d v6 = v2 + (Vec3d)v5;
	//Vec2b v7 = (Vec2b)v1 + v3;
	//Vec6f v8 = v4 * 20.0f;

	//Point pt1 = v1 + (Vec2i)v7;
	//Point3_<int> pt2 = (Vec3i)v2;

	//cout << "[v3] = " << v3 << endl;
	//cout << "[v7] = " << v7 << endl;
	//cout << "[v3 * v7] = " << v3.mul(v7) << endl; // saturate_cast 오버, 언더플로우시 최대 최소값
	//cout << "v8[0] = " << v8[0] << endl;
	//cout << "v8[1] = " << v8[1] << endl;
	//cout << "v8[2] = " << v8[2] << endl;
	//cout << "v8[3] = " << v8[3] << endl;
	//cout << "[v2] = " << v2 << endl;
	//cout << "[pt2] = " << pt2 << endl;



	//Scalar_<_TP> BGRA 저장용도
	//Scalar_<uchar> red(0, 0, 255);
	//Scalar_<int> blue(255, 0, 0);
	//Scalar_<double> color1(500);
	//Scalar_<float> color2(100.f, 200.f, 125.9f);

	//Vec3d green(0, 0, 300.5);
	//Scalar green1 = color1 + (Scalar)green;
	//Scalar green2 = color2 + (Scalar_<float>)green;

	//cout << "blue = " << blue[0] << ", " << blue[1];
	//cout << ", " << blue[2] << endl;
	//cout << "red = " << red << endl;
	//cout << "green = " << green << endl << endl;
	//cout << "(Scalar)green = " << (Scalar)green << endl;
	//cout << "green1 = " << green1 << endl;
	//cout << "green2 = " << green2 << endl;


	//Matx<int, 3, 3> m1(1, 2, 3, 4, 5, 6, 7, 8, 9);
	//Matx<float, 2, 3> m2(1, 2, 3, 4, 5, 6);
	//Matx<double, 3, 5> m3(3, 4, 5, 7);

	//Matx23d m4(3, 4, 5, 6, 7, 8);
	//Matx34d m5(1, 2, 3, 10, 11, 12, 13, 14, 15);
	//Matx66f m6(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

	//cout << "m5(0,0) = " << m5(0, 0) << " m5(1,0) = " << m5(1, 0) << endl;
	//cout << "m6(0,1) = " << m6(0, 1) << " m6(1,3) = " << m6(1, 3) << endl;

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;
	//cout << "[m4] = " << endl << m4 << endl;
	//cout << "[m5] = " << endl << m5 << endl;
	//cout << "[m6] = " << endl << m6 << endl << endl;


	
	//float data[] = { 1.2f, 2.3f, 3.2f, 4.5f, 5.f, 6.5f };

	//Mat m1(2, 3, CV_8U);
	//Mat m2(2, 3, CV_8U, Scalar(300));
	//Mat m3(2, 3, CV_16S, Scalar(300));
	//Mat m4(2, 3, CV_32F, data);

	//Size sz(2, 3);
	//Mat m5(Size(2, 3), CV_64F);
	//Mat m6(sz, CV_32F, data);

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;
	//cout << "[m4] = " << endl << m4 << endl << endl;
	//cout << "[m5] = " << endl << m5 << endl;
	//cout << "[m6] = " << endl << m6 << endl;



	//Mat m1 = Mat::ones(3, 5, CV_8UC1);
	//Mat m2 = Mat::zeros(3, 5, CV_8UC1);
	//Mat m3 = Mat::eye(3, 5, CV_8UC1);

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[m3] = " << endl << m3 << endl;



	//double a = 32.12345678, b = 2.7;
	//short c = 400;
	//float d = 10.f, e = 11.f, f = 13.f;

	//Mat_<int> m1(2, 4);
	//Mat_<uchar> m2(3, 4, 10);
	//Mat_<short> m3(4, 5, c);

	//m1 << 1, 2, 3, 4, 5, 6;
	//Mat m4 = (Mat_<double>(2, 3) << 1, 2, 3, 4, 5, 6);
	//Mat m5 = (Mat_<float>(2, 3) << a, b, c, d, e, f);

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl << endl;
	//cout << "[m3] = " << endl << m3 << endl << endl;
	//cout << "[m4] = " << endl << m4 << endl;
	//cout << "[m5] = " << endl << m5 << endl;


	Mat m1(4, 3, CV_32FC3);
	cout << m1 << endl;
	cout << "차원 수 = " << m1.dims << endl;
	cout << "행 개수 = " << m1.rows << endl;
	cout << "열 개수 = " << m1.cols << endl;
	cout << "행렬 크기 = " << m1.size() << endl << endl;

	cout << "전체 원소 개수 = " << m1.total() << endl;
	cout << "한 원소의 크기 = " << m1.elemSize() << endl;
	cout << "채널당 한 원소의 크기 = " << m1.elemSize1() << endl << endl;

	cout << "타입 = " << m1.type() << endl;
	cout << "((m1.channels() - 1) << 3) = " << ((m1.channels() - 1) << 3) << endl;
	cout << "타입(채널 수(3bit) | 깊이(3bit)) = " << ((m1.channels() - 1) << 3) + m1.depth() << endl;
	cout << "깊이 = " << m1.depth() << endl;
	cout << "채널 = " << m1.channels() << endl;
	cout << "step = " << m1.step << endl;
	cout << "step1() = " << m1.step1() << endl;

	

	return 0;
}