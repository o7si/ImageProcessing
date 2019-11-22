#include <opencv2/highgui.hpp>
#include <iostream>

cv::Mat BGR2GRAY(cv::Mat image)
{
    cv::Mat out = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);

    for (int i = 0; i < image.rows; ++ i)
    {
        for (int j = 0; j < image.cols; ++ j)
        {
            // Y = 0.2126 * R + 0.7152 * G + 0.0722 * B
            out.at<uchar>(i, j) =
                0.2126 * image.at<cv::Vec3b>(i, j)[2] + \
                0.7125 * image.at<cv::Vec3b>(i, j)[1] + \
                0.0722 * image.at<cv::Vec3b>(i, j)[0];
        }
    }

    return out;
}

cv::Mat GRAY2BINARIZE(cv::Mat image)
{
    double variance = 0;
    int threshold = 0;

    for (int th = 0; th <= 255; ++ th) 
    {
        int front = 0, fcount = 0;
        int back  = 0, bcount = 0;
        for (int i = 0; i < image.rows; ++ i)
        {
            for (int j = 0; j < image.cols; ++ j)
            {
                int gray = image.at<uchar>(i, j);
                if (gray < th) 
                {
                    front += gray;
                    ++ fcount;
                }
                else
                {
                    back += gray;
                    ++ bcount;
                }
            }
        }

        double w0 = fcount * 1.0 / (image.rows * image.cols);
        double w1 = bcount * 1.0 / (image.rows * image.cols);
        double u0 = front  * 1.0 / fcount;
        double u1 = back   * 1.0 / bcount;

        int tmp = w0 * w1 * pow(u0 - u1, 2);
        if (tmp > variance)
        {
            variance = tmp;
            threshold = th;
        }
    }

    std::cout << threshold << std::endl;

    cv::Mat out = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);

    for (int i = 0; i < image.cols; ++ i)
    {
        for (int j = 0; j < image.cols; ++ j)
        {
            out.at<uchar>(i, j) = 
                image.at<uchar>(i, j) < threshold ? 0 : 255;
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