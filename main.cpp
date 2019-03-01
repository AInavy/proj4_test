#include <iostream>
#include <proj_api.h>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

int proj4_convert_WGS84_6zone_coordinate(double x, double y, double& X, double& Y);
int proj4_convert_WGS84_3zone_coordinate(double x, double y, double& X, double& Y);
int proj4_convert_6zoneGauss2WGS84(double& X, double& Y);
int proj4_convert_3zoneGauss2WGS84(double& X, double& Y);

void duantoulu_proj4_convert();
void duantoulu_had_proj4_convert();

namespace strtool
{
    string trim(const string& str)
    {
        string::size_type pos = str.find_first_not_of(' ');
        if (pos == string::npos)
        {
            return str;
        }
        string::size_type pos2 = str.find_last_not_of(' ');
        if (pos2 != string::npos)
        {
            return str.substr(pos, pos2 - pos + 1);
        }
        return str.substr(pos);
    }
    int split(const string& str, vector<string>& ret_, string sep = ",")
    {
        if (str.empty())
        {
            return 0;
        }
        string tmp;
        string::size_type pos_begin = str.find_first_not_of(sep);
        string::size_type comma_pos = 0;
        while (pos_begin != string::npos)
        {
            comma_pos = str.find(sep, pos_begin);
            if (comma_pos != string::npos)
            {
                tmp = str.substr(pos_begin, comma_pos - pos_begin);
                pos_begin = comma_pos + sep.length();
            }
            else
            {
                tmp = str.substr(pos_begin);
                pos_begin = comma_pos;
            }
            if (!tmp.empty())
            {
                ret_.push_back(tmp);
                tmp.clear();
            }
        }
        return 0;
    }
};


//CGCS2000 zone 6 gauss: +proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=20500000 +y_0=0 +ellps=GRS80 +units=m +no_defs
//CGCS2000 zone 3 gauss: +proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=39500000 +y_0=0 +ellps=GRS80 +units=m +no_defs

int main()
{
//    double x, y;
//    x = 116.21924089;
//    y = 40.08037501;
//    double X,Y;
//    proj4_convert_WGS84_6zone_coordinate(x,y,X,Y);
//    cout<<X<<","<<Y<<endl;

//    duantoulu_proj4_convert();
    duantoulu_had_proj4_convert();

    return 0;
}


int proj4_convert_WGS84_6zone_coordinate(double x, double y, double& X, double& Y)
{
    projPJ pj_merc, pj_latlong;
    if (!(pj_merc = pj_init_plus("+proj=latlong +ellps=WGS84  +datum=WGS84 +no_defs")))
        exit(1);
    if (!(pj_latlong = pj_init_plus("+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=20500000 +y_0=0 +ellps=GRS80 +units=m +no_defs")))
        exit(1);
    x = x* DEG_TO_RAD;
    y = y * DEG_TO_RAD;
    pj_transform(pj_merc, pj_latlong, 1, 1, &x, &y, NULL);
    std::cout.precision(12);
    X = x - 20000000;
    Y = y;
    pj_free(pj_merc);
    pj_free(pj_latlong);
    return 0;

}

int proj4_convert_WGS84_3zone_coordinate(double x, double y, double& X, double& Y)
{
    projPJ pj_merc, pj_latlong;
    if (!(pj_merc = pj_init_plus("+proj=latlong +ellps=WGS84  +datum=WGS84 +no_defs")))
        exit(1);
    if (!(pj_latlong = pj_init_plus("+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=39500000 +y_0=0 +ellps=GRS80 +units=m +no_defs")))
        exit(1);
    x = x* DEG_TO_RAD;
    y = y * DEG_TO_RAD;
    pj_transform(pj_merc, pj_latlong, 1, 1, &x, &y, NULL);
    std::cout.precision(12);
    X = x - 39000000;
    Y = y;
    pj_free(pj_merc);
    pj_free(pj_latlong);
    return 0;
}

