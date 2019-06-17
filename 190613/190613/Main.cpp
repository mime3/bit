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

	magnitude(dst1, dst2, dst); // �Ÿ� ���

	dst1 = abs(dst1);
	dst2 = abs(dst2);

	dst.convertTo(dst, CV_8U);
	convertScaleAbs(dst1, dst1);
	convertScaleAbs(dst2, dst2);
	//dst1.convertTo(dst1, CV_8U); ���� ����
	//dst2.convertTo(dst2, CV_8U);
	imshow("dst1 - ����", dst1);
	imshow("dst2 - ����", dst2);
}

int main()
{
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	// �ι��� ����ũ
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

	//// ������ ����ũ
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

	//// �Һ� ����ũ (1���̺й�����δ� ���帹�̾�)
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

	////OpenCV���� Sobel
	//Sobel(image, dst3, CV_32F, 1, 0, 3);
	//Sobel(image, dst4, CV_32F, 0, 1, 3);
	//magnitude(dst3, dst4, dst5);
	//dst5.convertTo(dst5, CV_8U);
	//convertScaleAbs(dst3, dst3);
	//convertScaleAbs(dst4, dst4);

	//imshow("image", image);
	//imshow("Sobel", dst);

	//imshow("dst3-opencv���� ��������ũ", dst3);
	//imshow("dst4-opencv���� ���򸶽�ũ", dst4);
	//imshow("dst5-opencv���� Sobel", dst5);
	//waitKey();



	/*�������� (Morphology)
	������(Shape)

	1) ħ�Ŀ���
	��ü�� ũ��� ��� ����� Ȯ��
	���� ���� ũ���� �������� ȿ��
	��ü�� ����� ���ҷ� ���� ��� ��ü�� �и�ȿ��
	�Է�
	01110
	01110
	11101
	01111
	00111

	����ũ
	010
	111
	010

	1���̻� ����ġ 0
	�����ġ 1

	2) ��â����(Dilation operation)
	��ü�� ũ��� ��â, ����� ���
	��ü���ο� �� ������ ä����

	3x3 ��â ����ũ
	010
	111
	010

	��� ����ġ 0
	1���̻� ��ġ 1


	3) ���� ����, ���� ����
	���� ����(Opening operation)
	ħ�Ŀ��� -> ��â����
	ħ�Ŀ������� ��ü�� ���, ���κ��� �̼��� ���� ����
	��â�������� ����ũ�� ����

	���� ����(Closing operation)
	��â���� -> ħ�Ŀ���
	��â�������� ��ü Ȯ��, ��ü���� ����� ä��
	ħ�Ŀ������� ���� ũ�� ����
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
	//imshow("��������", th_img);
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
