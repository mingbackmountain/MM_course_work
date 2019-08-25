#include <iostream>
#include <opencv2/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define s 2
#define e 4

using namespace cv;
using namespace std;

//Class Act 1
//int main() {
//
//    int frameCounter = 0;
//
//    VideoCapture cap("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/test.avi");
//    if (!cap.isOpened()) {
//        return -1;
//    }
//
//    // Video property
//    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
//    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
//    int frame_rate = cap.get(CV_CAP_PROP_FPS);
//    VideoWriter video("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/video2.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25, Size(frame_width, frame_height), true);
//
//    while (1) {
//
//        frameCounter++;
//
//        Mat frame;
//        cap >> frame;
//        if (frame.empty())
//            break;
//
//        if (frameCounter >= s * 25 && frameCounter < e * 25) {
//            video.write(frame);
//        }
//
//    }
//    cap.release();
//    destroyAllWindows();
//
//}

//Lab11
//void mouse_callback(int event,int x,int y,int flag,void *param){
//    Mat* rgb = (Mat*) param;
//    if(event == EVENT_LBUTTONDOWN){
//        printf("X = %d Y = %d: Blue = %d, Green = %d, Red = %d \n",x,y,(int)(*rgb).at<Vec3b>(y,x)[0],(int)(*rgb).at<Vec3b>(y,x)[1],(int)(*rgb).at<Vec3b>(y,x)[2]);
//    }
//}
//
//int main () {
//    Mat img = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/color_img.jpg");
//    if(img.empty()){
//        cout << "Error loading the image" << endl;
//        return -1;
//    }
//
//    namedWindow("Test",1);
//    setMouseCallback("Test", mouse_callback,&img);
//    imshow("Test",img);
//    waitKey(0);
//
//    return 0;
//}

//Lab12

//int main(){
//    Mat img = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/test.jpg");
//    namedWindow("Input");
//    imshow("Input",img);
//
//    Mat sobel_x,sobel_y;
//    Mat abs_sobel_x, abs_sobel_y;
//
//    Mat img_gray;
//    cvtColor(img, img_gray, CV_BGR2GRAY);
//
//    //Gradient X
//    Sobel(img_gray,sobel_x,CV_16S,1,0,3);
//    convertScaleAbs(sobel_x, abs_sobel_x);
//    namedWindow("SobelX");
//    imshow("SobelX",abs_sobel_x);
//
//    //Gradient Y
//    Sobel(img_gray,sobel_y,CV_16S,1,0,3);
//    convertScaleAbs(sobel_y, abs_sobel_y);
//    namedWindow("SobelY");
//    imshow("SobelY",abs_sobel_x);
//
//    waitKey(0);
//
//    return 0;
//}

//Class Act 3
int main(){

        Mat img = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/test.jpg");
        namedWindow("Input");
        imshow("Input",img);

        Mat sobel_x,sobel_y;
        Mat abs_sobel_x, abs_sobel_y;

        Mat img_gray;
        cvtColor(img, img_gray, CV_BGR2GRAY);

        //Gradient X
        Sobel(img_gray,sobel_x,CV_32F,1,0,3);
        convertScaleAbs(sobel_x, abs_sobel_x);
        namedWindow("SobelX");
        imshow("SobelX",abs_sobel_x);

        //Gradient Y
        Sobel(img_gray,sobel_y,CV_32F,1,0,3);
        convertScaleAbs(sobel_y, abs_sobel_y);
        namedWindow("SobelY");
        imshow("SobelY",abs_sobel_y);

        Mat1f output;
        magnitude(sobel_x, sobel_y, output);
        imshow("Output", output);

        waitKey(0);

    return 0;
}

//Lab13

//int main(){
//
//    Mat img = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/color_img.jpg",IMREAD_COLOR);
//
//    vector<Mat> img_bgr;
//    split(img, img_bgr);
//
//    int histSize = 256;
//
//    float range[] = {0,256};
//    const float* histRange = {range};
//
//    bool uniform = true;
//    bool accumulate = false;
//
//    Mat b_hist, g_hist, r_hist;
//
//    calcHist( &img_bgr[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
//    calcHist( &img_bgr[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
//    calcHist( &img_bgr[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
//
//    int hist_w = 512;
//    int hist_h = 400;
//    int bin_w = cvRound((double) hist_w/histSize);
//
//    Mat histImage(hist_h,hist_w,CV_8UC3,Scalar(0,0,0));
//
//    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
//    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
//    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
//
//    for( int i = 1; i < histSize; i++ )
//    {
//        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
//             Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
//             Scalar( 255, 0, 0), 2, 8, 0  );
//        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
//             Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
//             Scalar( 0, 255, 0), 2, 8, 0  );
//        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
//             Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
//             Scalar( 0, 0, 255), 2, 8, 0  );
//    }
//
//    namedWindow("Input",WINDOW_AUTOSIZE);
//    imshow("Input",img);
//    namedWindow("Hist",WINDOW_AUTOSIZE);
//    imshow("Hist",histImage);
//
//    waitKey(0);
//
//    return 0;
//}

