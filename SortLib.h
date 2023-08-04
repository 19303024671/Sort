#pragma once
#include"CCTLib.h"
#include<opencv2/opencv.hpp>

//�����
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
//�����ͼ����Ϣ
struct ImgInfo
{
	string path;//ͼ��·��
	CCTColor color = black;//CCT��ɫ��Ĭ�Ϻ�ɫ
	int N = 8;//����λ����Ĭ��Ϊ8
	vector<int> save = { 0,3,15,63 };//��Ҫʶ���CCT���룬Ĭ��Ϊ0,3,15,63�ĸ�
public:
	ImgInfo(const string& path);
	ImgInfo(const ImgInfo& img_info_);
	ImgInfo() = default;
	ImgInfo(const string& path, const CCTColor& color, int N, const vector<int>& save);
};
//��ȡ�ĸ������Լ���Ӧ�ĵ�
vector<Points> GetPoints(const ImgInfo& img_info);
//����任
cv::Mat TranImg(const cv::Mat& input_img, const vector<Points>& ps);