int proj4_convert_6zoneGauss2WGS84(double& X, double& Y)
{
    projPJ pj_merc, pj_latlong;

    if (!(pj_merc = pj_init_plus("+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=20500000 +y_0=0 +ellps=GRS80 +units=m +no_defs")))
        exit(1);
    if (!(pj_latlong = pj_init_plus("+proj=latlong +ellps=WGS84 +datum=WGS84 +no_defs")))
        exit(1);

    pj_transform(pj_merc, pj_latlong, 1, 1, &X, &Y, NULL);
    X = X / DEG_TO_RAD;
    Y = Y / DEG_TO_RAD;

    cout<<setiosflags(ios::fixed)<<setprecision(8)<<X<<", "<<Y<<endl;
    pj_free(pj_merc);
    pj_free(pj_latlong);
    return 0;
}

int proj4_convert_3zoneGauss2WGS84(double& X, double& Y)
{
    X += 39000000;
    projPJ pj_merc, pj_latlong;

    if (!(pj_merc = pj_init_plus("+proj=tmerc +lat_0=0 +lon_0=117 +k=1 +x_0=39500000 +y_0=0 +ellps=GRS80 +units=m +no_defs")))
        exit(1);
    if (!(pj_latlong = pj_init_plus("+proj=latlong +ellps=WGS84 +datum=WGS84 +no_defs")))
        exit(1);

    pj_transform(pj_merc, pj_latlong, 1, 1, &X, &Y, NULL);
    X = X / DEG_TO_RAD;
    Y = Y / DEG_TO_RAD;

    cout<<setiosflags(ios::fixed)<<setprecision(8)<<X<<", "<<Y<<endl;
    pj_free(pj_merc);
    pj_free(pj_latlong);
    return 0;

}


void duantoulu_proj4_convert()
{
    ifstream fin("/cvg_home/home/mahj/data/断头路/captureRTK_image3.txt");
    ofstream fout("/cvg_home/home/mahj/data/断头路/captureRTK_image3_proj4_convert.txt");
    string s;

    while(getline(fin,s))
    {
        vector<string> s_vec;
        strtool::split(s,s_vec," ");
        double G = atof(s_vec[3].c_str()) / 100000000.0;
        double I = atof(s_vec[2].c_str()) / 100000000.0;

        double X, Y;
        proj4_convert_WGS84_3zone_coordinate(G, I, X, Y);


        cout<<s_vec[0]<<" "<<s_vec[1]<<" ";
        cout<<setiosflags(ios::fixed)<<setprecision(8)<<X<<" "<<Y<<" "
           <<s_vec[4]<<" "<<s_vec[6]<<" "<<s_vec[7]<<" "<<s_vec[8]<<endl;

        fout<<s_vec[0]<<" "<<s_vec[1]<<" ";
        fout<<setiosflags(ios::fixed)<<setprecision(8)<<X<<" "<<Y<<" "
           <<s_vec[4]<<" "<<s_vec[6]<<" "<<s_vec[7]<<" "<<s_vec[8]<<endl;

        s_vec.clear();
    }
}


void duantoulu_had_proj4_convert()
{
    ifstream fin("/home/mahj/PycharmProjects/json_parse/duantoulu_obj_filter_WGS84.txt");
    ofstream fout("/home/mahj/PycharmProjects/json_parse/duantoulu_proj4_had_convert.txt");
    string s;

    while(getline(fin,s))
    {
        vector<string> s_vec;
        strtool::split(s,s_vec," ");
        double G = atof(s_vec[0].c_str());
        double I = atof(s_vec[1].c_str());
       // cout<<G<<","<<I<<endl;
       // proj4_convert_6zoneGauss2WGS84(G, I);

        double X, Y;

        proj4_convert_WGS84_3zone_coordinate(G, I, X, Y);

        cout<<setiosflags(ios::fixed)<<setprecision(8)<<X<<" "<<Y<<" "<<s_vec[2]<<endl;
        fout<<setiosflags(ios::fixed)<<setprecision(8)<<X<<" "<<Y<<" "<<s_vec[2]<<endl;

        s_vec.clear();
    }
}


