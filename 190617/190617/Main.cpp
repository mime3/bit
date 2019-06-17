#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*
Mapping 
화소들의 재배치
입력화소 -> Mapping -> 위치 재배치

1)순방향 매핑(forward mapping)
원본영상의 좌표를 중심으로 목적영상의 좌표를 계산
원본영상과 목표영상의 크기가 다르면 hole 또는 overlap 발생
hole - 주로 영상 확대시 발생
overlap - 주로 영상 축소시 발생

2)역방향 매핑(reverse mapping)
목적영상의 좌표를 중심으로 역변환 계산을 수행, 입력영상의 좌표상의 화소값을 가져옴
원본영상의 한개의 화소가 목표영상의 여러개의 화소로 매핑될수 잇음(화질저하)

2. 크기저하
-비율을 이용한 방법
x2 = x * ratioX
y2 = Y * ratioY

입력영상과 목표영상의 크기차이 비율을 이용하는 방법
ratioX = dst- width / src-width
ratioY = dst- height / src-height


순방향 매핑을 이용한 영상크기 확대 예제 (hole 또는 overlap이 발생)


최근접 보간법(nearest neighbor interpolation)
hole이 발생하면 가장 가까운 화소의 값을 가져옴
목적화소의 좌표를 반올림하는 간단한 알고리즘으로 구현
확대비율이 커지면 영상내 경계선이나 모서리에 계단현상이 나타날 수 있음

x = x2 / ratioX
y = y2 / ratioY


평행이동
화면의 좌상단이 원점
순방향 매핑
x2 = x  + dx;
y2 = y  + dy;

역방향 매핑
x = x2 - dx;
y = y2 - dy;
*/
void print_locateROI(String str, Mat m)
{
	Size size;
	Point pt;
	m.locateROI(size, pt);

	cout << "부모크기 " << size << ", ";
	cout << "[" << str << "] = ";
	cout << m.size() << " from" << pt << endl;
}
void scaling(Mat img, Mat& dst, Size size)
{
	dst = Mat(size, img.type(), Scalar());
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			int x = (int)(j * ratioX);
			int y = (int)(i * ratioY);
			dst.at<uchar>(y, x) = img.at<uchar>(i, j);
		}
	}
}

void scaling_nearest(Mat img, Mat& dst, Size size)
{
	dst = Mat(size, CV_8U, Scalar(0));
	double ratioY = (double)size.height / img.rows;
	double ratioX = (double)size.width / img.cols;

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			int x = (int)cvRound(j / ratioX);
			int y = (int)cvRound(i / ratioY);
			dst.at<uchar>(i, j) = img.at<uchar>(y, x);
		}
	}
}

void translation(Mat img, Mat& dst, Point pt)
{
	Rect rect(Point(0, 0), img.size());
	dst = Mat(img.size(), img.type(), Scalar(0));

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			Point dst_pt(j, i);
			Point img_pt = dst_pt - pt;
			if (rect.contains(img_pt))
				dst.at<uchar>(dst_pt) = img.at<uchar>(img_pt);
		}
	}
}

int main()
{
	//Mat image = imread("image/scaling_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat dst1, dst2;
	//scaling(image, dst1, Size(550, 550));
	//scaling_nearest(image, dst2, Size(550, 550));

	//imshow("image", image);
	//imshow("dst1-순방향매핑", dst1);
	//imshow("dst2-최근접보간법", dst2);
	////resizeWindow("dst1-축소", 200, 150);
	//waitKey();



	//Mat image = imread("image/scaling_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat dst1, dst2;
	//resize(image, dst1, Size(550, 550), 0, 0, INTER_LINEAR);
	//resize(image, dst2, Size(550, 550), 0, 0, INTER_NEAREST);
	//imshow("image", image);
	//imshow("dst1-양선형", dst1);
	//imshow("dst2-최근접", dst2);
	//waitKey();



	//Mat image = imread("image/scaling_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat dst1, dst2;
	//translation(image, dst1, Point(30, 80));
	//translation(image, dst2, Point(-80, -50));

	//imshow("image", image);
	//imshow("dst1", dst1);
	//imshow("dst2", dst2);
	//waitKey();



	Mat m1, m2, m3;
	m1.push_back(100);
	m1.push_back(200);

	m1.pop_back(1);
		cout << "m1" << endl << m1 << endl;

	return 0;
}