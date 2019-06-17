//#ifdef _DEBUG
//#pragma comment(lib, "opencv_world346d.lib")
//#else
//#pragma comment(lib, "opencv_world346.lib")
//#endif

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#pragma warning(disable:26495)
#pragma warning(disable:26451)

using namespace cv;
using namespace std;

void onMouse(int, int, int, int, void*);
void onMouse2(int, int, int, int, void*);
void onMouse3(int, int, int, int, void*);
void onChange(int value, void* userData);
void print_matInfo(string name, Mat m);
void put_string(Mat& frame, string text, Point pt, int value);

//string title = "트랙바 이벤트";
string title = "Event Drawing";
string bar_name = "밝기값";
Mat image;

int main()
{
	//Mat image1(300, 400, CV_8U, Scalar(255));
	//Mat image2(300, 400, CV_8U, Scalar(200));

	//string title1 = "white window";
	//string title2 = "gray window";

	//namedWindow(title1, WINDOW_AUTOSIZE);
	//namedWindow(title2, WINDOW_NORMAL);

	//moveWindow(title1, 100, 200);
	//moveWindow(title2, 300, 200);

	//imshow(title1, image1);
	//imshow(title2, image2);
	//waitKey();

	//destroyAllWindows();



	//Mat image(300, 400, CV_8U, Scalar(255));

	//string title1 = "AUTOSIZE";
	//string title2 = "NORMAL";

	//namedWindow(title1, WINDOW_AUTOSIZE);
	//namedWindow(title2, WINDOW_NORMAL);

	//resizeWindow(title1, 500, 200);
	//resizeWindow(title2, 500, 200);

	//imshow(title1, image);
	//imshow(title2, image);
	//waitKey();



	//Mat image(200, 300, CV_8U, Scalar(255));

	//namedWindow("키보드 이벤트", WINDOW_AUTOSIZE);

	//imshow("키보드 이벤트", image);

	//while (true)
	//{
	//	int key = waitKeyEx(20);
	//	if (key == 27)
	//		break;

	//	if (key == -1)
	//		continue;

	//	switch (key)
	//	{
	//	case 'a':
	//		cout << "a 입력" << endl;
	//		break;
	//	case 'b':
	//		cout << "b 입력" << endl;
	//		break;
	//	case 0x41:
	//		cout << "A 입력" << endl;
	//		break;
	//	case 66:
	//		cout << "B 입력" << endl;
	//		break;
	//	case 2424832:
	//		cout << "왼쪽 화살표 입력" << endl;
	//		break;
	//	case 2490368:
	//		cout << "위쪽 화살표 입력" << endl;
	//		break;
	//	case 2555904:
	//		cout << "오른쪽 화살표 입력" << endl;
	//		break;
	//	case 2621440:
	//		cout << "아래쪽 화살표 입력" << endl;
	//		break;
	//	default:
	//		cout << key << endl;
	//		break;
	//	}
	//}



	//Mat image(200, 300, CV_8U);
	//image.setTo(255);

	//imshow("마우스 이벤트1", image);
	//imshow("마우스 이벤트2", image);
	//int a = 10;

	//setMouseCallback("마우스 이벤트1", onMouse, &a);
	//waitKeyEx();



	//int value = 130;
	//image = Mat(300, 500, CV_8UC1, Scalar(120));

	//namedWindow(title, WINDOW_AUTOSIZE);
	//createTrackbar(bar_name, title, &value, 255, onChange);
	//setMouseCallback(title, onMouse2, 0);

	//imshow(title, image);
	//waitKey();
	



	//Scalar blue(255, 0, 0), red(0, 0, 255), green(0, 255, 0);
	//Scalar white(255, 255, 255);
	//Scalar yellow(0, 255, 255);

	//Mat image(400, 600, CV_8UC3, white);
	//Point pt1(50, 130), pt2(200, 300), pt3(300, 150), pt4(400, 50);
	//Rect rect(pt3, Size(200, 150));

	//line(image, pt1, pt2, red);
	//line(image, pt3, pt4, green, 2, LINE_AA);
	//line(image, pt3, pt4, green, 3, LINE_8, 1);

	//rectangle(image, rect, blue, 2);
	//rectangle(image, rect, blue, FILLED, LINE_4, 1);
	//rectangle(image, pt1, pt2, red, 3);

	//imshow("직선 사각형", image);
	//waitKey(0);
	
	
	
		
	//Scalar olive(128, 128, 0), violet(221, 160, 221), brown(42, 42, 165);
	//Point pt1(20, 100), pt2(20, 200), pt3(20, 250);

	//Mat image(300, 500, CV_8UC3, Scalar(255, 255, 255));

	//putText(image, "SIMPLEX", Point(20, 30), FONT_HERSHEY_SIMPLEX, 1, brown);
	//putText(image, "DUPLEX", pt1, FONT_HERSHEY_DUPLEX, 2, olive);
	//putText(image, "TRIPLEX", pt2, FONT_HERSHEY_TRIPLEX, 3, violet);
	//putText(image, "ITALIC", pt3, FONT_HERSHEY_PLAIN | FONT_ITALIC, 2, violet);
	//
	//imshow("putText", image);
	//waitKey();
	
	
	
	//Scalar orange(0, 165, 255), blue(255, 0, 0), magenta(255, 0, 255);
	//Mat image(300, 500, CV_8UC3, Scalar(255, 255, 255));

	//Point center = (Point)image.size() / 2;
	//Point pt1(70, 50), pt2(350, 220);

	//circle(image, center, 100, blue);
	//circle(image, pt1, 80, orange, 2);
	//circle(image, pt2, 60, magenta, -1);

	//int font = FONT_HERSHEY_COMPLEX;
	//putText(image, "center_blue", center, font, 1.2, blue);
	//putText(image, "pt1_orange", pt1, font, 0.8, orange);
	//putText(image, "pt2_magenta", pt2 + Point(2,2), font, 0.5, Scalar(0,0,0), 2);
	//putText(image, "pt2_magenta", pt2, font, 0.5, magenta, 1);

	//imshow("원", image);
	//waitKey();




	//Mat image(300, 500, CV_8UC1, Scalar(255));
	//Point2f center(250, 150), pts[4];
	//Size2f size(300, 100);

	//RotatedRect rot_rect(center, size, 40);
	//Rect bound_rect = rot_rect.boundingRect();
	//rectangle(image, bound_rect, Scalar(0), 1);
	//circle(image, rot_rect.center, 1, Scalar(0), 2);
	//rot_rect.points(pts);
	//for (int i = 0; i < 4; i++)
	//{
	//	circle(image, pts[i], 4, Scalar(0), 1);
	//	line(image, pts[i], pts[(i + 1) % 4], Scalar(0), 2);
	//}
	//imshow("RotateRect", image);
	//waitKey(0);



	//Scalar orange(0, 165, 255), blue(255, 0, 0), magenta(255, 0, 255);
	//Mat image(300, 700, CV_8UC3, Scalar(255, 255, 255));

	//Point pt1(120, 150), pt2(550, 150);
	//circle(image, pt1, 1, Scalar(0), 1);
	//circle(image, pt2, 1, Scalar(0), 1);

	//ellipse(image, pt1, Size(100, 60), 0, 0, 360, orange, 2);
	//ellipse(image, pt1, Size(100, 60), 0, 30, 270, blue, 4);

	//ellipse(image, pt2, Size(100, 60), 30, 0, 360, orange, 2);
	////ellipse(image, pt2, Size(100, 60), 30, -30, 160, blue, 4); 	// start가 end보다 작으면 시계방향으로 그린다
	//ellipse(image, pt2, Size(100, 60), 30, 330, 160, blue, 4);		// start가 end보다 크면 반시계방향으로 그린다

	//imshow("타원", image);
	//waitKey();


	
	//image = Mat(300, 500, CV_8UC1, Scalar(255));
	//imshow(title, image);
	//setMouseCallback(title, onMouse3, 0);
	//waitKey();



	//string filename = "image/snowy-mountain-gray-srgb.jpg";
	//Mat gray2gray = imread(filename, IMREAD_GRAYSCALE);
	//Mat gray2color = imread(filename, IMREAD_COLOR);
	//CV_Assert(gray2gray.data && gray2color.data);

	//Rect roi(100, 100, 1, 1);
	//cout << "행렬좌표(100,100) 화소값" << endl;
	//cout << "gray2gray" << gray2gray(roi) << endl;
	//cout << "gray2color" << gray2color(roi) << endl;

	//print_matInfo("gray2gray", gray2gray);
	//print_matInfo("gray2color", gray2color);
	//imshow("gray2gray", gray2gray);
	//imshow("gray2color", gray2color);
	//waitKey();



	//string filename = "image/images.jpg";
	//Mat gray2gray = imread(filename, IMREAD_GRAYSCALE);
	//Mat gray2color = imread(filename, IMREAD_COLOR);
	//CV_Assert(gray2gray.data && gray2color.data);

	//Rect roi(100, 100, 1, 1);
	//cout << "행렬좌표(100,100) 화소값" << endl;
	//cout << "gray2gray" << gray2gray(roi) << endl;
	//cout << "gray2color" << gray2color(roi) << endl;

	//print_matInfo("gray2gray", gray2gray);
	//print_matInfo("gray2color", gray2color);
	//imshow("gray2gray", gray2gray);
	//imshow("gray2color", gray2color);
	//waitKey();




	//string filename1 = "image/example_16.tif";
	//string filename2 = "image/example_32.tif";
	//Mat color2unchanged1 = imread(filename1, IMREAD_UNCHANGED);
	//Mat color2unchanged2 = imread(filename2, IMREAD_UNCHANGED);
	//CV_Assert(color2unchanged1.data);
	//CV_Assert(color2unchanged2.data);

	//Rect roi(100, 100, 1, 1);
	//cout << "16/32 행렬좌표(100,100) 화소값" << endl;
	//cout << "color2unchanged1" << color2unchanged1(roi) << endl;
	//cout << "color2unchanged2" << color2unchanged2(roi) << endl;

	//print_matInfo("color2unchanged1", color2unchanged1);
	//print_matInfo("color2unchanged2", color2unchanged2);
	//imshow("color2unchanged1", color2unchanged1);
	//imshow("color2unchanged2", color2unchanged2);
	//waitKey();


	//Mat image = imread("image/images.jpg", IMREAD_COLOR);
	//CV_Assert(image.data);

	//vector<int> param_jpg, param_png;
	//param_jpg.push_back(IMWRITE_JPEG_QUALITY);
	//param_jpg.push_back(50);

	//param_png.push_back(IMWRITE_PNG_COMPRESSION);
	//param_png.push_back(9);

	//imwrite("image/write_test1.jpg", image);
	//imwrite("image/write_test2.jpg", image, param_jpg);

	//imwrite("image/write_test.png", image, param_png);
	//imwrite("image/write_test.png", image);



	//Mat img8 = imread("image/images.jpg");
	//CV_Assert(img8.data);

	//Mat img16, img32;
	//img8.convertTo(img16, CV_16U, 65535 / 255.0);
	//img8.convertTo(img32, CV_32F, 1 / 255.0);

	//Rect roi(10, 10, 3, 3);
	//cout << "img8 행렬의 일부" << endl << img8(roi) << endl << endl;
	//cout << "im168 행렬의 일부" << endl << img16(roi) << endl << endl;
	//cout << "img32 행렬의 일부" << endl << img32(roi) << endl << endl;

	//imwrite("image/write_test_16.tif", img16);
	//imwrite("image/write_test_32.tif", img32);

	//imshow("img16", img16);
	//imshow("img32", img32);
	//waitKey();



	//VideoCapture capture(0);
	//if (!capture.isOpened())
	//{
	//	cout << "카메라 연결하세요" << endl;
	//	return 0;
	//}

	//cout << "너비" << capture.get(CAP_PROP_FRAME_WIDTH) << endl;
	//cout << "높이" << capture.get(CAP_PROP_FRAME_HEIGHT) << endl;
	//cout << "노출" << capture.get(CAP_PROP_EXPOSURE) << endl;
	//cout << "밝기" << capture.get(CAP_PROP_BRIGHTNESS) << endl;

	//while (true)
	//{
	//	Mat frame;
	//	capture.read(frame);

	//	put_string(frame, "EXPOS: ", Point(10, 40), capture.get(CAP_PROP_EXPOSURE));
	//	imshow("카메라 영상", frame);
	//	if (waitKey(30) >= 0)
	//		break;
	//}



	VideoCapture capture;
	capture.open("image/video-sample.avi");
	CV_Assert(capture.isOpened());

	double fps = capture.get(CV_CAP_PROP_FPS);
	int delay = 1000 / fps;
	int frame_cnt = 0;
	Mat frame;

	while (capture.read(frame))
	{
		if (waitKey(delay) >= 0)
			break;

		frame_cnt = capture.get(CV_CAP_PROP_POS_FRAMES);
		if (frame_cnt < 100)
			;
		else if (frame_cnt < 200)
			frame -= Scalar(0, 0, 100);
		else if (frame_cnt < 300)
			frame -= Scalar(100, 0, 0);
		else if (frame_cnt < 400)
			frame *= 1.5;
		else if (frame_cnt < 500)
			frame *= 0.5;
		
		put_string(frame, "frame_cnt", Point(20, 50), frame_cnt);

		imshow("동영상", frame);
	}

	return 0;
}

