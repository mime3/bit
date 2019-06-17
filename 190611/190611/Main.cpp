#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	//FileStorage fs("file/test.xml", FileStorage::WRITE);
	//string name = "홍길동";

	//fs << "name" << name;
	//fs << "age" << 21;
	//fs << "address" << "Chosun";
	//fs << "picture" << "[" << "pic1.jpg" << "pic2.jpg" << "pic3.jpg" << "]";

	//fs << "score" << "{";
	//fs << "math" << 100;
	//fs << "Java" << 90;
	//fs << "C" << 95 << "}";

	//int data[] = { 1,2,3,4,5,6 };
	//vector<int> vec(data, data + sizeof(data) / sizeof(int));
	//fs << "vector" << vec;
	//Mat m(2, 3, CV_32S, data);
	//fs << "Mat" << m;

	//Point2d pt(10.5, 200);
	//Rect rect(pt, Size(100, 200));
	//fs << "Point" << pt;
	//fs << "Rect" << rect;

	//fs.release();



	//FileStorage fs("file/test.xml", FileStorage::READ);
	//CV_Assert(fs.isOpened());

	//string name, address, picture;
	//int age;
	//fs["address"] >> address;
	//fs["name"] >> name;
	//fs["age"] >> age;

	//cout << "address " << address << endl;
	//cout << "name " << name << endl;
	//cout << "age " << age << endl;

	//FileNode node_pic = fs["picture"];
	//FileNode node_score = fs["score"];

	//try
	//{
	//	if (node_pic.type() != FileNode::SEQ)
	//		CV_Error(Error::StsError, "시퀀스 노드가 아닙니다");
	//	if (!node_score.isMap())
	//		CV_Error(Error::StsError, "매핑 노드가 아닙니다");
	//}
	//catch(Exception & e)
	//{
	//	exit(1);
	//}

	//cout << "[picture] ";
	//cout << (string)node_pic[0] << ", ";
	//cout << (string)node_pic[1] << ", ";
	//cout << (string)node_pic[2] << endl << endl;

	//cout << "[score] " << endl;
	//cout << "math " << (int)node_score["math"] << endl;
	//cout << "Java " << (int)node_score["Java"] << endl;
	//cout << "C " << (int)node_score["C"] << endl << endl;

	//Point pt;
	//Rect rect;
	//Mat mat;
	//vector<int> vec;

	//fs["vector"] >> vec;
	//fs["Point"] >> pt;
	//fs["Rect"] >> rect;
	//fs["Mat"] >> mat;

	//cout << "[vec] = " << ((Mat)vec).t() << endl;
	//cout << "[pt] = " << pt << endl;
	//cout << "[rect] = " << rect << endl << endl;
	//cout << "[mat] = " << endl << mat << endl;

	//fs.release();



	//FileStorage fs_read("file/test.xml", FileStorage::READ);
	//CV_Assert(fs_read.isOpened());

	//FileNode node_pic = fs_read["picture"];
	//vector<Mat> images;
	//for (int i = 0; i < node_pic.size(); i++)
	//{
	//	Mat tmp = imread("image/" + (string)node_pic[i], IMREAD_UNCHANGED);
	//	CV_Assert(tmp.data);
	//	images.push_back(tmp);
	//	imshow(node_pic[i], images[i]);
	//}
	//FileStorage fs_write("file/result.xml", FileStorage::WRITE);
	//CV_Assert(fs_write.isOpened());

	//vector<double> mean, dev;
	//for (int i = 0; i < images.size(); i++)
	//{
	//	string pic_name = ((string)node_pic[i]).substr(0, 4);

	//	meanStdDev(images[i], mean, dev);	// 평균과 표준편차를 벡터로 변환
	//	fs_write << pic_name + "_mean" << "[";
	//	for (int j = 0; j < mean.size(); j++)
	//	{
	//		fs_write << mean[j];
	//	}
	//	fs_write << "[";
	//	fs_write << pic_name + "_dev" << dev;
	//}

	//waitKey();
	//fs_read.release();
	//fs_write.release();




	//Mat image = imread("image/flip_test.jpg", IMREAD_COLOR);
	//CV_Assert(image.data);

	//Mat x_axis, y_axis, xy_axis, rep_img, trans_img;
	//flip(image, x_axis, 0); // x축
	//flip(image, y_axis, 1); // y축(양수)
	//flip(image, xy_axis, -1); // 원점(음수)

	//repeat(image, 1, 2, rep_img);
	////(InputArray src, int ny(vertical), int nx(horizontal) OutputArray dst)
	//transpose(image, trans_img);

	//imshow("imshow", image);
	//imshow("x_axis", x_axis);
	//imshow("y_axis", y_axis);
	//imshow("xy_axis", xy_axis);
	//imshow("rep_img", rep_img);
	//imshow("trans_img", trans_img);
	//waitKey();



	//Mat ch0(3, 4, CV_8U, Scalar(10));
	//Mat ch1(3, 4, CV_8U, Scalar(20));
	//Mat ch2(3, 4, CV_8U, Scalar(30));

	//Mat bgr_arr[] = { ch0, ch1, ch2 };
	//Mat bgr;
	//merge(bgr_arr, 3, bgr);
	//vector<Mat> bgr_vec;
	//split(bgr, bgr_vec);

	//cout << "[ch0] = " << endl << ch0 << endl;
	//cout << "[ch1] = " << endl << ch0 << endl;
	//cout << "[ch2] = " << endl << ch0 << endl << endl;

	//cout << "[bgr] = " << endl << bgr << endl << endl;
	//cout << "[bgr_vec[0]] = " << endl << bgr_vec[0] << endl;
	//cout << "[bgr_vec[1]] = " << endl << bgr_vec[1] << endl;
	//cout << "[bgr_vec[2]] = " << endl << bgr_vec[2] << endl;



	//Mat image = imread("image/color.jpg", IMREAD_COLOR);
	//CV_Assert(image.data);

	//Mat bgr[3];
	//split(image, bgr);

	//imshow("image", image);
	//imshow("blue channel", bgr[0]);
	//imshow("green channel", bgr[1]);
	//imshow("red channel", bgr[2]);
	//waitKey();



	//Mat ch0(3, 4, CV_8U, Scalar(10));
	//Mat ch1(3, 4, CV_8U, Scalar(20));
	//Mat ch2(3, 4, CV_8U, Scalar(30));
	//Mat ch_012;

	//vector<Mat> vec_012;
	//vec_012.push_back(ch0);
	//vec_012.push_back(ch1);
	//vec_012.push_back(ch2);
	//merge(vec_012, ch_012);

	//Mat ch_13(ch_012.size(), CV_8UC2);
	//Mat ch_2(ch_012.size(), CV_8UC1);
	//Mat out[] = { ch_13, ch_2 };
	//int from_to[] = { 0,0,2,1,1,2 };
	//mixChannels(&ch_012, 1, out, 2, from_to, 3);

	//cout << "[cd_123] =	" << endl << ch_012 << endl << endl;
	//cout << "[ch_13] =	" << endl << ch_13 << endl;
	//cout << "[ch_2] =	" << endl << ch_2 << endl;



	//Mat m1(3, 6, CV_8UC1, Scalar(10));
	//Mat m2(3, 6, CV_8UC1, Scalar(50));
	//Mat m_add1, m_add2, m_sub, m_div1, m_div2;
	//Mat mask(m1.size(), CV_8UC1, Scalar(0));
	//
	//Rect rect(Point(3, 0), Size(3, 3));
	//mask(rect).setTo(1);

	//add(m1, m2, m_add1);
	//add(m1, m2, m_add2, mask);

	//divide(m1, m2, m_div1);
	//m1.convertTo(m1, CV_32F);
	//m2.convertTo(m2, CV_32F);
	//divide(m1, m2, m_div2);

	//cout << "[m1] = " << endl << m1 << endl;
	//cout << "[m2] = " << endl << m2 << endl;
	//cout << "[mask] = " << endl << mask << endl << endl;

	//cout << "[m_add1] = " << endl << m_add1 << endl;
	//cout << "[m_add2] = " << endl << m_add2 << endl;
	//cout << "[m_div1] = " << endl << m_div1 << endl;
	//cout << "[m_div2] = " << endl << m_div2 << endl;



	//vector<float> v1, v_exp, v_log;
	//Matx<float, 1, 5> m1(1, 2, 3, 5, 10);
	//Mat m_exp, m_sqrt, m_pow;
	//v1.push_back(1);
	//v1.push_back(2);
	//v1.push_back(3);

	//exp(v1, v_exp);
	//exp(m1, m_exp);
	//log(m1, v_log);
	//sqrt(m1, m_sqrt);
	//pow(m1, 3, m_pow);

	//cout << "[m1] = " << m1 << endl << endl;
	//cout << "[v_exp] = " << ((Mat)v_exp).reshape(1, 1) << endl;
	//cout << "[m_exp] = " << m_exp << endl;
	//cout << "[v_log] = " << ((Mat)v_log).reshape(1, 1) << endl << endl;

	//cout << "[m_sqrt] = " << m_sqrt << endl;
	//cout << "[m_pow] = " << m_pow << endl;


	//
	//float data1[] = { 1,2,3,5,10 };
	//float data2[] = { 2,5,7,2,9 };
	//vector<float> x_vec(data1, data1 + sizeof(data1) / sizeof(float));
	//vector<float> y_vec(data2, data2 + sizeof(data2) / sizeof(float));

	//vector<float> v_mag, v_ang;
	//magnitude(x_vec, y_vec, v_mag); // 거리 계산
	//phase(x_vec, y_vec, v_ang, true); // 각도 계산 (true:dgree, false:radian)

	//Mat m_mag, m_ang, x_mat, y_mat;
	//cartToPolar(x_vec, y_vec, m_mag, m_ang); // 거리 + 각도 계산
	//polarToCart(m_mag, m_ang, x_mat, y_mat); // 거리와 각도로 벡터 계산

	//cout << "[x_vec] = " << ((Mat)x_vec).reshape(1, 1) << endl;
	//cout << "[y_vec] = " << ((Mat)y_vec).reshape(1, 1) << endl;
	//cout << "[v_mag] = " << ((Mat)v_mag).reshape(1, 1) << endl;
	//cout << "[v_ang] = " << ((Mat)v_ang).reshape(1, 1) << endl;

	//cout << "[m_mag] = " << m_mag << endl;
	//cout << "[m_ang] = " << m_ang << endl;
	//cout << "[x_mat] = " << x_mat << endl;
	//cout << "[y_mat] = " << y_mat << endl;




	//Mat image1(300, 300, CV_8U, Scalar(0));
	//Mat image2(300, 300, CV_8U, Scalar(0));
	//Mat image3, image4, image5, image6;

	//Point center = image1.size() / 2;
	//circle(image1, center, 100, Scalar(255), -1);
	//rectangle(image2, Point(0, 0), Point(150, 300), Scalar(255), -1);

	//bitwise_or(image1, image2, image3);
	//bitwise_and(image1, image2, image4);
	//bitwise_xor(image1, image2, image5);
	//bitwise_not(image1, image6);

	//imshow("image1", image1);
	//imshow("image2", image2);
	//imshow("image3", image3);
	//imshow("image4", image4);
	//imshow("image5", image5);
	//imshow("image6", image6);
	//waitKey();




	//Mat image = imread("image/pic1.jpg", IMREAD_COLOR);
	//Mat logo = imread("image/logo.jpg", IMREAD_COLOR);
	//Mat logo_th, masks[5], background, foreground, dst;
	//CV_Assert(image.data, && logo.data);

	//threshold(logo, logo_th, 70, 255, THRESH_BINARY); // 70이하 0 나머지 255
	//split(logo_th, masks);

	//bitwise_or(masks[0], masks[1], masks[3]);
	//bitwise_or(masks[2], masks[3], masks[3]);
	//bitwise_not(masks[3], masks[4]);

	//imshow("a", masks[4]);
	//waitKey();

	//Point center1 = image.size() / 2;
	//Point center2 = logo.size() / 2;
	//Point start = center1 - center2;
	//Rect roi(start, logo.size());

	//bitwise_and(logo, logo, foreground, masks[3]);
	//bitwise_and(image(roi), image(roi), background, masks[4]);

	//add(background, foreground, dst);
	//dst.copyTo(image(roi));


	//imshow("background", background);
	//imshow("foreground", foreground);
	//imshow("dst", dst);
	//imshow("image", image);
	//waitKey();



	//uchar data[] =
	//{
	//	10,200,5,7,9,
	//	15,35,60,80,170,
	//	100,2,55,37,70
	//};
	//Mat m1(3, 5, CV_8U, data);
	//Mat m2(3, 5, CV_8U, Scalar(50));
	//Mat m_min, m_max;
	//double minVal, maxVal;
	//int minIdx[2] = {}, maxIdx[2] = {};
	//Point minLoc, maxLoc;

	//min(m1, 30, m_min);
	//max(m1, m2, m_max);
	//minMaxIdx(m1, &minVal, &maxVal, minIdx, maxIdx);
	//minMaxLoc(m1, 0, 0, &minLoc, &maxLoc);

	//cout << "[m1] =" << endl << m1 << endl;
	//cout << "[m_min] =" << endl << m_min << endl;
	//cout << "[m_max] =" << endl << m_max << endl;

	//cout << "m1 행렬 원소 최소값 : " << minVal << endl;
	//cout << "m1 행렬 원소 최소값 좌표 : " << minIdx[1] << ", " << minIdx[0] << endl;

	//cout << "m1 행렬 원소 최대값 : " << maxVal << endl;
	//cout << "m1 행렬 원소 최대값 좌표 : " << maxIdx[1] << ", " << maxIdx[0] << endl;

	//cout << "m1 행렬 최소값 좌표 : " << minLoc << endl;
	//cout << "m1 행렬 최대값 좌표 : " << maxLoc << endl;




	//Mat image = imread("image/minMax.jpg", IMREAD_GRAYSCALE);
	//double minVal, maxVal;
	//minMaxIdx(image, &minVal, &maxVal);

	//double ratio = (maxVal - minVal) / 255.0;
	//Mat dst = (image - minVal) / ratio * 2;

	//cout << "최소값 = " << minVal << endl;
	//cout << "최대값 = " << maxVal << endl;

	//imshow("image", image);
	//imshow("dst", dst);
	//waitKey();



	Matx23f src1(1, 2, 3, 4, 5, 1);
	Matx23f src2(5, 4, 2, 3, 2, 1);
	Matx32f src3(5, 4, 2, 3, 2, 1);
	Mat dst1, dst2, dst3;
	double alpha = 1.0, beta = 1.0;

	gemm(src1, src2, alpha, Mat(), beta, dst1, GEMM_1_T);					// transposes src1
	// dst1 = alpha * (src1)(src2) + beta * Mat() // 행렬곱, 가중치기능		  
	gemm(src1, src2, alpha, noArray(), beta, dst2, GEMM_2_T);				//transposes src2
	gemm(src1, src3, alpha, noArray(), beta, dst3);

	cout << "[src1] = " << endl << src1 << endl;
	cout << "[src2] = " << endl << src2 << endl;
	cout << "[src3] = " << endl << src3 << endl << endl;

	cout << "[dst1] = " << endl << dst1 << endl;
	cout << "[dst2] = " << endl << dst2 << endl;
	cout << "[dst3] = " << endl << dst3 << endl;


	return 0;
}