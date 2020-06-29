#include <bits/stdc++.h>
#define pdd pair<double, double> 
using namespace std;
pdd find(pdd A, pdd B, pdd C, pdd D) 
{ 
    // Line AB represented as a1x + b1y = c1 
    double a1 = B.second - A.second; 
    double b1 = A.first - B.first; 
    double c1 = a1*(A.first) + b1*(A.second); 
  
    // Line CD represented as a2x + b2y = c2 
    double a2 = D.second - C.second; 
    double b2 = C.first - D.first; 
    double c2 = a2*(C.first)+ b2*(C.second); 
  
    double determinant = a1*b2 - a2*b1; 
  
    if (determinant == 0) 
    { 
        // The lines are parallel. This is simplified 
        // by returning a pair of FLT_MAX 
        return make_pair(FLT_MAX, FLT_MAX); 
    } 
    else
    { 
        double x = (b2*c1 - b1*c2)/determinant; 
        double y = (a1*c2 - a2*c1)/determinant; 
        return make_pair(x, y); 
    } 
} 
double solve(int g,vector< vector< pair<double,double> > > &b,double si,double sj){
    
    double ans=0;
    int flg=0;
    if(g>0&&si>b[g-1][1].first&&si<b[g-1][2].first){
        g--;
        flg=1;
        ans+=b[g][2].first-b[g][1].first;
    }
    else if(sj<b[g][1].second){
        return b[g][1].second-b[g][0].second;
    }
    
    if(flg==0)
        ans+=b[g][1].second-b[g][0].second+b[g][2].first-b[g][1].first;
    for(int i=1+g;i<b.size();i++){
        pdd A,B,C,D;
        A={si,sj};
        B={b[i-1][2].first,b[i-1][2].second};
        C={b[i][0].first,b[i][0].second};
        D={b[i][1].first,b[i][1].second};
        pdd p=find(A,B,C,D);
        if(sj<b[i][1].second){
            ans+=(b[i][1].second-p.second);
            return ans;
        }
        if(p.second<=b[i][0].second){
            ans+=(b[i][1].second-b[i][0].second);
        }
        else if(p.second<=b[i][1].second){
            ans+=b[i][1].second-p.second;
            ans+=b[i][2].first-b[i][1].first;
        }
        else{
            pdd E;
            E={b[i][2].first,b[i][2].second};
            pdd e=find(A,B,D,E);
            ans+=b[i][2].first-e.first;
        } 
    }
    return ans;
    
}
void sorting(vector<pdd> &v){
    if(v[0].second>v[1].second){
        pdd p=v[1];
        v[1]=v[0];
        v[0]=p;
    }
    if(v[2].second<v[3].second){
        pdd p=v[3];
        v[3]=v[2];
        v[2]=p;
    }
}
bool cmp(vector<pair<double,double>> v1 ,vector<pair<double,double>> v2){
    
    return v1[0].first<v2[0].first;
}
int check(vector<vector<pdd>> &b,double si,double sj){
    
    for(int i=0;i<b.size();i++){
        if(si<b[i][0].first){
            return i;   
        }
    }
    return b.size();
    
}
int main (){
    
    int n;
    cin>>n;
    
    vector< vector< pair<double,double> > > b;
    
    while(n--){
        vector<pair<double,double>>v;
        for(int k=0;k<4;k++){
            double i,j;
            cin>>i>>j;
            v.push_back({i,j});
        }
        sorting(v);
        b.push_back(v);
    }
    
    double si,sj;
    cin>>si>>sj;
    // cout<<b[0][0].first<<" "<<b[0][0].second<<" "<<b[0][1].first<<" "<<b[0][1].second<<" "<<
    // b[0][2].first<<" "<<b[0][2].second<<" "<<b[0][3].first<<" "<<b[0][3].second<<" "<<
    // si<<" "<<sj<<" ";
    sort(b.begin(),b.end(),cmp);
    int g=check(b,si,sj);
    double ans=0;
    if(g<b.size())
        ans+=solve(g,b,si,sj);
    cout<<ans;  
    return 0;
    
}