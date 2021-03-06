#include "ros/ros.h"
#include "solve_equastions/SolveLines.h"
#include "stdio.h"


int main(int argc, char **argv)
{
    ros::init(argc, argv, "solve_lines_client");
    ros::NodeHandle n;
    
    ros::ServiceClient client = n.serviceClient<solve_equastions::SolveLines>("solve_two_lines");
    solve_equastions::SolveLines srv;
    
    while(ros::ok())
    {
        double a, b, c, d, e, f;
        
        std::cout << "Enter the a parametr:";
        std::cin >> a;
        
        std::cout << "Enter the b parametr:";
        std::cin >> b;
        
        std::cout << "Enter the c parametr:";
        std::cin >> c;
        
        std::cout << "Enter the d parametr:";
        std::cin >> d;
        
        std::cout << "Enter the e parametr:";
        std::cin >> e;
        
        std::cout << "Enter the f parametr:";
        std::cin >> f;
        
        srv.request.a = a;
        srv.request.b = b;
        srv.request.c = c;
        srv.request.d = d;
        srv.request.e = e;
        srv.request.f = f;
        
        if (client.call(srv))
        {
            std::cout << "Answer = " << srv.response.answer << std::endl;        
        }else{
            std::cout << "Failed to call service add_two_ints" << std::endl;
            return 1;
        }
    }

    return 0;
}
