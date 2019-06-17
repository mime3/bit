#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void differential(Mat image, Mat& dst, float data1[], float data2[])
{
	Mat dst1, dst2;
	Mat mask1(3, 3, CV_32F, data1);
	Mat mask2(3, 3, CV_32F, data2);

	filter2D(image, dst1, CV_32F, mask1);
	filter2D(image, dst2, CV_32F, mask2);

	magnitude(dst1, dst2, dst); // 거리 계산

	dst1 = abs(dst1);
	dst2 = abs(dst2);

	dst.convertTo(dst, CV_8U);
	convertScaleAbs(dst1, dst1);
	convertScaleAbs(dst2, dst2);
	//dst1.convertTo(dst1, CV_8U); 위랑 같음
	//dst2.convertTo(dst2, CV_8U);
	imshow("dst1 - 수직", dst1);
	imshow("dst2 - 수평", dst2);
}

int main()
{
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	// 로버츠 마스크
	//float data1[] =
	//{
	//	-1,0,0,
	//	0,1,0,
	//	0,0,0
	//};
	//float data2[] =
	//{
	//	0,0,-1,
	//	0,1,0,
	//	0,0,0
	//};

	//Mat dst;
	//differential(image, dst, data1, data2);

	//imshow("image", image);
	//imshow("Robets", dst);
	//waitKey();



	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//// 프리윗 마스크
	//float data1[] =
	//{
	//	-1,0,1,
	//	-1,1,1,
	//	-1,0,1
	//};
	//float data2[] =
	//{
	//	-1,-1,-1,
	//	0,1,0,
	//	1,1,1
	//};

	//Mat dst;
	//differential(image, dst, data1, data2);

	//imshow("image", image);
	//imshow("Prewitt", dst);
	//waitKey();




	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//// 소벨 마스크 (1차미분방법으로는 가장많이씀)
	//float data1[] =
	//{
	//	-1,0,1,
	//	-2,1,2,
	//	-1,0,1
	//};
	//float data2[] =
	//{
	//	-1,-2,-1,
	//	0,1,0,
	//	1,2,1
	//};

	//Mat dst, dst3, dst4, dst5;
	//differential(image, dst, data1, data2);

	////OpenCV제공 Sobel
	//Sobel(image, dst3, CV_32F, 1, 0, 3);
	//Sobel(image, dst4, CV_32F, 0, 1, 3);
	//magnitude(dst3, dst4, dst5);
	//dst5.convertTo(dst5, CV_8U);
	//convertScaleAbs(dst3, dst3);
	//convertScaleAbs(dst4, dst4);

	//imshow("image", image);
	//imshow("Sobel", dst);

	//imshow("dst3-opencv제공 수직마스크", dst3);
	//imshow("dst4-opencv제공 수평마스크", dst4);
	//imshow("dst5-opencv제공 Sobel", dst5);
	//waitKey();



	/*모폴로지 (Morphology)
	형태학(Shape)

	1) 침식연산
	객체의 크기는 축소 배경은 확대
	영상내 작은 크기의 잡음제거 효과
	객체의 돌출부 감소로 서로 닿는 물체의 분리효과
	입력
	01110
	01110
	11101
	01111
	00111

	마스크
	010
	111
	010

	1개이상 불일치 0
	모두일치 1

	2) 팽창연산(Dilation operation)
	객체의 크기는 팽창, 배경은 축소
	객체내부에 빈 공간이 채워짐

	3x3 팽창 마스크
	010
	111
	010

	모두 불일치 0
	1개이상 일치 1


	3) 열림 연산, 닫힘 연산
	열림 연산(Opening operation)
	침식연산 -> 팽창연산
	침식연산으로 객체는 축소, 배경부분의 미세한 잡음 제거
	팽창연산으로 원래크기 복귀

	닫힘 연산(Closing operation)
	팽창연산 -> 침식연산
	팽창연산으로 객체 확장, 객체내부 빈공간 채움
	침식연산으로 원래 크기 복귀
	*/

	//Mat image = imread("image/erosion.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat th_img, dst;
	//threshold(image, th_img, 128, 255, THRESH_BINARY);

	//uchar data[] =
	//{
	//	0,1,0,
	//	1,1,1,
	//	0,1,0
	//};
	//Mat mask(3, 3, CV_8UC1, data);
	//morphologyEx(th_img, dst, MORPH_ERODE, mask);

	//imshow("image", image);
	//imshow("이진영상", th_img);
	//imshow("Erosion", dst);
	//waitKey();



	//Mat image = imread("image/dilation.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Mat th_img, dst;
	//threshold(image, th_img, 128, 255, THRESH_BINARY);

	//Matx<uchar, 3, 3> mask; 
	//mask << 0,1,0,1,1,1,0,0,0;
	//morphologyEx(th_img, dst, MORPH_DILATE, mask);

	//imshow("image", image);
	//imshow("Dilation", dst);
	//waitKey();



	Mat image = imread("image/morphology2.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);

	Mat th_img, dst1, dst2;
	threshold(image, th_img, 128, 255, THRESH_BINARY);

	Matx<uchar, 3, 3> mask;
	mask << 0, 1, 0, 1, 1, 1, 0, 1, 0;

	morphologyEx(th_img, dst1, MORPH_OPEN, mask);
	morphologyEx(th_img, dst2, MORPH_CLOSE, mask);

	imshow("image", image);
	imshow("Opening", dst1);
	imshow("Closing", dst2);
	waitKey();


	return 0;
}
