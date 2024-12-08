#include <iostream>
#include <algorithm>
#include <iomanip>



double f(double pos, double v,double n){
    double b = (n - pos + n) / v;	
	double a = (pos + n) / v;
	return std::min(a,b);
}

void solve(){
	double n,p1,v1,p2,v2;
	std::cin>>n>>p1>>v1>>p2>>v2;
	
	if(p1 > p2){
        std::swap(v1,v2);
		std::swap(p1,p2);
	}
	double ans = 9999999999999999;
	
	ans = std::min(ans , f(p1,v1,n));
	ans = std::min(ans , f(p2,v2,n));
	ans = std::min(ans , std::max((n-p1)/v1 , p2/v2));
	
	double l = p1,r = p2;
	for(int i=1;i<=100;i++){
		double mid = (l + r) / 2;
		double ans1 = f(p1,v1,mid); 
		double ans2 = f(n-p2,v2,n-mid);
		ans = std::min(ans,std::max(ans1,ans2));
		if(ans1 < ans2) l = mid;
		else r = mid;
	}
	std::cout<<std::setprecision(12)<<ans<<"\n";
}

int main(){
	int t;
	std::cin>>t;
	for(int i = 0; i < t; i++) solve();
}

/*
2

4306.063 4079.874 0.607 1033.423 0.847
*/
