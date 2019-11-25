#include<iostream>
#include<cctype>
#include<cstdio>
#include<stack>
using namespace std;

int main()
{
    string s;
    cin>>s;
    string ans[100];
    stack<char> op;
    int i,j,cnt=0,flag_p=0,index;
    // if(s[0]=='-') {flag_fu=1;index=1;}
    // else index=0;
    for(i=0;i<s.size();i++){
        int isnumber=0,flag_fu=0;
        if(isdigit(s[i])) isnumber=1;
        else if(i==0&&s[i]=='-') {isnumber=1; flag_fu=1;}
        else if(s[i]=='-'&&(isdigit(s[i-1])||s[i-1]=='(')) {isnumber=1; flag_fu=1;}
        if(isnumber){  //扫描到的是操作数
            // cout<<"s[i]="<<s[i]<<endl;
            if(flag_fu) ans[cnt]+=s[i],i++;
            // ans[cnt]+=s[i];
            for(;i<s.size();i++){
                if(isdigit(s[i])) ans[cnt]+=s[i];
                else if(s[i]=='.') {flag_p=1; ans[cnt]+=s[i]; }
                else break;
            }
            // cout<<"the number is"<<ans[cnt]<<endl;
            cnt++;
        }
        else if(s[i]=='(') op.push(s[i]);
        while(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'){
            if(op.size()==0||op.top()=='('){op.push(s[i]);break;}
            else if((s[i]=='*'||s[i]=='/')&&(op.top()=='+'||op.top()=='-')){
                op.push(s[i]);
                break;
            }
            else{
                ans[cnt++]=op.top();
                op.pop();
            }
        }
        if(s[i]==')'){
            while(op.top()!='('){
                ans[cnt++]=op.top();
                op.pop();
            }
            op.pop();
        }
    }
    while(op.size()!=0){
        ans[cnt++]=op.top();
        op.pop();
    }
    /*for(i=0;i<cnt;i++)
        cout<<ans[i]<<' ';
    cout<<endl;*/

    ///////////////*以下为运算操作*///////////////////////////////////
    
    stack<double> num;
    int ok=1;
    for(i=0;i<cnt;i++){
        int flag=0,flag_in_p=0; /*判断是否为数字 判断是否有小数点*/
        for(j=0;j<ans[i].size();j++){
            if(isdigit(ans[i][j])) flag=1;
            if(ans[i][j]=='.') flag_in_p=1;
        }
        // if(!isdigit(ans[i][0])) flag=0; /*第一个字符不是数字 则不是数字*/
        if(flag){   /*如果扫描到数字*/
            double number1=0.0,number2=0.0;
            if(ans[i][0]=='-') index=1;
            else index=0;
            for(j=index;ans[i][j]!='.'&&j<ans[i].size();j++)
                number1=number1*10.0+ans[i][j]-'0';
            if(flag_in_p){
                for(j=ans[i].size()-1;ans[i][j]!='.';j--)
                    number2=number2/10.0+ans[i][j]-'0';
            }
            number2/=10.0;
            if(index==0) num.push(number1+number2);
            else num.push(-(number1+number2));
            // cout<<"top="<<num.top()<<endl;
        }
        else{
            if(num.size()<2) { ok=0; break; }
            double temp;
            switch (ans[i][0]){
                case '+':
                    temp=num.top();
                    num.pop();
                    num.top()+=temp;
                    break;
                case '-':
                    temp=num.top();
                    num.pop();
                    num.top()-=temp;
                    break;
                case '*':
                    temp=num.top();
                    num.pop();
                    num.top()*=temp;
                    break;
                case '/':
                    temp=num.top();
                    num.pop();
                    num.top()/=temp;
                    break;
                default:
                    ok=0;
                    break;
            }
            if(!ok) break;
        }
    }
    // printf("%.3lf\n",num.top());
    if(num.top()==(int)num.top()&&flag_p!=1) /*整数 且之前没有小数点出现*/
        printf("%.0lf\n",num.top());
    else{
        int result=num.top()*1000;
        printf("%.3lf\n",(double)result/1000.0);
    }
    // cout<<num.top()<<endl;
    return 0;
}