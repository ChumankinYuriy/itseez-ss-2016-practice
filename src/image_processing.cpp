#pragma once
#include "image_processing.hpp"

using namespace std;
using namespace cv;

Mat ImageProcessorImpl::CvtColor(const cv::Mat &src, const cv::Rect &roi) {
	Mat src_copy = src.clone();
	Mat src_copy_roi = src_copy(roi);
	Mat dst_gray_roi;
	cvtColor(src_copy_roi, dst_gray_roi, CV_BGR2GRAY);
	vector<Mat> channels(src.channels(), dst_gray_roi);
	Mat dst_roi;
	merge(channels, dst_roi);
	dst_roi.copyTo(src_copy_roi);
	return src_copy;
}

Mat ImageProcessorImpl::Filter(const cv::Mat &src, const cv::Rect &roi,
	const int kSize) {
	Mat src_copy = src.clone();
	Mat src_copy_roi = src_copy(roi);
	medianBlur(src_copy_roi, src_copy_roi, kSize);
	return src_copy;
}

Mat ImageProcessorImpl::DetectEdges(const cv::Mat &src, const cv::Rect &roi,
	const int filterSize, const int lowThreshold, const int ratio,
	const int kernelSize) {
	Mat src_roi = src.clone()(roi);
	Mat src_gray_roi;
	cvtColor(src_roi, src_gray_roi, CV_BGR2GRAY);
	Mat gray_blurred;
	blur(src_gray_roi, gray_blurred, Size(filterSize, filterSize));
	Mat detected_edges;
	Canny(gray_blurred, detected_edges, lowThreshold, lowThreshold * ratio);
	Mat dst = src.clone();
	Mat dst_roi = dst(roi);
	dst_roi.setTo(Scalar::all(0));
	src_roi.copyTo(dst_roi, detected_edges);
	return dst;

	/*�������� ���������� src_roi �� ����� src.
		��������������� ������� src_roi � ������� ������, ��������� �������� � ������� src_gray_roi.
		������������� src_gray_roi � �������������� ��������� �������, ��������� �������� � ������� gray_blurred.����������: ��� ���������� ����� ������������ ������� blur.
		��������� ����� detected_edges �� ����������� gray_blurred � ������� ������� Canny.
		������� ������� dst.
		����������� ����������� src � dst.
		�������� ���������� dst_roi �� dst � ������������ � �������� roi.
		�������� ��� �������� � ���������� dst_roi.���������� : ���������� ������������ ����������� ����� all ������ Scalar.
		����������� src_roi � dst_roi � ������������ � ������ detected_edges.
		������� dst.*/

}

Mat ImageProcessorImpl::Pixelize(const cv::Mat &src, const cv::Rect &roi,
		const int kDivs) {
	return src;
}