#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>
#include <cassert>

class Matrix:std::vector<std::vector<double>>{
private:
	int maxL;
public:
	Matrix(int n,int m,double a=0){
		resize(n);
		maxL=1;
		for(int i=0;i<size();i++){
			at(i).resize(m);
			if(n<=m)at(i).at(i)=a;
		}
	}
	Matrix(std::vector<std::vector<double>>a){
		int t;
		resize(a.size());
		for(int i=0;i<size();i++){
			at(i).resize(a[i].size());
			for(int j=0;j<a[i].size();j++){
				at(i).at(j)=a[i][j];
				t=log10(abs(at(i).at(j)))+1;
				if(at(i).at(j)<0)t++;
				if(t>maxL)maxL=t;
			}
		}
	}
	int row()const{return size();}
	int column()const{return at(0).size();}
	void operator+=(Matrix other){*this=*this+other;}
	void operator-=(Matrix other){*this=*this-other;}
	void operator*=(Matrix other){*this=*this*other;}
	void operator^=(int times){*this=*this^times;}
	void print(){
		for(int i=0;i<row();i++){
			if(i==0 && i==row()-1)std::cout<<"[";
			else if(i==0)std::cout<<"⎡";
			else if(i==row()-1)std::cout<<"⎣";
			else std::cout<<"⎢";
			for(int j=0;j<column();j++){
				std::cout<<std::setw(maxL)<<at(i).at(j);
				if(j==column()-1){
					if(i==0 && i==row()-1)std::cout<<"]";
					else if(i==0)std::cout<<"⎤";
					else if(i==row()-1)std::cout<<"⎦";
					else std::cout<<"⎥";
				}
				else std::cout<<" ";
			}
			std::cout<<std::endl;
		}
	}
	friend std::ostream & operator<<(std::ostream &out,const Matrix &a){
		for(int i=0;i<a.row();i++){
			for(int j=0;j<a.column();j++){
				out<<std::setw(a.maxL)<<a[i][j]<<" \n"[j==a.column()-1];
			}
		}
		return out;
	}
	friend std::istream & operator>>(std::istream &in,Matrix &a){
		int t;
		for(int i=0;i<a.row();i++){
			for(int j=0;j<a.column();j++){
				in>>a[i][j];
				t=log10(abs(a[i][j]))+1;
				if(a[i][j]<0)t++;
				if(t>a.maxL)a.maxL=t;
			}
		}
		return in;
	}
	friend int operator==(Matrix a,Matrix b){
		if(a.row()!=b.row() || a.column()!=b.column())return 0;
		for(int i=0;i<a.row();i++){
			for(int j=0;j<a.column();j++){
				if(a[i][j]!=b[i][j])return -1;
			}
		}
		return 1;
	}
	friend bool operator!=(Matrix a,Matrix b){return !(a==b);}
	friend Matrix operator+(Matrix a,Matrix b){
		assert(a==b);
		std::vector<std::vector<double>>c;
		c.resize(a.row());
		for(int i=0;i<a.row();i++){
			c[i].resize(a.column());
			for(int j=0;j<a.column();j++){
				c[i][j]=a[i][j]+b[i][j];
			}
		}
		Matrix ans(c);
		return ans;
	}
	friend Matrix operator-(Matrix a,Matrix b){return a+(-1*b);}
	friend Matrix operator*(Matrix a,double t){
		Matrix b(a.row(),a.column(),t);
		return a*b;
	}
	friend Matrix operator*(double t,Matrix a){return a*t;}
	friend Matrix operator*(Matrix a,Matrix b){
		assert(a==b);
		std::vector<std::vector<double>>c;
		c.resize(a.row());
		for(int i=0;i<a.row();i++){
			c[i].resize(a.column());
			for(int j=0;j<a.column();j++){
				for(int z=0;z<a.column();z++){
					c[i][j]+=a[i][z]*b[z][j];
				}
			}
		}
		Matrix ans(c);
		return ans;
	}
	friend Matrix operator^(Matrix a,int t){
		assert(t>0);
		Matrix b=a;
		while(--t)b=b*a;
		return b;
	}
	friend Matrix T(Matrix a){
		std::vector<std::vector<double>> c;
		c.resize(a.column());
		for(int i=0;i<a.column();i++){
			c[i].resize(a.row());
			for(int j=0;j<a.row();j++){
					c[i][j]=a[j][i];
			}
		}
		Matrix ans(c);
		return ans;
	}
	friend Matrix inverse(Matrix a){
		double d=det(a);
		assert(d);
		return (1/d)*adj(a);
	}
	friend double det(Matrix a){
		double ans=0;
		if(a.row()==1)ans=a[0][0];
		else for(int i=0;i<a.column();i++){
				ans+=pow(-1,i)*a[0][i]*det(cof(a,0,i));
		}
		return ans;
	}
	friend Matrix cof(Matrix a,int x,int y){
		assert(a.row()==a.column());
		std::vector<std::vector<double>>c;
		c.resize(a.row()-1);
		int q=0,w=0;
		for(int i=0;i<a.row()-1;i++){
			c[i].resize(a.column()-1);
			w=0;
			if(q==x)q++;
			for(int j=0;j<a.column()-1;j++){
				if(w==y)w++;
				c[i][j]=a[q][w];
				w++;
			}
			q++;
		}
		Matrix ans(c);
		return ans;
	}
	friend Matrix adj(Matrix a){
		assert(a.row()==a.column());
		std::vector<std::vector<double>>c;
		c.resize(a.row());
		for(int i=0;i<a.row();i++){
			c[i].resize(a.column());
			for(int j=0;j<a.column();j++){
				c[i][j]=pow(-1,i+j)*det(cof(a,i,j));
			}
		}
		Matrix ans(c);
		return T(ans);
	}
};

using namespace std;

int main(){
	int n,m;
	cin>>n>>m;
	Matrix a(n,m);
	Matrix b(n,m);
	cin>>a>>b;
	a+=b;
	a.print();
	return 0;
}
