#include "ros/ros.h"
#include "solve_equastions/SolveLines.h"
#include "stdio.h"
#include <string>


std::string form_answer(double x_ans, double y_ans)
{
    char bubble[100];
    sprintf(bubble, "x = %.2f, y = %.2f", x_ans, y_ans);
    
    return bubble; // I know about C++11, I know how to turn it on as well
}


bool solve(solve_equastions::SolveLines::Request  &req,
           solve_equastions::SolveLines::Response &res)
{
    // a*x + b*y = c
    // d*x + e*y = f
    // let's find x and y
    
    double a = req.a;
    double b = req.b;
    double c = req.c;
    double d = req.d;
    double e = req.e;
    double f = req.f;
    
    if ((b != 0) && (e != 0)){
        double k1 = -a/b;
        double k2 = -d/e;
        
        double b1 = c/b;
        double b2 = f/e;
        
        if ((k1 == k2) && (b1 == b2)){
            res.answer = "infinite number of solutions";
        }else if (k1 == k2){
            res.answer = "no solutions";
        }else{
            double x_ans = (b2 - b1)/(k1 - k2);
            double y_ans = k1*x_ans + b1;
            
            res.answer = form_answer(x_ans, y_ans);
        }
    }else if ((b == 0) && (e != 0)){
        if (a == 0){
            res.answer = "no solutions";
        }else{
            double x_ans = c/a;
            double y_ans = f/e - (d/e)*x_ans;
            
            res.answer = form_answer(x_ans, y_ans);
        }
    }else if ((b != 0) && (e == 0)){
        if (d == 0){
            res.answer = "no solutions";
        }else{
            double x_ans = f/d;
            double y_ans = c/b - (a/b)*x_ans;
            
            res.answer = form_answer(x_ans, y_ans);
        }
    }else{
        res.answer = "no solutions";
    }
        
    std::cout << "request:  a = " << req.a << ", " <<
                           "b = " << req.b << ", " <<
                           "c = " << req.c << ", " <<
                           "d = " << req.d << ", " <<
                           "e = " << req.e << ", " <<
                           "f = " << req.f << std::endl;
    
    std::cout << "response: [" << res.answer << "]" << std::endl;
    
    return true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "solve_lines_server");
    ros::NodeHandle n;
    
    ros::ServiceServer service = n.advertiseService("solve_two_lines", solve);
    ROS_INFO("ready to solve two lines");
    ros::spin();

    return 0;
}