void onMouse(int mouseEvent, int x, int y , int flags, void* param)
{
	switch (mouseEvent)
	{
	case EVENT_LBUTTONDOWN:
		cout << "마우스 왼쪽버튼 누르기" << *(int*)param << endl;
		break;
	case EVENT_RBUTTONDOWN:
		cout << "마우스 오른쪽버튼 누르기" << endl;
		break;
	case EVENT_RBUTTONUP:
		cout << "마우스 오른쪽버튼 떼기" << endl;
		break;
	case EVENT_LBUTTONDBLCLK:
		cout << "마우스 왼쪽버튼 더블클릭" << endl;
		break;
	default:
		break;
	}
}

void onChange(int value, void* userData)
{
	int add_value = value - 130;
	cout << "추가 화소값" << add_value << endl;

	Mat tmp = image + add_value;
	imshow(title, tmp);
}

void onMouse2(int mouseEvent, int x, int y, int flags, void* param)
{
	if (mouseEvent == EVENT_RBUTTONDOWN)
		add(image, 10, image);
	else if (mouseEvent == EVENT_LBUTTONDOWN)
		subtract(image, 10, image);
	setTrackbarPos(bar_name, title, image.at<uchar>(0, 0));
	imshow(title, image);
}

void onMouse3(int mouseEvent, int x, int y, int flags, void* param)
{
	static Point pt(-1, -1);

	switch (mouseEvent)
	{
	case EVENT_LBUTTONDOWN:
		if (pt.x < 0)
			pt = Point(x, y);
		else
		{
			rectangle(image, pt, Point(x, y), Scalar(50), 2);
			imshow(title, image);
			pt = Point(-1, -1);
		}
		break;
	case EVENT_RBUTTONDOWN:
		if (pt.x < 0)
			pt = Point(x, y);
		else
		{
			Point2d pt2 = pt - Point(x, y);
			int radius = (int)sqrt(pt2.x * pt2.x + pt2.y * pt2.y);
			circle(image, pt, radius, Scalar(150), 2);

			imshow(title, image);
			pt = Point(-1, -1);
		}
		break;
	default:
		break;
	}
}

void print_matInfo(string name, Mat m)
{
	String mat_type;
	int depth = m.depth();
	switch (depth)
	{
	case CV_8U:
		mat_type = "CV_8U";
		break;
	case CV_8S:
		mat_type = "CV_8S";
		break;
	case CV_16U:
		mat_type = "CV_16U";
		break;
	case CV_16S:
		mat_type = "CV_16S";
		break;
	case CV_32S:
		mat_type = "CV_32S";
		break;
	case CV_32F:
		mat_type = "CV_32F";
		break;
	case CV_64F:
		mat_type = "CV_64F";
		break;
	default:
		break;
	}

	cout << name;
	cout << format(": depth(%d) channels(%d) -> 자료형: ", depth, m.channels());
	cout << mat_type << "C" << m.channels() << endl;
}

void put_string(Mat& frame, string text, Point pt, int value)
{
	text += to_string(value);
	Point shade = pt + Point(2, 2);
	int font = FONT_HERSHEY_SIMPLEX;
	putText(frame, text, shade, font, 0.7, Scalar(0, 0, 0), 2);
	putText(frame, text, pt, font, 0.7, Scalar(120, 200, 90), 2);
}