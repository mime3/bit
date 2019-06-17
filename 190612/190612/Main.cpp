#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void differOp(Mat img, Mat& dst, int mask_size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2);
	int mask_length = mask_size * mask_size;

	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			vector<uchar> mask(mask_length, 0);
			for (int k = 0, s = 0; k < mask_size; k++)
			{
				for (int t = 0; t < mask_size; t++, s++)
				{
					int y = i + k - h_m.y;
					int x = j + t - h_m.x;
					mask[s] = img.at<uchar>(y, x);
				}
			}
			uchar max = 0;
			for (int k = 0; k < mask_length / 2; k++)
			{
				int start = mask[k];
				int end = mask[mask_length - k - 1];

				uchar difference = abs(start - end);
				if (difference > max)
					max = difference;
			}
			dst.at<uchar>(i, j) = max;
		}
	}
}

void homogenOp(Mat img, Mat& dst, int mask_size)
{
	dst = Mat(img.size(), CV_8U, Scalar(0));
	Point h_m(mask_size / 2, mask_size / 2);
	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float max = 0;
			for (int k = 0; k < mask_size; k++)
			{
				for (int t = 0; t < mask_size; t++)
				{
					int y = i + k - h_m.y;
					int x = j + t - h_m.x;
					float difference = abs(img.at<uchar>(i, j) - img.at<uchar>(y, x));
					if (difference > max)
						max = difference;
				}
			}
			dst.at<uchar>(i, j) = max;
		}
	}
}

void filter(Mat img, Mat& dst, Mat mask)
{
	dst = Mat(img.size(), CV_32F, Scalar(0));
	Point h_m = mask.size() / 2;
	for (int i = h_m.y; i < img.rows - h_m.y; i++)
	{
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float sum = 0;
			for (int k = 0; k < mask.rows; k++)
			{
				for (int t = 0; t < mask.cols; t++)
				{
					int y = i + k - h_m.y;
					int x = j + t - h_m.x;
					sum += mask.at<float>(k, t) * img.at<uchar>(y, x);
				}
			}
			dst.at<float>(i, j) = sum;
		}
	}
}

void bgr2hsi(Mat img, Mat& hsi)
{
	hsi = Mat(img.size(), CV_32FC3);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			float B = img.at<Vec3b>(i, j)[0];
			float G = img.at<Vec3b>(i, j)[1];
			float R = img.at<Vec3b>(i, j)[2];

			float s = 1 - 3 * min(R, min(G, B)) / (R + G + B);
			float v = (R + G + B) / 3.0f;

			float tmp1 = ((R - G) + (R - B)) * 0.5f;
			float tmp2 = sqrt((R - G) * (R - B) + (G - B) * (G - B));
			float angle = acos(tmp1 / tmp2) * (180.f / CV_PI);
			float h = (B <= G) ? angle : 360 - angle;

			hsi.at<Vec3f>(i, j) = Vec3f(h / 2, s * 255, v);
		}
	}
	hsi.convertTo(hsi, CV_8U);
}

