#include <opencv2/highgui.hpp>
#include <iostream>

cv::Mat BGR2GRAY(cv::Mat image) 
{
    cv::Mat out = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);

    for (int i = 0; i < image.rows; ++ i)
    {
        for (int j = 0; j < image.cols; ++ j)
        {
            // Y= 0.2126 R + 0.7152 G + 0.0722 B
            out.at<uchar>(i, j) =  
                0.2126 * image.at<cv::Vec3b>(i, j)[2] + \
                0.7152 * image.at<cv::Vec3b>(i, j)[1] + \
                0.0722 * image.at<cv::Vec3b>(i, j)[0];
        }
    }

    return out;
}

cv::Mat GRAY2BINARIZE(cv::Mat grayimage)
{
    cv::Mat out = cv::Mat::zeros(grayimage.rows, grayimage.cols, CV_8UC1);

    for (int i = 0; i < grayimage.rows; ++ i)
    {
        for (int j = 0; j < grayimage.cols; ++ j)
        {
            out.at<uchar>(i, j) = 
                grayimage.at<uchar>(i, j) < 128 ? 0 : 255;
        }
    }

    return out;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Params is error!" << std::endl;
        return EXIT_FAILURE;
    }

    cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
    cv::Mat grayimage = BGR2GRAY(image);
    cv::Mat binarizeimage = GRAY2BINARIZE(grayimage);

    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("GrayImage", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("BinarizeImage", cv::WINDOW_AUTOSIZE);

    cv::imshow("Image", image);
    cv::imshow("GrayImage", grayimage);
    cv::imshow("BinarizeImage", binarizeimage);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return EXIT_SUCCESS;
}