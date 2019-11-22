#include <opencv2/highgui.hpp>
#include <iostream>

cv::Mat BGR2GRAY(cv::Mat image) 
{
    int height = image.rows;
    int width  = image.cols;

    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC1);
    for (int i = 0; i < height; ++ i) 
    {
        for (int j = 0; j < width; ++ j) 
        {
            out.at<uchar>(i, j) = 
                0.2126 * static_cast<float>(image.at<cv::Vec3b>(i, j)[2]) +\
                0.7152 * static_cast<float>(image.at<cv::Vec3b>(i, j)[1]) +\
                0.0722 * static_cast<float>(image.at<cv::Vec3b>(i, j)[0]);
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
    cv::Mat out = BGR2GRAY(image);

    cv::namedWindow("Input", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);
    
    cv::imshow("Input", image);
    cv::imshow("Output", out);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}