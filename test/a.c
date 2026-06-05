
int f(int num){return num+2;}
const int a = 0;
static int b = 0;
int c = 10;

int main(int argc, char** argv){

    int(*fp)(int) = f;
    f(2);

    return 0;
}
