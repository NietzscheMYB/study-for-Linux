#include"tcp_client.hpp"
#include<jsoncpp/json/json.h>

int main()
{
    //1.创建一个tcp客户端
    TcpClient client;
    bool ret=client.Connect("127.0.0.1",9090);
    if(!ret)
    {
        printf("connect failed!\n");
        return 1;
    }
    //2.循环从标准输入读入数据
    while(true)
    {
        printf("请输入两个操作数和一个操作符：");
        fflush(stdout);
        int num1,num2;
        char op[10]={0};
        scanf("%d %d %s",&num1,&num2,op);
        //3.根据用户输入的内容，构造一个Json对象
        Json::Value req_json;
        req_json["num1"]=num1;
        req_json["num2"]=num2;
        req_json["op"]=op;

        //4.把Json对象序列化成一个字符串
        
        Json::StyledWriter writer;  //变成多行显示！！！！
        //Json::FastWriter writer;
        std::string req=writer.write(req_json);
        printf("req:%s\n",req.c_str());

        //5.把字符串发送到服务器端
        client.Send(req);
        //6.从服务器读取返回的结果
        std::string resp;
        client.Recv(&resp);
        //7.把服务器返回结果再进行Json解析
        Json::Reader reader;
        Json::Value resp_json;
        reader.parse(resp,resp_json);
        printf("result:%d\n",resp_json["result"].asInt());///百分百用
    }
    return 0;
}