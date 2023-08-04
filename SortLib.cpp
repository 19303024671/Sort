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
	return ps;
}



ImgInfo::ImgInfo(const string& path, const CCTColor& color, int N, const vector<int>& save)
	: path(path), color(color), N(N), save(save)
{
}
