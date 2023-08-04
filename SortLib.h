#pragma once
#include"CCTLib.h"
#include<opencv2/opencv.hpp>

//坐标对
struct Points
{
	cv::Point scan_pos;
	cv::Point cal_pos;
public:
	Points() = default;
	Points(const cv::Point& scan_pos, const cv::Point& cal_pos)
		: scan_pos(scan_pos), cal_pos(cal_pos)
	{
	}
	Points(const Points& points_);
};
//处理的图像信息
struct ImgInfo
{
	string path;//图像路径
	CCTColor color = black;//CCT颜色，默认黑色
	int N = 8;//编码位数，默认为8
	vector<int> save = { 0,3,15,63 };//需要识别的CCT编码，默认为0,3,15,63四个
public:
	ImgInfo(const string& path);
	ImgInfo(const ImgInfo& img_info_);
	ImgInfo() = default;
	ImgInfo(const string& path, const CCTColor& color, int N, const vector<int>& save);
};
//获取四个坐标以及对应的点
vector<Points> GetPoints(const ImgInfo& img_info);