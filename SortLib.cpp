#include "SortLib.h"

Points::Points(const Points& points_)
{
	this->cal_pos = points_.cal_pos;
	this->scan_pos = points_.scan_pos;
}

ImgInfo::ImgInfo(const string& path_)
{
	this->path = path_;
}

ImgInfo::ImgInfo(const ImgInfo& img_info_)
{
	this->color = img_info_.color;
	this->path = img_info_.path;
	this->N = img_info_.N;
	this->save = img_info_.save;
}

vector<Points> GetPoints(const ImgInfo& img_info)
{
	vector<Points> ps;
	DetectCCTInfo info(img_info.path, img_info.color, img_info.N, img_info.save);
	vector<Result>result = DecodeCCT(info);
	if (result.empty()) return vector<Points>();
	set<int>temp;
	for (const auto& r : result)temp.insert(r.index);
	if (temp.size() != 4) return vector<Points>();
	for (const auto& r : result)
	{
		if (r.index == img_info.save[0])
			ps.push_back(Points(r.pos, cv::Point(750, 550)));
		if (r.index == img_info.save[1])
			ps.push_back(Points(r.pos, cv::Point(750, 950)));
		if (r.index == img_info.save[2])
			ps.push_back(Points(r.pos, cv::Point(1350, 550)));
		if (r.index == img_info.save[3])
			ps.push_back(Points(r.pos, cv::Point(1350, 950)));
	}
	if(ps.size()!=4) return vector<Points>();
	return ps;
}

cv::Mat TranImg(const ImgInfo& img_info)
{
	cv::Mat input_img = ReadImg(img_info.path);
	vector<Points>ps = GetPoints(img_info);
	if (ps.empty())
	{
		cerr << img_info.path << "矫正失败！" << endl;
		return cv::Mat();
	}
	if (input_img.empty())
	{
		cerr << img_info.path << "矫正失败！" << endl;
		return cv::Mat();
	}
	vector<cv::Point2f>input;
	vector<cv::Point2f>output;
	for (const auto& p : ps)
	{
		input.push_back(p.scan_pos);
		output.push_back(p.cal_pos);
	}
	cv::Mat matrix = cv::getPerspectiveTransform(input, output);
	cv::Mat tran_img;
	cv::warpPerspective(input_img, tran_img, matrix, cv::Size(int(1.5*input_img.cols), int(1.5*input_img.rows)));
	string save_file_path = img_info.path;
	save_file_path = save_file_path.replace(save_file_path.find("test_img"), 8, "sort_img");
	cv::imwrite(save_file_path, tran_img);
	cout << img_info.path << "矫正成功！" << endl;
	return tran_img;
}

void ShowImg(const cv::Mat& img, const string& win_name, const cv::Size& win_size)
{
	if (img.empty())
	{
		cerr << "图像为空，无法展示！" << endl;
		return;
	}
	cv::namedWindow(win_name, cv::WINDOW_NORMAL);
	cv::imshow(win_name, img);
	cv::resizeWindow(win_name, win_size);
	cv::waitKey(0);
}

ImgInfo::ImgInfo(const string& path, const CCTColor& color, int N, const vector<int>& save)
	: path(path), color(color), N(N), save(save)
{
}
