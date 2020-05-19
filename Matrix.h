#include<iomanip>
#include<cmath>
class Matrix{
    private:
        int _n;
        int _m;
        int _arr[100][100];
        int _maxL;
    public:
        Matrix(){}
        Matrix(int n,int m,int a=0){
            _n=n;
            _m=m;
            _maxL=log10(a)+1;
            for(int i=1;i<=_n;i++){
                for(int j=1;j<=_m;j++){
                    if(i==j)_arr[i][j]=a;
                    else _arr[i][j]=0;
                }
            }
        }
        Matrix(int n,int m,int a[100][100]){
            _n=n;
            _m=m;
            _maxL=0;
            int t=0;
            for(int i=1;i<=_n;i++){
                for(int j=1;j<=_m;j++){
                    _arr[i][j]=a[i-1][j-1];
                    t=log10(abs(_arr[i][j]))+1;
                    if(_arr[i][j]<0)t++;
                    if(t>_maxL)_maxL=t;
                }
            }
        }
        friend Matrix operator+(Matrix a,Matrix b){
            if(a._n!=b._n &&a._m!=b._m){
                cerr<<"two Matrix's size need to be same"<<endl;
                exit(1);
            }
            int c[100][100];
            for(int i=1;i<=a._n;i++){
                for(int j=1;j<=a._m;j++){
                    c[i-1][j-1]=a._arr[i][j]+b._arr[i][j];
                }
            }
            Matrix ans(a._n,a._m,c);
            return ans;
        }
        friend Matrix operator*(Matrix a,Matrix b){
            if(a._m!=b._n){
                cerr<<"A's m and B's n need to be same."<<endl;
                exit(1);
            }
            int c[100][100];
            for(int i=1;i<=a._n;i++){
                for(int j=1;j<=b._m;j++){
                    c[i-1][j-1]=0;
                    for(int z=1;z<=a._m;z++){
                        c[i-1][j-1]+=a._arr[i][z]*b._arr[z][j];
                    }
                }
            }
            Matrix ans(a._n,b._m,c);
            return ans;
        }
        friend Matrix operator*(int t,Matrix a){
            Matrix b(a._n,a._n,t);
            return b*a;
        }
        friend Matrix operator*(Matrix a,int t){return t*a;}
        friend Matrix operator-(Matrix a,Matrix b){
            return  a+(-1*b);
        }
        friend int det(Matrix a){
            if(a._n!=a._m){
                cerr<<"the Matrix must be sqaure"<<endl;
            }
            int ans=0;
            if(a._n==1)ans=a._arr[1][1];
            else{
                for(int i=1;i<=a._m;i++){
                    ans+=int(pow(-1,i+1))*a._arr[1][i]*det(cof(a,1,i));
                }
            }
            return ans;
        }
        friend Matrix T(Matrix a){
            int c[100][100];
            for(int i=1;i<=a._n;i++){
                for(int j=1;j<=a._m;j++){
                    c[j-1][i-1]=a._arr[i][j];
                }
            }
            Matrix ans(a._m,a._n,c);
            return ans;
        }
        friend Matrix cof(Matrix a,int x,int y){
            int n=a._n-1;
            int m=a._m-1;
            int c[100][100];
            int q=0,w=0;
            for(int i=1;i<=a._n;i++){
                for(int j=1;j<=a._m;j++){
                    if(i!=x && j!=y){
                        c[q][w]=a._arr[i][j];
                        w++;
                    }
                }
                if(i!=x){q++;w=0;}
            }
            Matrix ans(n,m,c);
            return ans;
        }
        friend Matrix adj(Matrix a){
            if(a._n!=a._m){
                cerr<<"the Matrix must be sqaure"<<endl;
            }
            int c[100][100];
            for(int i=1;i<=a._n;i++){
                for(int j=1;j<=a._m;j++){
                    c[i-1][j-1]=int(pow(-1,i+j))*det(cof(a,i,j));
                }
            }
            Matrix ans(a._n,a._m,c);
            return T(ans);
        }
        friend ostream & operator<<(ostream &out,const Matrix &a){
            for(int i=1;i<=a._n;i++){
                if(i==1 && i==a._n)out<<"[";
                else if(i==1)out<<"⎡";
                else if(i==a._n)out<<"⎣";
                else out<<"⎢";
                for(int j=1;j<=a._m;j++){
                    out<<setw(a._maxL)<<a._arr[i][j];
                    if(j==a._m){
                        if(i==1 && i==a._n)out<<"]";
                        else if(i==1)out<<"⎤";
                        else if(i==a._n)out<<"⎦";
                        else out<<"⎥";
                    }
                    else out<<" ";
                }
                out<<endl;
            }
            return out;
        }
    	friend istream & operator>>(istream &in,Matrix &a){
            int t;
            for(int i=1;i<=a._n;i++){
                for(int j=1;j<=a._m;j++){
                    in>>a._arr[i][j];
                    t=log10(abs(a._arr[i][j]))+1;
                    if(a._arr[i][j]<0)t++;
                    if(t>a._maxL)a._maxL=t;
                }
            }
            return in;
        }
        friend Matrix inverse(Matrix a){
            int d=det(a);
            if(!d){
                cerr<<"det can't be 0."<<endl;
                exit(1);
            }
            return (1/d)*adj(a);
        }
        friend Matrix operator^(Matrix a,int t){
            Matrix b=a;
            if(t>0)while(--t)b=b*a;
            else while(t++)b=inverse(b);
            return b;
        }
        friend bool operator==(Matrix a,Matrix b){
            if(a._n!=b._n || a._m!=b._m)return false;
            for(int i=1;i<a._n;i++){
                for(int j=1;j<a._m;j++){
                    if(a._arr[i][j]!=b._arr[i][j])return false;
                }
            }
            return true;
        }
        friend bool operator!=(Matrix a,Matrix b){return !(a==b);}
};