//Lab14

//int main(){
//    Mat img1, hsv1;
//    Mat img2, hsv2;
//
//    img1 = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/color_img.jpg",IMREAD_COLOR);
//    img2 = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/test.jpg",IMREAD_COLOR);
//
//    cvtColor(img1, hsv1, COLOR_BGR2HSV);
//    cvtColor(img2, hsv2, COLOR_BGR2HSV);
//
//    int h_bins = 50;
//    int s_bins = 60;
//    int histSize[] = {h_bins,s_bins};
//
//    float h_ranges[] = {0,256};
//    float s_ranges[] = {0,256};
//
//    const float* ranges[] = {h_ranges,s_ranges};
//    int channels[] = {0,1};
//
//    MatND hist1;
//    MatND hist2;
//
//    calcHist( &hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges,true,false );
//    normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat() );
//
//    calcHist( &hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges,true,false );
//    normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat() );
//
//    double sim = compareHist(hist1, hist2, CV_COMP_CORREL);
//    printf("The correlation similarity is %f\n",sim);
//
//    return 0;
//}


//class Act 4
//int main(){
//    Mat img1, hsv1;
//    Mat img2, hsv2;
//    Mat img3, hsv3;
//
//    img1 = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/H1.jpg",IMREAD_COLOR);
//    img2 = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/H2.jpg",IMREAD_COLOR);
//    img3 = imread("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/H3.jpg",IMREAD_COLOR);
//
//    cvtColor(img1, hsv1, COLOR_BGR2HSV);
//    cvtColor(img2, hsv2, COLOR_BGR2HSV);
//    cvtColor(img3, hsv3, COLOR_BGR2HSV);
//
//    int h_bins = 50;
//    int s_bins = 60;
//    int histSize[] = {h_bins,s_bins};
//
//    float h_ranges[] = {0,256};
//    float s_ranges[] = {0,256};
//
//    const float* ranges[] = {h_ranges,s_ranges};
//    int channels[] = {0,1};
//
//    MatND hist1;
//    MatND hist2;
//    MatND hist3;
//
//    calcHist( &hsv1, 1, channels, Mat(), hist1, 2, histSize, ranges,true,false );
//    normalize(hist1, hist1, 0, 1, NORM_MINMAX, -1, Mat() );
//
//    calcHist( &hsv2, 1, channels, Mat(), hist2, 2, histSize, ranges,true,false );
//    normalize(hist2, hist2, 0, 1, NORM_MINMAX, -1, Mat() );
//
//    calcHist( &hsv3, 1, channels, Mat(), hist3, 2, histSize, ranges,true,false );
//    normalize(hist3, hist3, 0, 1, NORM_MINMAX, -1, Mat() );
//
//    double sim = compareHist(hist1, hist2, CV_COMP_CORREL);
//    double sim2 = compareHist(hist1, hist3, CV_COMP_CORREL);
//    
//    //If we use chi-squre simulation we can use change (sim<sim2)
//
//    if(sim>sim2){
//        printf("H1 is similar to H2 than H3 %f\n",sim);
//    }else{
//        printf("H1 is similar to H3 than H2 %f\n",sim2);
//    }
//    return 0;
//}

//Lab15

//int main(){
//    VideoCapture cap("/Users/thanakornpasangthien/Desktop/multimedia/MM_Worapan/OpenCV/OpenCV/test.avi");
//    if(!cap.isOpened()){
//        return -1;
//    }
//
//    Mat prev,diff,diff_gray;
//    cap >> prev;
//    while(1){
//        Mat cur;
//        cap >> cur;
//        if(cur.empty())
//            break;
//        absdiff(cur, prev, diff);
//        cvtColor(diff, diff_gray, COLOR_BGR2GRAY);
//        threshold(diff_gray, diff_gray, 15, 255, CV_THRESH_BINARY);
//        imshow("Frame Different",diff_gray);
//
//        prev = cur.clone();
//
//        char c = (char)waitKey(25);
//        if(c == 27)
//            break;
//    }
//    cap.release();
//    destroyAllWindows();
//
//    return 0;
//}