int main()
{
	//vector<Point> rect_pt1, rect_pt2;
	//rect_pt1.push_back(Point(200, 50));
	//rect_pt1.push_back(Point(400, 50));
	//rect_pt1.push_back(Point(400, 250));
	//rect_pt1.push_back(Point(200, 250));

	//float theta = 20 * CV_PI / 180;
	//Matx22f m(cos(theta), -sin(theta), sin(theta), cos(theta));
	//transform(rect_pt1, rect_pt2, m);

	//Mat image(400, 500, CV_8UC3, Scalar(255, 255, 255));
	//for (int i = 0; i < 4; i++)
	//{
	//	line(image, rect_pt1[i], rect_pt1[(i + 1) % 4], Scalar(0, 0, 0), 1);
	//	line(image, rect_pt2[i], rect_pt2[(i + 1) % 4], Scalar(255, 0, 0), 2);
	//	cout << "rect_pt1[" << to_string(i) + "] = " << rect_pt1[i] << "\t";
	//	cout << "rect_pt2[" << to_string(i) + "] = " << rect_pt2[i] << endl;
	//}
	//imshow("image", image);
	//waitKey();



	//Mat image1(50, 512, CV_8UC1, Scalar(0));
	//Mat image2(50, 512, CV_8UC1, Scalar(0));

	//for (int i = 0; i < image1.rows; i++)
	//{
	//	for (int j = 0; j < image1.cols; j++)
	//	{
	//		image1.at<uchar>(i, j) = j / 2;
	//		image2.at<uchar>(i, j) = (j / 20) * 10;
	//	}
	//}
	//imshow("image1", image1);
	//imshow("image2", image2);
	//waitKey();



	//Mat image = imread("image/pixel_test.jpg", IMREAD_GRAYSCALE);
	//if (image.empty())
	//{
	//	cout << "영상 읽기 실패" << endl;
	//	exit(1);
	//}

	//Rect roi(500, 313, 20, 15);
	//Mat roi_img = image(roi);
	//cout << "[roi_img] = " << endl;
	//for (int i = 0; i < roi_img.rows; i++)
	//{
	//	for (int j = 0; j < roi_img.cols; j++)
	//	{
	//		cout.width(5);
	//		cout << (int)roi_img.at<uchar>(i, j);
	//	}
	//	cout << endl;
	//}
	//rectangle(image, roi, Scalar(255), 1);
	//imshow("image", image);
	//waitKey();



	//Mat image = imread("image/bright.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(!image.empty());

	//Mat dst1 = image + 100;		// 행렬 연산시 자동으로 오버플로우, 언더플로우 처리
	//Mat dst2 = image - 100;
	//Mat dst3 = 255 - image;

	//Mat dst4(image.size(), image.type());
	//Mat dst5(image.size(), image.type());
	//for (int i = 0; i < image.rows; i++)
	//{
	//	for (int j = 0; j < image.cols; j++)
	//	{
	//		dst4.at<uchar>(i, j) = saturate_cast<uchar>(image.at<uchar>(i, j) + 100); // 오버플로우 처리
	//		//dst4.at<uchar>(i, j) = image.at<uchar>(i, j) + 100; // 오버플로우되면 어두워짐
	//		dst5.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
	//	}
	//}
	//imshow("Original", image);
	//imshow("dst1 - 밝게", dst1);
	//imshow("dst2 - 어둡게", dst2);
	//imshow("dst3 - 반전", dst3);
	//imshow("dst4 - 밝게", dst4);
	//imshow("dst5 - 반전", dst5);
	//waitKey();




	/* 두개의 행렬 합 연산시 saturate_cast로 인해 255를 넘어서는 값은 모두 흰색으로 나타남
	* 이 때문에 합성이 제대로 수행되지 않음. 이를 해결하는 방법은 다음과 같다
	* 1) dst(y, x) = image(y, x) *0.5 + image2(y, x) *0.5
	* 2) dst(y, x) = image1(y,) * alpha + image2(y, x) * (1-alpha)
	* 3) dst(y, x) = image1(y, x) * alpha + image2(y, x) * beta
	*/

	//Mat image1 = imread("image/add1.jpg", IMREAD_GRAYSCALE);
	//Mat image2 = imread("image/add2.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(!(image1.empty() || image2.empty()));

	//double alpha = 0.6, beta = 0.7;
	//Mat add_img1 = image1 + image2;
	//Mat add_img2 = image1 * 0.5 + image2 * 0.5;
	//Mat add_img3 = image1 * alpha + image2 * (1 - alpha);
	//Mat add_img4;
	//addWeighted(image1, alpha, image2, beta, 0, add_img4);

	//imshow("image1", image1);
	//imshow("add_img1", add_img1);
	//imshow("add_img2", add_img2);
	//imshow("add_img3", add_img3);
	//imshow("add_img4", add_img4);
	//waitKey();



	//Mat image = imread("image/contrast_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//Scalar avg = mean(image) / 2.0;
	//Mat dst1 = image * 0.5;
	//Mat dst2 = image * 2.0;
	//Mat dst3 = image * 0.5 + avg[0];
	//Mat dst4 = image * 2.0 - avg[0];

	//imshow("image", image);
	//imshow("dst1-대비감소", dst1);
	//imshow("dst2-대비증가", dst2);
	//imshow("dst3-평균이용 대비감소", dst3);
	//imshow("dst4-평균이용 대비증가", dst4);
	//waitKey();


	/*컬러 공간(color space)
	color system의 모든 색들을 3차원 조표로 표현한것
	-RGB CMY HSV LAB YUV등
	1. RGB 컬러 공간
	-- 빛의 삼원색
	-- 가산혼합 기본컬러 공간
	-- 모니터에서 컬러를 표현하기 위해 사용
	2. CMY 컬러 공간
	-- 인쇄기기글 이용해 종이에 출력하기 위한 컬러 공간
	-- 감산 혼합, 색의 삼우너색
	-- 빛의 삼원색과 보색관계, Cyan, Magenta, Yellow
	3. RGB - CMY 상호 변환
	C = 255 - R
	M = 255 - G
	Y = 255 - B
	R = 255 - C
	G = 255 - M
	B = 255 - Y
	4. CMY to CMYK
	-- black = min(Cyan, Magenta, Yellow)
	-- Cyan = Cyan - black
	-- Magenta = Magenta - black
	-- Yellow = Yellow - black
	색의 삼원색을 모두 합해도 잉크의 불순물 등의 영향으로 순수한 검은색이 만들어지지 않음
	이러한 이유로 검은색을 추가한 CMYK컬러 공간을 일반적으로 사용
	5.HSI 컬러공간
	-- 인간이 컬러정보를 인지하는 방법
	 색상(Hue), 채도(Saturation), 명도(Intensity)
	 
	*/
	
	//Mat BGR_img = imread("image/color_model.jpg", IMREAD_COLOR);
	//CV_Assert(BGR_img.data);

	//Scalar white(255, 255, 255);
	//Mat CMY_img = white - BGR_img;
	//Mat CMY_arr[3];
	//split(CMY_img, CMY_arr);

	//Mat black;
	//min(CMY_arr[0], CMY_arr[0], black);
	//min(black, CMY_arr[2], black);

	//CMY_arr[0] = CMY_arr[0] - black;
	//CMY_arr[1] = CMY_arr[1] - black;
	//CMY_arr[2] = CMY_arr[2] - black;


	//imshow("BGR_img", BGR_img);
	//imshow("CMY_img", CMY_img);
	//imshow("Yellow", CMY_arr[0]);
	//imshow("Magenta", CMY_arr[1]);
	//imshow("Cyan", CMY_arr[2]);
	//waitKey();

	


	//Mat BGR_img = imread("image/color_space.jpg", IMREAD_COLOR);
	//CV_Assert(BGR_img.data);

	//Mat HSI_img, HSV_img, hsi[3], hsv[3];

	//bgr2hsi(BGR_img, HSI_img);
	//cvtColor(BGR_img, HSV_img, CV_BGR2HSV); // opencv에서 제공하는 컬러변환 함수
	//split(HSI_img, hsi);
	//split(HSV_img, hsv);

	//imshow("BGR_img", BGR_img);
	//imshow("Hue", hsi[0]);
	//imshow("Saturation", hsi[1]);
	//imshow("Intensity", hsi[2]);
	//imshow("OpenCV_Hue", hsv[0]);
	//imshow("OpenCV_Saturation", hsv[1]);
	//imshow("OpenCV_Value", hsv[2]);
	//waitKey();



	/* 영역처리 Convolution
	- spatial domain, area based processing
	- 기존의 화소처리는 화소값 가각에 대한 연산수행
	 area based processing는 mask를 기반으로 영역에 대한 연산수행
	 
	 - 마스크기반 영역처리
	  마스크내의 원소값과 공간 영역에 있는 입력 영상의 화소값들을 대응되게 곱하여 출력화소값을 계산
	  이러한 처리를 하는과정을 모든 출력화소값에 대해 이동하면서 수행하는것을 Convolution 이라고 함
	  이때 입력영상에 곱해지는 이 마스크는 커널(Kernel), 윈도우(Window), 필터(Filter)등의 용어로도 사용됨
	  
	  1. 블러링
	  - 영상을 밝게 수정하면서 약간 흐리게 처리하는 기법
	  2. 샤프닝
	  영상의 밝기차이 극대화
	  3. Edge 검출
	  -- 영상처리에서 엣지의 정의 : 화소값이 급격하게 변하는 부분
	  -- 엣지검출방법 
	  - 차분연산 : 이웃하는 화소의 차분이 측정 임계값 이상인 지점찾기
	  - 1차 또는 2차 미분 마스크 이용
	  */

	//Mat image = imread("image/bright.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);
	//
	//float data[] =
	//{
	//	1 / 9.f, 1 / 9.f, 1 / 9.f,
	//	1 / 9.f, 1 / 9.f, 1 / 9.f,
	//	1 / 9.f, 1 / 9.f, 1 / 9.f
	//};

	//Mat mask(3, 3, CV_32F, data);
	//Mat blur;
	//filter(image, blur, mask);
	//blur.convertTo(blur, CV_8U);

	//imshow("image", image);
	//imshow("blur", blur);
	//waitKey();




	//Mat image = imread("image/blur.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);

	//float data1[] =
	//{
	//	0,-1,0,
	//	-1,5,-1,
	//	0,-1,0
	//};

	//float data2[] =
	//{
	//	-1,-1,-1,
	//	-1,9,-1,
	//	-1,-1,-1
	//};

	//Mat mask1(3, 3, CV_32F, data1);
	//Mat mask2(3, 3, CV_32F, data2);
	//Mat sharpen1, sharpen2;
	//filter(image, sharpen1, mask1);
	//filter(image, sharpen2, mask2);
	//sharpen1.convertTo(sharpen1, CV_8U);
	//sharpen2.convertTo(sharpen2, CV_8U);

	//imshow("image", image);
	//imshow("sharpen1", sharpen1);
	//imshow("sharpen2", sharpen2);
	//waitKey();



	
	//Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	//CV_Assert(image.data);
	//
	//Mat edge;
	//homogenOp(image, edge, 3);

	//imshow("image", image);
	//imshow("edge", edge);
	//waitKey();



	

	Mat image = imread("image/edge_test.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data);
	Mat edge;
	differOp(image, edge, 3);

	imshow("image", image);
	imshow("edge", edge);
	waitKey();
	

	return 0;
}